#pragma once

#include <memory>

#include <Event/EventGroup.hpp>
#include <Input/InputButton.hpp>
#include <Input/InputButtonState.hpp>

namespace obe::Events::Keys
{
    /**
     * \brief Event triggered when the state of an InputButton changes
     * \noconstructor
     */
    struct StateChanged
    {
        const Input::InputButtonState state;
        const Input::InputButtonState previousState;
    };
}

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
        void update(Event::EventGroupPtr events);
    };
} // namespace obe::Input