#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::keys::Bindings
{
    void LoadClassStateChanged(sol::state_view state);
};