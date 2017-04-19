//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <kaguya/kaguya.hpp>
#include <any/any.hpp>
#include <aube/ErrorHandler.hpp>

#include "TimeManager.hpp"
#include "Functions.hpp"

namespace obe
{
	namespace Script
	{
		class Trigger
		{
			private:
				std::string m_group;
				std::string m_triggerName;
				std::string m_triggerNamespace;
				std::map<std::string, std::pair<std::string, Types::any>> m_triggerParameters;
				bool m_enabled = false;
				bool m_toEnable = false;
				bool m_toDisable = false;
				bool m_permanent;
				void clearParameters();
				template <typename P>
				void pushParameter(std::string name, P parameter);
				friend class TriggerGroup;
				friend class TriggerDatabase;
			public:
				Trigger(std::string group, std::string triggerName, bool startState = false, bool permanent = false);
				Trigger(std::string nsp, std::string group, std::string triggerName, bool startState = false, bool permanent = false);
				bool getState() const;
				bool isPermanent() const;
				std::string getGroup() const;
				std::string getName() const;
				std::string getNamespace() const;
				std::map<std::string, std::pair<std::string, Types::any>>* getParameters();
		};

		class TriggerDelay
		{
			public:
				TriggerDelay(Trigger* trg, int del, bool sta);
				Trigger* m_trigger;
				int m_delay = 0;
				bool m_state = false;
				int m_delaytarget = 0;
		};

		class TriggerGroup
		{
			private:
				std::string m_triggerGroupName;
				std::string m_fromNsp;
				std::map<std::string, Trigger*> m_triggerMap;
				std::vector<TriggerDelay*> m_delayedTriggers;
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
		};

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
				void removeTriggerGroup(TriggerGroup* trgGroup);
				bool doesTriggerGroupExists(std::string groupNamespace, std::string triggerGroupName);
				std::vector<std::string> getAllTriggersNameFromTriggerGroup(std::string groupNamespace, std::string triggerGroupName);
				void update();
				void clear();
		};

		template<typename P>
		inline void Trigger::pushParameter(std::string name, P parameter)
		{
			std::vector<std::string> splittedTypeName = Functions::String::split(typeid(parameter).name(), " ");
			std::string datatype = Functions::Vector::join(splittedTypeName, "", 1);
			m_triggerParameters[name] = std::pair<std::string, Types::any>(datatype, Types::any(parameter));
		}

		template<typename P>
		inline void TriggerGroup::pushParameter(std::string triggerName, std::string parameterName, P parameter)
		{
			getTrigger(triggerName)->pushParameter(parameterName, parameter);
		}
	}
}