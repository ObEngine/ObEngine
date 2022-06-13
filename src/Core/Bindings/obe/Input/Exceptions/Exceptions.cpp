#include <Bindings/obe/Input/Exceptions/Exceptions.hpp>

#include <Input/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::input::Exceptions::Bindings
{
    void LoadClassInputButtonAlreadyInCombination(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["input"]["exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InputButtonAlreadyInCombination>
            bindInputButtonAlreadyInCombination = ExceptionsNamespace.new_usertype<
                obe::input::Exceptions::InputButtonAlreadyInCombination>(
                "InputButtonAlreadyInCombination", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InputButtonAlreadyInCombination(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InputButtonAlreadyInCombination>,
                    obe::BaseException>());
    }
    void LoadClassInputButtonInvalidOperation(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["input"]["exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InputButtonInvalidOperation>
            bindInputButtonInvalidOperation
            = ExceptionsNamespace.new_usertype<obe::input::Exceptions::InputButtonInvalidOperation>(
                "InputButtonInvalidOperation", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InputButtonInvalidOperation(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InputButtonInvalidOperation>,
                    obe::BaseException>());
    }
    void LoadClassInvalidGamepadButton(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["input"]["exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InvalidGamepadButton> bindInvalidGamepadButton
            = ExceptionsNamespace.new_usertype<obe::input::Exceptions::InvalidGamepadButton>(
                "InvalidGamepadButton", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InvalidGamepadButton(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InvalidGamepadButton>,
                    obe::BaseException>());
    }
    void LoadClassInvalidInputButtonState(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["input"]["exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InvalidInputButtonState> bindInvalidInputButtonState
            = ExceptionsNamespace.new_usertype<obe::input::Exceptions::InvalidInputButtonState>(
                "InvalidInputButtonState", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InvalidInputButtonState(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InvalidInputButtonState>,
                    obe::BaseException>());
    }
    void LoadClassInvalidInputCombinationCode(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["input"]["exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InvalidInputCombinationCode>
            bindInvalidInputCombinationCode
            = ExceptionsNamespace.new_usertype<obe::input::Exceptions::InvalidInputCombinationCode>(
                "InvalidInputCombinationCode", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InvalidInputCombinationCode(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InvalidInputCombinationCode>,
                    obe::BaseException>());
    }
    void LoadClassInvalidInputTypeEnumValue(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["input"]["exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::InvalidInputTypeEnumValue>
            bindInvalidInputTypeEnumValue
            = ExceptionsNamespace.new_usertype<obe::input::Exceptions::InvalidInputTypeEnumValue>(
                "InvalidInputTypeEnumValue", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::InvalidInputTypeEnumValue(
                    int, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::InvalidInputTypeEnumValue>,
                    obe::BaseException>());
    }
    void LoadClassUnknownInputAction(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["input"]["exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::UnknownInputAction> bindUnknownInputAction
            = ExceptionsNamespace.new_usertype<obe::input::Exceptions::UnknownInputAction>(
                "UnknownInputAction", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::UnknownInputAction(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::UnknownInputAction>,
                    obe::BaseException>());
    }
    void LoadClassUnknownInputButton(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["input"]["exceptions"].get<sol::table>();
        sol::usertype<obe::input::Exceptions::UnknownInputButton> bindUnknownInputButton
            = ExceptionsNamespace.new_usertype<obe::input::Exceptions::UnknownInputButton>(
                "UnknownInputButton", sol::call_constructor,
                sol::constructors<obe::input::Exceptions::UnknownInputButton(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::input::Exceptions::UnknownInputButton>,
                    obe::BaseException>());
    }
};