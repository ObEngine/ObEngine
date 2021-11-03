#include <Bindings/obe/System/Prefixes/Prefixes.hpp>

#include <System/MountablePath.hpp>

#include <Bindings/Config.hpp>

namespace obe::System::Prefixes::Bindings
{
    void LoadGlobalObe(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["System"]["Prefixes"].get<sol::table>();
        PrefixesNamespace["obe"] = obe::System::Prefixes::obe;
    }
    void LoadGlobalCwd(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["System"]["Prefixes"].get<sol::table>();
        PrefixesNamespace["cwd"] = obe::System::Prefixes::cwd;
    }
    void LoadGlobalExe(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["System"]["Prefixes"].get<sol::table>();
        PrefixesNamespace["exe"] = obe::System::Prefixes::exe;
    }
    void LoadGlobalCfg(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["System"]["Prefixes"].get<sol::table>();
        PrefixesNamespace["cfg"] = obe::System::Prefixes::cfg;
    }
    void LoadGlobalMount(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["System"]["Prefixes"].get<sol::table>();
        PrefixesNamespace["mount"] = obe::System::Prefixes::mount;
    }
    void LoadGlobalExtlibs(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["System"]["Prefixes"].get<sol::table>();
        PrefixesNamespace["extlibs"] = obe::System::Prefixes::extlibs;
    }
    void LoadGlobalRoot(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["System"]["Prefixes"].get<sol::table>();
        PrefixesNamespace["root"] = obe::System::Prefixes::root;
    }
};