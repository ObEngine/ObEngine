#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::Scene::bindings
{
    void load_class_loaded(sol::state_view state);
};