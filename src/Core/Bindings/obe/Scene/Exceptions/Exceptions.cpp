#include <Bindings/obe/Scene/Exceptions/Exceptions.hpp>

#include <Scene/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::scene::Exceptions::Bindings
{
    void LoadClassChildNotInSceneNode(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::ChildNotInSceneNode> bindChildNotInSceneNode
            = ExceptionsNamespace.new_usertype<obe::scene::Exceptions::ChildNotInSceneNode>(
                "ChildNotInSceneNode", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::ChildNotInSceneNode(
                    void*, void*, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::ChildNotInSceneNode>,
                    obe::BaseException>());
    }
    void LoadClassGameObjectAlreadyExists(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::GameObjectAlreadyExists> bindGameObjectAlreadyExists
            = ExceptionsNamespace.new_usertype<obe::scene::Exceptions::GameObjectAlreadyExists>(
                "GameObjectAlreadyExists", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::GameObjectAlreadyExists(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::GameObjectAlreadyExists>,
                    obe::BaseException>());
    }
    void LoadClassInvalidSceneFile(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::InvalidSceneFile> bindInvalidSceneFile
            = ExceptionsNamespace.new_usertype<obe::scene::Exceptions::InvalidSceneFile>(
                "InvalidSceneFile", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::InvalidSceneFile(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::InvalidSceneFile>,
                    obe::BaseException>());
    }
    void LoadClassMissingSceneFileBlock(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::MissingSceneFileBlock> bindMissingSceneFileBlock
            = ExceptionsNamespace.new_usertype<obe::scene::Exceptions::MissingSceneFileBlock>(
                "MissingSceneFileBlock", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::MissingSceneFileBlock(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::MissingSceneFileBlock>,
                    obe::BaseException>());
    }
    void LoadClassSceneOnLoadCallbackError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::SceneOnLoadCallbackError> bindSceneOnLoadCallbackError
            = ExceptionsNamespace.new_usertype<obe::scene::Exceptions::SceneOnLoadCallbackError>(
                "SceneOnLoadCallbackError", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::SceneOnLoadCallbackError(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::SceneOnLoadCallbackError>,
                    obe::BaseException>());
    }
    void LoadClassSceneScriptLoadingError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::SceneScriptLoadingError> bindSceneScriptLoadingError
            = ExceptionsNamespace.new_usertype<obe::scene::Exceptions::SceneScriptLoadingError>(
                "SceneScriptLoadingError", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::SceneScriptLoadingError(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::SceneScriptLoadingError>,
                    obe::BaseException>());
    }
    void LoadClassUnknownCollider(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::UnknownCollider> bindUnknownCollider
            = ExceptionsNamespace.new_usertype<obe::scene::Exceptions::UnknownCollider>(
                "UnknownCollider", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::UnknownCollider(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::UnknownCollider>,
                    obe::BaseException>());
    }
    void LoadClassUnknownGameObject(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::UnknownGameObject> bindUnknownGameObject
            = ExceptionsNamespace.new_usertype<obe::scene::Exceptions::UnknownGameObject>(
                "UnknownGameObject", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::UnknownGameObject(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::UnknownGameObject>,
                    obe::BaseException>());
    }
    void LoadClassUnknownSprite(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::scene::Exceptions::UnknownSprite> bindUnknownSprite
            = ExceptionsNamespace.new_usertype<obe::scene::Exceptions::UnknownSprite>(
                "UnknownSprite", sol::call_constructor,
                sol::constructors<obe::scene::Exceptions::UnknownSprite(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::scene::Exceptions::UnknownSprite>,
                    obe::BaseException>());
    }
};