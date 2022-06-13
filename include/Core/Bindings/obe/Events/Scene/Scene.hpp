#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::scene::Bindings
{
    void LoadClassLoaded(sol::state_view state);
};