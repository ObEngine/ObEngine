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
                (*lua)["obe"]["Camera"].setClass(kaguya::UserdataMetatable<Scene::Camera>()
                    .addFunction("getPosition", &Scene::Camera::getPosition)
                    .addFunction("getSize", &Scene::Camera::getSize)
                    .addFunction("move", &Scene::Camera::move)
                    .addFunction("scale", &Scene::Camera::scale)
                    .addFunction("setPosition", &Scene::Camera::setPosition)
                    .addFunction("setSize", &Scene::Camera::setSize)
                );
            }

            kaguya::LuaFunction SceneGameObjectWrapperFunction(Scene::Scene* scene, const std::string& objectType, const std::string& objectId = "")
            {
                return scene->createGameObject(objectType, objectId)->getConstructor();
            }

            KAGUYA_FUNCTION_OVERLOADS(Scene_createGameObject_wrapper, SceneGameObjectWrapperFunction, 2, 3);
            KAGUYA_MEMBER_FUNCTION_OVERLOADS(Scene_createLevelSprite_wrapper, Scene::Scene, createLevelSprite, 1, 2);
            KAGUYA_MEMBER_FUNCTION_OVERLOADS(Scene_createCollider_wrapper, Scene::Scene, createCollider, 1, 2);
            void LoadScene(kaguya::State* lua)
            {
                (*lua)["obe"]["Scene"].setClass(kaguya::UserdataMetatable<Scene::Scene>()
                    .addFunction("clear", &Scene::Scene::clear)
                    .addFunction("createCollider", Scene_createCollider_wrapper())
                    //.addFunction("createGameObject", &Scene::Scene::createGameObject)
                    .addFunction("createLevelSprite", Scene_createLevelSprite_wrapper())
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
                    .addFunction("getCamera", &Scene::Scene::getCamera)
                    .addFunction("getColliderAmount", &Scene::Scene::getColliderAmount)
                    .addFunction("getColliderByCentroidPosition", &Scene::Scene::getColliderByCentroidPosition)
                    .addFunction("getCollider", &Scene::Scene::getCollider)
                    .addFunction("getColliderPointByPosition", &Scene::Scene::getColliderPointByPosition)
                    .addFunction("getGameObjectAmount", &Scene::Scene::getGameObjectAmount)
                    //.addFunction("getGameObjectById", &Scene::Scene::getGameObjectById)
                    .addFunction("getLevelFile", &Scene::Scene::getLevelFile)
                    .addFunction("getLevelName", &Scene::Scene::getLevelName)
                    .addFunction("getLevelSpriteAmount", &Scene::Scene::getLevelSpriteAmount)
                    .addFunction("getLevelSprite", &Scene::Scene::getLevelSprite)
                    .addFunction("getLevelSpriteByPosition", &Scene::Scene::getLevelSpriteByPosition)
                    .addFunction("getLevelSpritesByLayer", &Scene::Scene::getLevelSpritesByLayer)
                    .addOverloadedFunctions("loadFromFile",
                        static_cast<void (Scene::Scene::*)(const std::string&)>(&Scene::Scene::setFutureLoadFromFile),
                        static_cast<void (Scene::Scene::*)(const std::string&, kaguya::LuaFunction)>(&Scene::Scene::setFutureLoadFromFile)
                    )
                    .addOverloadedFunctions("reload",
                        static_cast<void (Scene::Scene::*)()>(&Scene::Scene::reload),
                        static_cast<void (Scene::Scene::*)(kaguya::LuaFunction)>(&Scene::Scene::reload)
                    )
                    .addFunction("removeCollider", &Scene::Scene::removeCollider)
                    .addFunction("removeGameObject", &Scene::Scene::removeGameObject)
                    .addFunction("removeLevelSprite", &Scene::Scene::removeLevelSprite)
                    .addFunction("reorganizeLayers", &Scene::Scene::reorganizeLayers)
                    .addFunction("setLevelName", &Scene::Scene::setLevelName)
                    .addFunction("setUpdateState", &Scene::Scene::setUpdateState)
                    .addFunction("update", &Scene::Scene::update)
                );

                (*lua)["obe"]["Scene"]["getGameObject"] = kaguya::function([](Scene::Scene* scene, const std::string& objectId)
                {
                    return scene->getGameObject(objectId)->access();
                });

                (*lua)["obe"]["Scene"]["createGameObject"] = kaguya::function(Scene_createGameObject_wrapper());
            }
        }  
    }
}
