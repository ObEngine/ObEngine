#include <Bindings/obe/Graphics/Shapes/Shapes.hpp>

#include <Graphics/Shapes.hpp>

#include <Bindings/Config.hpp>

namespace obe::Graphics::Shapes::Bindings
{
    void LoadClassCircle(sol::state_view state)
    {
        sol::table ShapesNamespace = state["obe"]["Graphics"]["Shapes"].get<sol::table>();
        sol::usertype<obe::Graphics::Shapes::Circle> bindCircle
            = ShapesNamespace.new_usertype<obe::Graphics::Shapes::Circle>("Circle",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Shapes::Circle(),
                    obe::Graphics::Shapes::Circle(const sf::CircleShape&),
                    obe::Graphics::Shapes::Circle(
                        const obe::Graphics::Shapes::Circle&)>(),
                sol::base_classes, sol::bases<obe::Graphics::Shapes::Shape<Circle>>());
        bindCircle["setTexture"] = &obe::Graphics::Shapes::Circle::setTexture;
        bindCircle["setTextureRect"] = &obe::Graphics::Shapes::Circle::setTextureRect;
        bindCircle["setPosition"] = &obe::Graphics::Shapes::Circle::setPosition;
        bindCircle["setFillColor"] = &obe::Graphics::Shapes::Circle::setFillColor;
        bindCircle["setOutlineColor"] = &obe::Graphics::Shapes::Circle::setOutlineColor;
        bindCircle["setOutlineThickness"]
            = &obe::Graphics::Shapes::Circle::setOutlineThickness;
        bindCircle["getFillColor"] = &obe::Graphics::Shapes::Circle::getFillColor;
        bindCircle["getOutlineColor"] = &obe::Graphics::Shapes::Circle::getOutlineColor;
        bindCircle["getOutlineThickness"]
            = &obe::Graphics::Shapes::Circle::getOutlineThickness;
        bindCircle["getPointCount"] = &obe::Graphics::Shapes::Circle::getPointCount;
        bindCircle["getPoint"] = &obe::Graphics::Shapes::Circle::getPoint;
        bindCircle["getLocalBounds"] = &obe::Graphics::Shapes::Circle::getLocalBounds;
        bindCircle["getGlobalBounds"] = &obe::Graphics::Shapes::Circle::getGlobalBounds;
        bindCircle["setRotation"] = &obe::Graphics::Shapes::Circle::setRotation;
        bindCircle["setScale"] = &obe::Graphics::Shapes::Circle::setScale;
        bindCircle["setOrigin"] = &obe::Graphics::Shapes::Circle::setOrigin;
        bindCircle["getPosition"] = &obe::Graphics::Shapes::Circle::getPosition;
        bindCircle["getRotation"] = &obe::Graphics::Shapes::Circle::getRotation;
        bindCircle["getScale"] = &obe::Graphics::Shapes::Circle::getScale;
        bindCircle["getOrigin"] = &obe::Graphics::Shapes::Circle::getOrigin;
        bindCircle["move"] = &obe::Graphics::Shapes::Circle::move;
        bindCircle["rotate"] = &obe::Graphics::Shapes::Circle::rotate;
        bindCircle["scale"] = &obe::Graphics::Shapes::Circle::scale;
        bindCircle["draw"] = &obe::Graphics::Shapes::Circle::draw;
        bindCircle["operator sf::CircleShape &"]
            = &obe::Graphics::Shapes::Circle::operator sf::CircleShape&;
        bindCircle["operator const sf::CircleShape &"]
            = &obe::Graphics::Shapes::Circle::operator const sf::CircleShape&;
        bindCircle["setRadius"] = &obe::Graphics::Shapes::Circle::setRadius;
        bindCircle["getRadius"] = &obe::Graphics::Shapes::Circle::getRadius;
        bindCircle["shape"] = &obe::Graphics::Shapes::Circle::shape;
    }
    void LoadClassPolygon(sol::state_view state)
    {
        sol::table ShapesNamespace = state["obe"]["Graphics"]["Shapes"].get<sol::table>();
        sol::usertype<obe::Graphics::Shapes::Polygon> bindPolygon
            = ShapesNamespace.new_usertype<obe::Graphics::Shapes::Polygon>("Polygon",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Shapes::Polygon(),
                    obe::Graphics::Shapes::Polygon(const sf::ConvexShape&),
                    obe::Graphics::Shapes::Polygon(
                        const obe::Graphics::Shapes::Polygon&)>(),
                sol::base_classes, sol::bases<obe::Graphics::Shapes::Shape<Polygon>>());
        bindPolygon["setTexture"] = &obe::Graphics::Shapes::Polygon::setTexture;
        bindPolygon["setTextureRect"] = &obe::Graphics::Shapes::Polygon::setTextureRect;
        bindPolygon["setPosition"] = &obe::Graphics::Shapes::Polygon::setPosition;
        bindPolygon["setFillColor"] = &obe::Graphics::Shapes::Polygon::setFillColor;
        bindPolygon["setOutlineColor"] = &obe::Graphics::Shapes::Polygon::setOutlineColor;
        bindPolygon["setOutlineThickness"]
            = &obe::Graphics::Shapes::Polygon::setOutlineThickness;
        bindPolygon["getFillColor"] = &obe::Graphics::Shapes::Polygon::getFillColor;
        bindPolygon["getOutlineColor"] = &obe::Graphics::Shapes::Polygon::getOutlineColor;
        bindPolygon["getOutlineThickness"]
            = &obe::Graphics::Shapes::Polygon::getOutlineThickness;
        bindPolygon["getPointCount"] = &obe::Graphics::Shapes::Polygon::getPointCount;
        bindPolygon["getPoint"] = &obe::Graphics::Shapes::Polygon::getPoint;
        bindPolygon["getLocalBounds"] = &obe::Graphics::Shapes::Polygon::getLocalBounds;
        bindPolygon["getGlobalBounds"] = &obe::Graphics::Shapes::Polygon::getGlobalBounds;
        bindPolygon["setRotation"] = &obe::Graphics::Shapes::Polygon::setRotation;
        bindPolygon["setScale"] = &obe::Graphics::Shapes::Polygon::setScale;
        bindPolygon["setOrigin"] = &obe::Graphics::Shapes::Polygon::setOrigin;
        bindPolygon["getPosition"] = &obe::Graphics::Shapes::Polygon::getPosition;
        bindPolygon["getRotation"] = &obe::Graphics::Shapes::Polygon::getRotation;
        bindPolygon["getScale"] = &obe::Graphics::Shapes::Polygon::getScale;
        bindPolygon["getOrigin"] = &obe::Graphics::Shapes::Polygon::getOrigin;
        bindPolygon["move"] = &obe::Graphics::Shapes::Polygon::move;
        bindPolygon["rotate"] = &obe::Graphics::Shapes::Polygon::rotate;
        bindPolygon["scale"] = &obe::Graphics::Shapes::Polygon::scale;
        bindPolygon["draw"] = &obe::Graphics::Shapes::Polygon::draw;
        bindPolygon["operator sf::ConvexShape &"]
            = &obe::Graphics::Shapes::Polygon::operator sf::ConvexShape&;
        bindPolygon["operator const sf::ConvexShape &"]
            = &obe::Graphics::Shapes::Polygon::operator const sf::ConvexShape&;
        bindPolygon["setPointPosition"]
            = &obe::Graphics::Shapes::Polygon::setPointPosition;
        bindPolygon["getPointPosition"]
            = &obe::Graphics::Shapes::Polygon::getPointPosition;
        bindPolygon["shape"] = &obe::Graphics::Shapes::Polygon::shape;
    }
    void LoadClassRectangle(sol::state_view state)
    {
        sol::table ShapesNamespace = state["obe"]["Graphics"]["Shapes"].get<sol::table>();
        sol::usertype<obe::Graphics::Shapes::Rectangle> bindRectangle
            = ShapesNamespace.new_usertype<obe::Graphics::Shapes::Rectangle>("Rectangle",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Shapes::Rectangle(),
                    obe::Graphics::Shapes::Rectangle(const sf::RectangleShape&),
                    obe::Graphics::Shapes::Rectangle(
                        const obe::Graphics::Shapes::Rectangle&)>(),
                sol::base_classes, sol::bases<obe::Graphics::Shapes::Shape<Rectangle>>());
        bindRectangle["setTexture"] = &obe::Graphics::Shapes::Rectangle::setTexture;
        bindRectangle["setTextureRect"]
            = &obe::Graphics::Shapes::Rectangle::setTextureRect;
        bindRectangle["setPosition"] = &obe::Graphics::Shapes::Rectangle::setPosition;
        bindRectangle["setFillColor"] = &obe::Graphics::Shapes::Rectangle::setFillColor;
        bindRectangle["setOutlineColor"]
            = &obe::Graphics::Shapes::Rectangle::setOutlineColor;
        bindRectangle["setOutlineThickness"]
            = &obe::Graphics::Shapes::Rectangle::setOutlineThickness;
        bindRectangle["getFillColor"] = &obe::Graphics::Shapes::Rectangle::getFillColor;
        bindRectangle["getOutlineColor"]
            = &obe::Graphics::Shapes::Rectangle::getOutlineColor;
        bindRectangle["getOutlineThickness"]
            = &obe::Graphics::Shapes::Rectangle::getOutlineThickness;
        bindRectangle["getPointCount"] = &obe::Graphics::Shapes::Rectangle::getPointCount;
        bindRectangle["getPoint"] = &obe::Graphics::Shapes::Rectangle::getPoint;
        bindRectangle["getLocalBounds"]
            = &obe::Graphics::Shapes::Rectangle::getLocalBounds;
        bindRectangle["getGlobalBounds"]
            = &obe::Graphics::Shapes::Rectangle::getGlobalBounds;
        bindRectangle["setRotation"] = &obe::Graphics::Shapes::Rectangle::setRotation;
        bindRectangle["setScale"] = &obe::Graphics::Shapes::Rectangle::setScale;
        bindRectangle["setOrigin"] = &obe::Graphics::Shapes::Rectangle::setOrigin;
        bindRectangle["getPosition"] = &obe::Graphics::Shapes::Rectangle::getPosition;
        bindRectangle["getRotation"] = &obe::Graphics::Shapes::Rectangle::getRotation;
        bindRectangle["getScale"] = &obe::Graphics::Shapes::Rectangle::getScale;
        bindRectangle["getOrigin"] = &obe::Graphics::Shapes::Rectangle::getOrigin;
        bindRectangle["move"] = &obe::Graphics::Shapes::Rectangle::move;
        bindRectangle["rotate"] = &obe::Graphics::Shapes::Rectangle::rotate;
        bindRectangle["scale"] = &obe::Graphics::Shapes::Rectangle::scale;
        bindRectangle["draw"] = &obe::Graphics::Shapes::Rectangle::draw;
        bindRectangle["getSize"] = &obe::Graphics::Shapes::Rectangle::getSize;
        bindRectangle["setSize"] = &obe::Graphics::Shapes::Rectangle::setSize;
        bindRectangle["operator sf::RectangleShape &"]
            = &obe::Graphics::Shapes::Rectangle::operator sf::RectangleShape&;
        bindRectangle["operator const sf::RectangleShape &"]
            = &obe::Graphics::Shapes::Rectangle::operator const sf::RectangleShape&;
        bindRectangle["shape"] = &obe::Graphics::Shapes::Rectangle::shape;
    }
    void LoadClassText(sol::state_view state)
    {
        sol::table ShapesNamespace = state["obe"]["Graphics"]["Shapes"].get<sol::table>();
        sol::usertype<obe::Graphics::Shapes::Text> bindText
            = ShapesNamespace.new_usertype<obe::Graphics::Shapes::Text>("Text",
                sol::call_constructor,
                sol::constructors<obe::Graphics::Shapes::Text(),
                    obe::Graphics::Shapes::Text(const obe::Graphics::RichText&),
                    obe::Graphics::Shapes::Text(const obe::Graphics::Shapes::Text&)>(),
                sol::base_classes, sol::bases<obe::Graphics::Shapes::BaseShape<Text>>());
        bindText["setPosition"] = &obe::Graphics::Shapes::Text::setPosition;
        bindText["getLocalBounds"] = &obe::Graphics::Shapes::Text::getLocalBounds;
        bindText["getGlobalBounds"] = &obe::Graphics::Shapes::Text::getGlobalBounds;
        bindText["setRotation"] = &obe::Graphics::Shapes::Text::setRotation;
        bindText["setScale"] = &obe::Graphics::Shapes::Text::setScale;
        bindText["setOrigin"] = &obe::Graphics::Shapes::Text::setOrigin;
        bindText["getPosition"] = &obe::Graphics::Shapes::Text::getPosition;
        bindText["getRotation"] = &obe::Graphics::Shapes::Text::getRotation;
        bindText["getScale"] = &obe::Graphics::Shapes::Text::getScale;
        bindText["getOrigin"] = &obe::Graphics::Shapes::Text::getOrigin;
        bindText["move"] = &obe::Graphics::Shapes::Text::move;
        bindText["rotate"] = &obe::Graphics::Shapes::Text::rotate;
        bindText["scale"] = &obe::Graphics::Shapes::Text::scale;
        bindText["draw"] = &obe::Graphics::Shapes::Text::draw;
        bindText["operator RichText &"]
            = &obe::Graphics::Shapes::Text::operator RichText&;
        bindText["operator const RichText &"]
            = &obe::Graphics::Shapes::Text::operator const RichText&;
        bindText["clear"] = &obe::Graphics::Shapes::Text::clear;
        bindText["append"] = &obe::Graphics::Shapes::Text::append;
        bindText["getFont"] = &obe::Graphics::Shapes::Text::getFont;
        bindText["setFont"] = &obe::Graphics::Shapes::Text::setFont;
        bindText["getCharacterSize"] = &obe::Graphics::Shapes::Text::getCharacterSize;
        bindText["setCharacterSize"] = &obe::Graphics::Shapes::Text::setCharacterSize;
        bindText["shape"] = &obe::Graphics::Shapes::Text::shape;
    }
};