#include <Audio/AudioManager.hpp>
#include <Debug/Logger.hpp>
#include <System/Path.hpp>

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>
#include <soloud/soloud_wavstream.h>

namespace obe::Audio
{
    AudioManager::AudioManager()
        : Registrable("Audio")
    {
        m_engine.init();
    }
    AudioManager::~AudioManager()
    {
        m_engine.deinit();
    }
    void AudioManager::cache(const std::string& path)
    {
        if (m_cache.find(path) == m_cache.end())
        {
            std::string filePath = System::Path(path).find(System::PathType::File);
            std::shared_ptr<SoLoud::Wav> sample = std::make_shared<SoLoud::Wav>();
            sample->load(filePath.c_str());
            m_cache[filePath] = sample;
        }
    }
    Sound AudioManager::load(const std::string& path, bool stream)
    {
        std::string filePath = System::Path(path).find(System::PathType::File);
        std::shared_ptr<SoLoud::AudioSource> sample;
        if (m_cache.find(filePath) != m_cache.end())
        {
            sample = m_cache[filePath];
        }
        else
        {
            if (stream)
            {
                sample = std::make_shared<SoLoud::WavStream>();
                static_cast<SoLoud::WavStream*>(sample.get())->load(filePath.c_str());
            }
            else
            {
                sample = std::make_shared<SoLoud::Wav>();
                static_cast<SoLoud::Wav*>(sample.get())->load(filePath.c_str());
            }
        }
        return Sound(m_engine, std::move(sample));
    }

    Sound::Sound(SoLoud::Soloud& manager, std::shared_ptr<SoLoud::AudioSource> source)
        : m_manager(manager)
    {
        m_source = std::move(source);
        m_baseSamplerate = m_source->mBaseSamplerate;
    }
    double Sound::getDuration() const
    {
        if (dynamic_cast<SoLoud::WavStream*>(m_source.get()))
        {
            return static_cast<SoLoud::WavStream*>(m_source.get())->getLength();
        }
        else
        {
            return static_cast<SoLoud::Wav*>(m_source.get())->getLength();
        }
    }
    void Sound::play()
    {
        if (m_handle && m_manager.isValidVoiceHandle(*m_handle))
        {
            m_manager.setPause(*m_handle, false);
        }
        else
        {
            m_handle
                = std::make_optional(m_manager.play(*m_source.get(), m_source->mVolume));
            this->setPitch(m_pitch);
        }
    }
    void Sound::pause()
    {
        if (m_handle)
            m_manager.setPause(*m_handle, true);
    }
    void Sound::stop()
    {
        if (m_handle)
            m_manager.stop(*m_handle);
    }
    void Sound::setPitch(float pitch)
    {
        if (m_handle)
        {
            m_pitch = pitch;
            m_manager.setSamplerate(*m_handle, float(m_baseSamplerate) * m_pitch);
        }
    }
    float Sound::getPitch() const
    {
        return m_pitch;
    }
}