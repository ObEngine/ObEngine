//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <clip/clip.h>
#include <vili/Vili.hpp>

#include "World.hpp"
#include "Cursor.hpp"
#include "KeyBind.hpp"
#include "GUI.hpp"
#include "Dialog.hpp"
#include "Particle.hpp"
#include "Console.hpp"
#include "MathExp.hpp"
#include "Script.hpp"
#include "TimeManager.hpp"
#include "Dialog.hpp"
#include "Light.hpp"
#include "GameObject.hpp"
#include "EditorGrid.hpp"
#include "Network.hpp"
#include "MapEditorTools.hpp"
#include "FramerateManager.hpp"

namespace obe
{
	namespace Editor
	{
		void editMap(std::string mapName);
	}
}