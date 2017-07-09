#pragma once

#include <SFML/Audio.hpp>

namespace obe
{
    namespace Sound
    {
        /**
         * \brief A Wrapper around sf::Music
         */
        class MusicWrapper : sf::Music
        {
        public:
            /**
             * \brief Default constructor of MusicWrapper
             */
            MusicWrapper();
            /**
             * \brief Load Constructor of MusicWrapper
             * \param filename Path to the music file to load
             */
            explicit MusicWrapper(const std::string& filename);

            /**
             * \brief Loads a Music at the given path
             * \param filename Path to the Music to load
             */
            void load(const std::string& filename);
        };
    }
}
