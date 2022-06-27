#pragma once

namespace sol
{
    class state_view;
};
namespace obe::scene::Exceptions::bindings
{
    void load_class_child_not_in_scene_node(sol::state_view state);
    void load_class_game_object_already_exists(sol::state_view state);
    void load_class_invalid_scene_file(sol::state_view state);
    void load_class_missing_scene_file_block(sol::state_view state);
    void load_class_scene_on_load_callback_error(sol::state_view state);
    void load_class_scene_script_loading_error(sol::state_view state);
    void load_class_unknown_collider(sol::state_view state);
    void load_class_unknown_game_object(sol::state_view state);
    void load_class_unknown_sprite(sol::state_view state);
};