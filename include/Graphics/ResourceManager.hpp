#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>

namespace obe
{
    namespace Graphics
    {
        /**
         * \brief Singleton Class that manages and caches textures
         */
        class ResourceManager
        {
        private:
            std::map<std::string, std::unique_ptr<sf::Texture>> m_textureDatabase;
            static ResourceManager* m_instance;
        public:
            /**
             * \brief Access the Instance of the ResourceManager
             * \return A pointer to the Instance of the ResourceManager
             */
            static ResourceManager* GetInstance();
            /**
             * \brief Get the texture at the given path.\n 
             *        If it's already in cache it returns the cached version.\n
             *        Otherwise it loads the texture and caches it.
             * \param path Relative of absolute path to the texture, it uses the obe::System::Path loading system
             * \return A pointer to the texture stored in the cache
             */
            sf::Texture* getTexture(const std::string& path);
        };
    }
}
