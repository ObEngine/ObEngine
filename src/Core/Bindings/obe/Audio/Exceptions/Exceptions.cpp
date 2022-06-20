#include <Bindings/obe/audio/exceptions/Exceptions.hpp>

#include <Audio/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::audio::exceptions::bindings
{
    void load_class_audio_file_not_found(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["audio"]["exceptions"].get<sol::table>();
        sol::usertype<obe::audio::exceptions::AudioFileNotFound> bind_audio_file_not_found
            = exceptions_namespace.new_usertype<obe::audio::exceptions::AudioFileNotFound>(
                "AudioFileNotFound", sol::call_constructor,
                sol::constructors<obe::audio::exceptions::AudioFileNotFound(
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::audio::exceptions::AudioFileNotFound>,
                    obe::BaseException>());
    }
};