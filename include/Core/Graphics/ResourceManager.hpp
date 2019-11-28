#pragma once

#include <memory>
#include <unordered_map>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <Triggers/TriggerGroup.hpp>

namespace obe::Graphics
{
    using pairTexture = std::pair<std::unique_ptr<sf::Texture>,
                                 std::unique_ptr<sf::Texture>>;
    /**
     * \brief Singleton Class that manages and caches textures
     * @Bind
     */
    class ResourceManager
    {
    private:
        static std::unordered_map<std::string, std::unique_ptr<sf::Font>>
            m_fontDatabase;
        static Triggers::TriggerGroupPtr m_resourceManagerTriggers;
        static std::unordered_map<std::string, pairTexture>
            m_textureDatabase;

    public:
        static sf::Texture NullTexture;
        static void Init();
        static sf::Font* GetFont(const std::string& path);
        /**
         * \brief Get the texture at the given path.\n
         *        If it's already in cache it returns the cached version.\n
         *        Otherwise it loads the texture and caches it.
         * \param path Relative of absolute path to the texture, it uses the
         * obe::System::Path loading system \param antiAliasing Uses
         * Anti-Aliasing for the texture when first loading it \return A pointer
         * to the texture stored in the cache
         */
        static sf::Texture* GetTexture(const std::string& path,
                                       bool antiAliasing = true);
    };
} // namespace obe::Graphics

