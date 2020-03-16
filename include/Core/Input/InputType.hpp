#pragma once

#include <iostream>

namespace obe::Input
{
    /**
     * \brief The type of Input
     * \bind{InputType}
     */
    enum class InputType
    {
        /**
         * \brief All letters from A to Z
         */
        Alpha,
        /**
         * \brief All numbers from 0 to 9
         */
        Numeric,
        /**
         * \brief All numbers from 0 to 9 on Numeric pad
         */
        NumericNP,
        /**
         * \brief All arrow keys (Left, Up, Down, Right)
         */
        Arrows,
        /**
         * \brief All Functions keys from F1 to F12 on most keyboards
         */
        Functions,
        /**
         * \brief All Mouse buttons (Left / Right click)
         */
        Mouse,
        /**
         * \brief Other keys (Symbols etc..)
         */
        Others,
        /**
         * \brief All Gamepad buttons
         */
        GamepadButton,
        /**
         * \brief All Gamepad Axis (Joysticks, triggers)
         */
        GamepadAxis
    };

    std::string inputTypeToString(InputType type);
    /**
     * \nobind
     */
    std::ostream& operator<<(std::ostream& os, InputType m);
} // namespace obe::Input