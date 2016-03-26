#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include <queue>
#include <list>
#include <mutex>
#include <glm/glm.hpp>
#include "Webserver.h"
#include "ColorNode.h"
#include "Graphics/Quad.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include <json/json.h>
#include "Settings.h"

namespace ColorTree
{
    class Application
    {
    public:
        Application(GLFWwindow* window);

        void Init();

        void Update();
        void Draw() const;

        void WindowSizeCallback(int width, int height);
        void KeyCallback(int key, int scancode, int action, int mods) const;

    private:
        Settings settings;

        Webserver webserver;
        HandlerResult GetImage(std::string method, std::string body);
        HandlerResult ReciveColor(std::string method, std::string body);
        HandlerResult SaveTree(std::string method, std::string body) const;
        HandlerResult LoadTree(std::string method, std::string body);
        HandlerResult Randomize(std::string method, std::string body);

        int idCounter;

        std::mutex colorMutex;
        std::queue<glm::vec3> colorQueue;

        std::unique_ptr<ColorNode> rootNode;
        std::list<ColorNode*> splitList;
        void SplitNode(ColorNode* node);

        GLFWwindow* glfwWindow;
        glm::ivec2 windowSize;

        Quad quad;
        Texture texture;
        Shader shader;

        std::mutex saveMutex;
        std::atomic<bool> saveFramebufferToMemory;
        std::vector<unsigned char> saveBuffer;

        std::chrono::time_point<std::chrono::system_clock> lastColorAddedTime;

        void AppendColor(ColorNode* node, Json::Value* jsonArray) const;
    };
}
