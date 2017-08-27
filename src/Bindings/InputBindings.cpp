#include <Bindings/Bindings.hpp>
#include <Bindings/InputBindings.hpp>
#include <Input/InputButton.hpp>
#include <Input/InputActionEvent.hpp>
#include <Input/InputManager.hpp>
#include <Input/KeyList.hpp>
#include <Types/Identifiable.hpp>


namespace obe
{
    namespace Bindings
    {
        namespace InputBindings
        {
            void LoadInputAction(kaguya::State* lua)
            {
                Load(lua, "Core.Types.Identifiable");
                (*lua)["Core"]["Input"]["InputAction"].setClass(kaguya::UserdataMetatable<Input::InputAction, Types::Identifiable>()
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
                (*lua)["Core"]["Input"]["InputActionEvent"].setClass(kaguya::UserdataMetatable<Input::InputActionEvent>()
                    .addFunction("getAction", &Input::InputActionEvent::getAction)
                    .addFunction("getCondition", &Input::InputActionEvent::getCondition)
                );
            }
            void LoadInputButton(kaguya::State* lua)
            {
                (*lua)["Core"]["Input"]["InputButton"].setClass(kaguya::UserdataMetatable<Input::InputButton>()
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
                (*lua)["Core"]["Input"]["InputButtonMonitor"].setClass(kaguya::UserdataMetatable<Input::InputButtonMonitor>()
                    .addFunction("getButton", &Input::InputButtonMonitor::getButton)
                    .addFunction("getReferences", &Input::InputButtonMonitor::getReferences)
                    .addFunction("getState", &Input::InputButtonMonitor::getState)
                    .addFunction("update", &Input::InputButtonMonitor::update)
                );

                (*lua)["Core"]["Input"]["InputButtonMonitorPtr"].setClass(kaguya::UserdataMetatable<Input::InputButtonMonitorPtr>()
                    .addFunction("getButton", &Input::InputButtonMonitorPtr::getButton)
                    .addFunction("getState", &Input::InputButtonMonitorPtr::getState)
                );
            }
            
            void LoadInputCondition(kaguya::State* lua)
            {
                (*lua)["Core"]["Input"]["InputCondition"].setClass(kaguya::UserdataMetatable<Input::InputCondition>()
                    .addFunction("addCombinationElement", &Input::InputCondition::addCombinationElement)
                    .addFunction("check", &Input::InputCondition::check)
                    .addFunction("setCombination", &Input::InputCondition::setCombination)
                    .addFunction("setCombinationCode", &Input::InputCondition::setCombinationCode)
                );
            }

            void LoadInputManager(kaguya::State* lua)
            {
                (*lua)["Core"]["Input"]["InputManager"].setClass(kaguya::UserdataMetatable<Input::InputManager>()
                    .addFunction("actionExists", &Input::InputManager::actionExists)
                    .addFunction("clearContexts", &Input::InputManager::clearContexts)
                    .addFunction("configure", &Input::InputManager::configure)
                    .addFunction("getAction", &Input::InputManager::getAction)
                    .addFunction("handleTriggers", &Input::InputManager::handleTriggers)
                    .addFunction("setContext", &Input::InputManager::setContext)
                    .addFunction("setEnabled", &Input::InputManager::setEnabled)
                    .addFunction("update", &Input::InputManager::update)
                );

                (*lua)["Core"]["Input"]["InputManager"]["addContext"] = kaguya::function(
                    [](Input::InputManager& manager, const std::string& context)
                {
                    return &manager.addContext(context);
                });

                (*lua)["Core"]["Input"]["InputManager"]["removeContext"] = kaguya::function(
                    [](Input::InputManager& manager, const std::string& context)
                {
                    return &manager.removeContext(context);
                });
            }

            void LoadInputFunctions(kaguya::State* lua)
            {
                (*lua)["Core"]["Input"]["Monitors"] = kaguya::NewTable();
                (*lua)["Core"]["Input"]["Monitors"]["UpdateMonitors"] = kaguya::function(Input::Monitors::UpdateMonitors);
                (*lua)["Core"]["Input"]["Monitors"]["UpdateMonitorsAndRemoveIfNoReferences"] = kaguya::function(Input::Monitors::UpdateMonitorsAndRemoveIfNoReferences);
                (*lua)["Core"]["Input"]["Monitors"]["Monitor"] = kaguya::overload(
                    static_cast<Input::InputButtonMonitorPtr(*)(const std::string&)>(Input::Monitors::Monitor),
                    static_cast<Input::InputButtonMonitorPtr(*)(Input::InputButton*)>(Input::Monitors::Monitor));
                (*lua)["Core"]["Input"]["InitKeyList"] = kaguya::function(Input::InitKeyList);
                (*lua)["Core"]["Input"]["SetGamepadList"] = kaguya::function(Input::SetGamepadList);
                (*lua)["Core"]["Input"]["GetAllPressedButtons"] = kaguya::function(Input::GetAllPressedButtons);
                (*lua)["Core"]["Input"]["GetKey"] = kaguya::function(Input::GetKey);
            }
            
        }
    }
}
