#pragma once

#include <iostream>

namespace obe
{
    namespace Input
    {
        enum class InputButtonState
        {
            Idle,
            Hold,
            Pressed,
            Released
        };

        std::ostream& operator<<(std::ostream& os, InputButtonState m);
        InputButtonState stringToInputButtonState(const std::string& state);
        std::string inputButtonStateToString(InputButtonState state);
    }
}