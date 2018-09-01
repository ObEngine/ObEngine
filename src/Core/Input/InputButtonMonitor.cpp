#include <algorithm>

#include <Input/InputButtonMonitor.hpp>
#include <Input/KeyList.hpp>
#include "Debug/Logger.hpp"

namespace obe::Input
{
    InputButtonMonitor::InputButtonMonitor(InputButton* button)
    {
        m_button = button;
    }

    InputButton* InputButtonMonitor::getButton() const
    {
        return m_button;
    }

    InputButtonState InputButtonMonitor::getState() const
    {
        return m_buttonState;
    }

    void InputButtonMonitor::update()
    {
        const bool keyPressed = m_button->isPressed();
        if (keyPressed && (m_buttonState == InputButtonState::Idle || m_buttonState == InputButtonState::Released))
        {
            m_buttonState = InputButtonState::Pressed;
        }
        else if (keyPressed && m_buttonState == InputButtonState::Pressed)
        {
            m_buttonState = InputButtonState::Hold;
        }
        else if (!keyPressed && (m_buttonState == InputButtonState::Pressed || m_buttonState == InputButtonState::Hold))
        {
            m_buttonState = InputButtonState::Released;
            Monitors::RequireRefresh = true;
        }
        else if (!keyPressed && m_buttonState == InputButtonState::Released)
        {
            m_buttonState = InputButtonState::Idle;
        }
    }

    unsigned InputButtonMonitor::getReferences() const
    {
        return m_references;
    }

    InputButtonMonitorPtr::InputButtonMonitorPtr(InputButtonMonitor* monitor)
    {
        m_monitor = monitor;
        m_monitor->m_references++;
    }

    InputButton* InputButtonMonitorPtr::operator->() const
    {
        return m_monitor->getButton();
    }

    InputButton* InputButtonMonitorPtr::getButton() const
    {
        return m_monitor->getButton();
    }

    InputButtonState InputButtonMonitorPtr::getState() const
    {
        return m_monitor->getState();
    }

    InputButtonMonitorPtr::~InputButtonMonitorPtr()
    {
        m_monitor->m_references--;
    }

    namespace Monitors
    {
        void UpdateMonitors()
        {
            RequireRefresh = false;
            Monitors.erase(std::remove_if(Monitors.begin(), Monitors.end(), UpdateMonitorsAndRemoveIfNoReferences), Monitors.end());
        }

        bool UpdateMonitorsAndRemoveIfNoReferences(const std::unique_ptr<InputButtonMonitor>& element)
        {
            if (element->getReferences() > 0)
            {
                element->update();
                return false;
            }
            else
            {
                return true;
            }
        }

        InputButtonMonitorPtr Monitor(const std::string& buttonId)
        {
            return Monitor(GetKey(buttonId));
        }

        InputButtonMonitorPtr Monitor(InputButton* button)
        {
            for (auto& monitor : Monitors)
            {
                if (monitor->getButton() == button)
                {
                    return InputButtonMonitorPtr(monitor.get());
                }
            }
            Monitors.push_back(std::make_unique<InputButtonMonitor>(button));
            return InputButtonMonitorPtr(Monitors.back().get());
        }
    }
}
