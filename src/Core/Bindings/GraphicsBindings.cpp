#include <Bindings/Bindings.hpp>
#include <Bindings/GraphicsBindings.hpp>
#include <Graphics/Canvas.hpp>
#include <Graphics/Color.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Graphics/Sprite.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::GraphicsBindings
{
    void LoadSpriteHandlePoint(kaguya::State* lua)
    {
        (*lua)["obe"]["SpriteHandlePoint"].setClass(
            kaguya::UserdataMetatable<Graphics::SpriteHandlePoint>()
                .addFunction("getRect", &Graphics::SpriteHandlePoint::getRect)
                .addFunction(
                    "getReferential", &Graphics::SpriteHandlePoint::getReferential)
                .addFunction("moveTo", &Graphics::SpriteHandlePoint::moveTo));
    }

    void LoadSprite(kaguya::State* lua)
    {
        Load(lua, "obe.UnitBasedObject");
        Load(lua, "obe.Selectable");
        Load(lua, "obe.Serializable");
        Load(lua, "obe.Rect");
        Load(lua, "obe.Identifiable");
        (*lua)["obe"]["Sprite"].setClass(
            kaguya::UserdataMetatable<Graphics::Sprite,
                kaguya::MultipleBase<Transform::UnitBasedObject, Types::Selectable,
                    Transform::Rect, Types::Serializable, Types::Identifiable>>()
                .addFunction("drawHandle", &Graphics::Sprite::drawHandle)
                .addFunction("getColor", &Graphics::Sprite::getColor)
                .addFunction("getHandlePoint", &Graphics::Sprite::getHandlePoint)
                .addFunction("getLayer", &Graphics::Sprite::getLayer)
                .addFunction("getParentId", &Graphics::Sprite::getParentId)
                .addFunction("getPath", &Graphics::Sprite::getPath)
                .addFunction(
                    "getPositionTransformer", &Graphics::Sprite::getPositionTransformer)
                .addFunction("getRect", &Graphics::Sprite::getRect)
                .addFunction("getShader", &Graphics::Sprite::getShader)
                .addFunction("getSprite", &Graphics::Sprite::getSprite)
                .addFunction("getSpriteHeight", &Graphics::Sprite::getSpriteHeight)
                .addFunction("getSpriteWidth", &Graphics::Sprite::getSpriteWidth)
                //.addFunction("getTexture", &Graphics::Sprite::getTexture)
                .addFunction("getXScaleFactor", &Graphics::Sprite::getXScaleFactor)
                .addFunction("getYScaleFactor", &Graphics::Sprite::getYScaleFactor)
                .addFunction("getZDepth", &Graphics::Sprite::getZDepth)
                .addFunction("getAntiAliasing", &Graphics::Sprite::getAntiAliasing)
                .addFunction("hasShader", &Graphics::Sprite::hasShader)
                .addFunction("isVisible", &Graphics::Sprite::isVisible)
                .addFunction("loadTexture", &Graphics::Sprite::loadTexture)
                .addFunction("rotate", &Graphics::Sprite::rotate)
                .addFunction("setColor", &Graphics::Sprite::setColor)
                .addFunction("setLayer", &Graphics::Sprite::setLayer)
                .addFunction("setParentId", &Graphics::Sprite::setParentId)
                .addFunction(
                    "setPositionTransformer", &Graphics::Sprite::setPositionTransformer)
                .addFunction("setRotation", &Graphics::Sprite::setRotation)
                .addFunction("setRotationOrigin", &Graphics::Sprite::setRotationOrigin)
                .addFunction("setScalingOrigin", &Graphics::Sprite::setScalingOrigin)
                .addFunction("setShader", &Graphics::Sprite::setShader)
                .addFunction("setTexture", &Graphics::Sprite::setTexture)
                .addFunction("setTextureRect", &Graphics::Sprite::setTextureRect)
                .addFunction(
                    "setTranslationOrigin", &Graphics::Sprite::setTranslationOrigin)
                .addFunction("setVisible", &Graphics::Sprite::setVisible)
                .addFunction("setZDepth", &Graphics::Sprite::setZDepth)
                .addFunction("setAntiAliasing", &Graphics::Sprite::setAntiAliasing)
                .addFunction("useTextureSize", &Graphics::Sprite::useTextureSize));

        (*lua)["obe"]["Sprite"]["getTexture"] = kaguya::function(
            [](Graphics::Sprite* sprite) { return &sprite->getTexture(); });
    }

    void LoadResourceManager(kaguya::State* lua)
    {
        (*lua)["obe"]["ResourceManager"].setClass(
            kaguya::UserdataMetatable<Graphics::ResourceManager>()
                .addOverloadedFunctions("getTexture",
                    static_cast<sf::Texture* (
                        Graphics::ResourceManager::*)(const std::string&)>(
                        &Graphics::ResourceManager::getTexture),
                    static_cast<sf::Texture* (
                        Graphics::ResourceManager::*)(const std::string&, bool)>(
                        &Graphics::ResourceManager::getTexture))
                .addFunction("getFont", &Graphics::ResourceManager::getFont));
    }

    void LoadCanvas(kaguya::State* lua)
    {
        Load(lua, "obe.UnitVector");
        Load(lua, "SFML.Color");
        (*lua)["obe"]["Canvas"] = kaguya::NewTable();
        (*lua)["obe"]["Canvas"]["CanvasElement"].setClass(
            kaguya::UserdataMetatable<Graphics::Canvas::CanvasElement,
                Types::ProtectedIdentifiable>()
                .addProperty("layer", &Graphics::Canvas::CanvasElement::layer)
                .addProperty("visible", &Graphics::Canvas::CanvasElement::visible)
                .addFunction("setLayer", &Graphics::Canvas::CanvasElement::setLayer));
        (*lua)["obe"]["Canvas"]["CanvasShape"].setClass(
            kaguya::UserdataMetatable<Graphics::Canvas::CanvasPositionable>().addProperty(
                "position", &Graphics::Canvas::CanvasPositionable::position));
        (*lua)["obe"]["Canvas"]["Line"].setClass(
            kaguya::UserdataMetatable<Graphics::Canvas::Line,
                Graphics::Canvas::CanvasElement>()
                .addProperty("p1", &Graphics::Canvas::Line::p1)
                .addProperty("p2", &Graphics::Canvas::Line::p2)
                .addProperty("thickness", &Graphics::Canvas::Line::thickness)
                .addProperty("p1color", &Graphics::Canvas::Line::p1color)
                .addProperty("p2color", &Graphics::Canvas::Line::p2color));
        (*lua)["obe"]["Canvas"]["Rectangle"].setClass(
            kaguya::UserdataMetatable<Graphics::Canvas::Rectangle,
                kaguya::MultipleBase<Graphics::Canvas::CanvasElement,
                    Graphics::Canvas::CanvasPositionable>>()
                .addProperty("shape", &Graphics::Canvas::Rectangle::shape)
                .addProperty("size", &Graphics::Canvas::Rectangle::size));
        (*lua)["obe"]["Canvas"]["Text"].setClass(
            kaguya::UserdataMetatable<Graphics::Canvas::Text,
                kaguya::MultipleBase<Graphics::Canvas::CanvasElement,
                    Graphics::Canvas::CanvasPositionable>>()
                .addProperty("fontPath", &Graphics::Canvas::Text::fontPath)
                .addProperty("shape", &Graphics::Canvas::Text::shape)
                .addProperty("h_align", &Graphics::Canvas::Text::h_align)
                .addProperty("v_align", &Graphics::Canvas::Text::v_align));
        (*lua)["obe"]["Canvas"]["Circle"].setClass(
            kaguya::UserdataMetatable<Graphics::Canvas::Circle,
                kaguya::MultipleBase<Graphics::Canvas::CanvasElement,
                    Graphics::Canvas::CanvasPositionable>>()
                .addProperty("shape", &Graphics::Canvas::Circle::shape)
                .addProperty("radius", &Graphics::Canvas::Circle::radius));
        (*lua)["obe"]["Canvas"]["Sprite"].setClass(
            kaguya::UserdataMetatable<Graphics::Canvas::Image,
                kaguya::MultipleBase<Graphics::Canvas::CanvasElement,
                    Graphics::Canvas::CanvasPositionable>>()
                .addProperty("path", &Graphics::Canvas::Image::path)
                .addProperty("sprite", &Graphics::Canvas::Image::sprite));
        (*lua)["obe"]["Canvas"]["InternalCanvas"].setClass(
            kaguya::UserdataMetatable<Graphics::Canvas::Canvas>()
                .setConstructors<Graphics::Canvas::Canvas(unsigned int, unsigned int)>()
                .addFunction(
                    "Line", &Graphics::Canvas::Canvas::add<Graphics::Canvas::Line>)
                .addFunction("Rectangle",
                    &Graphics::Canvas::Canvas::add<Graphics::Canvas::Rectangle>)
                .addFunction(
                    "Text", &Graphics::Canvas::Canvas::add<Graphics::Canvas::Text>)
                .addFunction(
                    "Circle", &Graphics::Canvas::Canvas::add<Graphics::Canvas::Circle>)
                .addFunction(
                    "Image", &Graphics::Canvas::Canvas::add<Graphics::Canvas::Image>)
                .addFunction("render", &Graphics::Canvas::Canvas::render)
                .addFunction("setTarget", &Graphics::Canvas::Canvas::setTarget)
                .addFunction("clear", &Graphics::Canvas::Canvas::clear)
                .addFunction("remove", &Graphics::Canvas::Canvas::remove)
                .addFunction("get", &Graphics::Canvas::Canvas::get));

        (*lua)["obe"]["Canvas"]["Alignment"] = kaguya::NewTable();
        (*lua)["obe"]["Canvas"]["Alignment"]["Horizontal"] = kaguya::NewTable();
        (*lua)["obe"]["Canvas"]["Alignment"]["Horizontal"]["Left"]
            = Graphics::Canvas::TextHorizontalAlign::Left;
        (*lua)["obe"]["Canvas"]["Alignment"]["Horizontal"]["Center"]
            = Graphics::Canvas::TextHorizontalAlign::Center;
        (*lua)["obe"]["Canvas"]["Alignment"]["Horizontal"]["Right"]
            = Graphics::Canvas::TextHorizontalAlign::Right;
        (*lua)["obe"]["Canvas"]["Alignment"]["Vertical"] = kaguya::NewTable();
        (*lua)["obe"]["Canvas"]["Alignment"]["Vertical"]["Top"]
            = Graphics::Canvas::TextVerticalAlign::Top;
        (*lua)["obe"]["Canvas"]["Alignment"]["Vertical"]["Center"]
            = Graphics::Canvas::TextVerticalAlign::Center;
        (*lua)["obe"]["Canvas"]["Alignment"]["Vertical"]["Bottom"]
            = Graphics::Canvas::TextVerticalAlign::Bottom;

        System::Path("Lib/Internal/Canvas.lua")
            .load(System::Loaders::luaLoader, Script::ScriptEngine);
    }

    void LoadGraphicsUtils(kaguya::State* lua)
    {
        (*lua)["obe"]["SetClearColor"] = kaguya::function(
            [](sf::Color newColor) { Graphics::Utils::ClearColor = newColor; });
    }

    void LoadShader(kaguya::State* lua)
    {
        (*lua)["obe"]["Shader"].setClass(
            kaguya::UserdataMetatable<Graphics::Shader>()
                .setConstructors<Graphics::Shader(),
                    Graphics::Shader(const std::string&)>()
                .addFunction("loadShader", &Graphics::Shader::loadShader)
                .addOverloadedFunctions("setUniform",
                    static_cast<void (Graphics::Shader::*)(const std::string&, float)>(
                        &Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&, int)>(
                        &Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&, bool)>(
                        &Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&,
                        const sf::Texture&)>(&Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&,
                        const sf::Glsl::Vec2&)>(&Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&,
                        const sf::Glsl::Vec3&)>(&Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&,
                        const sf::Glsl::Vec4&)>(&Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&,
                        const sf::Glsl::Ivec2&)>(&Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&,
                        const sf::Glsl::Ivec3&)>(&Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&,
                        const sf::Glsl::Ivec4&)>(&Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&,
                        const sf::Glsl::Bvec2&)>(&Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&,
                        const sf::Glsl::Bvec3&)>(&Graphics::Shader::setUniform),
                    static_cast<void (Graphics::Shader::*)(const std::string&,
                        const sf::Glsl::Bvec4&)>(&Graphics::Shader::setUniform)));
    }

    KAGUYA_MEMBER_FUNCTION_OVERLOADS(
        Color_fromRgb_wrapper, Graphics::Color, fromRgb, 3, 4);
    void LoadColor(kaguya::State* lua)
    {
        (*lua)["obe"]["Color"].setClass(
            kaguya::UserdataMetatable<Graphics::Color, sf::Color>()
                .setConstructors<Graphics::Color(
                                     uint_fast8_t, uint_fast8_t, uint_fast8_t),
                    Graphics::Color(
                        uint_fast8_t, uint_fast8_t, uint_fast8_t, uint_fast8_t),
                    Graphics::Color(std::string)>()
                .addFunction("fromHex", &Graphics::Color::fromHex)
                .addFunction("fromRgb", Color_fromRgb_wrapper()));
    }
} // namespace obe::Bindings::GraphicsBindings