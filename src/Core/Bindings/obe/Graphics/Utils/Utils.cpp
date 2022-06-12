#include <Bindings/obe/Graphics/Utils/Utils.hpp>

#include <Graphics/DrawUtils.hpp>
#include <Graphics/RenderTarget.hpp>

#include <Bindings/Config.hpp>

namespace obe::graphics::utils::Bindings
{
    void LoadClassDrawPolygonOptions(sol::state_view state)
    {
        sol::table UtilsNamespace = state["obe"]["graphics"]["utils"].get<sol::table>();
        sol::usertype<obe::graphics::utils::DrawPolygonOptions> bindDrawPolygonOptions
            = UtilsNamespace.new_usertype<obe::graphics::utils::DrawPolygonOptions>(
                "DrawPolygonOptions", sol::call_constructor, sol::default_constructor);
        bindDrawPolygonOptions["lines"] = &obe::graphics::utils::DrawPolygonOptions::lines;
        bindDrawPolygonOptions["points"] = &obe::graphics::utils::DrawPolygonOptions::points;
        bindDrawPolygonOptions["radius"] = &obe::graphics::utils::DrawPolygonOptions::radius;
        bindDrawPolygonOptions["line_color"] = &obe::graphics::utils::DrawPolygonOptions::line_color;
        bindDrawPolygonOptions["point_color"]
            = &obe::graphics::utils::DrawPolygonOptions::point_color;
        bindDrawPolygonOptions["specific_line_color"]
            = &obe::graphics::utils::DrawPolygonOptions::specific_line_color;
        bindDrawPolygonOptions["specific_point_color"]
            = &obe::graphics::utils::DrawPolygonOptions::specific_point_color;
    }
    void LoadFunctionDrawPoint(sol::state_view state)
    {
        sol::table UtilsNamespace = state["obe"]["graphics"]["utils"].get<sol::table>();
        UtilsNamespace.set_function("draw_point", &obe::graphics::utils::draw_point);
    }
    void LoadFunctionDrawLine(sol::state_view state)
    {
        sol::table UtilsNamespace = state["obe"]["graphics"]["utils"].get<sol::table>();
        UtilsNamespace.set_function("draw_line", &obe::graphics::utils::draw_line);
    }
    void LoadFunctionDrawPolygon(sol::state_view state)
    {
        sol::table UtilsNamespace = state["obe"]["graphics"]["utils"].get<sol::table>();
        UtilsNamespace.set_function("draw_polygon", &obe::graphics::utils::draw_polygon);
    }
};