#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <tgui/TGUI.hpp>

#include "PathResolver.hpp"
#include "Script.hpp"
#include "World.hpp"

namespace obe
{
	namespace EditorTools
	{
		class Thumbnailer
		{
			private:
				sf::RenderTexture renderer;
				sf::Texture folderTexture;
				std::map<std::string, sf::Texture*> cache;
				sf::Font font;
				static Thumbnailer* _instance;
				Thumbnailer();
			public:
				static sf::Texture* GetSpriteThumbnail(std::string path);
				static sf::Texture* GetFolderThumbnail(std::string path);
		};

		void buildObjectTab(tgui::Panel::Ptr& objectPanel, tgui::Theme& baseTheme);
		void buildRequiresObjectTab(tgui::Gui&, std::string objName);
		void buildObjectThroughRequire(std::string objName);
		void loadSpriteFolder(tgui::Panel::Ptr& spritesPanel, tgui::Label::Ptr& spritesCatLabel, std::string path);
		void addSpriteToWorld(std::string geid);
	}
}