#include <Input/InputManager.hpp>
#include <Input/KeyList.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Input
{
    InputManager::InputManager()
        : Registrable("InputManager"),
          m_actionTriggers(
              Triggers::TriggerDatabase::GetInstance()->createTriggerGroup(
                  "Global", "Actions"),
              Triggers::TriggerGroupPtrRemover)
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
        aube::ErrorHandler::Warn("ObEngine.Input.InputManager.UnknownAction",
                                 {{"action", actionId}});
        m_allActions.push_back(
            std::make_unique<InputAction>(m_actionTriggers.get(), actionId));
        return *m_allActions.back().get();
    }

    void InputManager::setEnabled(const bool state)
    {
        m_binderEnabled = state;
    }

    void InputManager::update()
    {
        if (m_binderEnabled)
        {
            const unsigned int actionsAmount = m_currentActions.size();
            for (unsigned int i = 0; i < actionsAmount; i++)
            {
                if (i <
                    m_currentActions.size()) // Performance issue ? <REVISION>
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

    void InputManager::configure(vili::ComplexNode& config)
    {
        std::vector<std::string> alreadyInFile;
        for (vili::ComplexNode* context : config.getAll<vili::ComplexNode>())
        {
            for (vili::Node* action : context->getAll())
            {
                if (!this->actionExists(action->getId()))
                {
                    m_allActions.push_back(std::make_unique<InputAction>(
                        m_actionTriggers.get(), action->getId()));
                }
                else if (!Utils::Vector::contains(action->getId(),
                                                  alreadyInFile))
                {
                    this->getAction(action->getId()).clearConditions();
                }
                auto inputCondition = [](InputManager* inputManager,
                                         vili::Node* action,
                                         vili::DataNode* condition) {
                    InputCondition actionCondition;
                    actionCondition.setCombinationCode(
                        condition->get<std::string>());
                    Debug::Log->debug(
                        "<InputManager> Associated Key '{0}' for Action '{1}'",
                        condition->get<std::string>(), action->getId());
                    inputManager->getAction(action->getId())
                        .addCondition(actionCondition);
                };
                if (action->getType() == vili::NodeType::DataNode)
                {
                    inputCondition(this, action,
                                   static_cast<vili::DataNode*>(action));
                }
                else if (action->getType() == vili::NodeType::ArrayNode)
                {
                    for (vili::DataNode* condition :
                         *static_cast<vili::ArrayNode*>(action))
                    {
                        inputCondition(this, action, condition);
                    }
                }
                this->getAction(action->getId()).addContext(context->getId());
                alreadyInFile.push_back(action->getId());
            }
        }
        // Add Context keys in real time <REVISION>
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
            if (Utils::Vector::contains(context, action->getContexts()) &&
                !Utils::Vector::contains(action.get(), m_currentActions))
            {
                Debug::Log->debug(
                    "<InputManager> Add Action '{0}' in Context '{1}'",
                    action.get()->getId(), context);
                m_currentActions.push_back(action.get());
            }
        }
        return *this;
    }

    InputManager& InputManager::removeContext(const std::string& context)
    {
        //<REVISION> Multiple context, keep which one, remove keys of wrong
        //context
        m_allActions.erase(
            std::remove_if(
                m_allActions.begin(), m_allActions.end(),
                [&context](std::unique_ptr<InputAction>& inputAction) -> bool {
                    return (inputAction->getId() == context);
                }),
            m_allActions.end());

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
                if (!Utils::Vector::contains(context, allContexts))
                {
                    allContexts.push_back(context);
                }
            }
        }
        return allContexts;
    }
} // namespace obe::Input