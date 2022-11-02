#pragma once

#include <Input/InputSource.hpp>

namespace obe
{
    namespace engine
    {
        class Engine;
    }
} // namespace obe

namespace obe::input
{
    class InputSourceMouseButton : public InputSource
    {
    private:
        sf::Mouse::Button m_button;

    public:
        /**
         * \brief Creates a new InputSource representing a Mouse Button
         * \param button SFML Mouse Button
         */
        InputSourceMouseButton(sf::Mouse::Button button);
        /**
         * \brief Get the SFML Mouse Button
         * \return SFML Mouse Button
         */
        [[nodiscard]] sf::Mouse::Button get_mouse_button() const;
        [[nodiscard]] bool is_pressed() const override;
    };

    enum class MouseWheelScrollDirection
    {
        Up,
        Down,
        Left,
        Right
    };

    class InputSourceMouseWheelScroll : public InputSource
    {
    private:
        MouseWheelScrollDirection m_direction;
        float m_threshold = 1;
        float m_delta = 0;

        friend obe::engine::Engine;

    public:
        /**
         * \brief Creates a new InputSource representing a Mouse Wheel Scroll
         * \param direction MouseWheel scroll direction
         * \param threshold scroll detection threshold
         */
        InputSourceMouseWheelScroll(MouseWheelScrollDirection direction, float threshold = 1.0f);
        /**
         * \brief Get the MouseWheel scroll direction
         * \return MouseWheel scroll direction
         */
        [[nodiscard]] MouseWheelScrollDirection get_scroll_wheel_direction() const;
        [[nodiscard]] bool is_pressed() const override;
    };
}
