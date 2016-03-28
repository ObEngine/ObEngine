#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#include "Functions.hpp"

class TextRenderer
{
	private:
		int absoluteX = 0;
		int absoluteY = 0;
		std::vector<std::vector<std::string>> textList;
		sf::Texture dialogLine;
		sf::Sprite dialogLineSpr;
		sf::Texture arrowTex;
		sf::Sprite arrowSpr;
		sf::Font dialogFont;
		sf::Text speakerText;
		sf::Text dialogText;
		sf::RenderTexture renTex;
		sf::Texture renGetTex;
		sf::Sprite dispSpr;
		bool needToRender = true;

	public:
		TextRenderer();
		void setPos(int x, int y);
		void appendText(std::string speaker, std::string text);
		bool textRemaining();
		void next();
		void render(sf::RenderWindow* surf);
};