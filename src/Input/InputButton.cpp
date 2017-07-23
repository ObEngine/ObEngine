#include <Input/InputButton.hpp>

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

        bool InputButton::isAlpha() const
        {
            return (m_type == InputType::Alpha);
        }

        bool InputButton::isNumeric() const
        {
            return (m_type == InputType::Numeric);
        }

        bool InputButton::isNumericNP() const
        {
            return (m_type == InputType::NumericNP);
        }

        bool InputButton::isAlphaNumeric() const
        {
            return (isAlpha() || isNumeric() || isNumericNP());
        }

        bool InputButton::isArrow() const
        {
            return (m_type == InputType::Arrows);
        }

        bool InputButton::isFunction() const
        {
            return (m_type == InputType::Functions);
        }

        bool InputButton::isOther() const
        {
            return (m_type == InputType::Others);
        }

        bool InputButton::isWritable() const
        {
            return (!m_returnChar.empty());
        }

        bool InputButton::isPressed() const
        {
            if (m_type != InputType::Mouse)
                return sf::Keyboard::isKeyPressed(m_key);
            else
                return sf::Mouse::isButtonPressed(m_mb);
        }
    }
}