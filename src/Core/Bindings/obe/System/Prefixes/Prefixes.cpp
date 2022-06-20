#include <Bindings/obe/system/prefixes/Prefixes.hpp>

#include <System/MountablePath.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::prefixes::bindings
{
    void load_global_obe(sol::state_view state)
    {
        sol::table prefixes_namespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        prefixes_namespace["obe"] = obe::system::prefixes::obe;
    }
    void load_global_cwd(sol::state_view state)
    {
        sol::table prefixes_namespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        prefixes_namespace["cwd"] = obe::system::prefixes::cwd;
    }
    void load_global_exe(sol::state_view state)
    {
        sol::table prefixes_namespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        prefixes_namespace["exe"] = obe::system::prefixes::exe;
    }
    void load_global_cfg(sol::state_view state)
    {
        sol::table prefixes_namespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        prefixes_namespace["cfg"] = obe::system::prefixes::cfg;
    }
    void load_global_mount(sol::state_view state)
    {
        sol::table prefixes_namespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        prefixes_namespace["mount"] = obe::system::prefixes::mount;
    }
    void load_global_extlibs(sol::state_view state)
    {
        sol::table prefixes_namespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        prefixes_namespace["extlibs"] = obe::system::prefixes::extlibs;
    }
    void load_global_root(sol::state_view state)
    {
        sol::table prefixes_namespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        prefixes_namespace["root"] = obe::system::prefixes::root;
    }
    void load_global_game(sol::state_view state)
    {
        sol::table prefixes_namespace = state["obe"]["system"]["prefixes"].get<sol::table>();
        prefixes_namespace["game"] = obe::system::prefixes::game;
    }
};