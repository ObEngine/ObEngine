#include <Bindings/Bindings.hpp>
#include <Bindings/InputBindings.hpp>
#include <Input/InputButton.hpp>
#include <Input/InputActionEvent.hpp>
#include <Input/InputManager.hpp>
#include <Input/KeyList.hpp>
#include <Types/Identifiable.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::InputBindings
{
    void LoadInputAction(kaguya::State* lua)
    {
        Load(lua, "obe.Identifiable");
        (*lua)["obe"]["InputAction"].setClass(kaguya::UserdataMetatable<Input::InputAction, Types::Identifiable>()
            .addFunction("addCondition", &Input::InputAction::addCondition)
            .addFunction("addContext", &Input::InputAction::addContext)
            .addFunction("check", &Input::InputAction::check)
            .addFunction("connect", &Input::InputAction::connect)
            .addFunction("getContexts", &Input::InputAction::getContexts)
            .addFunction("getInterval", &Input::InputAction::getInterval)
            .addFunction("getRepeat", &Input::InputAction::getRepeat)
            .addFunction("setInterval", &Input::InputAction::setInterval)
            .addFunction("setRepeat", &Input::InputAction::setRepeat)
            .addFunction("update", &Input::InputAction::update)
        );
    }

    void LoadInputActionEvent(kaguya::State* lua)
    {
        (*lua)["obe"]["InputActionEvent"].setClass(kaguya::UserdataMetatable<Input::InputActionEvent>()
            .addFunction("getAction", &Input::InputActionEvent::getAction)
            .addFunction("getCondition", &Input::InputActionEvent::getCondition)
        );
    }

    void LoadInputButton(kaguya::State* lua)
    {
        (*lua)["obe"]["InputButton"].setClass(kaguya::UserdataMetatable<Input::InputButton>()
            .addFunction("getKey", &Input::InputButton::getKey)
            .addFunction("getName", &Input::InputButton::getName)
            .addFunction("getType", &Input::InputButton::getType)
            .addFunction("is", &Input::InputButton::is)
            .addFunction("isPressed", &Input::InputButton::isPressed)
            .addFunction("isWritable", &Input::InputButton::isWritable)
        );
    }

    void LoadInputButtonMonitor(kaguya::State* lua)
    {
        (*lua)["obe"]["InputButtonMonitor"].setClass(kaguya::UserdataMetatable<Input::InputButtonMonitor>()
            .addFunction("getButton", &Input::InputButtonMonitor::getButton)
            .addFunction("getState", &Input::InputButtonMonitor::getState)
            .addFunction("update", &Input::InputButtonMonitor::update)
        );

        /*(*lua)["obe"]["InputButtonMonitorPtr"].setClass(kaguya::UserdataMetatable<Input::InputButtonMonitorPtr>()
        );*/
    }
            
    void LoadInputCondition(kaguya::State* lua)
    {
        (*lua)["obe"]["InputCondition"].setClass(kaguya::UserdataMetatable<Input::InputCondition>()
            .addFunction("addCombinationElement", &Input::InputCondition::addCombinationElement)
            .addFunction("check", &Input::InputCondition::check)
            .addFunction("setCombination", &Input::InputCondition::setCombination)
            .addFunction("setCombinationCode", &Input::InputCondition::setCombinationCode)
        );
    }

    void LoadInputManager(kaguya::State* lua)
    {
        (*lua)["obe"]["InputManager"].setClass(kaguya::UserdataMetatable<Input::InputManager>()
            .addFunction("actionExists", &Input::InputManager::actionExists)
            .addFunction("clear", &Input::InputManager::clear)
            .addFunction("clearContexts", &Input::InputManager::clearContexts)
            .addFunction("configure", &Input::InputManager::configure)
            .addFunction("getAction", &Input::InputManager::getAction)
            .addFunction("setContext", &Input::InputManager::setContext)
            .addFunction("setEnabled", &Input::InputManager::setEnabled)
            .addFunction("update", &Input::InputManager::update)
        );

        (*lua)["obe"]["InputManager"]["addContext"] = kaguya::function(
            [](Input::InputManager& manager, const std::string& context)
        {
            return &manager.addContext(context);
        });

        (*lua)["obe"]["InputManager"]["removeContext"] = kaguya::function(
            [](Input::InputManager& manager, const std::string& context)
        {
            return &manager.removeContext(context);
        });
    }

    void LoadInputFunctions(kaguya::State* lua)
    {
        (*lua)["obe"]["Input"] = kaguya::NewTable();
        (*lua)["obe"]["Input"]["Monitors"] = kaguya::NewTable();
        (*lua)["obe"]["Input"]["Monitors"]["UpdateMonitors"] = kaguya::function(Input::Monitors::UpdateMonitors);
        //(*lua)["obe"]["Input"]["Monitors"]["UpdateMonitorsAndRemoveIfNoReferences"] = kaguya::function(Input::Monitors::UpdateMonitorsAndRemoveIfNoReferences);
        (*lua)["obe"]["Input"]["Monitors"]["Monitor"] = kaguya::overload(
            static_cast<Input::InputButtonMonitorPtr(*)(const std::string&)>(Input::Monitors::Monitor),
            static_cast<Input::InputButtonMonitorPtr(*)(Input::InputButton*)>(Input::Monitors::Monitor));
        (*lua)["obe"]["Input"]["InitKeyList"] = kaguya::function(Input::InitKeyList);
        (*lua)["obe"]["Input"]["SetGamepadList"] = kaguya::function(Input::SetGamepadList);
        (*lua)["obe"]["Input"]["GetAllPressedButtons"] = kaguya::function(Input::GetAllPressedButtons);
        (*lua)["obe"]["Input"]["GetKey"] = kaguya::function(Input::GetKey);
        (*lua)["obe"]["Input"]["InputStateToString"] = kaguya::function(Input::inputButtonStateToString);
        (*lua)["obe"]["Input"]["StringToInputState"] = kaguya::function(Input::stringToInputButtonState);
        (*lua)["obe"]["Input"]["State"] = kaguya::NewTable();
        (*lua)["obe"]["Input"]["State"]["Idle"] = Input::InputButtonState::Idle;
        (*lua)["obe"]["Input"]["State"]["Hold"] = Input::InputButtonState::Hold;
        (*lua)["obe"]["Input"]["State"]["Pressed"] = Input::InputButtonState::Pressed;
        (*lua)["obe"]["Input"]["State"]["Released"] = Input::InputButtonState::Released;
    }

    void LoadInputButtons(kaguya::State* lua)
    {
        (*lua)["obe"]["Keyboard"] = kaguya::NewTable();
        (*lua)["obe"]["Mouse"] = kaguya::NewTable();
        (*lua)["obe"]["Gamepad"] = kaguya::NewTable();
        for (auto& inputButtonPair : Input::AllKeys)
        {
            auto& inputButton = inputButtonPair.second;
            if (inputButton->getType() == Input::InputType::Mouse)
            {
                (*lua)["obe"]["Mouse"][inputButton->getName()] = inputButton.get();
            }
            else if (inputButton->getType() == Input::InputType::GamepadAxis
            || inputButton->getType() == Input::InputType::GamepadButton)
            {
                (*lua)["obe"]["Gamepad"][inputButton->getName()] = inputButton.get();
            }
            else
            {
                (*lua)["obe"]["Keyboard"][inputButton->getName()] = inputButton.get();
            }
        }
    }
}
