#pragma once

#include <memory>

namespace SoLoud
{
    class Soloud;
    class AudioSource;

    using Handle = unsigned int; // Forward declare equivalent type "handle" without name collision
} // namespace SoLoud

namespace obe::audio
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

    class Sound;

    class SoundHandle
    {
    private:
        const Sound& m_sound;
        SoLoud::Handle m_handle;
        float m_pitch = 1.f;
        float m_speed = 1.f;
        float m_volume = 1.f;
        bool m_looping = false;

        void apply_changes();

    public:
        SoundHandle(const Sound& sound);

        [[nodiscard]] const Sound& get_sound() const;

        void play();
        void pause() const;
        void stop() const;

        void set_pitch(float pitch);
        [[nodiscard]] float get_pitch() const;

        void set_speed(float speed);
        [[nodiscard]] float get_speed() const;

        [[nodiscard]] SoundStatus get_status() const;

        [[nodiscard]] double get_offset() const;
        void set_offset(double offset) const;

        [[nodiscard]] float get_volume() const;
        void set_volume(float volume);

        void set_looping(bool looping);
        [[nodiscard]] bool is_looping() const;
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
        SoundHandle m_base_handle;
        float m_base_samplerate;
        void apply_changes();

        friend class SoundHandle;

    public:
        Sound(SoLoud::Soloud& manager, std::shared_ptr<SoLoud::AudioSource> source);

        [[nodiscard]] double get_duration() const;

        void play();
        void pause() const;
        void stop() const;
        [[nodiscard]] SoundHandle make_handle() const;

        void set_pitch(float pitch);
        [[nodiscard]] float get_pitch() const;

        void set_speed(float speed);
        [[nodiscard]] float get_speed() const;

        [[nodiscard]] SoundStatus get_status() const;

        [[nodiscard]] double get_offset() const;
        void set_offset(double offset) const;

        [[nodiscard]] float get_volume() const;
        void set_volume(float volume);

        void set_looping(bool looping);
        [[nodiscard]] bool is_looping() const;
    };
} // namespace obe::audio
