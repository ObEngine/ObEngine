#include <algorithm>

#include <SFML/Window/Keyboard.hpp>

#include <Debug/Logger.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/KeyList.hpp>
#include <Triggers/TriggerDatabase.hpp>

namespace obe::Input
{
    Triggers::TriggerGroupPtr InputButtonMonitor::KeyTriggers;
    std::vector<std::shared_ptr<InputButtonMonitor>> InputButtonMonitor::TriggerMonitors;
    void InputButtonMonitor::InitKeyTriggerGroup()
    {
        InputButtonMonitor::KeyTriggers = Triggers::TriggerGroupPtr(
            Triggers::TriggerDatabase::GetInstance().createTriggerGroup("Global", "Keys"),
            Triggers::TriggerGroupPtrRemover);
        for (auto const& [key, val] : AllKeys)
        {
            Input::InputButton* button = val.get();
            InputButtonMonitor::KeyTriggers->addTrigger(button->getName());
            InputButtonMonitor::KeyTriggers->getTrigger(button->getName())
                .lock()
                ->onRegister([button](const Triggers::TriggerEnv& env) {
                    for (auto& monitor : InputButtonMonitor::TriggerMonitors)
                    {
                        if (monitor->getButton() == button)
                            return;
                    }
                    InputButtonMonitor::TriggerMonitors.push_back(Monitors::Monitor(button));
                });
            InputButtonMonitor::KeyTriggers->getTrigger(button->getName())
                .lock()
                ->onUnregister([button](const Triggers::TriggerEnv& env) {
                    InputButtonMonitor::TriggerMonitors.erase(
                        std::remove_if(InputButtonMonitor::TriggerMonitors.begin(),
                            InputButtonMonitor::TriggerMonitors.end(),
                            [button](
                                const auto& monitor) { return monitor->getButton() == button; }),
                        InputButtonMonitor::TriggerMonitors.end());
                });
        }
    }

    InputButtonMonitor::InputButtonMonitor(InputButton* button)
    {
        Debug::Log->trace("Started monitoring InputButton {}", button->getName());
        m_button = button;
    }

    InputButtonMonitor::~InputButtonMonitor()
    {
        Debug::Log->trace("Un-monitoring InputButton {}", m_button->getName());
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
        const InputButtonState oldState = m_buttonState;
        if (keyPressed
            && (m_buttonState == InputButtonState::Idle
                   || m_buttonState == InputButtonState::Released))
        {
            m_buttonState = InputButtonState::Pressed;
            Monitors::RequireRefresh = true;
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
            Monitors::RequireRefresh = true;
        }
        else if (!keyPressed && m_buttonState == InputButtonState::Released)
        {
            m_buttonState = InputButtonState::Idle;
        }
        if (oldState != m_buttonState)
        {
            InputButtonMonitor::KeyTriggers->pushParameter(
                m_button->getName(), "previousState", oldState);
            InputButtonMonitor::KeyTriggers->pushParameter(
                m_button->getName(), "state", m_buttonState);
            InputButtonMonitor::KeyTriggers->trigger(m_button->getName());
        }
    }

    namespace Monitors
    {
        std::vector<std::weak_ptr<InputButtonMonitor>> Monitors;
        bool RequireRefresh = true;
        void UpdateMonitors()
        {
            RequireRefresh = false;
            Monitors.erase(std::remove_if(Monitors.begin(), Monitors.end(),
                               UpdateMonitorsAndRemoveIfNotRemoved),
                Monitors.end());
        }

        bool UpdateMonitorsAndRemoveIfNotRemoved(const std::weak_ptr<InputButtonMonitor>& element)
        {
            if (auto monitor = element.lock())
            {
                monitor->update();
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
                if (const auto sharedMonitor = monitor.lock())
                {
                    if (sharedMonitor->getButton() == button)
                        return InputButtonMonitorPtr(sharedMonitor);
                }
            }
            InputButtonMonitorPtr monitor = std::make_shared<InputButtonMonitor>(button);
            Monitors.push_back(monitor);
            return std::move(monitor);
        }
    } // namespace Monitors
} // namespace obe::Input
