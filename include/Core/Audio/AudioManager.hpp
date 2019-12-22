#pragma once

#include <soloud/soloud.h>

namespace obe::Audio
{
    class AudioManager
    {
    private:
        SoLoud::Soloud m_engine;
    public:
        AudioManager();
    };

    extern AudioManager Audio;
}