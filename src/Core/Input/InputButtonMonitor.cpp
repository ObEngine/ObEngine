#include <Debug/Logger.hpp>
#include <Input/InputButtonMonitor.hpp>

namespace obe::input
{
    InputButtonMonitor::InputButtonMonitor(InputSource& button)
        : m_input_source(button)
    {
        debug::Log->debug("Started monitoring InputSource '{}'", m_input_source.get_name());
    }

    InputButtonMonitor::~InputButtonMonitor()
    {
        debug::Log->debug("Stopped monitoring InputSource '{}'", m_input_source.get_name());
    }

    InputSource& InputButtonMonitor::get_input_source() const
    {
        return m_input_source;
    }

    InputSourceState InputButtonMonitor::get_state() const
    {
        return m_button_state;
    }

    void InputButtonMonitor::update(event::EventGroupPtr events)
    {
        debug::Log->trace("Updating InputMonitor of {}", m_input_source.get_name());
        const bool key_pressed = m_input_source.is_pressed();
        const InputSourceState old_state = m_button_state;
        m_should_refresh = false;
        if (key_pressed
            && (m_button_state == InputSourceState::Idle
                || m_button_state == InputSourceState::Released))
        {
            m_button_state = InputSourceState::Pressed;
        }
        else if (key_pressed && m_button_state == InputSourceState::Pressed)
        {
            m_button_state = InputSourceState::Hold;
        }
        else if (!key_pressed
            && (m_button_state == InputSourceState::Pressed
                || m_button_state == InputSourceState::Hold))
        {
            m_button_state = InputSourceState::Released;
        }
        else if (!key_pressed && m_button_state == InputSourceState::Released)
        {
            m_button_state = InputSourceState::Idle;
        }
        if (old_state != m_button_state)
        {
            m_should_refresh = true;
            events->trigger(m_input_source.get_name(),
                events::Keys::StateChanged { m_button_state, old_state, m_input_source });
        }
    }

    bool InputButtonMonitor::check_for_refresh() const
    {
        return m_should_refresh;
    }
} // namespace obe::input
