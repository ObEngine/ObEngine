#include <Triggers/TriggerDatabase.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe
{
    namespace Triggers
    {
        TriggerGroup::TriggerGroup(const std::string& triggerGroupNamespace, const std::string& triggerGroupName)
        {
            m_fromNsp = triggerGroupNamespace;
            m_name = triggerGroupName;
        }

        Trigger* TriggerGroup::getTrigger(const std::string& triggerName)
        {
            if (m_triggerMap.find(triggerName) != m_triggerMap.end())
            {
                return m_triggerMap[triggerName].get();
            }
            throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerGroup.UnknownTrigger", {{"trigger", triggerName}, {"group", m_name}});
        }

        std::vector<std::string> TriggerDatabase::getAllTriggersNameFromTriggerGroup(const std::string& groupNamespace, const std::string& triggerGroupName)
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

        TriggerGroup* TriggerGroup::addTrigger(const std::string& triggerName)
        {
            m_triggerMap[triggerName] = std::make_unique<Trigger>(this, triggerName);
            m_triggerMap[triggerName]->clear();
            return this;
        }

        TriggerGroup* TriggerGroup::delayTriggerState(const std::string& triggerName, Time::TimeUnit delay)
        {
            m_delayedTriggers.push_back(std::make_unique<TriggerDelay>(getTrigger(triggerName), delay));
            return this;
        }

        TriggerGroup* TriggerGroup::trigger(const std::string& triggerName)
        {
            if (triggerName == "Init")
                std::cout << "INIT BEING TRIGGERED" << std::endl;
            this->getTrigger(triggerName)->m_enabled = true;
            this->getTrigger(triggerName)->prepareNewCall();
            return this;
        }

        bool TriggerGroup::getState(const std::string& triggerName)
        {
            return this->getTrigger(triggerName)->getState();
        }

        TriggerGroup* TriggerGroup::setPermanent(const std::string& triggerName, bool permanent)
        {
            this->getTrigger(triggerName)->m_permanent = permanent;
            return this;
        }

        void TriggerGroup::setJoinable(bool joinable)
        {
            m_joinable = joinable;
        }

        bool TriggerGroup::isJoinable() const
        {
            return m_joinable;
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
                returnVec.push_back(it->second.get());
            }
            return returnVec;
        }

        std::string TriggerGroup::getNamespace() const
        {
            return m_fromNsp;
        }

        std::string TriggerGroup::getName() const
        {
            return m_name;
        }

        unsigned int TriggerGroupPtr::amount = 0;

        TriggerGroupPtr::TriggerGroupPtr(TriggerGroup* link)
        {
            if (link != nullptr)
            {
                m_link = link;
                m_link->m_references++;
                m_id = amount++;
            }
        }

        TriggerGroupPtr& TriggerGroupPtr::operator=(const TriggerGroupPtr& link)
        {
            if (link.m_link != nullptr)
            {
                m_link = link.m_link;
                m_link->m_references++;
                m_id = amount++;
            }
            return *this;
        }

        TriggerGroupPtr::~TriggerGroupPtr()
        {
            if (m_link != nullptr)
            {
                m_link->m_references--;
                if (m_link->m_references == 0)
                {
                    TriggerDatabase::GetInstance()->removeTriggerGroup(m_link);
                }
            }
        }

        TriggerGroup* TriggerGroupPtr::operator->() const
        {
            return m_link;
        }
    }
}
