#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>
#include <soloud/soloud_wavstream.h>

#include <Audio/AudioManager.hpp>
#include <Audio/Exceptions.hpp>
#include <Audio/Sound.hpp>
#include <Debug/Logger.hpp>
#include <System/Path.hpp>

namespace obe::audio
{
    AudioManager::AudioManager()
    {
        debug::Log->debug("<AudioManager> Initializing AudioManager");
        m_engine = std::make_unique<SoLoud::Soloud>();
        m_engine->init();
    }
    AudioManager::~AudioManager()
    {
        debug::Log->debug("<AudioManager> Cleaning AudioManager");
        m_engine->deinit();
    }

    Sound AudioManager::load(const System::Path& path, LoadPolicy load_policy)
    {
        const std::string file_path = path.find(System::PathType::File);
        debug::Log->debug("<AudioManager> Loading audio at '{}'", file_path);
        if (file_path.empty())
        {
            throw exceptions::AudioFileNotFound(
                path.toString(), System::MountablePath::StringPaths(), EXC_INFO);
        }

        if (load_policy == LoadPolicy::Cache && !m_cache.contains(file_path))
        {
            const std::shared_ptr<SoLoud::Wav> sample = std::make_shared<SoLoud::Wav>();
            sample->load(file_path.c_str());
            m_cache[file_path] = sample;
        }
        std::shared_ptr<SoLoud::AudioSource> sample;
        if (m_cache.contains(file_path))
        {
            sample = m_cache[file_path];
        }
        else
        {
            if (load_policy == LoadPolicy::Stream)
            {
                sample = std::make_shared<SoLoud::WavStream>();
                dynamic_cast<SoLoud::WavStream*>(sample.get())->load(file_path.c_str());
            }
            else
            {
                sample = std::make_shared<SoLoud::Wav>();
                dynamic_cast<SoLoud::Wav*>(sample.get())->load(file_path.c_str());
            }
        }
        return Sound(*m_engine, std::move(sample));
    }
}
