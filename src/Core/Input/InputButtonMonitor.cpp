#include <Debug/Logger.hpp>
#include <Input/InputButtonMonitor.hpp>

namespace obe::input
{
    InputButtonMonitor::InputButtonMonitor(InputButton& button)
        : m_button(button)
    {
        debug::Log->debug("Started monitoring InputButton '{}'", m_button.get_name());
    }

    InputButtonMonitor::~InputButtonMonitor()
    {
        debug::Log->debug("Stopped monitoring InputButton '{}'", m_button.get_name());
    }

    InputButton& InputButtonMonitor::get_button() const
    {
        return m_button;
    }

    InputButtonState InputButtonMonitor::get_state() const
    {
        return m_button_state;
    }

    void InputButtonMonitor::update(event::EventGroupPtr events)
    {
        debug::Log->trace("Updating InputMonitor of {}", m_button.get_name());
        const bool key_pressed = m_button.is_pressed();
        const InputButtonState old_state = m_button_state;
        m_should_refresh = false;
        if (key_pressed
            && (m_button_state == InputButtonState::Idle
                || m_button_state == InputButtonState::Released))
        {
            m_button_state = InputButtonState::Pressed;
        }
        else if (key_pressed && m_button_state == InputButtonState::Pressed)
        {
            m_button_state = InputButtonState::Hold;
        }
        else if (!key_pressed
            && (m_button_state == InputButtonState::Pressed
                || m_button_state == InputButtonState::Hold))
        {
            m_button_state = InputButtonState::Released;
        }
        else if (!key_pressed && m_button_state == InputButtonState::Released)
        {
            m_button_state = InputButtonState::Idle;
        }
        if (old_state != m_button_state)
        {
            m_should_refresh = true;
            events->trigger(
                m_button.get_name(), events::Keys::StateChanged { m_button_state, old_state });
        }
    }

    bool InputButtonMonitor::check_for_refresh() const
    {
        return m_should_refresh;
    }
} // namespace obe::input
