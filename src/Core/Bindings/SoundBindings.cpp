#include <Bindings/SoundBindings.hpp>
#include <Sound/Music.hpp>
#include <Sound/Sound.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::SoundBindings
{
    void LoadMusic(kaguya::State* lua)
    {
        (*lua)["obe"]["Music"].setClass(kaguya::UserdataMetatable<Sound::MusicWrapper>()
            .setConstructors<Sound::MusicWrapper(), Sound::MusicWrapper(const std::string&)>()
            .addFunction("doesUsesSoundPosition", &Sound::MusicWrapper::doesUsesSoundPosition)
            .addFunction("getDuration", &Sound::MusicWrapper::getDuration)
            .addFunction("getMinimumDistance", &Sound::MusicWrapper::getMinimumDistance)
            .addFunction("getPitch", &Sound::MusicWrapper::getPitch)
            .addFunction("getPlayingOffset", &Sound::MusicWrapper::getPlayingOffset)
            .addFunction("getPosition", &Sound::MusicWrapper::getPosition)
            .addFunction("getSpatialAttenuation", &Sound::MusicWrapper::getSpatialAttenuation)
            .addFunction("getStatus", &Sound::MusicWrapper::getStatus)
            .addFunction("getVolume", &Sound::MusicWrapper::getVolume)
            .addFunction("isLooping", &Sound::MusicWrapper::isLooping)
            .addFunction("load", &Sound::MusicWrapper::load)
            .addFunction("pause", &Sound::MusicWrapper::pause)
            .addFunction("play", &Sound::MusicWrapper::play)
            .addFunction("setLooping", &Sound::MusicWrapper::setLooping)
            .addFunction("setMinimumDistance", &Sound::MusicWrapper::setMinimumDistance)
            .addFunction("setPitch", &Sound::MusicWrapper::setPitch)
            .addFunction("setPlayingOffset", &Sound::MusicWrapper::setPlayingOffset)
            .addFunction("setPosition", &Sound::MusicWrapper::setPosition)
            .addFunction("setSpatialAttenuation", &Sound::MusicWrapper::setSpatialAttenuation)
            .addFunction("setVolume", &Sound::MusicWrapper::setVolume)
            .addFunction("stop", &Sound::MusicWrapper::stop)
            .addFunction("useSoundPosition", &Sound::MusicWrapper::useSoundPosition)
        );
    }

    void LoadSound(kaguya::State* lua)
    {
        (*lua)["obe"]["Sound"].setClass(kaguya::UserdataMetatable<Sound::SoundWrapper>()
            .setConstructors<Sound::SoundWrapper(), Sound::SoundWrapper(const std::string&)>()
            .addFunction("doesUsesSoundPosition", &Sound::SoundWrapper::doesUsesSoundPosition)
            .addFunction("getMinimumDistance", &Sound::SoundWrapper::getMinimumDistance)
            .addFunction("getPitch", &Sound::SoundWrapper::getPitch)
            .addFunction("getPlayingOffset", &Sound::SoundWrapper::getPlayingOffset)
            .addFunction("getPosition", &Sound::SoundWrapper::getPosition)
            .addFunction("getSpatialAttenuation", &Sound::SoundWrapper::getSpatialAttenuation)
            .addFunction("getStatus", &Sound::SoundWrapper::getStatus)
            .addFunction("getVolume", &Sound::SoundWrapper::getVolume)
            .addFunction("isLooping", &Sound::SoundWrapper::isLooping)
            .addFunction("load", &Sound::SoundWrapper::load)
            .addFunction("pause", &Sound::SoundWrapper::pause)
            .addFunction("play", &Sound::SoundWrapper::play)
            .addFunction("setLooping", &Sound::SoundWrapper::setLooping)
            .addFunction("setMinimumDistance", &Sound::SoundWrapper::setMinimumDistance)
            .addFunction("setPitch", &Sound::SoundWrapper::setPitch)
            .addFunction("setPlayingOffset", &Sound::SoundWrapper::setPlayingOffset)
            .addFunction("setPosition", &Sound::SoundWrapper::setPosition)
            .addFunction("setSpatialAttenuation", &Sound::SoundWrapper::setSpatialAttenuation)
            .addFunction("setVolume", &Sound::SoundWrapper::setVolume)
            .addFunction("stop", &Sound::SoundWrapper::stop)
            .addFunction("useSoundPosition", &Sound::SoundWrapper::useSoundPosition)
        );
    }
}