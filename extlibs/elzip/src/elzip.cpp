#include <experimental/filesystem>
#include <fstream>
#include <iostream>

#include <elzip.hpp>
#include <unzipper.hpp>

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
            fs::path fillPath;
            for (fs::path pathPart : cDir)
            {
                fillPath /= pathPart;
                if (!exists(fillPath))
                {
                    create_directory(fillPath);
                }
            }
            std::cout << "Opening file : " << filename << std::endl;
            zipFile.openEntry(filename.c_str());
            std::ofstream wFile;
            wFile.open(cFile.string(), std::ios_base::binary | std::ios_base::out);
            std::string dumped = zipFile.dump();
            wFile.write(dumped.c_str(), dumped.size());
            wFile.close();
        }
    }

    void extractFile(std::string zipname, std::string filename, std::string target)
    {
        ziputils::unzipper zipFile;
        zipFile.open(zipname.c_str());
        zipFile.openEntry(filename.c_str());
        std::ofstream wFile;
        wFile.open(target, std::ios_base::binary | std::ios_base::out);
        std::string dumped = zipFile.dump();
        wFile.write(dumped.c_str(), dumped.size());
        wFile.close();
    }
}
