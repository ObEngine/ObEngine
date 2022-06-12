#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::Keys::Bindings
{
    void LoadClassStateChanged(sol::state_view state);
};