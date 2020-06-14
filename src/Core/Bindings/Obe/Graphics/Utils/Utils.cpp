#include <Bindings/obe/Graphics/Utils/Utils.hpp>

#include <Graphics/DrawUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::Graphics::Utils::Bindings
{
    void LoadFunctionDrawPoint(sol::state_view state)
    {
        sol::table UtilsNamespace = state["obe"]["Graphics"]["Utils"].get<sol::table>();
        UtilsNamespace.set_function("drawPoint", obe::Graphics::Utils::drawPoint);
    }
    void LoadFunctionDrawLine(sol::state_view state)
    {
        sol::table UtilsNamespace = state["obe"]["Graphics"]["Utils"].get<sol::table>();
        UtilsNamespace.set_function("drawLine", obe::Graphics::Utils::drawLine);
    }
    void LoadFunctionDrawPolygon(sol::state_view state)
    {
        sol::table UtilsNamespace = state["obe"]["Graphics"]["Utils"].get<sol::table>();
        UtilsNamespace.set_function("drawPolygon", obe::Graphics::Utils::drawPolygon);
    }
};