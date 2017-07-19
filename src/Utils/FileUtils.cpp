#include <Utils/FileUtils.hpp>

namespace obe
{
    namespace Utils
    {
        namespace File
        {
            std::vector<std::string> getDirectoryList(const std::string& path)
            {
                tinydir_dir dir;
                tinydir_open(&dir, path.c_str());

                std::vector<std::string> fileList;
                while (dir.has_next)
                {
                    tinydir_file file;
                    tinydir_readfile(&dir, &file);
                    if (file.is_dir)
                    {
                        if (std::string(file.name) != "." && std::string(file.name) != "..") { fileList.push_back(std::string(file.name)); }
                    }
                    tinydir_next(&dir);
                }
                tinydir_close(&dir);
                return fileList;
            }

            std::vector<std::string> getFileList(const std::string& path)
            {
                tinydir_dir dir;
                tinydir_open(&dir, path.c_str());

                std::vector<std::string> fileList;
                while (dir.has_next)
                {
                    tinydir_file file;
                    tinydir_readfile(&dir, &file);
                    if (!file.is_dir) { fileList.push_back(std::string(file.name)); }
                    tinydir_next(&dir);
                }
                tinydir_close(&dir);
                return fileList;
            }

            bool fileExists(const std::string& path)
            {
                struct stat buffer;
                bool fileFound = (stat(path.c_str(), &buffer) == 0);
                return fileFound;
            }

            bool directoryExists(const std::string& path)
            {
#ifdef _USE_CPP_NEW_FS
                return std::experimental::filesystem::exists(path) && std::experimental::filesystem::is_directory(path);
#else
                if (FsAccess(path.c_str(), 0) == 0) 
                {
                    struct stat status;
                    stat(path.c_str(), &status);
                    return (status.st_mode & S_IFDIR) != 0;
                }
                return false;
#endif
            }

            bool createDirectory(const std::string& path)
            {
#ifdef _USE_CPP_NEW_FS
                return std::experimental::filesystem::create_directory(path);
#else
#ifdef _WIN32
                return bool(CreateDirectory(path.c_str(), LPSECURITY_ATTRIBUTES(NULL)));
#else
                return bool(mkdir(path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR));    //   grant owner access only
#endif
#endif
            }

            void createFile(const std::string& path)
            {
                std::ofstream dst(path, std::ios::binary);
                dst.close();
            }

            void copy(const std::string& source, const std::string& target)
            {
#ifdef _USE_CPP_NEW_FS
                //std::experimental::filesystem::copy(source, target); (Doesn't work for now)
                std::ifstream src(source, std::ios::binary);
                std::ofstream dst(target, std::ios::binary);

                dst << src.rdbuf();
#else
                //Can Only Copy File (Fix it for fallback)
                std::ifstream src(source, std::ios::binary);
                std::ofstream dst(target, std::ios::binary);

                dst << src.rdbuf();
#endif
            }

            bool deleteFile(const std::string& path)
            {
                return std::remove(path.c_str()) == 0;
            }

            bool deleteDirectory(const std::string& path)
            {
#ifdef _USE_CPP_NEW_FS
                if (directoryExists(path))
                    return std::experimental::filesystem::remove(path);
                return false;
#else
#endif
            }

            std::string getCurrentDirectory()
            {
#ifdef _USE_CPP_NEW_FS
                return std::experimental::filesystem::current_path().string();
#else
                char buff[FILENAME_MAX];
                GetCurrentDir(buff, FILENAME_MAX);
                std::string current_working_dir(buff);
                return current_working_dir;
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
        }
    }
}
