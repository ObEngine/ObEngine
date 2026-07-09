#include <Bindings/obe/audio/Audio.hpp>

#include <Audio/AudioManager.hpp>
#include <Audio/Sound.hpp>
#include <System/Path.hpp>
#include <soloud/soloud.h>

#include <Bindings/Config.hpp>

namespace obe::audio::bindings
{
    void load_enum_load_policy(sol::state_view state)
    {
        sol::table audio_namespace = state["obe"]["audio"].get<sol::table>();
        audio_namespace.new_enum<obe::audio::LoadPolicy>("LoadPolicy",
            { { "Normal", obe::audio::LoadPolicy::Normal },
                { "Cache", obe::audio::LoadPolicy::Cache },
                { "Stream", obe::audio::LoadPolicy::Stream } });
    }
    void load_enum_sound_status(sol::state_view state)
    {
        sol::table audio_namespace = state["obe"]["audio"].get<sol::table>();
        audio_namespace.new_enum<obe::audio::SoundStatus>("SoundStatus",
            { { "Playing", obe::audio::SoundStatus::Playing },
                { "Paused", obe::audio::SoundStatus::Paused },
                { "Stopped", obe::audio::SoundStatus::Stopped } });
    }
    void load_class_audio_manager(sol::state_view state)
    {
        sol::table audio_namespace = state["obe"]["audio"].get<sol::table>();
        sol::usertype<obe::audio::AudioManager> bind_audio_manager
            = audio_namespace.new_usertype<obe::audio::AudioManager>("AudioManager",
                sol::call_constructor, sol::constructors<obe::audio::AudioManager()>());
        bind_audio_manager["load"] = sol::overload(
            [](obe::audio::AudioManager* self, const obe::system::Path& path) -> obe::audio::Sound {
                return self->load(path);
            },
            [](obe::audio::AudioManager* self, const obe::system::Path& path,
                obe::audio::LoadPolicy load_policy) -> obe::audio::Sound {
                return self->load(path, load_policy);
            });
    }
    void load_class_sound(sol::state_view state)
    {
        sol::table audio_namespace = state["obe"]["audio"].get<sol::table>();
        sol::usertype<obe::audio::Sound> bind_sound
            = audio_namespace.new_usertype<obe::audio::Sound>("Sound", sol::call_constructor,
                sol::constructors<obe::audio::Sound(
                    SoLoud::Soloud&, std::shared_ptr<SoLoud::AudioSource>)>());
        bind_sound["get_duration"] = &obe::audio::Sound::get_duration;
        bind_sound["play"] = &obe::audio::Sound::play;
        bind_sound["pause"] = &obe::audio::Sound::pause;
        bind_sound["stop"] = &obe::audio::Sound::stop;
        bind_sound["make_handle"] = &obe::audio::Sound::make_handle;
        bind_sound["set_pitch"] = &obe::audio::Sound::set_pitch;
        bind_sound["get_pitch"] = &obe::audio::Sound::get_pitch;
        bind_sound["set_speed"] = &obe::audio::Sound::set_speed;
        bind_sound["get_speed"] = &obe::audio::Sound::get_speed;
        bind_sound["get_status"] = &obe::audio::Sound::get_status;
        bind_sound["get_offset"] = &obe::audio::Sound::get_offset;
        bind_sound["set_offset"] = &obe::audio::Sound::set_offset;
        bind_sound["get_volume"] = &obe::audio::Sound::get_volume;
        bind_sound["set_volume"] = &obe::audio::Sound::set_volume;
        bind_sound["set_looping"] = &obe::audio::Sound::set_looping;
        bind_sound["is_looping"] = &obe::audio::Sound::is_looping;
    }
    void load_class_sound_handle(sol::state_view state)
    {
        sol::table audio_namespace = state["obe"]["audio"].get<sol::table>();
        sol::usertype<obe::audio::SoundHandle> bind_sound_handle
            = audio_namespace.new_usertype<obe::audio::SoundHandle>("SoundHandle",
                sol::call_constructor,
                sol::constructors<obe::audio::SoundHandle(const obe::audio::Sound&)>());
        bind_sound_handle["get_sound"] = &obe::audio::SoundHandle::get_sound;
        bind_sound_handle["play"] = &obe::audio::SoundHandle::play;
        bind_sound_handle["pause"] = &obe::audio::SoundHandle::pause;
        bind_sound_handle["stop"] = &obe::audio::SoundHandle::stop;
        bind_sound_handle["set_pitch"] = &obe::audio::SoundHandle::set_pitch;
        bind_sound_handle["get_pitch"] = &obe::audio::SoundHandle::get_pitch;
        bind_sound_handle["set_speed"] = &obe::audio::SoundHandle::set_speed;
        bind_sound_handle["get_speed"] = &obe::audio::SoundHandle::get_speed;
        bind_sound_handle["get_status"] = &obe::audio::SoundHandle::get_status;
        bind_sound_handle["get_offset"] = &obe::audio::SoundHandle::get_offset;
        bind_sound_handle["set_offset"] = &obe::audio::SoundHandle::set_offset;
        bind_sound_handle["get_volume"] = &obe::audio::SoundHandle::get_volume;
        bind_sound_handle["set_volume"] = &obe::audio::SoundHandle::set_volume;
        bind_sound_handle["set_looping"] = &obe::audio::SoundHandle::set_looping;
        bind_sound_handle["is_looping"] = &obe::audio::SoundHandle::is_looping;
    }
};