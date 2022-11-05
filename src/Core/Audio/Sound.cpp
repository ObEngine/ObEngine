#include <Audio/Sound.hpp>

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>
#include <soloud/soloud_wavstream.h>

namespace obe::audio
{
    Sound::Sound(SoLoud::Soloud& manager, std::shared_ptr<SoLoud::AudioSource> source)
        : m_manager(manager)
        , m_source(std::move(source))
        , m_base_handle(*this)
        , m_base_samplerate(m_source->mBaseSamplerate)
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
        m_base_handle.play();
    }
    void Sound::pause() const
    {
        m_base_handle.pause();
    }
    void Sound::stop() const
    {
        m_base_handle.stop();
    }

    SoundHandle Sound::make_handle() const
    {
        return SoundHandle(*this);
    }

    void Sound::set_pitch(float pitch)
    {
        m_base_handle.set_pitch(pitch);
    }
    float Sound::get_pitch() const
    {
        return m_base_handle.get_pitch();
    }

    void Sound::set_speed(float speed)
    {
        m_base_handle.set_speed(speed);
    }

    float Sound::get_speed() const
    {
        return m_base_handle.get_speed();
    }

    SoundStatus Sound::get_status() const
    {
        return m_base_handle.get_status();
    }
    void Sound::set_offset(double offset) const
    {
        m_base_handle.set_offset(offset);
    }
    float Sound::get_volume() const
    {
        return m_base_handle.get_volume();
    }
    void Sound::set_volume(float volume)
    {
        m_base_handle.set_volume(volume);
    }
    void Sound::set_looping(bool looping)
    {
        m_base_handle.set_looping(looping);
    }
    bool Sound::is_looping() const
    {
        return m_base_handle.is_looping();
    }

    double Sound::get_offset() const
    {
        return m_base_handle.get_offset();
    }

    void SoundHandle::apply_changes()
    {
        this->set_pitch(m_pitch);
        this->set_speed(m_speed);
        this->set_volume(m_volume);
        this->set_looping(m_looping);
    }

    SoundHandle::SoundHandle(const Sound& sound)
        : m_sound(sound)
        , m_handle(sound.m_manager.play(*sound.m_source, sound.m_source->mVolume, 0, true))
    {
    }

    const Sound& SoundHandle::get_sound() const
    {
        return m_sound;
    }

    void SoundHandle::play()
    {
        if (m_sound.m_manager.isValidVoiceHandle(m_handle))
        {
            m_sound.m_manager.setPause(m_handle, false);
        }
        else
        {
            m_handle = m_sound.m_manager.play(*m_sound.m_source, m_sound.m_source->mVolume, 0, true);
            this->apply_changes();
            m_sound.m_manager.setPause(m_handle, false);
        }
    }

    void SoundHandle::pause() const
    {
        m_sound.m_manager.setPause(m_handle, true);
    }

    void SoundHandle::stop() const
    {
        m_sound.m_manager.stop(m_handle);
    }

    void SoundHandle::set_pitch(float pitch)
    {
        m_pitch = pitch;
        m_sound.m_manager.setSamplerate(m_handle, m_sound.m_base_samplerate * m_pitch);
    }

    float SoundHandle::get_pitch() const
    {
        return m_pitch;
    }

    void SoundHandle::set_speed(float speed)
    {
        m_speed = speed;
        m_sound.m_manager.setRelativePlaySpeed(m_handle, speed);
    }

    float SoundHandle::get_speed() const
    {
        return m_sound.m_manager.getRelativePlaySpeed(m_handle);
    }

    SoundStatus SoundHandle::get_status() const
    {
        if (!m_sound.m_manager.isValidVoiceHandle(m_handle))
        {
            return SoundStatus::Stopped;
        }
        else if (m_sound.m_manager.getPause(m_handle))
        {
            return SoundStatus::Paused;
        }
        else
        {
            return SoundStatus::Playing;
        }
    }

    double SoundHandle::get_offset() const
    {
        return m_sound.m_manager.getStreamPosition(m_handle);
    }

    void SoundHandle::set_offset(double offset) const
    {
        m_sound.m_manager.seek(m_handle, offset);
    }

    float SoundHandle::get_volume() const
    {
        return m_sound.m_manager.getVolume(m_handle);
    }

    void SoundHandle::set_volume(float volume)
    {
        m_volume = volume;
        m_sound.m_manager.setVolume(m_handle, volume);
    }

    void SoundHandle::set_looping(bool looping)
    {
        m_looping = looping;
        m_sound.m_manager.setLooping(m_handle, looping);
    }

    bool SoundHandle::is_looping() const
    {
        return m_looping;
    }
}
