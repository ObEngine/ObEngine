#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Scene::Exceptions::Bindings
{
    void LoadClassChildNotInSceneNode(sol::state_view state);
    void LoadClassGameObjectAlreadyExists(sol::state_view state);
    void LoadClassMissingSceneFileBlock(sol::state_view state);
    void LoadClassSceneOnLoadCallbackError(sol::state_view state);
    void LoadClassSceneScriptLoadingError(sol::state_view state);
    void LoadClassUnknownCollider(sol::state_view state);
    void LoadClassUnknownGameObject(sol::state_view state);
    void LoadClassUnknownSprite(sol::state_view state);
};