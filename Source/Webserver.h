#pragma once
#pragma warning (push)
#pragma warning (disable: 4273 4005)
#include <mongoose.h>
#pragma warning (push)

#include <atomic>
#include <thread>
#include <unordered_map>

namespace ColorTree
{
	class Webserver
	{
	public:
		Webserver();
		~Webserver();
		void start();


        std::unordered_map<std::string, std::function<std::string(std::string)>> handleFunctions;

	private:
		mg_mgr manager;
		mg_connection* connection;

        std::string rootPath;

		void workerFunction();

		std::atomic<bool> running;
		std::thread workerThread;

        
	};
}