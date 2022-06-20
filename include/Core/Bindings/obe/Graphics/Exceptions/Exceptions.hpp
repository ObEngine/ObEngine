#pragma once

namespace sol
{
    class state_view;
};
namespace obe::graphics::exceptions::bindings
{
    void load_class_canvas_element_already_exists(sol::state_view state);
    void load_class_image_file_not_found(sol::state_view state);
    void load_class_invalid_color_name(sol::state_view state);
    void load_class_invalid_hex_format(sol::state_view state);
    void load_class_invalid_hsv_format(sol::state_view state);
    void load_class_invalid_rgb_format(sol::state_view state);
    void load_class_invalid_sprite_color_type(sol::state_view state);
    void load_class_read_only_texture(sol::state_view state);
};