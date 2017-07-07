#pragma once

#include <map>

#include <SFML/Audio.hpp>

namespace obe
{
    namespace Sound
    {
        class SoundWrapper
        {
        private:
            static std::map<std::string, sf::SoundBuffer> SoundBank;
            sf::Sound m_sound;
        public:
            SoundWrapper();
            explicit SoundWrapper(const std::string& filename);

            void load(const std::string& filename);

            bool isLooping() const;
            void setLooping(const bool& looping);

            sf::Time getPlayingOffset() const;
            void setPlayingOffset(const sf::Time& offset);

            float getPitch() const;
            void setPitch(float pitch);

            float getVolume() const;
            void setVolume(float volume);

            void setPosition(float x, float y, float z);
            sf::Vector3f getPosition() const;

            void useSoundPosition(bool usePosition);
            bool doesUsesSoundPosition() const;

            void setSpatialAttenuation(float attenuation);
            float getSpatialAttenuation() const;

            void setMinimumDistance(float distance);
            float getMinimumDistance() const;

            std::string getStatus() const;
            void pause();
            void play();
            void stop();
        };
    }
}
