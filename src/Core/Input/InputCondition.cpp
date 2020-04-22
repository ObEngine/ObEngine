#include <Input/InputCondition.hpp>
#include <Input/InputManager.hpp>
#include <Utils/StringUtils.hpp>

namespace obe::Input
{

    InputCombination InputCondition::getCombination() const
    {
        return m_combination;
    }

    InputButtonState InputCondition::getButtonState(InputButton* button) const
    {
        for (const InputButtonMonitorPtr& monitor : m_monitors)
        {
            if (&monitor->getButton() == button)
            {
                return monitor->getState();
            }
        }
    }

    InputCondition::InputCondition()
    {
    }

    void InputCondition::addCombinationElement(
        const InputCombinationElement combinationElement)
    {
        m_combination.push_back(combinationElement);
        m_enabled = true;
    }

    void InputCondition::setCombination(const InputCombination& combination)
    {
        m_combination = combination;
        m_enabled = true;
    }

    void InputCondition::enable(const std::vector<InputButtonMonitorPtr>& monitors)
    {
        m_enabled = true;
        for (const auto& monitor : monitors)
        {
            for (const InputCombinationElement& combination : m_combination)
            {
                if (&monitor->getButton() == combination.first)
                {
                    m_monitors.push_back(monitor);
                }
            }
        }
    }

    void InputCondition::disable()
    {
        m_enabled = false;
        m_monitors.clear();
    }

    bool InputCondition::isEnabled() const
    {
        return m_enabled;
    }

    bool InputCondition::check() const
    {
        if (!m_enabled)
            return false;
        bool conditionOk = true;
        for (const InputCombinationElement& element : m_combination)
        {
            if (!(element.second & getButtonState(element.first)))
            {
                conditionOk = false;
                break;
            }
        }
        return conditionOk;
    }

    void InputCondition::clear()
    {
        m_combination.clear();
        m_enabled = false;
    }
} // namespace obe::Input