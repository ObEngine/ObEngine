//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "KeyBind.hpp"

namespace obe
{
    namespace Input
    {
        KeyClass::KeyClass(sf::Keyboard::Key key, std::string name, std::string returnChar, std::string type)
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

        std::string KeyBinder::getActionKey(std::string action)
        {
            if (m_actionMap.find(action) != m_actionMap.end())
                return m_actionMap[action];
            throw aube::ErrorHandler::Raise("ObEngine.KeyBinder.KeyBinder.UnknownAction", {{"action", action}});
        }

        KeyClass* KeyBinder::getKey(std::string key)
        {
            if (m_keyMap.find(key) != m_keyMap.end())
                return &m_keyMap[key];
            throw aube::ErrorHandler::Raise("ObEngine.KeyBinder.KeyBinder.UnknownKey", {{"key", key}});
        }

        KeyBinder::KeyBinder()
        {
            m_keysTriggers = Script::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Keys")
                                                                   ->addTrigger("ActionReleased")
                                                                   ->addTrigger("ActionPressed")
                                                                   ->addTrigger("ActionToggled");

            //Alpha
            m_keyMap["A"] = KeyClass(sf::Keyboard::A, "A", "A", "Alpha");
            m_keyMap["Z"] = KeyClass(sf::Keyboard::Z, "Z", "Z", "Alpha");
            m_keyMap["E"] = KeyClass(sf::Keyboard::E, "E", "E", "Alpha");
            m_keyMap["R"] = KeyClass(sf::Keyboard::R, "R", "E", "Alpha");
            m_keyMap["T"] = KeyClass(sf::Keyboard::T, "T", "T", "Alpha");
            m_keyMap["Y"] = KeyClass(sf::Keyboard::Y, "Y", "Y", "Alpha");
            m_keyMap["U"] = KeyClass(sf::Keyboard::U, "U", "U", "Alpha");
            m_keyMap["I"] = KeyClass(sf::Keyboard::I, "I", "I", "Alpha");
            m_keyMap["O"] = KeyClass(sf::Keyboard::O, "O", "O", "Alpha");
            m_keyMap["P"] = KeyClass(sf::Keyboard::P, "P", "P", "Alpha");
            m_keyMap["Q"] = KeyClass(sf::Keyboard::Q, "Q", "Q", "Alpha");
            m_keyMap["S"] = KeyClass(sf::Keyboard::S, "S", "S", "Alpha");
            m_keyMap["D"] = KeyClass(sf::Keyboard::D, "D", "D", "Alpha");
            m_keyMap["F"] = KeyClass(sf::Keyboard::F, "F", "F", "Alpha");
            m_keyMap["G"] = KeyClass(sf::Keyboard::G, "G", "G", "Alpha");
            m_keyMap["H"] = KeyClass(sf::Keyboard::H, "H", "H", "Alpha");
            m_keyMap["J"] = KeyClass(sf::Keyboard::J, "J", "J", "Alpha");
            m_keyMap["K"] = KeyClass(sf::Keyboard::K, "K", "K", "Alpha");
            m_keyMap["L"] = KeyClass(sf::Keyboard::L, "L", "L", "Alpha");
            m_keyMap["M"] = KeyClass(sf::Keyboard::M, "M", "M", "Alpha");
            m_keyMap["W"] = KeyClass(sf::Keyboard::W, "W", "W", "Alpha");
            m_keyMap["X"] = KeyClass(sf::Keyboard::X, "X", "W", "Alpha");
            m_keyMap["C"] = KeyClass(sf::Keyboard::C, "C", "C", "Alpha");
            m_keyMap["V"] = KeyClass(sf::Keyboard::V, "V", "V", "Alpha");
            m_keyMap["B"] = KeyClass(sf::Keyboard::B, "B", "B", "Alpha");
            m_keyMap["N"] = KeyClass(sf::Keyboard::N, "N", "N", "Alpha");
            //Numeric
            m_keyMap["0"] = KeyClass(sf::Keyboard::Num0, "0", "0", "Numeric");
            m_keyMap["1"] = KeyClass(sf::Keyboard::Num1, "1", "1", "Numeric");
            m_keyMap["2"] = KeyClass(sf::Keyboard::Num2, "2", "2", "Numeric");
            m_keyMap["3"] = KeyClass(sf::Keyboard::Num3, "3", "3", "Numeric");
            m_keyMap["4"] = KeyClass(sf::Keyboard::Num4, "4", "4", "Numeric");
            m_keyMap["5"] = KeyClass(sf::Keyboard::Num5, "5", "5", "Numeric");
            m_keyMap["6"] = KeyClass(sf::Keyboard::Num6, "6", "6", "Numeric");
            m_keyMap["7"] = KeyClass(sf::Keyboard::Num7, "7", "7", "Numeric");
            m_keyMap["8"] = KeyClass(sf::Keyboard::Num8, "8", "8", "Numeric");
            m_keyMap["9"] = KeyClass(sf::Keyboard::Num9, "9", "9", "Numeric");
            //Numpad
            m_keyMap["NumPad0"] = KeyClass(sf::Keyboard::Numpad0, "NumPad0", "0", "NumericNP");
            m_keyMap["NumPad1"] = KeyClass(sf::Keyboard::Numpad1, "NumPad1", "1", "NumericNP");
            m_keyMap["NumPad2"] = KeyClass(sf::Keyboard::Numpad2, "NumPad2", "2", "NumericNP");
            m_keyMap["NumPad3"] = KeyClass(sf::Keyboard::Numpad3, "NumPad3", "3", "NumericNP");
            m_keyMap["NumPad4"] = KeyClass(sf::Keyboard::Numpad4, "NumPad4", "4", "NumericNP");
            m_keyMap["NumPad5"] = KeyClass(sf::Keyboard::Numpad5, "NumPad5", "5", "NumericNP");
            m_keyMap["NumPad6"] = KeyClass(sf::Keyboard::Numpad6, "NumPad6", "6", "NumericNP");
            m_keyMap["NumPad7"] = KeyClass(sf::Keyboard::Numpad7, "NumPad7", "7", "NumericNP");
            m_keyMap["NumPad8"] = KeyClass(sf::Keyboard::Numpad8, "NumPad8", "8", "NumericNP");
            m_keyMap["NumPad9"] = KeyClass(sf::Keyboard::Numpad9, "NumPad9", "9", "NumericNP");
            //Arrows
            m_keyMap["Left"] = KeyClass(sf::Keyboard::Left, "Left", "", "Arrows");
            m_keyMap["Right"] = KeyClass(sf::Keyboard::Right, "Right", "", "Arrows");
            m_keyMap["Up"] = KeyClass(sf::Keyboard::Up, "Up", "", "Arrows");
            m_keyMap["Down"] = KeyClass(sf::Keyboard::Down, "Down", "", "Arrows");
            //Functions
            m_keyMap["F1"] = KeyClass(sf::Keyboard::F1, "F1", "", "Functions");
            m_keyMap["F2"] = KeyClass(sf::Keyboard::F2, "F2", "", "Functions");
            m_keyMap["F3"] = KeyClass(sf::Keyboard::F3, "F3", "", "Functions");
            m_keyMap["F4"] = KeyClass(sf::Keyboard::F4, "F4", "", "Functions");
            m_keyMap["F5"] = KeyClass(sf::Keyboard::F5, "F5", "", "Functions");
            m_keyMap["F6"] = KeyClass(sf::Keyboard::F6, "F6", "", "Functions");
            m_keyMap["F7"] = KeyClass(sf::Keyboard::F7, "F7", "", "Functions");
            m_keyMap["F8"] = KeyClass(sf::Keyboard::F8, "F8", "", "Functions");
            m_keyMap["F9"] = KeyClass(sf::Keyboard::F9, "F9", "", "Functions");
            m_keyMap["F10"] = KeyClass(sf::Keyboard::F10, "F10", "", "Functions");
            m_keyMap["F11"] = KeyClass(sf::Keyboard::F11, "F11", "", "Functions");
            m_keyMap["F12"] = KeyClass(sf::Keyboard::F12, "F12", "", "Functions");
            //Others
            m_keyMap["Add"] = KeyClass(sf::Keyboard::Add, "Add", "+", "Others");
            m_keyMap["BackSlash"] = KeyClass(sf::Keyboard::BackSlash, "BackSlash", "\\", "Others");
            m_keyMap["BackSpace"] = KeyClass(sf::Keyboard::BackSpace, "BackSpace", "", "Others");
            m_keyMap["Comma"] = KeyClass(sf::Keyboard::Comma, "Comma", ",", "Others");
            m_keyMap["Dash"] = KeyClass(sf::Keyboard::Dash, "Dash", "-", "Others");
            m_keyMap["Delete"] = KeyClass(sf::Keyboard::Delete, "Delete", "", "Others");
            m_keyMap["Divide"] = KeyClass(sf::Keyboard::Divide, "Divide", "/", "Others");
            m_keyMap["End"] = KeyClass(sf::Keyboard::End, "End", "", "Others");
            m_keyMap["Equal"] = KeyClass(sf::Keyboard::Equal, "Equal", "=", "Others");
            m_keyMap["Escape"] = KeyClass(sf::Keyboard::Escape, "Escape", "", "Others");
            m_keyMap["Home"] = KeyClass(sf::Keyboard::Home, "Home", "", "Others");
            m_keyMap["Insert"] = KeyClass(sf::Keyboard::Insert, "Insert", "", "Others");
            m_keyMap["LAlt"] = KeyClass(sf::Keyboard::LAlt, "LAlt", "", "Others");
            m_keyMap["LBracket"] = KeyClass(sf::Keyboard::LBracket, "LBracket", "[", "Others");
            m_keyMap["LControl"] = KeyClass(sf::Keyboard::LControl, "LControl", "", "Others");
            m_keyMap["LShift"] = KeyClass(sf::Keyboard::LShift, "LShift", "", "Others");
            m_keyMap["Menu"] = KeyClass(sf::Keyboard::Menu, "Menu", "", "Others");
            m_keyMap["Multiply"] = KeyClass(sf::Keyboard::Multiply, "Multiply", "*", "Others");
            m_keyMap["PageDown"] = KeyClass(sf::Keyboard::PageDown, "PageDown", "", "Others");
            m_keyMap["PageUp"] = KeyClass(sf::Keyboard::PageUp, "PageUp", "", "Others");
            m_keyMap["Pause"] = KeyClass(sf::Keyboard::Pause, "Pause", "", "Others");
            m_keyMap["Period"] = KeyClass(sf::Keyboard::Period, "Period", ".", "Others");
            m_keyMap["Quote"] = KeyClass(sf::Keyboard::Quote, "Quote", "\"", "Others");
            m_keyMap["RAlt"] = KeyClass(sf::Keyboard::RAlt, "RAlt", "", "Others");
            m_keyMap["RBracket"] = KeyClass(sf::Keyboard::RBracket, "RBracket", "]", "Others");
            m_keyMap["RControl"] = KeyClass(sf::Keyboard::RControl, "RControl", "", "Others");
            m_keyMap["Return"] = KeyClass(sf::Keyboard::Return, "Return", "", "Others");
            m_keyMap["RShift"] = KeyClass(sf::Keyboard::RShift, "RShift", "", "Others");
            m_keyMap["RSystem"] = KeyClass(sf::Keyboard::RSystem, "RSystem", "", "Others");
            m_keyMap["SemiColon"] = KeyClass(sf::Keyboard::SemiColon, "SemiColor", ";", "Others");
            m_keyMap["Slash"] = KeyClass(sf::Keyboard::Slash, "Slash", "/", "Others");
            m_keyMap["Space"] = KeyClass(sf::Keyboard::Space, "Space", " ", "Others");
            m_keyMap["Substract"] = KeyClass(sf::Keyboard::Subtract, "Substract", "-", "Others");
            m_keyMap["Tab"] = KeyClass(sf::Keyboard::Tab, "Tab", "    ", "Others");
            m_keyMap["Tilde"] = KeyClass(sf::Keyboard::Tilde, "Tilde", "~", "Others");
        }

        void KeyBinder::setEnabled(bool state)
        {
            m_binderEnabled = state;
        }

        void KeyBinder::update()
        {
            if (m_binderEnabled)
            {
                typedef std::map<std::string, std::string>::iterator it_type;
                for (it_type iterator = m_actionMap.begin(); iterator != m_actionMap.end(); ++iterator)
                {
                    m_previousActionMap[iterator->first] = m_currentActionMap[iterator->first];
                    m_currentActionMap[iterator->first] = sf::Keyboard::isKeyPressed(getKey(iterator->second)->getKey());
                    if (!m_currentActionMap[iterator->first] && m_previousActionMap[iterator->first])
                    {
                        if (Functions::Map::keyInMap(iterator->first, m_actionDelayer))
                        {
                            m_actionDelayer[iterator->first] = 0;
                        }
                    }
                }
            }
        }

        void KeyBinder::handleTriggers()
        {
            if (m_binderEnabled)
            {
                typedef std::map<std::string, std::string>::iterator it_type;
                std::vector<std::string> toggledActions;
                std::vector<std::string> releasedActions;
                std::vector<std::string> pressedActions;
                for (it_type iterator = m_actionMap.begin(); iterator != m_actionMap.end(); ++iterator)
                {
                    if (isActionToggled(iterator->first))
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
                }
            }
        }

        bool KeyBinder::isActionReleased(std::string action)
        {
            if (m_binderEnabled && !m_currentActionMap[action] && m_previousActionMap[action])
            {
                return true;
            }
            return false;
        }

        bool KeyBinder::isActionEnabled(std::string action)
        {
            if (m_binderEnabled && m_currentActionMap[action])
            {
                if (Functions::Map::keyInMap(action, m_actionDelayer))
                {
                    if (Time::getTickSinceEpoch() - m_actionDelayer[action] > m_baseActionDelayer[action])
                    {
                        m_actionDelayer[action] = Time::getTickSinceEpoch();
                        return true;
                    }
                }
                else
                    return true;
            }
            return false;
        }

        bool KeyBinder::isActionDisabled(std::string action)
        {
            if (m_binderEnabled)
            {
                if (m_currentActionMap[action])
                    return false;
                return true;
            }
            return true;
        }

        void KeyBinder::setActionDelay(std::string action, int delay)
        {
            m_baseActionDelayer[action] = delay;
            m_actionDelayer[action] = 0;
        }

        bool KeyBinder::isKeyPressed(std::string key)
        {
            return sf::Keyboard::isKeyPressed(getKey(key)->getKey());
        }

        void KeyBinder::connectAction(std::string action, std::string key)
        {
            m_actionMap[action] = key;
        }

        bool KeyBinder::isActionToggled(std::string action)
        {
            if (m_binderEnabled)
            {
                if (m_currentActionMap[action] != m_previousActionMap[action])
                    return true;
                return false;
            }
            return false;
        }

        bool KeyBinder::isActionPressed(std::string action)
        {
            if (m_binderEnabled)
            {
                if (m_currentActionMap[action] && !m_previousActionMap[action])
                    return true;
                return false;
            }
            return false;
        }

        void KeyBinder::loadFromFile(vili::DataParser& configFile)
        {
            std::vector<std::string> allGameKeys = configFile.at("KeyBinding", "game").getAll(vili::Types::BaseAttribute);
            for (unsigned int i = 0; i < allGameKeys.size(); i++)
                m_actionMap[allGameKeys[i]] = configFile.at("KeyBinding", "game").getBaseAttribute(allGameKeys[i]).get<std::string>();
            std::vector<std::string> allMapEditorKeys = configFile.at("KeyBinding", "mapEditor").getAll(vili::Types::BaseAttribute);
            for (unsigned int i = 0; i < allMapEditorKeys.size(); i++)
                m_actionMap[allMapEditorKeys[i]] = configFile.at("KeyBinding", "mapEditor").getBaseAttribute(allMapEditorKeys[i]).get<std::string>();
        }
    }
}
