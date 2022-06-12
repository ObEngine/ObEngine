#include <Bindings/obe/Event/Exceptions/Exceptions.hpp>

#include <Event/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::event::Exceptions::Bindings
{
    void LoadClassCallbackCreationError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["event"]["exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::CallbackCreationError> bindCallbackCreationError
            = ExceptionsNamespace.new_usertype<obe::event::Exceptions::CallbackCreationError>(
                "CallbackCreationError", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::CallbackCreationError(std::string_view,
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::CallbackCreationError>,
                    obe::BaseException>());
    }
    void LoadClassEventAlreadyExists(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["event"]["exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventAlreadyExists> bindEventAlreadyExists
            = ExceptionsNamespace.new_usertype<obe::event::Exceptions::EventAlreadyExists>(
                "EventAlreadyExists", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventAlreadyExists(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventAlreadyExists>,
                    obe::BaseException>());
    }
    void LoadClassEventExecutionError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["event"]["exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventExecutionError> bindEventExecutionError
            = ExceptionsNamespace.new_usertype<obe::event::Exceptions::EventExecutionError>(
                "EventExecutionError", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventExecutionError(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventExecutionError>,
                    obe::BaseException>());
    }
    void LoadClassEventGroupAlreadyExists(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["event"]["exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventGroupAlreadyExists> bindEventGroupAlreadyExists
            = ExceptionsNamespace.new_usertype<obe::event::Exceptions::EventGroupAlreadyExists>(
                "EventGroupAlreadyExists", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventGroupAlreadyExists(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventGroupAlreadyExists>,
                    obe::BaseException>());
    }
    void LoadClassEventGroupNotJoinable(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["event"]["exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventGroupNotJoinable> bindEventGroupNotJoinable
            = ExceptionsNamespace.new_usertype<obe::event::Exceptions::EventGroupNotJoinable>(
                "EventGroupNotJoinable", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventGroupNotJoinable(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventGroupNotJoinable>,
                    obe::BaseException>());
    }
    void LoadClassEventNamespaceAlreadyExists(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["event"]["exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventNamespaceAlreadyExists>
            bindEventNamespaceAlreadyExists
            = ExceptionsNamespace.new_usertype<obe::event::Exceptions::EventNamespaceAlreadyExists>(
                "EventNamespaceAlreadyExists", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventNamespaceAlreadyExists(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventNamespaceAlreadyExists>,
                    obe::BaseException>());
    }
    void LoadClassEventNamespaceNotJoinable(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["event"]["exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventNamespaceNotJoinable>
            bindEventNamespaceNotJoinable
            = ExceptionsNamespace.new_usertype<obe::event::Exceptions::EventNamespaceNotJoinable>(
                "EventNamespaceNotJoinable", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventNamespaceNotJoinable(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventNamespaceNotJoinable>,
                    obe::BaseException>());
    }
    void LoadClassUnknownEvent(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["event"]["exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::UnknownEvent> bindUnknownEvent
            = ExceptionsNamespace.new_usertype<obe::event::Exceptions::UnknownEvent>("UnknownEvent",
                sol::call_constructor,
                sol::constructors<obe::event::Exceptions::UnknownEvent(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::UnknownEvent>,
                    obe::BaseException>());
    }
    void LoadClassUnknownEventGroup(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["event"]["exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::UnknownEventGroup> bindUnknownEventGroup
            = ExceptionsNamespace.new_usertype<obe::event::Exceptions::UnknownEventGroup>(
                "UnknownEventGroup", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::UnknownEventGroup(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::UnknownEventGroup>,
                    obe::BaseException>());
    }
    void LoadClassUnknownEventNamespace(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["event"]["exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::UnknownEventNamespace> bindUnknownEventNamespace
            = ExceptionsNamespace.new_usertype<obe::event::Exceptions::UnknownEventNamespace>(
                "UnknownEventNamespace", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::UnknownEventNamespace(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::UnknownEventNamespace>,
                    obe::BaseException>());
    }
};