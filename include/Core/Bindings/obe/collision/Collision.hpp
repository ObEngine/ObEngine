#pragma once

namespace sol
{
    class state_view;
};
namespace obe::collision::bindings
{
    void load_class_capsule_collider(sol::state_view state);
    void load_class_circle_collider(sol::state_view state);
    void load_class_collider(sol::state_view state);
    void load_class_collider_component(sol::state_view state);
    void load_class_collision_data(sol::state_view state);
    void load_class_collision_space(sol::state_view state);
    void load_class_complex_polygon_collider(sol::state_view state);
    void load_class_polygon_collider(sol::state_view state);
    void load_class_quadtree(sol::state_view state);
    void load_class_rectangle_collider(sol::state_view state);
    void load_class_trajectory(sol::state_view state);
    void load_class_trajectory_node(sol::state_view state);
    void load_class_collision_rejection_pair(sol::state_view state);
    void load_enum_collider_type(sol::state_view state);
    void load_function_collider_type_to_c2type(sol::state_view state);
};