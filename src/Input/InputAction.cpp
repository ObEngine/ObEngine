#include <Input/InputAction.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Input
    {
        InputAction::InputAction(const std::string& id) : Identifiable(id), m_interval(0), m_repeat(0)
        {
        }

        void InputAction::addCondition(InputCondition condition)
        {
            m_combinations.push_back(condition);
        }

        std::vector<std::string> InputAction::getContexts() const
        {
            return m_contexts;
        }

        void InputAction::addContext(const std::string& context)
        {
            if (!Utils::Vector::isInList(context, m_contexts))
                m_contexts.push_back(context);
        }

        void InputAction::setInterval(Time::TimeUnit delay)
        {
            m_interval.setDelay(delay);
        }

        Time::TimeUnit InputAction::getInterval() const
        {
            return m_interval.getDelay();
        }

        void InputAction::setRepeat(Time::TimeUnit delay)
        {
            m_repeat.setDelay(delay);
        }

        Time::TimeUnit InputAction::getRepeat() const
        {
            return m_repeat.getDelay();
        }

        void InputAction::connect(ActionCallback callback)
        {
            m_callback = callback;
        }

        void InputAction::update()
        {
            for (InputCondition& combination : m_combinations)
            {
                if (combination.check())
                {
                    if (m_state)
                    {
                        if (m_repeat.resetIfOver())
                        {
                            m_callback(InputActionEvent(this, &combination));
                        }
                    }
                    else
                    {
                        if (m_interval.resetIfOver())
                        {
                            m_state = true;
                            m_callback(InputActionEvent(this, &combination));
                        }
                    }
                }
            }
        }
    }
}
