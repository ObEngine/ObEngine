#include <Triggers/TriggerDatabase.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe
{
    namespace Triggers
    {
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
            m_triggerMap[triggerName] = new Trigger(*this, triggerName);
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

        unsigned int TriggerGroup::Ptr::amount = 0;
		TriggerGroup::Ptr::Ptr(TriggerGroup* link)
		{
            if (link != nullptr)
            {
                m_link = link;
                m_link->m_references++;
                m_id = amount++;
            }
		}

        TriggerGroup::Ptr& TriggerGroup::Ptr::operator=(const Ptr& link)
        {
            if (link.m_link != nullptr)
            {
                m_link = link.m_link;
                m_link->m_references++;
                m_id = amount++;
            }
            return *this;
        }

        TriggerGroup::Ptr::~Ptr()
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
		TriggerGroup* TriggerGroup::Ptr::operator->() const
		{
			return m_link;
		}
    }
}