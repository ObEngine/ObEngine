#include <Bindings/obe/event/Exceptions/Exceptions.hpp>

#include <Event/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::event::Exceptions::bindings
{
    void load_class_callback_creation_error(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["event"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::CallbackCreationError> bind_callback_creation_error
            = Exceptions_namespace.new_usertype<obe::event::Exceptions::CallbackCreationError>(
                "CallbackCreationError", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::CallbackCreationError(std::string_view,
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::CallbackCreationError>,
                    obe::BaseException>());
    }
    void load_class_event_already_exists(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["event"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventAlreadyExists> bind_event_already_exists
            = Exceptions_namespace.new_usertype<obe::event::Exceptions::EventAlreadyExists>(
                "EventAlreadyExists", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventAlreadyExists(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventAlreadyExists>,
                    obe::BaseException>());
    }
    void load_class_event_execution_error(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["event"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventExecutionError> bind_event_execution_error
            = Exceptions_namespace.new_usertype<obe::event::Exceptions::EventExecutionError>(
                "EventExecutionError", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventExecutionError(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventExecutionError>,
                    obe::BaseException>());
    }
    void load_class_event_group_already_exists(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["event"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventGroupAlreadyExists>
            bind_event_group_already_exists
            = Exceptions_namespace.new_usertype<obe::event::Exceptions::EventGroupAlreadyExists>(
                "EventGroupAlreadyExists", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventGroupAlreadyExists(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventGroupAlreadyExists>,
                    obe::BaseException>());
    }
    void load_class_event_group_not_joinable(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["event"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventGroupNotJoinable> bind_event_group_not_joinable
            = Exceptions_namespace.new_usertype<obe::event::Exceptions::EventGroupNotJoinable>(
                "EventGroupNotJoinable", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventGroupNotJoinable(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventGroupNotJoinable>,
                    obe::BaseException>());
    }
    void load_class_event_namespace_already_exists(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["event"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventNamespaceAlreadyExists>
            bind_event_namespace_already_exists = Exceptions_namespace.new_usertype<
                obe::event::Exceptions::EventNamespaceAlreadyExists>("EventNamespaceAlreadyExists",
                sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventNamespaceAlreadyExists(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventNamespaceAlreadyExists>,
                    obe::BaseException>());
    }
    void load_class_event_namespace_not_joinable(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["event"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::EventNamespaceNotJoinable>
            bind_event_namespace_not_joinable
            = Exceptions_namespace.new_usertype<obe::event::Exceptions::EventNamespaceNotJoinable>(
                "EventNamespaceNotJoinable", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::EventNamespaceNotJoinable(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::EventNamespaceNotJoinable>,
                    obe::BaseException>());
    }
    void load_class_unknown_event(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["event"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::UnknownEvent> bind_unknown_event
            = Exceptions_namespace.new_usertype<obe::event::Exceptions::UnknownEvent>(
                "UnknownEvent", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::UnknownEvent(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::UnknownEvent>,
                    obe::BaseException>());
    }
    void load_class_unknown_event_group(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["event"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::UnknownEventGroup> bind_unknown_event_group
            = Exceptions_namespace.new_usertype<obe::event::Exceptions::UnknownEventGroup>(
                "UnknownEventGroup", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::UnknownEventGroup(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::UnknownEventGroup>,
                    obe::BaseException>());
    }
    void load_class_unknown_event_namespace(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["event"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::event::Exceptions::UnknownEventNamespace> bind_unknown_event_namespace
            = Exceptions_namespace.new_usertype<obe::event::Exceptions::UnknownEventNamespace>(
                "UnknownEventNamespace", sol::call_constructor,
                sol::constructors<obe::event::Exceptions::UnknownEventNamespace(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::event::Exceptions::UnknownEventNamespace>,
                    obe::BaseException>());
    }
};