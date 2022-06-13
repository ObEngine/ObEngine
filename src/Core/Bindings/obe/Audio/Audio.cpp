#include <Bindings/obe/Audio/Audio.hpp>

#include <Audio/AudioManager.hpp>
#include <Audio/Sound.hpp>
#include <System/Path.hpp>
#include <soloud/soloud.h>

#include <Bindings/Config.hpp>

namespace obe::audio::Bindings
{
    void LoadEnumLoadPolicy(sol::state_view state)
    {
        sol::table AudioNamespace = state["obe"]["audio"].get<sol::table>();
        AudioNamespace.new_enum<obe::audio::LoadPolicy>("LoadPolicy",
            { { "Normal", obe::audio::LoadPolicy::Normal },
                { "Cache", obe::audio::LoadPolicy::Cache },
                { "Stream", obe::audio::LoadPolicy::Stream } });
    }
    void LoadEnumSoundStatus(sol::state_view state)
    {
        sol::table AudioNamespace = state["obe"]["audio"].get<sol::table>();
        AudioNamespace.new_enum<obe::audio::SoundStatus>("SoundStatus",
            { { "Playing", obe::audio::SoundStatus::Playing },
                { "Paused", obe::audio::SoundStatus::Paused },
                { "Stopped", obe::audio::SoundStatus::Stopped } });
    }
    void LoadClassAudioManager(sol::state_view state)
    {
        sol::table AudioNamespace = state["obe"]["audio"].get<sol::table>();
        sol::usertype<obe::audio::AudioManager> bindAudioManager
            = AudioNamespace.new_usertype<obe::audio::AudioManager>("AudioManager",
                sol::call_constructor, sol::constructors<obe::audio::AudioManager()>());
        bindAudioManager["load"] = sol::overload(
            [](obe::audio::AudioManager* self, const obe::system::Path& path) -> obe::audio::Sound {
                return self->load(path);
            },
            [](obe::audio::AudioManager* self, const obe::system::Path& path,
                obe::audio::LoadPolicy loadPolicy) -> obe::audio::Sound {
                return self->load(path, loadPolicy);
            });
    }
    void LoadClassSound(sol::state_view state)
    {
        sol::table AudioNamespace = state["obe"]["audio"].get<sol::table>();
        sol::usertype<obe::audio::Sound> bindSound
            = AudioNamespace.new_usertype<obe::audio::Sound>("Sound", sol::call_constructor,
                sol::constructors<obe::audio::Sound(
                    SoLoud::Soloud&, std::shared_ptr<SoLoud::AudioSource>)>());
        bindSound["get_duration"] = &obe::audio::Sound::get_duration;
        bindSound["play"] = &obe::audio::Sound::play;
        bindSound["pause"] = &obe::audio::Sound::pause;
        bindSound["stop"] = &obe::audio::Sound::stop;
        bindSound["set_pitch"] = &obe::audio::Sound::set_pitch;
        bindSound["get_pitch"] = &obe::audio::Sound::get_pitch;
        bindSound["set_speed"] = &obe::audio::Sound::set_speed;
        bindSound["get_speed"] = &obe::audio::Sound::get_speed;
        bindSound["get_status"] = &obe::audio::Sound::get_status;
        bindSound["get_offset"] = &obe::audio::Sound::get_offset;
        bindSound["set_offset"] = &obe::audio::Sound::set_offset;
        bindSound["get_volume"] = &obe::audio::Sound::get_volume;
        bindSound["set_volume"] = &obe::audio::Sound::set_volume;
        bindSound["set_looping"] = &obe::audio::Sound::set_looping;
        bindSound["is_looping"] = &obe::audio::Sound::is_looping;
    }
};