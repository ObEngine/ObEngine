//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <vili/Vili.hpp>

#include "Triggers.hpp"

namespace obe
{
    namespace Input
    {
        class KeyClass
        {
        private:
            sf::Keyboard::Key m_key;
            std::string m_name;
            std::string m_returnChar;
            std::string m_type;
        public:
            KeyClass()
            {
            }

            KeyClass(sf::Keyboard::Key key, std::string name, std::string returnChar, std::string type);
            sf::Keyboard::Key getKey() const;
            std::string getType();
            bool isAlpha();
            bool isNumeric();
            bool isNumericNP();
            bool isAlphaNumeric();
            bool isArrow();
            bool isFunction();
            bool isOther();
            bool isWritable();
        };

        class KeyBinder
        {
        private:
            std::map<std::string, std::string> m_actionMap;
            std::map<std::string, KeyClass> m_keyMap;
            std::map<std::string, bool> m_currentActionMap;
            std::map<std::string, bool> m_previousActionMap;
            std::map<std::string, int> m_baseActionDelayer;
            std::map<std::string, unsigned long long int> m_actionDelayer;
            bool m_binderEnabled = true;
            std::string getActionKey(std::string action);
            KeyClass* getKey(std::string key);
            Script::TriggerGroup::Ptr m_keysTriggers;
        public:
            KeyBinder();
            void setEnabled(bool state);
            void loadFromFile(vili::DataParser& configFile);
            void connectAction(std::string action, std::string key);
            bool isActionToggled(std::string action);
            bool isActionPressed(std::string action);
            bool isActionReleased(std::string action);
            bool isActionEnabled(std::string action);
            bool isActionDisabled(std::string action);
            void setActionDelay(std::string action, int delay);
            bool isKeyPressed(std::string key);
            void update();
            void handleTriggers();
        };
    }
}
