#include <Bindings/obe/Audio/Exceptions/Exceptions.hpp>

#include <Audio/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Audio::Exceptions::Bindings
{
    void LoadClassAudioFileNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Audio"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Audio::Exceptions::AudioFileNotFound> bindAudioFileNotFound
            = ExceptionsNamespace.new_usertype<obe::Audio::Exceptions::AudioFileNotFound>(
                "AudioFileNotFound", sol::call_constructor,
                sol::constructors<obe::Audio::Exceptions::AudioFileNotFound(
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
};