#include <Bindings/obe/system/priorities/Priorities.hpp>

#include <System/MountablePath.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::priorities::bindings
{
    void load_global_high(sol::state_view state)
    {
        sol::table priorities_namespace = state["obe"]["system"]["priorities"].get<sol::table>();
        priorities_namespace["high"] = obe::system::priorities::high;
    }
    void load_global_projectmount(sol::state_view state)
    {
        sol::table priorities_namespace = state["obe"]["system"]["priorities"].get<sol::table>();
        priorities_namespace["projectmount"] = obe::system::priorities::projectmount;
    }
    void load_global_project(sol::state_view state)
    {
        sol::table priorities_namespace = state["obe"]["system"]["priorities"].get<sol::table>();
        priorities_namespace["project"] = obe::system::priorities::project;
    }
    void load_global_mount(sol::state_view state)
    {
        sol::table priorities_namespace = state["obe"]["system"]["priorities"].get<sol::table>();
        priorities_namespace["mount"] = obe::system::priorities::mount;
    }
    void load_global_defaults(sol::state_view state)
    {
        sol::table priorities_namespace = state["obe"]["system"]["priorities"].get<sol::table>();
        priorities_namespace["defaults"] = obe::system::priorities::defaults;
    }
    void load_global_low(sol::state_view state)
    {
        sol::table priorities_namespace = state["obe"]["system"]["priorities"].get<sol::table>();
        priorities_namespace["low"] = obe::system::priorities::low;
    }
};