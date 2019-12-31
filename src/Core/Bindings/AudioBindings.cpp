#include <Audio/AudioManager.hpp>
#include <Audio/Sound.hpp>
#include <Bindings/AudioBindings.hpp>
#include <Bindings/Bindings.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::AudioBindings
{
    KAGUYA_MEMBER_FUNCTION_OVERLOADS(
        AudioManager_load_wrapper, Audio::AudioManager, load, 1, 2);
    void LoadAudioManager(kaguya::State* lua)
    {
        (*lua)["obe"]["AudioManager"].setClass(
            kaguya::UserdataMetatable<Audio::AudioManager>()
                .addFunction("cache", &Audio::AudioManager::cache)
                .addFunction("load", AudioManager_load_wrapper()));
    }
    void LoadSound(kaguya::State* lua)
    {
        (*lua)["obe"]["Sound"].setClass(
            kaguya::UserdataMetatable<Audio::Sound>()
                .addFunction("getDuration", &Audio::Sound::getDuration)
                .addFunction("getLooping", &Audio::Sound::getLooping)
                .addFunction("getOffset", &Audio::Sound::getOffset)
                .addFunction("getPitch", &Audio::Sound::getPitch)
                .addFunction("getStatus", &Audio::Sound::getStatus)
                .addFunction("getVolume", &Audio::Sound::getVolume)
                .addFunction("pause", &Audio::Sound::pause)
                .addFunction("play", &Audio::Sound::play)
                .addFunction("setLooping", &Audio::Sound::setLooping)
                .addFunction("setOffset", &Audio::Sound::setOffset)
                .addFunction("setPitch", &Audio::Sound::setPitch)
                .addFunction("setVolume", &Audio::Sound::setVolume)
                .addFunction("stop", &Audio::Sound::stop));
        (*lua)["obe"]["Sound"]["Status"] = kaguya::NewTable();
        (*lua)["obe"]["Sound"]["Status"]["Playing"] = Audio::SoundStatus::Playing;
        (*lua)["obe"]["Sound"]["Status"]["Paused"] = Audio::SoundStatus::Paused;
        (*lua)["obe"]["Sound"]["Status"]["Stopped"] = Audio::SoundStatus::Stopped;
    }
}
