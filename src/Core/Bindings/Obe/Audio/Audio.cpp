#include <Bindings/obe/Audio/Audio.hpp>

#include <Audio/AudioManager.hpp>
#include <Audio/Sound.hpp>

#include <Bindings/Config.hpp>

namespace obe::Audio::Bindings
{
    void LoadEnumLoadPolicy(sol::state_view state)
    {
        sol::table AudioNamespace = state["obe"]["Audio"].get<sol::table>();
        AudioNamespace.new_enum<obe::Audio::LoadPolicy>("LoadPolicy",
            { { "Normal", obe::Audio::LoadPolicy::Normal },
                { "Cache", obe::Audio::LoadPolicy::Cache },
                { "Stream", obe::Audio::LoadPolicy::Stream } });
    }
    void LoadEnumSoundStatus(sol::state_view state)
    {
        sol::table AudioNamespace = state["obe"]["Audio"].get<sol::table>();
        AudioNamespace.new_enum<obe::Audio::SoundStatus>("SoundStatus",
            { { "Playing", obe::Audio::SoundStatus::Playing },
                { "Paused", obe::Audio::SoundStatus::Paused },
                { "Stopped", obe::Audio::SoundStatus::Stopped } });
    }
    void LoadClassAudioManager(sol::state_view state)
    {
        sol::table AudioNamespace = state["obe"]["Audio"].get<sol::table>();
        sol::usertype<obe::Audio::AudioManager> bindAudioManager
            = AudioNamespace.new_usertype<obe::Audio::AudioManager>("AudioManager",
                sol::call_constructor, sol::constructors<obe::Audio::AudioManager()>());
        bindAudioManager["load"] = sol::overload(
            [](obe::Audio::AudioManager* self, const obe::System::Path& path)
                -> obe::Audio::Sound { return self->load(path); },
            [](obe::Audio::AudioManager* self, const obe::System::Path& path,
                obe::Audio::LoadPolicy loadPolicy) -> obe::Audio::Sound {
                return self->load(path, loadPolicy);
            });
    }
    void LoadClassSound(sol::state_view state)
    {
        sol::table AudioNamespace = state["obe"]["Audio"].get<sol::table>();
        sol::usertype<obe::Audio::Sound> bindSound
            = AudioNamespace.new_usertype<obe::Audio::Sound>("Sound",
                sol::call_constructor,
                sol::constructors<obe::Audio::Sound(
                    SoLoud::Soloud&, std::shared_ptr<SoLoud::AudioSource>)>());
        bindSound["getDuration"] = &obe::Audio::Sound::getDuration;
        bindSound["play"] = &obe::Audio::Sound::play;
        bindSound["pause"] = &obe::Audio::Sound::pause;
        bindSound["stop"] = &obe::Audio::Sound::stop;
        bindSound["setPitch"] = &obe::Audio::Sound::setPitch;
        bindSound["getPitch"] = &obe::Audio::Sound::getPitch;
        bindSound["getStatus"] = &obe::Audio::Sound::getStatus;
        bindSound["getOffset"] = &obe::Audio::Sound::getOffset;
        bindSound["setOffset"] = &obe::Audio::Sound::setOffset;
        bindSound["getVolume"] = &obe::Audio::Sound::getVolume;
        bindSound["setVolume"] = &obe::Audio::Sound::setVolume;
        bindSound["setLooping"] = &obe::Audio::Sound::setLooping;
        bindSound["getLooping"] = &obe::Audio::Sound::getLooping;
    }
};