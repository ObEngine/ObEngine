#include <Bindings/obe/Graphics/Utils/Utils.hpp>

#include <Graphics/DrawUtils.hpp>
#include <Graphics/RenderTarget.hpp>

#include <Bindings/Config.hpp>

namespace obe::Graphics::Utils::Bindings
{
    void LoadClassDrawPolygonOptions(sol::state_view state)
    {
        sol::table UtilsNamespace = state["obe"]["Graphics"]["Utils"].get<sol::table>();
        sol::usertype<obe::Graphics::Utils::DrawPolygonOptions> bindDrawPolygonOptions
            = UtilsNamespace.new_usertype<obe::Graphics::Utils::DrawPolygonOptions>(
                "DrawPolygonOptions", sol::call_constructor, sol::default_constructor);
        bindDrawPolygonOptions["lines"] = &obe::Graphics::Utils::DrawPolygonOptions::lines;
        bindDrawPolygonOptions["points"] = &obe::Graphics::Utils::DrawPolygonOptions::points;
        bindDrawPolygonOptions["radius"] = &obe::Graphics::Utils::DrawPolygonOptions::radius;
        bindDrawPolygonOptions["lineColor"] = &obe::Graphics::Utils::DrawPolygonOptions::lineColor;
        bindDrawPolygonOptions["pointColor"]
            = &obe::Graphics::Utils::DrawPolygonOptions::pointColor;
        bindDrawPolygonOptions["specificLineColor"]
            = &obe::Graphics::Utils::DrawPolygonOptions::specificLineColor;
        bindDrawPolygonOptions["specificPointColor"]
            = &obe::Graphics::Utils::DrawPolygonOptions::specificPointColor;
    }
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