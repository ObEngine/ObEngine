#include <Bindings/obe/Script/Exceptions/Exceptions.hpp>

#include <Script/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Script::Exceptions::Bindings
{
    void LoadClassGameObjectScriptError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::GameObjectScriptError> bindGameObjectScriptError
            = ExceptionsNamespace.new_usertype<obe::Script::Exceptions::GameObjectScriptError>(
                "GameObjectScriptError", sol::call_constructor,
                sol::constructors<obe::Script::Exceptions::GameObjectScriptError(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Script::Exceptions::GameObjectScriptError>,
                    obe::BaseException>());
    }
    void LoadClassInvalidScript(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::InvalidScript> bindInvalidScript
            = ExceptionsNamespace.new_usertype<obe::Script::Exceptions::InvalidScript>(
                "InvalidScript", sol::call_constructor,
                sol::constructors<obe::Script::Exceptions::InvalidScript(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Script::Exceptions::InvalidScript>,
                    obe::BaseException>());
    }
    void LoadClassLuaExecutionError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::LuaExecutionError> bindLuaExecutionError
            = ExceptionsNamespace.new_usertype<obe::Script::Exceptions::LuaExecutionError>(
                "LuaExecutionError", sol::call_constructor,
                sol::constructors<obe::Script::Exceptions::LuaExecutionError(
                    const std::exception&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Script::Exceptions::LuaExecutionError>,
                    obe::BaseException>());
    }
    void LoadClassNoSuchComponent(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::NoSuchComponent> bindNoSuchComponent
            = ExceptionsNamespace.new_usertype<obe::Script::Exceptions::NoSuchComponent>(
                "NoSuchComponent", sol::call_constructor,
                sol::constructors<obe::Script::Exceptions::NoSuchComponent(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Script::Exceptions::NoSuchComponent>,
                    obe::BaseException>());
    }
    void LoadClassObjectDefinitionNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::ObjectDefinitionNotFound>
            bindObjectDefinitionNotFound
            = ExceptionsNamespace.new_usertype<obe::Script::Exceptions::ObjectDefinitionNotFound>(
                "ObjectDefinitionNotFound", sol::call_constructor,
                sol::constructors<obe::Script::Exceptions::ObjectDefinitionNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Script::Exceptions::ObjectDefinitionNotFound>,
                    obe::BaseException>());
    }
    void LoadClassScriptFileNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::ScriptFileNotFound> bindScriptFileNotFound
            = ExceptionsNamespace.new_usertype<obe::Script::Exceptions::ScriptFileNotFound>(
                "ScriptFileNotFound", sol::call_constructor,
                sol::constructors<obe::Script::Exceptions::ScriptFileNotFound(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Script::Exceptions::ScriptFileNotFound>,
                    obe::BaseException>());
    }
    void LoadClassWrongSourceAttributeType(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::WrongSourceAttributeType>
            bindWrongSourceAttributeType
            = ExceptionsNamespace.new_usertype<obe::Script::Exceptions::WrongSourceAttributeType>(
                "WrongSourceAttributeType", sol::call_constructor,
                sol::constructors<obe::Script::Exceptions::WrongSourceAttributeType(
                    std::string_view, std::string_view, std::string_view, std::string_view,
                    obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Script::Exceptions::WrongSourceAttributeType>,
                    obe::BaseException>());
    }
};