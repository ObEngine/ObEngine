#pragma once

#include <unordered_map>

#include <Types/Registrable.hpp>
#include <Types/Singleton.hpp>

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

namespace obe::Audio
{
    class Sound;

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