#include <Bindings/Bindings.hpp>
#include <Bindings/GraphicsBindings.hpp>
#include <Graphics/Canvas.hpp>
#include <Graphics/Color.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::GraphicsBindings
{
    void LoadLevelSpriteHandlePoint(kaguya::State* lua)
    {
        (*lua)["obe"]["LevelSpriteHandlePoint"].setClass(kaguya::UserdataMetatable<Graphics::LevelSpriteHandlePoint>()
            .addFunction("getRect", &Graphics::LevelSpriteHandlePoint::getRect)
            .addFunction("getReferential", &Graphics::LevelSpriteHandlePoint::getReferential)
            .addFunction("moveTo", &Graphics::LevelSpriteHandlePoint::moveTo)
        );
    }

    void LoadLevelSprite(kaguya::State* lua)
    {
        Load(lua, "obe.UnitBasedObject");
        Load(lua, "obe.Selectable");
        Load(lua, "obe.Serializable");
        Load(lua, "obe.Rect");
        Load(lua, "obe.Identifiable");
        (*lua)["obe"]["LevelSprite"].setClass(kaguya::UserdataMetatable<Graphics::LevelSprite,
            kaguya::MultipleBase<
                Transform::UnitBasedObject,
                Types::Selectable,
                Transform::Rect,
                Types::Serializable,
                Types::Identifiable
            >
            >()
            .addFunction("drawHandle", &Graphics::LevelSprite::drawHandle)
            .addFunction("getColor", &Graphics::LevelSprite::getColor)
            .addFunction("getHandlePoint", &Graphics::LevelSprite::getHandlePoint)
            .addFunction("getLayer", &Graphics::LevelSprite::getLayer)
            .addFunction("getParentId", &Graphics::LevelSprite::getParentId)
            .addFunction("getPath", &Graphics::LevelSprite::getPath)
            .addFunction("getPositionTransformer", &Graphics::LevelSprite::getPositionTransformer)
            .addFunction("getRect", &Graphics::LevelSprite::getRect)
            .addFunction("getShader", &Graphics::LevelSprite::getShader)
            .addFunction("getSprite", &Graphics::LevelSprite::getSprite)
            .addFunction("getSpriteHeight", &Graphics::LevelSprite::getSpriteHeight)
            .addFunction("getSpriteWidth", &Graphics::LevelSprite::getSpriteWidth)
            //.addFunction("getTexture", &Graphics::LevelSprite::getTexture)
            .addFunction("getXScaleFactor", &Graphics::LevelSprite::getXScaleFactor)
            .addFunction("getYScaleFactor", &Graphics::LevelSprite::getYScaleFactor)
            .addFunction("getZDepth", &Graphics::LevelSprite::getZDepth)
            .addFunction("hasShader", &Graphics::LevelSprite::hasShader)
            .addFunction("isVisible", &Graphics::LevelSprite::isVisible)
            .addFunction("loadTexture", &Graphics::LevelSprite::loadTexture)
            .addFunction("rotate", &Graphics::LevelSprite::rotate)
            .addFunction("setColor", &Graphics::LevelSprite::setColor)
            .addFunction("setLayer", &Graphics::LevelSprite::setLayer)
            .addFunction("setParentId", &Graphics::LevelSprite::setParentId)
            .addFunction("setPositionTransformer", &Graphics::LevelSprite::setPositionTransformer)
            .addFunction("setRotation", &Graphics::LevelSprite::setRotation)
            .addFunction("setRotationOrigin", &Graphics::LevelSprite::setRotationOrigin)
            .addFunction("setScalingOrigin", &Graphics::LevelSprite::setScalingOrigin)
            .addFunction("setShader", &Graphics::LevelSprite::setShader)
            .addFunction("setTexture", &Graphics::LevelSprite::setTexture)
            .addFunction("setTextureRect", &Graphics::LevelSprite::setTextureRect)
            .addFunction("setTranslationOrigin", &Graphics::LevelSprite::setTranslationOrigin)
            .addFunction("setVisible", &Graphics::LevelSprite::setVisible)
            .addFunction("setZDepth", &Graphics::LevelSprite::setZDepth)
            .addFunction("useTextureSize", &Graphics::LevelSprite::useTextureSize)
        );

        (*lua)["obe"]["LevelSprite"]["getTexture"] = kaguya::function([](Graphics::LevelSprite* sprite)
        {
            return &sprite->getTexture();
        });
    }

    void LoadResourceManager(kaguya::State* lua)
    {
        (*lua)["obe"]["ResourceManager"].setClass(kaguya::UserdataMetatable<Graphics::ResourceManager>()
            .addStaticFunction("GetTexture", &Graphics::ResourceManager::GetTexture)
            .addStaticFunction("GetFont", &Graphics::ResourceManager::GetFont)
        );
    }

    void LoadCanvas(kaguya::State* lua)
    {
        Load(lua, "obe.UnitVector");
        Load(lua, "SFML.Color");
        (*lua)["obe"]["Canvas"] = kaguya::NewTable();
        (*lua)["obe"]["Canvas"]["CanvasElement"].setClass(
            kaguya::UserdataMetatable<Graphics::Canvas::CanvasElement, Types::ProtectedIdentifiable>()
            .addProperty("layer", &Graphics::Canvas::CanvasElement::layer)
            .addProperty("visible", &Graphics::Canvas::CanvasElement::visible)
            .addFunction("setLayer", &Graphics::Canvas::CanvasElement::setLayer)
        );
        (*lua)["obe"]["Canvas"]["CanvasShape"].setClass(kaguya::UserdataMetatable<Graphics::Canvas::CanvasPositionable>()
            .addProperty("position", &Graphics::Canvas::CanvasPositionable::position)
        );
        (*lua)["obe"]["Canvas"]["Line"].setClass(kaguya::UserdataMetatable<Graphics::Canvas::Line, 
            Graphics::Canvas::CanvasElement>()
                .addProperty("p1", &Graphics::Canvas::Line::p1)
                .addProperty("p2", &Graphics::Canvas::Line::p2)
                .addProperty("thickness", &Graphics::Canvas::Line::thickness)
                .addProperty("p1color", &Graphics::Canvas::Line::p1color)
                .addProperty("p2color", &Graphics::Canvas::Line::p2color)
        );
        (*lua)["obe"]["Canvas"]["Rectangle"].setClass(kaguya::UserdataMetatable<Graphics::Canvas::Rectangle, 
            kaguya::MultipleBase<Graphics::Canvas::CanvasElement, Graphics::Canvas::CanvasPositionable>>()
                .addProperty("shape", &Graphics::Canvas::Rectangle::shape)
                .addProperty("size", &Graphics::Canvas::Rectangle::size)
        );
        (*lua)["obe"]["Canvas"]["Text"].setClass(kaguya::UserdataMetatable<Graphics::Canvas::Text, 
            kaguya::MultipleBase<Graphics::Canvas::CanvasElement, Graphics::Canvas::CanvasPositionable>>()
                .addProperty("fontPath", &Graphics::Canvas::Text::fontPath)
                .addProperty("shape", &Graphics::Canvas::Text::shape)
                .addProperty("h_align", &Graphics::Canvas::Text::h_align)
                .addProperty("v_align", &Graphics::Canvas::Text::v_align)
        );
        (*lua)["obe"]["Canvas"]["Circle"].setClass(kaguya::UserdataMetatable<Graphics::Canvas::Circle, 
            kaguya::MultipleBase<Graphics::Canvas::CanvasElement, Graphics::Canvas::CanvasPositionable>>()
                .addProperty("shape", &Graphics::Canvas::Circle::shape)
                .addProperty("radius", &Graphics::Canvas::Circle::radius)
        );
        (*lua)["obe"]["Canvas"]["Sprite"].setClass(kaguya::UserdataMetatable<Graphics::Canvas::Sprite, 
            kaguya::MultipleBase<Graphics::Canvas::CanvasElement, Graphics::Canvas::CanvasPositionable>>()
                .addProperty("path", &Graphics::Canvas::Sprite::path)
                .addProperty("sprite", &Graphics::Canvas::Sprite::sprite)
        );
        (*lua)["obe"]["Canvas"]["InternalCanvas"].setClass(kaguya::UserdataMetatable<Graphics::Canvas::Canvas>()
            .setConstructors<Graphics::Canvas::Canvas(unsigned int, unsigned int)>()
            .addFunction("Line", &Graphics::Canvas::Canvas::add<Graphics::Canvas::Line>)
            .addFunction("Rectangle", &Graphics::Canvas::Canvas::add<Graphics::Canvas::Rectangle>)
            .addFunction("Text", &Graphics::Canvas::Canvas::add<Graphics::Canvas::Text>)
            .addFunction("Circle", &Graphics::Canvas::Canvas::add<Graphics::Canvas::Circle>)
            .addFunction("Sprite", &Graphics::Canvas::Canvas::add<Graphics::Canvas::Sprite>)
            .addFunction("render", &Graphics::Canvas::Canvas::render)
            .addFunction("setTarget", &Graphics::Canvas::Canvas::setTarget)
            .addFunction("clear", &Graphics::Canvas::Canvas::clear)
            .addFunction("remove", &Graphics::Canvas::Canvas::remove)
            .addFunction("get", &Graphics::Canvas::Canvas::get)
        );

        (*lua)["obe"]["Canvas"]["Alignment"] = kaguya::NewTable();
        (*lua)["obe"]["Canvas"]["Alignment"]["Horizontal"] = kaguya::NewTable();
        (*lua)["obe"]["Canvas"]["Alignment"]["Horizontal"]["Left"] = Graphics::Canvas::TextHorizontalAlign::Left;
        (*lua)["obe"]["Canvas"]["Alignment"]["Horizontal"]["Center"] = Graphics::Canvas::TextHorizontalAlign::Center;
        (*lua)["obe"]["Canvas"]["Alignment"]["Horizontal"]["Right"] = Graphics::Canvas::TextHorizontalAlign::Right;
        (*lua)["obe"]["Canvas"]["Alignment"]["Vertical"] = kaguya::NewTable();
        (*lua)["obe"]["Canvas"]["Alignment"]["Vertical"]["Top"] = Graphics::Canvas::TextVerticalAlign::Top;
        (*lua)["obe"]["Canvas"]["Alignment"]["Vertical"]["Center"] = Graphics::Canvas::TextVerticalAlign::Center;
        (*lua)["obe"]["Canvas"]["Alignment"]["Vertical"]["Bottom"] = Graphics::Canvas::TextVerticalAlign::Bottom;

        System::Path("Lib/Internal/Canvas.lua").load(System::Loaders::luaLoader, Script::ScriptEngine);
    }

    void LoadGraphicsUtils(kaguya::State* lua)
    {
        (*lua)["obe"]["SetClearColor"] = kaguya::function([](sf::Color newColor)
        {
            Graphics::Utils::ClearColor = newColor;
        });
    }

    void LoadShader(kaguya::State* lua)
    {
        (*lua)["obe"]["Shader"].setClass(kaguya::UserdataMetatable<Graphics::Shader>()
            .setConstructors<Graphics::Shader(), Graphics::Shader(const std::string&)>()
            .addFunction("loadShader", &Graphics::Shader::loadShader)
            .addOverloadedFunctions("setUniform",
                static_cast<void (Graphics::Shader::*)(const std::string&, float)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, int)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, bool)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, const sf::Texture&)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, const sf::Glsl::Vec2&)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, const sf::Glsl::Vec3&)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, const sf::Glsl::Vec4&)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, const sf::Glsl::Ivec2&)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, const sf::Glsl::Ivec3&)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, const sf::Glsl::Ivec4&)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, const sf::Glsl::Bvec2&)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, const sf::Glsl::Bvec3&)>(&Graphics::Shader::setUniform),
                static_cast<void (Graphics::Shader::*)(const std::string&, const sf::Glsl::Bvec4&)>(&Graphics::Shader::setUniform)
            )
        );
    }

    KAGUYA_MEMBER_FUNCTION_OVERLOADS(Color_fromRgb_wrapper, Graphics::Color, fromRgb, 3, 4);
    void LoadColor(kaguya::State* lua)
    {
        (*lua)["obe"]["Color"].setClass(kaguya::UserdataMetatable<Graphics::Color, sf::Color>()
            .setConstructors<
                Graphics::Color(uint_fast8_t, uint_fast8_t, uint_fast8_t),
                Graphics::Color(uint_fast8_t, uint_fast8_t, uint_fast8_t, uint_fast8_t),
                Graphics::Color(std::string)
            >()
            .addFunction("fromHex", &Graphics::Color::fromHex)
            .addFunction("fromRgb", Color_fromRgb_wrapper())
        );
    }
}