#pragma once

#include <memory>

#include <Event/EventGroup.hpp>
#include <Input/InputButton.hpp>
#include <Input/InputButtonState.hpp>

namespace obe::events
{
    namespace Keys
    {
        /**
        * \brief Event triggered when the state of an InputButton changes
        * \noconstructor
        */
        struct StateChanged
        {
            const input::InputButtonState state;
            const input::InputButtonState previous_state;
        };
    }
}

namespace obe::input
{
    class InputButtonMonitor;
    using InputButtonMonitorPtr = std::shared_ptr<InputButtonMonitor>;

    /**
     * \brief A class to monitor and update states of an InputButton
     */
    class InputButtonMonitor
    {
    private:
        InputButton& m_button;
        InputButtonState m_button_state = InputButtonState::Idle;
        bool m_should_refresh = false;

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
        [[nodiscard]] InputButton& get_button() const;
        /**
         * \brief Gets the state of the InputButton (InputButtonState)
         * \return The enum of value from InputButtonState corresponding to the
         *         state of the monitored InputButton
         */
        [[nodiscard]] InputButtonState get_state() const;
        /**
         * \brief Updates the InputButtonMonitor (needed to modify the linked
         *        InputButtonState)
         */
        void update(event::EventGroupPtr events);
        bool check_for_refresh() const;
    };
} // namespace obe::input
