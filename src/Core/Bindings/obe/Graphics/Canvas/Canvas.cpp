#include <Bindings/obe/Graphics/Canvas/Canvas.hpp>

#include <Graphics/Canvas.hpp>
#include <System/Path.hpp>

#include <Bindings/Config.hpp>

namespace obe::graphics::canvas::Bindings
{
    void LoadEnumCanvasElementType(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        CanvasNamespace.new_enum<obe::graphics::canvas::CanvasElementType>("CanvasElementType",
            { { "CanvasElement", obe::graphics::canvas::CanvasElementType::CanvasElement },
                { "Line", obe::graphics::canvas::CanvasElementType::Line },
                { "Rectangle", obe::graphics::canvas::CanvasElementType::Rectangle },
                { "Text", obe::graphics::canvas::CanvasElementType::Text },
                { "Circle", obe::graphics::canvas::CanvasElementType::Circle },
                { "Polygon", obe::graphics::canvas::CanvasElementType::Polygon },
                { "Bezier", obe::graphics::canvas::CanvasElementType::Bezier } });
    }
    void LoadEnumTextHorizontalAlign(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        CanvasNamespace.new_enum<obe::graphics::canvas::TextHorizontalAlign>("TextHorizontalAlign",
            { { "Left", obe::graphics::canvas::TextHorizontalAlign::Left },
                { "Center", obe::graphics::canvas::TextHorizontalAlign::Center },
                { "Right", obe::graphics::canvas::TextHorizontalAlign::Right } });
    }
    void LoadEnumTextVerticalAlign(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        CanvasNamespace.new_enum<obe::graphics::canvas::TextVerticalAlign>("TextVerticalAlign",
            { { "Top", obe::graphics::canvas::TextVerticalAlign::Top },
                { "Center", obe::graphics::canvas::TextVerticalAlign::Center },
                { "Bottom", obe::graphics::canvas::TextVerticalAlign::Bottom } });
    }
    void LoadClassBezier(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Bezier> bindBezier
            = CanvasNamespace.new_usertype<obe::graphics::canvas::Bezier>("Bezier",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Bezier(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasElement, obe::Types::ProtectedIdentifiable,
                    obe::Types::Identifiable>());
        bindBezier["draw"] = &obe::graphics::canvas::Bezier::draw;
        bindBezier["points"] = &obe::graphics::canvas::Bezier::points;
        bindBezier["colors"] = &obe::graphics::canvas::Bezier::colors;
        bindBezier["precision"] = &obe::graphics::canvas::Bezier::precision;
        bindBezier["Type"] = sol::var(&obe::graphics::canvas::Bezier::Type);
    }
    void LoadClassCanvas(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Canvas> bindCanvas
            = CanvasNamespace.new_usertype<obe::graphics::canvas::Canvas>("Canvas",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Canvas(unsigned int, unsigned int)>());
        bindCanvas["Line"] = static_cast<obe::graphics::canvas::Line& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bindCanvas["Rectangle"] = static_cast<obe::graphics::canvas::Rectangle& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bindCanvas["Text"] = static_cast<obe::graphics::canvas::Text& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bindCanvas["Circle"] = static_cast<obe::graphics::canvas::Circle& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bindCanvas["Polygon"] = static_cast<obe::graphics::canvas::Polygon& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bindCanvas["Bezier"] = static_cast<obe::graphics::canvas::Bezier& (
            obe::graphics::canvas::Canvas::*)(const std::string&)>(
            &obe::graphics::canvas::Canvas::add);
        ;
        bindCanvas["get"] = &obe::graphics::canvas::Canvas::get;
        bindCanvas["render"] = &obe::graphics::canvas::Canvas::render;
        bindCanvas["clear"] = &obe::graphics::canvas::Canvas::clear;
        bindCanvas["remove"] = &obe::graphics::canvas::Canvas::remove;
        bindCanvas["get_texture"] = &obe::graphics::canvas::Canvas::get_texture;
        bindCanvas["requires_sort"] = &obe::graphics::canvas::Canvas::requires_sort;
        state.script_file("obe://Lib/Internal/Canvas.lua"_fs);
    }
    void LoadClassCanvasElement(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::CanvasElement> bindCanvasElement
            = CanvasNamespace.new_usertype<obe::graphics::canvas::CanvasElement>("CanvasElement",
                sol::base_classes,
                sol::bases<obe::Types::ProtectedIdentifiable, obe::Types::Identifiable>());
        bindCanvasElement["draw"] = &obe::graphics::canvas::CanvasElement::draw;
        bindCanvasElement["set_layer"] = &obe::graphics::canvas::CanvasElement::set_layer;
        bindCanvasElement["layer"] = &obe::graphics::canvas::CanvasElement::layer;
        bindCanvasElement["visible"] = &obe::graphics::canvas::CanvasElement::visible;
        bindCanvasElement["type"] = &obe::graphics::canvas::CanvasElement::type;
        bindCanvasElement["Type"] = sol::var(&obe::graphics::canvas::CanvasElement::Type);
    }
    void LoadClassCanvasPositionable(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::CanvasPositionable> bindCanvasPositionable
            = CanvasNamespace.new_usertype<obe::graphics::canvas::CanvasPositionable>(
                "CanvasPositionable", sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasElement, obe::Types::ProtectedIdentifiable,
                    obe::Types::Identifiable>());
        bindCanvasPositionable["position"] = &obe::graphics::canvas::CanvasPositionable::position;
    }
    void LoadClassCircle(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Circle> bindCircle
            = CanvasNamespace.new_usertype<obe::graphics::canvas::Circle>("Circle",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Circle(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasPositionable,
                    obe::graphics::canvas::CanvasElement, obe::Types::ProtectedIdentifiable,
                    obe::Types::Identifiable>());
        bindCircle["draw"] = &obe::graphics::canvas::Circle::draw;
        bindCircle["shape"] = &obe::graphics::canvas::Circle::shape;
        bindCircle["Type"] = sol::var(&obe::graphics::canvas::Circle::Type);
    }
    void LoadClassLine(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Line> bindLine
            = CanvasNamespace.new_usertype<obe::graphics::canvas::Line>("Line",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Line(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasElement, obe::Types::ProtectedIdentifiable,
                    obe::Types::Identifiable>());
        bindLine["draw"] = &obe::graphics::canvas::Line::draw;
        bindLine["p1"] = &obe::graphics::canvas::Line::p1;
        bindLine["p2"] = &obe::graphics::canvas::Line::p2;
        bindLine["thickness"] = &obe::graphics::canvas::Line::thickness;
        bindLine["p1_color"] = &obe::graphics::canvas::Line::p1_color;
        bindLine["p2_color"] = &obe::graphics::canvas::Line::p2_color;
        bindLine["Type"] = sol::var(&obe::graphics::canvas::Line::Type);
    }
    void LoadClassPolygon(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Polygon> bindPolygon
            = CanvasNamespace.new_usertype<obe::graphics::canvas::Polygon>("Polygon",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Polygon(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasPositionable,
                    obe::graphics::canvas::CanvasElement, obe::Types::ProtectedIdentifiable,
                    obe::Types::Identifiable>());
        bindPolygon["draw"] = &obe::graphics::canvas::Polygon::draw;
        bindPolygon["shape"] = &obe::graphics::canvas::Polygon::shape;
        bindPolygon["Type"] = sol::var(&obe::graphics::canvas::Polygon::Type);
    }
    void LoadClassRectangle(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Rectangle> bindRectangle
            = CanvasNamespace.new_usertype<obe::graphics::canvas::Rectangle>("Rectangle",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Rectangle(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasPositionable,
                    obe::graphics::canvas::CanvasElement, obe::Types::ProtectedIdentifiable,
                    obe::Types::Identifiable>());
        bindRectangle["draw"] = &obe::graphics::canvas::Rectangle::draw;
        bindRectangle["shape"] = &obe::graphics::canvas::Rectangle::shape;
        bindRectangle["size"] = &obe::graphics::canvas::Rectangle::size;
        bindRectangle["Type"] = sol::var(&obe::graphics::canvas::Rectangle::Type);
    }
    void LoadClassText(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["graphics"]["canvas"].get<sol::table>();
        sol::usertype<obe::graphics::canvas::Text> bindText
            = CanvasNamespace.new_usertype<obe::graphics::canvas::Text>("Text",
                sol::call_constructor,
                sol::constructors<obe::graphics::canvas::Text(
                    obe::graphics::canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::graphics::canvas::CanvasPositionable,
                    obe::graphics::canvas::CanvasElement, obe::Types::ProtectedIdentifiable,
                    obe::Types::Identifiable>());
        bindText["draw"] = &obe::graphics::canvas::Text::draw;
        bindText["refresh"] = &obe::graphics::canvas::Text::refresh;
        bindText["text"] = sol::property(&obe::graphics::canvas::Text::current_text);
        bindText["font_path"] = &obe::graphics::canvas::Text::font_path;
        bindText["shape"] = &obe::graphics::canvas::Text::shape;
        bindText["h_align"] = &obe::graphics::canvas::Text::h_align;
        bindText["v_align"] = &obe::graphics::canvas::Text::v_align;
        bindText["texts"] = &obe::graphics::canvas::Text::texts;
        bindText["Type"] = sol::var(&obe::graphics::canvas::Text::Type);
    }
};