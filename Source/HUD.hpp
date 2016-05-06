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

class IntBar
{
	private:
		int barPercent = 0;
		double oldPercent = 0;
		sf::Texture barTexture;
		sf::Sprite barSprite;
		int x;
		int y;
		int w;
	public:
		IntBar(std::string barFilename, int x, int y, int w);
		void setPosition(int x, int y);
		void setWidth(int w);
		int getX();
		int getY();
		int getW();
		void setPercent(int percent);
		void addPercent(int percent);
		int getPercent();
		void update(double dt);
		void draw(sf::RenderWindow* surf);
};

class HUDOverlay
{
	private:
		IntBar* lifeBar;
		IntBar* manaBar;
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
		void draw(sf::RenderWindow* surf);
		void update(double dt);
		void hookToCaster(Caster* castHook);
		void hookToCharacter(Entity* entityHook);
		void loadIconForElement(std::string element);
		void loadAllIcons();
};