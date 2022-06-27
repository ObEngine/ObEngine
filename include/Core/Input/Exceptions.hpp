#pragma once

#include "Utils/StringUtils.hpp"

#include <Exception.hpp>
#include <vector>

/**
 * \nobind
 */
namespace obe::input::Exceptions
{
    class InputButtonInvalidOperation : public Exception<InputButtonInvalidOperation>
    {
    public:
        using Exception::Exception;
        InputButtonInvalidOperation(
            std::string_view input_button_type, std::string_view operation_type, DebugInfo info)
            : Exception(info)
        {
            this->error("Tried to do a '{}' operation on an InputButton of type '{}' "
                        "which is incompatible",
                operation_type, input_button_type);
        }
    };

    class InvalidInputButtonState : public Exception<InvalidInputButtonState>
    {
    public:
        using Exception::Exception;
        InvalidInputButtonState(std::string_view state, DebugInfo info)
            : Exception(info)
        {
            this->error("'{}' is not a valid InputButtonState value", state);
            this->hint("Try one of the following values : (Idle, Hold, Pressed, Released)");
        }
    };

    class UnknownInputAction : public Exception<UnknownInputAction>
    {
    public:
        using Exception::Exception;
        UnknownInputAction(std::string_view action_name,
            const std::vector<std::string>& existing_actions, DebugInfo info)
            : Exception(info)
        {
            this->error("InputAction named '{}' does not exists", action_name);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(action_name.data(), existing_actions, 5);
            std::ranges::transform(suggestions
                , suggestions.begin(), utils::string::quote);
            this->hint(
                "Try one of the following InputAction : ({}...)", fmt::join(suggestions, ", "));
        }
    };

    class UnknownInputButton : public Exception<UnknownInputButton>
    {
    public:
        using Exception::Exception;
        UnknownInputButton(std::string_view button_name,
            const std::vector<std::string>& existing_buttons, DebugInfo info)
            : Exception(info)
        {
            this->error("InputButton named '{}' does not exists", button_name);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(button_name.data(), existing_buttons, 5);
            std::ranges::transform(suggestions
                , suggestions.begin(), &utils::string::quote);
            this->hint(
                "Try one of the following InputButton : ({}...)", fmt::join(suggestions, ", "));
        }
    };

    class InvalidInputCombinationCode : public Exception<InvalidInputCombinationCode>
    {
    public:
        using Exception::Exception;
        InvalidInputCombinationCode(
            std::string_view action, std::string_view combination_code, DebugInfo info)
            : Exception(info)
        {
            this->error("The following InputCombinationCode '{}' for InputAction '{}' is invalid",
                combination_code, action);
        }
    };

    class InputButtonAlreadyInCombination : public Exception<InputButtonAlreadyInCombination>
    {
    public:
        using Exception::Exception;
        InputButtonAlreadyInCombination(std::string_view button, DebugInfo info)
            : Exception(info)
        {
            this->error("The same InputButton '{}' can't appear twice in the same "
                        "InputCondition",
                button);
            this->hint("If you want to handle more that one state for the same "
                       "InputButton, create a separate combination");
        }
    };

    class InvalidInputTypeEnumValue : public Exception<InvalidInputTypeEnumValue>
    {
    public:
        using Exception::Exception;
        InvalidInputTypeEnumValue(int enum_value, DebugInfo info)
            : Exception(info)
        {
            this->error("Enum InputType can't have invalid value ({})", enum_value);
        }
    };

    class InvalidGamepadButton : public Exception<InvalidGamepadButton>
    {
    public:
        using Exception::Exception;
        InvalidGamepadButton(std::string_view gamepad_button_id, DebugInfo info)
            : Exception(info)
        {
            this->error("Gamepad input '{}' is not a valid identifier", gamepad_button_id);
            this->hint("Gamepad input should look like this : 'GP_<GAMEPAD_ID>_BTN_<BUTTON_ID>' or "
                       "'GP_X_AXIS_<AXIS_NAME>_<AXIS_DIRECTION>",
                gamepad_button_id);
        }
    };
}
