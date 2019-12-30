#include <Bindings/Bindings.hpp>
#include <Bindings/ScriptBindings.hpp>
#include <Script/GameObject.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::ScriptBindings
{
    KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(Script_useTrigger_wrapper, GameObject,
        useTrigger, 3, 4,
        void (Script::GameObject::*)(std::string, std::string, std::string, std::string));
    void LoadGameObject(kaguya::State* lua)
    {
        Load(lua, "obe.Identifiable");
        (*lua)["obe"]["GameObject"].setClass(
            kaguya::UserdataMetatable<Script::GameObject, Types::Identifiable>()
                .addFunction("LevelSprite", &Script::GameObject::getLevelSprite)
                .addFunction("Collider", &Script::GameObject::getCollider)
                .addFunction("Animator", &Script::GameObject::getAnimator)
                .addFunction("delete", &Script::GameObject::deleteObject)
                .addFunction("exec", &Script::GameObject::exec)
                .addFunction("initialize", &Script::GameObject::initialize)
                .addFunction("getConstructor", &Script::GameObject::getConstructor)
                .addFunction("getSceneNode", &Script::GameObject::getSceneNode)
                .addFunction("getType", &Script::GameObject::getType)
                .addFunction("removeTrigger", &Script::GameObject::removeTrigger)
                .addFunction("sendInitArg", &Script::GameObject::sendInitArgFromLua)
                .addFunction("useTrigger", Script_useTrigger_wrapper())
                .addFunction("access", &Script::GameObject::access));
    }
} // namespace obe::Bindings::ScriptBindings