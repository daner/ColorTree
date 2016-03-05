#include "Webserver.h"
#include <iostream>

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

static void event_handler(mg_connection* nc, int ev, void* ev_data)
{
	if (ev == MG_EV_HTTP_REQUEST)
	{
		auto hm = static_cast<http_message*>(ev_data);

		mg_serve_http(nc, hm, s_http_server_opts);
	}
}

namespace ColorTree
{
	Webserver::Webserver() :
		manager{ nullptr },
		connection{ nullptr },
		running{ false },
		workerThread{}
	{

	}

	Webserver::~Webserver()
	{
		if(workerThread.joinable())
		{
			running.store(false);
			workerThread.join();
		}
	}

	void Webserver::start()
	{
		running.store(true);
		//workerThread = std::thread(std::bind(&Webserver::workerFunction, this));
		workerFunction();
	}

	void Webserver::workerFunction()
	{
		mg_mgr_init(&manager, nullptr);
		connection = mg_bind(&manager, s_http_port, event_handler);

		mg_set_protocol_http_websocket(connection);
		s_http_server_opts.document_root = "C:/Temp";
		s_http_server_opts.enable_directory_listing = "yes";

		std::cout << "Starting web server on port " << s_http_port << std::endl;

		while(running.load())
		{
			mg_mgr_poll(&manager, 1000);
		}

		mg_mgr_free(&manager);
	}
}
