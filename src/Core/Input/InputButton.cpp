#include <SFML/Window/Joystick.hpp>

#include <Input/Exceptions.hpp>
#include <Input/InputButton.hpp>

namespace obe::input
{
    void InputButton::set_mouse_wheel_delta(int delta)
    {
        m_wheel_delta = delta;
    }

    InputButton::InputButton(sf::Keyboard::Key key, const std::string& name,
        const std::string& return_char, InputType type)
        : m_button(key)
        , m_name(name)
        , m_return_char(return_char)
        , m_type(type)
    {
    }

    InputButton::InputButton(sf::Mouse::Button key, const std::string& name)
        : m_button(key)
        , m_name(name)
        , m_type(InputType::Mouse)
    {
    }

    InputButton::InputButton(
        const unsigned int gamepad_index, unsigned int button_index, const std::string& name)
        : m_button(button_index)
        , m_gamepad_index(gamepad_index)
        , m_name(name)
        , m_type(InputType::GamepadButton)
    {
    }

    InputButton::InputButton(const unsigned int gamepad_index, sf::Joystick::Axis gamepad_axis,
        std::pair<AxisThresholdDirection, float> detect, const std::string& name)
        : m_button(gamepad_axis)
        , m_detect_axis(detect)
        , m_gamepad_index(gamepad_index)
        , m_name(name)
        , m_type(InputType::GamepadAxis)
    {
    }

    InputButton::InputButton(MouseWheelScrollDirection direction, const std::string& name)
        : m_button(direction)
        , m_name(name)
        , m_type(InputType::ScrollWheel)
    {
    }

    InputButton::InputButton(const InputButton& other)
    {
        this->reload(other);
    }

    void InputButton::reload(const InputButton& other)
    {
        m_type = other.m_type;
        m_button = other.m_button;
        m_return_char = other.m_return_char;
        m_name = other.m_name;
        m_detect_axis = other.m_detect_axis;
        m_gamepad_index = other.m_gamepad_index;
        m_wheel_delta = other.m_wheel_delta;
    }

    sf::Keyboard::Key InputButton::get_key() const
    {
        if (std::holds_alternative<sf::Keyboard::Key>(m_button))
            return std::get<sf::Keyboard::Key>(m_button);
        throw Exceptions::InputButtonInvalidOperation(
            InputTypeMeta::to_string(m_type), "GetKey", EXC_INFO);
    }

    std::string InputButton::get_name() const
    {
        return m_name;
    }

    InputType InputButton::get_type() const
    {
        return m_type;
    }

    bool InputButton::is(InputType input_type) const
    {
        return input_type == m_type;
    }

    bool InputButton::is_writable() const
    {
        return (!m_return_char.empty());
    }

    bool InputButton::is_pressed() const
    {
        if (m_type == InputType::Mouse)
            return sf::Mouse::isButtonPressed(std::get<sf::Mouse::Button>(m_button));
        if (m_type == InputType::GamepadButton)
            return sf::Joystick::isButtonPressed(m_gamepad_index, std::get<unsigned int>(m_button));
        if (m_type == InputType::GamepadAxis)
        {
            const float axis_value = sf::Joystick::getAxisPosition(
                m_gamepad_index, std::get<sf::Joystick::Axis>(m_button));
            return (m_detect_axis.first == AxisThresholdDirection::Less)
                ? axis_value < m_detect_axis.second
                : axis_value > m_detect_axis.second;
        }
        if (m_type == InputType::ScrollWheel)
        {
            return m_wheel_delta != 0;
        }

        return sf::Keyboard::isKeyPressed(std::get<sf::Keyboard::Key>(m_button));
    }

    float InputButton::get_axis_position() const
    {
        if (m_type == InputType::GamepadAxis)
            return sf::Joystick::getAxisPosition(
                m_gamepad_index, std::get<sf::Joystick::Axis>(m_button));
        else
            throw Exceptions::InputButtonInvalidOperation(
                InputTypeMeta::to_string(m_type), "GetAxisPosition", EXC_INFO);
    }

    int InputButton::get_wheel_delta() const
    {
        return m_wheel_delta;
    }
} // namespace obe::input
