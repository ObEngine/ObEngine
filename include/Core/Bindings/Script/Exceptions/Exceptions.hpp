#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Script::Exceptions::Bindings
{
    void LoadClassNoScriptComponent(sol::state_view state);
};