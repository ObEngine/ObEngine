#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "GUI.hpp"
#include "PathResolver.hpp"
#include "Script.hpp"
#include "World.hpp"

namespace mse
{
	namespace EditorTools
	{
		class SpriteFile
		{
		private:
			std::string name;
			sf::Texture texture;
			sf::Font font;
		public:
			SpriteFile(std::string name, sf::Font font);
			SpriteFile(std::string name, sf::Texture texture);
			std::string getName();
			void render(sf::RenderTexture* rtexture);
			sf::Texture getTexture();
		};

		class SpriteFolder
		{
		private:
			std::string category;
			std::string name;
			std::string folderIcon;
			sf::Texture texture;
			sf::Sprite sprite;
			sf::Font font;
			std::vector<SpriteFile*> sprList;
		public:
			SpriteFolder(std::string category, std::string name, std::string folderIcon, sf::Font font);
			void pushSprite(SpriteFile* spr);
			std::vector<SpriteFile*>* getSpriteList();
			void render(sf::RenderTexture* rtexture);
			sf::Sprite* getSprite();
			sf::Texture getTexture();
		};

		void buildObjectTab();
		void buildRequiresObjectTab(std::string objName);
		void buildObjectThroughRequire(std::string objName);
		void loadEgFolder(std::string path);
		void loadSpriteFolder(std::string geid);
		void buildAddSpriteFolderList();
		void displayAddSpriteFolderList();
		void addSpriteToWorld(std::string geid);
	}
}