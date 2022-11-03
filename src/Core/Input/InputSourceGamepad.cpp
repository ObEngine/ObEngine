#include <Input/InputSourceGamepad.hpp>

namespace obe::input
{
    InputSourceGamepadButton::InputSourceGamepadButton(
        unsigned gamepad_index, unsigned button_index, const std::string& name)
        : InputSource(name, "")
        , m_gamepad_index(gamepad_index)
        , m_button_index(button_index)
    {
    }

    uint32_t InputSourceGamepadButton::get_gamepad_index() const
    {
        return m_gamepad_index;
    }

    uint32_t InputSourceGamepadButton::get_button_index() const
    {
        return m_button_index;
    }

    bool InputSourceGamepadButton::is_pressed() const
    {
        return sf::Joystick::isButtonPressed(m_gamepad_index, m_button_index);
    }

    std::string_view InputSourceGamepadButton::type() const
    {
        return InputSourceGamepadButton::Type;
    }

    InputSourceGamepadAxis::InputSourceGamepadAxis(unsigned gamepad_index,
        sf::Joystick::Axis gamepad_axis, std::pair<AxisThresholdDirection, float> axis_threshold,
        const std::string& name)
        : InputSource(name, "")
        , m_gamepad_index(gamepad_index)
        , m_axis(gamepad_axis)
        , m_axis_threshold(std::move(axis_threshold))
    {
    }

    uint32_t InputSourceGamepadAxis::get_gamepad_index() const
    {
        return m_gamepad_index;
    }

    float InputSourceGamepadAxis::get_axis_position() const
    {
        return sf::Joystick::getAxisPosition(m_gamepad_index, m_axis);
    }

    bool InputSourceGamepadAxis::is_pressed() const
    {
        const float axis_value = this->get_axis_position();
        return (m_axis_threshold.first == AxisThresholdDirection::Less)
            ? axis_value < m_axis_threshold.second
            : axis_value > m_axis_threshold.second;
    }

    std::string_view InputSourceGamepadAxis::type() const
    {
        return InputSourceGamepadAxis::Type;
    }
}
