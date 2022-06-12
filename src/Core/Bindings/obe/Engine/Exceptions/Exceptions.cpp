#include <Bindings/obe/Engine/Exceptions/Exceptions.hpp>

#include <Engine/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::engine::exceptions::Bindings
{
    void LoadClassBootScriptExecutionError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::BootScriptExecutionError>
            bindBootScriptExecutionError
            = ExceptionsNamespace.new_usertype<obe::engine::exceptions::BootScriptExecutionError>(
                "BootScriptExecutionError", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::BootScriptExecutionError(obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::BootScriptExecutionError>,
                    obe::BaseException>());
    }
    void LoadClassBootScriptLoadingError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::BootScriptLoadingError> bindBootScriptLoadingError
            = ExceptionsNamespace.new_usertype<obe::engine::exceptions::BootScriptLoadingError>(
                "BootScriptLoadingError", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::BootScriptLoadingError(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::BootScriptLoadingError>,
                    obe::BaseException>());
    }
    void LoadClassBootScriptMissing(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::BootScriptMissing> bindBootScriptMissing
            = ExceptionsNamespace.new_usertype<obe::engine::exceptions::BootScriptMissing>(
                "BootScriptMissing", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::BootScriptMissing(
                    const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::BootScriptMissing>,
                    obe::BaseException>());
    }
    void LoadClassFontNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::FontNotFound> bindFontNotFound
            = ExceptionsNamespace.new_usertype<obe::engine::exceptions::FontNotFound>(
                "FontNotFound", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::FontNotFound(
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::FontNotFound>,
                    obe::BaseException>());
    }
    void LoadClassTextureNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::TextureNotFound> bindTextureNotFound
            = ExceptionsNamespace.new_usertype<obe::engine::exceptions::TextureNotFound>(
                "TextureNotFound", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::TextureNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::TextureNotFound>,
                    obe::BaseException>());
    }
    void LoadClassUnitializedEngine(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::UnitializedEngine> bindUnitializedEngine
            = ExceptionsNamespace.new_usertype<obe::engine::exceptions::UnitializedEngine>(
                "UnitializedEngine", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::UnitializedEngine(obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::UnitializedEngine>,
                    obe::BaseException>());
    }
};