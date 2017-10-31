#include <vili/ErrorHandler.hpp>

#include <Input/InputButton.hpp>
#include <SFML/Window/Joystick.hpp>

namespace obe
{
    namespace Input
    {
        std::ostream& operator<<(std::ostream& os, const AxisCompareType& m)
        {
            (m == AxisCompareType::LESS) ? os << "LESS" : os << "MORE";
            return os;
        }

        InputButton::InputButton(sf::Keyboard::Key key, const std::string& name, const std::string& returnChar, InputType type): m_mb()
        {
            m_key = key;
            m_name = name;
            m_returnChar = returnChar;
            m_type = type;
        }

        InputButton::InputButton(sf::Mouse::Button key, const std::string& name): m_key()
        {
            m_mb = key;
            m_name = name;
            m_returnChar = "";
            m_type = InputType::Mouse;
        }

        InputButton::InputButton(unsigned gamepadIndex, unsigned buttonIndex, const std::string& name)
        {
            m_gamepadIndex = gamepadIndex;
            m_gamepadButtonIndex = buttonIndex;
            m_returnChar = "";
            m_type = InputType::GamepadButton;
            m_name = name;
        }

        InputButton::InputButton(unsigned gamepadIndex, sf::Joystick::Axis gamepadAxis, std::pair<AxisCompareType, float> detect, const std::string& name)
        {
            m_gamepadIndex = gamepadIndex;
            m_type = InputType::GamepadAxis;
            m_gamepadAxis = gamepadAxis;
            m_returnChar = "";
            m_name = name;
            m_detectAxis = detect;
        }

        sf::Keyboard::Key InputButton::getKey() const
        {
            return m_key;
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
                return sf::Mouse::isButtonPressed(m_mb);
            if (m_type == InputType::GamepadButton)
                return sf::Joystick::isButtonPressed(m_gamepadIndex, m_gamepadButtonIndex);
            if (m_type == InputType::GamepadAxis)
            {
                float axisValue = sf::Joystick::getAxisPosition(m_gamepadIndex, m_gamepadAxis);
                return (m_detectAxis.first == AxisCompareType::LESS) ? axisValue < m_detectAxis.second : axisValue > m_detectAxis.second;
            }
                
            return sf::Keyboard::isKeyPressed(m_key);
        }

        unsigned int InputButton::getAxisPosition()
        {
            if (m_type == InputType::GamepadAxis)
                return sf::Joystick::getAxisPosition(m_gamepadIndex, m_gamepadAxis);
            else
                throw aube::ErrorHandler::Raise("Obe.Input.InputButton.NotAnAxis");
        }
    }
}
