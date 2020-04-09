#pragma once

#include <memory>

#include <Input/InputButton.hpp>
#include <Input/InputButtonState.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe::Input
{
    class InputButtonMonitor;
    using InputButtonMonitorPtr = std::shared_ptr<InputButtonMonitor>;

    /**
     * \brief A class to monitor and update states of an InputButton
     * \bind{InputButtonMonitor}
     */
    class InputButtonMonitor
    {
    private:
        InputButton& m_button;
        InputButtonState m_buttonState = InputButtonState::Idle;

    public:
        /**
         * \brief Constructor of InputButtonMonition
         * \param button Pointer to the InputButton to monitor
         */
        explicit InputButtonMonitor(InputButton& button);
        ~InputButtonMonitor();
        /**
         * \brief Gets a pointer to the monitored InputButton
         * \return A pointer to the monitored InputButton
         */
        [[nodiscard]] InputButton& getButton() const;
        /**
         * \brief Gets the state of the InputButton (InputButtonState)
         * \return The enum of value from InputButtonState corresponding to the
         *         state of the monitored InputButton
         */
        [[nodiscard]] InputButtonState getState() const;
        /**
         * \brief Updates the InputButtonMonitor (needed to modify the linked
         *        InputButtonState)
         */
        void update(Triggers::TriggerGroupPtr triggers);
    };
} // namespace obe::Input