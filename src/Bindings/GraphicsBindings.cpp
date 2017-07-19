#include <Bindings/GraphicsBindings.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace GraphicsBindings
        {
            void LoadLevelSpriteHandlePoint(kaguya::State& lua)
            {
                lua["Core"]["Graphics"]["LevelSpriteHandlePoint"].setClass(kaguya::UserdataMetatable<Graphics::LevelSpriteHandlePoint>()
                    .addFunction("getRect", &Graphics::LevelSpriteHandlePoint::getRect)
                    .addFunction("getReferencial", &Graphics::LevelSpriteHandlePoint::getReferencial)
                    .addFunction("moveTo", &Graphics::LevelSpriteHandlePoint::moveTo)
                );
            }
            void LoadLevelSprite(kaguya::State& lua)
            {
                lua["Core"]["Graphics"]["LevelSprite"].setClass(kaguya::UserdataMetatable<Graphics::LevelSprite, kaguya::MultipleBase<Transform::UnitBasedObject, Types::Selectable, Transform::Rect, Types::Identifiable>>()
                    .addFunction("addAtr", &Graphics::LevelSprite::addAtr)
                    .addFunction("drawHandle", &Graphics::LevelSprite::drawHandle)
                    .addFunction("getAttributes", &Graphics::LevelSprite::getAttributes)
                    .addFunction("getColor", &Graphics::LevelSprite::getColor)
                    .addFunction("getDrawPosition", &Graphics::LevelSprite::getDrawPosition)
                    .addFunction("getHandlePoint", &Graphics::LevelSprite::getHandlePoint)
                    .addFunction("getLayer", &Graphics::LevelSprite::getLayer)
                    .addFunction("getParentId", &Graphics::LevelSprite::getParentId)
                    .addFunction("getPath", &Graphics::LevelSprite::getPath)
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
                    .addFunction("removeAtrByIndex", &Graphics::LevelSprite::removeAtrByIndex)
                    .addFunction("removeAtrByName", &Graphics::LevelSprite::removeAtrByName)
                    .addFunction("rotate", &Graphics::LevelSprite::rotate)
                    .addFunction("setAtr", &Graphics::LevelSprite::setAtr)
                    .addFunction("setColor", &Graphics::LevelSprite::setColor)
                    .addFunction("setLayer", &Graphics::LevelSprite::setLayer)
                    .addFunction("setParentId", &Graphics::LevelSprite::setParentId)
                    .addFunction("setRotation", &Graphics::LevelSprite::setRotation)
                    .addFunction("setRotationOrigin", &Graphics::LevelSprite::setRotationOrigin)
                    .addFunction("setScalingOrigin", &Graphics::LevelSprite::setScalingOrigin)
                    .addFunction("setTexture", &Graphics::LevelSprite::setTexture)
                    .addFunction("setTranslationOrigin", &Graphics::LevelSprite::setTranslationOrigin)
                    .addFunction("setVisible", &Graphics::LevelSprite::setVisible)
                    .addFunction("setZDepth", &Graphics::LevelSprite::setZDepth)
                );
            }
            void LoadResourceManager(kaguya::State& lua)
            {
                lua["Core"]["Graphics"]["ResourceManager"].setClass(kaguya::UserdataMetatable<Graphics::ResourceManager>()
                    .addStaticFunction("GetInstance", &Graphics::ResourceManager::GetInstance)
                    .addFunction("getTexture", &Graphics::ResourceManager::getTexture)
                );
            }
        }
    }
}
