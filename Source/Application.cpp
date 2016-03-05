#include "Application.h"
#include <chrono>
#include <iostream>
#include <functional>
#include <string>

using namespace std::chrono_literals;

namespace ColorTree 
{
	Application::Application()
	{

	}

	void Application::run()
	{
        webserver.handleFunctions["/test"] = std::bind(&Application::testMethod, this, std::placeholders::_1);


		webserver.start();
		
		int a;

		std::cin >> a;

	}

    std::string Application::testMethod(std::string body)
    {
        std::cout << body << std::endl;

        return "Test Done";
    }
}
