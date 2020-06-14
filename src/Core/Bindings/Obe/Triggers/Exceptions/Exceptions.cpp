#include <Bindings/obe/Triggers/Exceptions/Exceptions.hpp>

#include <Triggers/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Triggers::Exceptions::Bindings
{
    void LoadClassCallbackCreationError(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Triggers"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Triggers::Exceptions::CallbackCreationError>
            bindCallbackCreationError
            = ExceptionsNamespace
                  .new_usertype<obe::Triggers::Exceptions::CallbackCreationError>(
                      "CallbackCreationError", sol::call_constructor,
                      sol::constructors<obe::Triggers::Exceptions::CallbackCreationError(
                          std::string_view, std::string_view, std::string_view,
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassTriggerExecutionError(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Triggers"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Triggers::Exceptions::TriggerExecutionError>
            bindTriggerExecutionError
            = ExceptionsNamespace
                  .new_usertype<obe::Triggers::Exceptions::TriggerExecutionError>(
                      "TriggerExecutionError", sol::call_constructor,
                      sol::constructors<obe::Triggers::Exceptions::TriggerExecutionError(
                          std::string_view, std::string_view, std::string_view,
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassTriggerGroupAlreadyExists(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Triggers"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Triggers::Exceptions::TriggerGroupAlreadyExists>
            bindTriggerGroupAlreadyExists = ExceptionsNamespace.new_usertype<
                obe::Triggers::Exceptions::TriggerGroupAlreadyExists>(
                "TriggerGroupAlreadyExists", sol::call_constructor,
                sol::constructors<obe::Triggers::Exceptions::TriggerGroupAlreadyExists(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassTriggerGroupNotJoinable(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Triggers"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Triggers::Exceptions::TriggerGroupNotJoinable>
            bindTriggerGroupNotJoinable = ExceptionsNamespace.new_usertype<
                obe::Triggers::Exceptions::TriggerGroupNotJoinable>(
                "TriggerGroupNotJoinable", sol::call_constructor,
                sol::constructors<obe::Triggers::Exceptions::TriggerGroupNotJoinable(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassTriggerNamespaceAlreadyExists(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Triggers"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Triggers::Exceptions::TriggerNamespaceAlreadyExists>
            bindTriggerNamespaceAlreadyExists
            = ExceptionsNamespace
                  .new_usertype<obe::Triggers::Exceptions::TriggerNamespaceAlreadyExists>(
                      "TriggerNamespaceAlreadyExists", sol::call_constructor,
                      sol::constructors<
                          obe::Triggers::Exceptions::TriggerNamespaceAlreadyExists(
                              std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownTrigger(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Triggers"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Triggers::Exceptions::UnknownTrigger> bindUnknownTrigger
            = ExceptionsNamespace.new_usertype<obe::Triggers::Exceptions::UnknownTrigger>(
                "UnknownTrigger", sol::call_constructor,
                sol::constructors<obe::Triggers::Exceptions::UnknownTrigger(
                    std::string_view, std::string_view, std::string_view,
                    const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownTriggerGroup(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Triggers"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Triggers::Exceptions::UnknownTriggerGroup>
            bindUnknownTriggerGroup
            = ExceptionsNamespace
                  .new_usertype<obe::Triggers::Exceptions::UnknownTriggerGroup>(
                      "UnknownTriggerGroup", sol::call_constructor,
                      sol::constructors<obe::Triggers::Exceptions::UnknownTriggerGroup(
                          std::string_view, std::string_view,
                          const std::vector<std::string>&, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownTriggerNamespace(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Triggers"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Triggers::Exceptions::UnknownTriggerNamespace>
            bindUnknownTriggerNamespace = ExceptionsNamespace.new_usertype<
                obe::Triggers::Exceptions::UnknownTriggerNamespace>(
                "UnknownTriggerNamespace", sol::call_constructor,
                sol::constructors<obe::Triggers::Exceptions::UnknownTriggerNamespace(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
};