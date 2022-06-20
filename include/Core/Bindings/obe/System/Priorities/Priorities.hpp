#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::priorities::bindings
{
    void load_global_high(sol::state_view state);
    void load_global_projectmount(sol::state_view state);
    void load_global_project(sol::state_view state);
    void load_global_mount(sol::state_view state);
    void load_global_defaults(sol::state_view state);
    void load_global_low(sol::state_view state);
};