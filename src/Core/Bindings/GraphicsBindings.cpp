#include <Bindings/Bindings.hpp>
#include <Bindings/GraphicsBindings.hpp>
#include <Graphics/Canvas.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>

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
                    .addStaticFunction("GetInstance", &Graphics::ResourceManager::GetInstance)
                    .addFunction("getTexture", &Graphics::ResourceManager::getTexture)
                );
            }

            void LoadCanvas(kaguya::State* lua)
            {
                (*lua)["obe"]["Canvas"] = kaguya::NewTable();
                (*lua)["obe"]["Canvas"]["RequirePair"].setClass(kaguya::UserdataMetatable<std::pair<std::string, std::string>>()
                    .addFunction("first", &std::pair<std::string, std::string>::first)
                    .addFunction("second", &std::pair<std::string, std::string>::second)
                );
                (*lua)["obe"]["Canvas"]["Element"].setClass(kaguya::UserdataMetatable<Graphics::Canvas::Element>());
                (*lua)["obe"]["Canvas"]["Drawable"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Drawable, Graphics::Canvas::Element>()
                );
                (*lua)["obe"]["Canvas"]["Colorable"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Colorable, Graphics::Canvas::Drawable>()
                );
                (*lua)["obe"]["Canvas"]["Transformable"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Transformable, Graphics::Canvas::Element>()
                );
                (*lua)["obe"]["Canvas"]["CanvasElement"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::CanvasElement, Graphics::Canvas::Drawable>()
                );
                (*lua)["obe"]["Canvas"]["Line"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Line, 
                        kaguya::MultipleBase<Graphics::Canvas::CanvasElement, Graphics::Canvas::Colorable>
                    >()
                );
                (*lua)["obe"]["Canvas"]["Rectangle"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Rectangle, 
                        kaguya::MultipleBase<Graphics::Canvas::CanvasElement, Graphics::Canvas::Colorable, Graphics::Canvas::Transformable>
                    >()
                );
                (*lua)["obe"]["Canvas"]["Text"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Text, 
                        kaguya::MultipleBase<Graphics::Canvas::CanvasElement, Graphics::Canvas::Colorable, Graphics::Canvas::Transformable>
                    >()
                );
                (*lua)["obe"]["Canvas"]["Circle"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Circle, 
                        kaguya::MultipleBase<Graphics::Canvas::CanvasElement, Graphics::Canvas::Colorable, Graphics::Canvas::Transformable>
                    >()
                );
                (*lua)["obe"]["Canvas"]["Sprite"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Sprite, 
                        kaguya::MultipleBase<Graphics::Canvas::CanvasElement, Graphics::Canvas::Colorable, Graphics::Canvas::Transformable>
                    >()
                );
                (*lua)["obe"]["Canvas"]["Canvas"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas::Canvas>()
                    .setConstructors<Graphics::Canvas::Canvas(unsigned int, unsigned int)>()
                    .addFunction("Line", &Graphics::Canvas::Canvas::line)
                    .addFunction("Rectangle", &Graphics::Canvas::Canvas::rectangle)
                    .addFunction("Text", &Graphics::Canvas::Canvas::text)
                    .addFunction("Circle", &Graphics::Canvas::Canvas::circle)
                    .addFunction("Sprite", &Graphics::Canvas::Canvas::sprite)
                    .addFunction("render", &Graphics::Canvas::Canvas::render)
                    .addFunction("setTarget", &Graphics::Canvas::Canvas::setTarget)
                );
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
