#include <Bindings/obe/Debug/Render/Render.hpp>

#include <Debug/Render.hpp>

#include <Bindings/Config.hpp>

namespace obe::Debug::Render::Bindings
{
    void LoadFunctionDrawPolygon(sol::state_view state)
    {
        sol::table RenderNamespace = state["obe"]["Debug"]["Render"].get<sol::table>();
        RenderNamespace.set_function("drawPolygon", obe::Debug::Render::drawPolygon);
    }
};