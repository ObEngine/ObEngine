#include <Bindings/SceneBindings.hpp>
#include <Scene/Camera.hpp>
#include <Scene/Scene.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace SceneBindings
        {
            void LoadCamera(kaguya::State* lua)
            {
                (*lua)["Core"]["Scene"]["Camera"].setClass(kaguya::UserdataMetatable<Scene::Camera>()
                    .addFunction("getPosition", &Scene::Camera::getPosition)
                    .addFunction("getSize", &Scene::Camera::getSize)
                    .addFunction("lock", &Scene::Camera::lock)
                    .addFunction("move", &Scene::Camera::move)
                    .addFunction("rotate", &Scene::Camera::rotate)
                    .addFunction("scale", &Scene::Camera::scale)
                    .addFunction("setAngle", &Scene::Camera::setAngle)
                    .addFunction("setPosition", &Scene::Camera::setPosition)
                    .addFunction("setSize", &Scene::Camera::setSize)
                    .addFunction("unlock", &Scene::Camera::unlock)
                );
            }

            void LoadScene(kaguya::State* lua)
            {
                (*lua)["Core"]["Scene"]["Scene"].setClass(kaguya::UserdataMetatable<Scene::Scene>()
                    .addFunction("clearWorld", &Scene::Scene::clearWorld)
                    .addFunction("createCollider", &Scene::Scene::createCollider)
                    .addFunction("createGameObject", &Scene::Scene::createGameObject)
                    .addFunction("createLevelSprite", &Scene::Scene::createLevelSprite)
                    .addFunction("display", &Scene::Scene::display)
                    .addFunction("doesColliderExists", &Scene::Scene::doesColliderExists)
                    .addFunction("doesGameObjectExists", &Scene::Scene::doesGameObjectExists)
                    .addFunction("doesLevelSpriteExists", &Scene::Scene::doesLevelSpriteExists)
                    .addFunction("dump", &Scene::Scene::dump)
                    .addFunction("enableShowCollision", &Scene::Scene::enableShowCollision)
                    .addFunction("getAllColliders", &Scene::Scene::getAllColliders)
                    .addFunction("getAllGameObjects", &Scene::Scene::getAllGameObjects)
                    .addFunction("getAllLevelSprites", &Scene::Scene::getAllLevelSprites)
                    .addFunction("getBaseFolder", &Scene::Scene::getBaseFolder)
                    .addFunction("getColliderAmount", &Scene::Scene::getColliderAmount)
                    .addFunction("getColliderByCentroidPosition", &Scene::Scene::getColliderByCentroidPosition)
                    .addFunction("getColliderById", &Scene::Scene::getColliderById)
                    .addFunction("getColliderPointByPosition", &Scene::Scene::getColliderPointByPosition)
                    .addFunction("getGameObjectAmount", &Scene::Scene::getGameObjectAmount)
                    .addFunction("getGameObjectById", &Scene::Scene::getGameObjectById)
                    .addFunction("getLevelName", &Scene::Scene::getLevelName)
                    .addFunction("getLevelSpriteAmount", &Scene::Scene::getLevelSpriteAmount)
                    .addFunction("getLevelSpriteById", &Scene::Scene::getLevelSpriteById)
                    .addFunction("getLevelSpriteByPosition", &Scene::Scene::getLevelSpriteByPosition)
                    .addFunction("getLevelSpritesByLayer", &Scene::Scene::getLevelSpritesByLayer)
                    .addFunction("isCameraLocked", &Scene::Scene::isCameraLocked)
                    .addFunction("loadFromFile", &Scene::Scene::loadFromFile)
                    .addFunction("removeColliderById", &Scene::Scene::removeColliderById)
                    .addFunction("removeGameObjectById", &Scene::Scene::removeGameObjectById)
                    .addFunction("removeLevelSpriteById", &Scene::Scene::removeLevelSpriteById)
                    .addFunction("reorganizeLayers", &Scene::Scene::reorganizeLayers)
                    .addFunction("setCameraLock", &Scene::Scene::setCameraLock)
                    .addFunction("setLevelName", &Scene::Scene::setLevelName)
                    .addFunction("setUpdateState", &Scene::Scene::setUpdateState)
                    .addFunction("update", &Scene::Scene::update)
                );
            }
        }  
    }
}
