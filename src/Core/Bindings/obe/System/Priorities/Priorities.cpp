#include <Bindings/obe/System/Priorities/Priorities.hpp>

#include <System/MountablePath.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::priorities::Bindings
{
    void LoadGlobalHigh(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["system"]["priorities"].get<sol::table>();
        PrioritiesNamespace["high"] = obe::system::priorities::high;
    }
    void LoadGlobalProjectmount(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["system"]["priorities"].get<sol::table>();
        PrioritiesNamespace["projectmount"] = obe::system::priorities::projectmount;
    }
    void LoadGlobalProject(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["system"]["priorities"].get<sol::table>();
        PrioritiesNamespace["project"] = obe::system::priorities::project;
    }
    void LoadGlobalMount(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["system"]["priorities"].get<sol::table>();
        PrioritiesNamespace["mount"] = obe::system::priorities::mount;
    }
    void LoadGlobalDefaults(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["system"]["priorities"].get<sol::table>();
        PrioritiesNamespace["defaults"] = obe::system::priorities::defaults;
    }
    void LoadGlobalLow(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["system"]["priorities"].get<sol::table>();
        PrioritiesNamespace["low"] = obe::system::priorities::low;
    }
};