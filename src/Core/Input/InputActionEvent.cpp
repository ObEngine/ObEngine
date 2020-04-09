#include <Input/InputActionEvent.hpp>

namespace obe::Input
{
    InputActionEvent::InputActionEvent(InputAction& action, InputCondition& condition)
        : m_action(action)
        , m_condition(condition)
    {
    }

    InputAction& InputActionEvent::getAction() const
    {
        return m_action;
    }

    InputCondition& InputActionEvent::getCondition() const
    {
        return m_condition;
    }
} // namespace obe::Input