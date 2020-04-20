#include <Bindings/Engine/Exceptions/Exceptions.hpp>

#include <Engine/Exceptions.hpp>

#include <sol/sol.hpp>

namespace obe::Engine::Exceptions::Bindings
{
    void LoadClassBootScriptMissing(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Engine"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Engine::Exceptions::BootScriptMissing> bindBootScriptMissing
            = ExceptionsNamespace
                  .new_usertype<obe::Engine::Exceptions::BootScriptMissing>(
                      "BootScriptMissing", sol::call_constructor,
                      sol::constructors<obe::Engine::Exceptions::BootScriptMissing(
                          const std::vector<std::string>&, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassFontNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Engine"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Engine::Exceptions::FontNotFound> bindFontNotFound
            = ExceptionsNamespace.new_usertype<obe::Engine::Exceptions::FontNotFound>(
                "FontNotFound", sol::call_constructor,
                sol::constructors<obe::Engine::Exceptions::FontNotFound(
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassTextureNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Engine"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Engine::Exceptions::TextureNotFound> bindTextureNotFound
            = ExceptionsNamespace.new_usertype<obe::Engine::Exceptions::TextureNotFound>(
                "TextureNotFound", sol::call_constructor,
                sol::constructors<obe::Engine::Exceptions::TextureNotFound(
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
};