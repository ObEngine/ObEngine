#pragma once

#include <Triggers/TriggerDelay.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe
{
    namespace Triggers
    {
        class TriggerGroup
        {
        private:
            std::string m_name;
            std::string m_fromNsp;
            std::map<std::string, std::unique_ptr<Trigger>> m_triggerMap;
            std::vector<std::unique_ptr<TriggerDelay>> m_delayedTriggers;
            bool m_joinable = false;
			unsigned int m_references = 0;
            friend class TriggerDatabase;
        public:
            TriggerGroup(const std::string& triggerGroupName);
            TriggerGroup(const std::string& triggerGroupNamespace, const std::string& triggerGroupName);
            void setJoinable(bool joinable);
            bool isJoinable() const;
            Trigger* getTrigger(const std::string& triggerName);
            TriggerGroup* addTrigger(const std::string& triggerName);
            TriggerGroup* delayTriggerState(const std::string& triggerName, int delay, bool state);
            TriggerGroup* enableTrigger(const std::string& triggerName);
            TriggerGroup* disableTrigger(const std::string& triggerName);
            TriggerGroup* setTriggerState(const std::string& triggerName, bool state);
            bool getState(const std::string& triggerName);
            TriggerGroup* setPermanent(const std::string& triggerName, bool permanent);
            template <typename P>
            void pushParameter(const std::string& triggerName, const std::string& parameterName, P parameter);
            std::vector<std::string> getAllTriggersName();
            std::vector<Trigger*> getAllTriggers();
            std::string getNamespace() const;
            std::string getName() const;
			class Ptr
			{
				private:
					TriggerGroup* m_link = nullptr;
                    static unsigned int amount;
                    unsigned int m_id = 0;
					friend class TriggerDatabase;
				public:
					Ptr(TriggerGroup* link);
                    Ptr& operator=(const Ptr& link);
					TriggerGroup* operator->() const;
					~Ptr();
			};
			friend class TriggerGroup::Ptr;
        };

        template <typename P>
        void TriggerGroup::pushParameter(const std::string& triggerName, const std::string& parameterName, P parameter)
        {
            getTrigger(triggerName)->pushParameter(parameterName, parameter);
        }
    }
}