#include <Bindings/obe/System/Priorities/Priorities.hpp>

#include <System/MountablePath.hpp>

#include <Bindings/Config.hpp>

namespace obe::System::Priorities::Bindings
{
    void LoadGlobalHigh(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["System"]["Priorities"].get<sol::table>();
        PrioritiesNamespace["high"] = obe::System::Priorities::high;
    }
    void LoadGlobalProjectmount(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["System"]["Priorities"].get<sol::table>();
        PrioritiesNamespace["projectmount"] = obe::System::Priorities::projectmount;
    }
    void LoadGlobalProject(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["System"]["Priorities"].get<sol::table>();
        PrioritiesNamespace["project"] = obe::System::Priorities::project;
    }
    void LoadGlobalMount(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["System"]["Priorities"].get<sol::table>();
        PrioritiesNamespace["mount"] = obe::System::Priorities::mount;
    }
    void LoadGlobalDefaults(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["System"]["Priorities"].get<sol::table>();
        PrioritiesNamespace["defaults"] = obe::System::Priorities::defaults;
    }
    void LoadGlobalLow(sol::state_view state)
    {
        sol::table PrioritiesNamespace = state["obe"]["System"]["Priorities"].get<sol::table>();
        PrioritiesNamespace["low"] = obe::System::Priorities::low;
    }
};