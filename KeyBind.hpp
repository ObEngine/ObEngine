#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

#include "DataParser.hpp"

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
		std::map<std::string, bool> previousActionMap;
		std::map<std::string, int> baseActionDelayer;
		std::map<std::string, int> actionDelayer;
		bool binderEnabled = true;
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
		void update();
};