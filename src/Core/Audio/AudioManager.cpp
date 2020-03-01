#include <Audio/AudioManager.hpp>
#include <Audio/Sound.hpp>
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
}