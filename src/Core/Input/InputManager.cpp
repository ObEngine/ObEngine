#include <set>

#include <Input/Exceptions.hpp>
#include <Input/InputManager.hpp>
#include <Triggers/TriggerManager.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Input
{
    bool updateOrCleanMonitor(Triggers::TriggerGroupPtr triggers,
        const std::weak_ptr<InputButtonMonitor>& element)
    {
        if (auto monitor = element.lock())
        {
            monitor->update(triggers);
            return false;
        }
        else
        {
            return true;
        }
    }

    bool InputManager::isActionCurrentlyInUse(const std::string& actionId)
    {
        for (const auto& action : m_currentActions)
        {
            if (action->getId() == actionId)
            {
                return true;
            }
        }
        return false;
    }

    InputManager::InputManager()
        : Togglable(true)
    {
    }

    void InputManager::init(Triggers::TriggerManager& triggers)
    {
        t_actions = triggers.createTriggerGroup("Event", "Actions");
        this->createInputMap();
        this->createTriggerGroups(triggers);
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
        std::vector<std::string> actionIds;
        actionIds.reserve(m_allActions.size());
        for (auto& action : m_allActions)
        {
            actionIds.push_back(action->getId());
        }
        throw Exceptions::UnknownInputAction(actionId, actionIds, EXC_INFO);
    }

    void InputManager::update()
    {
        if (m_enabled)
        {
            auto actionBuffer = m_currentActions;
            for (auto action : actionBuffer)
            {

                action->update();
            }
            if (m_refresh)
            {
                bool noRefresh = true;
                for (auto& [_, input] : m_inputs)
                {

                    if (input->isPressed())
                    {

                        noRefresh = false;
                        break;
                    }
                }
                for (const auto& monitorPtr : m_monitors)
                {
                    if (const auto& monitor = monitorPtr.lock())
                    {
                        if (monitor->getButton().isPressed())
                        {
                            noRefresh = false;
                            break;
                        }
                    }
                }
                m_refresh = !noRefresh;
                m_monitors.erase(
                    std::remove_if(m_monitors.begin(), m_monitors.end(),
                        [this](const std::weak_ptr<InputButtonMonitor>& element) {
                            return updateOrCleanMonitor(t_inputs, element);
                        }),
                    m_monitors.end());
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
            t_actions->remove(action->getId());
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
                        std::make_unique<InputAction>(t_actions.get(), action->getId()));
                }
                else if (!Utils::Vector::contains(action->getId(), alreadyInFile))
                {
                    this->getAction(action->getId()).clearConditions();
                }
                auto inputCondition = [this](InputManager* inputManager,
                                          vili::Node* action, vili::DataNode* condition) {
                    InputCondition actionCondition;
                    const InputCombination combination
                        = this->makeCombination(condition->get<std::string>());
                    actionCondition.setCombination(combination);
                    Debug::Log->debug(
                        "<InputManager> Associated Key '{0}' for Action '{1}'",
                        condition->get<std::string>(), action->getId());
                    inputManager->getAction(action->getId())
                        .addCondition(actionCondition);
                };
                if (action->getType() == vili::NodeType::DataNode)
                {
                    inputCondition(this, action, static_cast<vili::DataNode*>(action));
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
        for (InputAction* action : m_currentActions)
        {
            action->disable();
        }
        m_currentActions.clear();
        // m_monitors.clear();
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
                    action->getId(), context);
                m_currentActions.push_back(action.get());
                std::vector<InputButtonMonitorPtr> monitors;
                for (InputButton* button : action->getInvolvedButtons())
                {
                    monitors.push_back(this->monitor(*button));
                }
                action->enable(monitors);
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
                [&context](auto& action) -> bool {
                    const auto& contexts = action->getContexts();
                    auto isActionInContext
                        = std::find(contexts.begin(), contexts.end(), context)
                        != contexts.end();
                    if (isActionInContext)
                    {
                        Debug::Log->debug("<InputManager> Remove Action '{0}' "
                                          "from Context '{1}'",
                            action->getId(), context);
                        action->disable();
                        return true;
                    }
                    else
                    {
                        return false;
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

        for (const auto& action : m_currentActions)
        {
            for (const auto& context : action->getContexts())
            {
                allContexts.emplace(context);
            }
        }
        return std::vector<std::string>(allContexts.begin(), allContexts.end());
    }

    InputButton& InputManager::getInput(const std::string& keyId)
    {
        if (m_inputs.find(keyId) != m_inputs.end())
            return *m_inputs[keyId].get();
        std::vector<std::string> buttonsNames;
        buttonsNames.reserve(m_inputs.size());
        for (const auto& button : m_inputs)
        {
            buttonsNames.push_back(button.second->getName());
        }
        throw Exceptions::UnknownInputButton(keyId, buttonsNames, EXC_INFO);
    }

    std::vector<InputButton*> InputManager::getInputs()
    {
        std::vector<InputButton*> inputs;
        inputs.reserve(m_inputs.size());
        for (auto& [_, input] : m_inputs)
        {
            inputs.push_back(input.get());
        }
        return inputs;
    }

    std::vector<InputButton*> InputManager::getInputs(InputType filter)
    {
        std::vector<InputButton*> inputs;
        for (auto& keyIterator : m_inputs)
        {
            if (keyIterator.second->is(filter))
            {
                inputs.push_back(keyIterator.second.get());
            }
        }
        return inputs;
    }

    std::vector<InputButton*> InputManager::getPressedInputs()
    {
        std::vector<InputButton*> allPressedButtons;
        for (auto& keyIterator : m_inputs)
        {
            if (keyIterator.second->isPressed())
            {
                allPressedButtons.push_back(keyIterator.second.get());
            }
        }
        return allPressedButtons;
    }

    InputButtonMonitorPtr InputManager::monitor(const std::string& name)
    {
        return this->monitor(this->getInput(name));
    }

    InputButtonMonitorPtr InputManager::monitor(InputButton& input)
    {
        for (auto& monitor : m_monitors)
        {
            if (const auto sharedMonitor = monitor.lock())
            {
                if (&sharedMonitor->getButton() == &input)
                    return InputButtonMonitorPtr(sharedMonitor);
            }
        }
        InputButtonMonitorPtr monitor = std::make_shared<InputButtonMonitor>(input);
        m_monitors.push_back(monitor);
        return std::move(monitor);
    }

    void InputManager::requireRefresh()
    {
        m_refresh = true;
    }

    bool isKeyAlreadyInCombination(InputCombination& combination, InputButton* button)
    {
        for (auto& [monitoredButton, _] : combination)
        {
            if (monitoredButton == button)
            {
                return true;
            }
        }
        return false;
    }
    InputCombination InputManager::makeCombination(const std::string& code)
    {
        InputCombination combination;
        std::vector<std::string> elements = Utils::String::split(code, "+");
        if (code != "NotAssociated")
        {
            for (std::string element : elements)
            {
                Utils::String::replaceInPlace(element, " ", "");
                std::vector<std::string> stateAndButton
                    = Utils::String::split(element, ":");
                if (stateAndButton.size() == 1 || stateAndButton.size() == 2)
                {
                    if (stateAndButton.size() == 1)
                    {
                        stateAndButton.push_back(stateAndButton[0]);
                        stateAndButton[0] = "Pressed";
                    }

                    std::vector<std::string> stateList
                        = Utils::String::split(stateAndButton[0], ",");
                    Types::FlagSet<InputButtonState> buttonStates;
                    for (std::string& buttonState : stateList)
                    {
                        if (Utils::Vector::contains(
                                buttonState, { "Idle", "Hold", "Pressed", "Released" }))
                        {
                            buttonStates |= stringToInputButtonState(buttonState);
                        }
                        else
                        {
                            throw aube::ErrorHandler::Raise(
                                "ObEngine.Input.InputCondition."
                                "UnknownState",
                                { { "state", buttonState } });
                        }
                    }
                    const std::string keyId = stateAndButton[1];
                    if (m_inputs.find(keyId) != m_inputs.end())
                    {
                        InputButton& button = this->getInput(keyId);

                        if (!isKeyAlreadyInCombination(combination, &button))
                        {
                            combination.emplace_back(&button, buttonStates);
                        }
                        else
                        {
                            throw aube::ErrorHandler::Raise(
                                "ObEngine.Input.InputCondition."
                                "ButtonAlreadyInCombination",
                                { { "button", button.getName() } });
                        }
                    }
                    else
                    {
                        Debug::Log->warn("<InputCondition> Button not "
                                         "found : '{0}' in code '{1}'",
                            keyId, code);
                    }
                }
            }
        }
        return combination;
    }
} // namespace obe::Input