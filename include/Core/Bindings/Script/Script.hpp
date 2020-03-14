#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Script::Bindings
{
    void LoadClassGameObject(sol::state_view state);
    void LoadClassGameObjectDatabase(sol::state_view state);
};