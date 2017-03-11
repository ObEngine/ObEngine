//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "KeyBind.hpp"

namespace obe
{
	namespace Input
	{
		KeyClass::KeyClass(sf::Keyboard::Key key, std::string name, std::string returnChar, std::string type)
		{
			this->key = key;
			this->name = name;
			this->returnChar = returnChar;
			this->type = type;
		}

		sf::Keyboard::Key KeyClass::getKey()
		{
			return this->key;
		}

		std::string KeyBinder::getActionKey(std::string action)
		{
			if (actionMap.find(action) != actionMap.end())
				return actionMap[action];
			else
				std::cout << "<Error:KeyBind:KeyBinder>[getActionKey] : Can't find key for action : " << action << std::endl;
		}

		KeyClass* KeyBinder::getKey(std::string key)
		{
			if (keyMap.find(key) != keyMap.end())
				return keyMap[key];
			else
				std::cout << "<Error:KeyBind:KeyBinder>[getKey] : Can't find KeyClass for key : " << key << std::endl;
		}

		KeyBinder::KeyBinder()
		{
			keysTriggers = Script::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Keys")
				->addTrigger("ActionReleased")
				->addTrigger("ActionPressed")
				->addTrigger("ActionToggled");

			//Alpha
			keyMap["A"] = new KeyClass(sf::Keyboard::A, "A", "A", "Alpha");
			keyMap["Z"] = new KeyClass(sf::Keyboard::Z, "Z", "Z", "Alpha");
			keyMap["E"] = new KeyClass(sf::Keyboard::E, "E", "E", "Alpha");
			keyMap["R"] = new KeyClass(sf::Keyboard::R, "R", "E", "Alpha");
			keyMap["T"] = new KeyClass(sf::Keyboard::T, "T", "T", "Alpha");
			keyMap["Y"] = new KeyClass(sf::Keyboard::Y, "Y", "Y", "Alpha");
			keyMap["U"] = new KeyClass(sf::Keyboard::U, "U", "U", "Alpha");
			keyMap["I"] = new KeyClass(sf::Keyboard::I, "I", "I", "Alpha");
			keyMap["O"] = new KeyClass(sf::Keyboard::O, "O", "O", "Alpha");
			keyMap["P"] = new KeyClass(sf::Keyboard::P, "P", "P", "Alpha");
			keyMap["Q"] = new KeyClass(sf::Keyboard::Q, "Q", "Q", "Alpha");
			keyMap["S"] = new KeyClass(sf::Keyboard::S, "S", "S", "Alpha");
			keyMap["D"] = new KeyClass(sf::Keyboard::D, "D", "D", "Alpha");
			keyMap["F"] = new KeyClass(sf::Keyboard::F, "F", "F", "Alpha");
			keyMap["G"] = new KeyClass(sf::Keyboard::G, "G", "G", "Alpha");
			keyMap["H"] = new KeyClass(sf::Keyboard::H, "H", "H", "Alpha");
			keyMap["J"] = new KeyClass(sf::Keyboard::J, "J", "J", "Alpha");
			keyMap["K"] = new KeyClass(sf::Keyboard::K, "K", "K", "Alpha");
			keyMap["L"] = new KeyClass(sf::Keyboard::L, "L", "L", "Alpha");
			keyMap["M"] = new KeyClass(sf::Keyboard::M, "M", "M", "Alpha");
			keyMap["W"] = new KeyClass(sf::Keyboard::W, "W", "W", "Alpha");
			keyMap["X"] = new KeyClass(sf::Keyboard::X, "X", "W", "Alpha");
			keyMap["C"] = new KeyClass(sf::Keyboard::C, "C", "C", "Alpha");
			keyMap["V"] = new KeyClass(sf::Keyboard::V, "V", "V", "Alpha");
			keyMap["B"] = new KeyClass(sf::Keyboard::B, "B", "B", "Alpha");
			keyMap["N"] = new KeyClass(sf::Keyboard::N, "N", "N", "Alpha");
			//Numeric
			keyMap["0"] = new KeyClass(sf::Keyboard::Num0, "0", "0", "Numeric");
			keyMap["1"] = new KeyClass(sf::Keyboard::Num1, "1", "1", "Numeric");
			keyMap["2"] = new KeyClass(sf::Keyboard::Num2, "2", "2", "Numeric");
			keyMap["3"] = new KeyClass(sf::Keyboard::Num3, "3", "3", "Numeric");
			keyMap["4"] = new KeyClass(sf::Keyboard::Num4, "4", "4", "Numeric");
			keyMap["5"] = new KeyClass(sf::Keyboard::Num5, "5", "5", "Numeric");
			keyMap["6"] = new KeyClass(sf::Keyboard::Num6, "6", "6", "Numeric");
			keyMap["7"] = new KeyClass(sf::Keyboard::Num7, "7", "7", "Numeric");
			keyMap["8"] = new KeyClass(sf::Keyboard::Num8, "8", "8", "Numeric");
			keyMap["9"] = new KeyClass(sf::Keyboard::Num9, "9", "9", "Numeric");
			//Numpad
			keyMap["NumPad0"] = new KeyClass(sf::Keyboard::Numpad0, "NumPad0", "0", "NumericNP");
			keyMap["NumPad1"] = new KeyClass(sf::Keyboard::Numpad1, "NumPad1", "1", "NumericNP");
			keyMap["NumPad2"] = new KeyClass(sf::Keyboard::Numpad2, "NumPad2", "2", "NumericNP");
			keyMap["NumPad3"] = new KeyClass(sf::Keyboard::Numpad3, "NumPad3", "3", "NumericNP");
			keyMap["NumPad4"] = new KeyClass(sf::Keyboard::Numpad4, "NumPad4", "4", "NumericNP");
			keyMap["NumPad5"] = new KeyClass(sf::Keyboard::Numpad5, "NumPad5", "5", "NumericNP");
			keyMap["NumPad6"] = new KeyClass(sf::Keyboard::Numpad6, "NumPad6", "6", "NumericNP");
			keyMap["NumPad7"] = new KeyClass(sf::Keyboard::Numpad7, "NumPad7", "7", "NumericNP");
			keyMap["NumPad8"] = new KeyClass(sf::Keyboard::Numpad8, "NumPad8", "8", "NumericNP");
			keyMap["NumPad9"] = new KeyClass(sf::Keyboard::Numpad9, "NumPad9", "9", "NumericNP");
			//Arrows
			keyMap["Left"] = new KeyClass(sf::Keyboard::Left, "Left", "", "Arrows");
			keyMap["Right"] = new KeyClass(sf::Keyboard::Right, "Right", "", "Arrows");
			keyMap["Up"] = new KeyClass(sf::Keyboard::Up, "Up", "", "Arrows");
			keyMap["Down"] = new KeyClass(sf::Keyboard::Down, "Down", "", "Arrows");
			//Functions
			keyMap["F1"] = new KeyClass(sf::Keyboard::F1, "F1", "", "Functions");
			keyMap["F2"] = new KeyClass(sf::Keyboard::F2, "F2", "", "Functions");
			keyMap["F3"] = new KeyClass(sf::Keyboard::F3, "F3", "", "Functions");
			keyMap["F4"] = new KeyClass(sf::Keyboard::F4, "F4", "", "Functions");
			keyMap["F5"] = new KeyClass(sf::Keyboard::F5, "F5", "", "Functions");
			keyMap["F6"] = new KeyClass(sf::Keyboard::F6, "F6", "", "Functions");
			keyMap["F7"] = new KeyClass(sf::Keyboard::F7, "F7", "", "Functions");
			keyMap["F8"] = new KeyClass(sf::Keyboard::F8, "F8", "", "Functions");
			keyMap["F9"] = new KeyClass(sf::Keyboard::F9, "F9", "", "Functions");
			keyMap["F10"] = new KeyClass(sf::Keyboard::F10, "F10", "", "Functions");
			keyMap["F11"] = new KeyClass(sf::Keyboard::F11, "F11", "", "Functions");
			keyMap["F12"] = new KeyClass(sf::Keyboard::F12, "F12", "", "Functions");
			//Others
			keyMap["Add"] = new KeyClass(sf::Keyboard::Add, "Add", "+", "Others");
			keyMap["BackSlash"] = new KeyClass(sf::Keyboard::BackSlash, "BackSlash", "\\", "Others");
			keyMap["BackSpace"] = new KeyClass(sf::Keyboard::BackSpace, "BackSpace", "", "Others");
			keyMap["Comma"] = new KeyClass(sf::Keyboard::Comma, "Comma", ",", "Others");
			keyMap["Dash"] = new KeyClass(sf::Keyboard::Dash, "Dash", "-", "Others");
			keyMap["Delete"] = new KeyClass(sf::Keyboard::Delete, "Delete", "", "Others");
			keyMap["Divide"] = new KeyClass(sf::Keyboard::Divide, "Divide", "/", "Others");
			keyMap["End"] = new KeyClass(sf::Keyboard::End, "End", "", "Others");
			keyMap["Equal"] = new KeyClass(sf::Keyboard::Equal, "Equal", "=", "Others");
			keyMap["Escape"] = new KeyClass(sf::Keyboard::Escape, "Escape", "", "Others");
			keyMap["Home"] = new KeyClass(sf::Keyboard::Home, "Home", "", "Others");
			keyMap["Insert"] = new KeyClass(sf::Keyboard::Insert, "Insert", "", "Others");
			keyMap["LAlt"] = new KeyClass(sf::Keyboard::LAlt, "LAlt", "", "Others");
			keyMap["LBracket"] = new KeyClass(sf::Keyboard::LBracket, "LBracket", "[", "Others");
			keyMap["LControl"] = new KeyClass(sf::Keyboard::LControl, "LControl", "", "Others");
			keyMap["LShift"] = new KeyClass(sf::Keyboard::LShift, "LShift", "", "Others");
			keyMap["Menu"] = new KeyClass(sf::Keyboard::Menu, "Menu", "", "Others");
			keyMap["Multiply"] = new KeyClass(sf::Keyboard::Multiply, "Multiply", "*", "Others");
			keyMap["PageDown"] = new KeyClass(sf::Keyboard::PageDown, "PageDown", "", "Others");
			keyMap["PageUp"] = new KeyClass(sf::Keyboard::PageUp, "PageUp", "", "Others");
			keyMap["Pause"] = new KeyClass(sf::Keyboard::Pause, "Pause", "", "Others");
			keyMap["Period"] = new KeyClass(sf::Keyboard::Period, "Period", ".", "Others");
			keyMap["Quote"] = new KeyClass(sf::Keyboard::Quote, "Quote", "\"", "Others");
			keyMap["RAlt"] = new KeyClass(sf::Keyboard::RAlt, "RAlt", "", "Others");
			keyMap["RBracket"] = new KeyClass(sf::Keyboard::RBracket, "RBracket", "]", "Others");
			keyMap["RControl"] = new KeyClass(sf::Keyboard::RControl, "RControl", "", "Others");
			keyMap["Return"] = new KeyClass(sf::Keyboard::Return, "Return", "", "Others");
			keyMap["RShift"] = new KeyClass(sf::Keyboard::RShift, "RShift", "", "Others");
			keyMap["RSystem"] = new KeyClass(sf::Keyboard::RSystem, "RSystem", "", "Others");
			keyMap["SemiColon"] = new KeyClass(sf::Keyboard::SemiColon, "SemiColor", ";", "Others");
			keyMap["Slash"] = new KeyClass(sf::Keyboard::Slash, "Slash", "/", "Others");
			keyMap["Space"] = new KeyClass(sf::Keyboard::Space, "Space", " ", "Others");
			keyMap["Substract"] = new KeyClass(sf::Keyboard::Subtract, "Substract", "-", "Others");
			keyMap["Tab"] = new KeyClass(sf::Keyboard::Tab, "Tab", "    ", "Others");
			keyMap["Tilde"] = new KeyClass(sf::Keyboard::Tilde, "Tilde", "~", "Others");
		}

		void KeyBinder::setEnabled(bool state)
		{
			binderEnabled = state;
		}

		void KeyBinder::update()
		{
			if (binderEnabled) {
				typedef std::map<std::string, std::string>::iterator it_type;
				for (it_type iterator = actionMap.begin(); iterator != actionMap.end(); iterator++) {
					previousActionMap[iterator->first] = currentActionMap[iterator->first];
					currentActionMap[iterator->first] = sf::Keyboard::isKeyPressed(getKey(iterator->second)->getKey());
					if (!currentActionMap[iterator->first] && previousActionMap[iterator->first]) {
						if (Functions::Map::keyInMap(iterator->first, actionDelayer)) {
							actionDelayer[iterator->first] = 0;
						}
					}
				}
			}
		}

		void KeyBinder::handleTriggers()
		{
			if (binderEnabled)
			{
				typedef std::map<std::string, std::string>::iterator it_type;
				std::vector<std::string> toggledActions;
				std::vector<std::string> releasedActions;
				std::vector<std::string> pressedActions;
				for (it_type iterator = actionMap.begin(); iterator != actionMap.end(); iterator++)
				{
					if (isActionToggled(iterator->first)) {
						if (isActionPressed(iterator->first))
							pressedActions.push_back(iterator->first);
						if (isActionReleased(iterator->first))
							releasedActions.push_back(iterator->first);
						toggledActions.push_back(iterator->first); 
					}
					
				}

				if (releasedActions.size() >= 1) {
					keysTriggers->pushParameter("ActionReleased", "ReleasedActions", releasedActions);
					keysTriggers->enableTrigger("ActionReleased");
				}
				if (pressedActions.size() >= 1) {
					keysTriggers->pushParameter("ActionPressed", "PressedActions", pressedActions);
					keysTriggers->enableTrigger("ActionPressed");
				}
				if (toggledActions.size() >= 1) {
					keysTriggers->pushParameter("ActionToggled", "ToggledActions", toggledActions);
					keysTriggers->enableTrigger("ActionToggled");
				}
			}
		}

		bool KeyBinder::isActionReleased(std::string action)
		{
			if (binderEnabled && !currentActionMap[action] && previousActionMap[action]) {
				return true;
			}
			return false;
		}

		bool KeyBinder::isActionEnabled(std::string action)
		{
			if (binderEnabled && currentActionMap[action]) {
				if (Functions::Map::keyInMap(action, actionDelayer)) {
					if (Time::getTickSinceEpoch() - actionDelayer[action] > baseActionDelayer[action]) {
						actionDelayer[action] = Time::getTickSinceEpoch();
						return true;
					}
				}
				else
					return true;
			}
			return false;
		}

		bool KeyBinder::isActionDisabled(std::string action)
		{
			if (binderEnabled) {
				if (currentActionMap[action])
					return false;
				else
					return true;
			}
			else
				return true;
		}

		void KeyBinder::setActionDelay(std::string action, int delay)
		{
			baseActionDelayer[action] = delay;
			actionDelayer[action] = 0;
		}

		bool KeyBinder::isKeyPressed(std::string key)
		{
			return sf::Keyboard::isKeyPressed(getKey(key)->getKey());;
		}

		void KeyBinder::connectAction(std::string action, std::string key) {
			actionMap[action] = key;
		}

		bool KeyBinder::isActionToggled(std::string action)
		{
			if (binderEnabled) {
				if (currentActionMap[action] != previousActionMap[action])
					return true;
				else
					return false;
			}
			else
				return false;
		}

		bool KeyBinder::isActionPressed(std::string action)
		{
			if (binderEnabled) {
				if (currentActionMap[action] && !previousActionMap[action])
					return true;
				else
					return false;
			}
			else
				return false;
		}

		void KeyBinder::loadFromFile(vili::DataParser* configFile)
		{
			std::vector<std::string> allGameKeys = configFile->at("KeyBinding", "game")->getAll(vili::Types::BaseAttribute);
			for (unsigned int i = 0; i < allGameKeys.size(); i++)
				actionMap[allGameKeys[i]] = configFile->at("KeyBinding", "game")->getBaseAttribute(allGameKeys[i])->get<std::string>();
			std::vector<std::string> allMapEditorKeys = configFile->at("KeyBinding", "mapEditor")->getAll(vili::Types::BaseAttribute);
			for (unsigned int i = 0; i < allMapEditorKeys.size(); i++)
				actionMap[allMapEditorKeys[i]] = configFile->at("KeyBinding", "mapEditor")->getBaseAttribute(allMapEditorKeys[i])->get<std::string>();
		}
	}
}