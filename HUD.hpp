//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#include "Caster.hpp"
#include "Functions.hpp"
#include "SpriteFunc.hpp"

class intBar
{
	private:
		int barPercent = 0;
		double oldPercent = 0;
		sf::Texture barTexture;
		sf::Sprite barSprite;
	public:
		intBar(std::string barFilename);
		void setPercent(int percent);
		void addPercent(int percent);
		void draw(sf::RenderWindow* surf, int x, int y, int w, double dt);
};

class HUDOverlay
{
	private:
		intBar* lifeBar;
		intBar* manaBar;
		sf::Font font;
		sf::Text textCD;
		std::map<std::string, sf::Texture*> elemTexture;
		std::map<std::string, sf::Sprite*> elemMap;
		sf::Texture casterOverlay;
		sf::Sprite casterOverlaySpr;
		Caster* castHook;
		Entity* entityHook;
		std::map<std::string, sf::Texture*> spellIconTextureMap;
		std::map<std::string, sf::Sprite*> spellIconSpriteMap;
		sf::Texture* selectTex;
		sf::Sprite selectTexSpr;
	public:
		HUDOverlay();
		void draw(sf::RenderWindow* surf, double dt);
		void hookToCaster(Caster* castHook);
		void hookToCharacter(Entity* entityHook);
		void loadIconForElement(std::string element);
		void loadAllIcons();
};