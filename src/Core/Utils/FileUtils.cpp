#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>

#ifdef _USE_FILESYSTEM_FALLBACK
#include <cstdio>
#include <tinydir/tinydir.h>
#if _MSC_VER
#include <direct.h>
#include <io.h>
#include <winbase.h>
#define FsAccess _access
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define FsAccess access
#define GetCurrentDir getcwd
#endif
#else
#include <fswrapper/fswrapper.hpp>
#endif

#include <Debug/Logger.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::Utils::File
{
    std::vector<std::string> getDirectoryList(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Get Directory List at {0}", path);
        std::vector<std::string> folderList;
#ifdef _USE_FILESYSTEM_FALLBACK
        tinydir_dir dir;
        tinydir_open(&dir, path.c_str());

        while (dir.has_next)
        {
            tinydir_file file;
            tinydir_readfile(&dir, &file);
            if (file.is_dir && std::string(file.name) != "."
                && std::string(file.name) != "..")
            {
                folderList.push_back(std::string(file.name));
            }
            tinydir_next(&dir);
        }
        tinydir_close(&dir);
#else
        for (auto& p : std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_directory(p))
            {
                folderList.push_back(std::filesystem::path(p.path()).filename().string());
            }
        }
#endif
        return folderList;
    }

    std::vector<std::string> getFileList(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Get File List at {0}", path);

        std::vector<std::string> fileList;
#ifdef _USE_FILESYSTEM_FALLBACK
        tinydir_dir dir;
        tinydir_open(&dir, path.c_str());

        while (dir.has_next)
        {
            tinydir_file file;
            tinydir_readfile(&dir, &file);
            if (!file.is_dir)
            {
                fileList.push_back(std::string(file.name));
            }
            tinydir_next(&dir);
        }
        tinydir_close(&dir);
#else
        for (auto& p : std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_regular_file(p))
            {
                fileList.push_back(std::filesystem::path(p.path()).filename().string());
            }
        }
#endif
        return fileList;
    }

    bool fileExists(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Test File existence at {0}", path);

#ifdef _USE_FILESYSTEM_FALLBACK
        struct stat buffer;
        bool fileFound = (stat(path.c_str(), &buffer) == 0);
        return fileFound;
#else
        return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
#endif
    }

    bool directoryExists(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Get Directory existence at {0}", path);

#ifdef _USE_FILESYSTEM_FALLBACK
        if (FsAccess(path.c_str(), 0) == 0)
        {
            struct stat status;
            stat(path.c_str(), &status);
            return (status.st_mode & S_IFDIR) != 0;
        }
        return false;
#else
        return std::filesystem::exists(path) && std::filesystem::is_directory(path);
#endif
    }

    bool createDirectory(const std::string& path)
    {
        Debug::Log->trace("<FileUtils> Create Directory at {0}", path);

#ifdef _USE_FILESYSTEM_FALLBACK
#ifdef _WIN32
        return bool(CreateDirectory(path.c_str(), LPSECURITY_ATTRIBUTES(NULL)));
#else
        return bool(mkdir(path.c_str(),
            S_IRUSR | S_IWUSR | S_IXUSR)); //   grant owner access only
#endif
#else
        return std::filesystem::create_directory(path);
#endif
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

        // std::filesystem::copy(source, target); (Doesn't work for now)
        const std::ifstream src(source, std::ios::binary);
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

#ifdef _USE_FILESYSTEM_FALLBACK
        Debug::Log->error("<FileUtils> Unimplemented deleteDirectory for "
                          "filesystem fallback");
#else
        if (directoryExists(path))
            return std::filesystem::remove(path);
#endif
        return false;
    }

    std::string getCurrentDirectory()
    {
#ifdef _USE_FILESYSTEM_FALLBACK
        char buff[FILENAME_MAX];
        GetCurrentDir(buff, FILENAME_MAX);
        std::string current_working_dir(buff);
        return current_working_dir;
#else
        return std::filesystem::current_path().string();
#endif
    }

    std::string separator()
    {
#ifdef _WIN32
        return "\\";
#else
        return "/";
#endif
    }
} // namespace obe::Utils::File