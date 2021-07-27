#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Event::Exceptions::Bindings
{
    void LoadClassCallbackCreationError(sol::state_view state);
    void LoadClassEventAlreadyExists(sol::state_view state);
    void LoadClassEventExecutionError(sol::state_view state);
    void LoadClassEventGroupAlreadyExists(sol::state_view state);
    void LoadClassEventGroupNotJoinable(sol::state_view state);
    void LoadClassEventNamespaceAlreadyExists(sol::state_view state);
    void LoadClassUnknownEvent(sol::state_view state);
    void LoadClassUnknownEventGroup(sol::state_view state);
    void LoadClassUnknownEventNamespace(sol::state_view state);
};