#pragma once

#include <functional>
#include <vector>

#include <Event/EventGroup.hpp>
#include <Input/InputCondition.hpp>
#include <Time/Chronometer.hpp>
#include <Types/Identifiable.hpp>

namespace obe::input
{

    /**
     * \brief Action triggered by one or more Keyboard key(s)
     */
    class InputAction : public Types::Identifiable
    {
    private:
        event::EventGroup* e_actions;
        std::vector<InputCondition> m_conditions;
        std::vector<std::string> m_contexts;
        time::Chronometer m_interval;
        time::Chronometer m_repeat;
        bool m_state = true;
        bool m_enabled = false;

    public:
        /**
         * \brief Creates a new InputAction
         * \param actions_events Pointer to the Actions EventGroup
         * \param id Id of the InputAction
         */
        explicit InputAction(event::EventGroup* actions_events, const std::string& id);
        /**
         * \brief Adds an InputCondition to the InputAction
         * \param condition An InputCondition to add to the InputAction
         */
        void add_condition(const InputCondition& condition);
        /**
         * \brief Adds a context to the InputAction
         * \param context New context for the InputAction
         */
        void add_context(const std::string& context);
        /**
         * \brief Check if the InputAction is enabled
         * \return true if the InputAction is enabled, false otherwise
         */
        [[nodiscard]] bool check() const;
        /**
         * \brief Clears all the InputCondition of the InputAction
         */
        void clear_conditions();
        /**
         * \brief Get all the contexts the InputAction is in
         * \return A std::vector of std::string containing all the contexts
         */
        [[nodiscard]] std::vector<std::string> get_contexts() const;
        /**
         * \brief Gets the delay required between two InputAction triggerings
         * \return The delay required between two InputAction triggerings (in
         * ms)
         */
        [[nodiscard]] time::TimeUnit get_interval() const;
        /**
         * \brief Gets the delay between two 'Hold' callbacks activations
         * \return The delay required between two 'Hold' callbacks activations
         */
        [[nodiscard]] time::TimeUnit get_repeat() const;
        /**
         * \brief Sets the delay required between two InputAction triggerings
         * \param delay Delay required between two InputAction triggerings
         *        (in ms)
         */
        void set_interval(time::TimeUnit delay);
        /**
         * \brief Sets the delay between two 'Hold' callbacks activations
         * \param delay Delay required between two 'Hold' callbacks activations
         */
        void set_repeat(time::TimeUnit delay);
        /**
         * \brief Updates the InputAction
         */
        void update();
        [[nodiscard]] std::vector<InputButton*> get_involved_buttons() const;

        void enable(const std::vector<InputButtonMonitorPtr>& monitors);
        void disable();
        bool is_enabled() const;
    };
} // namespace obe::input

namespace obe::events
{
    namespace Actions
    {
        /**
        * \brief Event containing information about an Action that has been triggered
        * \noconstructor
        */
        struct Action
        {
            input::InputAction& action;
            input::InputCondition& condition;
        };
    }
};
