#include "SoundManager.hpp"

namespace obe
{
    namespace Sound
    {
        MusicWrapper::MusicWrapper()
        {
        }

        MusicWrapper::MusicWrapper(const std::string& filename)
        {
            this->load(filename);
        }

        void MusicWrapper::load(const std::string& filename)
        {
            System::Path(filename).loadResource(&m_music, System::Loaders::musicLoader);
        }

        float MusicWrapper::getSpatialAttenuation() const
        {
            return m_music.getAttenuation();
        }

        void MusicWrapper::setSpatialAttenuation(float attenuation)
        {
            m_music.setAttenuation(attenuation);
        }

        sf::Time MusicWrapper::getDuration() const
        {
            return m_music.getDuration();
        }

        bool MusicWrapper::isLooping() const
        {
            return m_music.getLoop();
        }

        void MusicWrapper::setLooping(const bool& looping)
        {
            m_music.setLoop(looping);
        }

        void MusicWrapper::setMinimumDistance(float distance)
        {
            m_music.setMinDistance(distance);
        }

        float MusicWrapper::getMinimumDistance() const
        {
            return m_music.getMinDistance();
        }

        float MusicWrapper::getPitch() const
        {
            return m_music.getPitch();
        }

        void MusicWrapper::setPitch(float pitch)
        {
            m_music.setPitch(pitch);
        }

        sf::Time MusicWrapper::getPlayingOffset() const
        {
            return m_music.getPlayingOffset();
        }

        void MusicWrapper::setPlayingOffset(const sf::Time& offset)
        {
            m_music.setPlayingOffset(offset);
        }

        void MusicWrapper::setPosition(float x, float y, float z)
        {
            m_music.setPosition(x, y, z);
        }

        sf::Vector3f MusicWrapper::getPosition() const
        {
            return m_music.getPosition();
        }

        float MusicWrapper::getVolume() const
        {
            return m_music.getVolume();
        }

        void MusicWrapper::setVolume(float volume)
        {
            m_music.setVolume(volume);
        }

        void MusicWrapper::useSoundPosition(bool usePosition)
        {
            m_music.setRelativeToListener(usePosition);
        }

        bool MusicWrapper::doesUsesSoundPosition() const
        {
            return m_music.isRelativeToListener();
        }

        const std::string& MusicWrapper::getStatus() const
        {
            switch (m_music.getStatus())
            {
            case sf::SoundSource::Stopped: return "Stopped";
            case sf::SoundSource::Paused: return "Paused";
            case sf::SoundSource::Playing: return "Playing";
            }
            throw aube::ErrorHandler::Raise("ObEngine.Sound.MusicWrapper.IncorrectStatus");
        }

        void MusicWrapper::pause()
        {
            m_music.pause();
        }

        void MusicWrapper::play()
        {
            m_music.play();
        }

        void MusicWrapper::stop()
        {
            m_music.stop();
        }

        std::map<std::string, sf::SoundBuffer> SoundWrapper::SoundBank = std::map<std::string, sf::SoundBuffer>();

        SoundWrapper::SoundWrapper()
        {
        }

        SoundWrapper::SoundWrapper(const std::string& filename)
        {
            this->load(filename);
        }

        void SoundWrapper::load(const std::string& filename)
        {
            if (SoundBank.find(filename) == SoundBank.end())
            {
                sf::SoundBuffer loadSound;
                System::Path(filename).loadResource(&loadSound, System::Loaders::soundLoader);
                SoundBank[filename] = loadSound;
            }
            m_sound.setBuffer(SoundBank[filename]);
        }

        bool SoundWrapper::isLooping() const
        {
            return m_sound.getLoop();
        }

        void SoundWrapper::setLooping(const bool& looping)
        {
            m_sound.setLoop(looping);
        }

        sf::Time SoundWrapper::getPlayingOffset() const
        {
            return m_sound.getPlayingOffset();
        }

        void SoundWrapper::setPlayingOffset(const sf::Time& offset)
        {
            m_sound.setPlayingOffset(offset);
        }

        float SoundWrapper::getPitch() const
        {
            return m_sound.getPitch();
        }

        void SoundWrapper::setPitch(float pitch)
        {
            m_sound.setPitch(pitch);
        }

        float SoundWrapper::getVolume() const
        {
            return m_sound.getVolume();
        }

        void SoundWrapper::setVolume(float volume)
        {
            m_sound.setVolume(volume);
        }

        void SoundWrapper::setPosition(float x, float y, float z)
        {
            m_sound.setPosition(x, y, z);
        }

        sf::Vector3f SoundWrapper::getPosition() const
        {
            return m_sound.getPosition();
        }

        void SoundWrapper::useSoundPosition(bool usePosition)
        {
            m_sound.setRelativeToListener(usePosition);
        }

        bool SoundWrapper::doesUsesSoundPosition() const
        {
            return m_sound.isRelativeToListener();
        }

        void SoundWrapper::setSpatialAttenuation(float attenuation)
        {
            m_sound.setAttenuation(attenuation);
        }

        float SoundWrapper::getSpatialAttenuation() const
        {
            return m_sound.getAttenuation();
        }

        void SoundWrapper::setMinimumDistance(float distance)
        {
            m_sound.setMinDistance(distance);
        }

        float SoundWrapper::getMinimumDistance() const
        {
            return m_sound.getMinDistance();
        }

        const std::string& SoundWrapper::getStatus() const
        {
            switch (m_sound.getStatus())
            {
            case sf::SoundSource::Stopped: return "Stopped";
            case sf::SoundSource::Paused: return "Paused";
            case sf::SoundSource::Playing: return "Playing";
            }
            throw aube::ErrorHandler::Raise("ObEngine.Sound.SoundWrapper.IncorrectStatus");
        }

        void SoundWrapper::pause()
        {
            m_sound.pause();
        }

        void SoundWrapper::play()
        {
            m_sound.play();
        }

        void SoundWrapper::stop()
        {
            m_sound.stop();
        }
    }
}
