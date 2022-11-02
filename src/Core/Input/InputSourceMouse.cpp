#include <magic_enum/magic_enum.hpp>

#include <Input/InputSourceMouse.hpp>

namespace obe::input
{
    InputSourceMouseButton::InputSourceMouseButton(sf::Mouse::Button button)
        : InputSource("MouseButton", fmt::format("MouseButton{}", magic_enum::enum_name(button).data()), "")
        , m_button(button)
    {
        
    }

    sf::Mouse::Button InputSourceMouseButton::get_mouse_button() const
    {
        return m_button;
    }

    bool InputSourceMouseButton::is_pressed() const
    {
        return sf::Mouse::isButtonPressed(m_button);
    }

    InputSourceMouseWheelScroll::InputSourceMouseWheelScroll(
        MouseWheelScrollDirection direction, float threshold)
        : InputSource("MouseWheelScroll", fmt::format("MouseWheelScroll{}", magic_enum::enum_name(direction).data()), "")
        , m_direction(direction)
        , m_threshold(threshold)
    {
    }

    MouseWheelScrollDirection InputSourceMouseWheelScroll::get_scroll_wheel_direction() const
    {
        return m_direction;
    }

    bool InputSourceMouseWheelScroll::is_pressed() const
    {
        return m_delta >= m_threshold;
    }
}
