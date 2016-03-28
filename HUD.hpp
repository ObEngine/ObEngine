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