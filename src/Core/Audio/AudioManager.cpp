#include <Audio\AudioManager.hpp>

namespace obe::Audio
{
    AudioManager::AudioManager()
    {
        m_engine.init();
    }
}