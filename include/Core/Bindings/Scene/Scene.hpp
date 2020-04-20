#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Scene::Bindings
{
    void LoadClassCamera(sol::state_view state);
    void LoadClassScene(sol::state_view state);
    void LoadClassSceneNode(sol::state_view state);
    void LoadFunctionSceneGetGameObjectProxy(sol::state_view state);
    void LoadFunctionSceneCreateGameObjectProxy(sol::state_view state);
};