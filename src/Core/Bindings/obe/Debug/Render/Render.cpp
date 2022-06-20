#include <Bindings/obe/debug/render/Render.hpp>

#include <Debug/Render.hpp>

#include <Bindings/Config.hpp>

namespace obe::debug::render::bindings
{
    void load_function_draw_polygon(sol::state_view state)
    {
        sol::table render_namespace = state["obe"]["debug"]["render"].get<sol::table>();
        render_namespace.set_function("draw_polygon", &obe::debug::render::draw_polygon);
    }
};