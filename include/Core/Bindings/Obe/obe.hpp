#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Bindings
{
    void LoadFunctionInitEngine(sol::state_view state);
};