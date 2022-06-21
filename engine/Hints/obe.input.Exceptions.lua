---@meta

obe.input.Exceptions = {};
---@class obe.input.Exceptions.InputButtonAlreadyInCombination : obe.Exception[obe.input.Exceptions.InputButtonAlreadyInCombination]
obe.input.Exceptions._InputButtonAlreadyInCombination = {};

--- obe.input.Exceptions.InputButtonAlreadyInCombination constructor
---
---@param button string #
---@param info obe.DebugInfo #
---@return obe.input.Exceptions.InputButtonAlreadyInCombination
function obe.input.Exceptions.InputButtonAlreadyInCombination(button, info) end



---@class obe.input.Exceptions.InputButtonInvalidOperation : obe.Exception[obe.input.Exceptions.InputButtonInvalidOperation]
obe.input.Exceptions._InputButtonInvalidOperation = {};

--- obe.input.Exceptions.InputButtonInvalidOperation constructor
---
---@param input_button_type string #
---@param operation_type string #
---@param info obe.DebugInfo #
---@return obe.input.Exceptions.InputButtonInvalidOperation
function obe.input.Exceptions.InputButtonInvalidOperation(input_button_type, operation_type, info) end



---@class obe.input.Exceptions.InvalidGamepadButton : obe.Exception[obe.input.Exceptions.InvalidGamepadButton]
obe.input.Exceptions._InvalidGamepadButton = {};

--- obe.input.Exceptions.InvalidGamepadButton constructor
---
---@param gamepad_button_id string #
---@param info obe.DebugInfo #
---@return obe.input.Exceptions.InvalidGamepadButton
function obe.input.Exceptions.InvalidGamepadButton(gamepad_button_id, info) end



---@class obe.input.Exceptions.InvalidInputButtonState : obe.Exception[obe.input.Exceptions.InvalidInputButtonState]
obe.input.Exceptions._InvalidInputButtonState = {};

--- obe.input.Exceptions.InvalidInputButtonState constructor
---
---@param state string #
---@param info obe.DebugInfo #
---@return obe.input.Exceptions.InvalidInputButtonState
function obe.input.Exceptions.InvalidInputButtonState(state, info) end



---@class obe.input.Exceptions.InvalidInputCombinationCode : obe.Exception[obe.input.Exceptions.InvalidInputCombinationCode]
obe.input.Exceptions._InvalidInputCombinationCode = {};

--- obe.input.Exceptions.InvalidInputCombinationCode constructor
---
---@param action string #
---@param combination_code string #
---@param info obe.DebugInfo #
---@return obe.input.Exceptions.InvalidInputCombinationCode
function obe.input.Exceptions.InvalidInputCombinationCode(action, combination_code, info) end



---@class obe.input.Exceptions.InvalidInputTypeEnumValue : obe.Exception[obe.input.Exceptions.InvalidInputTypeEnumValue]
obe.input.Exceptions._InvalidInputTypeEnumValue = {};

--- obe.input.Exceptions.InvalidInputTypeEnumValue constructor
---
---@param enum_value number #
---@param info obe.DebugInfo #
---@return obe.input.Exceptions.InvalidInputTypeEnumValue
function obe.input.Exceptions.InvalidInputTypeEnumValue(enum_value, info) end



---@class obe.input.Exceptions.UnknownInputAction : obe.Exception[obe.input.Exceptions.UnknownInputAction]
obe.input.Exceptions._UnknownInputAction = {};

--- obe.input.Exceptions.UnknownInputAction constructor
---
---@param action_name string #
---@param existing_actions string[] #
---@param info obe.DebugInfo #
---@return obe.input.Exceptions.UnknownInputAction
function obe.input.Exceptions.UnknownInputAction(action_name, existing_actions, info) end



---@class obe.input.Exceptions.UnknownInputButton : obe.Exception[obe.input.Exceptions.UnknownInputButton]
obe.input.Exceptions._UnknownInputButton = {};

--- obe.input.Exceptions.UnknownInputButton constructor
---
---@param button_name string #
---@param existing_buttons string[] #
---@param info obe.DebugInfo #
---@return obe.input.Exceptions.UnknownInputButton
function obe.input.Exceptions.UnknownInputButton(button_name, existing_buttons, info) end



return obe.input.Exceptions;