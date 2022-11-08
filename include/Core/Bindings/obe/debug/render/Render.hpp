#pragma once

namespace sol
{
    class state_view;
};
namespace obe::debug::render::bindings
{
    void load_class_collider_render_options(sol::state_view state);
    void load_function_draw_polygon(sol::state_view state);
    void load_function_draw_collider(sol::state_view state);
};