#pragma once

#include <memory>

#include <vili/vili/ComplexNode.hpp>

#include <Input/InputAction.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Types/Registrable.hpp>

namespace obe
{
    namespace Input
    {
        /**
        * \brief Class used to manage KeyClass and KeyboardAction
        * @Bind
        */
        class InputManager : public Types::Registrable<InputManager>
        {
        private:
            std::vector<std::unique_ptr<InputAction>> m_allActions;
            std::vector<InputAction*> m_currentActions;
            Triggers::TriggerGroupPtr m_actionTriggers;
            
            bool m_binderEnabled = true;
        public:
            /**
            * \brief Creates a new KeyboardManager
            */
            InputManager();
            /**
            * \brief Get the KeyboardAction identified by actionId if it exists
            * \param actionId Id of the KeyboardAction to retrieve
            * \return A reference to the KeyboardAction if found
            */
            InputAction& getAction(const std::string& actionId);
            /**
            * \brief Get if a KeyboardAction exists
            * \param actionId Id of the KeyboardAction to check the existance
            * \return true if the KeyboardAction is found in the KeyboardManager, false otherwise
            */
            bool actionExists(const std::string& actionId);
            /**
             * \brief Clears all Actions
             */
            void clear();
            /**
            * \brief Clear all contexts the KeyboardManager is using
            */
            void clearContexts();
            /**
            * \brief Adds a new context the KeyboardManager will use
            * \param context Name of the context to add
            * \return A reference to the KeyboardManager (to chain calls)
            */
            InputManager& addContext(const std::string& context);
            /**
             * \brief Removes a context in use
             * \param context Name of the context to remove
             * \return A reference to the InputManager (to chain calls)
             */
            InputManager& removeContext(const std::string& context);
            /**
            * \brief Cleans all the contexts and adds a new one
            * \param context Name of the only context to use
            */
            void setContext(const std::string& context);
            /**
             * \brief Gets all the contexts currently used by the InputManager
             * \return A std::vector of std::string containing all the contexts used by the InputManager
             */
            std::vector<std::string> getContexts();
            /**
            * \brief Enables or disables the KeyboardManager
            * \param state true if the KeyboardManager should be enabled, false otherwise
            */
            void setEnabled(bool state);
            /**
            * \brief Configure KeyboardAction from a vili configuration file
            * \param config Reference to the vili ComplexAttribute used to configure the KeyboardManager
            */
            void configure(vili::ComplexNode& config);
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
