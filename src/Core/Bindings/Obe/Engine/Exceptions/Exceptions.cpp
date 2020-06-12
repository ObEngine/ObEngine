#include <Bindings/obe/Engine/Exceptions/Exceptions.hpp>

#include <Engine/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Engine::Exceptions::Bindings
{
    void LoadClassBootScriptExecutionError(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Engine"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Engine::Exceptions::BootScriptExecutionError>
            bindBootScriptExecutionError
            = ExceptionsNamespace
                  .new_usertype<obe::Engine::Exceptions::BootScriptExecutionError>(
                      "BootScriptExecutionError", sol::call_constructor,
                      sol::constructors<obe::Engine::Exceptions::BootScriptExecutionError(
                          std::string_view, std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassBootScriptLoadingError(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Engine"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Engine::Exceptions::BootScriptLoadingError>
            bindBootScriptLoadingError
            = ExceptionsNamespace
                  .new_usertype<obe::Engine::Exceptions::BootScriptLoadingError>(
                      "BootScriptLoadingError", sol::call_constructor,
                      sol::constructors<obe::Engine::Exceptions::BootScriptLoadingError(
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
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
    void LoadClassUnitializedEngine(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Engine"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Engine::Exceptions::UnitializedEngine> bindUnitializedEngine
            = ExceptionsNamespace
                  .new_usertype<obe::Engine::Exceptions::UnitializedEngine>(
                      "UnitializedEngine", sol::call_constructor,
                      sol::constructors<obe::Engine::Exceptions::UnitializedEngine(
                          obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
};