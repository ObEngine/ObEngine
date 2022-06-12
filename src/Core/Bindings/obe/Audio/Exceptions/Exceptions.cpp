#include <Bindings/obe/Audio/Exceptions/Exceptions.hpp>

#include <Audio/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::audio::exceptions::Bindings
{
    void LoadClassAudioFileNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["audio"]["exceptions"].get<sol::table>();
        sol::usertype<obe::audio::exceptions::AudioFileNotFound> bindAudioFileNotFound
            = ExceptionsNamespace.new_usertype<obe::audio::exceptions::AudioFileNotFound>(
                "AudioFileNotFound", sol::call_constructor,
                sol::constructors<obe::audio::exceptions::AudioFileNotFound(
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::audio::exceptions::AudioFileNotFound>,
                    obe::BaseException>());
    }
};