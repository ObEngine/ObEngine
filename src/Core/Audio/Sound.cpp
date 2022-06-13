#include <Audio/Sound.hpp>

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>
#include <soloud/soloud_wavstream.h>

namespace obe::audio
{
    void Sound::apply_changes()
    {
        this->set_pitch(m_pitch);
        this->set_volume(m_volume);
        this->set_looping(m_looping);
    }

    Sound::Sound(SoLoud::Soloud& manager, std::shared_ptr<SoLoud::AudioSource> source)
        : m_manager(manager), m_source(std::move(source)),
          m_handle(m_manager.play(*m_source, m_source->mVolume, 0, true)),
          m_base_samplerate(m_source->mBaseSamplerate)
    {
    }
    double Sound::get_duration() const
    {
        if (const auto source = dynamic_cast<SoLoud::WavStream*>(m_source.get()); source)
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
            this->apply_changes();
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
    void Sound::set_pitch(float pitch)
    {
        m_pitch = pitch;
        m_manager.setSamplerate(m_handle, m_base_samplerate * m_pitch);
    }
    float Sound::get_pitch() const
    {
        return m_pitch;
    }

    void Sound::set_speed(float speed) const
    {
        m_manager.setRelativePlaySpeed(m_handle, speed);
    }

    float Sound::get_speed() const
    {
        return m_manager.getRelativePlaySpeed(m_handle);
    }

    SoundStatus Sound::get_status() const
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
    void Sound::set_offset(double offset) const
    {
        m_manager.seek(m_handle, offset);
    }
    float Sound::get_volume() const
    {
        return m_manager.getVolume(m_handle);
    }
    void Sound::set_volume(float volume)
    {
        m_volume = volume;
        m_manager.setVolume(m_handle, volume);
    }
    void Sound::set_looping(bool looping)
    {
        m_looping = looping;
        m_manager.setLooping(m_handle, looping);
    }
    bool Sound::is_looping() const
    {
        return m_manager.getLooping(m_handle);
    }
    double Sound::get_offset() const
    {
        return m_manager.getStreamPosition(m_handle);
    }
}
