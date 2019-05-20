#pragma once

#include <map>
#include <string>

#include <SFML/Audio/Sound.hpp>

namespace obe::Sound
{
    /**
    * \brief A wrapper around sf::Sound
    * @Bind
    */
    class SoundWrapper
    {
    private:
        static std::map<std::string, sf::SoundBuffer> SoundBank;
        sf::Sound m_sound;
    public:
        /**
        * \brief Default constructor of SoundWrapper
        */
        SoundWrapper() = default;
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

        bool isLooping() const;
        void setLooping(bool looping);

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