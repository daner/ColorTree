#include "Filesystem.h"
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

namespace ColorTree
{
    namespace Filesystem
    {
        string GetExecutablePath()
        {
            WCHAR path[MAX_PATH];
            GetModuleFileNameW(nullptr, path, MAX_PATH);
            wstring wpath(path);
            auto dir = wpath.substr(0, wpath.find_last_of('\\') + 1);
            return string(begin(dir), end(dir));
        }

        string GetPath(string fileName)
        {
            return GetExecutablePath() + fileName;
        }

        string GetFileContents(string fileName)
        {
            string result;
            fstream file(fileName.c_str(), ios::in);
            if (file.is_open())
            {
                file.seekg(0, ios::end);
                result.resize(file.tellg());
                file.seekg(0, ios::beg);
                result.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
            }
            return result;
        }
    }
}
