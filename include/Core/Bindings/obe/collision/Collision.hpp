#pragma once

namespace sol
{
    class state_view;
};
namespace obe::collision::bindings
{
    void load_class_collision_data(sol::state_view state);
    void load_class_polygonal_collider(sol::state_view state);
    void load_class_trajectory(sol::state_view state);
    void load_class_trajectory_node(sol::state_view state);
    void load_enum_collider_tag_type(sol::state_view state);
}; // namespace obe::collision::bindings