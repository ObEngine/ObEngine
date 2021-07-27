#include <Bindings/obe/Script/Exceptions/Exceptions.hpp>

#include <Script/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Script::Exceptions::Bindings
{
    void LoadClassGameObjectScriptError(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::GameObjectScriptError>
            bindGameObjectScriptError
            = ExceptionsNamespace
                  .new_usertype<obe::Script::Exceptions::GameObjectScriptError>(
                      "GameObjectScriptError", sol::call_constructor,
                      sol::constructors<obe::Script::Exceptions::GameObjectScriptError(
                          std::string_view, std::string_view, std::string_view,
                          obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassInvalidScript(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::InvalidScript> bindInvalidScript
            = ExceptionsNamespace.new_usertype<obe::Script::Exceptions::InvalidScript>(
                "InvalidScript", sol::call_constructor,
                sol::constructors<obe::Script::Exceptions::InvalidScript(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassLuaExecutionError(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::LuaExecutionError> bindLuaExecutionError
            = ExceptionsNamespace
                  .new_usertype<obe::Script::Exceptions::LuaExecutionError>(
                      "LuaExecutionError", sol::call_constructor,
                      sol::constructors<obe::Script::Exceptions::LuaExecutionError(
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassNoSuchComponent(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::NoSuchComponent> bindNoSuchComponent
            = ExceptionsNamespace.new_usertype<obe::Script::Exceptions::NoSuchComponent>(
                "NoSuchComponent", sol::call_constructor,
                sol::constructors<obe::Script::Exceptions::NoSuchComponent(
                    std::string_view, std::string_view, std::string_view,
                    obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassObjectDefinitionBlockNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::ObjectDefinitionBlockNotFound>
            bindObjectDefinitionBlockNotFound = ExceptionsNamespace.new_usertype<
                obe::Script::Exceptions::ObjectDefinitionBlockNotFound>(
                "ObjectDefinitionBlockNotFound", sol::call_constructor,
                sol::constructors<obe::Script::Exceptions::ObjectDefinitionBlockNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassObjectDefinitionNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::ObjectDefinitionNotFound>
            bindObjectDefinitionNotFound
            = ExceptionsNamespace
                  .new_usertype<obe::Script::Exceptions::ObjectDefinitionNotFound>(
                      "ObjectDefinitionNotFound", sol::call_constructor,
                      sol::constructors<obe::Script::Exceptions::ObjectDefinitionNotFound(
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassScriptFileNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::ScriptFileNotFound> bindScriptFileNotFound
            = ExceptionsNamespace
                  .new_usertype<obe::Script::Exceptions::ScriptFileNotFound>(
                      "ScriptFileNotFound", sol::call_constructor,
                      sol::constructors<obe::Script::Exceptions::ScriptFileNotFound(
                          std::string_view, std::string_view, std::string_view,
                          obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassWrongSourceAttributeType(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Script"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Script::Exceptions::WrongSourceAttributeType>
            bindWrongSourceAttributeType
            = ExceptionsNamespace
                  .new_usertype<obe::Script::Exceptions::WrongSourceAttributeType>(
                      "WrongSourceAttributeType", sol::call_constructor,
                      sol::constructors<obe::Script::Exceptions::WrongSourceAttributeType(
                          std::string_view, std::string_view, std::string_view,
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
};