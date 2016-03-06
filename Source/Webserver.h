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
    typedef std::function<std::string(std::string, std::string)> HandleFunction;

	class Webserver
	{
	public:
		Webserver();
		~Webserver();
		void Start();
        void AddHandleFunction(std::string path, HandleFunction fn);

        std::unordered_map<std::string, HandleFunction>::iterator HandlersBegin();
        std::unordered_map<std::string, HandleFunction>::iterator HandlersEnd();

	private:
		mg_mgr manager;
		mg_connection* connection;

        std::string rootPath;
		std::atomic<bool> running;
		std::thread workerThread;
        std::unordered_map<std::string, HandleFunction> handleFunctions;

        void workerFunction();
	};
}