#include <System/Loaders.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::System
{
    // LoaderResult Implementation
    LoaderResult::LoaderResult()
    {
        m_success = false;
    }

    LoaderResult::LoaderResult(const std::string& path)
    {
        m_success = true;
        m_path = path;
    }

    std::string LoaderResult::path() const
    {
        return m_path;
    }

    bool LoaderResult::success() const
    {
        return m_success;
    }

    LoaderResult::operator bool() const
    {
        return this->success();
    }

    // LoaderMultipleResult Implementation
    LoaderMultipleResult::LoaderMultipleResult()
    {
        m_loadCount = 0;
    }
    LoaderMultipleResult::LoaderMultipleResult(const std::vector<std::string>& paths)
    {
        m_loadCount = paths.size();
        m_paths = paths;
    }
    std::vector<std::string> LoaderMultipleResult::paths() const
    {
        return m_paths;
    }
    unsigned int LoaderMultipleResult::loadCount() const
    {
        return m_loadCount;
    }
    bool LoaderMultipleResult::success() const
    {
        return m_loadCount > 0;
    }
    LoaderMultipleResult::operator bool() const
    {
        return this->success();
    }
} // namespace obe::System

namespace obe::System::Loaders
{
    // Loaders
    Loader<sf::Texture> textureLoader(
        [](sf::Texture& obj, const std::string& path) -> bool { return obj.loadFromFile(path); });

    Loader<vili::ViliParser> dataLoader(
        [](vili::ViliParser& obj, const std::string& path) -> bool { return obj.parseFile(path); });

    Loader<sf::Font> fontLoader(
        [](sf::Font& obj, const std::string& path) -> bool { return obj.loadFromFile(path); });

    Loader<std::vector<std::string>> dirPathLoader(
        [](std::vector<std::string>& obj, const std::string& path) -> bool {
            if (Utils::File::directoryExists(path))
            {
                std::vector<std::string> newPaths = Utils::File::getDirectoryList(path);
                obj.insert(obj.end(), newPaths.begin(), newPaths.end());
                return true;
            }
            else
            {
                return false;
            }
        });

    Loader<std::vector<std::string>> filePathLoader(
        [](std::vector<std::string>& obj, const std::string& path) -> bool {
            if (Utils::File::directoryExists(path))
            {
                std::vector<std::string> newFiles = Utils::File::getFileList(path);
                obj.insert(obj.end(), newFiles.begin(), newFiles.end());
                return true;
            }
            else
            {
                return false;
            }
        });

    Loader<kaguya::State> luaLoader(
        [](kaguya::State& obj, const std::string& path) -> bool { return obj.dofile(path); });
} // namespace obe::System::Loaders