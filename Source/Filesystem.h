#pragma once
#include <string>

namespace ColorTree
{
    namespace Filesystem
    {
        std::string GetExecutablePath();
        std::string GetPath(std::string fileName);
        std::string GetFileContents(std::string fileName);
    }
}
