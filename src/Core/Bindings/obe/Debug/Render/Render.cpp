#include <Bindings/obe/Debug/Render/Render.hpp>

#include <Debug/Render.hpp>

#include <Bindings/Config.hpp>

namespace obe::debug::render::Bindings
{
    void LoadFunctionDrawPolygon(sol::state_view state)
    {
        sol::table RenderNamespace = state["obe"]["debug"]["render"].get<sol::table>();
        RenderNamespace.set_function("draw_polygon", &obe::debug::render::draw_polygon);
    }
};