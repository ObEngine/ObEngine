#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::project::Prefixes::bindings
{
    void load_global_objects(sol::state_view state);
    void load_global_scenes(sol::state_view state);
};