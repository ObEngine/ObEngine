#pragma once

#include <Exception.hpp>

/**
 * \nobind
 */
namespace obe::event::Exceptions
{
    class CallbackCreationError : public Exception<CallbackCreationError>
    {
    public:
        using Exception::Exception;
        CallbackCreationError(std::string_view event_name, std::string_view environment_id,
            std::string_view callback, std::string_view error, DebugInfo info)
            : Exception(info)
        {
            this->error("Error while creating an Event callback"
                        "\n     Event '{}'"
                        "\n     Callback '{}'"
                        "\n     Environment '{}'"
                        "\n     Lua Error : {}",
                event_name, callback, environment_id, error);
        }
    };

    class EventExecutionError : public Exception<EventExecutionError>
    {
    public:
        using Exception::Exception;
        EventExecutionError(
            std::string_view event_name, std::string_view listener_id, DebugInfo info)
            : Exception(info)
        {
            this->error("Error while executing an Event callback"
                        "\n     Event '{}'"
                        "\n     Listener '{}'",
                event_name, listener_id);
        }
    };

    class UnknownEvent : public Exception<UnknownEvent>
    {
    public:
        using Exception::Exception;
        UnknownEvent(std::string_view event_group, std::string_view event_name,
            const std::vector<std::string>& existing_events, DebugInfo info)
            : Exception(info)
        {
            this->error("Unable to find a Event named '{}' inside EventGroup '{}'", event_name,
                event_group);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(event_name.data(), existing_events, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), utils::string::quote);
            this->hint("Try one of the following Events ({}...)", fmt::join(suggestions, ", "));
        }
    };

    class UnknownEventNamespace : public Exception<UnknownEventNamespace>
    {
    public:
        using Exception::Exception;
        UnknownEventNamespace(std::string_view event_namespace,
            const std::vector<std::string>& existing_namespaces, DebugInfo info)
            : Exception(info)
        {
            this->error("Unable to find a EventNamespace named '{}'", event_namespace);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(event_namespace.data(), existing_namespaces, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), utils::string::quote);
            this->hint(
                "Try one of the following EventNamespaces ({}...)", fmt::join(suggestions, ", "));
        }
    };

    class UnknownEventGroup : public Exception<UnknownEventGroup>
    {
    public:
        using Exception::Exception;
        UnknownEventGroup(std::string_view event_namespace, std::string_view event_group,
            const std::vector<std::string>& existing_groups, DebugInfo info)
            : Exception(info)
        {
            this->error("Unable to find an EventGroup named '{}' inside EventNamespace '{}'",
                event_group, event_namespace);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(event_group.data(), existing_groups, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), utils::string::quote);
            this->hint(
                "Try one of the following EventGroups ({}...)", fmt::join(suggestions, ", "));
        }
    };

    class EventNamespaceAlreadyExists : public Exception<EventNamespaceAlreadyExists>
    {
    public:
        using Exception::Exception;
        EventNamespaceAlreadyExists(std::string_view event_namespace, DebugInfo info)
            : Exception(info)
        {
            this->error("An EventNamespace named '{}' already exists", event_namespace);
            this->hint("Try creating a EventNamespace with a different name that is "
                       "not already taken");
        }
    };

    class EventGroupAlreadyExists : public Exception<EventGroupAlreadyExists>
    {
    public:
        using Exception::Exception;
        EventGroupAlreadyExists(
            std::string_view event_namespace, std::string_view event_group, DebugInfo info)
            : Exception(info)
        {
            this->error("An EventGroup named '{}' already exists inside EventNamespace '{}'",
                event_group, event_namespace);
            this->hint("Try creating an EventGroup with a different name that is "
                       "not already taken");
        }
    };

    class EventAlreadyExists : public Exception<EventAlreadyExists>
    {
    public:
        using Exception::Exception;
        EventAlreadyExists(
            std::string_view event_group_identifier, std::string_view event_name, DebugInfo info)
            : Exception(info)
        {
            this->error("An Event named '{}' already exists inside EventGroup '{}'", event_name,
                event_group_identifier);
            this->hint("Try creating an Event with a different name that is "
                       "not already taken");
        }
    };

    class EventGroupNotJoinable : public Exception<EventGroupNotJoinable>
    {
    public:
        using Exception::Exception;
        EventGroupNotJoinable(
            std::string_view event_namespace, std::string_view event_group, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to join EventGroup '{}' inside EventNamespace "
                        "'{}' as it is defined as non-joinable",
                event_group, event_namespace);
            this->hint("If you want this EventGroup to be able to be joined, use "
                       "group.set_joinable(true) from its manager");
        }
    };

    class EventNamespaceNotJoinable : public Exception<EventNamespaceNotJoinable>
    {
    public:
        using Exception::Exception;
        EventNamespaceNotJoinable(std::string_view event_namespace, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to join EventNamespace "
                        "'{}' as it is defined as non-joinable",
                event_namespace);
            this->hint("If you want this EventNamespace to be able to be joined, use "
                       "event_namespace.set_joinable(true) from its manager");
        }
    };
} // namespace obe::event::Exceptions
