#pragma once

#include <memory>
#include <unordered_map>

#include <SFML/Graphics/Font.hpp>

#include <Graphics/Font.hpp>
#include <Graphics/Texture.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe::Engine
{
    template <class T> using ResourceStore = std::unordered_map<std::string, T>;
    using TexturePair = std::pair<std::unique_ptr<Graphics::Texture>,
        std::unique_ptr<Graphics::Texture>>;
    /**
     * \brief Class that manages and caches textures}
     */
    class ResourceManager
    {
    private:
        Triggers::TriggerGroupPtr t_resources;
        ResourceStore<std::shared_ptr<Graphics::Font>> m_fonts;
        ResourceStore<TexturePair> m_textures;

    public:
        bool defaultAntiAliasing;
        ResourceManager();
        std::shared_ptr<Graphics::Font> getFont(const std::string& path);
        /**
         * \brief Get the texture at the given path.
         *        If it's already in cache it returns the cached version.
         *        Otherwise it loads the texture and caches it.
         * \param path Relative of absolute path to the texture,
         *        it uses the obe::System::Path loading system
         * \param antiAliasing Uses Anti-Aliasing for the texture when first loading it
         * \return A pointer to the texture stored in the cache
         */
        const Graphics::Texture& getTexture(const std::string& path, bool antiAliasing);
        const Graphics::Texture& getTexture(const std::string& path);

        void clean();
    };

    class ResourceManagedObject
    {
    protected:
        ResourceManager* m_resources = nullptr;

    public:
        virtual ~ResourceManagedObject() = default;
        virtual void removeResourceManager();
        virtual void attachResourceManager(ResourceManager& resources);
    };
} // namespace obe::Graphics
