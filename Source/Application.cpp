#include "Application.h"
#include <iostream>
#include <functional>
#include <string>

namespace ColorTree 
{
	Application::Application()
	{
	}

	void Application::Run()
	{
        webserver.AddHandleFunction("/color", std::bind(&Application::ReciveColor, this, std::placeholders::_1));
		webserver.Start();
		
		int a;

		std::cin >> a;

	}

    std::string Application::ReciveColor(std::string body)
    {
        std::cout << body << std::endl;

        return "{ \"Message\": \"Ok\" }";
    }
}
