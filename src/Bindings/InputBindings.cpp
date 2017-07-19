#include <Bindings/InputBindings.hpp>
#include <Input/KeyManager.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace InputBindings
        {
            void LoadKeyClass(kaguya::State& lua)
            {
                lua["Core"]["Input"]["KeyClass"].setClass(kaguya::UserdataMetatable<Input::KeyClass>()
                    .addFunction("getKey", &Input::KeyClass::getKey)
                    .addFunction("getName", &Input::KeyClass::getName)
                    .addFunction("getType", &Input::KeyClass::getType)
                    .addFunction("isAlpha", &Input::KeyClass::isAlpha)
                    .addFunction("isAlphaNumeric", &Input::KeyClass::isAlphaNumeric)
                    .addFunction("isArrow", &Input::KeyClass::isArrow)
                    .addFunction("isFunction", &Input::KeyClass::isFunction)
                    .addFunction("isNumeric", &Input::KeyClass::isNumeric)
                    .addFunction("isNumericNP", &Input::KeyClass::isNumericNP)
                    .addFunction("isOther", &Input::KeyClass::isOther)
                    .addFunction("isPressed", &Input::KeyClass::isPressed)
                    .addFunction("isWritable", &Input::KeyClass::isWritable)
                );
            }
            void LoadKeyboardActionEvent(kaguya::State& lua)
            {
                lua["Core"]["Input"]["KeyboardActionEvent"].setClass(kaguya::UserdataMetatable<Input::KeyboardActionEvent>()
                    .addFunction("getAction", &Input::KeyboardActionEvent::getAction)
                    .addFunction("getKey", &Input::KeyboardActionEvent::getKey)
                    .addFunction("getState", &Input::KeyboardActionEvent::getState)
                );
            }
            void LoadKeyboardAction(kaguya::State& lua)
            {
                lua["Core"]["Input"]["KeyboardAction"].setClass(kaguya::UserdataMetatable<Input::KeyboardAction, Types::Identifiable>()
                    .addFunction("addContext", &Input::KeyboardAction::addContext)
                    .addFunction("addKey", &Input::KeyboardAction::addKey)
                    .addFunction("connect", &Input::KeyboardAction::connect)
                    .addFunction("getContexts", &Input::KeyboardAction::getContexts)
                    .addFunction("getKeys", &Input::KeyboardAction::getKeys)
                    .addFunction("getPressDelay", &Input::KeyboardAction::getPressDelay)
                    .addFunction("getRepeat", &Input::KeyboardAction::getRepeat)
                    .addFunction("getState", &Input::KeyboardAction::getState)
                    .addFunction("setPressDelay", &Input::KeyboardAction::setPressDelay)
                    .addFunction("setRepeat", &Input::KeyboardAction::setRepeat)
                    .addFunction("update", &Input::KeyboardAction::update)
                );
            }
            void LoadKeyboardManager(kaguya::State& lua)
            {
                lua["Core"]["Input"]["KeyboardManager"].setClass(kaguya::UserdataMetatable<Input::KeyboardManager>()
                    .addFunction("actionExists", &Input::KeyboardManager::actionExists)
                    /*.addFunction("addContext", &Input::KeyboardManager::addContext) <REVISION> */
                    .addFunction("clearContexts", &Input::KeyboardManager::clearContexts)
                    .addFunction("configure", &Input::KeyboardManager::configure)
                    .addFunction("getAction", &Input::KeyboardManager::getAction)
                    .addFunction("getKey", &Input::KeyboardManager::getKey)
                    .addFunction("handleTriggers", &Input::KeyboardManager::handleTriggers)
                    .addFunction("setContext", &Input::KeyboardManager::setContext)
                    .addFunction("setEnabled", &Input::KeyboardManager::setEnabled)
                    .addFunction("update", &Input::KeyboardManager::update)
                );
            }
        }
    }
}
