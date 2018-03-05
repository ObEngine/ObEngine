#pragma once

#include <SFML/Audio/Music.hpp>

namespace obe::Sound
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
        MusicWrapper() = default;
        /**
        * \brief Load Constructor of MusicWrapper
        * \param filename Path to the music file to load
        */
        explicit MusicWrapper(const std::string& filename);
        bool doesUsesSoundPosition() const;
        sf::Time getDuration() const;
        float getMinimumDistance() const;
        float getPitch() const;
        sf::Time getPlayingOffset() const;
        sf::Vector3f getPosition() const;
        float getSpatialAttenuation() const;
        std::string getStatus() const;
        float getVolume() const;
        bool isLooping() const;
        /**
        * \brief Loads a Music at the given path
        * \param filename Path to the Music to load
        */
        void load(const std::string& filename);
        void pause();
        void play();
        void setLooping(const bool& looping);
        void setMinimumDistance(float distance);
        void setPitch(float pitch);
        void setPlayingOffset(const sf::Time& offset);
        void setPosition(float x, float y, float z);
        void setSpatialAttenuation(float attenuation);
        void setVolume(float volume);
        void stop();
        void useSoundPosition(bool usePosition);
    };
}