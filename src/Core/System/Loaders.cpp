#include <System/Loaders.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::System::Loaders
{
    std::function<int(sf::Texture*, const std::string&)> textureLoader = 
        [](sf::Texture* obj, const std::string& path) -> int { return obj->loadFromFile(path); };
    std::function<int(vili::ViliParser*, const std::string&)> dataLoader = 
        [](vili::ViliParser* obj, const std::string& path) -> int { return obj->parseFile(path); };
    std::function<int(sf::Font*, const std::string&)> fontLoader = 
        [](sf::Font* obj, const std::string& path) -> int { return obj->loadFromFile(path); };
    std::function<int(std::vector<std::string>*, const std::string&)> dirPathLoader = 
        [](std::vector<std::string>* obj, const std::string& path) -> int
    {
        std::vector<std::string> newPaths = Utils::File::getDirectoryList(path);
        obj->insert(obj->end(), newPaths.begin(), newPaths.end());
        return 0x002;
    };
    std::function<int(std::vector<std::string>*, const std::string&)> filePathLoader = 
        [](std::vector<std::string>* obj, const std::string& path) -> int
    {
        std::vector<std::string> newFiles = Utils::File::getFileList(path);
        obj->insert(obj->end(), newFiles.begin(), newFiles.end());
        return 0x002;
    };
    std::function<int(kaguya::State*, const std::string&)> luaLoader = 
        [](kaguya::State* obj, const std::string& path) -> int { return obj->dofile(path); };
    std::function<int(sf::SoundBuffer*, const std::string&)> soundLoader = 
        [](sf::SoundBuffer* sound, const std::string& path) -> int { return sound->loadFromFile(path); };
    std::function<int(sf::Music*, const std::string&)> musicLoader = 
        [](sf::Music* music, const std::string& path) -> int { return music->openFromFile(path); };
}