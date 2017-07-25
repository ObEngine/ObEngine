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

        /**
         * \brief A class represented the required conditions to trigger an InputAction
         * @Bind
         */
        class InputCondition
        {
        private:
            InputCombination m_triggerConditions;
            bool isKeyAlreadyInCombination(InputButton* button);
        public:
            InputCondition();
            /**
             * \brief Uses a parsable string to define the InputCombination <DOCUMENT>
             * \param code The string that contains the new InputCombination
             */
            void setCombinationCode(const std::string& code);
            /**
             * \brief Adds a new InputCombinationElement to the InputCondition
             * \param combinationElement The InputCombinationElement to add to the InputCondition
             */
            void addCombinationElement(InputCombinationElement combinationElement);
            /**
             * \brief Sets the new required InputCombination to trigger the InputCondition
             * \param combination The new InputCombination
             */
            void setCombination(const InputCombination& combination);
            /**
             * \brief Checks if the condition is fulfilled
             * \return true if the InputCondition is fulfilled, false otherwise
             */
            bool check() const;
        };
    }
}
