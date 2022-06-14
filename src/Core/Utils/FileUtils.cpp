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

#include <whereami/whereami.h>

#include <Debug/Logger.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::Utils::File
{
    std::vector<std::string> get_directory_list(const std::string& path)
    {
        debug::Log->trace("<FileUtils> Get Directory List at {0}", path);
        std::vector<std::string> folder_list;
#ifdef _USE_FILESYSTEM_FALLBACK
        tinydir_dir dir;
        tinydir_open(&dir, path.c_str());

        while (dir.has_next)
        {
            tinydir_file file;
            tinydir_readfile(&dir, &file);
            if (file.is_dir && std::string(file.name) != "." && std::string(file.name) != "..")
            {
                folder_list.push_back(normalize_path(std::string(file.name)));
            }
            tinydir_next(&dir);
        }
        tinydir_close(&dir);
#else
        for (auto& p : std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_directory(p))
            {
                const std::string dirpath = std::filesystem::path(p.path()).filename().string();
                folder_list.push_back(normalize_path(dirpath));
            }
        }
#endif
        return folder_list;
    }

    std::vector<std::string> get_file_list(const std::string& path)
    {
        debug::Log->trace("<FileUtils> Get File List at {0}", path);

        std::vector<std::string> file_list;
#ifdef _USE_FILESYSTEM_FALLBACK
        tinydir_dir dir;
        tinydir_open(&dir, path.c_str());

        while (dir.has_next)
        {
            tinydir_file file;
            tinydir_readfile(&dir, &file);
            if (!file.is_dir)
            {
                file_list.push_back(normalize_path(std::string(file.name)));
            }
            tinydir_next(&dir);
        }
        tinydir_close(&dir);
#else
        for (auto& p : std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_regular_file(p))
            {
                std::string filepath = std::filesystem::path(p.path()).filename().string();
                file_list.push_back(normalize_path(filepath));
            }
        }
#endif
        return file_list;
    }

    bool file_exists(const std::string& path)
    {
        debug::Log->trace("<FileUtils> Test File existence at {0}", path);

#ifdef _USE_FILESYSTEM_FALLBACK
        struct stat buffer;
        bool file_found = (stat(path.c_str(), &buffer) == 0);
        return file_found;
#else
        return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
#endif
    }

    bool directory_exists(const std::string& path)
    {
        debug::Log->trace("<FileUtils> Get Directory existence at {0}", path);

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

    bool create_directory(const std::string& path)
    {
        debug::Log->trace("<FileUtils> Create Directory at {0}", path);

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

    void create_file(const std::string& path)
    {
        debug::Log->trace("<FileUtils> Create File at {0}", path);
        std::ofstream dst(path, std::ios::binary);
        dst.close();
    }

    void copy(const std::string& source, const std::string& target)
    {
        debug::Log->trace("<FileUtils> Copy file from {0} to {1}", source, target);

        // std::filesystem::copy(source, target); (Doesn't work for now)
        const std::ifstream src(source, std::ios::binary);
        std::ofstream dst(target, std::ios::binary);

        dst << src.rdbuf();
    }

    bool delete_file(const std::string& path)
    {
        if (debug::Log != nullptr)
            debug::Log->trace("<FileUtils> Delete File at {0}", path);
        return std::remove(path.c_str()) == 0;
    }

    bool delete_directory(const std::string& path)
    {
        debug::Log->trace("<FileUtils> Delete Directory at {0}", path);

#ifdef _USE_FILESYSTEM_FALLBACK
        debug::Log->error("<FileUtils> Unimplemented delete_directory for "
                          "filesystem fallback");
#else
        if (directory_exists(path))
            return std::filesystem::remove(path);
#endif
        return false;
    }

    std::string get_current_directory()
    {
#ifdef _USE_FILESYSTEM_FALLBACK
        char buff[FILENAME_MAX];
        GetCurrentDir(buff, FILENAME_MAX);
        std::string current_working_dir(buff);
        return current_working_dir;
#else
        return normalize_path(std::filesystem::current_path().string());
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
    std::string get_executable_directory()
    {
        std::string executable_path;

        int path_length = wai_getExecutablePath(nullptr, 0, nullptr);
        executable_path.resize(path_length);
        int dirname_length;
        wai_getExecutablePath(executable_path.data(), path_length, &dirname_length);

        return normalize_path(executable_path.substr(0, dirname_length));
    }
    std::string get_executable_path()
    {
        std::string executable_path;

        int path_length = wai_getExecutablePath(nullptr, 0, nullptr);
        executable_path.resize(path_length);
        int dirname_length;
        wai_getExecutablePath(executable_path.data(), path_length, &dirname_length);

        return normalize_path(executable_path);
    }
    std::string normalize_path(const std::string& path)
    {
        std::string normalized_path = path;
        std::ranges::replace(normalized_path, '\\', '/');
        return normalized_path;
    }

    std::string canonical_path(const std::string& path)
    {
        return std::filesystem::canonical(path).string();
    }

    std::string join(const std::vector<std::string> parts)
    {
        if (parts.empty())
        {
            return "";
        }
        std::filesystem::path base = parts.front();
        for (size_t i = 1; i < parts.size(); i++)
        {
            base /= parts[i];
        }
        return normalize_path(base.string());
    }
} // namespace obe::Utils::File
