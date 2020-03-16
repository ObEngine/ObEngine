#pragma once

#include <iostream>

namespace obe::Input
{
    /**
     * \brief Possible states of InputButton
     * \bind{InputButtonState}
     */
    enum class InputButtonState
    {
        /**
         * \brief InputButton is not pressed
         */
        Idle,
        /**
         * \brief InputButton is being hold
         */
        Hold,
        /**
         * \brief InputButton is just being pressed
         */
        Pressed,
        /**
         * \brief InputButton is just being released
         */
        Released,
        LAST__
    };

    /**
     * \brief Converts an InputButtonState to a std::string
     * \param state InputButtonState to convert
     * \return A std::string containing the name of the given InputButtonState
     */
    std::string inputButtonStateToString(InputButtonState state);
    /**
     * \nobind
     */
    std::ostream& operator<<(std::ostream& os, InputButtonState m);
    /**
     * \brief Converts a string to the corresponding InputButtonState
     * \param state InputButtonState in string form
     * \return The corresponding InputButtonState
     */
    InputButtonState stringToInputButtonState(const std::string& state);

} // namespace obe::Input