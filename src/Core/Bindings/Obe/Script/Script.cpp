#include <Bindings/obe/Script/Script.hpp>

#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>

#include <Bindings/Config.hpp>

namespace obe::Script::Bindings
{
    void LoadClassGameObject(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["Script"].get<sol::table>();
        sol::usertype<obe::Script::GameObject> bindGameObject
            = ScriptNamespace.new_usertype<obe::Script::GameObject>("GameObject",
                sol::call_constructor,
                sol::constructors<obe::Script::GameObject(obe::Triggers::TriggerManager&,
                    sol::state_view, const std::string&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::Types::Identifiable, obe::Types::Serializable>());
        bindGameObject["getType"] = &obe::Script::GameObject::getType;
        bindGameObject["doesHaveAnimator"] = &obe::Script::GameObject::doesHaveAnimator;
        bindGameObject["doesHaveCollider"] = &obe::Script::GameObject::doesHaveCollider;
        bindGameObject["doesHaveSprite"] = &obe::Script::GameObject::doesHaveSprite;
        bindGameObject["doesHaveScriptEngine"]
            = &obe::Script::GameObject::doesHaveScriptEngine;
        bindGameObject["getUpdateState"] = &obe::Script::GameObject::getUpdateState;
        bindGameObject["setUpdateState"] = &obe::Script::GameObject::setUpdateState;
        bindGameObject["Animator"] = sol::property(&obe::Script::GameObject::getAnimator);
        bindGameObject["Collider"] = sol::property(&obe::Script::GameObject::getCollider);
        bindGameObject["Sprite"] = sol::property(&obe::Script::GameObject::getSprite);
        bindGameObject["SceneNode"]
            = sol::property(&obe::Script::GameObject::getSceneNode);
        bindGameObject["useTrigger"] = sol::overload(
            [](obe::Script::GameObject* self, const std::string& trNsp,
                const std::string& trGrp, const std::string& trName) -> void {
                return self->useTrigger(trNsp, trGrp, trName);
            },
            [](obe::Script::GameObject* self, const std::string& trNsp,
                const std::string& trGrp, const std::string& trName,
                const std::string& callAlias) -> void {
                return self->useTrigger(trNsp, trGrp, trName, callAlias);
            });
        bindGameObject["removeTrigger"] = &obe::Script::GameObject::removeTrigger;
        bindGameObject["exec"] = &obe::Script::GameObject::exec;
        bindGameObject["sendInitArg"] = &obe::Script::GameObject::sendInitArgFromLua;
        bindGameObject["registerTrigger"] = &obe::Script::GameObject::registerTrigger;
        bindGameObject["loadGameObject"] = sol::overload(
            [](obe::Script::GameObject* self, obe::Scene::Scene& scene,
                vili::node& obj) -> void { return self->loadGameObject(scene, obj); },
            [](obe::Script::GameObject* self, obe::Scene::Scene& scene, vili::node& obj,
                obe::Engine::ResourceManager* resources) -> void {
                return self->loadGameObject(scene, obj, resources);
            });
        bindGameObject["update"] = &obe::Script::GameObject::update;
        bindGameObject["deleteObject"] = &obe::Script::GameObject::deleteObject;
        bindGameObject["access"] = &obe::Script::GameObject::access;
        bindGameObject["getConstructor"] = &obe::Script::GameObject::getConstructor;
        bindGameObject["initialize"] = &obe::Script::GameObject::initialize;
        bindGameObject["setPermanent"] = &obe::Script::GameObject::setPermanent;
        bindGameObject["isPermanent"] = &obe::Script::GameObject::isPermanent;
        bindGameObject["getEnvironment"] = &obe::Script::GameObject::getEnvironment;
        bindGameObject["setState"] = &obe::Script::GameObject::setState;
        bindGameObject["dump"] = &obe::Script::GameObject::dump;
        bindGameObject["load"] = &obe::Script::GameObject::load;
        bindGameObject["deletable"] = &obe::Script::GameObject::deletable;
    }
    void LoadClassGameObjectDatabase(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["Script"].get<sol::table>();
        sol::usertype<obe::Script::GameObjectDatabase> bindGameObjectDatabase
            = ScriptNamespace.new_usertype<obe::Script::GameObjectDatabase>(
                "GameObjectDatabase", sol::call_constructor, sol::default_constructor);
        bindGameObjectDatabase["GetRequirementsForGameObject"]
            = &obe::Script::GameObjectDatabase::GetRequirementsForGameObject;
        bindGameObjectDatabase["GetDefinitionForGameObject"]
            = &obe::Script::GameObjectDatabase::GetDefinitionForGameObject;
        bindGameObjectDatabase["ApplyRequirements"]
            = &obe::Script::GameObjectDatabase::ApplyRequirements;
        bindGameObjectDatabase["Clear"] = &obe::Script::GameObjectDatabase::Clear;
    }
};