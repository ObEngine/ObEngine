#include <Bindings/obe/scene/Exceptions/Exceptions.hpp>

#include <Scene/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::scene::Exceptions::bindings
{
    void load_class_child_not_in_scene_node(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::ChildNotInSceneNode> bind_child_not_in_scene_node
            = Exceptions_namespace.new_usertype<obe::scene::Exceptions::ChildNotInSceneNode>(
                "ChildNotInSceneNode", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::ChildNotInSceneNode(
                    void*, void*, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::ChildNotInSceneNode>,
                    obe::BaseException>());
    }
    void load_class_game_object_already_exists(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::GameObjectAlreadyExists>
            bind_game_object_already_exists
            = Exceptions_namespace.new_usertype<obe::scene::Exceptions::GameObjectAlreadyExists>(
                "GameObjectAlreadyExists", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::GameObjectAlreadyExists(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::GameObjectAlreadyExists>,
                    obe::BaseException>());
    }
    void load_class_invalid_scene_file(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::InvalidSceneFile> bind_invalid_scene_file
            = Exceptions_namespace.new_usertype<obe::scene::Exceptions::InvalidSceneFile>(
                "InvalidSceneFile", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::InvalidSceneFile(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::InvalidSceneFile>,
                    obe::BaseException>());
    }
    void load_class_missing_scene_file_block(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::MissingSceneFileBlock> bind_missing_scene_file_block
            = Exceptions_namespace.new_usertype<obe::scene::Exceptions::MissingSceneFileBlock>(
                "MissingSceneFileBlock", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::MissingSceneFileBlock(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::MissingSceneFileBlock>,
                    obe::BaseException>());
    }
    void load_class_scene_on_load_callback_error(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::SceneOnLoadCallbackError>
            bind_scene_on_load_callback_error
            = Exceptions_namespace.new_usertype<obe::scene::Exceptions::SceneOnLoadCallbackError>(
                "SceneOnLoadCallbackError", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::SceneOnLoadCallbackError(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::SceneOnLoadCallbackError>,
                    obe::BaseException>());
    }
    void load_class_scene_script_loading_error(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::SceneScriptLoadingError>
            bind_scene_script_loading_error
            = Exceptions_namespace.new_usertype<obe::scene::Exceptions::SceneScriptLoadingError>(
                "SceneScriptLoadingError", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::SceneScriptLoadingError(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::SceneScriptLoadingError>,
                    obe::BaseException>());
    }
    void load_class_unknown_collider(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::UnknownCollider> bind_unknown_collider
            = Exceptions_namespace.new_usertype<obe::scene::Exceptions::UnknownCollider>(
                "UnknownCollider", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::UnknownCollider(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::UnknownCollider>,
                    obe::BaseException>());
    }
    void load_class_unknown_game_object(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::UnknownGameObject> bind_unknown_game_object
            = Exceptions_namespace.new_usertype<obe::scene::Exceptions::UnknownGameObject>(
                "UnknownGameObject", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::UnknownGameObject(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::UnknownGameObject>,
                    obe::BaseException>());
    }
    void load_class_unknown_sprite(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::UnknownSprite> bind_unknown_sprite
            = Exceptions_namespace.new_usertype<obe::scene::Exceptions::UnknownSprite>(
                "UnknownSprite", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::UnknownSprite(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::UnknownSprite>,
                    obe::BaseException>());
    }
};