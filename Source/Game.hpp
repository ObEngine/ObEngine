//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Character.hpp"
#include "World.hpp"
#include "DataParser.hpp"
#include "Cursor.hpp"
#include "KeyBind.hpp"
#include "GUI.hpp"
#include "Console.hpp"
#include "TimeManager.hpp"

namespace mse
{
	namespace Modes
	{
		void startGame(std::string mapName);
	}
}