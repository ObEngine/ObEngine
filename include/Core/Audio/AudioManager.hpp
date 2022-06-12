#pragma once

#include <memory>
#include <unordered_map>

namespace SoLoud
{
    class Wav;
    class Soloud;
}

namespace obe
{
    namespace System
    {
        class Path;
    }
}

/**
 * \additionalinclude{System/Path.hpp}
 * \additionalinclude{soloud/soloud.h}
 */
namespace obe::audio
{
    class Sound;

    /**
     * \brief Defines how a sound should be loaded
     */
    enum class LoadPolicy
    {
        /**
         * \brief The sound will be loaded in memory from a file or the cache
         */
        Normal,
        /**
         * \brief The sound will be loaded in memory and cached in the AudioManager
         */
        Cache,
        /**
         * \brief The sound will be streamed from a disk or copied from the cache
         */
        Stream
    };

    /**
     * \brief Class to handle audio playback
     */
    class AudioManager
    {
    private:
        std::unique_ptr<SoLoud::Soloud> m_engine;
        std::unordered_map<std::string, std::shared_ptr<SoLoud::Wav>> m_cache;

    public:
        /**
         * \brief Initializes the underlying audio engine
         */
        AudioManager();
        /**
         * \brief Closes the underlying audio engine
         */
        ~AudioManager();

        AudioManager& operator=(AudioManager&&) = delete;

        /**
         * \brief Loads a sound file at a given path
         * \param path Path to the sound file
         * \param load_policy The way you want to load the sound file
         * \return A Sound object loaded with the sound file
         */
        Sound load(const System::Path& path, LoadPolicy load_policy = LoadPolicy::Normal);
    };
}
