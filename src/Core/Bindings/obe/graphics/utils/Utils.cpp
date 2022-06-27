#include <Bindings/obe/graphics/utils/Utils.hpp>

#include <Graphics/DrawUtils.hpp>
#include <Graphics/RenderTarget.hpp>

#include <Bindings/Config.hpp>

namespace obe::graphics::utils::bindings
{
    void load_class_draw_polygon_options(sol::state_view state)
    {
        sol::table utils_namespace = state["obe"]["graphics"]["utils"].get<sol::table>();
        sol::usertype<obe::graphics::utils::DrawPolygonOptions> bind_draw_polygon_options
            = utils_namespace.new_usertype<obe::graphics::utils::DrawPolygonOptions>(
                "DrawPolygonOptions", sol::call_constructor, sol::default_constructor);
        bind_draw_polygon_options["lines"] = &obe::graphics::utils::DrawPolygonOptions::lines;
        bind_draw_polygon_options["points"] = &obe::graphics::utils::DrawPolygonOptions::points;
        bind_draw_polygon_options["radius"] = &obe::graphics::utils::DrawPolygonOptions::radius;
        bind_draw_polygon_options["line_color"]
            = &obe::graphics::utils::DrawPolygonOptions::line_color;
        bind_draw_polygon_options["point_color"]
            = &obe::graphics::utils::DrawPolygonOptions::point_color;
        bind_draw_polygon_options["specific_line_color"]
            = &obe::graphics::utils::DrawPolygonOptions::specific_line_color;
        bind_draw_polygon_options["specific_point_color"]
            = &obe::graphics::utils::DrawPolygonOptions::specific_point_color;
    }
    void load_function_draw_point(sol::state_view state)
    {
        sol::table utils_namespace = state["obe"]["graphics"]["utils"].get<sol::table>();
        utils_namespace.set_function("draw_point", &obe::graphics::utils::draw_point);
    }
    void load_function_draw_line(sol::state_view state)
    {
        sol::table utils_namespace = state["obe"]["graphics"]["utils"].get<sol::table>();
        utils_namespace.set_function("draw_line", &obe::graphics::utils::draw_line);
    }
    void load_function_draw_polygon(sol::state_view state)
    {
        sol::table utils_namespace = state["obe"]["graphics"]["utils"].get<sol::table>();
        utils_namespace.set_function("draw_polygon", &obe::graphics::utils::draw_polygon);
    }
};