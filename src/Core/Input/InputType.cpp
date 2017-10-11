#include <Input/InputType.hpp>

#define OBE_INPUT_WRITE_INPUTTYPE_TO_STREAM(TYPE) case InputType::TYPE: os << #TYPE; break;

namespace obe
{
    namespace Input
    {
        std::ostream& operator<<(std::ostream& os, InputType m)
        {
            switch (m)
            {
                OBE_INPUT_WRITE_INPUTTYPE_TO_STREAM(Alpha)
                OBE_INPUT_WRITE_INPUTTYPE_TO_STREAM(Numeric)
                OBE_INPUT_WRITE_INPUTTYPE_TO_STREAM(NumericNP)
                OBE_INPUT_WRITE_INPUTTYPE_TO_STREAM(Arrows)
                OBE_INPUT_WRITE_INPUTTYPE_TO_STREAM(Functions)
                OBE_INPUT_WRITE_INPUTTYPE_TO_STREAM(Mouse)
                OBE_INPUT_WRITE_INPUTTYPE_TO_STREAM(Others)
                default: os << "Error";
            }
            return os;
        }
    }
}