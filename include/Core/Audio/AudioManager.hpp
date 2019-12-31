#pragma once

#include <optional>

#include <Types/Registrable.hpp>
#include <Types/Singleton.hpp>

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

namespace obe::Audio
{
    class AudioManager;

    class Sound
    {
    private:
        SoLoud::Soloud& m_manager;
        std::shared_ptr<SoLoud::AudioSource> m_source;
        std::optional<SoLoud::handle> m_handle;

    public:
        Sound(SoLoud::Soloud& manager, std::shared_ptr<SoLoud::AudioSource> source);
        void play();
        void pause();
        void stop();
    };
    class AudioManager : public Types::Registrable<AudioManager>,
                         public Types::Singleton<AudioManager>
    {
    private:
        SoLoud::Soloud m_engine;
        std::unordered_map<std::string, std::shared_ptr<SoLoud::Wav>> m_cache;

    public:
        AudioManager();
        ~AudioManager();
        void cache(const std::string& path);
        Sound load(const std::string& path, bool stream = false);
    };
}