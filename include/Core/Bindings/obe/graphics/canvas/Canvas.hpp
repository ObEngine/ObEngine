#pragma once

namespace sol
{
    class state_view;
};
namespace obe::graphics::canvas::bindings
{
    void load_class_bezier(sol::state_view state);
    void load_class_canvas(sol::state_view state);
    void load_class_canvas_element(sol::state_view state);
    void load_class_canvas_positionable(sol::state_view state);
    void load_class_circle(sol::state_view state);
    void load_class_line(sol::state_view state);
    void load_class_polygon(sol::state_view state);
    void load_class_rectangle(sol::state_view state);
    void load_class_text(sol::state_view state);
    void load_enum_canvas_element_type(sol::state_view state);
    void load_enum_text_horizontal_align(sol::state_view state);
    void load_enum_text_vertical_align(sol::state_view state);
};