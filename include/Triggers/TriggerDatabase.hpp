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
            std::map<std::string, std::map<std::string, std::unique_ptr<TriggerGroup>>> m_allTriggers;
            Time::Chronometer m_databaseChrono;
            std::vector<std::unique_ptr<TriggerDelay>> m_delayedTriggers;
            static TriggerDatabase* m_instance;
        public:
            static TriggerDatabase* GetInstance();
            Trigger* getTrigger(const std::string& groupNamespace, const std::string& triggerGroupName, const std::string& triggerName);
            void createNamespace(const std::string& groupNamespace);
            TriggerGroup* createTriggerGroup(const std::string& groupNamespace, const std::string& triggerGroupName);
            TriggerGroup* joinTriggerGroup(const std::string& groupNamespace, const std::string& triggerGroupName);
            std::vector<std::string> getAllTriggersNameFromTriggerGroup(const std::string& groupNamespace, const std::string& triggerGroupName);
            void removeNamespace(const std::string& namespaceId);
            void removeTriggerGroup(TriggerGroup* trgGroup);
            bool doesTriggerGroupExists(const std::string& groupNamespace, const std::string& triggerGroupName);
            void update();
            void clear();
        };
    }
}