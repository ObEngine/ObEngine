#pragma once

#include <vector>

#include <Input/InputButton.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/InputButtonState.hpp>

namespace obe
{
    namespace Input
    {
        using InputCombinationElement = std::pair<InputButtonMonitorPtr, std::vector<InputButtonState>>;
        using InputCombination = std::vector<InputCombinationElement>;
        class InputCondition
        {
        private:
            InputCombination m_triggerConditions;
            bool isKeyAlreadyInCombination(InputButton* button);
        public:
            InputCondition();
            void setCombinationCode(const std::string& code);
            void addCombinationElement(InputCombinationElement combinationElement);
            void setCombination(const InputCombination& combination);
            bool check() const;
        };
    }
}
