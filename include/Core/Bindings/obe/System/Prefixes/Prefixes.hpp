#pragma once

namespace sol
{
    class state_view;
};
namespace obe::System::Prefixes::Bindings
{
    void LoadGlobalObe(sol::state_view state);
    void LoadGlobalCwd(sol::state_view state);
    void LoadGlobalExe(sol::state_view state);
    void LoadGlobalCfg(sol::state_view state);
    void LoadGlobalMount(sol::state_view state);
    void LoadGlobalExtlibs(sol::state_view state);
    void LoadGlobalRoot(sol::state_view state);
};