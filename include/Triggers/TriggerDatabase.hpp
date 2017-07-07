#pragma once

#include <map>

#include <Time/Chronometer.hpp>
#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe
{
    namespace Triggers
    {
        class TriggerDatabase
        {
        private:
            TriggerDatabase();
            std::map<std::string, std::map<std::string, TriggerGroup*>> m_allTriggers;
            Time::Chronometer m_databaseChrono;
            std::vector<TriggerDelay*> m_delayedTriggers;
            static TriggerDatabase* m_instance;
        public:
            static TriggerDatabase* GetInstance();
            Trigger* getTrigger(std::string groupNamespace, std::string triggerGroupName, std::string triggerName);
            void createNamespace(std::string groupNamespace);
            TriggerGroup* createTriggerGroup(std::string groupNamespace, std::string triggerGroupName);
            TriggerGroup* joinTriggerGroup(std::string groupNamespace, std::string triggerGroupName);
            void removeNamespace(const std::string& namespaceId);
            void removeTriggerGroup(TriggerGroup* trgGroup);
            bool doesTriggerGroupExists(std::string groupNamespace, std::string triggerGroupName);
            std::vector<std::string> getAllTriggersNameFromTriggerGroup(std::string groupNamespace, std::string triggerGroupName);
            void update();
            void clear();
        };
    }
}