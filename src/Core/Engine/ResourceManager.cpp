#include <Engine/Exceptions.hpp>
#include <Engine/ResourceManager.hpp>
#include <System/Path.hpp>

namespace obe::Engine
{
    const Graphics::Texture& ResourceManager::getTexture(
        const System::Path& path, bool antiAliasing)
    {
        const std::string pathAsString = path.toString();
        if (m_textures.find(pathAsString) == m_textures.end()
            || (!m_textures[pathAsString].first && !antiAliasing)
            || (!m_textures[pathAsString].second && antiAliasing))
        {
            std::shared_ptr<sf::Texture> tempTexture = std::make_shared<sf::Texture>();
            const std::string realPath = path.find();
            Debug::Log->debug(
                "[ResourceManager] Loading <Texture> {} from {}", pathAsString, realPath);

            const bool success = tempTexture->loadFromFile(realPath);
            if (success)
            {
                tempTexture->setSmooth(antiAliasing);
                if (!antiAliasing)
                {
                    m_textures[pathAsString].first
                        = std::make_unique<Graphics::Texture>(tempTexture);
                    return *m_textures[pathAsString].first;
                }
                else
                {
                    m_textures[pathAsString].second
                        = std::make_unique<Graphics::Texture>(tempTexture);
                    return *m_textures[pathAsString].second;
                }
            }
            else
                throw Exceptions::TextureNotFound(
                    pathAsString, System::MountablePath::StringPaths(), EXC_INFO);
        }
        else
        {
            if (antiAliasing)
            {
                return *m_textures[pathAsString].second;
            }
            else
            {
                return *m_textures[pathAsString].first;
            }
        }
    }

    const Graphics::Texture& ResourceManager::getTexture(const System::Path& path)
    {
        return getTexture(path, defaultAntiAliasing);
    }

    void ResourceManager::clean()
    {
        for (auto& texturePair : m_textures)
        {
            if (texturePair.second.first && texturePair.second.first->useCount() == 1)
            {
                texturePair.second.first.reset();
            }
            if (texturePair.second.second && texturePair.second.second->useCount() == 1)
            {
                texturePair.second.second.reset();
            }
        }
    }

    ResourceManager::ResourceManager()
        : defaultAntiAliasing(false)
    {
    }

    std::shared_ptr<Graphics::Font> ResourceManager::getFont(const std::string& path)
    {
        if (m_fonts.find(path) == m_fonts.end())
        {
            const System::FindResult findResult = System::Path(path).find(System::PathType::File);
            std::shared_ptr<Graphics::Font> newFont = std::make_shared<Graphics::Font>();
            newFont->loadFromFile(findResult);

            if (findResult.success())
            {
                Debug::Log->debug(
                    "[ResourceManager] Loading <Font> {} from {}", path, findResult.path());
                m_fonts[path] = move(newFont);
            }
            else
                throw Exceptions::FontNotFound(
                    path, System::MountablePath::StringPaths(), EXC_INFO);
        }
        return m_fonts[path];
    }

    void ResourceManagedObject::removeResourceManager()
    {
        m_resources = nullptr;
    }

    void ResourceManagedObject::attachResourceManager(ResourceManager& resources)
    {
        m_resources = &resources;
    }
} // namespace obe::Graphics
