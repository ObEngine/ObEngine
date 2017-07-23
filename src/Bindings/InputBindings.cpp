#include <Bindings/InputBindings.hpp>
#include <Input/InputButton.hpp>
#include <Input/InputActionEvent.hpp>
#include <Input/InputManager.hpp>
#include <Types/Identifiable.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace InputBindings
        {
            void LoadKeyClass(kaguya::State& lua)
            {
                lua["Core"]["Input"]["KeyClass"].setClass(kaguya::UserdataMetatable<Input::InputButton>()
                    .addFunction("getKey", &Input::InputButton::getKey)
                    .addFunction("getName", &Input::InputButton::getName)
                    .addFunction("getType", &Input::InputButton::getType)
                    .addFunction("isAlpha", &Input::InputButton::isAlpha)
                    .addFunction("isAlphaNumeric", &Input::InputButton::isAlphaNumeric)
                    .addFunction("isArrow", &Input::InputButton::isArrow)
                    .addFunction("isFunction", &Input::InputButton::isFunction)
                    .addFunction("isNumeric", &Input::InputButton::isNumeric)
                    .addFunction("isNumericNP", &Input::InputButton::isNumericNP)
                    .addFunction("isOther", &Input::InputButton::isOther)
                    .addFunction("isPressed", &Input::InputButton::isPressed)
                    .addFunction("isWritable", &Input::InputButton::isWritable)
                );
            }
            void LoadKeyboardActionEvent(kaguya::State& lua)
            {
                lua["Core"]["Input"]["KeyboardActionEvent"].setClass(kaguya::UserdataMetatable<Input::InputActionEvent>()
                    .addFunction("getAction", &Input::InputActionEvent::getAction)
                );
            }
            void LoadKeyboardAction(kaguya::State& lua)
            {
                lua["Core"]["Input"]["KeyboardAction"].setClass(kaguya::UserdataMetatable<Input::InputAction, Types::Identifiable>()
                    .addFunction("addContext", &Input::InputAction::addContext)
                    .addFunction("getContexts", &Input::InputAction::getContexts)
                    .addFunction("getRepeat", &Input::InputAction::getRepeat)
                    .addFunction("setRepeat", &Input::InputAction::setRepeat)
                    .addFunction("update", &Input::InputAction::update)
                );
            }
            void LoadKeyboardManager(kaguya::State& lua)
            {
                lua["Core"]["Input"]["KeyboardManager"].setClass(kaguya::UserdataMetatable<Input::InputManager>()
                    .addFunction("actionExists", &Input::InputManager::actionExists)
                    /*.addFunction("addContext", &Input::KeyboardManager::addContext) <REVISION> */
                    .addFunction("clearContexts", &Input::InputManager::clearContexts)
                    .addFunction("configure", &Input::InputManager::configure)
                    .addFunction("getAction", &Input::InputManager::getAction)
                    .addFunction("handleTriggers", &Input::InputManager::handleTriggers)
                    .addFunction("setContext", &Input::InputManager::setContext)
                    .addFunction("setEnabled", &Input::InputManager::setEnabled)
                    .addFunction("update", &Input::InputManager::update)
                );
            }
        }
    }
}
