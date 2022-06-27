#include <Bindings/obe/graphics/shapes/Shapes.hpp>

#include <Graphics/Shapes.hpp>

#include <Bindings/Config.hpp>

namespace obe::graphics::shapes::bindings
{
    void load_class_circle(sol::state_view state)
    {
        sol::table shapes_namespace = state["obe"]["graphics"]["shapes"].get<sol::table>();
        sol::usertype<obe::graphics::shapes::Circle> bind_circle
            = shapes_namespace.new_usertype<obe::graphics::shapes::Circle>("Circle",
                sol::call_constructor,
                sol::constructors<obe::graphics::shapes::Circle(),
                    obe::graphics::shapes::Circle(const sf::CircleShape&),
                    obe::graphics::shapes::Circle(const obe::graphics::shapes::Circle&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::shapes::Shape<obe::graphics::shapes::Circle>>());
        bind_circle["set_texture"] = &obe::graphics::shapes::Circle::set_texture;
        bind_circle["set_texture_rect"] = &obe::graphics::shapes::Circle::set_texture_rect;
        bind_circle["set_position"] = &obe::graphics::shapes::Circle::set_position;
        bind_circle["set_fill_color"] = &obe::graphics::shapes::Circle::set_fill_color;
        bind_circle["set_outline_color"] = &obe::graphics::shapes::Circle::set_outline_color;
        bind_circle["set_outline_thickness"]
            = &obe::graphics::shapes::Circle::set_outline_thickness;
        bind_circle["get_fill_color"] = &obe::graphics::shapes::Circle::get_fill_color;
        bind_circle["get_outline_color"] = &obe::graphics::shapes::Circle::get_outline_color;
        bind_circle["get_outline_thickness"]
            = &obe::graphics::shapes::Circle::get_outline_thickness;
        bind_circle["get_point_count"] = &obe::graphics::shapes::Circle::get_point_count;
        bind_circle["get_point"] = &obe::graphics::shapes::Circle::get_point;
        bind_circle["get_local_bounds"] = &obe::graphics::shapes::Circle::get_local_bounds;
        bind_circle["get_global_bounds"] = &obe::graphics::shapes::Circle::get_global_bounds;
        bind_circle["set_rotation"] = &obe::graphics::shapes::Circle::set_rotation;
        bind_circle["set_scale"] = &obe::graphics::shapes::Circle::set_scale;
        bind_circle["set_origin"] = &obe::graphics::shapes::Circle::set_origin;
        bind_circle["get_position"] = &obe::graphics::shapes::Circle::get_position;
        bind_circle["get_rotation"] = &obe::graphics::shapes::Circle::get_rotation;
        bind_circle["get_scale"] = &obe::graphics::shapes::Circle::get_scale;
        bind_circle["get_origin"] = &obe::graphics::shapes::Circle::get_origin;
        bind_circle["move"] = &obe::graphics::shapes::Circle::move;
        bind_circle["rotate"] = &obe::graphics::shapes::Circle::rotate;
        bind_circle["scale"] = &obe::graphics::shapes::Circle::scale;
        bind_circle["draw"] = &obe::graphics::shapes::Circle::draw;
        bind_circle["set_radius"] = &obe::graphics::shapes::Circle::set_radius;
        bind_circle["get_radius"] = &obe::graphics::shapes::Circle::get_radius;
        bind_circle["shape"] = &obe::graphics::shapes::Circle::shape;
    }
    void load_class_polygon(sol::state_view state)
    {
        sol::table shapes_namespace = state["obe"]["graphics"]["shapes"].get<sol::table>();
        sol::usertype<obe::graphics::shapes::Polygon> bind_polygon
            = shapes_namespace.new_usertype<obe::graphics::shapes::Polygon>("Polygon",
                sol::call_constructor,
                sol::constructors<obe::graphics::shapes::Polygon(),
                    obe::graphics::shapes::Polygon(const sf::ConvexShape&),
                    obe::graphics::shapes::Polygon(const obe::graphics::shapes::Polygon&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::shapes::Shape<obe::graphics::shapes::Polygon>>());
        bind_polygon["set_texture"] = &obe::graphics::shapes::Polygon::set_texture;
        bind_polygon["set_texture_rect"] = &obe::graphics::shapes::Polygon::set_texture_rect;
        bind_polygon["set_position"] = &obe::graphics::shapes::Polygon::set_position;
        bind_polygon["set_fill_color"] = &obe::graphics::shapes::Polygon::set_fill_color;
        bind_polygon["set_outline_color"] = &obe::graphics::shapes::Polygon::set_outline_color;
        bind_polygon["set_outline_thickness"]
            = &obe::graphics::shapes::Polygon::set_outline_thickness;
        bind_polygon["get_fill_color"] = &obe::graphics::shapes::Polygon::get_fill_color;
        bind_polygon["get_outline_color"] = &obe::graphics::shapes::Polygon::get_outline_color;
        bind_polygon["get_outline_thickness"]
            = &obe::graphics::shapes::Polygon::get_outline_thickness;
        bind_polygon["get_point_count"] = &obe::graphics::shapes::Polygon::get_point_count;
        bind_polygon["get_point"] = &obe::graphics::shapes::Polygon::get_point;
        bind_polygon["get_local_bounds"] = &obe::graphics::shapes::Polygon::get_local_bounds;
        bind_polygon["get_global_bounds"] = &obe::graphics::shapes::Polygon::get_global_bounds;
        bind_polygon["set_rotation"] = &obe::graphics::shapes::Polygon::set_rotation;
        bind_polygon["set_scale"] = &obe::graphics::shapes::Polygon::set_scale;
        bind_polygon["set_origin"] = &obe::graphics::shapes::Polygon::set_origin;
        bind_polygon["get_position"] = &obe::graphics::shapes::Polygon::get_position;
        bind_polygon["get_rotation"] = &obe::graphics::shapes::Polygon::get_rotation;
        bind_polygon["get_scale"] = &obe::graphics::shapes::Polygon::get_scale;
        bind_polygon["get_origin"] = &obe::graphics::shapes::Polygon::get_origin;
        bind_polygon["move"] = &obe::graphics::shapes::Polygon::move;
        bind_polygon["rotate"] = &obe::graphics::shapes::Polygon::rotate;
        bind_polygon["scale"] = &obe::graphics::shapes::Polygon::scale;
        bind_polygon["draw"] = &obe::graphics::shapes::Polygon::draw;
        bind_polygon["set_point_position"] = &obe::graphics::shapes::Polygon::set_point_position;
        bind_polygon["get_point_position"] = &obe::graphics::shapes::Polygon::get_point_position;
        bind_polygon["shape"] = &obe::graphics::shapes::Polygon::shape;
    }
    void load_class_rectangle(sol::state_view state)
    {
        sol::table shapes_namespace = state["obe"]["graphics"]["shapes"].get<sol::table>();
        sol::usertype<obe::graphics::shapes::Rectangle> bind_rectangle
            = shapes_namespace.new_usertype<obe::graphics::shapes::Rectangle>("Rectangle",
                sol::call_constructor,
                sol::constructors<obe::graphics::shapes::Rectangle(),
                    obe::graphics::shapes::Rectangle(const sf::RectangleShape&),
                    obe::graphics::shapes::Rectangle(const obe::graphics::shapes::Rectangle&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::shapes::Shape<obe::graphics::shapes::Rectangle>>());
        bind_rectangle["set_texture"] = &obe::graphics::shapes::Rectangle::set_texture;
        bind_rectangle["set_texture_rect"] = &obe::graphics::shapes::Rectangle::set_texture_rect;
        bind_rectangle["set_position"] = &obe::graphics::shapes::Rectangle::set_position;
        bind_rectangle["set_fill_color"] = &obe::graphics::shapes::Rectangle::set_fill_color;
        bind_rectangle["set_outline_color"] = &obe::graphics::shapes::Rectangle::set_outline_color;
        bind_rectangle["set_outline_thickness"]
            = &obe::graphics::shapes::Rectangle::set_outline_thickness;
        bind_rectangle["get_fill_color"] = &obe::graphics::shapes::Rectangle::get_fill_color;
        bind_rectangle["get_outline_color"] = &obe::graphics::shapes::Rectangle::get_outline_color;
        bind_rectangle["get_outline_thickness"]
            = &obe::graphics::shapes::Rectangle::get_outline_thickness;
        bind_rectangle["get_point_count"] = &obe::graphics::shapes::Rectangle::get_point_count;
        bind_rectangle["get_point"] = &obe::graphics::shapes::Rectangle::get_point;
        bind_rectangle["get_local_bounds"] = &obe::graphics::shapes::Rectangle::get_local_bounds;
        bind_rectangle["get_global_bounds"] = &obe::graphics::shapes::Rectangle::get_global_bounds;
        bind_rectangle["set_rotation"] = &obe::graphics::shapes::Rectangle::set_rotation;
        bind_rectangle["set_scale"] = &obe::graphics::shapes::Rectangle::set_scale;
        bind_rectangle["set_origin"] = &obe::graphics::shapes::Rectangle::set_origin;
        bind_rectangle["get_position"] = &obe::graphics::shapes::Rectangle::get_position;
        bind_rectangle["get_rotation"] = &obe::graphics::shapes::Rectangle::get_rotation;
        bind_rectangle["get_scale"] = &obe::graphics::shapes::Rectangle::get_scale;
        bind_rectangle["get_origin"] = &obe::graphics::shapes::Rectangle::get_origin;
        bind_rectangle["move"] = &obe::graphics::shapes::Rectangle::move;
        bind_rectangle["rotate"] = &obe::graphics::shapes::Rectangle::rotate;
        bind_rectangle["scale"] = &obe::graphics::shapes::Rectangle::scale;
        bind_rectangle["draw"] = &obe::graphics::shapes::Rectangle::draw;
        bind_rectangle["get_size"] = &obe::graphics::shapes::Rectangle::get_size;
        bind_rectangle["set_size"] = &obe::graphics::shapes::Rectangle::set_size;
        bind_rectangle["shape"] = &obe::graphics::shapes::Rectangle::shape;
    }
    void load_class_text(sol::state_view state)
    {
        sol::table shapes_namespace = state["obe"]["graphics"]["shapes"].get<sol::table>();
        sol::usertype<obe::graphics::shapes::Text> bind_text
            = shapes_namespace.new_usertype<obe::graphics::shapes::Text>("Text",
                sol::call_constructor,
                sol::constructors<obe::graphics::shapes::Text(),
                    obe::graphics::shapes::Text(const obe::graphics::RichText&),
                    obe::graphics::shapes::Text(const obe::graphics::shapes::Text&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::shapes::BaseShape<obe::graphics::shapes::Text>>());
        bind_text["set_position"] = &obe::graphics::shapes::Text::set_position;
        bind_text["get_local_bounds"] = &obe::graphics::shapes::Text::get_local_bounds;
        bind_text["get_global_bounds"] = &obe::graphics::shapes::Text::get_global_bounds;
        bind_text["set_rotation"] = &obe::graphics::shapes::Text::set_rotation;
        bind_text["set_scale"] = &obe::graphics::shapes::Text::set_scale;
        bind_text["set_origin"] = &obe::graphics::shapes::Text::set_origin;
        bind_text["get_position"] = &obe::graphics::shapes::Text::get_position;
        bind_text["get_rotation"] = &obe::graphics::shapes::Text::get_rotation;
        bind_text["get_scale"] = &obe::graphics::shapes::Text::get_scale;
        bind_text["get_origin"] = &obe::graphics::shapes::Text::get_origin;
        bind_text["move"] = &obe::graphics::shapes::Text::move;
        bind_text["rotate"] = &obe::graphics::shapes::Text::rotate;
        bind_text["scale"] = &obe::graphics::shapes::Text::scale;
        bind_text["draw"] = &obe::graphics::shapes::Text::draw;
        bind_text["clear"] = &obe::graphics::shapes::Text::clear;
        bind_text["append"] = &obe::graphics::shapes::Text::append;
        bind_text["get_font"] = &obe::graphics::shapes::Text::get_font;
        bind_text["set_font"] = &obe::graphics::shapes::Text::set_font;
        bind_text["get_character_size"] = &obe::graphics::shapes::Text::get_character_size;
        bind_text["set_character_size"] = &obe::graphics::shapes::Text::set_character_size;
        bind_text["shape"] = &obe::graphics::shapes::Text::shape;
    }
};