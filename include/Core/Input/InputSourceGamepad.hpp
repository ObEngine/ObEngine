#pragma once

#include <Input/InputSource.hpp>

namespace obe::input
{
    class InputSourceGamepadButton : public InputSource
    {
    private:
        uint32_t m_gamepad_index = 0;
        uint32_t m_button_index = 0;

    public:
        static constexpr std::string_view Type = "GamepadButton";
        /**
         * \brief Creates a new InputSource representing a Gamepad Button
         * \param gamepad_index Index of the gamepad
         * \param button_index Index of the button of the gamepad
         * \param name Name of the gamepad Button
         */
        InputSourceGamepadButton(
            unsigned int gamepad_index, unsigned int button_index, const std::string& name);
        [[nodiscard]] uint32_t get_gamepad_index() const;
        [[nodiscard]] uint32_t get_button_index() const;
        [[nodiscard]] bool is_pressed() const override;
        [[nodiscard]] std::string_view type() const override;
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

    class InputSourceGamepadAxis : public InputSource
    {
    private:
        uint32_t m_gamepad_index = 0;
        sf::Joystick::Axis m_axis;
        std::pair<AxisThresholdDirection, float> m_axis_threshold;
        ;

    public:
        static constexpr std::string_view Type = "GamepadAxis";
        /**
         * \brief Creates a new InputSource representing a gamepad Axis
         * \param gamepad_index Index of the gamepad
         * \param gamepad_axis Enum value of the Gamepad Axis
         * \param detect Pair containing the check type (More / Less) and the
         *        threshold before axis activation detection
         * \param name Name of the gamepad Axis
         */
        InputSourceGamepadAxis(unsigned int gamepad_index, sf::Joystick::Axis gamepad_axis,
            std::pair<AxisThresholdDirection, float> axis_threshold, const std::string& name);
        [[nodiscard]] uint32_t get_gamepad_index() const;
        /**
         * \brief Get Axis Position value
         */
        [[nodiscard]] float get_axis_position() const;
        [[nodiscard]] bool is_pressed() const override;
        [[nodiscard]] std::string_view type() const override;
    };
}
