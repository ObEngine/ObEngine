#include <Sound/Music.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

namespace obe::Sound
{
    MusicWrapper::MusicWrapper(const std::string& filename)
    {
        this->load(filename);
    }

    void MusicWrapper::load(const std::string& filename)
    {
        System::Path(filename).load(System::Loaders::musicLoader, m_music);
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

    std::string MusicWrapper::getStatus() const
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
}