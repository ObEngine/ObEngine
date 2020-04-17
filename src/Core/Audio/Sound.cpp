#include <Audio/Sound.hpp>

#include <soloud/soloud_wav.h>
#include <soloud/soloud_wavstream.h>

namespace obe::Audio
{
    void Sound::applyChanges()
    {
        this->setPitch(m_pitch);
        this->setVolume(m_volume);
        this->setLooping(m_looping);
    }

    Sound::Sound(SoLoud::Soloud& manager, std::shared_ptr<SoLoud::AudioSource> source)
        : m_manager(manager)
    {
        m_source = std::move(source);
        m_baseSamplerate = m_source->mBaseSamplerate;
        m_handle = m_manager.play(*m_source, m_source->mVolume, 0, true);
    }
    double Sound::getDuration() const
    {
        if (auto source = dynamic_cast<SoLoud::WavStream*>(m_source.get()); source)
        {
            return source->getLength();
        }
        else
        {
            return dynamic_cast<SoLoud::Wav*>(m_source.get())->getLength();
        }
    }
    void Sound::play()
    {
        if (m_manager.isValidVoiceHandle(m_handle))
        {
            m_manager.setPause(m_handle, false);
        }
        else
        {
            m_handle = m_manager.play(*m_source, m_source->mVolume, 0);
            this->applyChanges();
        }
    }
    void Sound::pause() const
    {
        m_manager.setPause(m_handle, true);
    }
    void Sound::stop() const
    {
        m_manager.stop(m_handle);
    }
    void Sound::setPitch(float pitch)
    {
        m_pitch = pitch;
        m_manager.setSamplerate(m_handle, float(m_baseSamplerate) * m_pitch);
    }
    float Sound::getPitch() const
    {
        return m_pitch;
    }
    SoundStatus Sound::getStatus() const
    {
        if (!m_manager.isValidVoiceHandle(m_handle))
        {
            return SoundStatus::Stopped;
        }
        else if (m_manager.getPause(m_handle))
        {
            return SoundStatus::Paused;
        }
        else
        {
            return SoundStatus::Playing;
        }
    }
    void Sound::setOffset(double offset) const
    {
        m_manager.seek(m_handle, offset);
    }
    float Sound::getVolume() const
    {
        return m_manager.getVolume(m_handle);
    }
    void Sound::setVolume(float volume)
    {
        m_volume = volume;
        m_manager.setVolume(m_handle, volume);
    }
    void Sound::setLooping(bool looping)
    {
        m_looping = looping;
        m_manager.setLooping(m_handle, looping);
    }
    bool Sound::getLooping() const
    {
        return m_manager.getLooping(m_handle);
    }
    double Sound::getOffset() const
    {
        return m_manager.getStreamPosition(m_handle);
    }
}