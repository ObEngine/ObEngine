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
#include "HUD.hpp"
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

namespace me
{
	class SpriteFile
	{
		private:
			std::string name;
			sf::Texture texture;
			sf::Sprite sprite;
			sf::Font font;
		public:
			SpriteFile(std::string name, sf::Font font);
			std::string getName();
			void render();
			sf::Sprite* getSprite();
			sf::Texture getTexture();
	};

	class SpriteFolder
	{
		private:
			std::string cat;
			std::string name;
			std::string folderIcon;
			sf::Texture texture;
			sf::Sprite sprite;
			sf::Font font;
			std::vector<SpriteFile*> sprList;
		public:
			SpriteFolder(std::string cat, std::string name, std::string folderIcon, sf::Font font);
			void pushSprite(me::SpriteFile* spr);
			std::vector<SpriteFile*>* getSpriteList();
			void render();
			sf::Sprite* getSprite();
			sf::Texture getTexture();
	};
}


void buildAddSpriteFolderList(GUI::Container* gui, std::vector<me::SpriteFolder*>* addSprFolderList, sf::Font* font);
void editMap(std::string mapName);