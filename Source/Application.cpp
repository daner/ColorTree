#include <GL/glew.h>
#include <functional>
#include <json/json.h>
#include <vector>
#include <chrono>
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_WRITE_NO_STDIO
#include <stb_image_write.h>
#include "Application.h"

namespace ColorTree
{
    using namespace std;
    using namespace glm;
    using namespace chrono;
    using namespace chrono_literals;

    Application::Application(GLFWwindow* window) :
        glfwWindow{ window },
        saveFramebufferToMemory{ false },
        idCounter{ 0 }
    {
    }

    void Application::Init()
    {
        webserver.AddHandleFunction("/color", bind(&Application::ReciveColor, this, placeholders::_1, placeholders::_2));
        webserver.AddHandleFunction("/save", bind(&Application::SaveTree, this, placeholders::_1, placeholders::_2));
        webserver.AddHandleFunction("/image", bind(&Application::GetImage, this, placeholders::_1, placeholders::_2));
        webserver.AddHandleFunction("/load", bind(&Application::LoadTree, this, placeholders::_1, placeholders::_2));
        webserver.Start();

        windowSize = { 960, 540 };

        rootNode = make_unique<ColorNode>(ivec2{ 0, 0 }, ivec2{ 2048, 2048 });
        lastColorAddedTime = system_clock::now();
        splitList.push_back(rootNode.get());

        shader.InitWithSourceFiles("texture.vert", "texture.frag");
        quad.Init();
        texture.Init(rootNode->Size(), { 0.0f, 0.0f, 0.0f });

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void Application::Update()
    {
        if (colorMutex.try_lock())
        {
            if (!colorQueue.empty() && (system_clock::now() - lastColorAddedTime) > 300ms)
            {
                auto color = colorQueue.front();
                colorQueue.pop();

                auto assignedColorToNode = false;
                while (!assignedColorToNode)
                {
                    auto node = splitList.front();
                    splitList.pop_front();

                    if (node->Status() == NodeStatus::Assigned)
                    {
                        SplitNode(node);
                    }
                    else
                    {
                        node->Color(++idCounter, color);
                        texture.UpdateColor(node->Offset(), node->Size(), node->Color());
                        if (node->Parent() != nullptr && node->Parent()->Child(1) == node)
                        {
                            auto sibling = node->Parent()->Child(3);
                            texture.UpdateColor(sibling->Offset(), sibling->Size(), node->Color());
                        }
                        assignedColorToNode = true;
                        SplitNode(node);
                    }
                }
                lastColorAddedTime = system_clock::now();
            }
            colorMutex.unlock();
        }

        if (saveFramebufferToMemory.load())
        {
            saveBuffer.resize(windowSize.x * windowSize.y * 4);
            glReadPixels(0, 0, windowSize.x, windowSize.y, GL_RGBA, GL_UNSIGNED_BYTE, saveBuffer.data());
            saveFramebufferToMemory.store(false);
        }
    }

    void Application::Draw() const
    {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Bind();
        texture.Bind(0);
        quad.Draw();
    }

    void Application::WindowSizeCallback(int width, int height)
    {
        if (width > 0 && height > 0)
        {
            glViewport(0, 0, width, height);
            windowSize = { width, height };
        }
    }

    void Application::SplitNode(ColorNode* node)
    {
        node->Split();
        node->Child(0)->Color(-1, node->Color());
        for (auto i = 0; i < 4; i++)
        {
            splitList.push_back(node->Child(i));
        }
    }

    void Application::KeyCallback(int key, int scancode, int action, int mods) const
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
            break;
        default:
            break;
        }
    }

    HandlerResult Application::GetImage(string method, string body)
    {
        HandlerResult result{};
        result.Type = ResultType::Data;
        {
            lock_guard<mutex> lock(saveMutex);
            saveFramebufferToMemory.store(true);

            while (saveFramebufferToMemory.load())
            {
				this_thread::sleep_for(1ms);
            }
			
			//Flip image
            for (auto j = 0; j * 2 < windowSize.y; ++j)
            {
                auto x = j * windowSize.x * 4;
                auto y = (windowSize.y - 1 - j) * windowSize.x * 4;
                for (auto i = windowSize.x * 4; i > 0; --i)
                {
                    auto tmp = saveBuffer.data()[x];
                    saveBuffer.data()[x] = saveBuffer.data()[y];
                    saveBuffer.data()[y] = tmp;
                    ++x;
                    ++y;
                }
            }		
			result.DataContent = stbi_write_png_to_mem(saveBuffer.data(), 0, windowSize.x, windowSize.y, 4, &result.DataLength);
		}
        result.Headers = "Content-Type: image/png\r\nContent-Disposition: attachment; filename=\"image.png\"";
        return result;
    }

    HandlerResult Application::ReciveColor(string method, string body)
    {
        HandlerResult result{};
        result.Type = ResultType::Text;

        Json::Value root;
        Json::Reader reader;
        if (reader.parse(body, root))
        {
            auto r = clamp(root["r"].asFloat() / 255.0f, 0.0f, 1.0f);
            auto g = clamp(root["g"].asFloat() / 255.0f, 0.0f, 1.0f);
            auto b = clamp(root["b"].asFloat() / 255.0f, 0.0f, 1.0f);
            {
                lock_guard<mutex> lock(colorMutex);
                colorQueue.push({ r, g, b });
            }
            result.TextContent = "{ \"Message\": \"Ok\" }";
        }
        else
        {
            result.TextContent = "{ \"Message\": \"Failed to parse json\" }";
        }
        result.Headers = "Content-Type: application/json";
        return result;
    }

    HandlerResult Application::SaveTree(string method, string body) const
    {
        HandlerResult result{};
        result.Type = ResultType::Text;
        Json::Value root;
        AppendColor(rootNode.get(), &root);
        Json::FastWriter writer;
        result.TextContent = writer.write(root);
        result.Headers = "Content-Type: application/json\r\nContent-Disposition: attachment; filename=\"tree.json\"";
        return result;
    }

    void Application::AppendColor(ColorNode* node, Json::Value* jsonArray) const
    {
        if (node->ColorId() > 0)
        {
            Json::Value color;
            color["Id"] = node->ColorId();
            color["r"] = node->Color().r * 255.0f;
            color["g"] = node->Color().g * 255.0f;
            color["b"] = node->Color().b * 255.0f;
            jsonArray->append(color);
        }
        for (auto i = 0; i < 4; i++)
        {
            if (node->Child(i) != nullptr)
            {
                AppendColor(node->Child(i), jsonArray);
            }
        }
    }

    HandlerResult Application::LoadTree(string method, string body)
    {
        HandlerResult result{};
        result.Type = ResultType::Text;

        auto first = body.find("\r\n\r\n");
        auto second = body.substr(first + 4).find("\n\r\n");
        auto content = body.substr(first + 4, second);

        Json::Reader reader;
        Json::Value root;
        if (reader.parse(content, root))
        {
            if (root.isArray())
            {
                vector<OrderedColor> orderedColors;

                for (auto& object : root)
                {
                    OrderedColor orderedColor{};
                    orderedColor.colorId = object["Id"].asInt();
                    orderedColor.color.r = object["r"].asFloat() / 255.0f;
                    orderedColor.color.g = object["g"].asFloat() / 255.0f;
                    orderedColor.color.b = object["b"].asFloat() / 255.0f;
                    orderedColors.push_back(orderedColor);
                }

                sort(begin(orderedColors), end(orderedColors), [](const OrderedColor& a, const OrderedColor& b) { return a.colorId < b.colorId; });

                {
                    lock_guard<mutex> lock(colorMutex);

                    rootNode = make_unique<ColorNode>(ivec2{ 0, 0 }, ivec2{ 2048, 2048 });
                    splitList.clear();
                    splitList.push_back(rootNode.get());

                    for (auto& orderedColor : orderedColors)
                    {
                        colorQueue.push(orderedColor.color);
                    }
                }
                result.TextContent = "{ \"Message\": \"Ok\" }";
            }
            else
            {
                result.TextContent = "{ \"Message\": \"Failed\" }";
            }
        }
        else
        {
            result.TextContent = "{ \"Message\": \"Failed\" }";
        }

        result.Headers = "Content-Type: application/json";
        return result;
    }
}
