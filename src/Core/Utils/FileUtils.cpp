#include <string>
#include <vector>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

#include <experimental/filesystem>

#include <Debug/Logger.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::Utils::File
{
    std::vector<std::string> getDirectoryList(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Get Directory List at {0}", path);

        std::vector<std::string> folderList;
        for (auto& p : std::experimental::filesystem::directory_iterator(path))
        {
            if (std::experimental::filesystem::is_directory(p))
            {
                folderList.push_back(std::experimental::filesystem::path(p.path()).filename().string());
            }
        }
        return folderList;
    }

    std::vector<std::string> getFileList(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Get File List at {0}", path);

        std::vector<std::string> fileList;
        for (auto& p : std::experimental::filesystem::directory_iterator(path))
        {
            if (std::experimental::filesystem::is_regular_file(p))
            {
                fileList.push_back(std::experimental::filesystem::path(p.path()).filename().string());
            }
        }
        return fileList;
    }

    bool fileExists(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Test File existence at {0}", path);
        
		return std::experimental::filesystem::exists(path) && std::experimental::filesystem::is_regular_file(path);
    }

    bool directoryExists(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Get Directory existence at {0}", path);

        return std::experimental::filesystem::exists(path) && std::experimental::filesystem::is_directory(path);
    }

    bool createDirectory(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Create Directory at {0}", path);

        return std::experimental::filesystem::create_directory(path);
    }

    void createFile(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Create File at {0}", path);
        std::ofstream dst(path, std::ios::binary);
        dst.close();
    }

    void copy(const std::string& source, const std::string& target)
    { 
        Debug::Log->trace("<FileUtils> Copy file from {0} to {1}", source, target);

        //std::experimental::filesystem::copy(source, target); (Doesn't work for now)
        std::ifstream src(source, std::ios::binary);
        std::ofstream dst(target, std::ios::binary);

        dst << src.rdbuf();
    }

    bool deleteFile(const std::string& path)
    {
        if (Debug::Log != nullptr)
            Debug::Log->trace("<FileUtils> Delete File at {0}", path);
        return std::remove(path.c_str()) == 0;
    }

    bool deleteDirectory(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Delete Directory at {0}", path);

        if (directoryExists(path))
            return std::experimental::filesystem::remove(path);
        return false;
    }

    std::string getCurrentDirectory()
    {
        return std::experimental::filesystem::current_path().string();
    }

    std::string separator()
    {
#ifdef _WIN32
        return "\\";
#else
        return "/";
#endif
    }
}
