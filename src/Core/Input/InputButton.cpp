#include <SFML/Window/Joystick.hpp>

#include <Input/Exceptions.hpp>
#include <Input/InputButton.hpp>

namespace obe::Input
{
    std::ostream& operator<<(std::ostream& os, const AxisThresholdDirection& m)
    {
        (m == AxisThresholdDirection::Less) ? os << "Less" : os << "More";
        return os;
    }

    void InputButton::setMouseWheelDelta(int delta)
    {
        m_wheelDelta = delta;
    }

    InputButton::InputButton(sf::Keyboard::Key key, const std::string& name,
        const std::string& returnChar, InputType type)
    {
        m_button = key;
        m_name = name;
        m_returnChar = returnChar;
        m_type = type;
    }

    InputButton::InputButton(sf::Mouse::Button key, const std::string& name)
    {
        m_button = key;
        m_name = name;
        m_returnChar = "";
        m_type = InputType::Mouse;
    }

    InputButton::InputButton(const unsigned int gamepadIndex, unsigned int buttonIndex,
        const std::string& name)
    {
        m_gamepadIndex = gamepadIndex;
        m_button = buttonIndex;
        m_returnChar = "";
        m_type = InputType::GamepadButton;
        m_name = name;
    }

    InputButton::InputButton(const unsigned int gamepadIndex,
        sf::Joystick::Axis gamepadAxis, std::pair<AxisThresholdDirection, float> detect,
        const std::string& name)
    {
        m_gamepadIndex = gamepadIndex;
        m_type = InputType::GamepadAxis;
        m_button = gamepadAxis;
        m_returnChar = "";
        m_name = name;
        m_detectAxis = detect;
    }

    InputButton::InputButton(MouseWheelScrollDirection direction, const std::string& name)
    {
        m_type = InputType::ScrollWheel;
        m_button = direction;
        m_returnChar = "";
        m_name = name;
    }

    InputButton::InputButton(const InputButton& other)
    {
        this->reload(other);
    }

    void InputButton::reload(const InputButton& other)
    {
        m_type = other.m_type;
        m_button = other.m_button;
        m_returnChar = other.m_returnChar;
        m_name = other.m_name;
        m_detectAxis = m_detectAxis;
        m_gamepadIndex = other.m_gamepadIndex;
        m_wheelDelta = other.m_wheelDelta;
    }

    sf::Keyboard::Key InputButton::getKey() const
    {
        if (std::holds_alternative<sf::Keyboard::Key>(m_button))
            return std::get<sf::Keyboard::Key>(m_button);
        throw Exceptions::InputButtonInvalidOperation(
            inputTypeToString(m_type), "GetKey", EXC_INFO);
    }

    std::string InputButton::getName() const
    {
        return m_name;
    }

    InputType InputButton::getType() const
    {
        return m_type;
    }

    bool InputButton::is(InputType inputType) const
    {
        return inputType == m_type;
    }

    bool InputButton::isWritable() const
    {
        return (!m_returnChar.empty());
    }

    bool InputButton::isPressed() const
    {
        if (m_type == InputType::Mouse)
            return sf::Mouse::isButtonPressed(std::get<sf::Mouse::Button>(m_button));
        if (m_type == InputType::GamepadButton)
            return sf::Joystick::isButtonPressed(
                m_gamepadIndex, std::get<unsigned int>(m_button));
        if (m_type == InputType::GamepadAxis)
        {
            const float axisValue = sf::Joystick::getAxisPosition(
                m_gamepadIndex, std::get<sf::Joystick::Axis>(m_button));
            return (m_detectAxis.first == AxisThresholdDirection::Less)
                ? axisValue < m_detectAxis.second
                : axisValue > m_detectAxis.second;
        }
        if (m_type == InputType::ScrollWheel)
        {
            return m_wheelDelta != 0;
        }

        return sf::Keyboard::isKeyPressed(std::get<sf::Keyboard::Key>(m_button));
    }

    float InputButton::getAxisPosition() const
    {
        if (m_type == InputType::GamepadAxis)
            return sf::Joystick::getAxisPosition(
                m_gamepadIndex, std::get<sf::Joystick::Axis>(m_button));
        else
            throw Exceptions::InputButtonInvalidOperation(
                inputTypeToString(m_type), "GetAxisPosition", EXC_INFO);
    }

    int InputButton::getWheelDelta() const
    {
        return m_wheelDelta;
    }
} // namespace obe::Input
