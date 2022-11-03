#include <Input/InputSourceKeyboard.hpp>

namespace obe::input
{
    InputSourceKeyboardKey::InputSourceKeyboardKey(
        sf::Keyboard::Key key, const std::string& printable_char)
        : InputSource(magic_enum::enum_name(key).data(), printable_char)
        , m_key(key)
    {
    }

    InputSourceKeyboardKey::InputSourceKeyboardKey(sf::Keyboard::Key key, const std::string& name,
        const std::string& printable_char)
        : InputSource(name, printable_char)
        , m_key(key)
    {
    }

    sf::Keyboard::Key InputSourceKeyboardKey::get_key() const
    {
        return m_key;
    }

    bool InputSourceKeyboardKey::is_pressed() const
    {
        return sf::Keyboard::isKeyPressed(m_key);
    }

    std::string_view InputSourceKeyboardKey::type() const
    {
        return InputSourceKeyboardKey::Type;
    }
}
