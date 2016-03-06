#include "Filesystem.h"
#include <windows.h>
#include <string>

using namespace std;

namespace ColorTree
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
}
