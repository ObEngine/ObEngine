#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Events::Keys::Bindings
{
    void LoadClassStateChanged(sol::state_view state);
};
