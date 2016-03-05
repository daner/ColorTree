#pragma once
#include "Webserver.h"

namespace ColorTree
{
	class Application 
	{
	public:
		Application();
		void run();
	
	private:
		Webserver webserver;

        std::string testMethod(std::string body);

	};
}
