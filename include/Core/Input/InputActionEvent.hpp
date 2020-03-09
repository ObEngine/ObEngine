#pragma once

#include <Input/InputCondition.hpp>

namespace obe::Input
{
    class InputAction;
    /**
     * \brief Model to send to KeyboardAction callbacks as only parameter
     */
    class InputActionEvent
    {
    private:
        InputAction& m_action;
        InputCondition& m_condition;

    public:
        /**
         * \brief Creates a new KeyboardActionEvent
         * \param action Action linked to the event
         * \param condition Condition that triggered the event <REVISION> Add
         *        specific combination
         */
        InputActionEvent(InputAction& action, InputCondition& condition);
        /**
         * \brief Get the KeyboardAction linked to the KeyboardActionEvent
         * \return A pointer to the KeyboardAction linked to the
         *         KeyboardActionEvent
         */
        [[nodiscard]] InputAction& getAction() const;
        /**
         * \brief Get the InputCondition that triggered the KeyboardAction
         * \return A pointer to the KeyClass that represents the key that
         *         triggered the KeyboardAction
         */
        InputCondition& getCondition() const;
    };
} // namespace obe::Input