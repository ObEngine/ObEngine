#include <algorithm>

#include <SFML/Window/Keyboard.hpp>

#include <Debug/Logger.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Triggers/TriggerManager.hpp>

namespace obe::Input
{
    InputButtonMonitor::InputButtonMonitor(InputButton& button)
        : m_button(button)
    {
        Debug::Log->trace("Started monitoring InputButton {}", m_button.getName());
    }

    InputButtonMonitor::~InputButtonMonitor()
    {
        Debug::Log->trace("Un-monitoring InputButton {}", m_button.getName());
    }

    InputButton& InputButtonMonitor::getButton() const
    {
        return m_button;
    }

    InputButtonState InputButtonMonitor::getState() const
    {
        return m_buttonState;
    }

    void InputButtonMonitor::update(Triggers::TriggerGroupPtr triggers)
    {
        const bool keyPressed = m_button.isPressed();
        const InputButtonState oldState = m_buttonState;
        if (keyPressed
            && (m_buttonState == InputButtonState::Idle
                || m_buttonState == InputButtonState::Released))
        {
            m_buttonState = InputButtonState::Pressed;
            // InputButtonMonitor::RequireRefresh = true;
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
            // InputButtonMonitor::RequireRefresh = true;
        }
        else if (!keyPressed && m_buttonState == InputButtonState::Released)
        {
            m_buttonState = InputButtonState::Idle;
        }
        if (oldState != m_buttonState)
        {
            triggers->pushParameter(m_button.getName(), "previousState", oldState);
            triggers->pushParameter(m_button.getName(), "state", m_buttonState);
            triggers->trigger(m_button.getName());
        }
    }

} // namespace obe::Input
