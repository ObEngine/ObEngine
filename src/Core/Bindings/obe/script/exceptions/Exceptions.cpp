#include <Bindings/obe/script/exceptions/Exceptions.hpp>

#include <Script/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::script::exceptions::bindings
{
    void load_class_game_object_script_error(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::GameObjectScriptError> bind_game_object_script_error
            = exceptions_namespace.new_usertype<obe::script::exceptions::GameObjectScriptError>(
                "GameObjectScriptError", sol::call_constructor,
                sol::constructors<obe::script::exceptions::GameObjectScriptError(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::GameObjectScriptError>,
                    obe::BaseException>());
    }
    void load_class_invalid_script(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::InvalidScript> bind_invalid_script
            = exceptions_namespace.new_usertype<obe::script::exceptions::InvalidScript>(
                "InvalidScript", sol::call_constructor,
                sol::constructors<obe::script::exceptions::InvalidScript(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::InvalidScript>,
                    obe::BaseException>());
    }
    void load_class_lua_execution_error(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::LuaExecutionError> bind_lua_execution_error
            = exceptions_namespace.new_usertype<obe::script::exceptions::LuaExecutionError>(
                "LuaExecutionError", sol::call_constructor,
                sol::constructors<obe::script::exceptions::LuaExecutionError(
                    const std::exception&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::LuaExecutionError>,
                    obe::BaseException>());
    }
    void load_class_lua_nested_exception_error(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::LuaNestedExceptionError>
            bind_lua_nested_exception_error
            = exceptions_namespace.new_usertype<obe::script::exceptions::LuaNestedExceptionError>(
                "LuaNestedExceptionError", sol::call_constructor,
                sol::constructors<obe::script::exceptions::LuaNestedExceptionError(
                    const std::exception&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::LuaNestedExceptionError>,
                    obe::BaseException>());
    }
    void load_class_no_such_component(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::NoSuchComponent> bind_no_such_component
            = exceptions_namespace.new_usertype<obe::script::exceptions::NoSuchComponent>(
                "NoSuchComponent", sol::call_constructor,
                sol::constructors<obe::script::exceptions::NoSuchComponent(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::NoSuchComponent>,
                    obe::BaseException>());
    }
    void load_class_object_definition_not_found(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::ObjectDefinitionNotFound>
            bind_object_definition_not_found
            = exceptions_namespace.new_usertype<obe::script::exceptions::ObjectDefinitionNotFound>(
                "ObjectDefinitionNotFound", sol::call_constructor,
                sol::constructors<obe::script::exceptions::ObjectDefinitionNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::ObjectDefinitionNotFound>,
                    obe::BaseException>());
    }
    void load_class_script_file_not_found(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::ScriptFileNotFound> bind_script_file_not_found
            = exceptions_namespace.new_usertype<obe::script::exceptions::ScriptFileNotFound>(
                "ScriptFileNotFound", sol::call_constructor,
                sol::constructors<obe::script::exceptions::ScriptFileNotFound(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::ScriptFileNotFound>,
                    obe::BaseException>());
    }
    void load_class_wrong_source_attribute_type(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::WrongSourceAttributeType>
            bind_wrong_source_attribute_type
            = exceptions_namespace.new_usertype<obe::script::exceptions::WrongSourceAttributeType>(
                "WrongSourceAttributeType", sol::call_constructor,
                sol::constructors<obe::script::exceptions::WrongSourceAttributeType(
                    std::string_view, std::string_view, std::string_view, std::string_view,
                    obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::WrongSourceAttributeType>,
                    obe::BaseException>());
    }
};