#include <Bindings/obe/engine/exceptions/Exceptions.hpp>

#include <Engine/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::engine::exceptions::bindings
{
    void load_class_boot_script_execution_error(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::BootScriptExecutionError>
            bind_boot_script_execution_error
            = exceptions_namespace.new_usertype<obe::engine::exceptions::BootScriptExecutionError>(
                "BootScriptExecutionError", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::BootScriptExecutionError(
                    obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::BootScriptExecutionError>,
                    obe::BaseException>());
    }
    void load_class_boot_script_loading_error(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::BootScriptLoadingError>
            bind_boot_script_loading_error
            = exceptions_namespace.new_usertype<obe::engine::exceptions::BootScriptLoadingError>(
                "BootScriptLoadingError", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::BootScriptLoadingError(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::BootScriptLoadingError>,
                    obe::BaseException>());
    }
    void load_class_boot_script_missing(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::BootScriptMissing> bind_boot_script_missing
            = exceptions_namespace.new_usertype<obe::engine::exceptions::BootScriptMissing>(
                "BootScriptMissing", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::BootScriptMissing(
                    const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::BootScriptMissing>,
                    obe::BaseException>());
    }
    void load_class_font_not_found(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::FontNotFound> bind_font_not_found
            = exceptions_namespace.new_usertype<obe::engine::exceptions::FontNotFound>(
                "FontNotFound", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::FontNotFound(
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::FontNotFound>,
                    obe::BaseException>());
    }
    void load_class_texture_not_found(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::TextureNotFound> bind_texture_not_found
            = exceptions_namespace.new_usertype<obe::engine::exceptions::TextureNotFound>(
                "TextureNotFound", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::TextureNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::TextureNotFound>,
                    obe::BaseException>());
    }
    void load_class_unitialized_engine(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["engine"]["exceptions"].get<sol::table>();
        sol::usertype<obe::engine::exceptions::UnitializedEngine> bind_unitialized_engine
            = exceptions_namespace.new_usertype<obe::engine::exceptions::UnitializedEngine>(
                "UnitializedEngine", sol::call_constructor,
                sol::constructors<obe::engine::exceptions::UnitializedEngine(obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::engine::exceptions::UnitializedEngine>,
                    obe::BaseException>());
    }
};