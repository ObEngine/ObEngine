#pragma once

namespace sol
{
    class state_view;
};
namespace obe::tiles::bindings
{
    void load_class_animated_tile(sol::state_view state);
    void load_class_tile_layer(sol::state_view state);
    void load_class_tile_scene(sol::state_view state);
    void load_class_tileset(sol::state_view state);
    void load_class_tileset_collection(sol::state_view state);
    void load_class_texture_quads_index(sol::state_view state);
    void load_class_tile_info(sol::state_view state);
    void load_function_get_tile_info(sol::state_view state);
    void load_function_strip_tile_flags(sol::state_view state);
    void load_function_apply_texture_quads_transforms(sol::state_view state);
}; // namespace obe::tiles::bindings