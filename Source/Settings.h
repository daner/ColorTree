#pragma once
#include <string>

namespace ColorTree
{
	class Settings
	{
	public:
		Settings();
        Settings(std::string fileName);
        void InitWithFile(std::string fileName);

		std::string WebRootPath;
	};
}