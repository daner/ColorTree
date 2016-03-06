#include <GL/glew.h>
#include "Application.h"
#include <functional>
#include <json/json.h>

namespace ColorTree
{
    using namespace std;
    using namespace glm;

    Application::Application(GLFWwindow* window) :
        glfwWindow{ window }
    {
    }

    void Application::Init()
    {
        webserver.AddHandleFunction("/color", bind(&Application::ReciveColor, this, placeholders::_1, placeholders::_2));
        webserver.Start();

        rootNode = make_unique<ColorNode>(ivec2{ 0, 0 }, ivec2{ 960, 540 });
        splitList.push_back(rootNode.get());
        
		shader.InitWithSourceFiles("texture.vert", "texture.frag");
        quad.Init();
        texture.Init(rootNode->Size(), { 0.0f, 0.0f, 0.0f });
        
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

	void Application::Update()
	{
		vec3 color;
		auto colorInQueue = false;
		
		{
			lock_guard<mutex> lock(colorMutex);
			if (!colorQueue.empty())
			{
				color = colorQueue.front();
				colorQueue.pop();
				colorInQueue = true;
			}
		}

		if (colorInQueue)
		{
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
					node->Color(color);
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
		}
	}

	void Application::Draw() const
	{
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Bind();
        texture.Bind(0);
        quad.Draw();
    }

    void Application::SplitNode(ColorNode* node)
    {
        node->Split();
        node->Child(0)->Color(node->Color());
        for (auto i = 0; i < 4; i++)
        {
            splitList.push_back(node->Child(i));
        }
    }

    void Application::KeyCallback(int key, int scancode, int action, int mods)
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

    string Application::ReciveColor(string method, string body)
    {
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
            return "{ \"Message\": \"Ok\" }";
        }
        return "{ \"Message\": \"Failed to parse json\" }";
    }
}
