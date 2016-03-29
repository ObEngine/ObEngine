//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

#include "Functions.hpp"
#include "Character.hpp"
#include "World.hpp"
#include "Animation.hpp"
#include "Spells.hpp"
#include "Character.hpp"
#include "Cursor.hpp"

class Caster
{
	private:
		int bloodAmount = 100;
		int maxBloodAmount = 100;
		World* worldHook;
		Character* charHook;
		Cursor* cursHook;
		std::map<std::string, double> cooldownTimer;
		std::map<std::string, float> elementMultiplier;
		anim::RessourceManager castRessource;
		DataParser castInfos;
		DataParser spellInfos;
		std::vector<std::string> elemList;
		std::vector<std::string> spellList;
		std::map<std::string, std::vector<std::string>> spellElemList;
		std::string currentElement;
		std::string currentSpell;
		unsigned int elemIndex = 0;
		unsigned int spellIndex = 0;
	public:
		Caster();
		int getBloodAmount();
		int getMaxBloodAmount();
		long int getSpellCooldown(std::string spellName);
		long int getSpellMaxCooldown(std::string spellName);
		void hookToWorld(World* hook);
		void hookToChar(Character* chook);
		void hookToCurs(Cursor* curs);
		void selectSpell(std::string spellName);
		void addBlood(int blood);
		void setBlood(int blood);
		void switchElement(std::string rotation);
		void selectSpell(int slot);
		void switchSpell(std::string rotation);
		void castSpell();
		void resetCooldown(std::string spellName);
		std::string getCurrentElement();
		int getCurrentSpellIndex();
		std::string getCurrentSpell();
		std::vector<std::string> getSpellList(std::string element);
};