#include <Bindings/obe/graphics/canvas/Canvas.hpp>

#include <Graphics/Canvas.hpp>
#include <System/Path.hpp>

#include <Bindings/Config.hpp>

namespace obe::graphics::canvas::bindings
{
    void load_enum_canvas_element_type(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        canvas_namespace.new_enum<obe::graphics::canvas::CanvasElementType>("CanvasElementType",
            { { "CanvasElement", obe::graphics::canvas::CanvasElementType::CanvasElement },
                { "Line", obe::graphics::canvas::CanvasElementType::Line },
                { "Rectangle", obe::graphics::canvas::CanvasElementType::Rectangle },
                { "Text", obe::graphics::canvas::CanvasElementType::Text },
                { "Circle", obe::graphics::canvas::CanvasElementType::Circle },
                { "Polygon", obe::graphics::canvas::CanvasElementType::Polygon },
                { "Bezier", obe::graphics::canvas::CanvasElementType::Bezier },
                { "NinePatch", obe::graphics::canvas::CanvasElementType::NinePatch } });
    }
    void load_enum_text_horizontal_align(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        canvas_namespace.new_enum<obe::graphics::canvas::TextHorizontalAlign>("TextHorizontalAlign",
            { { "Left", obe::graphics::canvas::TextHorizontalAlign::Left },
                { "Center", obe::graphics::canvas::TextHorizontalAlign::Center },
                { "Right", obe::graphics::canvas::TextHorizontalAlign::Right } });
    }
    void load_enum_text_vertical_align(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        canvas_namespace.new_enum<obe::graphics::canvas::TextVerticalAlign>("TextVerticalAlign",
            { { "Top", obe::graphics::canvas::TextVerticalAlign::Top },
                { "Center", obe::graphics::canvas::TextVerticalAlign::Center },
                { "Bottom", obe::graphics::canvas::TextVerticalAlign::Bottom } });
    }
    void load_class_bezier(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Bezier> bind_bezier
            = canvas_namespace.new_usertype<obe::graphics::canvas::Bezier>("Bezier",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Bezier(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasElement, obe::types::ProtectedIdentifiable,
                    obe::types::Identifiable>());
        bind_bezier["draw"] = &obe::graphics::canvas::Bezier::draw;
        bind_bezier["points"] = &obe::graphics::canvas::Bezier::points;
        bind_bezier["colors"] = &obe::graphics::canvas::Bezier::colors;
        bind_bezier["precision"] = &obe::graphics::canvas::Bezier::precision;
        bind_bezier["Type"] = sol::var(&obe::graphics::canvas::Bezier::Type);
    }
    void load_class_canvas(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Canvas> bind_canvas
            = canvas_namespace.new_usertype<obe::graphics::canvas::Canvas>("Canvas",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Canvas(unsigned int, unsigned int)>());
        bind_canvas["Line"] = static_cast<obe::graphics::canvas::Line& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bind_canvas["Rectangle"] = static_cast<obe::graphics::canvas::Rectangle& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bind_canvas["Text"] = static_cast<obe::graphics::canvas::Text& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bind_canvas["Circle"] = static_cast<obe::graphics::canvas::Circle& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bind_canvas["Polygon"] = static_cast<obe::graphics::canvas::Polygon& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bind_canvas["Bezier"] = static_cast<obe::graphics::canvas::Bezier& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bind_canvas["NinePatch"] = static_cast<obe::graphics::canvas::NinePatch& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bind_canvas["get"] = &obe::graphics::canvas::Canvas::get;
        bind_canvas["render"] = &obe::graphics::canvas::Canvas::render;
        bind_canvas["clear"] = &obe::graphics::canvas::Canvas::clear;
        bind_canvas["remove"] = &obe::graphics::canvas::Canvas::remove;
        bind_canvas["get_texture"] = &obe::graphics::canvas::Canvas::get_texture;
        bind_canvas["requires_sort"] = &obe::graphics::canvas::Canvas::requires_sort;
        state.script_file("obe://Lib/Internal/Canvas.lua"_fs);
    }
    void load_class_canvas_element(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::CanvasElement> bind_canvas_element
            = canvas_namespace.new_usertype<obe::graphics::canvas::CanvasElement>("CanvasElement",
                sol::base_classes,
                sol::bases<obe::types::ProtectedIdentifiable, obe::types::Identifiable>());
        bind_canvas_element["draw"] = &obe::graphics::canvas::CanvasElement::draw;
        bind_canvas_element["set_layer"] = &obe::graphics::canvas::CanvasElement::set_layer;
        bind_canvas_element["layer"] = &obe::graphics::canvas::CanvasElement::layer;
        bind_canvas_element["visible"] = &obe::graphics::canvas::CanvasElement::visible;
        bind_canvas_element["type"] = &obe::graphics::canvas::CanvasElement::type;
        bind_canvas_element["Type"] = sol::var(&obe::graphics::canvas::CanvasElement::Type);
    }
    void load_class_canvas_positionable(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::CanvasPositionable> bind_canvas_positionable
            = canvas_namespace.new_usertype<obe::graphics::canvas::CanvasPositionable>(
                "CanvasPositionable", sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasElement, obe::types::ProtectedIdentifiable,
                    obe::types::Identifiable>());
        bind_canvas_positionable["position"] = &obe::graphics::canvas::CanvasPositionable::position;
    }
    void load_class_circle(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Circle> bind_circle
            = canvas_namespace.new_usertype<obe::graphics::canvas::Circle>("Circle",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Circle(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasPositionable,
                    obe::graphics::canvas::CanvasElement, obe::types::ProtectedIdentifiable,
                    obe::types::Identifiable>());
        bind_circle["draw"] = &obe::graphics::canvas::Circle::draw;
        bind_circle["shape"] = &obe::graphics::canvas::Circle::shape;
        bind_circle["Type"] = sol::var(&obe::graphics::canvas::Circle::Type);
    }
    void load_class_line(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Line> bind_line
            = canvas_namespace.new_usertype<obe::graphics::canvas::Line>("Line",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Line(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasElement, obe::types::ProtectedIdentifiable,
                    obe::types::Identifiable>());
        bind_line["draw"] = &obe::graphics::canvas::Line::draw;
        bind_line["p1"] = &obe::graphics::canvas::Line::p1;
        bind_line["p2"] = &obe::graphics::canvas::Line::p2;
        bind_line["thickness"] = &obe::graphics::canvas::Line::thickness;
        bind_line["p1_color"] = &obe::graphics::canvas::Line::p1_color;
        bind_line["p2_color"] = &obe::graphics::canvas::Line::p2_color;
        bind_line["Type"] = sol::var(&obe::graphics::canvas::Line::Type);
    }
    void load_class_nine_patch(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::NinePatch> bind_nine_patch
            = canvas_namespace.new_usertype<obe::graphics::canvas::NinePatch>("NinePatch",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::NinePatch(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasPositionable,
                    obe::graphics::canvas::CanvasElement, obe::types::ProtectedIdentifiable,
                    obe::types::Identifiable>());
        bind_nine_patch["draw"] = &obe::graphics::canvas::NinePatch::draw;
        bind_nine_patch["shape"] = &obe::graphics::canvas::NinePatch::shape;
        bind_nine_patch["Type"] = sol::var(&obe::graphics::canvas::NinePatch::Type);
    }
    void load_class_polygon(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Polygon> bind_polygon
            = canvas_namespace.new_usertype<obe::graphics::canvas::Polygon>("Polygon",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Polygon(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasPositionable,
                    obe::graphics::canvas::CanvasElement, obe::types::ProtectedIdentifiable,
                    obe::types::Identifiable>());
        bind_polygon["draw"] = &obe::graphics::canvas::Polygon::draw;
        bind_polygon["shape"] = &obe::graphics::canvas::Polygon::shape;
        bind_polygon["Type"] = sol::var(&obe::graphics::canvas::Polygon::Type);
    }
    void load_class_rectangle(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Rectangle> bind_rectangle
            = canvas_namespace.new_usertype<obe::graphics::canvas::Rectangle>("Rectangle",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Rectangle(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasPositionable,
                    obe::graphics::canvas::CanvasElement, obe::types::ProtectedIdentifiable,
                    obe::types::Identifiable>());
        bind_rectangle["draw"] = &obe::graphics::canvas::Rectangle::draw;
        bind_rectangle["shape"] = &obe::graphics::canvas::Rectangle::shape;
        bind_rectangle["size"] = &obe::graphics::canvas::Rectangle::size;
        bind_rectangle["Type"] = sol::var(&obe::graphics::canvas::Rectangle::Type);
    }
    void load_class_text(sol::state_view state)
    {
        sol::table canvas_namespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Text> bind_text
            = canvas_namespace.new_usertype<obe::graphics::canvas::Text>("Text",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Text(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasPositionable,
                    obe::graphics::canvas::CanvasElement, obe::types::ProtectedIdentifiable,
                    obe::types::Identifiable>());
        bind_text["draw"] = &obe::graphics::canvas::Text::draw;
        bind_text["refresh"] = &obe::graphics::canvas::Text::refresh;
        bind_text["text"] = sol::property(&obe::graphics::canvas::Text::current_text);
        bind_text["font_path"] = &obe::graphics::canvas::Text::font_path;
        bind_text["shape"] = &obe::graphics::canvas::Text::shape;
        bind_text["h_align"] = &obe::graphics::canvas::Text::h_align;
        bind_text["v_align"] = &obe::graphics::canvas::Text::v_align;
        bind_text["texts"] = &obe::graphics::canvas::Text::texts;
        bind_text["Type"] = sol::var(&obe::graphics::canvas::Text::Type);
    }
};