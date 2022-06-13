#include <Bindings/obe/System/Prefixes/Prefixes.hpp>

#include <System/MountablePath.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::prefixes::Bindings
{
    void LoadGlobalObe(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        PrefixesNamespace["obe"] = obe::system::prefixes::obe;
    }
    void LoadGlobalCwd(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        PrefixesNamespace["cwd"] = obe::system::prefixes::cwd;
    }
    void LoadGlobalExe(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        PrefixesNamespace["exe"] = obe::system::prefixes::exe;
    }
    void LoadGlobalCfg(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        PrefixesNamespace["cfg"] = obe::system::prefixes::cfg;
    }
    void LoadGlobalMount(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        PrefixesNamespace["mount"] = obe::system::prefixes::mount;
    }
    void LoadGlobalExtlibs(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        PrefixesNamespace["extlibs"] = obe::system::prefixes::extlibs;
    }
    void LoadGlobalRoot(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        PrefixesNamespace["root"] = obe::system::prefixes::root;
    }
    void LoadGlobalGame(sol::state_view state)
    {
        sol::table PrefixesNamespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        PrefixesNamespace["game"] = obe::system::prefixes::game;
    }
};