//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <string>
#include <iostream>
#include <kaguya/kaguya.hpp>
#include <any/any.hpp>
#include <vili/Vili.hpp>

#include "Collisions.hpp"
#include "Console.hpp"
#include "Cursor.hpp"
#include "Dialog.hpp"
#include "GUI.hpp"
#include "KeyBind.hpp"
#include "LevelSprite.hpp"
#include "Light.hpp"
#include "MathExp.hpp"
#include "Particle.hpp"
#include "Triggers.hpp"

namespace mse
{
	namespace Script
	{
		void loadLib(kaguya::State* lua, std::string lib);
		void loadHook(kaguya::State* lua, std::string hookname);
		void loadCoreLib(kaguya::State* lua, std::vector<std::string> lib);
		void registerLib(kaguya::State* lua, std::string lib);
		void loadBaseLib(kaguya::State* lua);

		namespace CoreLib
		{
			void loadAnimation(kaguya::State* lua, std::vector<std::string> args);
			void loadCollision(kaguya::State* lua, std::vector<std::string> args);
			void loadConsole(kaguya::State* lua, std::vector<std::string> args);
			void loadConstants(kaguya::State* lua, std::vector<std::string> args);
			void loadCursor(kaguya::State* lua, std::vector<std::string> args);
			void loadDialog(kaguya::State* lua, std::vector<std::string> args);
			void loadGUI(kaguya::State* lua, std::vector<std::string> args);
			void loadKeyBind(kaguya::State* lua, std::vector<std::string> args);
			void loadLevelSprite(kaguya::State* lua, std::vector<std::string> args);
			void loadLight(kaguya::State* lua, std::vector<std::string> args);
			void loadMathExp(kaguya::State* lua, std::vector<std::string> args);
			void loadParticle(kaguya::State* lua, std::vector<std::string> args);
			void loadSFML(kaguya::State* lua, std::vector<std::string> args);
			void loadSTD(kaguya::State* lua, std::vector<std::string> args);
			void loadTrigger(kaguya::State* lua, std::vector<std::string> args);
			void loadUtils(kaguya::State* lua, std::vector<std::string> args);
			void loadVili(kaguya::State* lua, std::vector<std::string> args);
		}

		class CoreHook
		{
		private:
			std::map<std::string, std::pair<std::string, Types::any*>> containerMap;
		public:
			template <typename T>
			void dropValue(std::string name, T val);
			void getValue(kaguya::State* lua, std::string name);
			Types::any* getPointer(std::string name);
		};

		template <typename T>
		inline void CoreHook::dropValue(std::string name, T val)
		{
			containerMap[name] = std::pair<std::string, Types::any*>(Functions::Type::getObjectType(val), new Types::any(val));
		}

		extern CoreHook hookCore;
	}
}