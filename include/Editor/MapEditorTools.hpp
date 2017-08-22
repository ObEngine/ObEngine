#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <TGUI/TGUI.hpp>

namespace vili 
{
    class ComplexNode;
}

namespace obe
{
    namespace Editor
    {
        /**
         * \brief Class used to create Thumbnails of Sprites / Folders
         */
        class Thumbnailer
        {
        private:
            sf::RenderTexture m_renderer;
            sf::Texture m_folderTexture;
            std::map<std::string, sf::Texture*> m_cache;
            sf::Font m_font;
            static Thumbnailer* m_instance;
            static const int m_size = 246;
            Thumbnailer();
        public:
            /**
             * \brief Creates a thumbnail of the Sprite at the given path
             * \param path Path of the Sprite you want to create the Thumbnail
             * \return An adress to the created sf::Texture
             */
            static sf::Texture* GetSpriteThumbnail(const std::string& path);
            /**
            * \brief Creates a thumbnail of the Folder at the given path
            * \param path Path of the Folder you want to create the Thumbnail
            * \return An adress to the created sf::Texture
            */
            static sf::Texture* GetFolderThumbnail(const std::string& path);
        };

        void buildObjectTab(tgui::Panel::Ptr& objectPanel, tgui::Panel::Ptr& requiresPanel, tgui::Theme& baseTheme, tgui::Scrollbar::Ptr objectsScrollbar);
        void buildRequiresObjectTab(tgui::Panel::Ptr& requiresPanel, tgui::Theme& baseTheme, const std::string& objName);
        void buildObjectThroughRequire(const std::string& objName, vili::ComplexNode* requires);
        void loadSpriteFolder(tgui::Panel::Ptr spritesPanel, tgui::Label::Ptr spritesCatLabel, const std::string& path, tgui::Scrollbar::Ptr spritesScrollbar);
        void addSpriteToWorld(std::string geid);
    }
}
