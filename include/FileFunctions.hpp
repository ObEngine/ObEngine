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
            class FilePath
            {
            };
            class File
            {
                
            };
            class Directory
            {
                
            };
            std::vector<std::string> getDirectoryList(const std::string& path);
            std::vector<std::string> getFileList(const std::string& path);
            bool fileExists(const std::string& path);
            bool directoryExists(const std::string& path);
            bool createDirectory(const std::string& path);
            bool createFile(const std::string& path);
            void copyFile(const std::string& source, const std::string& target);
            void copyDirectory(const std::string& source, const std::string& target);

            std::string getCurrentDirectory();
            std::string separator();
        }
    }
}
