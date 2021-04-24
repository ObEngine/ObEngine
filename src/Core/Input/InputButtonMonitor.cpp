#include <Debug/Logger.hpp>
#include <Event/EventGroup.hpp>
#include <Input/InputButtonMonitor.hpp>

namespace obe::Input
{
    InputButtonMonitor::InputButtonMonitor(InputButton& button)
        : m_button(button)
    {
        Debug::Log->debug("Started monitoring InputButton '{}'", m_button.getName());
    }

    InputButtonMonitor::~InputButtonMonitor()
    {
        Debug::Log->debug("Stopped monitoring InputButton '{}'", m_button.getName());
    }

    InputButton& InputButtonMonitor::getButton() const
    {
        return m_button;
    }

    InputButtonState InputButtonMonitor::getState() const
    {
        return m_buttonState;
    }

    void InputButtonMonitor::update(Event::EventGroupPtr events)
    {
        Debug::Log->trace("Updating InputMonitor of {}", m_button.getName());
        const bool keyPressed = m_button.isPressed();
        const InputButtonState oldState = m_buttonState;
        m_shouldRefresh = false;
        if (keyPressed
            && (m_buttonState == InputButtonState::Idle
                || m_buttonState == InputButtonState::Released))
        {
            m_buttonState = InputButtonState::Pressed;
        }
        else if (keyPressed && m_buttonState == InputButtonState::Pressed)
        {
            m_buttonState = InputButtonState::Hold;
        }
        else if (!keyPressed
            && (m_buttonState == InputButtonState::Pressed
                || m_buttonState == InputButtonState::Hold))
        {
            m_buttonState = InputButtonState::Released;
        }
        else if (!keyPressed && m_buttonState == InputButtonState::Released)
        {
            m_buttonState = InputButtonState::Idle;
        }
        if (oldState != m_buttonState)
        {
            m_shouldRefresh = true;
            events->trigger(m_button.getName(),
                Events::Keys::StateChanged { m_buttonState, oldState });
        }
    }

    bool InputButtonMonitor::checkForRefresh() const
    {
        return m_shouldRefresh;
    }
} // namespace obe::Input
