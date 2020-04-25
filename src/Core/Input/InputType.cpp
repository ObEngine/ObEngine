#include <Input/Exceptions.hpp>
#include <Input/InputType.hpp>

#define OBE_INPUT_WRITE_INPUT_TYPE_TO_STRING(TYPE)                                       \
    case InputType::TYPE:                                                                \
        return #TYPE;                                                                    \
        break;

namespace obe::Input
{
    std::string inputTypeToString(InputType type)
    {
        switch (type)
        {
            OBE_INPUT_WRITE_INPUT_TYPE_TO_STRING(Alpha)
            OBE_INPUT_WRITE_INPUT_TYPE_TO_STRING(Numeric)
            OBE_INPUT_WRITE_INPUT_TYPE_TO_STRING(NumericNP)
            OBE_INPUT_WRITE_INPUT_TYPE_TO_STRING(Arrows)
            OBE_INPUT_WRITE_INPUT_TYPE_TO_STRING(Functions)
            OBE_INPUT_WRITE_INPUT_TYPE_TO_STRING(Mouse)
            OBE_INPUT_WRITE_INPUT_TYPE_TO_STRING(Others)
            OBE_INPUT_WRITE_INPUT_TYPE_TO_STRING(GamepadAxis)
            OBE_INPUT_WRITE_INPUT_TYPE_TO_STRING(GamepadButton)
        }
        const int enumValue = static_cast<std::underlying_type_t<InputType>>(type);
        throw Exceptions::InvalidInputTypeEnumValue(enumValue, EXC_INFO);
    }

    std::ostream& operator<<(std::ostream& os, InputType m)
    {
        os << inputTypeToString(m);
        return os;
    }
} // namespace obe::Input