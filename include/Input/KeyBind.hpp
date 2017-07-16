#pragma once

#include <SFML/Window.hpp>
#include <vili/Vili.hpp>

#include <Triggers/TriggerGroup.hpp>

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
            KeyClass() {}
            KeyClass(sf::Keyboard::Key key, const std::string& name, const std::string& returnChar, const std::string& type);
            sf::Keyboard::Key getKey() const;
            std::string getType() const;
            bool isAlpha() const;
            bool isNumeric() const;
            bool isNumericNP() const;
            bool isAlphaNumeric() const;
            bool isArrow() const;
            bool isFunction();
            bool isOther();
            bool isWritable() const;
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
            Triggers::TriggerGroup::Ptr m_keysTriggers;
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
