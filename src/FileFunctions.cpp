#include "FileFunctions.hpp"

namespace obe
{
	namespace Functions
	{
		namespace File
		{
			std::vector<std::string> File::listDirInDir(const std::string& path)
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

			std::vector<std::string> File::listFileInDir(const std::string& path)
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

			bool File::fileExists(const std::string& path)
			{
				struct stat buffer;
				bool fileFound = (stat(path.c_str(), &buffer) == 0);
				return fileFound;
			}

			void File::copy(const std::string& source, const std::string& target)
			{
				std::ifstream src(source, std::ios::binary);
				std::ofstream dst(target, std::ios::binary);

				dst << src.rdbuf();
			}

			std::string File::separator()
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