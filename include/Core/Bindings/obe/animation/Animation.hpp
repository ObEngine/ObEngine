#pragma once

namespace sol
{
    class state_view;
};
namespace obe::animation::bindings
{
    void load_class_animation(sol::state_view state);
    void load_class_animation_group(sol::state_view state);
    void load_class_animation_state(sol::state_view state);
    void load_class_animator(sol::state_view state);
    void load_class_animator_state(sol::state_view state);
    void load_class_color_tweening(sol::state_view state);
    void load_class_unit_vector_tweening(sol::state_view state);
    void load_class_rect_tweening(sol::state_view state);
    void load_class_trajectory_tweening(sol::state_view state);
    void load_class_int_tweening(sol::state_view state);
    void load_class_double_tweening(sol::state_view state);
    void load_enum_animation_play_mode(sol::state_view state);
    void load_enum_animation_command(sol::state_view state);
    void load_enum_animation_status(sol::state_view state);
    void load_enum_animator_target_scale_mode(sol::state_view state);
    void load_function_template_specialization_exists_impl(sol::state_view state);
    void load_function_tween(sol::state_view state);
};