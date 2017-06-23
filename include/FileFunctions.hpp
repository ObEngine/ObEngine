#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#include <tinydir/tinydir.h>
#ifdef _USE_CPP_NEW_FS
#include <filesystem>
#endif

#ifdef _WIN32
#include <io.h>
#include <direct.h>
#include <winbase.h>
#define FsAccess _access
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define FsAccess access
#define GetCurrentDir getcwd
#endif



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
            void createFile(const std::string& path);
            void copy(const std::string& source, const std::string& target);
            bool deleteFile(const std::string& path);
            bool deleteDirectory(const std::string& path);

            std::string getCurrentDirectory();
            std::string separator();
        }
    }
}
