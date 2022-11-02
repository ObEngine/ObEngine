#pragma once

#include <Event/EventGroup.hpp>
#include <Input/InputSourceState.hpp>
#include <Input/InputSource.hpp>
#include <memory>

namespace obe::events
{
    namespace Keys
    {
        struct Pressed
        {
        };
        /**
        * \brief Event triggered when the state of an InputButton changes
        * \noconstructor
        */
        struct StateChanged
        {
            const input::InputSourceState state;
            const input::InputSourceState previous_state;
        };
    } // namespace Keys
} // namespace obe::events

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
        InputSource& m_button;
        InputSourceState m_button_state = InputSourceState::Idle;
        bool m_should_refresh = false;

    public:
        /**
         * \brief Constructor of InputButtonMonition
         * \param button Pointer to the InputButton to monitor
         */
        explicit InputButtonMonitor(InputSource& button);
        ~InputButtonMonitor();
        /**
         * \brief Gets a pointer to the monitored InputButton
         * \return A pointer to the monitored InputButton
         */
        [[nodiscard]] InputSource& get_input_source() const;
        /**
         * \brief Gets the state of the InputButton (InputButtonState)
         * \return The enum of value from InputButtonState corresponding to the
         *         state of the monitored InputButton
         */
        [[nodiscard]] InputSourceState get_state() const;
        /**
         * \brief Updates the InputButtonMonitor (needed to modify the linked
         *        InputButtonState)
         */
        void update(event::EventGroupPtr events);
        bool check_for_refresh() const;
    };
} // namespace obe::input
