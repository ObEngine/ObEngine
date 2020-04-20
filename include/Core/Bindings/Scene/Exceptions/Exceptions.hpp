#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Scene::Exceptions::Bindings
{
    void LoadClassChildNotInSceneNode(sol::state_view state);
};