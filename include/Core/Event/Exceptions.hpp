#pragma once

#include <Exception.hpp>

namespace obe::Event::Exceptions
{
    class CallbackCreationError : public Exception
    {
    public:
        CallbackCreationError(std::string_view eventName, std::string_view environmentId,
            std::string_view callback, std::string_view error, DebugInfo info)
            : Exception("CallbackCreationError", info)
        {
            this->error("Error while creating an Event callback"
                        "\n     Event '{}'"
                        "\n     Callback '{}'"
                        "\n     Environment '{}'"
                        "\n     Lua Error : {}",
                eventName, callback, environmentId, error);
        }
    };

    class EventExecutionError : public Exception
    {
    public:
        EventExecutionError(
            std::string_view eventName, std::string_view listenerId, DebugInfo info)
            : Exception("EventExecutionError", info)
        {
            this->error("Error while executing an Event callback"
                        "\n     Event '{}'"
                        "\n     Listener '{}'",
                eventName, listenerId);
        }
    };

    class UnknownEvent : public Exception
    {
    public:
        UnknownEvent(std::string_view eventGroup, std::string_view eventName,
            const std::vector<std::string>& existingEvents, DebugInfo info)
            : Exception("UnknownEvent", info)
        {
            this->error("Unable to find a Event named '{}' inside EventGroup '{}'",
                eventName, eventGroup);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(eventName.data(), existingEvents, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint(
                "Try one of the following Events ({}...)", fmt::join(suggestions, ", "));
        }
    };

    class UnknownEventNamespace : public Exception
    {
    public:
        UnknownEventNamespace(std::string_view eventNamespace,
            const std::vector<std::string>& existingNamespaces, DebugInfo info)
            : Exception("UnknownEventNamespace", info)
        {
            this->error("Unable to find a EventNamespace named '{}'", eventNamespace);
            std::vector<std::string> suggestions = Utils::String::sortByDistance(
                eventNamespace.data(), existingNamespaces, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint("Try one of the following EventNamespaces ({}...)",
                fmt::join(suggestions, ", "));
        }
    };

    class UnknownEventGroup : public Exception
    {
    public:
        UnknownEventGroup(std::string_view eventNamespace, std::string_view eventGroup,
            const std::vector<std::string>& existingGroups, DebugInfo info)
            : Exception("UnknownEventGroup", info)
        {
            this->error(
                "Unable to find an EventGroup named '{}' inside EventNamespace '{}'",
                eventGroup, eventNamespace);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(eventGroup.data(), existingGroups, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint("Try one of the following EventGroups ({}...)",
                fmt::join(suggestions, ", "));
        }
    };

    class EventNamespaceAlreadyExists : public Exception
    {
    public:
        EventNamespaceAlreadyExists(std::string_view eventNamespace, DebugInfo info)
            : Exception("EventNamespaceAlreadyExists", info)
        {
            this->error("An EventNamespace named '{}' already exists", eventNamespace);
            this->hint("Try creating a EventNamespace with a different name that is "
                       "not already taken");
        }
    };

    class EventGroupAlreadyExists : public Exception
    {
    public:
        EventGroupAlreadyExists(
            std::string_view eventNamespace, std::string_view eventGroup, DebugInfo info)
            : Exception("EventGroupAlreadyExists", info)
        {
            this->error(
                "An EventGroup named '{}' already exists inside EventNamespace '{}'",
                eventGroup, eventNamespace);
            this->hint("Try creating an EventGroup with a different name that is "
                       "not already taken");
        }
    };

    class EventAlreadyExists : public Exception
    {
    public:
        EventAlreadyExists(std::string_view eventGroupIdentifier,
            std::string_view eventName, DebugInfo info)
            : Exception("EventAlreadyExists", info)
        {
            this->error("An Event named '{}' already exists inside EventGroup '{}'",
                eventName, eventGroupIdentifier);
            this->hint("Try creating an Event with a different name that is "
                       "not already taken");
        }
    };

    class EventGroupNotJoinable : public Exception
    {
    public:
        EventGroupNotJoinable(
            std::string_view eventNamespace, std::string_view eventGroup, DebugInfo info)
            : Exception("EventGroupNotJoinable", info)
        {
            this->error("Impossible to join EventGroup '{}' inside EventNamespace "
                        "'{}' as it is defined as non-joinable",
                eventGroup, eventNamespace);
            this->hint("If you want this EventGroup to be able to be joined, use "
                       "group.setJoinable(true) from its manager");
        }
    };

    class LuaExecutionError : public Exception
    {
    public:
        LuaExecutionError(std::string_view errorMessage, DebugInfo info)
            : Exception("LuaExecutionError", info)
        {
            this->error(
                "Lua encountered an error while executing code :\n{}", errorMessage);
        }
    };
}
