#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Time::Bindings
{
    void LoadClassChronometer(sol::state_view state);
    void LoadClassFramerateCounter(sol::state_view state);
    void LoadClassFramerateManager(sol::state_view state);
    void LoadFunctionEpoch(sol::state_view state);
    void LoadGlobalSeconds(sol::state_view state);
    void LoadGlobalMilliseconds(sol::state_view state);
    void LoadGlobalMicroseconds(sol::state_view state);
    void LoadGlobalMinutes(sol::state_view state);
    void LoadGlobalHours(sol::state_view state);
    void LoadGlobalDays(sol::state_view state);
    void LoadGlobalWeeks(sol::state_view state);
};