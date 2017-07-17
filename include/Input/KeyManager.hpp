#pragma once

#include <unordered_map>

#include <SFML/Window.hpp>
#include <vili/Vili.hpp>

#include <Triggers/TriggerGroup.hpp>
#include <Types/Identifiable.hpp>

namespace obe
{
    namespace Input
    {
        /**
         * \brief The type of a Keyboard Key
         */
        enum class KeyType
        {
            /**
             * \brief All letters from A to Z
             */
            Alpha,
            /**
             * \brief All numbers from 0 to 9
             */
            Numeric,
            /**
             * \brief All numbers from 0 to 9 on Numpad
             */
            NumericNP,
            /**
             * \brief All arrow keys (Left, Up, Down, Right)
             */
            Arrows,
            /**
             * \brief All Functions keys from F1 to F12 on most keyboards
             */
            Functions,
            /**
             * \brief Other keys (Symbols etc..)
             */
            Others
        };
        /**
         * \brief Class that does represent a Keyboard key
         */
        class KeyClass
        {
        private:
            sf::Keyboard::Key m_key;
            std::string m_name;
            std::string m_returnChar;
            KeyType m_type;
        public:
            /**
             * \brief Creates a new KeyClass
             * \param key SFML Keyboard Key
             * \param name Name of the Key
             * \param returnChar The character printed when the key is pressed
             * \param type Type of the Key (Arrows, Alpha, Numeric, NumericNP, Functions, Others)
             */
            KeyClass(sf::Keyboard::Key key, const std::string& name, const std::string& returnChar, KeyType type);
            /**
             * \brief Get the SFML Keyboard Key
             * \return SFML Keyboard Key
             */
            sf::Keyboard::Key getKey() const;
            /**
             * \brief Get the name of the Key
             * \return A std::string containing the name of the Key
             */
            std::string getName() const;
            /**
             * \brief Get the type of the Key (Arrows, Alpha, Numeric, NumericNP, Functions, Others)
             * \return An enum value from KeyType which is the type of the key
             */
            KeyType getType() const;
            // Type
            /**
             * \brief Get if the key is a letter
             * \return true if the key is a letter from the Alphabet (A-Z), false otherwise
             */
            bool isAlpha() const;
            /**
             * \brief Get if the key is a number
             * \return true if the key is a number (not from the numpad), false otherwise
             */
            bool isNumeric() const;
            /**
             * \brief Get if the key is a number from the NumPad
             * \return true if the key is a number (from the numpad), false otherwise
             */
            bool isNumericNP() const;
            /**
             * \brief Get if the key is either isAlpha() or isNumeric()
             * \return true if the key is a number or a letter, false otherwise
             */
            bool isAlphaNumeric() const;
            /**
             * \brief Get if the key is an arrow key
             * \return true if the key is an arrow key, false other wise
             */
            bool isArrow() const;
            /**
             * \brief Get if the key is a function key
             * \return true if the key is a function key (From F1 to F12 on most keyboards), false otherwise
             */
            bool isFunction() const;
            /**
             * \brief Get if the key is not any of the type above
             * \return true if the key is not one of the other type, false otherwise
             */
            bool isOther() const;
            // Write
            /**
             * \brief Get if the key prints a writable character
             * \return true if the key prints a writable character, false otherwise
             */
            bool isWritable() const;
            // State
            /**
             * \brief Get if the key is pressed
             * \return true if the key is pressed, false otherwise
             */
            bool isPressed() const;
        };

        enum class KeyState
        {
            Idle,
            Hold,
            Pressed,
            Released
        };

        std::ostream& operator<<(std::ostream& os, KeyState m);

        class KeyboardAction;
        /**
         * \brief Model to send to KeyboardAction callbacks as only parameter
         */
        class KeyboardActionEvent
        {
        private:
            KeyState m_state;
            KeyboardAction* m_action;
            KeyClass* m_key;
        public:
            /**
             * \brief Creates a new KeyboardActionEvent
             * \param state Type of the event (From KeyState)
             * \param action Action linked to the event
             * \param key Key that triggered the action
             */
            KeyboardActionEvent(KeyState state, KeyboardAction* action, KeyClass* key);
            /**
             * \brief Get the type of the event (From KeyState)
             * \return The type of the event (Idle, Hold, Pressed, Released)
             */
            KeyState getState() const;
            /**
             * \brief Get the KeyboardAction linked to the KeyboardActionEvent
             * \return A pointer to the KeyboardAction linked to the KeyboardActionEvent
             */
            KeyboardAction* getAction() const;
            /**
             * \brief Get the key that triggered the KeyboardAction
             * \return A pointer to the KeyClass that represents the key that triggered the KeyboardAction
             */
            KeyClass* getKey() const;
        };

        /**
         * \brief Function callback type for KeyboardAction
         */
        using ActionCallback = std::function<void(KeyboardActionEvent event)>;
        class KeyboardAction : public Types::Identifiable
        {
        private:
            std::map<KeyState, ActionCallback> m_callbacks;
            std::vector<std::string> m_contexts;
            KeyState m_state = KeyState::Idle;
            std::vector<KeyClass*> m_associatedKeys;
            Time::TimeUnit m_pressDelay = 0;
            Time::TimeUnit m_pressClock = 0;
            Time::TimeUnit m_repeatDelay = 0;
            Time::TimeUnit m_repeatClock = 0;
        public:
            /**
             * \brief Creates a new KeyboardAction
             * \param id Id of the KeyboardAction
             */
            explicit KeyboardAction(const std::string& id);
            /**
             * \brief Adds a key which will be able to trigger the KeyboardAction
             * \param key Pointer to the KeyClass that will be able to trigger the KeyboardAction
             */
            void addKey(KeyClass* key);
            /**
             * \brief Adds a new Callback (Only one callback per state)
             * \param state Type of the state you want to set the callback (From KeyState)
             * \param callback A function that will be called when the state is triggered
             */
            void connect(KeyState state, ActionCallback callback);
            /**
             * \brief Get the current state of the KeyboardAction
             * \return The KeyState defining the current state of the KeyboardAction
             */
            KeyState getState() const;
            /**
             * \brief Adds a context to the KeyboardAction
             * \param context New context for the KeyboardAction
             */
            void addContext(const std::string& context);
            /**
             * \brief Get all the contexts the KeyboardAction is in
             * \return A std::vector of std::string containing all the contexts
             */
            std::vector<std::string> getContexts() const;
            /**
             * \brief Get the list of all keys that are able to trigger the KeyboardAction
             * \return A std::vector of KeyClass that are able to trigger the KeyboardAction
             */
            std::vector<KeyClass*> getKeys() const;
            /**
             * \brief Sets the delay required between two KeyboardAction triggerings
             * \param delay Delay required between two KeyboardAction triggerings (in ms)
             */
            void setPressDelay(Time::TimeUnit delay);
            /**
             * \brief Gets the delay required between two KeyboardAction triggerings
             * \return The delay required between two KeyboardAction triggerings (in ms)
             */
            Time::TimeUnit getPressDelay() const;
            /**
             * \brief Sets the delay between two 'Hold' callbacks activations
             * \param delay Delay required between two 'Hold' callbacks activations
             */
            void setRepeat(Time::TimeUnit delay);
            /**
             * \brief Gets the delay between two 'Hold' callbacks activations
             * \return The delay required between two 'Hold' callbacks activations
             */
            Time::TimeUnit getRepeat() const;
            /**
             * \brief Updates the KeyboardAction
             */
            void update();
        };

        /**
         * \brief Class used to manage KeyClass and KeyboardAction
         */
        class KeyboardManager
        {
        private:
            std::vector<std::unique_ptr<KeyboardAction>> m_allActions;
            std::vector<KeyboardAction*> m_currentActions;
            std::unordered_map<std::string, std::unique_ptr<KeyClass>> m_keys;
            
            bool m_binderEnabled = true;
            Triggers::TriggerGroup::Ptr m_keysTriggers;
        public:
            /**
             * \brief Creates a new KeyboardManager
             */
            KeyboardManager();
            /**
             * \brief Get the KeyboardAction identified by actionId if it exists
             * \param actionId Id of the KeyboardAction to retrieve
             * \return A reference to the KeyboardAction if found
             */
            KeyboardAction& getAction(const std::string& actionId);
            /**
             * \brief Get if a KeyboardAction exists
             * \param actionId Id of the KeyboardAction to check the existance
             * \return true if the KeyboardAction is found in the KeyboardManager, false otherwise
             */
            bool actionExists(const std::string& actionId);
            /**
             * \brief Get a KeyClass that is inside the KeyboardManager
             * \param keyId Id of the KeyClass to retrievez
             * \return A pointer to the KeyClass if found
             */
            KeyClass* getKey(const std::string& keyId);
            /**
             * \brief Clear all contexts the KeyboardManager is using
             */
            void clearContexts();
            /**
             * \brief Adds a new context the KeyboardManager will use
             * \param context Name of the context to add
             * \return A reference to the KeyboardManager (to chain calls)
             */
            KeyboardManager& addContext(const std::string& context);
            /**
             * \brief Cleans all the contexts and adds a new one
             * \param context Name of the only context to use
             */
            void setContext(const std::string& context);
            /**
             * \brief Enables or disables the KeyboardManager
             * \param state true if the KeyboardManager should be enabled, false otherwise
             */
            void setEnabled(bool state);
            /**
             * \brief Configure KeyboardAction from a vili configuration file
             * \param config Reference to the vili ComplexAttribute used to configure the KeyboardManager
             */
            void configure(vili::ComplexAttribute& config);
            /**
             * \brief Updates the KeyboardManager
             */
            void update();
            /**
             * \brief Handles the Triggers of the KeyboardManager
             */
            void handleTriggers();
        };
    }
}
