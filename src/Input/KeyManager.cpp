#include <Input/KeyManager.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/MapUtils.hpp>
#include <Time/TimeUtils.hpp>

namespace obe
{
    namespace Input
    {
        std::ostream& operator<<(std::ostream& os, KeyState m)
        {
            switch (m)
            {
            case KeyState::Hold:
                os << "Hold";
                break;
            case KeyState::Idle:
                os << "Idle";
                break;
            case KeyState::Pressed:
                os << "Pressed";
                break;
            case KeyState::Released:
                os << "Released";
                break;
            default:
                os << "Error";
                break;
            }
            return os;
        }

        KeyClass::KeyClass(sf::Keyboard::Key key, const std::string& name, const std::string& returnChar, KeyType type)
        {
            m_key = key;
            m_name = name;
            m_returnChar = returnChar;
            m_type = type;
        }

        sf::Keyboard::Key KeyClass::getKey() const
        {
            return m_key;
        }

        std::string KeyClass::getName() const
        {
            return m_name;
        }

        KeyType KeyClass::getType() const
        {
            return m_type;
        }

        bool KeyClass::isAlpha() const
        {
            return (m_type == KeyType::Alpha);
        }

        bool KeyClass::isNumeric() const
        {
            return (m_type == KeyType::Numeric);
        }

        bool KeyClass::isNumericNP() const
        {
            return (m_type == KeyType::NumericNP);
        }

        bool KeyClass::isAlphaNumeric() const
        {
            return (isAlpha() || isNumeric() || isNumericNP());
        }

        bool KeyClass::isArrow() const
        {
            return (m_type == KeyType::Arrows);
        }

        bool KeyClass::isFunction() const
        {
            return (m_type == KeyType::Functions);
        }

        bool KeyClass::isOther() const
        {
            return (m_type == KeyType::Others);
        }

        bool KeyClass::isWritable() const
        {
            return (!m_returnChar.empty());
        }

        bool KeyClass::isPressed() const
        {
            return sf::Keyboard::isKeyPressed(m_key);
        }

        KeyboardActionEvent::KeyboardActionEvent(KeyState state, KeyboardAction* action, KeyClass* key)
        {
            m_state = state;
            m_action = action;
            m_key = key;
        }

        KeyState KeyboardActionEvent::getState() const
        {
            return m_state;
        }

        KeyboardAction* KeyboardActionEvent::getAction() const
        {
            return m_action;
        }

        KeyClass* KeyboardActionEvent::getKey() const
        {
            return m_key;
        }

        KeyboardAction::KeyboardAction(const std::string& id) : Identifiable(id)
        {
        }

        std::vector<std::string> KeyboardAction::getContexts() const
        {
            return m_contexts;
        }

        std::vector<KeyClass*> KeyboardAction::getKeys() const
        {
            return m_associatedKeys;
        }

        void KeyboardAction::addContext(const std::string& context)
        {
            if (!Utils::Vector::isInList(context, m_contexts))
                m_contexts.push_back(context);
        }

        void KeyboardAction::setPressDelay(Time::TimeUnit delay)
        {
            m_pressDelay = delay;
        }

        Time::TimeUnit KeyboardAction::getPressDelay() const
        {
            return m_pressDelay;
        }

        void KeyboardAction::setRepeat(Time::TimeUnit delay)
        {
            m_repeatDelay = delay;
        }

        Time::TimeUnit KeyboardAction::getRepeat() const
        {
            return m_repeatDelay;
        }

        void KeyboardAction::connect(KeyState state, ActionCallback callback)
        {
            m_callbacks[state] = callback;
        }

        KeyState KeyboardAction::getState() const
        {
            return m_state;
        }

        void KeyboardAction::addKey(KeyClass* key)
        {
            m_associatedKeys.push_back(key);
        }

        void KeyboardAction::update()
        {
            for (KeyClass* key : m_associatedKeys)
            {
                bool keyPressed = sf::Keyboard::isKeyPressed(key->getKey());
                if (keyPressed && (m_state == KeyState::Idle || m_state == KeyState::Released))
                {
                    if (m_pressDelay == 0)
                        m_state = KeyState::Pressed;
                    else if (Time::getTickSinceEpoch() - m_pressClock >= m_pressDelay)
                    {
                        m_pressClock = Time::getTickSinceEpoch();
                        m_state = KeyState::Pressed;
                    }
                }
                else if (keyPressed && m_state == KeyState::Pressed)
                {
                    m_state = KeyState::Hold;
                }
                else if (!keyPressed && (m_state == KeyState::Pressed || m_state == KeyState::Hold))
                {
                    m_state = KeyState::Released;
                    m_repeatClock = 0;
                }
                else if (!keyPressed && m_state == KeyState::Released)
                {
                    m_state = KeyState::Idle;
                }
                if (m_callbacks.find(m_state) != m_callbacks.end())
                {
                    if (m_repeatDelay != 0 && m_state == KeyState::Hold)
                    {
                        if (Time::getTickSinceEpoch() - m_repeatClock >= m_repeatDelay)
                        {
                            m_repeatClock = Time::getTickSinceEpoch();
                            m_callbacks[m_state](KeyboardActionEvent(m_state, this, key));
                        }
                    }
                    else
                        m_callbacks[m_state](KeyboardActionEvent(m_state, this, key));
                }
            }
        }

        KeyboardAction& KeyboardManager::getAction(const std::string& actionId)
        {
            for (auto& action : m_allActions)
            {
                if (action->getId() == actionId)
                {
                    return *action.get();
                }
            }
            throw aube::ErrorHandler::Raise("ObEngine.KeyBinder.KeyBinder.UnknownAction", {{"action", actionId}});
        }

        KeyClass* KeyboardManager::getKey(const std::string& keyId)
        {
            if (m_keys.find(keyId) != m_keys.end())
                return m_keys[keyId].get();
            throw aube::ErrorHandler::Raise("ObEngine.KeyBinder.KeyBinder.UnknownKey", {{"key", keyId}});
        }

        KeyboardManager::KeyboardManager() : m_keysTriggers(Triggers::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Keys"))
        {
            m_keysTriggers->addTrigger("ActionReleased")
                          ->addTrigger("ActionPressed")
                          ->addTrigger("ActionToggled");

            //Alpha
            m_keys["A"] = std::make_unique<KeyClass>(sf::Keyboard::A, "A", "A", KeyType::Alpha);
            m_keys["Z"] = std::make_unique<KeyClass>(sf::Keyboard::Z, "Z", "Z", KeyType::Alpha);
            m_keys["E"] = std::make_unique<KeyClass>(sf::Keyboard::E, "E", "E", KeyType::Alpha);
            m_keys["R"] = std::make_unique<KeyClass>(sf::Keyboard::R, "R", "E", KeyType::Alpha);
            m_keys["T"] = std::make_unique<KeyClass>(sf::Keyboard::T, "T", "T", KeyType::Alpha);
            m_keys["Y"] = std::make_unique<KeyClass>(sf::Keyboard::Y, "Y", "Y", KeyType::Alpha);
            m_keys["U"] = std::make_unique<KeyClass>(sf::Keyboard::U, "U", "U", KeyType::Alpha);
            m_keys["I"] = std::make_unique<KeyClass>(sf::Keyboard::I, "I", "I", KeyType::Alpha);
            m_keys["O"] = std::make_unique<KeyClass>(sf::Keyboard::O, "O", "O", KeyType::Alpha);
            m_keys["P"] = std::make_unique<KeyClass>(sf::Keyboard::P, "P", "P", KeyType::Alpha);
            m_keys["Q"] = std::make_unique<KeyClass>(sf::Keyboard::Q, "Q", "Q", KeyType::Alpha);
            m_keys["S"] = std::make_unique<KeyClass>(sf::Keyboard::S, "S", "S", KeyType::Alpha);
            m_keys["D"] = std::make_unique<KeyClass>(sf::Keyboard::D, "D", "D", KeyType::Alpha);
            m_keys["F"] = std::make_unique<KeyClass>(sf::Keyboard::F, "F", "F", KeyType::Alpha);
            m_keys["G"] = std::make_unique<KeyClass>(sf::Keyboard::G, "G", "G", KeyType::Alpha);
            m_keys["H"] = std::make_unique<KeyClass>(sf::Keyboard::H, "H", "H", KeyType::Alpha);
            m_keys["J"] = std::make_unique<KeyClass>(sf::Keyboard::J, "J", "J", KeyType::Alpha);
            m_keys["K"] = std::make_unique<KeyClass>(sf::Keyboard::K, "K", "K", KeyType::Alpha);
            m_keys["L"] = std::make_unique<KeyClass>(sf::Keyboard::L, "L", "L", KeyType::Alpha);
            m_keys["M"] = std::make_unique<KeyClass>(sf::Keyboard::M, "M", "M", KeyType::Alpha);
            m_keys["W"] = std::make_unique<KeyClass>(sf::Keyboard::W, "W", "W", KeyType::Alpha);
            m_keys["X"] = std::make_unique<KeyClass>(sf::Keyboard::X, "X", "W", KeyType::Alpha);
            m_keys["C"] = std::make_unique<KeyClass>(sf::Keyboard::C, "C", "C", KeyType::Alpha);
            m_keys["V"] = std::make_unique<KeyClass>(sf::Keyboard::V, "V", "V", KeyType::Alpha);
            m_keys["B"] = std::make_unique<KeyClass>(sf::Keyboard::B, "B", "B", KeyType::Alpha);
            m_keys["N"] = std::make_unique<KeyClass>(sf::Keyboard::N, "N", "N", KeyType::Alpha);
            //Numeric
            m_keys["0"] = std::make_unique<KeyClass>(sf::Keyboard::Num0, "0", "0", KeyType::Numeric);
            m_keys["1"] = std::make_unique<KeyClass>(sf::Keyboard::Num1, "1", "1", KeyType::Numeric);
            m_keys["2"] = std::make_unique<KeyClass>(sf::Keyboard::Num2, "2", "2", KeyType::Numeric);
            m_keys["3"] = std::make_unique<KeyClass>(sf::Keyboard::Num3, "3", "3", KeyType::Numeric);
            m_keys["4"] = std::make_unique<KeyClass>(sf::Keyboard::Num4, "4", "4", KeyType::Numeric);
            m_keys["5"] = std::make_unique<KeyClass>(sf::Keyboard::Num5, "5", "5", KeyType::Numeric);
            m_keys["6"] = std::make_unique<KeyClass>(sf::Keyboard::Num6, "6", "6", KeyType::Numeric);
            m_keys["7"] = std::make_unique<KeyClass>(sf::Keyboard::Num7, "7", "7", KeyType::Numeric);
            m_keys["8"] = std::make_unique<KeyClass>(sf::Keyboard::Num8, "8", "8", KeyType::Numeric);
            m_keys["9"] = std::make_unique<KeyClass>(sf::Keyboard::Num9, "9", "9", KeyType::Numeric);
            //Numpad
            m_keys["NumPad0"] = std::make_unique<KeyClass>(sf::Keyboard::Numpad0, "NumPad0", "0", KeyType::NumericNP);
            m_keys["NumPad1"] = std::make_unique<KeyClass>(sf::Keyboard::Numpad1, "NumPad1", "1", KeyType::NumericNP);
            m_keys["NumPad2"] = std::make_unique<KeyClass>(sf::Keyboard::Numpad2, "NumPad2", "2", KeyType::NumericNP);
            m_keys["NumPad3"] = std::make_unique<KeyClass>(sf::Keyboard::Numpad3, "NumPad3", "3", KeyType::NumericNP);
            m_keys["NumPad4"] = std::make_unique<KeyClass>(sf::Keyboard::Numpad4, "NumPad4", "4", KeyType::NumericNP);
            m_keys["NumPad5"] = std::make_unique<KeyClass>(sf::Keyboard::Numpad5, "NumPad5", "5", KeyType::NumericNP);
            m_keys["NumPad6"] = std::make_unique<KeyClass>(sf::Keyboard::Numpad6, "NumPad6", "6", KeyType::NumericNP);
            m_keys["NumPad7"] = std::make_unique<KeyClass>(sf::Keyboard::Numpad7, "NumPad7", "7", KeyType::NumericNP);
            m_keys["NumPad8"] = std::make_unique<KeyClass>(sf::Keyboard::Numpad8, "NumPad8", "8", KeyType::NumericNP);
            m_keys["NumPad9"] = std::make_unique<KeyClass>(sf::Keyboard::Numpad9, "NumPad9", "9", KeyType::NumericNP);
            //Arrows
            m_keys["Left"] = std::make_unique<KeyClass>(sf::Keyboard::Left, "Left", "", KeyType::Arrows);
            m_keys["Right"] = std::make_unique<KeyClass>(sf::Keyboard::Right, "Right", "", KeyType::Arrows);
            m_keys["Up"] = std::make_unique<KeyClass>(sf::Keyboard::Up, "Up", "", KeyType::Arrows);
            m_keys["Down"] = std::make_unique<KeyClass>(sf::Keyboard::Down, "Down", "", KeyType::Arrows);
            //Functions
            m_keys["F1"] = std::make_unique<KeyClass>(sf::Keyboard::F1, "F1", "", KeyType::Functions);
            m_keys["F2"] = std::make_unique<KeyClass>(sf::Keyboard::F2, "F2", "", KeyType::Functions);
            m_keys["F3"] = std::make_unique<KeyClass>(sf::Keyboard::F3, "F3", "", KeyType::Functions);
            m_keys["F4"] = std::make_unique<KeyClass>(sf::Keyboard::F4, "F4", "", KeyType::Functions);
            m_keys["F5"] = std::make_unique<KeyClass>(sf::Keyboard::F5, "F5", "", KeyType::Functions);
            m_keys["F6"] = std::make_unique<KeyClass>(sf::Keyboard::F6, "F6", "", KeyType::Functions);
            m_keys["F7"] = std::make_unique<KeyClass>(sf::Keyboard::F7, "F7", "", KeyType::Functions);
            m_keys["F8"] = std::make_unique<KeyClass>(sf::Keyboard::F8, "F8", "", KeyType::Functions);
            m_keys["F9"] = std::make_unique<KeyClass>(sf::Keyboard::F9, "F9", "", KeyType::Functions);
            m_keys["F10"] = std::make_unique<KeyClass>(sf::Keyboard::F10, "F10", "", KeyType::Functions);
            m_keys["F11"] = std::make_unique<KeyClass>(sf::Keyboard::F11, "F11", "", KeyType::Functions);
            m_keys["F12"] = std::make_unique<KeyClass>(sf::Keyboard::F12, "F12", "", KeyType::Functions);
            //Others
            m_keys["Add"] = std::make_unique<KeyClass>(sf::Keyboard::Add, "Add", "+", KeyType::Others);
            m_keys["BackSlash"] = std::make_unique<KeyClass>(sf::Keyboard::BackSlash, "BackSlash", "\\", KeyType::Others);
            m_keys["BackSpace"] = std::make_unique<KeyClass>(sf::Keyboard::BackSpace, "BackSpace", "", KeyType::Others);
            m_keys["Comma"] = std::make_unique<KeyClass>(sf::Keyboard::Comma, "Comma", ",", KeyType::Others);
            m_keys["Dash"] = std::make_unique<KeyClass>(sf::Keyboard::Dash, "Dash", "-", KeyType::Others);
            m_keys["Delete"] = std::make_unique<KeyClass>(sf::Keyboard::Delete, "Delete", "", KeyType::Others);
            m_keys["Divide"] = std::make_unique<KeyClass>(sf::Keyboard::Divide, "Divide", "/", KeyType::Others);
            m_keys["End"] = std::make_unique<KeyClass>(sf::Keyboard::End, "End", "", KeyType::Others);
            m_keys["Equal"] = std::make_unique<KeyClass>(sf::Keyboard::Equal, "Equal", "=", KeyType::Others);
            m_keys["Escape"] = std::make_unique<KeyClass>(sf::Keyboard::Escape, "Escape", "", KeyType::Others);
            m_keys["Home"] = std::make_unique<KeyClass>(sf::Keyboard::Home, "Home", "", KeyType::Others);
            m_keys["Insert"] = std::make_unique<KeyClass>(sf::Keyboard::Insert, "Insert", "", KeyType::Others);
            m_keys["LAlt"] = std::make_unique<KeyClass>(sf::Keyboard::LAlt, "LAlt", "", KeyType::Others);
            m_keys["LBracket"] = std::make_unique<KeyClass>(sf::Keyboard::LBracket, "LBracket", "[", KeyType::Others);
            m_keys["LControl"] = std::make_unique<KeyClass>(sf::Keyboard::LControl, "LControl", "", KeyType::Others);
            m_keys["LShift"] = std::make_unique<KeyClass>(sf::Keyboard::LShift, "LShift", "", KeyType::Others);
            m_keys["Menu"] = std::make_unique<KeyClass>(sf::Keyboard::Menu, "Menu", "", KeyType::Others);
            m_keys["Multiply"] = std::make_unique<KeyClass>(sf::Keyboard::Multiply, "Multiply", "*", KeyType::Others);
            m_keys["PageDown"] = std::make_unique<KeyClass>(sf::Keyboard::PageDown, "PageDown", "", KeyType::Others);
            m_keys["PageUp"] = std::make_unique<KeyClass>(sf::Keyboard::PageUp, "PageUp", "", KeyType::Others);
            m_keys["Pause"] = std::make_unique<KeyClass>(sf::Keyboard::Pause, "Pause", "", KeyType::Others);
            m_keys["Period"] = std::make_unique<KeyClass>(sf::Keyboard::Period, "Period", ".", KeyType::Others);
            m_keys["Quote"] = std::make_unique<KeyClass>(sf::Keyboard::Quote, "Quote", "\"", KeyType::Others);
            m_keys["RAlt"] = std::make_unique<KeyClass>(sf::Keyboard::RAlt, "RAlt", "", KeyType::Others);
            m_keys["RBracket"] = std::make_unique<KeyClass>(sf::Keyboard::RBracket, "RBracket", "]", KeyType::Others);
            m_keys["RControl"] = std::make_unique<KeyClass>(sf::Keyboard::RControl, "RControl", "", KeyType::Others);
            m_keys["Return"] = std::make_unique<KeyClass>(sf::Keyboard::Return, "Return", "", KeyType::Others);
            m_keys["RShift"] = std::make_unique<KeyClass>(sf::Keyboard::RShift, "RShift", "", KeyType::Others);
            m_keys["RSystem"] = std::make_unique<KeyClass>(sf::Keyboard::RSystem, "RSystem", "", KeyType::Others);
            m_keys["SemiColon"] = std::make_unique<KeyClass>(sf::Keyboard::SemiColon, "SemiColor", ";", KeyType::Others);
            m_keys["Slash"] = std::make_unique<KeyClass>(sf::Keyboard::Slash, "Slash", "/", KeyType::Others);
            m_keys["Space"] = std::make_unique<KeyClass>(sf::Keyboard::Space, "Space", " ", KeyType::Others);
            m_keys["Substract"] = std::make_unique<KeyClass>(sf::Keyboard::Subtract, "Substract", "-", KeyType::Others);
            m_keys["Tab"] = std::make_unique<KeyClass>(sf::Keyboard::Tab, "Tab", "    ", KeyType::Others);
            m_keys["Tilde"] = std::make_unique<KeyClass>(sf::Keyboard::Tilde, "Tilde", "~", KeyType::Others);
        }

        void KeyboardManager::setEnabled(bool state)
        {
            m_binderEnabled = state;
        }

        void KeyboardManager::update()
        {
            if (m_binderEnabled)
            {
                for (auto& action : m_currentActions)
                {
                    action->update();
                }
            }
        }

        bool KeyboardManager::actionExists(const std::string& actionId)
        {
            for (auto& action : m_allActions)
            {
                if (action->getId() == actionId)
                {
                    return true;
                }
            }
            return false;
        }

        void KeyboardManager::handleTriggers()
        {
            if (m_binderEnabled)
            {
                /*typedef std::map<std::string, std::string>::iterator it_type;
                std::vector<std::string> toggledActions;
                std::vector<std::string> releasedActions;
                std::vector<std::string> pressedActions;
                for (Action& action : m_actions)
                {
                        if (isActionPressed(iterator->first))
                            pressedActions.push_back(iterator->first);
                        if (isActionReleased(iterator->first))
                            releasedActions.push_back(iterator->first);
                        toggledActions.push_back(iterator->first);
                    }
                }

                if (releasedActions.size() >= 1)
                {
                    m_keysTriggers->pushParameter("ActionReleased", "ReleasedActions", releasedActions);
                    m_keysTriggers->enableTrigger("ActionReleased");
                }
                if (pressedActions.size() >= 1)
                {
                    m_keysTriggers->pushParameter("ActionPressed", "PressedActions", pressedActions);
                    m_keysTriggers->enableTrigger("ActionPressed");
                }
                if (toggledActions.size() >= 1)
                {
                    m_keysTriggers->pushParameter("ActionToggled", "ToggledActions", toggledActions);
                    m_keysTriggers->enableTrigger("ActionToggled");
                }*/
            }
        }

        void KeyboardManager::configure(vili::ComplexAttribute& config)
        {
            std::vector<std::string> contexts = config.getAll(vili::AttributeType::ComplexAttribute);
            for (std::string& context : contexts)
            {
                std::vector<std::string> allContextKeys = config.at(context).getAll(vili::AttributeType::BaseAttribute);
                for (std::string& action : allContextKeys)
                {
                    if (!this->actionExists(action))
                    {
                        m_allActions.push_back(std::make_unique<KeyboardAction>(action));
                    }
                    std::string associatedKey = config.at(context).getBaseAttribute(action);
                    std::cout << "Associated Key : " << associatedKey << " for action " << action << std::endl;
                    this->getAction(action).addKey(this->getKey(associatedKey));
                    this->getAction(action).addContext(context);
                }
            }
            //Add Context keys in real time <REVISION>
        }

        void KeyboardManager::clearContexts()
        {
            m_currentActions.clear();
        }

        KeyboardManager& KeyboardManager::addContext(const std::string& context)
        {
            for (auto& action : m_allActions)
            {
                if (Utils::Vector::isInList(context, action->getContexts()) && !Utils::Vector::isInList(action.get(), m_currentActions))
                {
                    m_currentActions.push_back(action.get());
                }
            }
            return *this;
        }

        void KeyboardManager::setContext(const std::string& context)
        {
            this->clearContexts();
            this->addContext(context);
        }
    }
}
