#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Utils::Vector::Bindings
{
    void LoadFunctionContains(sol::state_view state);
    void LoadFunctionJoin(sol::state_view state);
};