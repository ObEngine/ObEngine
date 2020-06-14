#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Input::Exceptions::Bindings
{
    void LoadClassInputButtonAlreadyInCombination(sol::state_view state);
    void LoadClassInputButtonInvalidOperation(sol::state_view state);
    void LoadClassInvalidInputButtonState(sol::state_view state);
    void LoadClassInvalidInputCombinationCode(sol::state_view state);
    void LoadClassInvalidInputTypeEnumValue(sol::state_view state);
    void LoadClassUnknownInputAction(sol::state_view state);
    void LoadClassUnknownInputButton(sol::state_view state);
};