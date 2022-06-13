#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::constraints::Bindings
{
    void LoadGlobalDefault(sol::state_view state);
};