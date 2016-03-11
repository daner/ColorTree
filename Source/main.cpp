#include <memory>
#include <GL/glew.h>
#include "Application.h"
#include <iostream>

using namespace std;
using namespace ColorTree;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    static_cast<Application*>(glfwGetWindowUserPointer(window))->WindowSizeCallback(width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<Application*>(glfwGetWindowUserPointer(window))->KeyCallback(key, scancode, action, mods);
}

int main(int argc, char* argv[])
{
	if (!glfwInit())
	{
		cout << "glfwInit failed, aborting." << endl;
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	auto window = glfwCreateWindow(960, 540, "ColorTree", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
    auto err = glewInit();
	if (err != GLEW_OK)
	{
		cout << "glewInit failed, aborting. Error: " << glewGetErrorString(err) << endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	cout << "GLEW: " << reinterpret_cast<const char*>(glewGetString(GLEW_VERSION)) << endl
		<< "OpenGL: " << reinterpret_cast<char const*>(glGetString(GL_VERSION)) << endl
		<< "GLSL: " << reinterpret_cast<char const*>(glGetString(GL_SHADING_LANGUAGE_VERSION)) << endl
		<< "Renderer: " << reinterpret_cast<char const*>(glGetString(GL_RENDERER)) << endl
		<< "Vendor: " << reinterpret_cast<char const*>(glGetString(GL_VENDOR)) << endl;

	glfwSwapInterval(1);

	{
		auto app = make_unique<Application>(window);

		glfwSetWindowUserPointer(window, app.get());
		glfwSetKeyCallback(window, &keyCallback);
        glfwSetFramebufferSizeCallback(window, &framebufferSizeCallback);

		app->Init();

		while (!glfwWindowShouldClose(window))
		{
			app->Draw();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();

	return 0;
}