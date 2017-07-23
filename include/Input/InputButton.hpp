#pragma once

#include <string>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <Input/InputType.hpp>

namespace obe
{
    namespace Input
    {
        /**
        * \brief Class that does represent an Input button
        * @Bind
        */
        class InputButton
        {
        private:
            sf::Keyboard::Key m_key;
            sf::Mouse::Button m_mb;
            std::string m_name;
            std::string m_returnChar;
            InputType m_type;
        public:
            /**
            * \brief Creates a new KeyClass representing a Keyboard key
            * \param key SFML Keyboard Key
            * \param name Name of the Key
            * \param returnChar The character printed when the key is pressed
            * \param type Type of the Key (Arrows, Alpha, Numeric, NumericNP, Functions, Others)
            */
            InputButton(sf::Keyboard::Key key, const std::string& name, const std::string& returnChar, InputType type);
            /**
            * \brief Creates a new KeyClass representing a Mouse Button
            * \param key SFML Mouse Button
            * \param name Name of the Mouse Button
            */
            InputButton(sf::Mouse::Button key, const std::string& name);
            /**
            * \brief Get the SFML Keyboard Key
            * \return SFML Keyboard Key
            */
            sf::Keyboard::Key getKey() const;
            /**
            * \brief Get the name of the Key
            * \return A std::string containing the name of the Key
            */
            std::string getName() const;
            /**
            * \brief Get the type of the Key (Arrows, Alpha, Numeric, NumericNP, Functions, Others)
            * \return An enum value from KeyType which is the type of the key
            */
            InputType getType() const;
            // Type
            /**
            * \brief Get if the key is a letter
            * \return true if the key is a letter from the Alphabet (A-Z), false otherwise
            */
            bool isAlpha() const;
            /**
            * \brief Get if the key is a number
            * \return true if the key is a number (not from the numpad), false otherwise
            */
            bool isNumeric() const;
            /**
            * \brief Get if the key is a number from the NumPad
            * \return true if the key is a number (from the numpad), false otherwise
            */
            bool isNumericNP() const;
            /**
            * \brief Get if the key is either isAlpha() or isNumeric()
            * \return true if the key is a number or a letter, false otherwise
            */
            bool isAlphaNumeric() const;
            /**
            * \brief Get if the key is an arrow key
            * \return true if the key is an arrow key, false other wise
            */
            bool isArrow() const;
            /**
            * \brief Get if the key is a function key
            * \return true if the key is a function key (From F1 to F12 on most keyboards), false otherwise
            */
            bool isFunction() const;
            /**
            * \brief Get if the key is not any of the type above
            * \return true if the key is not one of the other type, false otherwise
            */
            bool isOther() const;
            // Write
            /**
            * \brief Get if the key prints a writable character
            * \return true if the key prints a writable character, false otherwise
            */
            bool isWritable() const;
            // State
            /**
            * \brief Get if the key is pressed
            * \return true if the key is pressed, false otherwise
            */
            bool isPressed() const;
        };
    }
}
