#pragma once

namespace sol
{
    class state_view;
};
namespace obe::transform::bindings
{
    void load_class_matrix2_d(sol::state_view state);
    void load_class_movable(sol::state_view state);
    void load_class_polygon(sol::state_view state);
    void load_class_polygon_point(sol::state_view state);
    void load_class_polygon_segment(sol::state_view state);
    void load_class_rect(sol::state_view state);
    void load_class_referential(sol::state_view state);
    void load_class_unit_based_object(sol::state_view state);
    void load_class_unit_vector(sol::state_view state);
    void load_class_screen_struct(sol::state_view state);
    void load_class_view_struct(sol::state_view state);
    void load_enum_referential_conversion_type(sol::state_view state);
    void load_enum_flip_axis(sol::state_view state);
    void load_enum_units(sol::state_view state);
    void load_enum_relative_position_from(sol::state_view state);
}; // namespace obe::transform::bindings