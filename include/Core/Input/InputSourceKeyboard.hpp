#pragma once

#include <Input/InputSource.hpp>

namespace obe::input
{
    class InputSourceKeyboardKey : public InputSource
    {
    private:
        sf::Keyboard::Key m_key;

    public:
        static constexpr std::string_view Type = "KeyboardKey";
        /**
         * \brief Creates a new InputSource representing a Keyboard key
         * \param key SFML Keyboard Key
         * \param printable_char The character printed when the key is pressed

         */
        InputSourceKeyboardKey(sf::Keyboard::Key key, const std::string& printable_char);
        /**
         * \brief Creates a new InputSource representing a Keyboard key
         * \param key SFML Keyboard Key
         * \param name Name of the Key
         * \param printable_char The character printed when the key is pressed
         */
        InputSourceKeyboardKey(
            sf::Keyboard::Key key, const std::string& name, const std::string& printable_char);
        /**
         * \brief Get the SFML Keyboard Key
         * \return SFML Keyboard Key
         */
        [[nodiscard]] sf::Keyboard::Key get_key() const;
        [[nodiscard]] bool is_pressed() const override;
        [[nodiscard]] std::string_view type() const override;
    };
}
