#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Input::Bindings
{
    void LoadClassInputAction(sol::state_view state);
    void LoadClassInputActionEvent(sol::state_view state);
    void LoadClassInputButton(sol::state_view state);
    void LoadClassInputButtonMonitor(sol::state_view state);
    void LoadClassInputCondition(sol::state_view state);
    void LoadClassInputManager(sol::state_view state);
    void LoadEnumAxisThresholdDirection(sol::state_view state);
    void LoadEnumInputButtonState(sol::state_view state);
    void LoadEnumInputType(sol::state_view state);
    void LoadFunctionInputButtonStateToString(sol::state_view state);
    void LoadFunctionStringToInputButtonState(sol::state_view state);
    void LoadFunctionInputTypeToString(sol::state_view state);
};