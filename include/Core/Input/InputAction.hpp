#pragma once

#include <functional>
#include <vector>

#include <Input/InputActionEvent.hpp>
#include <Input/InputCondition.hpp>
#include <Time/TimeCheck.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Types/Identifiable.hpp>

namespace obe::Input
{
    /**
     * \brief Function callback type for InputAction
     */
    using ActionCallback = std::function<void(const InputActionEvent& event)>;

    /**
     * \brief Action triggered by one or more Keyboard key(s)
     * @Bind
     */
    class InputAction : public Types::Identifiable
    {
    private:
        Triggers::TriggerGroup* m_actionTrigger;
        ActionCallback m_callback = [](const InputActionEvent& event) {};
        std::vector<InputCondition> m_combinations;
        std::vector<std::string> m_contexts;
        Time::TimeCheck m_interval;
        Time::TimeCheck m_repeat;
        bool m_state = true;

    public:
        /**
         * \brief Creates a new InputAction
         * \param triggerPtr Pointer to the TriggerGroup
         * \param id Id of the InputAction
         */
        explicit InputAction(
            Triggers::TriggerGroup* triggerPtr, const std::string& id);
        /**
         * \brief Adds an InputCondition to the InputAction
         * \param condition An InputCondition to add to the InputAction
         */
        void addCondition(InputCondition condition);
        /**
         * \brief Adds a context to the InputAction
         * \param context New context for the InputAction
         */
        void addContext(const std::string& context);
        /**
         * \brief Check if the InputAction is enabled
         * \return true if the InputAction is enabled, false otherwise
         */
        bool check() const;
        /**
         * \brief Clears all the InputCondition of the InputAction
         */
        void clearConditions();
        /**
         * \brief Adds a new Callback
         * \param callback A function that will be called when the Action is
         * triggered
         */
        void connect(ActionCallback callback);
        /**
         * \brief Get all the contexts the InputAction is in
         * \return A std::vector of std::string containing all the contexts
         */
        std::vector<std::string> getContexts() const;
        /**
         * \brief Gets the delay required between two InputAction triggerings
         * \return The delay required between two InputAction triggerings (in
         * ms)
         */
        Time::TimeUnit getInterval() const;
        /**
         * \brief Gets the delay between two 'Hold' callbacks activations
         * \return The delay required between two 'Hold' callbacks activations
         */
        Time::TimeUnit getRepeat() const;
        /**
         * \brief Sets the delay required between two InputAction triggerings
         * \param delay Delay required between two InputAction triggerings
         * (in ms)
         */
        void setInterval(Time::TimeUnit delay);
        /**
         * \brief Sets the delay between two 'Hold' callbacks activations
         * \param delay Delay required between two 'Hold' callbacks activations
         */
        void setRepeat(Time::TimeUnit delay);
        /**
         * \brief Updates the InputAction
         */
        void update();
    };
} // namespace obe::Input
