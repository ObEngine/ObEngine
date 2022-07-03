#pragma once

namespace sol
{
    class state_view;
};
namespace obe::animation::schemas::bindings
{
    void load_global_animation_schema_str(sol::state_view state);
    void load_global_animation_schema(sol::state_view state);
};