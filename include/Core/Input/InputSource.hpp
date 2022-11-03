#pragma once

#include <Input/InputType.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <Types/SmartEnum.hpp>
#include <string>
#include <variant>

/**
 * \additionalinclude{Script/AutoCastManager.hpp}
 */
namespace obe::input
{
    /**
     * \brief Class that does represent an Input source
     * \hook{Inherit, script::AutoCastManager<input::InputSource>::Register<%childclass%>();}
     */
    class InputSource
    {
    private:
        std::string m_name;
        std::string m_printable_char = "";

    public:
        InputSource(const std::string& name, const std::string& printable_char);

        InputSource(const InputSource& other) = default;
        virtual ~InputSource() = default;

        /**
         * \brief Get the name of the Input source
         * \return A std::string containing the name of the Input source
         */
        [[nodiscard]] std::string get_name() const;
        [[nodiscard]] std::string get_printable_char() const;

        // State
        /**
         * \brief Get if the key is pressed
         * \return true if the key is pressed, false otherwise
         */
        [[nodiscard]] virtual bool is_pressed() const = 0;
        // Write
        /**
         * \brief Get if the key prints a writable character
         * \return true if the key prints a writable character, false otherwise
         */
        [[nodiscard]] bool is_printable() const;

        [[nodiscard]] virtual std::string_view type() const = 0;
    };
} // namespace obe::input
