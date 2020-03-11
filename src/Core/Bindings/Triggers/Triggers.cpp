#include <Bindings/Triggers/Triggers.hpp>

#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerDelay.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Triggers/TriggerManager.hpp>

#include <sol/sol.hpp>

namespace obe::Triggers::Bindings
{
    void LoadClassTrigger(sol::state_view state)
    {
        sol::table TriggersNamespace = state["obe"]["Triggers"].get<sol::table>();
        sol::usertype<obe::Triggers::Trigger> bindTrigger
            = TriggersNamespace.new_usertype<obe::Triggers::Trigger>("Trigger",
                sol::call_constructor,
                sol::constructors<obe::Triggers::Trigger(
                                      obe::Triggers::TriggerGroup*, const std::string&),
                    obe::Triggers::Trigger(
                        obe::Triggers::TriggerGroup*, const std::string&, bool)>());
        bindTrigger["getState"] = &obe::Triggers::Trigger::getState;
        bindTrigger["getGroup"] = &obe::Triggers::Trigger::getGroup;
        bindTrigger["getName"] = &obe::Triggers::Trigger::getName;
        bindTrigger["getNamespace"] = &obe::Triggers::Trigger::getNamespace;
        bindTrigger["registerEnvironment"] = &obe::Triggers::Trigger::registerEnvironment;
        bindTrigger["unregisterEnvironment"]
            = &obe::Triggers::Trigger::unregisterEnvironment;
        bindTrigger["execute"] = &obe::Triggers::Trigger::execute;
        bindTrigger["onRegister"] = &obe::Triggers::Trigger::onRegister;
        bindTrigger["onUnregister"] = &obe::Triggers::Trigger::onUnregister;
    }
    void LoadClassTriggerDelay(sol::state_view state)
    {
        sol::table TriggersNamespace = state["obe"]["Triggers"].get<sol::table>();
        sol::usertype<obe::Triggers::TriggerDelay> bindTriggerDelay
            = TriggersNamespace.new_usertype<obe::Triggers::TriggerDelay>("TriggerDelay",
                sol::call_constructor,
                sol::constructors<obe::Triggers::TriggerDelay(
                    obe::Triggers::Trigger&, obe::Time::TimeUnit)>());
        bindTriggerDelay["m_trigger"] = sol::property(
            [](obe::Triggers::TriggerDelay* self) { return self->m_trigger; });
        bindTriggerDelay["m_delay"]
            = sol::readonly(&obe::Triggers::TriggerDelay::m_delay);
        bindTriggerDelay["m_delayTarget"]
            = sol::readonly(&obe::Triggers::TriggerDelay::m_delayTarget);
    }
    void LoadClassTriggerEnv(sol::state_view state)
    {
        sol::table TriggersNamespace = state["obe"]["Triggers"].get<sol::table>();
        sol::usertype<obe::Triggers::TriggerEnv> bindTriggerEnv
            = TriggersNamespace.new_usertype<obe::Triggers::TriggerEnv>("TriggerEnv",
                sol::call_constructor,
                sol::constructors<obe::Triggers::TriggerEnv(
                    unsigned int, std::string, bool*)>());
        bindTriggerEnv["envIndex"] = sol::readonly(&obe::Triggers::TriggerEnv::envIndex);
        bindTriggerEnv["callbackName"]
            = sol::readonly(&obe::Triggers::TriggerEnv::callbackName);
        bindTriggerEnv["envActive"]
            = sol::readonly(&obe::Triggers::TriggerEnv::envActive);
    }
    void LoadClassTriggerGroup(sol::state_view state)
    {
        sol::table TriggersNamespace = state["obe"]["Triggers"].get<sol::table>();
        sol::usertype<obe::Triggers::TriggerGroup> bindTriggerGroup
            = TriggersNamespace.new_usertype<obe::Triggers::TriggerGroup>("TriggerGroup",
                sol::call_constructor,
                sol::constructors<obe::Triggers::TriggerGroup(
                    const std::string&, const std::string&)>());
        bindTriggerGroup["setJoinable"] = &obe::Triggers::TriggerGroup::setJoinable;
        bindTriggerGroup["isJoinable"] = &obe::Triggers::TriggerGroup::isJoinable;
        bindTriggerGroup["getTrigger"] = &obe::Triggers::TriggerGroup::getTrigger;
        bindTriggerGroup["addTrigger"] = &obe::Triggers::TriggerGroup::addTrigger;
        bindTriggerGroup["removeTrigger"] = &obe::Triggers::TriggerGroup::removeTrigger;
        bindTriggerGroup["delayTriggerState"]
            = &obe::Triggers::TriggerGroup::delayTriggerState;
        bindTriggerGroup["trigger"] = &obe::Triggers::TriggerGroup::trigger;
        bindTriggerGroup["pushParameterFromLua"]
            = &obe::Triggers::TriggerGroup::pushParameterFromLua;
        bindTriggerGroup["getAllTriggersName"]
            = &obe::Triggers::TriggerGroup::getAllTriggersName;
        bindTriggerGroup["getAllTriggers"] = &obe::Triggers::TriggerGroup::getAllTriggers;
        bindTriggerGroup["getNamespace"] = &obe::Triggers::TriggerGroup::getNamespace;
        bindTriggerGroup["getName"] = &obe::Triggers::TriggerGroup::getName;
    }
    void LoadClassTriggerManager(sol::state_view state)
    {
        sol::table TriggersNamespace = state["obe"]["Triggers"].get<sol::table>();
        sol::usertype<obe::Triggers::TriggerManager> bindTriggerManager
            = TriggersNamespace.new_usertype<obe::Triggers::TriggerManager>(
                "TriggerManager", sol::call_constructor,
                sol::constructors<obe::Triggers::TriggerManager()>());
        bindTriggerManager["getTrigger"] = &obe::Triggers::TriggerManager::getTrigger;
        bindTriggerManager["getAllTriggersNameFromTriggerGroup"]
            = &obe::Triggers::TriggerManager::getAllTriggersNameFromTriggerGroup;
        bindTriggerManager["createNamespace"]
            = &obe::Triggers::TriggerManager::createNamespace;
        bindTriggerManager["createTriggerGroup"]
            = &obe::Triggers::TriggerManager::createTriggerGroup;
        bindTriggerManager["joinTriggerGroup"]
            = &obe::Triggers::TriggerManager::joinTriggerGroup;
        bindTriggerManager["getAllTriggersGroupNames"]
            = &obe::Triggers::TriggerManager::getAllTriggersGroupNames;
        bindTriggerManager["removeNamespace"]
            = &obe::Triggers::TriggerManager::removeNamespace;
        bindTriggerManager["removeTriggerGroup"]
            = &obe::Triggers::TriggerManager::removeTriggerGroup;
        bindTriggerManager["doesTriggerGroupExists"]
            = &obe::Triggers::TriggerManager::doesTriggerGroupExists;
        bindTriggerManager["update"] = &obe::Triggers::TriggerManager::update;
        bindTriggerManager["clear"] = &obe::Triggers::TriggerManager::clear;
    }
};