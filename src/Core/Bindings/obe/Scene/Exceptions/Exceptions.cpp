#include <Bindings/obe/Scene/Exceptions/Exceptions.hpp>

#include <Scene/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Scene::Exceptions::Bindings
{
    void LoadClassChildNotInSceneNode(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::ChildNotInSceneNode> bindChildNotInSceneNode
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::ChildNotInSceneNode>(
                "ChildNotInSceneNode", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::ChildNotInSceneNode(
                    void*, void*, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Scene::Exceptions::ChildNotInSceneNode>,
                    obe::BaseException>());
    }
    void LoadClassGameObjectAlreadyExists(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::GameObjectAlreadyExists> bindGameObjectAlreadyExists
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::GameObjectAlreadyExists>(
                "GameObjectAlreadyExists", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::GameObjectAlreadyExists(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Scene::Exceptions::GameObjectAlreadyExists>,
                    obe::BaseException>());
    }
    void LoadClassInvalidSceneFile(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::InvalidSceneFile> bindInvalidSceneFile
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::InvalidSceneFile>(
                "InvalidSceneFile", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::InvalidSceneFile(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Scene::Exceptions::InvalidSceneFile>,
                    obe::BaseException>());
    }
    void LoadClassMissingSceneFileBlock(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::MissingSceneFileBlock> bindMissingSceneFileBlock
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::MissingSceneFileBlock>(
                "MissingSceneFileBlock", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::MissingSceneFileBlock(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Scene::Exceptions::MissingSceneFileBlock>,
                    obe::BaseException>());
    }
    void LoadClassSceneOnLoadCallbackError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::SceneOnLoadCallbackError> bindSceneOnLoadCallbackError
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::SceneOnLoadCallbackError>(
                "SceneOnLoadCallbackError", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::SceneOnLoadCallbackError(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Scene::Exceptions::SceneOnLoadCallbackError>,
                    obe::BaseException>());
    }
    void LoadClassSceneScriptLoadingError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::SceneScriptLoadingError> bindSceneScriptLoadingError
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::SceneScriptLoadingError>(
                "SceneScriptLoadingError", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::SceneScriptLoadingError(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Scene::Exceptions::SceneScriptLoadingError>,
                    obe::BaseException>());
    }
    void LoadClassUnknownCollider(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::UnknownCollider> bindUnknownCollider
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::UnknownCollider>(
                "UnknownCollider", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::UnknownCollider(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Scene::Exceptions::UnknownCollider>,
                    obe::BaseException>());
    }
    void LoadClassUnknownGameObject(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::UnknownGameObject> bindUnknownGameObject
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::UnknownGameObject>(
                "UnknownGameObject", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::UnknownGameObject(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Scene::Exceptions::UnknownGameObject>,
                    obe::BaseException>());
    }
    void LoadClassUnknownSprite(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Scene"]["exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::UnknownSprite> bindUnknownSprite
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::UnknownSprite>(
                "UnknownSprite", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::UnknownSprite(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::Scene::Exceptions::UnknownSprite>,
                    obe::BaseException>());
    }
};