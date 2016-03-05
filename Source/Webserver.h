#pragma once
#include <mongoose.h>
#include <atomic>
#include <thread>

namespace ColorTree
{
	class Webserver
	{
	public:
		Webserver();
		~Webserver();
		void start();

	private:
		mg_mgr manager;
		mg_connection* connection;

		void workerFunction();

		std::atomic<bool> running;
		std::thread workerThread;
	};
}