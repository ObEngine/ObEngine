#pragma once

#include <experimental/filesystem>
#include <iostream>
#include <fstream>

#include <unzipper.hpp>

namespace elz
{
    void extractZip(std::string zipname, std::string target = ".");
    void extractFile(std::string zipname, std::string filename, std::string target = ".");
}
