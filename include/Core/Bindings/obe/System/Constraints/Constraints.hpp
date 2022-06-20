#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::constraints::bindings
{
    void load_global_default(sol::state_view state);
};