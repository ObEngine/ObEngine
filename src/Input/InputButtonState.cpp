#include <Input/InputButtonState.hpp>

#define OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STREAM(TYPE) case InputButtonState::TYPE: os << #TYPE; break;
#define OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STRING(TYPE) if (state == InputButtonState::TYPE) { return #TYPE; }

namespace obe
{
    namespace Input
    {
        std::ostream& operator<<(std::ostream& os, InputButtonState m)
        {
            switch (m)
            {
                OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STREAM(Idle)
                OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STREAM(Hold)
                OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STREAM(Pressed)
                OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STREAM(Released)
                default: os << "Error";
            }
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
            //Add Error <REVISION>
        }

        std::string inputButtonStateToString(InputButtonState state)
        {
            OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STRING(Idle)
            OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STRING(Hold)
            OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STRING(Pressed)
            OBE_INPUT_WRITE_INPUTBUTTONSTATE_TO_STRING(Released)
            return "";
        }
    }
}