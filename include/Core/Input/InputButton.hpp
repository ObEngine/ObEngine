#pragma once

#include <string>
#include <variant>

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <Input/InputType.hpp>

namespace obe::Input
{
    /**
     * \brief Trigger condition on an AxisButton input
     * \bind{AxisThresholdDirection}
     */
    enum class AxisThresholdDirection
    {
        /**
         * \brief Input triggered when the current AxisButton value is less that the
         *        threshold
         */
        Less,
        /**
         * \brief Input triggered when the current AxisButton value is more than the
         *        threshold
         */
        More
    };

    /**
     * \nobind
     */
    std::ostream& operator<<(std::ostream& os, const AxisThresholdDirection& m);

    /**
     * \brief Class that does represent an Input button
     * \bind{InputButton}
     */
    class InputButton
    {
    private:
        std::variant<sf::Keyboard::Key, sf::Mouse::Button, unsigned int,
            sf::Joystick::Axis>
            m_button;
        std::pair<AxisThresholdDirection, float> m_detectAxis;
        unsigned int m_gamepadIndex = 0;
        std::string m_name;
        std::string m_returnChar;
        InputType m_type;

    public:
        /**
         * \brief Creates a new InputButton representing a Keyboard key
         * \param key SFML Keyboard Key
         * \param name Name of the Key
         * \param returnChar The character printed when the key is pressed
         * \param type Type of the Key (Arrows, Alpha, Numeric, NumericNP,
         *        Functions, Others)
         */
        InputButton(sf::Keyboard::Key key, const std::string& name,
            const std::string& returnChar, InputType type);
        /**
         * \brief Creates a new InputButton representing a Mouse Button
         * \param key SFML Mouse Button
         * \param name Name of the Mouse Button
         */
        InputButton(sf::Mouse::Button key, const std::string& name);
        /**
         * \brief Creates a new InputButton representing a Gamepad Button
         * \param gamepadIndex Index of the gamepad
         * \param buttonIndex Index of the button of the gamepad
         * \param name Name of the gamepad Button
         */
        InputButton(
            unsigned int gamepadIndex, unsigned int buttonIndex, const std::string& name);
        /**
         * \brief Creates a new InputButton representing a gamepad Axis
         * \param gamepadIndex Index of the gamepad
         * \param gamepadAxis Enum value of the Gamepad Axis
         * \param detect Pair containing the check type (More / Less) and the
         *        threshold before axis activation detection
         * \param name Name of the gamepad Axis
         */
        InputButton(unsigned int gamepadIndex, sf::Joystick::Axis gamepadAxis,
            std::pair<AxisThresholdDirection, float> detect, const std::string& name);
        /**
         * \brief Get Axis Position value if InputButton is an axis (throws
         *        error otherwise)
         * \return Return value of GetAxisPosition
         */
        float getAxisPosition();
        /**
         * \brief Get the SFML Keyboard Key
         * \return SFML Keyboard Key
         */
        [[nodiscard]] sf::Keyboard::Key getKey() const;
        /**
         * \brief Get the name of the Key
         * \return A std::string containing the name of the Key
         */
        [[nodiscard]] std::string getName() const;
        /**
         * \brief Get the type of the Key (Arrows, Alpha, Numeric, NumericNP,
         * Functions, Others) \return An enum value from KeyType which is the
         * type of the key
         */
        [[nodiscard]] InputType getType() const;
        /**
         * \brief Equivalent to InputButton::getType() == inputType
         * \param inputType Type to test the equivalence
         * \return true if InputButton is of type inputType, false otherwise
         */
        [[nodiscard]] bool is(InputType inputType) const;
        // State
        /**
         * \brief Get if the key is pressed
         * \return true if the key is pressed, false otherwise
         */
        [[nodiscard]] bool isPressed() const;
        // Write
        /**
         * \brief Get if the key prints a writable character
         * \return true if the key prints a writable character, false otherwise
         */
        [[nodiscard]] bool isWritable() const;
    };
} // namespace obe::Input