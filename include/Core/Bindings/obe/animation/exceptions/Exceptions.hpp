#pragma once

namespace sol
{
    class state_view;
};
namespace obe::animation::exceptions::bindings
{
    void load_class_animation_group_texture_index_overflow(sol::state_view state);
    void load_class_animation_texture_index_overflow(sol::state_view state);
    void load_class_invalid_animation_file(sol::state_view state);
    void load_class_invalid_easing_function(sol::state_view state);
    void load_class_no_selected_animation(sol::state_view state);
    void load_class_no_selected_animation_group(sol::state_view state);
    void load_class_unknown_animation(sol::state_view state);
    void load_class_unknown_animation_group(sol::state_view state);
    void load_class_unknown_easing_from_enum(sol::state_view state);
    void load_class_unknown_easing_from_string(sol::state_view state);
};