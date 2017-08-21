#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <Bindings/SFMLBindings.hpp>
#include "Bindings/Bindings.hpp"

namespace obe
{
    namespace Bindings
    {
        namespace SFMLBindings
        {
            void LoadSfColor(kaguya::State* lua)
            {
                (*lua)["SFML"]["Color"].setClass(kaguya::UserdataMetatable<sf::Color>()
                    .setConstructors<sf::Color(int, int, int, int), sf::Color(int, int, int)>()
                    .addProperty("r", &sf::Color::r)
                    .addProperty("g", &sf::Color::g)
                    .addProperty("b", &sf::Color::b)
                    .addProperty("a", &sf::Color::a)
                    .addFunction("toInteger", &sf::Color::toInteger)
                    .addStaticField("Black", &sf::Color::Black)
                    .addStaticField("Blue", &sf::Color::Blue)
                    .addStaticField("Cyan", &sf::Color::Cyan)
                    .addStaticField("Green", &sf::Color::Green)
                    .addStaticField("Magenta", &sf::Color::Magenta)
                    .addStaticField("Red", &sf::Color::Red)
                    .addStaticField("Transparent", &sf::Color::Transparent)
                    .addStaticField("White", &sf::Color::White)
                    .addStaticField("Yellow", &sf::Color::Yellow)
                );
            }

            void LoadSfDrawable(kaguya::State* lua)
            {
                (*lua)["SFML"]["Drawable"].setClass(kaguya::UserdataMetatable<sf::Drawable>()
                );
            }

            void LoadSfFont(kaguya::State* lua)
            {
                //Wrapper pour Font Loader ? <REVISION>
                (*lua)["SFML"]["Font"].setClass(kaguya::UserdataMetatable<sf::Font>()
                    .setConstructors<sf::Font()>()
                    .addFunction("getGlyph", &sf::Font::getGlyph)
                    .addFunction("getInfo", &sf::Font::getInfo)
                    .addFunction("getKerning", &sf::Font::getKerning)
                    .addFunction("getLineSpacing", &sf::Font::getLineSpacing)
                    .addFunction("getTexture", &sf::Font::getTexture)
                    .addFunction("getUnderlinePosition", &sf::Font::getUnderlinePosition)
                    .addFunction("getUnderlineThickness", &sf::Font::getUnderlineThickness)
                    .addFunction("loadFromFile", &sf::Font::loadFromFile)
                );

                (*lua)["SFML"]["FontInfo"].setClass(kaguya::UserdataMetatable<sf::Font::Info>()
                    .addProperty("family", &sf::Font::Info::family)
                );
            }

            void LoadSfShape(kaguya::State* lua)
            {
                Load(lua, "SFML.Drawable");
                Load(lua, "SFML.Transformable");

                (*lua)["SFML"]["Shape"].setClass(kaguya::UserdataMetatable<sf::Shape, kaguya::MultipleBase<sf::Drawable, sf::Transformable>>()
                    .addFunction("getFillColor", &sf::Shape::getFillColor)
                    .addFunction("getGlobalBounds", &sf::Shape::getGlobalBounds)
                    .addFunction("getLocalBounds", &sf::Shape::getLocalBounds)
                    .addFunction("getOutlineColor", &sf::Shape::getOutlineColor)
                    .addFunction("getOutlineThickness", &sf::Shape::getOutlineThickness)
                    .addFunction("getPoint", &sf::Shape::getPoint)
                    .addFunction("getPointCount", &sf::Shape::getPointCount)
                    .addFunction("getTexture", &sf::Shape::getTexture)
                    .addFunction("getTextureRect", &sf::Shape::getTextureRect)
                    .addFunction("setFillColor", &sf::Shape::setFillColor)
                    .addFunction("setOutlineColor", &sf::Shape::setOutlineColor)
                    .addFunction("setOutlineThickness", &sf::Shape::setOutlineThickness)
                    .addFunction("setTexture", &sf::Shape::setTexture)
                    .addFunction("setTextureRect", &sf::Shape::setTextureRect)
                );

                (*lua)["SFML"]["CircleShape"].setClass(kaguya::UserdataMetatable<sf::CircleShape, sf::Shape>()
                    .setConstructors<sf::CircleShape(), sf::CircleShape(float), sf::CircleShape(float, unsigned int)>()
                    .addFunction("getPoint", &sf::CircleShape::getPoint)
                    .addFunction("getPointCount", &sf::CircleShape::getPointCount)
                    .addFunction("getRadius", &sf::CircleShape::getRadius)
                    .addFunction("setRadius", &sf::CircleShape::setRadius)
                );

                (*lua)["SFML"]["ConvexShape"].setClass(kaguya::UserdataMetatable<sf::ConvexShape, sf::Shape>()
                    .setConstructors<sf::ConvexShape(), sf::ConvexShape(unsigned int)>()
                    .addFunction("getPoint", &sf::ConvexShape::getPoint)
                    .addFunction("getPointCount", &sf::ConvexShape::getPointCount)
                    .addFunction("setPoint", &sf::ConvexShape::setPoint)
                    .addFunction("setPointCount", &sf::ConvexShape::setPointCount)
                );

                (*lua)["SFML"]["RectangleShape"].setClass(kaguya::UserdataMetatable<sf::RectangleShape, sf::Shape>()
                    .setConstructors<sf::RectangleShape(), sf::RectangleShape(const sf::Vector2f&)>()
                    .addFunction("getPoint", &sf::RectangleShape::getPoint)
                    .addFunction("getPointCount", &sf::RectangleShape::getPointCount)
                    .addFunction("getSize", &sf::RectangleShape::getSize)
                    .addFunction("setSize", &sf::RectangleShape::setSize)
                );
            }

            void LoadSfSprite(kaguya::State* lua)
            {
                Load(lua, "SFML.Drawable");
                Load(lua, "SFML.Transformable");

                (*lua)["SFML"]["Sprite"].setClass(kaguya::UserdataMetatable<sf::Sprite, kaguya::MultipleBase<sf::Drawable, sf::Transformable>>()
                    .setConstructors<sf::Sprite(), sf::Sprite(const sf::Texture&)>()
                    .addFunction("getColor", &sf::Sprite::getColor)
                    .addFunction("getGlobalBounds", &sf::Sprite::getGlobalBounds)
                    .addFunction("getLocalBounds", &sf::Sprite::getLocalBounds)
                    .addFunction("getTexture", &sf::Sprite::getTexture)
                    .addFunction("getTextureRect", &sf::Sprite::getTextureRect)
                    .addFunction("setColor", &sf::Sprite::setColor)
                    .addFunction("setTexture", &sf::Sprite::setTexture)
                    .addFunction("setTextureRect", &sf::Sprite::setTextureRect)
                );
            }

            void LoadSfTransformable(kaguya::State* lua)
            {
                (*lua)["SFML"]["Transformable"].setClass(kaguya::UserdataMetatable<sf::Transformable>()
                    .addFunction("getInverseTransform", &sf::Transformable::getInverseTransform)
                    .addFunction("getOrigin", &sf::Transformable::getOrigin)
                    .addFunction("getPosition", &sf::Transformable::getPosition)
                    .addFunction("getRotation", &sf::Transformable::getRotation)
                    .addFunction("getScale", &sf::Transformable::getScale)
                    .addFunction("getTransform", &sf::Transformable::getTransform)
                    .addOverloadedFunctions("move",
                        static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::move),
                        static_cast<void (sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::move)
                    )
                    .addFunction("rotate", &sf::Transformable::rotate)
                    .addOverloadedFunctions("scale",
                        static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::scale),
                        static_cast<void (sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::scale)
                    )
                    .addOverloadedFunctions("setOrigin",
                        static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::setOrigin),
                        static_cast<void (sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::setOrigin)
                    )
                    .addOverloadedFunctions("setPosition",
                        static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::setPosition),
                        static_cast<void (sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::setPosition)
                    )
                    .addFunction("setRotation", &sf::Transformable::setRotation)
                    .addOverloadedFunctions("setScale",
                        static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::setScale),
                        static_cast<void (sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::setScale)
                    )
                );
            }
        }
    }
}
