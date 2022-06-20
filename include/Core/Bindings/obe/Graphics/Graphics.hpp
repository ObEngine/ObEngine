#pragma once

namespace sol
{
    class state_view;
};
namespace obe::graphics::bindings
{
    void load_class_color(sol::state_view state);
    void load_class_editor_sprite(sol::state_view state);
    void load_class_font(sol::state_view state);
    void load_class_position_transformer(sol::state_view state);
    void load_class_render_target(sol::state_view state);
    void load_class_renderable(sol::state_view state);
    void load_class_rich_text(sol::state_view state);
    void load_class_shader(sol::state_view state);
    void load_class_sprite(sol::state_view state);
    void load_class_sprite_handle_point(sol::state_view state);
    void load_class_svg_texture(sol::state_view state);
    void load_class_text(sol::state_view state);
    void load_class_texture(sol::state_view state);
    void load_class_hsv(sol::state_view state);
    void load_enum_color_type(sol::state_view state);
    void load_enum_sprite_handle_point_type(sol::state_view state);
    void load_function_init_position_transformers(sol::state_view state);
    void load_function_make_null_texture(sol::state_view state);
    void load_global_transformers(sol::state_view state);
    void load_global_parallax(sol::state_view state);
    void load_global_camera(sol::state_view state);
    void load_global_position(sol::state_view state);
};