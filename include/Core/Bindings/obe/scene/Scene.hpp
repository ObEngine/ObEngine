#pragma once

namespace sol
{
    class state_view;
};
namespace obe::scene::bindings
{
    void load_class_camera(sol::state_view state);
    void load_class_scene(sol::state_view state);
    void load_class_scene_node(sol::state_view state);
    void load_class_scene_render_options(sol::state_view state);
};