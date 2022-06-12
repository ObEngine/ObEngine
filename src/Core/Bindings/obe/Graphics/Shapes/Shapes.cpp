#include <Bindings/obe/Graphics/Shapes/Shapes.hpp>

#include <Graphics/Shapes.hpp>

#include <Bindings/Config.hpp>

namespace obe::graphics::shapes::Bindings
{
    void LoadClassCircle(sol::state_view state)
    {
        sol::table ShapesNamespace = state["obe"]["graphics"]["shapes"].get<sol::table>();
        sol::usertype<obe::graphics::shapes::Circle> bindCircle
            = ShapesNamespace.new_usertype<obe::graphics::shapes::Circle>("Circle",
                sol::call_constructor,
                sol::constructors<obe::graphics::shapes::Circle(),
                    obe::graphics::shapes::Circle(const sf::CircleShape&),
                    obe::graphics::shapes::Circle(const obe::graphics::shapes::Circle&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::shapes::Shape<obe::graphics::shapes::Circle>>());
        bindCircle["set_texture"] = &obe::graphics::shapes::Circle::set_texture;
        bindCircle["set_texture_rect"] = &obe::graphics::shapes::Circle::set_texture_rect;
        bindCircle["set_position"] = &obe::graphics::shapes::Circle::set_position;
        bindCircle["set_fill_color"] = &obe::graphics::shapes::Circle::set_fill_color;
        bindCircle["set_outline_color"] = &obe::graphics::shapes::Circle::set_outline_color;
        bindCircle["set_outline_thickness"] = &obe::graphics::shapes::Circle::set_outline_thickness;
        bindCircle["get_fill_color"] = &obe::graphics::shapes::Circle::get_fill_color;
        bindCircle["get_outline_color"] = &obe::graphics::shapes::Circle::get_outline_color;
        bindCircle["get_outline_thickness"] = &obe::graphics::shapes::Circle::get_outline_thickness;
        bindCircle["get_point_count"] = &obe::graphics::shapes::Circle::get_point_count;
        bindCircle["get_point"] = &obe::graphics::shapes::Circle::get_point;
        bindCircle["get_local_bounds"] = &obe::graphics::shapes::Circle::get_local_bounds;
        bindCircle["get_global_bounds"] = &obe::graphics::shapes::Circle::get_global_bounds;
        bindCircle["set_rotation"] = &obe::graphics::shapes::Circle::set_rotation;
        bindCircle["set_scale"] = &obe::graphics::shapes::Circle::set_scale;
        bindCircle["set_origin"] = &obe::graphics::shapes::Circle::set_origin;
        bindCircle["get_position"] = &obe::graphics::shapes::Circle::get_position;
        bindCircle["get_rotation"] = &obe::graphics::shapes::Circle::get_rotation;
        bindCircle["get_scale"] = &obe::graphics::shapes::Circle::get_scale;
        bindCircle["get_origin"] = &obe::graphics::shapes::Circle::get_origin;
        bindCircle["move"] = &obe::graphics::shapes::Circle::move;
        bindCircle["rotate"] = &obe::graphics::shapes::Circle::rotate;
        bindCircle["scale"] = &obe::graphics::shapes::Circle::scale;
        bindCircle["draw"] = &obe::graphics::shapes::Circle::draw;
        bindCircle["set_radius"] = &obe::graphics::shapes::Circle::set_radius;
        bindCircle["get_radius"] = &obe::graphics::shapes::Circle::get_radius;
        bindCircle["shape"] = &obe::graphics::shapes::Circle::shape;
    }
    void LoadClassPolygon(sol::state_view state)
    {
        sol::table ShapesNamespace = state["obe"]["graphics"]["shapes"].get<sol::table>();
        sol::usertype<obe::graphics::shapes::Polygon> bindPolygon
            = ShapesNamespace.new_usertype<obe::graphics::shapes::Polygon>("Polygon",
                sol::call_constructor,
                sol::constructors<obe::graphics::shapes::Polygon(),
                    obe::graphics::shapes::Polygon(const sf::ConvexShape&),
                    obe::graphics::shapes::Polygon(const obe::graphics::shapes::Polygon&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::shapes::Shape<obe::graphics::shapes::Polygon>>());
        bindPolygon["set_texture"] = &obe::graphics::shapes::Polygon::set_texture;
        bindPolygon["set_texture_rect"] = &obe::graphics::shapes::Polygon::set_texture_rect;
        bindPolygon["set_position"] = &obe::graphics::shapes::Polygon::set_position;
        bindPolygon["set_fill_color"] = &obe::graphics::shapes::Polygon::set_fill_color;
        bindPolygon["set_outline_color"] = &obe::graphics::shapes::Polygon::set_outline_color;
        bindPolygon["set_outline_thickness"] = &obe::graphics::shapes::Polygon::set_outline_thickness;
        bindPolygon["get_fill_color"] = &obe::graphics::shapes::Polygon::get_fill_color;
        bindPolygon["get_outline_color"] = &obe::graphics::shapes::Polygon::get_outline_color;
        bindPolygon["get_outline_thickness"] = &obe::graphics::shapes::Polygon::get_outline_thickness;
        bindPolygon["get_point_count"] = &obe::graphics::shapes::Polygon::get_point_count;
        bindPolygon["get_point"] = &obe::graphics::shapes::Polygon::get_point;
        bindPolygon["get_local_bounds"] = &obe::graphics::shapes::Polygon::get_local_bounds;
        bindPolygon["get_global_bounds"] = &obe::graphics::shapes::Polygon::get_global_bounds;
        bindPolygon["set_rotation"] = &obe::graphics::shapes::Polygon::set_rotation;
        bindPolygon["set_scale"] = &obe::graphics::shapes::Polygon::set_scale;
        bindPolygon["set_origin"] = &obe::graphics::shapes::Polygon::set_origin;
        bindPolygon["get_position"] = &obe::graphics::shapes::Polygon::get_position;
        bindPolygon["get_rotation"] = &obe::graphics::shapes::Polygon::get_rotation;
        bindPolygon["get_scale"] = &obe::graphics::shapes::Polygon::get_scale;
        bindPolygon["get_origin"] = &obe::graphics::shapes::Polygon::get_origin;
        bindPolygon["move"] = &obe::graphics::shapes::Polygon::move;
        bindPolygon["rotate"] = &obe::graphics::shapes::Polygon::rotate;
        bindPolygon["scale"] = &obe::graphics::shapes::Polygon::scale;
        bindPolygon["draw"] = &obe::graphics::shapes::Polygon::draw;
        bindPolygon["set_point_position"] = &obe::graphics::shapes::Polygon::set_point_position;
        bindPolygon["get_point_position"] = &obe::graphics::shapes::Polygon::get_point_position;
        bindPolygon["shape"] = &obe::graphics::shapes::Polygon::shape;
    }
    void LoadClassRectangle(sol::state_view state)
    {
        sol::table ShapesNamespace = state["obe"]["graphics"]["shapes"].get<sol::table>();
        sol::usertype<obe::graphics::shapes::Rectangle> bindRectangle
            = ShapesNamespace.new_usertype<obe::graphics::shapes::Rectangle>("Rectangle",
                sol::call_constructor,
                sol::constructors<obe::graphics::shapes::Rectangle(),
                    obe::graphics::shapes::Rectangle(const sf::RectangleShape&),
                    obe::graphics::shapes::Rectangle(const obe::graphics::shapes::Rectangle&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::shapes::Shape<obe::graphics::shapes::Rectangle>>());
        bindRectangle["set_texture"] = &obe::graphics::shapes::Rectangle::set_texture;
        bindRectangle["set_texture_rect"] = &obe::graphics::shapes::Rectangle::set_texture_rect;
        bindRectangle["set_position"] = &obe::graphics::shapes::Rectangle::set_position;
        bindRectangle["set_fill_color"] = &obe::graphics::shapes::Rectangle::set_fill_color;
        bindRectangle["set_outline_color"] = &obe::graphics::shapes::Rectangle::set_outline_color;
        bindRectangle["set_outline_thickness"]
            = &obe::graphics::shapes::Rectangle::set_outline_thickness;
        bindRectangle["get_fill_color"] = &obe::graphics::shapes::Rectangle::get_fill_color;
        bindRectangle["get_outline_color"] = &obe::graphics::shapes::Rectangle::get_outline_color;
        bindRectangle["get_outline_thickness"]
            = &obe::graphics::shapes::Rectangle::get_outline_thickness;
        bindRectangle["get_point_count"] = &obe::graphics::shapes::Rectangle::get_point_count;
        bindRectangle["get_point"] = &obe::graphics::shapes::Rectangle::get_point;
        bindRectangle["get_local_bounds"] = &obe::graphics::shapes::Rectangle::get_local_bounds;
        bindRectangle["get_global_bounds"] = &obe::graphics::shapes::Rectangle::get_global_bounds;
        bindRectangle["set_rotation"] = &obe::graphics::shapes::Rectangle::set_rotation;
        bindRectangle["set_scale"] = &obe::graphics::shapes::Rectangle::set_scale;
        bindRectangle["set_origin"] = &obe::graphics::shapes::Rectangle::set_origin;
        bindRectangle["get_position"] = &obe::graphics::shapes::Rectangle::get_position;
        bindRectangle["get_rotation"] = &obe::graphics::shapes::Rectangle::get_rotation;
        bindRectangle["get_scale"] = &obe::graphics::shapes::Rectangle::get_scale;
        bindRectangle["get_origin"] = &obe::graphics::shapes::Rectangle::get_origin;
        bindRectangle["move"] = &obe::graphics::shapes::Rectangle::move;
        bindRectangle["rotate"] = &obe::graphics::shapes::Rectangle::rotate;
        bindRectangle["scale"] = &obe::graphics::shapes::Rectangle::scale;
        bindRectangle["draw"] = &obe::graphics::shapes::Rectangle::draw;
        bindRectangle["get_size"] = &obe::graphics::shapes::Rectangle::get_size;
        bindRectangle["set_size"] = &obe::graphics::shapes::Rectangle::set_size;
        bindRectangle["shape"] = &obe::graphics::shapes::Rectangle::shape;
    }
    void LoadClassText(sol::state_view state)
    {
        sol::table ShapesNamespace = state["obe"]["graphics"]["shapes"].get<sol::table>();
        sol::usertype<obe::graphics::shapes::Text> bindText
            = ShapesNamespace.new_usertype<obe::graphics::shapes::Text>("Text",
                sol::call_constructor,
                sol::constructors<obe::graphics::shapes::Text(),
                    obe::graphics::shapes::Text(const obe::graphics::RichText&),
                    obe::graphics::shapes::Text(const obe::graphics::shapes::Text&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::shapes::BaseShape<obe::graphics::shapes::Text>>());
        bindText["set_position"] = &obe::graphics::shapes::Text::set_position;
        bindText["get_local_bounds"] = &obe::graphics::shapes::Text::get_local_bounds;
        bindText["get_global_bounds"] = &obe::graphics::shapes::Text::get_global_bounds;
        bindText["set_rotation"] = &obe::graphics::shapes::Text::set_rotation;
        bindText["set_scale"] = &obe::graphics::shapes::Text::set_scale;
        bindText["set_origin"] = &obe::graphics::shapes::Text::set_origin;
        bindText["get_position"] = &obe::graphics::shapes::Text::get_position;
        bindText["get_rotation"] = &obe::graphics::shapes::Text::get_rotation;
        bindText["get_scale"] = &obe::graphics::shapes::Text::get_scale;
        bindText["get_origin"] = &obe::graphics::shapes::Text::get_origin;
        bindText["move"] = &obe::graphics::shapes::Text::move;
        bindText["rotate"] = &obe::graphics::shapes::Text::rotate;
        bindText["scale"] = &obe::graphics::shapes::Text::scale;
        bindText["draw"] = &obe::graphics::shapes::Text::draw;
        bindText["clear"] = &obe::graphics::shapes::Text::clear;
        bindText["append"] = &obe::graphics::shapes::Text::append;
        bindText["get_font"] = &obe::graphics::shapes::Text::get_font;
        bindText["set_font"] = &obe::graphics::shapes::Text::set_font;
        bindText["get_character_size"] = &obe::graphics::shapes::Text::get_character_size;
        bindText["set_character_size"] = &obe::graphics::shapes::Text::set_character_size;
        bindText["shape"] = &obe::graphics::shapes::Text::shape;
    }
};