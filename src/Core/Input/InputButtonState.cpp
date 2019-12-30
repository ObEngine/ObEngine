#include "vili/ErrorHandler.hpp"
#include <Input/InputButtonState.hpp>

#define OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STRING(TYPE)                                           \
    if (state == InputButtonState::TYPE)                                                           \
    {                                                                                              \
        return #TYPE;                                                                              \
    }

namespace obe::Input
{
    std::ostream& operator<<(std::ostream& os, const InputButtonState m)
    {
        os << inputButtonStateToString(m);
        return os;
    }

    InputButtonState stringToInputButtonState(const std::string& state)
    {
        if (state == "Idle")
            return InputButtonState::Idle;
        if (state == "Hold")
            return InputButtonState::Hold;
        if (state == "Pressed")
            return InputButtonState::Pressed;
        if (state == "Released")
            return InputButtonState::Released;
        throw aube::ErrorHandler::Raise(
            "ObEngine.Input.InputButtonState.WrongStringState", { { "state", state } });
    }

    std::string inputButtonStateToString(InputButtonState state)
    {
        OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STRING(Idle)
        OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STRING(Hold)
        OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STRING(Pressed)
        OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STRING(Released)
        throw aube::ErrorHandler::Raise("ObEngine.Input.InputButtonState.WrongEnumState");
    }
} // namespace obe::Input