#include <set>

#include <Input/InputManager.hpp>
#include <Input/KeyList.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Input
{
    bool InputManager::isActionCurrentlyInUse(const std::string& actionId)
    {
        for (const auto& actionPtr : m_currentActions)
        {
            if (const auto& action = actionPtr.lock())
            {
                if (action->getId() == actionId)
                {
                    return true;
                }
            }
        }
        return false;
    }

    InputManager::InputManager()
        : Registrable("InputManager")
        , Togglable(true)
        , m_actionTriggers(
              Triggers::TriggerDatabase::GetInstance().createTriggerGroup("Global", "Actions"),
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
        aube::ErrorHandler::Warn(
            "ObEngine.Input.InputManager.UnknownAction", { { "action", actionId } });
        m_allActions.push_back(std::make_unique<InputAction>(m_actionTriggers.get(), actionId));
        return *m_allActions.back().get();
    }

    void InputManager::update()
    {
        if (m_enabled)
        {
            auto actionBuffer = m_currentActions;
            for (auto actionPtr : actionBuffer)
            {
                if (auto action = actionPtr.lock())
                {
                    Debug::Log->trace("Updating action {}", action->getId());
                    action->update();
                }
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
                    m_allActions.push_back(
                        std::make_unique<InputAction>(m_actionTriggers.get(), action->getId()));
                }
                else if (!Utils::Vector::contains(action->getId(), alreadyInFile))
                {
                    this->getAction(action->getId()).clearConditions();
                }
                auto inputCondition = [](InputManager* inputManager, vili::Node* action,
                                          vili::DataNode* condition) {
                    InputCondition actionCondition;
                    actionCondition.setCombinationCode(condition->get<std::string>());
                    Debug::Log->debug("<InputManager> Associated Key '{0}' for Action '{1}'",
                        condition->get<std::string>(), action->getId());
                    inputManager->getAction(action->getId()).addCondition(actionCondition);
                };
                if (action->getType() == vili::NodeType::DataNode)
                {
                    inputCondition(this, action, static_cast<vili::DataNode*>(action));
                }
                else if (action->getType() == vili::NodeType::ArrayNode)
                {
                    for (vili::DataNode* condition : *static_cast<vili::ArrayNode*>(action))
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
            if (Utils::Vector::contains(context, action->getContexts())
                && !isActionCurrentlyInUse(action->getId()))
            {
                Debug::Log->debug("<InputManager> Add Action '{0}' in Context '{1}'",
                    action.get()->getId(), context);
                m_currentActions.push_back(action);
            }
        }
        return *this;
    }

    InputManager& InputManager::removeContext(const std::string& context)
    {
        //<REVISION> Multiple context, keep which one, remove keys of wrong
        // context
        m_currentActions.erase(
            std::remove_if(m_currentActions.begin(), m_currentActions.end(),
                [&context](const auto& inputAction) -> bool {
                    if (const auto& action = inputAction.lock())
                    {
                        const auto& contexts = action->getContexts();
                        auto isActionInContext
                            = std::find(contexts.begin(), contexts.end(), context)
                            != contexts.end();
                        if (isActionInContext)
                        {
                            Debug::Log->debug("<InputManager> Remove Action '{0}' "
                                              "from Context '{1}'",
                                action->getId(), context);
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return true;
                    }
                }),
            m_currentActions.end());
        return *this;
    }

    void InputManager::setContext(const std::string& context)
    {
        this->clearContexts();
        this->addContext(context);
    }

    std::vector<std::string> InputManager::getContexts()
    {
        std::set<std::string> allContexts;

        for (const auto& actionPtr : m_currentActions)
        {
            if (auto action = actionPtr.lock())
            {
                for (const auto& context : action->getContexts())
                {
                    allContexts.emplace(context);
                }
            }
        }
        return std::vector<std::string>(allContexts.begin(), allContexts.end());
    }
} // namespace obe::Input