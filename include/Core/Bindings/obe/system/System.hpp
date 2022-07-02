#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::bindings
{
    void load_class_contextual_path_factory(sol::state_view state);
    void load_class_cursor(sol::state_view state);
    void load_class_cursor_model(sol::state_view state);
    void load_class_find_result(sol::state_view state);
    void load_class_mountable_path(sol::state_view state);
    void load_class_path(sol::state_view state);
    void load_class_plugin(sol::state_view state);
    void load_class_window(sol::state_view state);
    void load_enum_cursor_type(sol::state_view state);
    void load_enum_mountable_path_type(sol::state_view state);
    void load_enum_same_prefix_policy(sol::state_view state);
    void load_enum_path_type(sol::state_view state);
    void load_enum_window_context(sol::state_view state);
    void load_enum_stretch_mode(sol::state_view state);
    void load_enum_window_size(sol::state_view state);
    void load_enum_render_size(sol::state_view state);
    void load_function_split_path_and_prefix(sol::state_view state);
}; // namespace obe::system::bindings