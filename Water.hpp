//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <ctime>

#include "Functions.hpp"

//FICHIER EN COURS DE DEBUG

class WaterBox
{
	private:
		int waveAmount;
		int waveDistort;
		int waveSpeed;
		int x;
		int y;
		int width;
		int height;
		sf::Texture waterTexture;
		sf::Sprite waterSprite;
		sf::Shader waterShader;
	public:
};