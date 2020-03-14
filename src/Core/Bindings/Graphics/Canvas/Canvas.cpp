#include <Bindings/Graphics/Canvas/Canvas.hpp>

#include <Graphics/Canvas.hpp>
#include <System/Path.hpp>

#include <sol/sol.hpp>

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
                { "Sprite", obe::Graphics::Canvas::CanvasElementType::Sprite } });
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
    void LoadClassCanvas(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Canvas> bindCanvas
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Canvas>("Canvas",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Canvas(
                    unsigned int, unsigned int)>());
        bindCanvas["get"] = &obe::Graphics::Canvas::Canvas::get;
        bindCanvas["render"] = &obe::Graphics::Canvas::Canvas::render;
        bindCanvas["clear"] = &obe::Graphics::Canvas::Canvas::clear;
        bindCanvas["remove"] = &obe::Graphics::Canvas::Canvas::remove;
        bindCanvas["getTexture"] = &obe::Graphics::Canvas::Canvas::getTexture;
        bindCanvas["requiresSort"] = &obe::Graphics::Canvas::Canvas::requiresSort;
        bindCanvas["Text"]
            = &obe::Graphics::Canvas::Canvas::add<obe::Graphics::Canvas::Text>;
        state.script_file("Lib/Internal/Canvas.lua"_fs);
    }
    void LoadClassCanvasElement(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::CanvasElement> bindCanvasElement
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::CanvasElement>(
                "CanvasElement");
        bindCanvasElement["draw"] = &obe::Graphics::Canvas::CanvasElement::draw;
        bindCanvasElement["setLayer"] = &obe::Graphics::Canvas::CanvasElement::setLayer;
        /*bindCanvasElement["parent"] = sol::property(
            [](obe::Graphics::Canvas::CanvasElement* self) { return self->parent; });*/
        bindCanvasElement["layer"] = &obe::Graphics::Canvas::CanvasElement::layer;
        bindCanvasElement["visible"] = &obe::Graphics::Canvas::CanvasElement::visible;
        bindCanvasElement["type"] = &obe::Graphics::Canvas::CanvasElement::type;
    }
    void LoadClassCanvasPositionable(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::CanvasPositionable> bindCanvasPositionable
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::CanvasPositionable>(
                "CanvasPositionable");
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
                    obe::Graphics::Canvas::Canvas&, const std::string&)>());
        bindCircle["draw"] = &obe::Graphics::Canvas::Circle::draw;
        bindCircle["shape"] = &obe::Graphics::Canvas::Circle::shape;
        bindCircle["radius"] = &obe::Graphics::Canvas::Circle::radius;
    }
    void LoadClassImage(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Image> bindImage
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Image>("Image",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Image(
                    obe::Graphics::Canvas::Canvas&, const std::string&)>());
        bindImage["draw"] = &obe::Graphics::Canvas::Image::draw;
        bindImage["path"] = &obe::Graphics::Canvas::Image::path;
        bindImage["sprite"] = &obe::Graphics::Canvas::Image::sprite;
    }
    void LoadClassLine(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Line> bindLine
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Line>("Line",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Line(
                    obe::Graphics::Canvas::Canvas&, const std::string&)>());
        bindLine["draw"] = &obe::Graphics::Canvas::Line::draw;
        bindLine["p1"] = &obe::Graphics::Canvas::Line::p1;
        bindLine["p2"] = &obe::Graphics::Canvas::Line::p2;
        bindLine["thickness"] = &obe::Graphics::Canvas::Line::thickness;
        bindLine["p1color"] = &obe::Graphics::Canvas::Line::p1color;
        bindLine["p2color"] = &obe::Graphics::Canvas::Line::p2color;
    }
    void LoadClassPolygon(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        /*sol::usertype<obe::Graphics::Canvas::Polygon> bindPolygon
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Polygon>(
                "Polygon", sol::call_constructor, sol::default_constructor);*/
    }
    void LoadClassRectangle(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Rectangle> bindRectangle
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Rectangle>("Rectangle",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Rectangle(
                    obe::Graphics::Canvas::Canvas&, const std::string&)>());
        bindRectangle["draw"] = &obe::Graphics::Canvas::Rectangle::draw;
        bindRectangle["shape"] = &obe::Graphics::Canvas::Rectangle::shape;
        bindRectangle["size"] = &obe::Graphics::Canvas::Rectangle::size;
    }
    void LoadClassText(sol::state_view state)
    {
        sol::table CanvasNamespace = state["obe"]["Graphics"]["Canvas"].get<sol::table>();
        sol::usertype<obe::Graphics::Canvas::Text> bindText
            = CanvasNamespace.new_usertype<obe::Graphics::Canvas::Text>("Text",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Canvas::Text(
                    obe::Graphics::Canvas::Canvas&, const std::string&)>());
        bindText["draw"] = &obe::Graphics::Canvas::Text::draw;
        bindText["fontPath"] = &obe::Graphics::Canvas::Text::fontPath;
        bindText["shape"] = &obe::Graphics::Canvas::Text::shape;
        bindText["h_align"] = &obe::Graphics::Canvas::Text::h_align;
        bindText["v_align"] = &obe::Graphics::Canvas::Text::v_align;
    }
};