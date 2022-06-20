#include <Bindings/obe/input/Exceptions/Exceptions.hpp>

#include <Input/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::input::Exceptions::bindings
{
    void load_class_input_button_already_in_combination(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InputButtonAlreadyInCombination>
            bind_input_button_already_in_combination = Exceptions_namespace.new_usertype<
                obe::input::Exceptions::InputButtonAlreadyInCombination>(
                "InputButtonAlreadyInCombination", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InputButtonAlreadyInCombination(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InputButtonAlreadyInCombination>,
                    obe::BaseException>());
    }
    void load_class_input_button_invalid_operation(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InputButtonInvalidOperation>
            bind_input_button_invalid_operation = Exceptions_namespace.new_usertype<
                obe::input::Exceptions::InputButtonInvalidOperation>("InputButtonInvalidOperation",
                sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InputButtonInvalidOperation(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InputButtonInvalidOperation>,
                    obe::BaseException>());
    }
    void load_class_invalid_gamepad_button(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InvalidGamepadButton> bind_invalid_gamepad_button
            = Exceptions_namespace.new_usertype<obe::input::Exceptions::InvalidGamepadButton>(
                "InvalidGamepadButton", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InvalidGamepadButton(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InvalidGamepadButton>,
                    obe::BaseException>());
    }
    void load_class_invalid_input_button_state(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InvalidInputButtonState>
            bind_invalid_input_button_state
            = Exceptions_namespace.new_usertype<obe::input::Exceptions::InvalidInputButtonState>(
                "InvalidInputButtonState", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InvalidInputButtonState(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InvalidInputButtonState>,
                    obe::BaseException>());
    }
    void load_class_invalid_input_combination_code(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InvalidInputCombinationCode>
            bind_invalid_input_combination_code = Exceptions_namespace.new_usertype<
                obe::input::Exceptions::InvalidInputCombinationCode>("InvalidInputCombinationCode",
                sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InvalidInputCombinationCode(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InvalidInputCombinationCode>,
                    obe::BaseException>());
    }
    void load_class_invalid_input_type_enum_value(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InvalidInputTypeEnumValue>
            bind_invalid_input_type_enum_value
            = Exceptions_namespace.new_usertype<obe::input::Exceptions::InvalidInputTypeEnumValue>(
                "InvalidInputTypeEnumValue", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InvalidInputTypeEnumValue(
                    int, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InvalidInputTypeEnumValue>,
                    obe::BaseException>());
    }
    void load_class_unknown_input_action(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::UnknownInputAction> bind_unknown_input_action
            = Exceptions_namespace.new_usertype<obe::input::Exceptions::UnknownInputAction>(
                "UnknownInputAction", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::UnknownInputAction(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::UnknownInputAction>,
                    obe::BaseException>());
    }
    void load_class_unknown_input_button(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::UnknownInputButton> bind_unknown_input_button
            = Exceptions_namespace.new_usertype<obe::input::Exceptions::UnknownInputButton>(
                "UnknownInputButton", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::UnknownInputButton(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::UnknownInputButton>,
                    obe::BaseException>());
    }
};