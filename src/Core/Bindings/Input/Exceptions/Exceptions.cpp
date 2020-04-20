#include <Bindings/Input/Exceptions/Exceptions.hpp>

#include <Input/Exceptions.hpp>

#include <sol/sol.hpp>

namespace obe::Input::Exceptions::Bindings
{
    void LoadClassInputButtonInvalidOperation(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Input::Exceptions::InputButtonInvalidOperation>
            bindInputButtonInvalidOperation = ExceptionsNamespace.new_usertype<
                obe::Input::Exceptions::InputButtonInvalidOperation>(
                "InputButtonInvalidOperation", sol::call_constructor,
                sol::constructors<obe::Input::Exceptions::InputButtonInvalidOperation(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassInvalidInputButtonState(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Input::Exceptions::InvalidInputButtonState>
            bindInvalidInputButtonState
            = ExceptionsNamespace
                  .new_usertype<obe::Input::Exceptions::InvalidInputButtonState>(
                      "InvalidInputButtonState", sol::call_constructor,
                      sol::constructors<obe::Input::Exceptions::InvalidInputButtonState(
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownInputAction(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Input::Exceptions::UnknownInputAction> bindUnknownInputAction
            = ExceptionsNamespace.new_usertype<
                obe::Input::Exceptions::UnknownInputAction>("UnknownInputAction",
                sol::call_constructor,
                sol::constructors<obe::Input::Exceptions::UnknownInputAction(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownInputButton(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Input"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Input::Exceptions::UnknownInputButton> bindUnknownInputButton
            = ExceptionsNamespace.new_usertype<
                obe::Input::Exceptions::UnknownInputButton>("UnknownInputButton",
                sol::call_constructor,
                sol::constructors<obe::Input::Exceptions::UnknownInputButton(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
};