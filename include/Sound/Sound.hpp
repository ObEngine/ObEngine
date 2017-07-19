#pragma once

#include <map>

#include <SFML/Audio.hpp>

namespace obe
{
    namespace Sound
    {
        /**
         * \brief A wrapper around sf::Sound
         * @Bind
         */
        class SoundWrapper : public sf::Sound
        {
        private:
            static std::map<std::string, sf::SoundBuffer> SoundBank;
        public:
            /**
             * \brief Default constructor of SoundWrapper
             */
            SoundWrapper();
            /**
             * \brief Load constructor of SoundWrapper
             * \param filename Path to the Sound you want to load
             */
            explicit SoundWrapper(const std::string& filename);

            /**
            * \brief Loads a Sound at the given path
            * \param filename Path to the Sound to load
            */
            void load(const std::string& filename);
        };
    }
}
