#include <utility>

#include <Input/InputAction.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::input
{
    InputAction::InputAction(event::EventGroup* actions_events, const std::string& id)
        : Identifiable(id)
    {
        e_actions = actions_events;
        e_actions->add<events::Actions::Action>(id);
    }

    void InputAction::add_condition(const InputCondition& condition)
    {
        m_conditions.push_back(condition);
    }

    void InputAction::clear_conditions()
    {
        m_conditions.clear();
    }

    std::vector<std::string> InputAction::get_contexts() const
    {
        return m_contexts;
    }

    void InputAction::add_context(const std::string& context)
    {
        if (!utils::vector::contains(context, m_contexts))
            m_contexts.push_back(context);
    }

    void InputAction::set_interval(time::TimeUnit delay)
    {
        m_interval.set_limit(delay);
    }

    time::TimeUnit InputAction::get_interval() const
    {
        return m_interval.get_limit();
    }

    void InputAction::set_repeat(time::TimeUnit delay)
    {
        m_repeat.set_limit(delay);
    }

    time::TimeUnit InputAction::get_repeat() const
    {
        return m_repeat.get_limit();
    }

    void InputAction::update()
    {
        if (!m_enabled)
            return;
        for (InputCondition& condition : m_conditions)
        {
            if (condition.check())
            {
                if (m_state)
                {
                    if (m_repeat.is_over()) // Reset repeat when combination is unchecked <REVISION>
                    {
                        m_repeat.reset();
                        e_actions->trigger(m_id, events::Actions::Action { *this, condition });
                    }
                }
                else
                {
                    if (m_interval
                            .is_over()) // What is this for, when does m_state goes back to false ? <REVISION>
                    {
                        m_interval.reset();
                        m_state = true;
                    }
                }
            }
            else
            {
                m_repeat.stop();
            }
        }
    }

    std::vector<InputSource*> InputAction::get_involved_input_sources() const
    {
        std::vector<InputSource*> involved_input_sources;
        for (const InputCondition& condition : m_conditions)
        {
            for (const InputCombinationElement& combination_element : condition.get_combination())
            {
                involved_input_sources.push_back(combination_element.first);
            }
        }
        return involved_input_sources;
    }

    void InputAction::enable(const std::vector<InputButtonMonitorPtr>& monitors)
    {
        m_enabled = true;
        for (InputCondition& condition : m_conditions)
        {
            condition.enable(monitors);
        }
    }

    void InputAction::disable()
    {
        m_enabled = false;
        for (InputCondition& condition : m_conditions)
        {
            condition.disable();
        }
    }

    bool InputAction::is_enabled() const
    {
        return m_enabled;
    }

    bool InputAction::check() const
    {
        if (!m_enabled)
            return false;
        for (const InputCondition& combination : m_conditions)
        {
            if (combination.check())
            {
                if (m_state)
                {
                    if (m_repeat.is_over())
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
} // namespace obe::input
