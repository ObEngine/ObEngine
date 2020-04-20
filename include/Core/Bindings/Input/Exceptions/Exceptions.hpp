#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Input::Exceptions::Bindings
{
    void LoadClassInputButtonInvalidOperation(sol::state_view state);
    void LoadClassInvalidInputButtonState(sol::state_view state);
    void LoadClassUnknownInputAction(sol::state_view state);
    void LoadClassUnknownInputButton(sol::state_view state);
};