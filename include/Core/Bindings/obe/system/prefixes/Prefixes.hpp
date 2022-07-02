#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::prefixes::bindings
{
    void load_global_obe(sol::state_view state);
    void load_global_cwd(sol::state_view state);
    void load_global_exe(sol::state_view state);
    void load_global_cfg(sol::state_view state);
    void load_global_mount(sol::state_view state);
    void load_global_extlibs(sol::state_view state);
    void load_global_root(sol::state_view state);
    void load_global_game(sol::state_view state);
}; // namespace obe::system::prefixes::bindings