#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Bindings::Bindings
{
    void LoadFunctionIndexAllBindings(sol::state_view state);
};