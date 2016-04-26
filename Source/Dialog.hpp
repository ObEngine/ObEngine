//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#include "Functions.hpp"
#include "Animation.hpp"

class TextRenderer
{
	private:
		int absoluteX = 0;
		int absoluteY = 0;
		anim::Animation circleAnim;
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