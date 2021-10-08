#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Event::Bindings
{
    void LoadClassCallbackProfiler(sol::state_view state);
    void LoadClassCallbackScheduler(sol::state_view state);
    void LoadClassEventBase(sol::state_view state);
    void LoadClassEventGroup(sol::state_view state);
    void LoadClassEventGroupView(sol::state_view state);
    void LoadClassEventManager(sol::state_view state);
    void LoadClassEventNamespace(sol::state_view state);
    void LoadClassEventNamespaceView(sol::state_view state);
    void LoadClassLuaEventListener(sol::state_view state);
    void LoadClassScopeProfiler(sol::state_view state);
    void LoadEnumCallbackSchedulerState(sol::state_view state);
    void LoadEnumListenerChangeState(sol::state_view state);
};
