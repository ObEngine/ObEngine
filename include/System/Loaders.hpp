#pragma once

#include <string>

#include <kaguya/kaguya.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vili/Vili.hpp>

namespace obe
{
    namespace System
    {
        /**
         * \brief Lambdas used to load different kind of resources using the System::Path
         */
        namespace Loaders
        {
            /**
             * \brief Load a sf::Texture from a file
             */
            extern std::function<int(sf::Texture*, std::string)> textureLoader;
            /**
             * \brief Load a vili::DataParser from a file
             */
            extern std::function<int(vili::ViliParser*, std::string)> dataLoader;
            /**
             * \brief Load a sf::Font from a file
             */
            extern std::function<int(sf::Font*, std::string)> fontLoader;
            /**
             * \brief List all folders in the specified path
             */
            extern std::function<int(std::vector<std::string>*, std::string)> dirPathLoader;
            /**
             * \brief List all files in the specified path
             */
            extern std::function<int(std::vector<std::string>*, std::string)> filePathLoader;
            /**
             * \brief Load the Lua source from a file
             */
            extern std::function<int(kaguya::State*, std::string)> luaLoader;
            /**
             * \brief Load a sf::SoundBuffer from a file
             */
            extern std::function<int(sf::SoundBuffer*, std::string)> soundLoader;
            /**
             * \brief Load a sf::Music from a file
             */
            extern std::function<int(sf::Music*, std::string)> musicLoader;
        }
    }
}
