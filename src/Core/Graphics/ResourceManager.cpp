#include <Graphics/ResourceManager.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <Triggers/TriggerDatabase.hpp>

namespace obe
{
    namespace Graphics
    {
        std::map<std::string, std::unique_ptr<sf::Texture>> ResourceManager::m_textureDatabase;
        std::map<std::string, std::unique_ptr<sf::Font>> ResourceManager::m_fontDatabase;

        sf::Texture* ResourceManager::GetTexture(const std::string& path, bool antiAliasing)
        {
            if (m_textureDatabase.find(path) == m_textureDatabase.end())
            {
                std::unique_ptr<sf::Texture> tempTexture = std::make_unique<sf::Texture>();
                System::Path(path).loadResource(tempTexture.get(), System::Loaders::textureLoader);
                
                if (tempTexture != nullptr)
                {
                    tempTexture->setSmooth(antiAliasing);
                    m_textureDatabase[path] = move(tempTexture);
                }
                else
                    throw aube::ErrorHandler::Raise("ObEngine.Animation.RessourceManager.LoadTexture", {{"file", path}});
            }
            return m_textureDatabase[path].get();
        }

        sf::Font* ResourceManager::GetFont(const std::string& path)
        {
            if (m_fontDatabase.find(path) == m_fontDatabase.end())
            {
                std::unique_ptr<sf::Font> tempFont = std::make_unique<sf::Font>();
                std::string foundAt = System::Path(path).loadResource(tempFont.get(), System::Loaders::fontLoader);
                std::cout << "Font : " << path << " : found at : " << foundAt << std::endl;
                
                if (tempFont != nullptr)
                    m_fontDatabase[path] = move(tempFont);
                else
                    throw aube::ErrorHandler::Raise("ObEngine.Animation.RessourceManager.LoadTexture", {{"file", path}});
            }
            return m_fontDatabase[path].get();
        }
    }
}
