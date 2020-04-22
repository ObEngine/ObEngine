#pragma once

#include "Utils/StringUtils.hpp"

#include <Exception.hpp>
#include <vector>

namespace obe::Input::Exceptions
{
    class InputButtonInvalidOperation : public Exception
    {
    public:
        InputButtonInvalidOperation(std::string_view inputButtonType,
            std::string_view operationType, DebugInfo info)
            : Exception("InputButtonInvalidOperation", info)
        {
            this->error("Tried to do a '{}' operation on an InputButton of type '{}' "
                        "which is incompatible",
                operationType, inputButtonType);
        }
    };

    class InvalidInputButtonState : public Exception
    {
    public:
        InvalidInputButtonState(std::string_view state, DebugInfo info)
            : Exception("InvalidInputButtonState", info)
        {
            this->error("'{}' is not a valid InputButtonState value", state);
            this->hint(
                "Try one of the following values : (Idle, Hold, Pressed, Released)");
        }
    };

    class UnknownInputAction : public Exception
    {
    public:
        UnknownInputAction(std::string_view actionName,
            const std::vector<std::string>& existingActions, DebugInfo info)
            : Exception("UnknownInputAction", info)
        {
            this->error("InputAction named '{}' does not exists", actionName);
            std::vector<std::string> sortedByDistance = existingActions;
            std::sort(sortedByDistance.begin(), sortedByDistance.end(),
                [actionName](const std::string& s1, const std::string& s2) {
                    return Utils::String::distance(s1, actionName)
                        < Utils::String::distance(s2, actionName);
                });
            this->hint("Try one of the following InputAction : ({}...)",
                fmt::join(
                    std::vector(sortedByDistance.begin(), sortedByDistance.begin() + 5),
                    ", "));
        }
    };

    class UnknownInputButton : public Exception
    {
    public:
        UnknownInputButton(std::string_view buttonName,
            const std::vector<std::string>& existingButtons, DebugInfo info)
            : Exception("UnknownInputButton", info)
        {
            this->error("InputButton named '{}' does not exists", buttonName);
            std::vector<std::string> sortedByDistance = existingButtons;
            std::sort(sortedByDistance.begin(), sortedByDistance.end(),
                [buttonName](const std::string& s1, const std::string& s2) {
                    return Utils::String::distance(s1, buttonName)
                        < Utils::String::distance(s2, buttonName);
                });
            this->hint("Try one of the following InputButton : ({}...)",
                fmt::join(std::vector<std::string_view>(
                              sortedByDistance.begin(), sortedByDistance.begin() + 5),
                    ", "));
        }
    };

    class InvalidInputCombinationCode : public Exception
    {
    public:
        InvalidInputCombinationCode(
            std::string_view action, std::string_view combinationCode, DebugInfo info)
            : Exception("InvalidInputCombinationCode", info)
        {
            this->error(
                "The following InputCombinationCode '{}' for InputAction '{}' is invalid",
                combinationCode, action);
        }
    };

    class InputButtonAlreadyInCombination : public Exception
    {
    public:
        InputButtonAlreadyInCombination(std::string_view button, DebugInfo info)
            : Exception("InputButtonAlreadyInCombination", info)
        {
            this->error("The same InputButton '{}' can't appear twice in the same "
                        "InputCondition",
                button);
            this->hint("If you want to handle more that one state for the same "
                       "InputButton, create a separate combination");
        }
    };
}