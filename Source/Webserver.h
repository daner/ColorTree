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
    enum class ResultType
    {
        Text,
        Data
    };

    struct HandlerResult
    {
        ResultType Type;

        std::string TextContent;

        unsigned char* DataContent;
        int DataLength;
    };

    typedef std::function<HandlerResult(std::string, std::string)> HandlerFunction;

    class Webserver
    {
    public:
        Webserver();
        ~Webserver();
        void Start();
        void AddHandleFunction(std::string path, HandlerFunction fn);

        std::unordered_map<std::string, HandlerFunction>::iterator HandlersBegin();
        std::unordered_map<std::string, HandlerFunction>::iterator HandlersEnd();

    private:
        mg_mgr manager;
        mg_connection* connection;

        std::string rootPath;
        std::atomic<bool> running;
        std::thread workerThread;
        std::unordered_map<std::string, HandlerFunction> handleFunctions;

        void workerFunction();
    };
}