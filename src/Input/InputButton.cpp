#include <Input/InputButton.hpp>
#include <SFML/Window/Joystick.hpp>

namespace obe
{
    namespace Input
    {
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
            m_type = InputType::Gamepad;
            m_name = name;
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
            if (m_type == InputType::Gamepad)
                return sf::Joystick::isButtonPressed(m_gamepadIndex, m_gamepadButtonIndex);
            return sf::Keyboard::isKeyPressed(m_key);
        }
    }
}
