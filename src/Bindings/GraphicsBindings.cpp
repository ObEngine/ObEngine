#include <Bindings/GraphicsBindings.hpp>
#include <Graphics/Canvas.hpp>
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
                (*lua)["Core"]["Graphics"]["LevelSpriteHandlePoint"].setClass(kaguya::UserdataMetatable<Graphics::LevelSpriteHandlePoint>()
                    .addFunction("getRect", &Graphics::LevelSpriteHandlePoint::getRect)
                    .addFunction("getReferencial", &Graphics::LevelSpriteHandlePoint::getReferencial)
                    .addFunction("moveTo", &Graphics::LevelSpriteHandlePoint::moveTo)
                );
            }
            void LoadLevelSprite(kaguya::State* lua)
            {
                (*lua)["Core"]["Graphics"]["LevelSprite"].setClass(kaguya::UserdataMetatable<Graphics::LevelSprite, kaguya::MultipleBase<Transform::UnitBasedObject, Types::Selectable, Transform::Rect, Types::Identifiable>>()
                    .addFunction("drawHandle", &Graphics::LevelSprite::drawHandle)
                    .addFunction("getColor", &Graphics::LevelSprite::getColor)
                    .addFunction("getDrawPosition", &Graphics::LevelSprite::getDrawPosition)
                    .addFunction("getHandlePoint", &Graphics::LevelSprite::getHandlePoint)
                    .addFunction("getLayer", &Graphics::LevelSprite::getLayer)
                    .addFunction("getParentId", &Graphics::LevelSprite::getParentId)
                    .addFunction("getPath", &Graphics::LevelSprite::getPath)
                    .addFunction("getPositionTransformer", &Graphics::LevelSprite::getPositionTransformer)
                    .addFunction("getRect", &Graphics::LevelSprite::getRect)
                    .addFunction("getRotation", &Graphics::LevelSprite::getRotation)
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
                );
            }
            void LoadResourceManager(kaguya::State* lua)
            {
                (*lua)["Core"]["Graphics"]["ResourceManager"].setClass(kaguya::UserdataMetatable<Graphics::ResourceManager>()
                    .addStaticFunction("GetInstance", &Graphics::ResourceManager::GetInstance)
                    .addFunction("getTexture", &Graphics::ResourceManager::getTexture)
                );
            }

            void LoadCanvas(kaguya::State* lua)
            {
                (*lua)["Core"]["Graphics"]["Canvas"] = kaguya::NewTable();
                (*lua)["Core"]["Graphics"]["Canvas"]["RequirePair"].setClass(kaguya::UserdataMetatable<std::pair<std::string, std::string>>()
                    .addFunction("first", &std::pair<std::string, std::string>::first)
                    .addFunction("second", &std::pair<std::string, std::string>::second)
                );
                (*lua)["Core"]["Graphics"]["Canvas"]["Element"].setClass(kaguya::UserdataMetatable<Graphics::Element>());
                (*lua)["Core"]["Graphics"]["Canvas"]["Configurable"].setClass(kaguya::UserdataMetatable<Graphics::Configurable, Graphics::Element>()
                    .addFunction("init", &Graphics::Configurable::init)
                );
                (*lua)["Core"]["Graphics"]["Canvas"]["Drawable"].setClass(
                    kaguya::UserdataMetatable<Graphics::Drawable, Graphics::Configurable>()
                );
                (*lua)["Core"]["Graphics"]["Canvas"]["Colorable"].setClass(
                    kaguya::UserdataMetatable<Graphics::Colorable, Graphics::Drawable>()
                );
                (*lua)["Core"]["Graphics"]["Canvas"]["Transformable"].setClass(
                    kaguya::UserdataMetatable<Graphics::Transformable, Graphics::Configurable>()
                );
                (*lua)["Core"]["Graphics"]["Canvas"]["CanvasElement"].setClass(
                    kaguya::UserdataMetatable<Graphics::CanvasElement, Graphics::Drawable>()
                );
                (*lua)["Core"]["Graphics"]["Canvas"]["Line"].setClass(
                    kaguya::UserdataMetatable<Graphics::Line, kaguya::MultipleBase<Graphics::CanvasElement, Graphics::Colorable>>()
                );
                (*lua)["Core"]["Graphics"]["Canvas"]["Rectangle"].setClass(
                    kaguya::UserdataMetatable<Graphics::Rectangle, kaguya::MultipleBase<Graphics::CanvasElement, Graphics::Colorable, Graphics::Transformable>>()
                );
                (*lua)["Core"]["Graphics"]["Canvas"]["Text"].setClass(
                    kaguya::UserdataMetatable<Graphics::Text, kaguya::MultipleBase<Graphics::CanvasElement, Graphics::Colorable, Graphics::Transformable>>()
                );
                (*lua)["Core"]["Graphics"]["Canvas"]["Circle"].setClass(
                    kaguya::UserdataMetatable<Graphics::Circle, kaguya::MultipleBase<Graphics::CanvasElement, Graphics::Colorable, Graphics::Transformable>>()
                );
                (*lua)["Core"]["Graphics"]["Canvas"]["Canvas"].setClass(
                    kaguya::UserdataMetatable<Graphics::Canvas>()
                    .setConstructors<Graphics::Canvas(kaguya::State*, unsigned int, unsigned int)>()
                    .addFunction("Line", &Graphics::Canvas::line)
                    .addFunction("Rectangle", &Graphics::Canvas::rectangle)
                    .addFunction("Text", &Graphics::Canvas::text)
                    .addFunction("Circle", &Graphics::Canvas::circle)
                    .addFunction("Get", &Graphics::Canvas::get)
                    .addFunction("render", &Graphics::Canvas::render)
                    .addFunction("setTarget", &Graphics::Canvas::setTarget)
                );
            }
        }
    }
}
