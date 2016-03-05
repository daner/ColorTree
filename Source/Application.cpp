#include "Application.h"
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

namespace ColorTree 
{
	Application::Application()
	{

	}

	void Application::run()
	{
		webserver.start();
		
		int a;

		std::cin >> a;

	}
}
