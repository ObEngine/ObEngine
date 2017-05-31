#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <TGUI/TGUI.hpp>

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
            static const int size = 246;
            Thumbnailer();
        public:
            static sf::Texture* GetSpriteThumbnail(std::string path);
            static sf::Texture* GetFolderThumbnail(std::string path);
        };

        void buildObjectTab(tgui::Panel::Ptr& objectPanel, tgui::Panel::Ptr& requiresPanel, tgui::Theme& baseTheme);
        void buildRequiresObjectTab(tgui::Panel::Ptr& requiresPanel, std::string objName);
        void buildObjectThroughRequire(std::string objName);
        void loadSpriteFolder(tgui::Panel::Ptr& spritesPanel, tgui::Label::Ptr& spritesCatLabel, std::string path);
        void addSpriteToWorld(std::string geid);
    }
}
