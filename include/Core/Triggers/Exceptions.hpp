#pragma once

#include <Exception.hpp>

namespace obe::Triggers::Exceptions
{
    class CallbackCreationError : public Exception
    {
    public:
        CallbackCreationError(std::string_view triggerName,
            std::string_view environmentId, std::string_view callback,
            std::string_view error, DebugInfo info)
            : Exception("CallbackCreationError", info)
        {
            this->error("Error while creating a Trigger callback"
                        "\n     Trigger '{}'"
                        "\n     Callback '{}'"
                        "\n     Environment '{}'"
                        "\n     Lua Error : {}",
                triggerName, callback, environmentId, error);
        }
    };

    class TriggerExecutionError : public Exception
    {
    public:
        TriggerExecutionError(std::string_view triggerName,
            std::string_view environmentId, std::string_view callback,
            std::string_view error, DebugInfo info)
            : Exception("TriggerExecutionError", info)
        {
            this->error("Error while executing a Trigger callback"
                        "\n     Trigger '{}'"
                        "\n     Callback '{}'"
                        "\n     Environment '{}'"
                        "\n     Lua Error : {}",
                triggerName, callback, environmentId, error);
        }
    };

    class UnknownTrigger : public Exception
    {
    public:
        UnknownTrigger(std::string_view triggerNamespace, std::string_view triggerGroup,
            std::string_view triggerName,
            const std::vector<std::string>& existingTriggers, DebugInfo info)
            : Exception("UnknownTrigger", info)
        {
            this->error("Unable to find a Trigger named '{}' inside TriggerGroup '{}.{}'",
                triggerName, triggerNamespace, triggerGroup);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(triggerName.data(), existingTriggers, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint("Try one of the following Triggers ({}...)",
                fmt::join(suggestions, ", "));
        }
    };

    class UnknownTriggerNamespace : public Exception
    {
    public:
        UnknownTriggerNamespace(std::string_view triggerNamespace,
            const std::vector<std::string>& existingNamespaces, DebugInfo info)
            : Exception("UnknownTriggerNamespace", info)
        {
            this->error("Unable to find a TriggerNamespace named '{}'", triggerNamespace);
            std::vector<std::string> suggestions = Utils::String::sortByDistance(
                triggerNamespace.data(), existingNamespaces, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint("Try one of the following TriggerNamespaces ({}...)",
                fmt::join(suggestions, ", "));
        }
    };

    class UnknownTriggerGroup : public Exception
    {
    public:
        UnknownTriggerGroup(std::string_view triggerNamespace,
            std::string_view triggerGroup, const std::vector<std::string>& existingGroups,
            DebugInfo info)
            : Exception("UnknownTriggerGroup", info)
        {
            this->error(
                "Unable to find a TriggerGroup named '{}' inside TriggerNamespace '{}'",
                triggerGroup, triggerNamespace);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(triggerGroup.data(), existingGroups, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint("Try one of the following TriggerGroups ({}...)",
                fmt::join(suggestions, ", "));
        }
    };

    class TriggerNamespaceAlreadyExists : public Exception
    {
    public:
        TriggerNamespaceAlreadyExists(std::string_view triggerNamespace, DebugInfo info)
            : Exception("TriggerNamespaceAlreadyExists", info)
        {
            this->error("A TriggerNamespace named '{}' already exists", triggerNamespace);
            this->hint("Try creating a TriggerNamespace with a different name that is "
                       "not already taken");
        }
    };

    class TriggerGroupAlreadyExists : public Exception
    {
    public:
        TriggerGroupAlreadyExists(std::string_view triggerNamespace,
            std::string_view triggerGroup, DebugInfo info)
            : Exception("TriggerGroupAlreadyExists", info)
        {
            this->error(
                "A TriggerGroup named '{}' already exists inside TriggerNamespace '{}'",
                triggerGroup, triggerNamespace);
            this->hint("Try creating a TriggerGroup with a different name that is "
                       "not already taken");
        }
    };

    class TriggerGroupNotJoinable : public Exception
    {
    public:
        TriggerGroupNotJoinable(std::string_view triggerNamespace,
            std::string_view triggerGroup, DebugInfo info)
            : Exception("TriggerGroupNotJoinable", info)
        {
            this->error("Impossible to join TriggerGroup '{}' inside TriggerNamespace "
                        "'{}' as it is defined as non-joinable",
                triggerGroup, triggerNamespace);
            this->hint("If you want this TriggerGroup to be able to be joined, use "
                       "group.setJoinable(true) from its manager");
        }
    };
}
