#pragma once

#include <memory>
#include <unordered_map>

#include <Event/EventGroup.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/Texture.hpp>

namespace obe
{
    namespace System
    {
        class Path;
    }
}

namespace obe::engine
{
    template <class T>
    using ResourceStore = std::unordered_map<std::string, T>;
    using TexturePair
        = std::pair<std::unique_ptr<graphics::Texture>, std::unique_ptr<graphics::Texture>>;
    /**
     * \brief Class that manages and caches textures}
     */
    class ResourceManager
    {
    private:
        event::EventGroupPtr e_resources;
        ResourceStore<std::shared_ptr<graphics::Font>> m_fonts;
        ResourceStore<TexturePair> m_textures;

    public:
        bool default_anti_aliasing;
        ResourceManager();
        std::shared_ptr<graphics::Font> get_font(const std::string& path);
        /**
         * \brief Get the texture at the given path.
         *        If it's already in cache it returns the cached version.
         *        Otherwise it loads the texture and caches it.
         * \param path Relative of absolute path to the texture,
         *        it uses the obe::System::Path loading system
         * \param anti_aliasing Uses Anti-Aliasing for the texture when first loading it
         * \return A pointer to the texture stored in the cache
         */
        const graphics::Texture& get_texture(const System::Path& path, bool anti_aliasing);
        const graphics::Texture& get_texture(const System::Path& path);

        void clean();
    };

    class ResourceManagedObject
    {
    protected:
        ResourceManager* m_resources = nullptr;

    public:
        virtual ~ResourceManagedObject() = default;
        virtual void remove_resource_manager();
        virtual void attach_resource_manager(ResourceManager& resources);
    };
} // namespace obe::graphics
