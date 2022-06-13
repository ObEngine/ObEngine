#include <Input/InputCondition.hpp>

namespace obe::input
{

    InputCombination InputCondition::get_combination() const
    {
        return m_combination;
    }

    InputButtonState InputCondition::get_button_state(InputButton* button) const
    {
        for (const InputButtonMonitorPtr& monitor : m_monitors)
        {
            if (&monitor->get_button() == button)
            {
                return monitor->get_state();
            }
        }
    }

    InputCondition::InputCondition()
    {
    }

    void InputCondition::add_combination_element(const InputCombinationElement combination_element)
    {
        m_combination.push_back(combination_element);
        m_enabled = true;
    }

    void InputCondition::set_combination(const InputCombination& combination)
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
                if (&monitor->get_button() == combination.first)
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

    bool InputCondition::is_enabled() const
    {
        return m_enabled;
    }

    bool InputCondition::check() const
    {
        if (!m_enabled)
            return false;
        bool condition_ok = true;
        for (const InputCombinationElement& element : m_combination)
        {
            if (!(element.second & get_button_state(element.first)))
            {
                condition_ok = false;
                break;
            }
        }
        return condition_ok;
    }

    void InputCondition::clear()
    {
        m_combination.clear();
        m_enabled = false;
    }
} // namespace obe::input
