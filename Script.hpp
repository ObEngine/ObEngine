#pragma once

#include <string>
#include <iostream>
#include <Any/any.hpp>
#include <kaguya/kaguya.hpp>

#include "Console.hpp"
#include "Dialog.hpp"
#include "Triggers.hpp"
#include "Light.hpp"
#include "MathExp.hpp"
#include "World.hpp"

void funtest(); //To Remove

void loadLib(kaguya::State* lua, std::string lib);
void loadCoreLib(kaguya::State* lua, std::vector<std::string> lib);
void registerLib(kaguya::State* lua, std::string lib);

namespace CoreLib
{
	void loadConsole(kaguya::State* lua, std::vector<std::string> args);
	void loadDialog(kaguya::State* lua, std::vector<std::string> args);
	void loadLight(kaguya::State* lua, std::vector<std::string> args);
	void loadMathExp(kaguya::State* lua, std::vector<std::string> args);
	void loadTrigger(kaguya::State* lua, std::vector<std::string> args);
	void loadUtils(kaguya::State* lua, std::vector<std::string> args);
	void loadWorld(kaguya::State* lua, std::vector<std::string> args);
}

class CoreHook
{
	private:
		std::map<std::string, std::pair<std::string, emorph::any*>> containerMap;
	public:
		template <typename T>
		void dropValue(std::string name, T val);
		void getValue(kaguya::State* lua, std::string name);
		emorph::any* getPointer(std::string name);
};

template <typename T>
inline void CoreHook::dropValue(std::string name, T val)
{
	std::string datatype = fn::Vector::join(fn::String::split(typeid(val).name(), " "), "", 1);
	containerMap[name] = std::pair<std::string, emorph::any*>(datatype, new emorph::any(val));
}

extern CoreHook hookCore;