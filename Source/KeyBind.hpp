//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

#include "DataParser.hpp"
#include "TimeManager.hpp"

class KeyClass
{
	private:
		sf::Keyboard::Key key;
		std::string name;
		std::string returnChar;
		std::string type;
	public:
		KeyClass(sf::Keyboard::Key key, std::string name, std::string returnChar, std::string type);
		sf::Keyboard::Key getKey();
		std::string getType();
		bool isAlpha();
		bool isNumeric();
		bool isNumericNP();
		bool isAlphaNumeric();
		bool isArrow();
		bool isFunction();
		bool isOther();
		bool isWritable();
};

class KeyBinder
{
	private:
		std::map<std::string, std::string> actionMap;
		std::map<std::string, KeyClass*> keyMap;
		std::map<std::string, bool> currentActionMap;
		std::map<std::string, bool> previousActionMap;
		std::map<std::string, int> baseActionDelayer;
		std::map<std::string, unsigned long long int> actionDelayer;
		bool binderEnabled = true;
		std::string getActionKey(std::string action);
		KeyClass* getKey(std::string key);
	public:
		KeyBinder();
		void setEnabled(bool state);
		void loadFromFile(DataParser* configFile);
		void connectAction(std::string action, std::string key);
		bool isActionToggled(std::string action);
		bool isActionReleased(std::string action);
		bool isActionEnabled(std::string action);
		bool isActionDisabled(std::string action);
		void setActionDelay(std::string action, int delay);
		bool isKeyPressed(std::string key);
		void update();
};