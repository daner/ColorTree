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

namespace ColorTree
{
	class Application 
	{
	public:
		Application(GLFWwindow* window);

		void Init();
		void Update();
		void Draw() const;
		
		void KeyCallback(int key, int scancode, int action, int mods);

	private:
		Webserver webserver;
		std::mutex colorMutex;
		std::queue<glm::vec3> colorQueue;
		std::string ReciveColor(std::string method, std::string body);

        std::unique_ptr<ColorNode> rootNode;
		std::list<ColorNode*> splitList;
        void SplitNode(ColorNode* node);

		GLFWwindow* glfwWindow;

        Quad quad;
        Texture texture;
        Shader shader;
	};
}
