#include <Bindings/Bindings.hpp>
#include <Bindings/GraphicsBindings.hpp>
#include <Graphics/Canvas.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace GraphicsBindings
        {
            void LoadLevelSpriteHandlePoint(kaguya::State* lua)
            {
                (*lua)["obe"]["LevelSpriteHandlePoint"].setClass(kaguya::UserdataMetatable<Graphics::LevelSpriteHandlePoint>()
                    .addFunction("getRect", &Graphics::LevelSpriteHandlePoint::getRect)
                    .addFunction("getReferencial", &Graphics::LevelSpriteHandlePoint::getReferencial)
                    .addFunction("moveTo", &Graphics::LevelSpriteHandlePoint::moveTo)
                );
            }
            void LoadLevelSprite(kaguya::State* lua)
            {
                Load(lua, "obe.UnitBasedObject");
                Load(lua, "obe.Selectable");
                Load(lua, "obe.Rect");
                (*lua)["obe"]["LevelSprite"].setClass(
                    kaguya::UserdataMetatable<
                    Graphics::LevelSprite,
                    kaguya::MultipleBase<
                    Transform::UnitBasedObject,
                    Types::Selectable,
                    Transform::Rect
                    >
                    >()
                    .addFunction("drawHandle", &Graphics::LevelSprite::drawHandle)
                    .addFunction("getColor", &Graphics::LevelSprite::getColor)
                    .addFunction("getDrawPosition", &Graphics::LevelSprite::getDrawPosition)
                    .addFunction("getHandlePoint", &Graphics::LevelSprite::getHandlePoint)
                    .addFunction("getLayer", &Graphics::LevelSprite::getLayer)
                    .addFunction("getParentId", &Graphics::LevelSprite::getParentId)
                    .addFunction("getPath", &Graphics::LevelSprite::getPath)
                    .addFunction("getPositionTransformer", &Graphics::LevelSprite::getPositionTransformer)
                    .addFunction("getRect", &Graphics::LevelSprite::getRect)
                    .addFunction("getSprite", &Graphics::LevelSprite::getSprite)
                    .addFunction("getSpriteHeight", &Graphics::LevelSprite::getSpriteHeight)
                    .addFunction("getSpriteWidth", &Graphics::LevelSprite::getSpriteWidth)
                    .addFunction("getTexture", &Graphics::LevelSprite::getTexture)
                    .addFunction("getXScaleFactor", &Graphics::LevelSprite::getXScaleFactor)
                    .addFunction("getYScaleFactor", &Graphics::LevelSprite::getYScaleFactor)
                    .addFunction("getZDepth", &Graphics::LevelSprite::getZDepth)
                    .addFunction("isVisible", &Graphics::LevelSprite::isVisible)
                    .addFunction("load", &Graphics::LevelSprite::load)
                    .addFunction("rotate", &Graphics::LevelSprite::rotate)
                    .addFunction("setColor", &Graphics::LevelSprite::setColor)
                    .addFunction("setLayer", &Graphics::LevelSprite::setLayer)
                    .addFunction("setParentId", &Graphics::LevelSprite::setParentId)
                    .addFunction("setPositionTransformer", &Graphics::LevelSprite::setPositionTransformer)
                    .addFunction("setRotation", &Graphics::LevelSprite::setRotation)
                    .addFunction("setRotationOrigin", &Graphics::LevelSprite::setRotationOrigin)
                    .addFunction("setScalingOrigin", &Graphics::LevelSprite::setScalingOrigin)
                    .addFunction("setTexture", &Graphics::LevelSprite::setTexture)
                    .addFunction("setTranslationOrigin", &Graphics::LevelSprite::setTranslationOrigin)
                    .addFunction("setVisible", &Graphics::LevelSprite::setVisible)
                    .addFunction("setZDepth", &Graphics::LevelSprite::setZDepth)
                    .addFunction("useTextureSize", &Graphics::LevelSprite::useTextureSize)
                );
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
                    kaguya::UserdataMetatable<Graphics::Canvas::CanvasElement>()
                    .addProperty("layer", &Graphics::Canvas::CanvasElement::layer)
                    .addProperty("visible", &Graphics::Canvas::CanvasElement::visible)
                    .addProperty("id", &Graphics::Canvas::CanvasElement::id)
                );
                (*lua)["obe"]["Canvas"]["Line"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Line, Graphics::Canvas::CanvasElement>()
                        .addProperty("p1", &Graphics::Canvas::Line::p1)
                        .addProperty("p2", &Graphics::Canvas::Line::p2)
                        .addProperty("thickness", &Graphics::Canvas::Line::thickness)
                        .addProperty("color", &Graphics::Canvas::Line::color)
                );
                (*lua)["obe"]["Canvas"]["Rectangle"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Rectangle, Graphics::Canvas::CanvasElement>()
                        .addProperty("shape", &Graphics::Canvas::Rectangle::shape)
                );
                (*lua)["obe"]["Canvas"]["Text"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Text, Graphics::Canvas::CanvasElement>()
                        .addProperty("fontPath", &Graphics::Canvas::Text::fontPath)
                        .addProperty("shape", &Graphics::Canvas::Text::shape)
                        .addProperty("h_align", &Graphics::Canvas::Text::h_align)
                        .addProperty("v_align", &Graphics::Canvas::Text::v_align)
                );
                (*lua)["obe"]["Canvas"]["Circle"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Circle, Graphics::Canvas::CanvasElement>()
                        .addProperty("shape", &Graphics::Canvas::Circle::shape)
                        .addProperty("radius", &Graphics::Canvas::Circle::radius)
                );
                (*lua)["obe"]["Canvas"]["Sprite"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Sprite, Graphics::Canvas::CanvasElement>()
                        .addProperty("path", &Graphics::Canvas::Sprite::path)
                        .addProperty("sprite", &Graphics::Canvas::Sprite::sprite)
                );
                (*lua)["obe"]["Canvas"]["InternalCanvas"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Canvas>()
                    .setConstructors<Graphics::Canvas::Canvas(unsigned int, unsigned int)>()
                    .addFunction("Line", &Graphics::Canvas::Canvas::line)
                    .addFunction("Rectangle", &Graphics::Canvas::Canvas::rectangle)
                    .addFunction("Text", &Graphics::Canvas::Canvas::text)
                    .addFunction("Circle", &Graphics::Canvas::Canvas::circle)
                    .addFunction("Sprite", &Graphics::Canvas::Canvas::sprite)
                    .addFunction("render", &Graphics::Canvas::Canvas::render)
                    .addFunction("setTarget", &Graphics::Canvas::Canvas::setTarget)
                    .addFunction("clear", &Graphics::Canvas::Canvas::clear)
                    .addFunction("remove", &Graphics::Canvas::Canvas::remove)
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

                System::Path("Lib/Internal/Canvas.lua").loadResource(&Script::ScriptEngine, System::Loaders::luaLoader);
            }

            void LoadGraphicsUtils(kaguya::State* lua)
            {
                (*lua)["obe"]["SetClearColor"] = kaguya::function([](sf::Color newColor)
                {
                    Graphics::Utils::clearColor = newColor;
                });
            }
        }
    }
}
