#pragma once

namespace sol
{
    class state_view;
};
namespace obe::graphics::utils::bindings
{
    void load_class_draw_polygon_options(sol::state_view state);
    void load_function_draw_point(sol::state_view state);
    void load_function_draw_line(sol::state_view state);
    void load_function_draw_polygon(sol::state_view state);
};