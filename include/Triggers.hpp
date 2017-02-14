//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <kaguya/kaguya.hpp>
#include <any/any.hpp>

#include "TimeManager.hpp"
#include "Functions.hpp"

namespace mse
{
	namespace Script
	{
		class Trigger
		{
			private:
				std::string group;
				std::string triggerName;
				std::string triggerNamespace;
				std::map<std::string, std::pair<std::string, Types::any>> triggerParameters;
				bool enabled = false;
				bool toEnable = false;
				bool toDisable = false;
				bool permanent;
				void clearParameters();
				template <typename P>
				void pushParameter(std::string name, P parameter);
				friend class TriggerGroup;
				friend class TriggerDatabase;
			public:
				Trigger(std::string group, std::string triggerName, bool startState = false, bool permanent = false);
				Trigger(std::string nsp, std::string group, std::string triggerName, bool startState = false, bool permanent = false);
				bool getState();
				bool isPermanent();
				std::string getGroup();
				std::string getName();
				std::string getNamespace();
				std::map<std::string, std::pair<std::string, Types::any>>* getParameters();
		};

		class TriggerDelay
		{
			public:
				TriggerDelay(Trigger* trg, int del, bool sta);
				Trigger* trigger;
				int delay;
				bool state;
				int delaytarget;
		};

		class TriggerGroup
		{
			private:
				std::string triggerGroupName;
				std::string fromNsp;
				std::map<std::string, Trigger*> triggerMap;
				std::vector<TriggerDelay*> delayedTriggers;
				friend class TriggerDatabase;

			public:
				TriggerGroup(std::string triggerGroupName);
				TriggerGroup(std::string triggerGroupNamespace, std::string triggerGroupName);
				Trigger* getTrigger(std::string triggerName);
				TriggerGroup* addTrigger(std::string triggerName);
				void delayTriggerState(std::string triggerName, int delay, bool state);
				void enableTrigger(std::string triggerName);
				void disableTrigger(std::string triggerName);
				void setTriggerState(std::string triggerName, bool state);
				bool getState(std::string triggerName);
				void setPermanent(std::string triggerName, bool permanent);
				template <typename P>
				void pushParameter(std::string triggerName, std::string parameterName, P parameter);
				std::vector<std::string> getAllTriggersName();
				std::vector<Trigger*> getAllTriggers();
				std::string getNamespace();
				std::string getName();
		};

		class TriggerDatabase
		{
			private:
				TriggerDatabase();
				std::map<std::string, std::map<std::string, TriggerGroup*>> allTriggers;
				Time::Chronometer databaseChrono;
				std::vector<TriggerDelay*> delayedTriggers;
				static TriggerDatabase* instance;
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
			triggerParameters[name] = std::pair<std::string, Types::any>(datatype, Types::any(parameter));
		}

		template<typename P>
		inline void TriggerGroup::pushParameter(std::string triggerName, std::string parameterName, P parameter)
		{
			getTrigger(triggerName)->pushParameter(parameterName, parameter);
		}
	}
}