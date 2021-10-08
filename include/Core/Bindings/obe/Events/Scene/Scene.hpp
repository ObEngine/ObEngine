#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Events::Scene::Bindings
{
    void LoadClassLoaded(sol::state_view state);
};
