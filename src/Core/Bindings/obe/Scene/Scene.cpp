#include <Bindings/obe/Scene/Scene.hpp>

#include <Scene/Camera.hpp>
#include <Scene/Scene.hpp>
#include <Scene/SceneNode.hpp>

#include <Bindings/Config.hpp>

namespace obe::Scene::Bindings
{
    void LoadClassCamera(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["Scene"].get<sol::table>();
        sol::usertype<obe::Scene::Camera> bindCamera
            = SceneNamespace.new_usertype<obe::Scene::Camera>("Camera",
                sol::call_constructor, sol::constructors<obe::Scene::Camera()>(),
                sol::base_classes,
                sol::bases<obe::Transform::Rect, obe::Transform::Movable>());
        bindCamera["getPosition"] = sol::overload(
            [](obe::Scene::Camera* self) -> obe::Transform::UnitVector {
                return self->getPosition();
            },
            [](obe::Scene::Camera* self, const obe::Transform::Referential& ref)
                -> obe::Transform::UnitVector { return self->getPosition(ref); });
        bindCamera["getSize"] = &obe::Scene::Camera::getSize;
        bindCamera["move"] = &obe::Scene::Camera::move;
        bindCamera["scale"]
            = sol::overload([](obe::Scene::Camera* self,
                                double pScale) -> void { return self->scale(pScale); },
                [](obe::Scene::Camera* self, double pScale,
                    const obe::Transform::Referential& ref) -> void {
                    return self->scale(pScale, ref);
                });
        bindCamera["setPosition"] = sol::overload(
            [](obe::Scene::Camera* self, const obe::Transform::UnitVector& position)
                -> void { return self->setPosition(position); },
            [](obe::Scene::Camera* self, const obe::Transform::UnitVector& position,
                const obe::Transform::Referential& ref) -> void {
                return self->setPosition(position, ref);
            });
        bindCamera["setSize"]
            = sol::overload([](obe::Scene::Camera* self,
                                double pSize) -> void { return self->setSize(pSize); },
                [](obe::Scene::Camera* self, double pSize,
                    const obe::Transform::Referential& ref) -> void {
                    return self->setSize(pSize, ref);
                });
    }
    void LoadClassScene(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["Scene"].get<sol::table>();
        sol::usertype<obe::Scene::Scene> bindScene
            = SceneNamespace.new_usertype<obe::Scene::Scene>("Scene",
                sol::call_constructor,
                sol::constructors<obe::Scene::Scene(
                    obe::Triggers::TriggerManager&, sol::state_view)>(),
                sol::base_classes, sol::bases<obe::Types::Serializable>());
        bindScene["attachResourceManager"] = &obe::Scene::Scene::attachResourceManager;
        bindScene["loadFromFile"]
            = sol::overload(static_cast<void (obe::Scene::Scene::*)(const std::string&)>(
                                &obe::Scene::Scene::setFutureLoadFromFile),
                static_cast<void (obe::Scene::Scene::*)(
                    const std::string&, const obe::Scene::OnSceneLoadCallback&)>(
                    &obe::Scene::Scene::setFutureLoadFromFile));
        bindScene["clear"] = &obe::Scene::Scene::clear;
        bindScene["dump"] = &obe::Scene::Scene::dump;
        bindScene["load"] = &obe::Scene::Scene::load;
        bindScene["update"] = &obe::Scene::Scene::update;
        bindScene["draw"] = &obe::Scene::Scene::draw;
        bindScene["getLevelName"] = &obe::Scene::Scene::getLevelName;
        bindScene["setLevelName"] = &obe::Scene::Scene::setLevelName;
        bindScene["setUpdateState"] = &obe::Scene::Scene::setUpdateState;
        bindScene["createGameObject"] = sol::overload(
            [](obe::Scene::Scene* self, const std::string& obj) -> sol::function {
                return obe::Scene::sceneCreateGameObjectProxy(self, obj);
            },
            [](obe::Scene::Scene* self, const std::string& obj,
                const std::string& id) -> sol::function {
                return obe::Scene::sceneCreateGameObjectProxy(self, obj, id);
            });
        bindScene["getGameObjectAmount"] = &obe::Scene::Scene::getGameObjectAmount;
        bindScene["getAllGameObjects"] = sol::overload(
            [](obe::Scene::Scene* self) -> std::vector<obe::Script::GameObject*> {
                return self->getAllGameObjects();
            },
            [](obe::Scene::Scene* self,
                const std::string& objectType) -> std::vector<obe::Script::GameObject*> {
                return self->getAllGameObjects(objectType);
            });
        bindScene["getGameObject"] = &obe::Scene::sceneGetGameObjectProxy;
        bindScene["doesGameObjectExists"] = &obe::Scene::Scene::doesGameObjectExists;
        bindScene["removeGameObject"] = &obe::Scene::Scene::removeGameObject;
        bindScene["getCamera"] = &obe::Scene::Scene::getCamera;
        bindScene["reorganizeLayers"] = &obe::Scene::Scene::reorganizeLayers;
        bindScene["createSprite"] = sol::overload(
            [](obe::Scene::Scene* self) -> obe::Graphics::Sprite& {
                return self->createSprite();
            },
            [](obe::Scene::Scene* self, const std::string& id) -> obe::Graphics::Sprite& {
                return self->createSprite(id);
            },
            [](obe::Scene::Scene* self, const std::string& id,
                bool addToSceneRoot) -> obe::Graphics::Sprite& {
                return self->createSprite(id, addToSceneRoot);
            });
        bindScene["getSpriteAmount"] = &obe::Scene::Scene::getSpriteAmount;
        bindScene["getAllSprites"] = &obe::Scene::Scene::getAllSprites;
        bindScene["getSpritesByLayer"] = &obe::Scene::Scene::getSpritesByLayer;
        bindScene["getSpriteByPosition"] = &obe::Scene::Scene::getSpriteByPosition;
        bindScene["getSprite"] = &obe::Scene::Scene::getSprite;
        bindScene["doesSpriteExists"] = &obe::Scene::Scene::doesSpriteExists;
        bindScene["removeSprite"] = &obe::Scene::Scene::removeSprite;
        bindScene["createCollider"] = sol::overload(
            [](obe::Scene::Scene* self) -> obe::Collision::PolygonalCollider& {
                return self->createCollider();
            },
            [](obe::Scene::Scene* self,
                const std::string& id) -> obe::Collision::PolygonalCollider& {
                return self->createCollider(id);
            },
            [](obe::Scene::Scene* self, const std::string& id,
                bool addToSceneRoot) -> obe::Collision::PolygonalCollider& {
                return self->createCollider(id, addToSceneRoot);
            });
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
            = SceneNamespace.new_usertype<obe::Scene::SceneNode>("SceneNode",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<obe::Transform::Movable, obe::Types::Selectable>());
        bindSceneNode["addChild"] = &obe::Scene::SceneNode::addChild;
        bindSceneNode["removeChild"] = &obe::Scene::SceneNode::removeChild;
        bindSceneNode["setPosition"] = &obe::Scene::SceneNode::setPosition;
        bindSceneNode["move"] = &obe::Scene::SceneNode::move;
    }
    void LoadFunctionSceneGetGameObjectProxy(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["Scene"].get<sol::table>();
        SceneNamespace.set_function(
            "sceneGetGameObjectProxy", obe::Scene::sceneGetGameObjectProxy);
    }
    void LoadFunctionSceneCreateGameObjectProxy(sol::state_view state)
    {
        sol::table SceneNamespace = state["obe"]["Scene"].get<sol::table>();
        SceneNamespace.set_function(
            "sceneCreateGameObjectProxy", obe::Scene::sceneCreateGameObjectProxy);
    }
};