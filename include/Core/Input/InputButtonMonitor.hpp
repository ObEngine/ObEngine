#pragma once

#include <memory>
#include <vector>

#include <Input/InputButton.hpp>
#include <Input/InputButtonState.hpp>
#include <Triggers/TriggerGroup.hpp>

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
        static Triggers::TriggerGroupPtr KeyTriggers;
        static std::vector<std::shared_ptr<InputButtonMonitor>> TriggerMonitors;

        /**
         * \brief Update the InputButtonMonitor or returns true if it has no
         * more references to them \param element InputButtonMonitor to update
         * \return true if the InputButtonMonitor should be removed, false
         * otherwise
         */
        static bool UpdateOrClean(const std::weak_ptr<InputButtonMonitor>& element);

    public:
        static void InitKeyTriggerGroup();
        /**
         * \brief Constuctor of InputButtonMonition
         * \param button Pointer to the InputButton to monitor
         */
        InputButtonMonitor(InputButton& button);
        ~InputButtonMonitor();
        /**
         * \brief Gets a pointer to the monitored InputButton
         * \return A pointer to the monitored InputButton
         */
        InputButton& getButton() const;
        /**
         * \brief Gets the state of the InputButton (InputButtonState)
         * \return The enum of value from InputButtonState corresponding to the
         * state of the monitored InputButton
         */
        InputButtonState getState() const;
        /**
         * \brief Updates the InputButtonMonitor (needed to modify the linked
         * InputButtonState)
         */
        void update();

        /**
         * \brief Global list of all InputButtonMonitor
         */
        static std::vector<std::weak_ptr<InputButtonMonitor>> Monitors;
        static bool RequireRefresh;
        /**
         * \brief Updates all the InputButtonMonitor
         */
        static void Update();
        /**
         * \brief Creates a new InputButtonMonitor from an InputButton id
         * \param buttonId Id of the InputButton to monitor
         * \return An InputButtonMonitorPtr managing the underlying
         * InputButtonMonitor
         */
        static InputButtonMonitorPtr Monitor(const std::string& buttonId);
        /**
         * \brief Creates a new InputButtonMonitor from an InputButton pointer
         * \param button Pointer to the InputButton to monitor
         * \return An InputButtonMonitorPtr managing the underlying
         * InputButtonMonitor
         */
        static InputButtonMonitorPtr Monitor(InputButton& button);
    };
} // namespace obe::Input