#include "elzip.hpp"

namespace fs = std::experimental::filesystem;

namespace elz
{
    void extractZip(std::string zipname, std::string target)
    {
        ziputils::unzipper zipFile;
        zipFile.open(zipname.c_str());
        for (std::string filename : zipFile.getFilenames())
        {
            fs::path cDir(target + ((fs::path(filename).parent_path().string() == "") ? "" : "/") + fs::path(filename).parent_path().string());
            fs::path cFile(target + "/" + filename);
            std::cout << "Path : " << cDir.string() << std::endl;
            std::cout << "Exist : " << fs::exists(cDir) << std::endl;
            std::cout << "ExistF : " << fs::exists(cFile) << std::endl;
            std::cout << "IsDir : " << fs::is_directory(cDir) << std::endl;
            fs::path fillPath;
            for (fs::path pathPart : cDir) {
                fillPath /= pathPart;
                if (!fs::exists(fillPath)) {
                    std::cout << "Creating directory : " << cDir.string() << std::endl;
                    fs::create_directory(fillPath);
                }
            }
            std::cout << "Creating file : " << cFile.string() << std::endl;
            zipFile.openEntry(filename.c_str());
            std::ofstream wFile;
            wFile.open(cFile.string(), std::ios_base::binary | std::ios_base::out);
			std::string dumped = zipFile.dump();
			wFile.write(dumped.c_str(), dumped.size());
            wFile.close();
        }
    }
}