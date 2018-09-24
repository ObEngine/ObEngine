#include <Bindings/Bindings.hpp>
#include <Bindings/ScriptBindings.hpp>
#include <Script/GameObject.hpp>

namespace obe::Bindings::ScriptBindings
{
    KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(useExternalTriggerProxy, GameObject, useExternalTrigger, 3, 4,
        void(Script::GameObject::*)(std::string, std::string, std::string, std::string));
    void LoadGameObject(kaguya::State* lua)
    {
        Load(lua, "obe.Identifiable");
        (*lua)["obe"]["GameObject"].setClass(kaguya::UserdataMetatable<Script::GameObject, Types::Identifiable>()
            .addFunction("LevelSprite", &Script::GameObject::getLevelSprite)
            .addFunction("Collider", &Script::GameObject::getCollider)
            .addFunction("Animator", &Script::GameObject::getAnimator)
            .addFunction("delete", &Script::GameObject::deleteObject)
            .addFunction("exec", &Script::GameObject::exec)
            .addFunction("initialize", &Script::GameObject::initialize)
            .addFunction("getConstructor", &Script::GameObject::getConstructor)
            .addFunction("getSceneNode", &Script::GameObject::getSceneNode)
            .addFunction("getType", &Script::GameObject::getType)
            .addFunction("removeExternalTrigger", &Script::GameObject::removeExternalTrigger)
            .addFunction("sendInitArg", &Script::GameObject::sendInitArgFromLua)
            .addFunction("useLocalTrigger", &Script::GameObject::useLocalTrigger)
            .addFunction("useExternalTrigger", useExternalTriggerProxy())
            .addFunction("access", &Script::GameObject::access)
        );
    }
}