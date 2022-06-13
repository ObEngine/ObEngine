#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::priorities::Bindings
{
    void LoadGlobalHigh(sol::state_view state);
    void LoadGlobalProjectmount(sol::state_view state);
    void LoadGlobalProject(sol::state_view state);
    void LoadGlobalMount(sol::state_view state);
    void LoadGlobalDefaults(sol::state_view state);
    void LoadGlobalLow(sol::state_view state);
};