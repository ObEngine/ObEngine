#include <Input/InputAction.hpp>
#include <Triggers/TriggerManager.hpp>
#include <Utils/VectorUtils.hpp>
#include <utility>

namespace obe::Input
{
    InputAction::InputAction(Triggers::TriggerGroup* triggerPtr, const std::string& id)
        : Identifiable(id)
    {
        m_actionTrigger = triggerPtr;
        triggerPtr->add(id);
    }

    void InputAction::addCondition(const InputCondition& condition)
    {
        m_conditions.push_back(condition);
    }

    void InputAction::clearConditions()
    {
        m_conditions.clear();
    }

    void InputAction::connect(ActionCallback callback)
    {
        m_callback = std::move(callback);
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
        if (!m_enabled)
            return;
        for (InputCondition& condition : m_conditions)
        {
            if (condition.check())
            {
                if (m_state)
                {
                    if (m_repeat
                            .over()) // Reset repeat when combination is unchecked <REVISION>
                    {
                        m_repeat.reset();
                        const InputActionEvent ev(*this, condition);
                        if (m_callback)
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
                        if (m_callback)
                            m_callback(InputActionEvent(*this, condition));
                    }
                }
            }
            else
            {
                m_repeat.stop();
            }
        }
    }

    std::vector<InputButton*> InputAction::getInvolvedButtons() const
    {
        std::vector<InputButton*> involvedButtons;
        for (const InputCondition& condition : m_conditions)
        {
            for (const InputCombinationElement& combinationElement :
                condition.getCombination())
            {
                involvedButtons.push_back(combinationElement.first);
            }
        }
        return involvedButtons;
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

    bool InputAction::isEnabled() const
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