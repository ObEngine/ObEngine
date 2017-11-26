#include <Input/InputManager.hpp>
#include <Input/KeyList.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Input
    {
        InputManager::InputManager() : 
        m_actionTriggers(Triggers::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Actions"), Triggers::TriggerGroupPtrRemover)
        {
        }

        InputAction& InputManager::getAction(const std::string& actionId)
        {
            for (auto& action : m_allActions)
            {
                if (action->getId() == actionId)
                {
                    return *action.get();
                }
            }
            aube::ErrorHandler::Warn("ObEngine.Input.InputManager.UnknownAction", { { "action", actionId } });
            m_allActions.push_back(std::make_unique<InputAction>(m_actionTriggers.get(), actionId));
            return *m_allActions.back().get();
        }

        void InputManager::setEnabled(bool state)
        {
            m_binderEnabled = state;
        }

        void InputManager::update()
        {
            if (m_binderEnabled)
            {
                Monitors::UpdateMonitors();
                unsigned int actionsAmount = m_currentActions.size();
                for (unsigned int i = 0; i < actionsAmount; i++)
                {
                    if (i < m_currentActions.size()) // Performance issue ? <REVISION>
                        m_currentActions[i]->update();
                }
            }
        }

        bool InputManager::actionExists(const std::string& actionId)
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

        void InputManager::clear()
        {
            m_currentActions.clear();
            for (auto& action : m_allActions)
                m_actionTriggers->removeTrigger(action->getId());
            m_allActions.clear();
        }

        void InputManager::handleTriggers()
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

        void InputManager::configure(vili::ComplexNode& config)
        {
            std::vector<std::string> alreadyInFile;
            for (vili::ComplexNode* context : config.getAll<vili::ComplexNode>())
            {
                for (vili::DataNode* action : context->getAll<vili::DataNode>())
                {
                    if (!this->actionExists(action->getId()))
                    {
                        m_allActions.push_back(std::make_unique<InputAction>(m_actionTriggers.get(), action->getId()));
                    }
                    else if (!Utils::Vector::isInList(action->getId(), alreadyInFile))
                    {
                        this->getAction(action->getId()).clearConditions();
                    }
                    InputCondition actionCondition;
                    actionCondition.setCombinationCode(action->get<std::string>());
                    Debug::Log->debug("<InputManager> Associated Key '{0}' for Action '{1}'", action->get<std::string>(), action->getId());
                    this->getAction(action->getId()).addCondition(actionCondition);
                    this->getAction(action->getId()).addContext(context->getId());
                    alreadyInFile.push_back(action->getId());
                }
            }
            //Add Context keys in real time <REVISION>
        }

        void InputManager::clearContexts()
        {
            m_currentActions.clear();
        }

        InputManager& InputManager::addContext(const std::string& context)
        {
            Debug::Log->debug("<InputManager> Adding Context '{0}'", context);
            for (auto& action : m_allActions)
            {
                if (Utils::Vector::isInList(context, action->getContexts()) && !Utils::Vector::isInList(action.get(), m_currentActions))
                {
                    Debug::Log->debug("<InputManager> Add Action '{0}' in Context '{1}'", action.get()->getId(), context);
                    m_currentActions.push_back(action.get());
                }
            }
            return *this;
        }

        InputManager& InputManager::removeContext(const std::string& context)
        {
            //<REVISION> Multiple context, keep which one, remove keys of wrong context
            m_allActions.erase(
                std::remove_if(m_allActions.begin(), m_allActions.end(), 
                [&context](std::unique_ptr<InputAction>& inputAction) -> bool
            {
                return (inputAction->getId() == context);
            }), m_allActions.end());

            return *this;
        }

        void InputManager::setContext(const std::string& context)
        {
            this->clearContexts();
            this->addContext(context);
        }

        std::vector<std::string> InputManager::getContexts()
        {
            std::vector<std::string> allContexts;
            for (const InputAction* action : m_currentActions)
            {
                for (const std::string& context : action->getContexts())
                {
                    if (!Utils::Vector::isInList(context, allContexts))
                    {
                        allContexts.push_back(context);
                    }
                }
            }
            return allContexts;
        }
    }
}
