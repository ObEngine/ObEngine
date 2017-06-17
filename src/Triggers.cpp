//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Triggers.hpp"

namespace obe
{
    namespace Script
    {
        //Trigger
        Trigger::Trigger(std::string group, std::string triggerName, bool startState, bool permanent)
        {
            m_triggerNamespace = "";
            m_group = group;
            m_triggerName = triggerName;
            m_permanent = permanent;
            m_enabled = startState;
            m_triggerParameters = std::map<std::string, std::pair<std::string, Types::any>>();
        }

        Trigger::Trigger(std::string nsp, std::string group, std::string triggerName, bool startState, bool permanent)
        {
            m_triggerNamespace = nsp;
            m_group = group;
            m_triggerName = triggerName;
            m_permanent = permanent;
            m_enabled = startState;
            m_triggerParameters = std::map<std::string, std::pair<std::string, Types::any>>();
        }

        bool Trigger::getState() const
        {
            return m_enabled;
        }

        bool Trigger::isPermanent() const
        {
            return m_permanent;
        }

        std::string Trigger::getGroup() const
        {
            return m_group;
        }

        std::string Trigger::getName() const
        {
            return m_triggerName;
        }

        std::string Trigger::getNamespace() const
        {
            return m_triggerNamespace;
        }

        std::map<std::string, std::pair<std::string, Types::any>>* Trigger::getParameters()
        {
            return &m_triggerParameters;
        }

        void Trigger::clearParameters()
        {
            m_triggerParameters.clear();
        }


        //TriggerDelay
        TriggerDelay::TriggerDelay(Trigger* trg, int del, bool sta)
        {
            m_trigger = trg;
            m_delay = del;
            m_state = sta;
        }

        //TriggerGroup
        TriggerGroup::TriggerGroup(std::string triggerGroupName)
        {
            m_fromNsp = "";
            m_triggerGroupName = triggerGroupName;
        }

        TriggerGroup::TriggerGroup(std::string triggerGroupNamespace, std::string triggerGroupName)
        {
            m_fromNsp = triggerGroupNamespace;
            m_triggerGroupName = triggerGroupName;
        }

        Trigger* TriggerGroup::getTrigger(std::string triggerName)
        {
            if (m_triggerMap.find(triggerName) != m_triggerMap.end())
            {
                return m_triggerMap[triggerName];
            }
            throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerGroup.UnknownTrigger", {{"trigger", triggerName}, {"group", m_triggerGroupName}});
        }

        TriggerGroup* TriggerGroup::addTrigger(std::string triggerName)
        {
            m_triggerMap[triggerName] = new Trigger(m_fromNsp, m_triggerGroupName, triggerName);
            return this;
        }

        TriggerGroup* TriggerGroup::delayTriggerState(std::string triggerName, int delay, bool state)
        {
            m_delayedTriggers.push_back(new TriggerDelay(getTrigger(triggerName), delay, state));
            return this;
        }

        TriggerGroup* TriggerGroup::enableTrigger(std::string triggerName)
        {
            this->getTrigger(triggerName)->m_toEnable = true;
            if (this->getTrigger(triggerName)->m_toDisable) this->getTrigger(triggerName)->m_toDisable = false;
            return this;
        }

        TriggerGroup* TriggerGroup::disableTrigger(std::string triggerName)
        {
            this->getTrigger(triggerName)->m_toDisable = true;
            if (this->getTrigger(triggerName)->m_toEnable) this->getTrigger(triggerName)->m_toEnable = false;
            return this;
        }

        TriggerGroup* TriggerGroup::setTriggerState(std::string triggerName, bool state)
        {
            if (state) this->enableTrigger(triggerName);
            else this->disableTrigger(triggerName);
            return this;
        }

        bool TriggerGroup::getState(std::string triggerName)
        {
            return this->getTrigger(triggerName)->getState();
        }

        TriggerGroup* TriggerGroup::setPermanent(std::string triggerName, bool permanent)
        {
            this->getTrigger(triggerName)->m_permanent = permanent;
            return this;
        }

        std::vector<std::string> TriggerGroup::getAllTriggersName()
        {
            std::vector<std::string> returnVec;
            for (auto it = m_triggerMap.begin(); it != m_triggerMap.end(); ++it)
            {
                returnVec.push_back(it->first);
            }
            return returnVec;
        }

        std::vector<Trigger*> TriggerGroup::getAllTriggers()
        {
            std::vector<Trigger*> returnVec;
            for (auto it = m_triggerMap.begin(); it != m_triggerMap.end(); ++it)
            {
                returnVec.push_back(it->second);
            }
            return returnVec;
        }

        std::string TriggerGroup::getNamespace() const
        {
            return m_fromNsp;
        }

        std::string TriggerGroup::getName() const
        {
            return m_triggerGroupName;
        }

        TriggerDatabase* TriggerDatabase::m_instance = nullptr;

        //TriggerDatabase
        TriggerDatabase::TriggerDatabase()
        {
            this->createNamespace("Global");
            m_databaseChrono.start();
        }

        TriggerDatabase* TriggerDatabase::GetInstance()
        {
            if (!m_instance)
                m_instance = new TriggerDatabase();
            return m_instance;
        }

        Trigger* TriggerDatabase::getTrigger(std::string groupNamespace, std::string triggerGroupName, std::string triggerName)
        {
            if (m_allTriggers.find(groupNamespace) != m_allTriggers.end())
            {
                if (m_allTriggers[groupNamespace].find(triggerGroupName) != m_allTriggers[groupNamespace].end())
                    return m_allTriggers[groupNamespace][triggerGroupName]->getTrigger(triggerName);
                throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerDatabase.UnknownCustomTriggerGroup", {
                                                    {"function", "getTrigger"},
                                                    {"group", triggerGroupName},
                                                    {"nsp", groupNamespace}
                                                });
            }
            throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerDatabase.UnknownNamespace", {{"function", "getTrigger"}, {"nsp", groupNamespace}});
        }

        void TriggerDatabase::createNamespace(std::string groupNamespace)
        {
            if (m_allTriggers.size() == 0)
                m_allTriggers[groupNamespace] = std::map<std::string, TriggerGroup*>();
            else
            {
                if (m_allTriggers.find(groupNamespace) == m_allTriggers.end())
                    m_allTriggers[groupNamespace] = std::map<std::string, TriggerGroup*>();
                else
                    throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerDatabase.NamespaceAlreadyExists", {{"nsp", groupNamespace}});
            }
        }

        TriggerGroup* TriggerDatabase::createTriggerGroup(std::string groupNamespace, std::string triggerGroupName)
        {
            if (m_allTriggers.find(groupNamespace) != m_allTriggers.end())
            {
                if (m_allTriggers[groupNamespace].find(triggerGroupName) == m_allTriggers[groupNamespace].end())
                {
                    m_allTriggers[groupNamespace][triggerGroupName] = new TriggerGroup(groupNamespace, triggerGroupName);
                    return m_allTriggers[groupNamespace][triggerGroupName];
                }
                throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerDatabase.TriggerGroupAlreadyExists", {{"group", triggerGroupName}, {"nsp", groupNamespace}});
            }
            throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerDatabase.UnknownNamespace", {{"function", "createTriggerGroup"},{"nsp", groupNamespace}});
        }

        TriggerGroup* TriggerDatabase::joinTriggerGroup(std::string groupNamespace, std::string triggerGroupName)
        {
            std::cout << "Trying to join TriggerGroup : " << triggerGroupName << " inside : " << groupNamespace << std::endl;
            if (m_allTriggers.find(groupNamespace) != m_allTriggers.end())
            {
                if (m_allTriggers[groupNamespace].find(triggerGroupName) != m_allTriggers[groupNamespace].end())
                    return m_allTriggers[groupNamespace][triggerGroupName];
                throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerDatabase.UnknownCustomTriggerGroup", {
                                                    {"function", "joinTriggerGroup"},
                                                    {"group", triggerGroupName},
                                                    {"nsp", groupNamespace}
                                                });
            }
            throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerDatabase.UnknownNamespace", {{"function", "joinTriggerGroup"},{"nsp", groupNamespace}});
        }

        void TriggerDatabase::removeNamespace(const std::string& namespaceId)
        {
            if (m_allTriggers.find(namespaceId) != m_allTriggers.end())
                m_allTriggers.erase(m_allTriggers.find(namespaceId));
            else
                throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerDatabase.UnknownNamespace", { {"function", "removeNamespace"}, {"nsp", namespaceId} });
        }

        void TriggerDatabase::removeTriggerGroup(TriggerGroup* trgGroup)
        {
            m_allTriggers[trgGroup->getNamespace()].erase(trgGroup->getName());
            delete trgGroup;
        }

        bool TriggerDatabase::doesTriggerGroupExists(std::string groupNamespace, std::string triggerGroupName)
        {
            if (m_allTriggers[groupNamespace].find(triggerGroupName) == m_allTriggers[groupNamespace].end())
                return false;
            return true;
        }

        std::vector<std::string> TriggerDatabase::getAllTriggersNameFromTriggerGroup(std::string groupNamespace, std::string triggerGroupName)
        {
            if (m_allTriggers.find(groupNamespace) != m_allTriggers.end())
            {
                if (m_allTriggers[groupNamespace].find(triggerGroupName) != m_allTriggers[groupNamespace].end())
                    return m_allTriggers[groupNamespace][triggerGroupName]->getAllTriggersName();
                throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerDatabase.UnknownCustomTriggerGroup", {
                                                    {"function", "getAllTriggersNameFromTriggerGroup"},
                                                    {"group", triggerGroupName},
                                                    {"nsp", groupNamespace}
                                                });
            }
            throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerDatabase.UnknownNamespace", {
                                                {"function", "getAllTriggersNameFromTriggerGroup"},
                                                {"nsp", groupNamespace}
                                            });
        }

        void TriggerDatabase::update()
        {
            for (auto it = m_allTriggers.begin(); it != m_allTriggers.end(); ++it)
            {
                for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                {
                    if (it2->second->m_delayedTriggers.size() != 0)
                    {
                        for (int i = 0; i < it2->second->m_delayedTriggers.size(); i++)
                        {
                            it2->second->m_delayedTriggers[i]->m_delaytarget = m_databaseChrono.getTime() + it2->second->m_delayedTriggers[i]->m_delay;
                            m_delayedTriggers.push_back(it2->second->m_delayedTriggers[i]);
                        }
                        it2->second->m_delayedTriggers.clear();
                    }
                    std::vector<Trigger*> trgList = it2->second->getAllTriggers();
                    for (int i = 0; i < trgList.size(); i++)
                    {
                        if (!trgList[i]->isPermanent()) trgList[i]->m_enabled = false;
                        if (trgList[i]->m_toDisable)
                        {
                            trgList[i]->m_enabled = false;
                            trgList[i]->m_toDisable = false;
                        }
                        if (trgList[i]->m_toEnable)
                        {
                            trgList[i]->m_enabled = true;
                            trgList[i]->m_toEnable = false;
                        }
                    }
                }
            }
            std::vector<int> triggeredDelayedTriggers;
            for (int i = 0; i < m_delayedTriggers.size(); i++)
            {
                if (m_delayedTriggers[i]->m_delaytarget <= m_databaseChrono.getTime())
                {
                    if (m_delayedTriggers[i]->m_state) m_delayedTriggers[i]->m_trigger->m_toEnable = true;
                    else m_delayedTriggers[i]->m_trigger->m_toDisable = true;
                    delete(m_delayedTriggers[i]);
                    triggeredDelayedTriggers.push_back(i);
                }
            }
            for (int i = 0; i < triggeredDelayedTriggers.size(); i++)
            {
                m_delayedTriggers.erase(m_delayedTriggers.begin() + triggeredDelayedTriggers[i]);
            }
        }

        void TriggerDatabase::clear()
        {
            m_delayedTriggers.clear();
            m_databaseChrono.stop();
            m_allTriggers.clear();
            m_databaseChrono.start();
            //Need to delete Map-only stuff !!
        }
    }
}
