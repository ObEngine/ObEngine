#include <Bindings/Script/Script.hpp>

#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>
#include <Script/GlobalState.hpp>

#include <sol/sol.hpp>

namespace obe::Script::Bindings
{
    void LoadClassGameObject(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["Script"].get<sol::table>();
        sol::usertype<obe::Script::GameObject> bindGameObject
            = ScriptNamespace.new_usertype<obe::Script::GameObject>("GameObject",
                sol::call_constructor,
                sol::constructors<obe::Script::GameObject(obe::Triggers::TriggerManager&,
                    const std::string&, const std::string&)>());
        bindGameObject["getType"] = &obe::Script::GameObject::getType;
        bindGameObject["doesHaveAnimator"] = &obe::Script::GameObject::doesHaveAnimator;
        bindGameObject["doesHaveCollider"] = &obe::Script::GameObject::doesHaveCollider;
        bindGameObject["doesHaveSprite"] = &obe::Script::GameObject::doesHaveSprite;
        bindGameObject["doesHaveScriptEngine"]
            = &obe::Script::GameObject::doesHaveScriptEngine;
        bindGameObject["getUpdateState"] = &obe::Script::GameObject::getUpdateState;
        bindGameObject["setUpdateState"] = &obe::Script::GameObject::setUpdateState;
        bindGameObject["getAnimator"] = &obe::Script::GameObject::getAnimator;
        bindGameObject["getCollider"] = &obe::Script::GameObject::getCollider;
        bindGameObject["getSprite"] = &obe::Script::GameObject::getSprite;
        bindGameObject["getSceneNode"] = &obe::Script::GameObject::getSceneNode;
        bindGameObject["useTrigger"] = &obe::Script::GameObject::useTrigger;
        bindGameObject["removeTrigger"] = &obe::Script::GameObject::removeTrigger;
        bindGameObject["exec"] = &obe::Script::GameObject::exec;
        bindGameObject["sendInitArgFromLua"]
            = &obe::Script::GameObject::sendInitArgFromLua;
        bindGameObject["registerTrigger"] = &obe::Script::GameObject::registerTrigger;
        bindGameObject["loadGameObject"] = &obe::Script::GameObject::loadGameObject;
        bindGameObject["update"] = &obe::Script::GameObject::update;
        bindGameObject["deleteObject"] = &obe::Script::GameObject::deleteObject;
        bindGameObject["access"] = &obe::Script::GameObject::access;
        bindGameObject["getConstructor"] = &obe::Script::GameObject::getConstructor;
        bindGameObject["getEnvIndex"] = &obe::Script::GameObject::getEnvIndex;
        bindGameObject["initialize"] = &obe::Script::GameObject::initialize;
        bindGameObject["setPermanent"] = &obe::Script::GameObject::setPermanent;
        bindGameObject["isPermanent"] = &obe::Script::GameObject::isPermanent;
        bindGameObject["setState"] = &obe::Script::GameObject::setState;
        bindGameObject["deletable"] = sol::readonly(&obe::Script::GameObject::deletable);
    }
    void LoadClassGameObjectDatabase(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["Script"].get<sol::table>();
        sol::usertype<obe::Script::GameObjectDatabase> bindGameObjectDatabase
            = ScriptNamespace.new_usertype<obe::Script::GameObjectDatabase>(
                "GameObjectDatabase", sol::call_constructor, sol::default_constructor);
    }
    void LoadFunctionInitScriptEngine(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["Script"].get<sol::table>();
        ScriptNamespace.set_function("InitScriptEngine", obe::Script::InitScriptEngine);
    }
    void LoadFunctionCreateNewEnvironment(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["Script"].get<sol::table>();
        ScriptNamespace.set_function(
            "CreateNewEnvironment", obe::Script::CreateNewEnvironment);
    }
    void LoadFunctionExecuteFile(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["Script"].get<sol::table>();
        ScriptNamespace.set_function("executeFile", obe::Script::executeFile);
    }
    void LoadFunctionExecuteString(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["Script"].get<sol::table>();
        ScriptNamespace.set_function("executeString", obe::Script::executeString);
    }
    void LoadGlobalScriptEngine(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["Script"].get<sol::table>();
        // ScriptNamespace["ScriptEngine"] = obe::Script::ScriptEngine;
    }
};