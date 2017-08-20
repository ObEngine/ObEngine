#include <Graphics/ResourceManager.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <Triggers/TriggerDatabase.hpp>

namespace obe
{
    namespace Graphics
    {
        ResourceManager* ResourceManager::m_instance = nullptr;

        ResourceManager::ResourceManager() : m_resourceManagerTriggers(Triggers::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "ResourceManager"))
        {
            m_resourceManagerTriggers->addTrigger("TextureLoaded");
        }

        ResourceManager* ResourceManager::GetInstance()
        {
            if (m_instance == nullptr)
                m_instance = new ResourceManager();
            return m_instance;
        }

        sf::Texture* ResourceManager::getTexture(const std::string& path, bool antiAliasing)
        {
            if (m_textureDatabase.size() != 0)
            {
                if (m_textureDatabase.find(path) == m_textureDatabase.end())
                {
                    std::unique_ptr<sf::Texture> tempTexture = std::make_unique<sf::Texture>();
                    System::Path(path).loadResource(tempTexture.get(), System::Loaders::textureLoader);
                    
                    if (tempTexture != nullptr)
                    {
                        tempTexture->setSmooth(antiAliasing);
                        m_textureDatabase[path] = move(tempTexture);
                        m_resourceManagerTriggers->pushParameter("TextureLoaded", "texture", m_textureDatabase[path].get());
                        m_resourceManagerTriggers->trigger("TextureLoaded");
                        return m_textureDatabase[path].get();
                    }
                    throw aube::ErrorHandler::Raise("ObEngine.Animation.RessourceManager.LoadTexture", {{"file", path}});
                }
                return m_textureDatabase[path].get();
            }
            std::unique_ptr<sf::Texture> tempTexture = std::make_unique<sf::Texture>();
            System::Path(path).loadResource(tempTexture.get(), System::Loaders::textureLoader);
            if (tempTexture != nullptr)
            {
                tempTexture->setSmooth(antiAliasing);
                m_textureDatabase[path] = move(tempTexture);
                m_resourceManagerTriggers->pushParameter("TextureLoaded", "texture", m_textureDatabase[path].get());
                m_resourceManagerTriggers->trigger("TextureLoaded");
                return m_textureDatabase[path].get();
            }
            throw aube::ErrorHandler::Raise("ObEngine.Animation.RessourceManager.LoadTexture", {{"file", path}});
        }
    }
}
