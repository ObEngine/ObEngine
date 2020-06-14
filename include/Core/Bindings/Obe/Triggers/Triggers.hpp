#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Triggers::Bindings
{
    void LoadClassCallbackScheduler(sol::state_view state);
    void LoadClassTrigger(sol::state_view state);
    void LoadClassTriggerEnv(sol::state_view state);
    void LoadClassTriggerGroup(sol::state_view state);
    void LoadClassTriggerManager(sol::state_view state);
    void LoadEnumCallbackSchedulerState(sol::state_view state);
};