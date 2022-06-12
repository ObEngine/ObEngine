#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::Scene::Bindings
{
    void LoadClassLoaded(sol::state_view state);
};