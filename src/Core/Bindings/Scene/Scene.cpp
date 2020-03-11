#include <Bindings/Scene/Scene.hpp>

#include <Scene/Camera.hpp>
#include <Scene/Scene.hpp>
#include <Scene/SceneNode.hpp>

#include <sol/sol.hpp>

namespace obe::Scene::Bindings
{
    void LoadClassCamera(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["Scene"].get<sol::table>();
        sol::usertype<obe::Scene::Camera> bindCamera
            = SceneNamespace.new_usertype<obe::Scene::Camera>("Camera",
                sol::call_constructor, sol::constructors<obe::Scene::Camera()>());
        bindCamera["getPosition"] = &obe::Scene::Camera::getPosition;
        bindCamera["getSize"] = &obe::Scene::Camera::getSize;
        bindCamera["move"] = &obe::Scene::Camera::move;
        bindCamera["scale"] = &obe::Scene::Camera::scale;
        bindCamera["setPosition"] = &obe::Scene::Camera::setPosition;
        bindCamera["setSize"] = &obe::Scene::Camera::setSize;
    }
    void LoadClassScene(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["Scene"].get<sol::table>();
        sol::usertype<obe::Scene::Scene> bindScene
            = SceneNamespace.new_usertype<obe::Scene::Scene>("Scene",
                sol::call_constructor,
                sol::constructors<obe::Scene::Scene(obe::Triggers::TriggerManager&)>());
        bindScene["attachResourceManager"] = &obe::Scene::Scene::attachResourceManager;
        bindScene["loadFromFile"] = &obe::Scene::Scene::loadFromFile;
        bindScene["setFutureLoadFromFile"]
            = sol::overload(static_cast<void (obe::Scene::Scene::*)(const std::string&)>(
                                &obe::Scene::Scene::setFutureLoadFromFile),
                static_cast<void (obe::Scene::Scene::*)(
                    const std::string&, const obe::Scene::OnSceneLoadCallback&)>(
                    &obe::Scene::Scene::setFutureLoadFromFile));
        bindScene["clear"] = &obe::Scene::Scene::clear;
        bindScene["dump"] = &obe::Scene::Scene::dump;
        bindScene["update"] = &obe::Scene::Scene::update;
        bindScene["draw"] = &obe::Scene::Scene::draw;
        bindScene["getLevelName"] = &obe::Scene::Scene::getLevelName;
        bindScene["setLevelName"] = &obe::Scene::Scene::setLevelName;
        bindScene["setUpdateState"] = &obe::Scene::Scene::setUpdateState;
        bindScene["createGameObject"] = &obe::Scene::Scene::createGameObject;
        bindScene["getGameObjectAmount"] = &obe::Scene::Scene::getGameObjectAmount;
        bindScene["getAllGameObjects"] = &obe::Scene::Scene::getAllGameObjects;
        bindScene["getGameObject"] = &obe::Scene::Scene::getGameObject;
        bindScene["doesGameObjectExists"] = &obe::Scene::Scene::doesGameObjectExists;
        bindScene["removeGameObject"] = &obe::Scene::Scene::removeGameObject;
        bindScene["getCamera"] = &obe::Scene::Scene::getCamera;
        bindScene["reorganizeLayers"] = &obe::Scene::Scene::reorganizeLayers;
        bindScene["createSprite"] = &obe::Scene::Scene::createSprite;
        bindScene["getSpriteAmount"] = &obe::Scene::Scene::getSpriteAmount;
        bindScene["getAllSprites"] = &obe::Scene::Scene::getAllSprites;
        bindScene["getSpritesByLayer"] = &obe::Scene::Scene::getSpritesByLayer;
        bindScene["getSpriteByPosition"] = &obe::Scene::Scene::getSpriteByPosition;
        bindScene["getSprite"] = &obe::Scene::Scene::getSprite;
        bindScene["doesSpriteExists"] = &obe::Scene::Scene::doesSpriteExists;
        bindScene["removeSprite"] = &obe::Scene::Scene::removeSprite;
        bindScene["createCollider"] = &obe::Scene::Scene::createCollider;
        bindScene["getColliderAmount"] = &obe::Scene::Scene::getColliderAmount;
        bindScene["getAllColliders"] = &obe::Scene::Scene::getAllColliders;
        bindScene["getColliderPointByPosition"]
            = &obe::Scene::Scene::getColliderPointByPosition;
        bindScene["getColliderByCentroidPosition"]
            = &obe::Scene::Scene::getColliderByCentroidPosition;
        bindScene["getCollider"] = &obe::Scene::Scene::getCollider;
        bindScene["doesColliderExists"] = &obe::Scene::Scene::doesColliderExists;
        bindScene["removeCollider"] = &obe::Scene::Scene::removeCollider;
        bindScene["getSceneRootNode"] = &obe::Scene::Scene::getSceneRootNode;
        bindScene["getFilePath"] = &obe::Scene::Scene::getFilePath;
        bindScene["reload"] = sol::overload(
            static_cast<void (obe::Scene::Scene::*)()>(&obe::Scene::Scene::reload),
            static_cast<void (obe::Scene::Scene::*)(
                const obe::Scene::OnSceneLoadCallback&)>(&obe::Scene::Scene::reload));
        bindScene["getLevelFile"] = &obe::Scene::Scene::getLevelFile;
        bindScene["enableShowSceneNodes"] = &obe::Scene::Scene::enableShowSceneNodes;
        bindScene["getSceneNodeByPosition"] = &obe::Scene::Scene::getSceneNodeByPosition;
    }
    void LoadClassSceneNode(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["Scene"].get<sol::table>();
        sol::usertype<obe::Scene::SceneNode> bindSceneNode
            = SceneNamespace.new_usertype<obe::Scene::SceneNode>(
                "SceneNode", sol::call_constructor, sol::default_constructor);
        bindSceneNode["addChild"] = &obe::Scene::SceneNode::addChild;
        bindSceneNode["setPosition"] = &obe::Scene::SceneNode::setPosition;
        bindSceneNode["move"] = &obe::Scene::SceneNode::move;
    }
};