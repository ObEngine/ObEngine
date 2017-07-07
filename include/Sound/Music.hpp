#pragma once

#include <SFML/Audio.hpp>

namespace obe
{
    namespace Sound
    {
        class MusicWrapper
        {
        private:
            sf::Music m_music;
        public:
            MusicWrapper();
            explicit MusicWrapper(const std::string& filename);

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
