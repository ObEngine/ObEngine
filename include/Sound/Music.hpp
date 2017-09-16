#pragma once

#include <SFML/Audio.hpp>

namespace obe
{
    namespace Sound
    {
        /**
         * \brief A Wrapper around sf::Music
         * @Bind
         */
        class MusicWrapper
        {
        private:
            sf::Music m_music;
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

            float getSpatialAttenuation() const;
            void setSpatialAttenuation(float attenuation);

            sf::Time getDuration() const;

            bool isLooping() const;
            void setLooping(const bool& looping);

            void setMinimumDistance(float distance);
            float getMinimumDistance() const;

            float getPitch() const;
            void setPitch(float pitch);

            sf::Time getPlayingOffset() const;
            void setPlayingOffset(const sf::Time& offset);

            void setPosition(float x, float y, float z);
            sf::Vector3f getPosition() const;

            float getVolume() const;
            void setVolume(float volume);

            void useSoundPosition(bool usePosition);
            bool doesUsesSoundPosition() const;

            std::string getStatus() const;
            void pause();
            void play();
            void stop();
        };
    }
}
