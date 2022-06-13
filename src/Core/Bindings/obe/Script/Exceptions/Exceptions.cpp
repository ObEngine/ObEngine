#include <Bindings/obe/Script/Exceptions/Exceptions.hpp>

#include <Script/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::script::exceptions::Bindings
{
    void LoadClassGameObjectScriptError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::GameObjectScriptError> bindGameObjectScriptError
            = ExceptionsNamespace.new_usertype<obe::script::exceptions::GameObjectScriptError>(
                "GameObjectScriptError", sol::call_constructor,
                sol::constructors<obe::script::exceptions::GameObjectScriptError(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::GameObjectScriptError>,
                    obe::BaseException>());
    }
    void LoadClassInvalidScript(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::InvalidScript> bindInvalidScript
            = ExceptionsNamespace.new_usertype<obe::script::exceptions::InvalidScript>(
                "InvalidScript", sol::call_constructor,
                sol::constructors<obe::script::exceptions::InvalidScript(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::InvalidScript>,
                    obe::BaseException>());
    }
    void LoadClassLuaExecutionError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::LuaExecutionError> bindLuaExecutionError
            = ExceptionsNamespace.new_usertype<obe::script::exceptions::LuaExecutionError>(
                "LuaExecutionError", sol::call_constructor,
                sol::constructors<obe::script::exceptions::LuaExecutionError(
                    const std::exception&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::LuaExecutionError>,
                    obe::BaseException>());
    }
    void LoadClassLuaNestedExceptionError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::LuaNestedExceptionError> bindLuaNestedExceptionError
            = ExceptionsNamespace.new_usertype<obe::script::exceptions::LuaNestedExceptionError>(
                "LuaNestedExceptionError", sol::call_constructor,
                sol::constructors<obe::script::exceptions::LuaNestedExceptionError(
                    const std::exception&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::LuaNestedExceptionError>,
                    obe::BaseException>());
    }
    void LoadClassNoSuchComponent(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::NoSuchComponent> bindNoSuchComponent
            = ExceptionsNamespace.new_usertype<obe::script::exceptions::NoSuchComponent>(
                "NoSuchComponent", sol::call_constructor,
                sol::constructors<obe::script::exceptions::NoSuchComponent(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::NoSuchComponent>,
                    obe::BaseException>());
    }
    void LoadClassObjectDefinitionNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::ObjectDefinitionNotFound>
            bindObjectDefinitionNotFound
            = ExceptionsNamespace.new_usertype<obe::script::exceptions::ObjectDefinitionNotFound>(
                "ObjectDefinitionNotFound", sol::call_constructor,
                sol::constructors<obe::script::exceptions::ObjectDefinitionNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::ObjectDefinitionNotFound>,
                    obe::BaseException>());
    }
    void LoadClassScriptFileNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::ScriptFileNotFound> bindScriptFileNotFound
            = ExceptionsNamespace.new_usertype<obe::script::exceptions::ScriptFileNotFound>(
                "ScriptFileNotFound", sol::call_constructor,
                sol::constructors<obe::script::exceptions::ScriptFileNotFound(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::ScriptFileNotFound>,
                    obe::BaseException>());
    }
    void LoadClassWrongSourceAttributeType(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["script"]["exceptions"].get<sol::table>();
        sol::usertype<obe::script::exceptions::WrongSourceAttributeType>
            bindWrongSourceAttributeType
            = ExceptionsNamespace.new_usertype<obe::script::exceptions::WrongSourceAttributeType>(
                "WrongSourceAttributeType", sol::call_constructor,
                sol::constructors<obe::script::exceptions::WrongSourceAttributeType(
                    std::string_view, std::string_view, std::string_view, std::string_view,
                    obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::script::exceptions::WrongSourceAttributeType>,
                    obe::BaseException>());
    }
};