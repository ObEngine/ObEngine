#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <TGUI/TGUI.hpp>

#include <Scene/Scene.hpp>

namespace vili
{
    class ComplexNode;
}

namespace obe::Editor
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

    /**
     * \brief Builds the Editor Object Tab
     * \param scene Reference to the Scene
     * \param objectPanel TGUI Panel that will contains the Objects Creation
     * Button \param requiresPanel TGUI Panel used to transmit Init parameters
     * \param baseTheme TGUI Theme
     * \param objectsScrollbar Scrollbar of the objectsPanel
     */
    void buildObjectTab(Scene::Scene& scene, tgui::Panel::Ptr& objectPanel,
                        tgui::Panel::Ptr& requiresPanel, tgui::Theme& baseTheme,
                        tgui::Scrollbar::Ptr objectsScrollbar);
    /**
     * \brief Builds the RequiresPanel that will transmit Init parameters to the
     * GameObject \param scene Reference to the Scene \param requiresPanel TGUI
     * Panel used to transmit Init parameters \param baseTheme TGUI Theme \param
     * objName Type of GameObject to build
     */
    void buildRequiresObjectTab(Scene::Scene& scene,
                                tgui::Panel::Ptr& requiresPanel,
                                tgui::Theme& baseTheme,
                                const std::string& objName);
    /**
     * \brief Builds an Object through Parameters
     * \param scene Reference to the Scene
     * \param objName Type of GameObject to build
     * \param requires Vili ComplexNode containing the different parameters
     */
    void buildObjectThroughRequire(Scene::Scene& scene,
                                   const std::string& objName,
                                   vili::ComplexNode* requires);
    /**
     * \brief Loads the Sprite Folder
     * \param scene Reference to the Scene
     * \param spritesPanel TGUI Panel that will contains all Sprite Creation
     * Buttons \param spritesCatLabel Name of the folder \param path Path where
     * are the Sprite located \param spritesScrollbar Scrollbar of spritesPanel
     */
    void loadSpriteFolder(Scene::Scene& scene, tgui::Panel::Ptr spritesPanel,
                          tgui::Label::Ptr spritesCatLabel,
                          const std::string& path,
                          tgui::Scrollbar::Ptr spritesScrollbar);
    /**
     * \brief Adds a Sprite to the Scene
     * \param scene Reference to the Scene
     * \param spritePath Path to the image
     */
    void addSpriteToScene(Scene::Scene& scene, const std::string& spritePath);
} // namespace obe::Editor