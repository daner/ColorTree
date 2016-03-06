#include "Application.h"
#include <iostream>
#include <functional>
#include <string>
#include <json/json.h>

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
		Json::Value root;
		Json::Reader reader;

		if(reader.parse(body, root))
		{
			auto r = root["r"].asFloat();
			auto g = root["g"].asFloat();
			auto b = root["b"].asFloat();

			std::cout << "R: " << r << " G: " << g << " B: " << b << std::endl;

			return "{ \"Message\": \"Ok\" }";
		}
        return "{ \"Message\": \"Failed to parse json\" }";
    }
}
