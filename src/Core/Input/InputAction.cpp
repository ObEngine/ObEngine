#include <Input/InputAction.hpp>
#include <Triggers/TriggerManager.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Input
{
    InputAction::InputAction(Triggers::TriggerGroup* triggerPtr, const std::string& id)
        : Identifiable(id)
    {
        m_actionTrigger = triggerPtr;
        triggerPtr->add(id);
    }

    void InputAction::addCondition(InputCondition condition)
    {
        m_combinations.push_back(condition);
    }

    void InputAction::clearConditions()
    {
        m_combinations.clear();
    }

    void InputAction::connect(ActionCallback callback)
    {
        m_callback = callback;
    }

    std::vector<std::string> InputAction::getContexts() const
    {
        return m_contexts;
    }

    void InputAction::addContext(const std::string& context)
    {
        if (!Utils::Vector::contains(context, m_contexts))
            m_contexts.push_back(context);
    }

    void InputAction::setInterval(Time::TimeUnit delay)
    {
        m_interval.setLimit(delay);
    }

    Time::TimeUnit InputAction::getInterval() const
    {
        return m_interval.getLimit();
    }

    void InputAction::setRepeat(Time::TimeUnit delay)
    {
        m_repeat.setLimit(delay);
    }

    Time::TimeUnit InputAction::getRepeat() const
    {
        return m_repeat.getLimit();
    }

    void InputAction::update()
    {
        for (InputCondition& combination : m_combinations)
        {
            if (combination.check())
            {
                if (m_state)
                {
                    if (m_repeat
                            .over()) // Reset repeat when combination is unchecked <REVISION>
                    {
                        m_repeat.reset();
                        const InputActionEvent ev(*this, combination);
                        m_callback(ev);
                        m_actionTrigger->pushParameter(m_id, "event", ev);
                        m_actionTrigger->trigger(m_id);
                    }
                }
                else
                {
                    if (m_interval
                            .over()) // What is this for, when does m_state goes back to false ? <REVISION>
                    {
                        m_interval.reset();
                        m_state = true;
                        m_callback(InputActionEvent(*this, combination));
                    }
                }
            }
            else
            {
                m_repeat.stop();
            }
        }
    }

    bool InputAction::check() const
    {
        for (const InputCondition& combination : m_combinations)
        {
            if (combination.check())
            {
                if (m_state)
                {
                    if (m_repeat.over())
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
} // namespace obe::Input