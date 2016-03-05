#include "Webserver.h"
#include "Filesystem.h"
#include <iostream>

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

static void event_handler(mg_connection* nc, int ev, void* ev_data)
{
	if (ev == MG_EV_HTTP_REQUEST)
	{
		auto hm = static_cast<http_message*>(ev_data);
        auto webserver = static_cast<ColorTree::Webserver*>(nc->mgr->user_data);
        auto handlerFound = false;

        for (auto it = begin(webserver->handleFunctions); it != end(webserver->handleFunctions); ++it)
        {
            if(mg_vcmp(&hm->uri, it->first.c_str()) == 0)
            {
                handlerFound = true;
                auto result = it->second({ hm->body.p, hm->body.len });
                mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
                mg_send_http_chunk(nc, result.c_str(), result.length());
                mg_send_http_chunk(nc, "", 0);
            }
        }
        
        if(!handlerFound)
        {
            mg_serve_http(nc, hm, s_http_server_opts);
        }	
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
        rootPath = GetExecutablePath() + "/Resources/Web";
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
		workerThread = std::thread(std::bind(&Webserver::workerFunction, this));
	}

	void Webserver::workerFunction()
	{
		mg_mgr_init(&manager, this);
		connection = mg_bind(&manager, s_http_port, event_handler);

		mg_set_protocol_http_websocket(connection);
        s_http_server_opts.document_root = rootPath.c_str();
		s_http_server_opts.enable_directory_listing = "yes";

		std::cout << "Starting web server on port " << s_http_port << std::endl;

		while(running.load())
		{
			mg_mgr_poll(&manager, 1000);
		}

        std::cout << "Shutting down web server." << std::endl;
		mg_mgr_free(&manager);
	}
}
