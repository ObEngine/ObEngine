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