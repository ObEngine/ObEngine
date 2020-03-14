#include <Engine/ResourceManager.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <Triggers/TriggerManager.hpp>

namespace obe::Engine
{
    std::shared_ptr<Graphics::Texture> ResourceManager::getTexture(
        const std::string& path, bool antiAliasing)
    {
        if (m_textures.find(path) == m_textures.end()
            || (!m_textures[path].first && !antiAliasing)
            || (!m_textures[path].second && antiAliasing))
        {
            std::shared_ptr<Graphics::Texture> tempTexture
                = std::make_shared<Graphics::Texture>();
            const System::LoaderResult loadResult = System::Path(path).load(
                System::Loaders::textureLoader, *tempTexture.get());
            Debug::Log->debug("[ResourceManager] Loading <Texture> {} from {}", path,
                loadResult.path());

            if (loadResult.success())
            {
                tempTexture->setAntiAliasing(antiAliasing);
                if (!antiAliasing)
                {
                    m_textures[path].first = move(tempTexture);
                    return m_textures[path].first;
                }
                else
                {
                    m_textures[path].second = move(tempTexture);
                    return m_textures[path].second;
                }
            }
            else
                throw aube::ErrorHandler::Raise(
                    "ObEngine.Animation.ResourceManager.LoadTexture",
                    { { "file", path } });
        }
        else
        {
            if (antiAliasing)
            {
                return m_textures[path].second;
            }
            else
            {
                return m_textures[path].first;
            }
        }
    }

    std::shared_ptr<Graphics::Texture> ResourceManager::getTexture(
        const std::string& path)
    {
        return getTexture(path, defaultAntiAliasing);
    }

    ResourceManager::ResourceManager()
        : defaultAntiAliasing(false)
    {
    }

    std::shared_ptr<Graphics::Font> ResourceManager::getFont(const std::string& path)
    {
        if (m_fonts.find(path) == m_fonts.end())
        {
            std::shared_ptr<Graphics::Font> tempFont = std::make_shared<Graphics::Font>();
            const System::LoaderResult loadResult
                = System::Path(path).load(System::Loaders::fontLoader, *tempFont);
            Debug::Log->debug(
                "[ResourceManager] Loading <Font> {} from {}", path, loadResult.path());

            if (loadResult.success())
                m_fonts[path] = move(tempFont);
            else
                throw aube::ErrorHandler::Raise(
                    "ObEngine.Animation.ResourceManager.LoadFont", { { "file", path } });
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