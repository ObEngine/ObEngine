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
            std::string m_triggerGroupName;
            std::string m_fromNsp;
            std::map<std::string, Trigger*> m_triggerMap;
            std::vector<TriggerDelay*> m_delayedTriggers;
			unsigned int m_references = 0;
            friend class TriggerDatabase;
        public:
            TriggerGroup(std::string triggerGroupName);
            TriggerGroup(std::string triggerGroupNamespace, std::string triggerGroupName);
            Trigger* getTrigger(std::string triggerName);
            TriggerGroup* addTrigger(std::string triggerName);
            TriggerGroup* delayTriggerState(std::string triggerName, int delay, bool state);
            TriggerGroup* enableTrigger(std::string triggerName);
            TriggerGroup* disableTrigger(std::string triggerName);
            TriggerGroup* setTriggerState(std::string triggerName, bool state);
            bool getState(std::string triggerName);
            TriggerGroup* setPermanent(std::string triggerName, bool permanent);
            template <typename P>
            void pushParameter(std::string triggerName, std::string parameterName, P parameter);
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
        void TriggerGroup::pushParameter(std::string triggerName, std::string parameterName, P parameter)
        {
            getTrigger(triggerName)->pushParameter(parameterName, parameter);
        }
    }
}