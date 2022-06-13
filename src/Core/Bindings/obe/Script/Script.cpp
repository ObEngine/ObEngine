#include <Bindings/obe/Script/Script.hpp>

#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>
#include <Script/LuaState.hpp>
#include <Script/Scripting.hpp>

#include <Bindings/Config.hpp>

namespace obe::script::Bindings
{
    void LoadClassGameObject(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["script"].get<sol::table>();
        sol::usertype<obe::script::GameObject> bindGameObject
            = ScriptNamespace.new_usertype<obe::script::GameObject>("GameObject",
                sol::call_constructor,
                sol::constructors<obe::script::GameObject(
                    sol::state_view, const std::string&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::Types::Identifiable, obe::Types::Serializable>());
        bindGameObject["get_type"] = &obe::script::GameObject::get_type;
        bindGameObject["does_have_animator"] = &obe::script::GameObject::does_have_animator;
        bindGameObject["does_have_collider"] = &obe::script::GameObject::does_have_collider;
        bindGameObject["does_have_sprite"] = &obe::script::GameObject::does_have_sprite;
        bindGameObject["does_have_script_engine"] = &obe::script::GameObject::does_have_script_engine;
        bindGameObject["get_update_state"] = &obe::script::GameObject::get_update_state;
        bindGameObject["set_update_state"] = &obe::script::GameObject::set_update_state;
        bindGameObject["Animator"] = sol::property(&obe::script::GameObject::get_animator);
        bindGameObject["Collider"] = sol::property(&obe::script::GameObject::get_collider);
        bindGameObject["Sprite"] = sol::property(&obe::script::GameObject::get_sprite);
        bindGameObject["SceneNode"] = sol::property(&obe::script::GameObject::get_scene_node);
        bindGameObject["exec"] = &obe::script::GameObject::exec;
        bindGameObject["init_from_vili"] = &obe::script::GameObject::init_from_vili;
        bindGameObject["sendInitArg"] = &obe::script::GameObject::send_init_arg_from_lua;
        bindGameObject["load_game_object"] = sol::overload(
            [](obe::script::GameObject* self, obe::scene::Scene& scene, vili::node& obj) -> void {
                return self->load_game_object(scene, obj);
            },
            [](obe::script::GameObject* self, obe::scene::Scene& scene, vili::node& obj,
                obe::engine::ResourceManager* resources) -> void {
                return self->load_game_object(scene, obj, resources);
            });
        bindGameObject["update"] = &obe::script::GameObject::update;
        bindGameObject["delete_object"] = &obe::script::GameObject::delete_object;
        bindGameObject["access"] = &obe::script::GameObject::access;
        bindGameObject["get_constructor"] = &obe::script::GameObject::get_constructor;
        bindGameObject["initialize"] = &obe::script::GameObject::initialize;
        bindGameObject["set_permanent"] = &obe::script::GameObject::set_permanent;
        bindGameObject["is_permanent"] = &obe::script::GameObject::is_permanent;
        bindGameObject["get_outer_environment"] = &obe::script::GameObject::get_outer_environment;
        bindGameObject["set_state"] = &obe::script::GameObject::set_state;
        bindGameObject["dump"] = &obe::script::GameObject::dump;
        bindGameObject["load"] = &obe::script::GameObject::load;
        bindGameObject["load_source"] = &obe::script::GameObject::load_source;
        bindGameObject["deletable"] = &obe::script::GameObject::deletable;
    }
    void LoadClassGameObjectDatabase(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["script"].get<sol::table>();
        sol::usertype<obe::script::GameObjectDatabase> bindGameObjectDatabase
            = ScriptNamespace.new_usertype<obe::script::GameObjectDatabase>(
                "GameObjectDatabase", sol::call_constructor, sol::default_constructor);
        bindGameObjectDatabase["get_requirements_for_game_object"]
            = &obe::script::GameObjectDatabase::get_requirements_for_game_object;
        bindGameObjectDatabase["get_definition_for_game_object"]
            = &obe::script::GameObjectDatabase::get_definition_for_game_object;
        bindGameObjectDatabase["ApplyRequirements"]
            = &obe::script::GameObjectDatabase::ApplyRequirements;
        bindGameObjectDatabase["clear"] = &obe::script::GameObjectDatabase::clear;
    }
    void LoadClassLuaState(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["script"].get<sol::table>();
        sol::usertype<obe::script::LuaState> bindLuaState
            = ScriptNamespace.new_usertype<obe::script::LuaState>(
                "LuaState", sol::call_constructor, sol::default_constructor);
        bindLuaState["load_config"] = &obe::script::LuaState::load_config;
    }
    void LoadFunctionSafeLuaCall(sol::state_view state)
    {
        sol::table ScriptNamespace = state["obe"]["script"].get<sol::table>();
    }
};