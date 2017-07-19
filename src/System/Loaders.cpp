#include <System/Loaders.hpp>
#include <Utils/FileUtils.hpp>

namespace obe
{
    namespace System
    {
        namespace Loaders
        {
            std::function<int(sf::Texture*, std::string)> textureLoader = [](sf::Texture* obj, std::string path) -> int { return obj->loadFromFile(path); };
            std::function<int(vili::DataParser*, std::string)> dataLoader = [](vili::DataParser* obj, std::string path) -> int { return obj->parseFile(path); };
            std::function<int(sf::Font*, std::string)> fontLoader = [](sf::Font* obj, std::string path) -> int { return obj->loadFromFile(path); };
            std::function<int(std::vector<std::string>*, std::string)> dirPathLoader = [](std::vector<std::string>* obj, std::string path) -> int
            {
                std::vector<std::string> newPaths = Utils::File::getDirectoryList(path);
                obj->insert(obj->end(), newPaths.begin(), newPaths.end());
                return 0x002;
            };
            std::function<int(std::vector<std::string>*, std::string)> filePathLoader = [](std::vector<std::string>* obj, std::string path) -> int
            {
                std::vector<std::string> newFiles = Utils::File::getFileList(path);
                obj->insert(obj->end(), newFiles.begin(), newFiles.end());
                return 0x002;
            };
            std::function<int(kaguya::State*, std::string)> luaLoader = [](kaguya::State* obj, std::string path) -> int { return obj->dofile(path); };
            std::function<int(sf::SoundBuffer*, std::string)> soundLoader = [](sf::SoundBuffer* sound, std::string path) -> int { return sound->loadFromFile(path); };
            std::function<int(sf::Music*, std::string)> musicLoader = [](sf::Music* music, std::string path) -> int { return music->openFromFile(path); };
        }
    }
}
