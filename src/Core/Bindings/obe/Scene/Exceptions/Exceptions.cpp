#include <Bindings/obe/Scene/Exceptions/Exceptions.hpp>

#include <Scene/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Scene::Exceptions::Bindings
{
    void LoadClassChildNotInSceneNode(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::ChildNotInSceneNode> bindChildNotInSceneNode
            = ExceptionsNamespace
                  .new_usertype<obe::Scene::Exceptions::ChildNotInSceneNode>(
                      "ChildNotInSceneNode", sol::call_constructor,
                      sol::constructors<obe::Scene::Exceptions::ChildNotInSceneNode(
                          void*, void*, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassGameObjectAlreadyExists(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::GameObjectAlreadyExists>
            bindGameObjectAlreadyExists
            = ExceptionsNamespace
                  .new_usertype<obe::Scene::Exceptions::GameObjectAlreadyExists>(
                      "GameObjectAlreadyExists", sol::call_constructor,
                      sol::constructors<obe::Scene::Exceptions::GameObjectAlreadyExists(
                          std::string_view, std::string_view, std::string_view,
                          obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassMissingSceneFileBlock(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::MissingSceneFileBlock>
            bindMissingSceneFileBlock
            = ExceptionsNamespace
                  .new_usertype<obe::Scene::Exceptions::MissingSceneFileBlock>(
                      "MissingSceneFileBlock", sol::call_constructor,
                      sol::constructors<obe::Scene::Exceptions::MissingSceneFileBlock(
                          std::string_view, std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassSceneOnLoadCallbackError(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::SceneOnLoadCallbackError>
            bindSceneOnLoadCallbackError
            = ExceptionsNamespace
                  .new_usertype<obe::Scene::Exceptions::SceneOnLoadCallbackError>(
                      "SceneOnLoadCallbackError", sol::call_constructor,
                      sol::constructors<obe::Scene::Exceptions::SceneOnLoadCallbackError(
                          std::string_view, std::string_view, std::string_view,
                          obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassSceneScriptLoadingError(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::SceneScriptLoadingError>
            bindSceneScriptLoadingError
            = ExceptionsNamespace
                  .new_usertype<obe::Scene::Exceptions::SceneScriptLoadingError>(
                      "SceneScriptLoadingError", sol::call_constructor,
                      sol::constructors<obe::Scene::Exceptions::SceneScriptLoadingError(
                          std::string_view, std::string_view, std::string_view,
                          obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownCollider(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::UnknownCollider> bindUnknownCollider
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::UnknownCollider>(
                "UnknownCollider", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::UnknownCollider(
                    std::string_view, std::string_view, const std::vector<std::string>&,
                    obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownGameObject(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::UnknownGameObject> bindUnknownGameObject
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::UnknownGameObject>(
                "UnknownGameObject", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::UnknownGameObject(
                    std::string_view, std::string_view, const std::vector<std::string>&,
                    obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownSprite(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Scene"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Scene::Exceptions::UnknownSprite> bindUnknownSprite
            = ExceptionsNamespace.new_usertype<obe::Scene::Exceptions::UnknownSprite>(
                "UnknownSprite", sol::call_constructor,
                sol::constructors<obe::Scene::Exceptions::UnknownSprite(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
};