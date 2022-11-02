#pragma once

#include <Exception.hpp>
#include <vector>

#include "Utils/StringUtils.hpp"

/**
 * \nobind
 */
namespace obe::input::exceptions
{
    class InvalidInputSourceState : public Exception<InvalidInputSourceState>
    {
    public:
        using Exception::Exception;
        InvalidInputSourceState(std::string_view state, DebugInfo info)
            : Exception(info)
        {
            this->error("'{}' is not a valid InputSourceState value", state);
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
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), utils::string::quote);
            this->hint(
                "Try one of the following InputAction : ({}...)", fmt::join(suggestions, ", "));
        }
    };

    class UnknownInputSource : public Exception<UnknownInputSource>
    {
    public:
        using Exception::Exception;
        UnknownInputSource(std::string_view button_name,
            const std::vector<std::string>& existing_buttons, DebugInfo info)
            : Exception(info)
        {
            this->error("InputSource named '{}' does not exists", button_name);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(button_name.data(), existing_buttons, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), utils::string::quote);
            this->hint(
                "Try one of the following InputSources : ({}...)", fmt::join(suggestions, ", "));
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

    class InputSourceAlreadyInCombination : public Exception<InputSourceAlreadyInCombination>
    {
    public:
        using Exception::Exception;
        InputSourceAlreadyInCombination(std::string_view input_source, DebugInfo info)
            : Exception(info)
        {
            this->error("The same InputSource '{}' can't appear twice in the same "
                        "InputCondition",
                input_source);
            this->hint("If you want to handle more that one state for the same "
                       "InputSource, create a separate combination");
        }
    };

    class InputSourceNotInCombination : public Exception<InputSourceNotInCombination>
    {
    public:
        using Exception::Exception;
        InputSourceNotInCombination(std::string_view input_source, DebugInfo info)
            : Exception(info)
        {
            this->error("The InputSource '{}' does not appear in InputCondition", input_source);
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
} // namespace obe::input::exceptions
