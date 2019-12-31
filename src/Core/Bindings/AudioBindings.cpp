#include <Audio/AudioManager.hpp>
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
        (*lua)["obe"]["Sound"].setClass(
            kaguya::UserdataMetatable<Audio::Sound>()
                .addFunction("getDuration", &Audio::Sound::getDuration)
                .addFunction("getPitch", &Audio::Sound::getPitch)
                .addFunction("pause", &Audio::Sound::pause)
                .addFunction("play", &Audio::Sound::play)
                .addFunction("setPitch", &Audio::Sound::setPitch)
                .addFunction("stop", &Audio::Sound::stop));
    }
}
