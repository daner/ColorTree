#include <GL/glew.h>
#include "Application.h"
#include <iostream>
#include <functional>
#include <string>
#include <json/json.h>

using namespace std;

namespace ColorTree
{
	Application::Application(GLFWwindow* window) :
		glfwWindow{ window }
	{
	}

	void Application::Init()
	{
		webserver.AddHandleFunction("/color", bind(&Application::ReciveColor, this, placeholders::_1));
		webserver.Start();

		glClearColor(0.8f, 0.2f, 0.2f, 1.0f);
	}

	void Application::Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);

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

	string Application::ReciveColor(string body)
	{
		Json::Value root;
		Json::Reader reader;
		if (reader.parse(body, root))
		{
			auto r = root["r"].asFloat();
			auto g = root["g"].asFloat();
			auto b = root["b"].asFloat();
			//cout << "R: " << r << " G: " << g << " B: " << b << endl;
			{
				lock_guard<mutex> lock(colorMutex);
				colorQueue.push({ r, g, b });
			}
			return "{ \"Message\": \"Ok\" }";
		}
		return "{ \"Message\": \"Failed to parse json\" }";
	}
}
