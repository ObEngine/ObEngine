#include <Graphics/ResourceManager.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <Triggers/TriggerDatabase.hpp>


namespace obe::Graphics
{
    /*std::unordered_map<std::pair<std::string, bool>, std::unique_ptr<sf::Texture>>
        ResourceManager::m_textureDatabase;*/
    std::unordered_map<std::string, pairTexture>
        ResourceManager::m_textureDatabase;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>>
        ResourceManager::m_fontDatabase;
    sf::Texture ResourceManager::NullTexture;

    sf::Texture* ResourceManager::GetTexture(const std::string& path,
                                             bool antiAliasing)
    {
        if (m_textureDatabase.find(path) == m_textureDatabase.end()
            || (!m_textureDatabase[path].first && !antiAliasing)
            || (!m_textureDatabase[path].second && antiAliasing))
        {
            std::unique_ptr<sf::Texture> tempTexture =
                std::make_unique<sf::Texture>();
            System::Path(path).load(System::Loaders::textureLoader,
                                    *tempTexture.get());

            if (tempTexture != nullptr)
            {
                tempTexture->setSmooth(antiAliasing);
                if (!antiAliasing)
                {
                    m_textureDatabase[path].first = move(tempTexture);
                    return m_textureDatabase[path].first.get();
                }
                else
                {
                    m_textureDatabase[path].second = move(tempTexture);
                    return m_textureDatabase[path].second.get();
                }
            }
            else
                throw aube::ErrorHandler::Raise(
                    "ObEngine.Animation.RessourceManager.LoadTexture",
                    {{"file", path}});
        }
        else
        {
            if (antiAliasing)
            {
                return m_textureDatabase[path].second.get();
            }
            else
            {
                return m_textureDatabase[path].first.get();
            }
        }
        
    }

    void ResourceManager::Init()
    {
        sf::Image nullImage;
        nullImage.create(100, 100, sf::Color::Transparent);
        for (unsigned int i = 0; i < nullImage.getSize().x; i++)
        {
            for (unsigned int j = 0; j < nullImage.getSize().y; j++)
            {
                if (i == 0 || j == 0 || i == nullImage.getSize().x - 1 ||
                    j == nullImage.getSize().y - 1 || i == j ||
                    i == ((nullImage.getSize().x - 1) - j))
                    nullImage.setPixel(i, j, sf::Color::Red);
            }
        }
        NullTexture.loadFromImage(nullImage);
    }

    sf::Font* ResourceManager::GetFont(const std::string& path)
    {
        if (m_fontDatabase.find(path) == m_fontDatabase.end())
        {
            std::unique_ptr<sf::Font> tempFont = std::make_unique<sf::Font>();
            System::LoaderResult loadResult = System::Path(path).load(
                System::Loaders::fontLoader, *tempFont.get());
            std::cout << "Font : " << path
                      << " : found at : " << loadResult.path() << std::endl;

            if (tempFont != nullptr)
                m_fontDatabase[path] = move(tempFont);
            else
                throw aube::ErrorHandler::Raise(
                    "ObEngine.Animation.RessourceManager.LoadFont",
                    {{"file", path}});
        }
        return m_fontDatabase[path].get();
    }
} // namespace obe::Graphics