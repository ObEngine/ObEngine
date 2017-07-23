#pragma once

#include <memory>
#include <vector>

#include <Input/InputButton.hpp>
#include <Input/InputButtonState.hpp>

namespace obe
{
    namespace Input
    {
        /**
        * \brief A class to monitor and update states of an InputButton
        */
        class InputButtonMonitor
        {
        private:
            InputButton* m_button = nullptr;
            InputButtonState m_buttonState = InputButtonState::Idle;
            unsigned int m_references = 0;
            friend class InputButtonMonitorPtr;
        public:
            InputButtonMonitor(InputButton* button);
            InputButton* getButton() const;
            InputButtonState getState() const;
            void update();
            unsigned int getReferences() const;
        };

        /**
         * \brief A class to get the states determined by InputButtonMonitor
         */
        class InputButtonMonitorPtr
        {
        private:
            InputButtonMonitor* m_monitor;
            static unsigned int amount;
            unsigned int m_id = 0;
        public:
            InputButtonMonitorPtr(InputButtonMonitor* monitor);
            InputButton* operator->() const;
            InputButton* getButton() const;
            InputButtonState getState() const;
            ~InputButtonMonitorPtr();
        };

        namespace Monitors
        {
            extern std::vector<std::unique_ptr<InputButtonMonitor>> Monitors;
            void UpdateMonitors();
            bool UpdateMonitorsAndRemoveIfNoReferences(const std::unique_ptr<InputButtonMonitor>& element);
            InputButtonMonitorPtr Monitor(const std::string& buttonId);
            InputButtonMonitorPtr Monitor(InputButton* button);
        }
    }
}