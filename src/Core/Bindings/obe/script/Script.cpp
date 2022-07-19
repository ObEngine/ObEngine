#include <Bindings/obe/script/Script.hpp>

#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>
#include <Script/LuaState.hpp>
#include <Script/Scripting.hpp>

#include <Bindings/Config.hpp>

namespace obe::script::bindings
{
    void load_enum_environment_target(sol::state_view state)
    {
        sol::table script_namespace = state["obe"]["script"].get<sol::table>();
        script_namespace.new_enum<obe::script::EnvironmentTarget>("EnvironmentTarget",
            { { "Outer", obe::script::EnvironmentTarget::Outer },
                { "Inner", obe::script::EnvironmentTarget::Inner } });
    }
    void load_class_game_object(sol::state_view state)
    {
        sol::table script_namespace = state["obe"]["script"].get<sol::table>();
        sol::usertype<obe::script::GameObject> bind_game_object
            = script_namespace.new_usertype<obe::script::GameObject>("GameObject",
                sol::call_constructor,
                sol::constructors<obe::script::GameObject(
                    sol::state_view, const std::string&, const std::string&)>(),
                sol::base_classes,
                sol::bases<obe::types::Identifiable, obe::types::Serializable>());
        bind_game_object["get_type"] = &obe::script::GameObject::get_type;
        bind_game_object["does_have_animator"] = &obe::script::GameObject::does_have_animator;
        bind_game_object["does_have_collider"] = &obe::script::GameObject::does_have_collider;
        bind_game_object["does_have_sprite"] = &obe::script::GameObject::does_have_sprite;
        bind_game_object["does_have_script_engine"]
            = &obe::script::GameObject::does_have_script_engine;
        bind_game_object["get_update_state"] = &obe::script::GameObject::get_update_state;
        bind_game_object["set_update_state"] = &obe::script::GameObject::set_update_state;
        bind_game_object["Animator"] = sol::property(&obe::script::GameObject::get_animator);
        bind_game_object["Collider"] = sol::property(&obe::script::GameObject::get_collider);
        bind_game_object["Sprite"] = sol::property(&obe::script::GameObject::get_sprite);
        bind_game_object["SceneNode"] = sol::property(&obe::script::GameObject::get_scene_node);
        bind_game_object["exec"] = &obe::script::GameObject::exec;
        bind_game_object["init_from_vili"] = &obe::script::GameObject::init_from_vili;
        bind_game_object["load_game_object"] = sol::overload(
            [](obe::script::GameObject* self, obe::scene::Scene& scene, vili::node& obj) -> void {
                return self->load_game_object(scene, obj);
            },
            [](obe::script::GameObject* self, obe::scene::Scene& scene, vili::node& obj,
                obe::engine::ResourceManager* resources) -> void {
                return self->load_game_object(scene, obj, resources);
            });
        bind_game_object["update"] = &obe::script::GameObject::update;
        bind_game_object["destroy"] = &obe::script::GameObject::destroy;
        bind_game_object["access"] = &obe::script::GameObject::access;
        bind_game_object["get_constructor"] = &obe::script::GameObject::get_constructor;
        bind_game_object["initialize"] = &obe::script::GameObject::initialize;
        bind_game_object["set_permanent"] = &obe::script::GameObject::set_permanent;
        bind_game_object["is_permanent"] = &obe::script::GameObject::is_permanent;
        bind_game_object["get_outer_environment"] = &obe::script::GameObject::get_outer_environment;
        bind_game_object["set_state"] = &obe::script::GameObject::set_state;
        bind_game_object["schema"] = &obe::script::GameObject::schema;
        bind_game_object["dump"] = &obe::script::GameObject::dump;
        bind_game_object["load"] = &obe::script::GameObject::load;
        bind_game_object["load_source"] = &obe::script::GameObject::load_source;
        bind_game_object["is_parent_of_component"]
            = &obe::script::GameObject::is_parent_of_component;
        bind_game_object["deletable"] = &obe::script::GameObject::deletable;
    }
    void load_class_game_object_database(sol::state_view state)
    {
        sol::table script_namespace = state["obe"]["script"].get<sol::table>();
        sol::usertype<obe::script::GameObjectDatabase> bind_game_object_database
            = script_namespace.new_usertype<obe::script::GameObjectDatabase>(
                "GameObjectDatabase", sol::call_constructor, sol::default_constructor);
        bind_game_object_database["get_requirements_for_game_object"]
            = &obe::script::GameObjectDatabase::get_requirements_for_game_object;
        bind_game_object_database["get_definition_for_game_object"]
            = &obe::script::GameObjectDatabase::get_definition_for_game_object;
        bind_game_object_database["clear"] = &obe::script::GameObjectDatabase::clear;
    }
    void load_class_lua_state(sol::state_view state)
    {
        sol::table script_namespace = state["obe"]["script"].get<sol::table>();
        sol::usertype<obe::script::LuaState> bind_lua_state
            = script_namespace.new_usertype<obe::script::LuaState>(
                "LuaState", sol::call_constructor, sol::default_constructor);
        bind_lua_state["load_config"] = &obe::script::LuaState::load_config;
    }
    void load_function_sol_call_status_to_string(sol::state_view state)
    {
        sol::table script_namespace = state["obe"]["script"].get<sol::table>();
        script_namespace.set_function(
            "sol_call_status_to_string", &obe::script::sol_call_status_to_string);
    }
    void load_function_safe_lua_call(sol::state_view state)
    {
        sol::table script_namespace = state["obe"]["script"].get<sol::table>();
    }
};