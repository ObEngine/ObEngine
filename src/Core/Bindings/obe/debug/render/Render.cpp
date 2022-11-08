#include <Bindings/obe/debug/render/Render.hpp>

#include <Debug/Render.hpp>

#include <Bindings/Config.hpp>

namespace obe::debug::render::bindings
{
    void load_class_collider_render_options(sol::state_view state)
    {
        sol::table render_namespace = state["obe"]["debug"]["render"].get<sol::table>();
        sol::usertype<obe::debug::render::ColliderRenderOptions> bind_collider_render_options
            = render_namespace.new_usertype<obe::debug::render::ColliderRenderOptions>(
                "ColliderRenderOptions", sol::call_constructor, sol::default_constructor);
        bind_collider_render_options["color"] = &obe::debug::render::ColliderRenderOptions::color;
    }
    void load_function_draw_polygon(sol::state_view state)
    {
        sol::table render_namespace = state["obe"]["debug"]["render"].get<sol::table>();
        render_namespace.set_function("draw_polygon", &obe::debug::render::draw_polygon);
    }
    void load_function_draw_collider(sol::state_view state)
    {
        sol::table render_namespace = state["obe"]["debug"]["render"].get<sol::table>();
        render_namespace.set_function("draw_collider", &obe::debug::render::draw_collider);
    }
};