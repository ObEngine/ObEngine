#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::project::Prefixes::Bindings
{
    void LoadGlobalObjects(sol::state_view state);
    void LoadGlobalScenes(sol::state_view state);
};