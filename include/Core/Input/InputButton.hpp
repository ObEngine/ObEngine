#pragma once

#include <Input/InputType.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <Types/SmartEnum.hpp>
#include <string>
#include <variant>

namespace obe
{
    namespace engine
    {
        class Engine;
    }
} // namespace obe

namespace obe::input
{
    enum class MouseWheelScrollDirection
    {
        Up,
        Down,
        Left,
        Right
    };
    /**
     * \brief Trigger condition on an AxisButton input
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

    using AxisThresholdDirectionMeta = types::SmartEnum<AxisThresholdDirection>;

    /**
     * \brief Class that does represent an Input button
     */
    class InputButton
    {
    private:
        std::variant<sf::Keyboard::Key, sf::Mouse::Button, unsigned int, sf::Joystick::Axis,
            MouseWheelScrollDirection>
            m_button;
        std::pair<AxisThresholdDirection, float> m_detect_axis;
        unsigned int m_gamepad_index = 0;
        std::string m_name;
        std::string m_return_char = "";
        InputType m_type;

        int m_wheel_delta = 0;
        void set_mouse_wheel_delta(int delta);
        friend obe::engine::Engine;

    public:
        /**
         * \brief Creates a new InputButton representing a Keyboard key
         * \param key SFML Keyboard Key
         * \param name Name of the Key
         * \param return_char The character printed when the key is pressed
         * \param type Type of the Key (Arrows, Alpha, Numeric, NumericNP,
         *        Functions, Others)
         */
        InputButton(sf::Keyboard::Key key, const std::string& name, const std::string& return_char,
            InputType type);
        /**
         * \brief Creates a new InputButton representing a Mouse Button
         * \param key SFML Mouse Button
         * \param name Name of the Mouse Button
         */
        InputButton(sf::Mouse::Button key, const std::string& name);
        /**
         * \brief Creates a new InputButton representing a Gamepad Button
         * \param gamepad_index Index of the gamepad
         * \param button_index Index of the button of the gamepad
         * \param name Name of the gamepad Button
         */
        InputButton(unsigned int gamepad_index, unsigned int button_index, const std::string& name);
        /**
         * \brief Creates a new InputButton representing a gamepad Axis
         * \param gamepad_index Index of the gamepad
         * \param gamepad_axis Enum value of the Gamepad Axis
         * \param detect Pair containing the check type (More / Less) and the
         *        threshold before axis activation detection
         * \param name Name of the gamepad Axis
         */
        InputButton(unsigned int gamepad_index, sf::Joystick::Axis gamepad_axis,
            std::pair<AxisThresholdDirection, float> detect, const std::string& name);

        InputButton(MouseWheelScrollDirection direction, const std::string& name);

        InputButton(const InputButton& other);

        void reload(const InputButton& other);
        /**
         * \brief Get Axis Position value if InputButton is an axis (throws
         *        error otherwise)
         * \return Return value of GetAxisPosition
         */
        [[nodiscard]] float get_axis_position() const;

        [[nodiscard]] int get_wheel_delta() const;
        /**
         * \brief Get the SFML Keyboard Key
         * \return SFML Keyboard Key
         */
        [[nodiscard]] sf::Keyboard::Key get_key() const;
        /**
         * \brief Get the name of the Key
         * \return A std::string containing the name of the Key
         */
        [[nodiscard]] std::string get_name() const;
        /**
         * \brief Get the type of the Key (Arrows, Alpha, Numeric, NumericNP,
         * Functions, Others) \return An enum value from KeyType which is the
         * type of the key
         */
        [[nodiscard]] InputType get_type() const;
        /**
         * \brief Equivalent to InputButton::get_type() == input_type
         * \param input_type Type to test the equivalence
         * \return true if InputButton is of type input_type, false otherwise
         */
        [[nodiscard]] bool is(InputType input_type) const;
        // State
        /**
         * \brief Get if the key is pressed
         * \return true if the key is pressed, false otherwise
         */
        [[nodiscard]] bool is_pressed() const;
        // Write
        /**
         * \brief Get if the key prints a writable character
         * \return true if the key prints a writable character, false otherwise
         */
        [[nodiscard]] bool is_writable() const;
    };
} // namespace obe::input
