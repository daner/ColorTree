#include "Settings.h"
#include "Filesystem.h"
#include <json/json.h>
#include <iostream>

namespace ColorTree
{
    using namespace std;
    using namespace Filesystem;

    Settings::Settings() :
        WebRootPath{"C:/Dev/Projects/ColorTree/Web/wwwroot"}
    {
    }

    Settings::Settings(string fileName) : Settings()
    {
        InitWithFile(fileName);
    }

    void Settings::InitWithFile(string fileName)
    {
        try
        {
            auto content = GetFileContents(GetPath(fileName));

            if (content.length() == 0) return;

            Json::Value root;
            Json::Reader reader;

            if (reader.parse(content, root))
            {
                WebRootPath = root["WebRootPath"].asString();
            }
        }
        catch (exception &e)
        {
            cout << e.what() << endl;
        }
    }
}
