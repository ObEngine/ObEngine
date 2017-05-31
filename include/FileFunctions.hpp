#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <tinydir/tinydir.h>

namespace obe
{
    namespace Functions
    {
        namespace File
        {
            std::vector<std::string> listDirInDir(const std::string& path);
            std::vector<std::string> listFileInDir(const std::string& path);
            bool fileExists(const std::string& path);
            void copy(const std::string& source, const std::string& target);
            std::string separator();
        }
    }
}
