#pragma once
#include <memory>
#include "Webserver.h"
#include "ColorNode.h"

namespace ColorTree
{
	class Application 
	{
	public:
		Application();
		void Run();
	
	private:
		Webserver webserver;
        std::string ReciveColor(std::string body);

        std::unique_ptr<ColorNode> rootNode;
	};
}
