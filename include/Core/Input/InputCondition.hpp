#pragma once

#include <vector>

#include <Input/InputButton.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/InputButtonState.hpp>
#include <Types/FlagSet.hpp>

namespace obe::Input
{
    using InputCombinationElement
        = std::pair<InputButtonMonitorPtr, Types::FlagSet<InputButtonState>>;
    using InputCombination = std::vector<InputCombinationElement>;

    /**
     * \brief A class represented the required conditions to trigger an
     *        InputAction
     */
    class InputCondition
    {
    private:
        bool m_enabled = false;
        InputCombination m_triggerConditions;

    public:
        /**
         * \brief Adds a new InputCombinationElement to the InputCondition
         * \param combinationElement The InputCombinationElement to add to the
         *        InputCondition
         */
        void addCombinationElement(InputCombinationElement combinationElement);
        /**
         * \brief Checks if the condition is fulfilled
         * \return true if the InputCondition is fulfilled, false otherwise
         */
        [[nodiscard]] bool check() const;
        /**
         * \brief Clears the InputCondition
         */
        void clear();
        /**
         * \nobind
         * \brief Gets the InputCombination used by the InputCondition
         * \return The InputCombination used by the InputCondition
         */
        [[nodiscard]] InputCombination getCombination() const;
        /**
         * TODO: Fix this nobind
         * \nobind
         * \brief Sets the new required InputCombination to trigger the
         *        InputCondition
         * \param combination The new InputCombination
         */
        void setCombination(const InputCombination& combination);
    };
} // namespace obe::Input