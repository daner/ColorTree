#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include <atomic>
#include <queue>
#include <string>
#include <list>
#include <mutex>
#include <glm/glm.hpp>
#include "Webserver.h"
#include "ColorNode.h"

namespace ColorTree
{
	class Application 
	{
	public:
		Application(GLFWwindow* window);

		void Init();
		void Draw();
		void KeyCallback(int key, int scancode, int action, int mods);

	private:
		Webserver webserver;
        std::string ReciveColor(std::string body);
		std::mutex colorMutex;
		std::queue<glm::vec3> colorQueue;

        std::unique_ptr<ColorNode> rootNode;
		std::list<ColorNode*> splitList;

		GLFWwindow* glfwWindow;
	};
}
