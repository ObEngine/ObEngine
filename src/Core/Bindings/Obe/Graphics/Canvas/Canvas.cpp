#include <Bindings/obe/Graphics/Canvas/Canvas.hpp>

#include <Graphics/Canvas.hpp>
#include <System/Path.hpp>

#include <Bindings/Config.hpp>

namespace obe::Graphics::Canvas::Bindings
{
    void LoadEnumCanvasElementType(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        CanvasNamespace.new_enum<obe::Graphics::Canvas::CanvasElementType>(
            "CanvasElementType",
            { { "CanvasElement",
                  obe::Graphics::Canvas::CanvasElementType::CanvasElement },
                { "Line", obe::Graphics::Canvas::CanvasElementType::Line },
                { "Rectangle", obe::Graphics::Canvas::CanvasElementType::Rectangle },
                { "Text", obe::Graphics::Canvas::CanvasElementType::Text },
                { "Circle", obe::Graphics::Canvas::CanvasElementType::Circle },
                { "Polygon", obe::Graphics::Canvas::CanvasElementType::Polygon },
                { "Bezier", obe::Graphics::Canvas::CanvasElementType::Bezier } });
    }
    void LoadEnumTextHorizontalAlign(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        CanvasNamespace.new_enum<obe::Graphics::Canvas::TextHorizontalAlign>(
            "TextHorizontalAlign",
            { { "Left", obe::Graphics::Canvas::TextHorizontalAlign::Left },
                { "Center", obe::Graphics::Canvas::TextHorizontalAlign::Center },
                { "Right", obe::Graphics::Canvas::TextHorizontalAlign::Right } });
    }
    void LoadEnumTextVerticalAlign(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        CanvasNamespace.new_enum<obe::Graphics::Canvas::TextVerticalAlign>(
            "TextVerticalAlign",
            { { "Top", obe::Graphics::Canvas::TextVerticalAlign::Top },
                { "Center", obe::Graphics::Canvas::TextVerticalAlign::Center },
                { "Bottom", obe::Graphics::Canvas::TextVerticalAlign::Bottom } });
    }
    void LoadClassBezier(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Bezier> bindBezier
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Bezier>("Bezier",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Bezier(
                    obe::Graphics::Canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::Graphics::Canvas::CanvasElement,
                    obe::Types::ProtectedIdentifiable, obe::Types::Identifiable>());
        bindBezier["draw"] = &obe::Graphics::Canvas::Bezier::draw;
        bindBezier["points"] = &obe::Graphics::Canvas::Bezier::points;
        bindBezier["colors"] = &obe::Graphics::Canvas::Bezier::colors;
        bindBezier["precision"] = &obe::Graphics::Canvas::Bezier::precision;
        bindBezier["Type"] = sol::var(obe::Graphics::Canvas::Bezier::Type);
    }
    void LoadClassCanvas(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Canvas> bindCanvas
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Canvas>("Canvas",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Canvas(
                    unsigned int, unsigned int)>());
        bindCanvas["Line"] = static_cast<obe::Graphics::Canvas::Line& (
            obe::Graphics::Canvas::Canvas::*)(const std::string&)>(
            &obe::Graphics::Canvas::Canvas::add);
        bindCanvas["Rectangle"] = static_cast<obe::Graphics::Canvas::Rectangle& (
            obe::Graphics::Canvas::Canvas::*)(const std::string&)>(
            &obe::Graphics::Canvas::Canvas::add);
        bindCanvas["Text"] = static_cast<obe::Graphics::Canvas::Text& (
            obe::Graphics::Canvas::Canvas::*)(const std::string&)>(
            &obe::Graphics::Canvas::Canvas::add);
        bindCanvas["Circle"] = static_cast<obe::Graphics::Canvas::Circle& (
            obe::Graphics::Canvas::Canvas::*)(const std::string&)>(
            &obe::Graphics::Canvas::Canvas::add);
        bindCanvas["Polygon"] = static_cast<obe::Graphics::Canvas::Polygon& (
            obe::Graphics::Canvas::Canvas::*)(const std::string&)>(
            &obe::Graphics::Canvas::Canvas::add);
        bindCanvas["Bezier"] = static_cast<obe::Graphics::Canvas::Bezier& (
            obe::Graphics::Canvas::Canvas::*)(const std::string&)>(
            &obe::Graphics::Canvas::Canvas::add);
        bindCanvas["get"] = &obe::Graphics::Canvas::Canvas::get;
        bindCanvas["render"] = &obe::Graphics::Canvas::Canvas::render;
        bindCanvas["clear"] = &obe::Graphics::Canvas::Canvas::clear;
        bindCanvas["remove"] = &obe::Graphics::Canvas::Canvas::remove;
        bindCanvas["getTexture"] = &obe::Graphics::Canvas::Canvas::getTexture;
        bindCanvas["requiresSort"] = &obe::Graphics::Canvas::Canvas::requiresSort;
        state.script_file("Lib/Internal/Canvas.lua"_fs);
    }
    void LoadClassCanvasElement(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::CanvasElement> bindCanvasElement
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::CanvasElement>(
                "CanvasElement", sol::base_classes,
                sol::bases<obe::Types::ProtectedIdentifiable,
                    obe::Types::Identifiable>());
        bindCanvasElement["draw"] = &obe::Graphics::Canvas::CanvasElement::draw;
        bindCanvasElement["setLayer"] = &obe::Graphics::Canvas::CanvasElement::setLayer;
        bindCanvasElement["layer"] = &obe::Graphics::Canvas::CanvasElement::layer;
        bindCanvasElement["visible"] = &obe::Graphics::Canvas::CanvasElement::visible;
        bindCanvasElement["type"] = &obe::Graphics::Canvas::CanvasElement::type;
        bindCanvasElement["Type"] = sol::var(obe::Graphics::Canvas::CanvasElement::Type);
    }
    void LoadClassCanvasPositionable(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::CanvasPositionable> bindCanvasPositionable
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::CanvasPositionable>(
                "CanvasPositionable", sol::base_classes,
                sol::bases<obe::Graphics::Canvas::CanvasElement,
                    obe::Types::ProtectedIdentifiable, obe::Types::Identifiable>());
        bindCanvasPositionable["position"]
            = &obe::Graphics::Canvas::CanvasPositionable::position;
    }
    void LoadClassCircle(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Circle> bindCircle
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Circle>("Circle",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Circle(
                    obe::Graphics::Canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::Graphics::Canvas::CanvasPositionable,
                    obe::Graphics::Canvas::CanvasElement,
                    obe::Types::ProtectedIdentifiable, obe::Types::Identifiable>());
        bindCircle["draw"] = &obe::Graphics::Canvas::Circle::draw;
        bindCircle["shape"] = &obe::Graphics::Canvas::Circle::shape;
        bindCircle["Type"] = sol::var(obe::Graphics::Canvas::Circle::Type);
    }
    void LoadClassLine(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Line> bindLine
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Line>("Line",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Line(
                    obe::Graphics::Canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::Graphics::Canvas::CanvasElement,
                    obe::Types::ProtectedIdentifiable, obe::Types::Identifiable>());
        bindLine["draw"] = &obe::Graphics::Canvas::Line::draw;
        bindLine["p1"] = &obe::Graphics::Canvas::Line::p1;
        bindLine["p2"] = &obe::Graphics::Canvas::Line::p2;
        bindLine["thickness"] = &obe::Graphics::Canvas::Line::thickness;
        bindLine["p1color"] = &obe::Graphics::Canvas::Line::p1color;
        bindLine["p2color"] = &obe::Graphics::Canvas::Line::p2color;
        bindLine["Type"] = sol::var(obe::Graphics::Canvas::Line::Type);
    }
    void LoadClassPolygon(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Polygon> bindPolygon
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Polygon>("Polygon",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Polygon(
                    obe::Graphics::Canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::Graphics::Canvas::CanvasPositionable,
                    obe::Graphics::Canvas::CanvasElement,
                    obe::Types::ProtectedIdentifiable, obe::Types::Identifiable>());
        bindPolygon["draw"] = &obe::Graphics::Canvas::Polygon::draw;
        bindPolygon["shape"] = &obe::Graphics::Canvas::Polygon::shape;
        bindPolygon["Type"] = sol::var(obe::Graphics::Canvas::Polygon::Type);
    }
    void LoadClassRectangle(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Rectangle> bindRectangle
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Rectangle>("Rectangle",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Rectangle(
                    obe::Graphics::Canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::Graphics::Canvas::CanvasPositionable,
                    obe::Graphics::Canvas::CanvasElement,
                    obe::Types::ProtectedIdentifiable, obe::Types::Identifiable>());
        bindRectangle["draw"] = &obe::Graphics::Canvas::Rectangle::draw;
        bindRectangle["shape"] = &obe::Graphics::Canvas::Rectangle::shape;
        bindRectangle["size"] = &obe::Graphics::Canvas::Rectangle::size;
        bindRectangle["Type"] = sol::var(obe::Graphics::Canvas::Rectangle::Type);
    }
    void LoadClassText(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Text> bindText
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Text>("Text",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Text(
                    obe::Graphics::Canvas::Canvas&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::Graphics::Canvas::CanvasPositionable,
                    obe::Graphics::Canvas::CanvasElement,
                    obe::Types::ProtectedIdentifiable, obe::Types::Identifiable>());
        bindText["draw"] = &obe::Graphics::Canvas::Text::draw;
        bindText["refresh"] = &obe::Graphics::Canvas::Text::refresh;
        bindText["text"] = sol::property(&obe::Graphics::Canvas::Text::currentText);
        bindText["fontPath"] = &obe::Graphics::Canvas::Text::fontPath;
        bindText["shape"] = &obe::Graphics::Canvas::Text::shape;
        bindText["h_align"] = &obe::Graphics::Canvas::Text::h_align;
        bindText["v_align"] = &obe::Graphics::Canvas::Text::v_align;
        bindText["texts"] = &obe::Graphics::Canvas::Text::texts;
        bindText["Type"] = sol::var(obe::Graphics::Canvas::Text::Type);
    }
    void LoadFunctionCanvasElementTypeToString(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        CanvasNamespace.set_function("canvasElementTypeToString",
            obe::Graphics::Canvas::canvasElementTypeToString);
    }
};