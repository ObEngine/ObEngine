#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Triggers::Exceptions::Bindings
{
    void LoadClassCallbackCreationError(sol::state_view state);
    void LoadClassTriggerExecutionError(sol::state_view state);
    void LoadClassTriggerGroupAlreadyExists(sol::state_view state);
    void LoadClassTriggerGroupNotJoinable(sol::state_view state);
    void LoadClassTriggerNamespaceAlreadyExists(sol::state_view state);
    void LoadClassUnknownTrigger(sol::state_view state);
    void LoadClassUnknownTriggerGroup(sol::state_view state);
    void LoadClassUnknownTriggerNamespace(sol::state_view state);
};