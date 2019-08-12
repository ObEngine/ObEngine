#include <bitset>
#include <codecvt>

#include <sfe/RichText.hpp>
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Network/TcpSocket.hpp>

#include <Bindings/Bindings.hpp>
#include <Bindings/SFMLBindings.hpp>
#include <SFML/System/Time.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::SFMLBindings
{
    void LoadSfColor(kaguya::State* lua)
    {
        (*lua)["SFML"]["Color"].setClass(kaguya::UserdataMetatable<sf::Color>()
            .setConstructors<sf::Color(), sf::Color(int, int, int), sf::Color(int, int, int, int)>()
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

    void LoadSfGlsl(kaguya::State* lua)
    {
        (*lua)["GLSL"] = kaguya::NewTable();

        /*(*lua)["GLSL"]["Vec2"].setClass(kaguya::UserdataMetatable<sf::Glsl::Vec2>()
            .setConstructors<sf::Glsl::Vec2(), sf::Glsl::Vec2(float, float)>()
            .addProperty("x", &sf::Glsl::Vec2::x)
            .addProperty("y", &sf::Glsl::Vec2::y)
        );*/

        (*lua)["GLSL"]["Vec3"].setClass(kaguya::UserdataMetatable<sf::Glsl::Vec3>()
            .setConstructors<sf::Glsl::Vec3(), sf::Glsl::Vec3(float, float, float)>()
            .addProperty("x", &sf::Glsl::Vec3::x)
            .addProperty("y", &sf::Glsl::Vec3::y)
            .addProperty("z", &sf::Glsl::Vec3::z)
        );

        (*lua)["GLSL"]["Vec4"].setClass(kaguya::UserdataMetatable<sf::Glsl::Vec4>()
            .setConstructors<sf::Glsl::Vec4(), sf::Glsl::Vec4(float, float, float, float)>()
            .addProperty("x", &sf::Glsl::Vec4::x)
            .addProperty("y", &sf::Glsl::Vec4::y)
            .addProperty("z", &sf::Glsl::Vec4::z)
            .addProperty("w", &sf::Glsl::Vec4::w)
        );

        (*lua)["GLSL"]["Bvec2"].setClass(kaguya::UserdataMetatable<sf::Glsl::Bvec2>()
            .setConstructors<sf::Glsl::Bvec2(), sf::Glsl::Bvec2(bool, bool)>()
            .addProperty("x", &sf::Glsl::Bvec2::x)
            .addProperty("y", &sf::Glsl::Bvec2::y)
        );

        (*lua)["GLSL"]["Bvec3"].setClass(kaguya::UserdataMetatable<sf::Glsl::Bvec3>()
            .setConstructors<sf::Glsl::Bvec3(), sf::Glsl::Bvec3(bool, bool, bool)>()
            .addProperty("x", &sf::Glsl::Bvec3::x)
            .addProperty("y", &sf::Glsl::Bvec3::y)
            .addProperty("z", &sf::Glsl::Bvec3::z)
        );

        (*lua)["GLSL"]["Bvec4"].setClass(kaguya::UserdataMetatable<sf::Glsl::Bvec4>()
            .setConstructors<sf::Glsl::Bvec4(), sf::Glsl::Bvec4(bool, bool, bool, bool)>()
            .addProperty("x", &sf::Glsl::Bvec4::x)
            .addProperty("y", &sf::Glsl::Bvec4::y)
            .addProperty("z", &sf::Glsl::Bvec4::z)
            .addProperty("w", &sf::Glsl::Bvec4::w)
        );

        (*lua)["GLSL"]["Ivec2"].setClass(kaguya::UserdataMetatable<sf::Glsl::Ivec2>()
            .setConstructors<sf::Glsl::Ivec2(), sf::Glsl::Ivec2(int, int)>()
            .addProperty("x", &sf::Glsl::Ivec2::x)
            .addProperty("y", &sf::Glsl::Ivec2::y)
        );

        (*lua)["GLSL"]["Ivec3"].setClass(kaguya::UserdataMetatable<sf::Glsl::Ivec3>()
            .setConstructors<sf::Glsl::Ivec3(), sf::Glsl::Ivec3(int, int, int)>()
            .addProperty("x", &sf::Glsl::Ivec3::x)
            .addProperty("y", &sf::Glsl::Ivec3::y)
            .addProperty("z", &sf::Glsl::Ivec3::z)
        );

        (*lua)["GLSL"]["Ivec4"].setClass(kaguya::UserdataMetatable<sf::Glsl::Ivec4>()
            .setConstructors<sf::Glsl::Ivec4(), sf::Glsl::Ivec4(int, int, int, int)>()
            .addProperty("x", &sf::Glsl::Ivec4::x)
            .addProperty("y", &sf::Glsl::Ivec4::y)
            .addProperty("z", &sf::Glsl::Ivec4::z)
            .addProperty("w", &sf::Glsl::Ivec4::w)
        );
    }

    void LoadSfRect(kaguya::State* lua)
    {
        (*lua)["SFML"]["FloatRect"].setClass(kaguya::UserdataMetatable<sf::FloatRect>()
            .setConstructors<sf::FloatRect(), sf::FloatRect(float, float, float, float)>()
            .addProperty("left", &sf::FloatRect::left)
            .addProperty("top", &sf::FloatRect::top)
            .addProperty("width", &sf::FloatRect::width)
            .addProperty("height", &sf::FloatRect::height)
        );
    }

    std::wstring toUtf8WString(const std::string& input)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(input.c_str());
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

    void LoadSfTcpSocket(kaguya::State* lua)
    {
        /*(*lua)["SFML"]["TcpSocket"].setClass(kaguya::UserdataMetatable<sf::TcpSocket>()
            .addFunction("connect", &sf::TcpSocket::connect)
            .addFunction("disconnect", &sf::TcpSocket::disconnect)
            .addFunction("getLocalPort", &sf::TcpSocket::getLocalPort)
            .addFunction("getRemoteAddress", &sf::TcpSocket::getRemoteAddress)
            .addFunction("getRemotePort", &sf::TcpSocket::getRemotePort)
            .addFunction("isBlocking", &sf::TcpSocket::isBlocking)
            //.addFunction("receive", &sf::TcpSocket::receive)
            //.addFunction("send", &sf::TcpSocket::send)
            .addFunction("setBlocking", &sf::TcpSocket::setBlocking)
        );*/
    }

    KAGUYA_MEMBER_FUNCTION_OVERLOADS(SFML_String_toAnsiString_wrapper, sf::String, toAnsiString, 0, 1);
    void LoadSfText(kaguya::State* lua)
    {
        Load(lua, "SFML.Transformable");

        (*lua)["SFML"]["String"].setClass(kaguya::UserdataMetatable<sf::String>()
            .setConstructors<sf::String(), sf::String(const std::string&)>()
            .addFunction("toAnsiString", SFML_String_toAnsiString_wrapper())
        );

        (*lua)["SFML"]["WString"] = kaguya::function([](std::string bob){
            return sf::String(toUtf8WString(bob));
        });

        (*lua)["SFML"]["Text"].setClass(kaguya::UserdataMetatable<sf::Text, kaguya::MultipleBase<sf::Drawable, sf::Transformable>>()
            .setConstructors<sf::Text(), 
                                sf::Text(const sf::String&, const sf::Font&), 
                                sf::Text(const sf::String&, const sf::Font&, unsigned int characterSize)>()
            .addFunction("setString", &sf::Text::setString)
            .addFunction("setFont", &sf::Text::setFont)
            .addFunction("setCharacterSize", &sf::Text::setCharacterSize)
            .addFunction("setStyle", &sf::Text::setStyle)
            .addFunction("setFillColor", &sf::Text::setFillColor)
            .addFunction("setOutlineColor", &sf::Text::setOutlineColor)
            .addFunction("setOutlineThickness", &sf::Text::setOutlineThickness)
            .addFunction("getString", &sf::Text::getString)
            .addFunction("getFont", &sf::Text::getFont)
            .addFunction("getCharacterSize", &sf::Text::getCharacterSize)
            .addFunction("getStyle", &sf::Text::getStyle)
            .addFunction("getFillColor", &sf::Text::getFillColor)
            .addFunction("getOutlineColor", &sf::Text::getOutlineColor)
            .addFunction("getOutlineThickness", &sf::Text::getOutlineThickness)
            .addFunction("findCharacterPos", &sf::Text::findCharacterPos)
        );

        (*lua)["SFML"]["RichLine"].setClass(kaguya::UserdataMetatable<sfe::RichText::Line, kaguya::MultipleBase<sf::Drawable, sf::Transformable>>()
            .addFunction("appendText", &sfe::RichText::Line::appendText)
            .addFunction("getGlobalBounds", &sfe::RichText::Line::getGlobalBounds)
            .addFunction("getTexts", &sfe::RichText::Line::getTexts)
            .addFunction("setCharacterSize", &sfe::RichText::Line::setCharacterSize)
            .addFunction("setFont", &sfe::RichText::Line::setFont)
        );

        (*lua)["SFML"]["RichText"].setClass(kaguya::UserdataMetatable<sfe::RichText, kaguya::MultipleBase<sf::Drawable, sf::Transformable>>()
            .setConstructors<sfe::RichText(), sfe::RichText(const sf::Font&)>()
            .addFunction("pushFillColor", &sfe::RichText::pushFillColor)
            .addFunction("pushOutlineColor", &sfe::RichText::pushOutlineColor)
            .addFunction("pushOutlineThickness", &sfe::RichText::pushOutlineThickness)
            .addFunction("pushString", &sfe::RichText::pushString)
            .addFunction("pushStyle", &sfe::RichText::pushStyle)
            .addFunction("setCharacterSize", &sfe::RichText::setCharacterSize)
            .addFunction("getCharacterSize", &sfe::RichText::getCharacterSize)
            .addFunction("setFont", &sfe::RichText::setFont)
            .addFunction("getFont", &sfe::RichText::getFont)
            .addFunction("clear", &sfe::RichText::clear)
            .addFunction("getLocalBounds", &sfe::RichText::getLocalBounds)
            .addFunction("getGlobalBounds", &sfe::RichText::getGlobalBounds)
            .addFunction("getLines", &sfe::RichText::getLines)
        );

        (*lua)["SFML"]["RichText"]["getOutlineColor"] = kaguya::function([](sfe::RichText* text)
        {
            if (text->getLines().size() > 0 && text->getLines().back().getTexts().size() > 0)
                return text->getLines().back().getTexts().back().getOutlineColor();
            else
                return sf::Color::White;
        });
        (*lua)["SFML"]["RichText"]["getFillColor"] = kaguya::function([](sfe::RichText* text)
        {
            if (text->getLines().size() > 0 && text->getLines().back().getTexts().size() > 0)
                return text->getLines().back().getTexts().back().getFillColor();
            else
                return sf::Color::White;
        });
        (*lua)["SFML"]["RichText"]["getOutlineThickness"] = kaguya::function([](sfe::RichText* text)
        {
            if (text->getLines().size() > 0 && text->getLines().back().getTexts().size() > 0)
                return text->getLines().back().getTexts().back().getOutlineThickness();
            else
                return 0.f;
        });

        (*lua)["SFML"]["Style"] = kaguya::NewTable();
        (*lua)["SFML"]["Style"]["Regular"] = sf::Text::Style::Regular;
        (*lua)["SFML"]["Style"]["Bold"] = sf::Text::Style::Bold;
        (*lua)["SFML"]["Style"]["Italic"] = sf::Text::Style::Italic;
        (*lua)["SFML"]["Style"]["StrikeThrough"] = sf::Text::Style::StrikeThrough;
        (*lua)["SFML"]["Style"]["Underlined"] = sf::Text::Style::Underlined;
    }

    void LoadSfTexture(kaguya::State * lua)
    {
        (*lua)["SFML"]["Texture"].setClass(kaguya::UserdataMetatable<sf::Texture>()
            .addFunction("getSize", &sf::Texture::getSize)
            .addFunction("isRepeated", &sf::Texture::isRepeated)
            .addFunction("isSmooth", &sf::Texture::isSmooth)
            .addFunction("loadFromFile", &sf::Texture::loadFromFile)
            .addFunction("setRepeated", &sf::Texture::setRepeated)
            .addFunction("setSmooth", &sf::Texture::setSmooth)
        );
    }

    void LoadSfTime(kaguya::State* lua)
    {
        (*lua)["SFML"]["Time"].setClass(kaguya::UserdataMetatable<sf::Time>()
            .setConstructors<sf::Time()>()
            .addFunction("asMicroseconds", &sf::Time::asMicroseconds)
            .addFunction("asMilliseconds", &sf::Time::asMilliseconds)
            .addFunction("asSeconds", &sf::Time::asSeconds)
            .addStaticField("Zero", &sf::Time::Zero)
        );
        (*lua)["SFML"]["Time"]["Seconds"] = kaguya::function([](float seconds)
        {
            return std::move(sf::seconds(seconds));
        });
        (*lua)["SFML"]["Time"]["Milliseconds"] = kaguya::function([](sf::Int32 milliseconds)
        {
            return std::move(sf::milliseconds(milliseconds));
        });
        (*lua)["SFML"]["Time"]["Microseconds"] = kaguya::function([](sf::Int64 microseconds)
        {
            return std::move(sf::microseconds(microseconds));
        });
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

    void LoadSfVector(kaguya::State* lua)
    {
        (*lua)["SFML"]["Vector2f"].setClass(kaguya::UserdataMetatable<sf::Vector2f>()
            .setConstructors<sf::Vector2f(), sf::Vector2f(float, float)>()
            .addProperty("x", &sf::Vector2f::x)
            .addProperty("y", &sf::Vector2f::y)
        );

        (*lua)["SFML"]["Vector2u"].setClass(kaguya::UserdataMetatable<sf::Vector2u>()
            .setConstructors<sf::Vector2u(), sf::Vector2u(unsigned int, unsigned int)>()
            .addProperty("x", &sf::Vector2u::x)
            .addProperty("y", &sf::Vector2u::y)
        );
    }
}
