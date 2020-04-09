#pragma once

#include <memory>

#include <soloud/soloud.h>

namespace obe::Audio
{
    class AudioManager;

    /**
     * \brief Enum that defines the current status of a sound
     */
    enum class SoundStatus
    {
        // The sound is currently playing
        Playing,
        // The sound is paused
        Paused,
        // The sound is stopped
        Stopped
    };

    /**
     * \brief Class to handle sounds / musics
     *        The music can be either streamed from disk or read from ram
     */
    class Sound
    {
    private:
        SoLoud::Soloud& m_manager;
        std::shared_ptr<SoLoud::AudioSource> m_source;
        SoLoud::handle m_handle;
        float m_baseSamplerate;
        float m_pitch = 1.f;
        bool m_looping = false;
        float m_volume = 1.f;
        void applyChanges();

    public:
        Sound(SoLoud::Soloud& manager, std::shared_ptr<SoLoud::AudioSource> source);
        [[nodiscard]] double getDuration() const;
        void play();
        void pause() const;
        void stop() const;

        void setPitch(float pitch);
        [[nodiscard]] float getPitch() const;

        [[nodiscard]] SoundStatus getStatus() const;

        [[nodiscard]] double getOffset() const;
        void setOffset(double offset) const;

        [[nodiscard]] float getVolume() const;
        void setVolume(float volume);

        void setLooping(bool looping);
        [[nodiscard]] bool getLooping() const;
    };
}