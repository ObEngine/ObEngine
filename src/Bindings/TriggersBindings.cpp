#include <Bindings/TriggersBindings.hpp>
#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace TriggersBindings
        {
            void LoadTrigger(kaguya::State* lua)
            {
                (*lua)["Core"]["Triggers"]["Trigger"].setClass(kaguya::UserdataMetatable<Triggers::Trigger>()
                    .addFunction("clear", &Triggers::Trigger::clear)
                    .addFunction("execute", &Triggers::Trigger::execute)
                    .addFunction("getGroup", &Triggers::Trigger::getGroup)
                    .addFunction("getName", &Triggers::Trigger::getName)
                    .addFunction("getNamespace", &Triggers::Trigger::getNamespace)
                    .addFunction("getState", &Triggers::Trigger::getState)
                    .addFunction("prepareNewCall", &Triggers::Trigger::prepareNewCall)
                    .addFunction("registerState", &Triggers::Trigger::registerState)
                );
            }
            void LoadTriggerDatabase(kaguya::State* lua)
            {
                (*lua)["Core"]["Triggers"]["TriggerDatabase"].setClass(kaguya::UserdataMetatable<Triggers::TriggerDatabase>()
                    .addStaticFunction("GetInstance", &Triggers::TriggerDatabase::GetInstance)
                    .addFunction("clear", &Triggers::TriggerDatabase::clear)
                    .addFunction("createNamespace", &Triggers::TriggerDatabase::createNamespace)
                    .addFunction("createTriggerGroup", &Triggers::TriggerDatabase::createTriggerGroup)
                    .addFunction("doesTriggerGroupExists", &Triggers::TriggerDatabase::doesTriggerGroupExists)
                    .addFunction("getAllTriggersNameFromTriggerGroup", &Triggers::TriggerDatabase::getAllTriggersNameFromTriggerGroup)
                    .addFunction("getTrigger", &Triggers::TriggerDatabase::getTrigger)
                    .addFunction("joinTriggerGroup", &Triggers::TriggerDatabase::joinTriggerGroup)
                    .addFunction("removeNamespace", &Triggers::TriggerDatabase::removeNamespace)
                    .addFunction("removeTriggerGroup", &Triggers::TriggerDatabase::removeTriggerGroup)
                    .addFunction("update", &Triggers::TriggerDatabase::update)
                );
            }
            void LoadTriggerDelay(kaguya::State* lua)
            {
                (*lua)["Core"]["Triggers"]["TriggerDelay"].setClass(kaguya::UserdataMetatable<Triggers::TriggerDelay>()
                );
            }
            void LoadTriggerGroup(kaguya::State* lua)
            {
                (*lua)["Core"]["Triggers"]["TriggerGroup"].setClass(kaguya::UserdataMetatable<Triggers::TriggerGroup>()
                    .addFunction("addTrigger", &Triggers::TriggerGroup::addTrigger)
                    .addFunction("delayTriggerState", &Triggers::TriggerGroup::delayTriggerState)
                    .addFunction("getAllTriggers", &Triggers::TriggerGroup::getAllTriggers)
                    .addFunction("getAllTriggersName", &Triggers::TriggerGroup::getAllTriggersName)
                    .addFunction("getName", &Triggers::TriggerGroup::getName)
                    .addFunction("getNamespace", &Triggers::TriggerGroup::getNamespace)
                    .addFunction("getState", &Triggers::TriggerGroup::getState)
                    .addFunction("getTrigger", &Triggers::TriggerGroup::getTrigger)
                    .addFunction("isJoinable", &Triggers::TriggerGroup::isJoinable)
                    .addOverloadedFunctions("pushParameter",
                        &Triggers::TriggerGroup::pushParameter<int>,
                        &Triggers::TriggerGroup::pushParameter<std::string>,
                        &Triggers::TriggerGroup::pushParameter<double>,
                        &Triggers::TriggerGroup::pushParameter<bool>,
                        &Triggers::TriggerGroup::pushParameter<std::vector<int>>,
                        &Triggers::TriggerGroup::pushParameter<std::vector<std::string>>,
                        &Triggers::TriggerGroup::pushParameter<std::vector<double>>,
                        &Triggers::TriggerGroup::pushParameter<std::vector<bool>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<int, int>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<int, std::string>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<int, double>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<int, bool>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<std::string, int>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<std::string, std::string>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<std::string, double>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<std::string, bool>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<double, int>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<double, std::string>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<double, double>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<double, bool>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<bool, int>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<bool, std::string>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<bool, double>>,
                        &Triggers::TriggerGroup::pushParameter<std::map<bool, bool>>
                    )
                    .addFunction("setJoinable", &Triggers::TriggerGroup::setJoinable)
                    .addFunction("setPermanent", &Triggers::TriggerGroup::setPermanent)
                    .addFunction("trigger", &Triggers::TriggerGroup::trigger)
                );
            }
        }
    }
}