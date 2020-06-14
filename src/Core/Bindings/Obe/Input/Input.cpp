#include <Bindings/obe/Input/Input.hpp>

#include <Input/InputAction.hpp>
#include <Input/InputActionEvent.hpp>
#include <Input/InputButton.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/InputButtonState.hpp>
#include <Input/InputCondition.hpp>
#include <Input/InputManager.hpp>
#include <Input/InputType.hpp>

#include <Bindings/Config.hpp>

namespace obe::Input::Bindings
{
    void LoadEnumAxisThresholdDirection(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        InputNamespace.new_enum<obe::Input::AxisThresholdDirection>(
            "AxisThresholdDirection",
            { { "Less", obe::Input::AxisThresholdDirection::Less },
                { "More", obe::Input::AxisThresholdDirection::More } });
    }
    void LoadEnumInputButtonState(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        InputNamespace.new_enum<obe::Input::InputButtonState>("InputButtonState",
            { { "Idle", obe::Input::InputButtonState::Idle },
                { "Hold", obe::Input::InputButtonState::Hold },
                { "Pressed", obe::Input::InputButtonState::Pressed },
                { "Released", obe::Input::InputButtonState::Released },
                { "LAST__", obe::Input::InputButtonState::LAST__ } });
    }
    void LoadEnumInputType(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        InputNamespace.new_enum<obe::Input::InputType>("InputType",
            { { "Alpha", obe::Input::InputType::Alpha },
                { "Numeric", obe::Input::InputType::Numeric },
                { "NumericNP", obe::Input::InputType::NumericNP },
                { "Arrows", obe::Input::InputType::Arrows },
                { "Functions", obe::Input::InputType::Functions },
                { "Mouse", obe::Input::InputType::Mouse },
                { "Others", obe::Input::InputType::Others },
                { "GamepadButton", obe::Input::InputType::GamepadButton },
                { "GamepadAxis", obe::Input::InputType::GamepadAxis } });
    }
    void LoadClassInputAction(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        sol::usertype<obe::Input::InputAction> bindInputAction
            = InputNamespace.new_usertype<obe::Input::InputAction>("InputAction",
                sol::call_constructor,
                sol::constructors<obe::Input::InputAction(
                    obe::Triggers::TriggerGroup*, const std::string&)>(),
                sol::base_classes, sol::bases<obe::Types::Identifiable>());
        bindInputAction["addCondition"] = &obe::Input::InputAction::addCondition;
        bindInputAction["addContext"] = &obe::Input::InputAction::addContext;
        bindInputAction["check"] = &obe::Input::InputAction::check;
        bindInputAction["clearConditions"] = &obe::Input::InputAction::clearConditions;
        bindInputAction["connect"] = &obe::Input::InputAction::connect;
        bindInputAction["getContexts"] = &obe::Input::InputAction::getContexts;
        bindInputAction["getInterval"] = &obe::Input::InputAction::getInterval;
        bindInputAction["getRepeat"] = &obe::Input::InputAction::getRepeat;
        bindInputAction["setInterval"] = &obe::Input::InputAction::setInterval;
        bindInputAction["setRepeat"] = &obe::Input::InputAction::setRepeat;
        bindInputAction["update"] = &obe::Input::InputAction::update;
        bindInputAction["getInvolvedButtons"]
            = &obe::Input::InputAction::getInvolvedButtons;
        bindInputAction["enable"] = &obe::Input::InputAction::enable;
        bindInputAction["disable"] = &obe::Input::InputAction::disable;
        bindInputAction["isEnabled"] = &obe::Input::InputAction::isEnabled;
    }
    void LoadClassInputActionEvent(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        sol::usertype<obe::Input::InputActionEvent> bindInputActionEvent
            = InputNamespace.new_usertype<obe::Input::InputActionEvent>(
                "InputActionEvent", sol::call_constructor,
                sol::constructors<obe::Input::InputActionEvent(
                    obe::Input::InputAction&, obe::Input::InputCondition&)>());
        bindInputActionEvent["getAction"] = &obe::Input::InputActionEvent::getAction;
        bindInputActionEvent["getCondition"]
            = &obe::Input::InputActionEvent::getCondition;
    }
    void LoadClassInputButton(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        sol::usertype<obe::Input::InputButton> bindInputButton
            = InputNamespace.new_usertype<obe::Input::InputButton>("InputButton",
                sol::call_constructor,
                sol::constructors<obe::Input::InputButton(sf::Keyboard::Key,
                                      const std::string&, const std::string&,
                                      obe::Input::InputType),
                    obe::Input::InputButton(sf::Mouse::Button, const std::string&),
                    obe::Input::InputButton(
                        unsigned int, unsigned int, const std::string&),
                    obe::Input::InputButton(unsigned int, sf::Joystick::Axis,
                        std::pair<obe::Input::AxisThresholdDirection, float>,
                        const std::string&)>());
        bindInputButton["getAxisPosition"] = &obe::Input::InputButton::getAxisPosition;
        bindInputButton["getKey"] = &obe::Input::InputButton::getKey;
        bindInputButton["getName"] = &obe::Input::InputButton::getName;
        bindInputButton["getType"] = &obe::Input::InputButton::getType;
        bindInputButton["is"] = &obe::Input::InputButton::is;
        bindInputButton["isPressed"] = &obe::Input::InputButton::isPressed;
        bindInputButton["isWritable"] = &obe::Input::InputButton::isWritable;
    }
    void LoadClassInputButtonMonitor(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        sol::usertype<obe::Input::InputButtonMonitor> bindInputButtonMonitor
            = InputNamespace.new_usertype<obe::Input::InputButtonMonitor>(
                "InputButtonMonitor", sol::call_constructor,
                sol::constructors<obe::Input::InputButtonMonitor(
                    obe::Input::InputButton&)>());
        bindInputButtonMonitor["getButton"] = &obe::Input::InputButtonMonitor::getButton;
        bindInputButtonMonitor["getState"] = &obe::Input::InputButtonMonitor::getState;
        bindInputButtonMonitor["update"] = &obe::Input::InputButtonMonitor::update;
    }
    void LoadClassInputCondition(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        sol::usertype<obe::Input::InputCondition> bindInputCondition
            = InputNamespace.new_usertype<obe::Input::InputCondition>("InputCondition",
                sol::call_constructor, sol::constructors<obe::Input::InputCondition()>());
        bindInputCondition["addCombinationElement"]
            = &obe::Input::InputCondition::addCombinationElement;
        bindInputCondition["check"] = &obe::Input::InputCondition::check;
        bindInputCondition["clear"] = &obe::Input::InputCondition::clear;
        bindInputCondition["enable"] = &obe::Input::InputCondition::enable;
        bindInputCondition["disable"] = &obe::Input::InputCondition::disable;
        bindInputCondition["isEnabled"] = &obe::Input::InputCondition::isEnabled;
    }
    void LoadClassInputManager(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        sol::usertype<obe::Input::InputManager> bindInputManager
            = InputNamespace.new_usertype<obe::Input::InputManager>("InputManager",
                sol::call_constructor, sol::constructors<obe::Input::InputManager()>(),
                sol::base_classes, sol::bases<obe::Types::Togglable>());
        bindInputManager["init"] = &obe::Input::InputManager::init;
        bindInputManager["actionExists"] = &obe::Input::InputManager::actionExists;
        bindInputManager["addContext"] = &obe::Input::InputManager::addContext;
        bindInputManager["getAction"] = &obe::Input::InputManager::getAction;
        bindInputManager["getContexts"] = &obe::Input::InputManager::getContexts;
        bindInputManager["clear"] = &obe::Input::InputManager::clear;
        bindInputManager["clearContexts"] = &obe::Input::InputManager::clearContexts;
        bindInputManager["configure"] = &obe::Input::InputManager::configure;
        bindInputManager["removeContext"] = &obe::Input::InputManager::removeContext;
        bindInputManager["setContext"] = &obe::Input::InputManager::setContext;
        bindInputManager["update"] = &obe::Input::InputManager::update;
        bindInputManager["getInput"] = &obe::Input::InputManager::getInput;
        bindInputManager["getInputs"] = sol::overload(
            static_cast<std::vector<obe::Input::InputButton*> (
                obe::Input::InputManager::*)()>(&obe::Input::InputManager::getInputs),
            static_cast<std::vector<obe::Input::InputButton*> (
                obe::Input::InputManager::*)(obe::Input::InputType)>(
                &obe::Input::InputManager::getInputs));
        bindInputManager["getPressedInputs"]
            = &obe::Input::InputManager::getPressedInputs;
        bindInputManager["monitor"] = sol::overload(
            static_cast<obe::Input::InputButtonMonitorPtr (obe::Input::InputManager::*)(
                const std::string&)>(&obe::Input::InputManager::monitor),
            static_cast<obe::Input::InputButtonMonitorPtr (obe::Input::InputManager::*)(
                obe::Input::InputButton&)>(&obe::Input::InputManager::monitor));
        bindInputManager["requireRefresh"] = &obe::Input::InputManager::requireRefresh;
    }
    void LoadFunctionInputButtonStateToString(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        InputNamespace.set_function(
            "inputButtonStateToString", obe::Input::inputButtonStateToString);
    }
    void LoadFunctionStringToInputButtonState(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        InputNamespace.set_function(
            "stringToInputButtonState", obe::Input::stringToInputButtonState);
    }
    void LoadFunctionInputTypeToString(sol::state_view state)
    {
        sol::table InputNamespace = state["obe"]["Input"].get<sol::table>();
        InputNamespace.set_function("inputTypeToString", obe::Input::inputTypeToString);
    }
};