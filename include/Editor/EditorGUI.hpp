#pragma once

#include <TGUI/TGUI.hpp>
#include "Scene/Scene.hpp"
#include "Grid.hpp"

namespace obe
{
    namespace Editor
    {
        namespace GUI
        {
            extern unsigned int bigFontSize;
            extern unsigned int mediumFontSize;
            extern unsigned int smallFontSize;
            extern tgui::Theme baseTheme;
            void init(sf::RenderWindow& window);
            void buildToolbar(tgui::Panel::Ptr& mainPanel, tgui::Panel::Ptr& editorPanel);
            void buildEditorMenu(tgui::Panel::Ptr& mainPanel);
            void buildEditorMapMenu(tgui::Panel::Ptr& mapPanel, Scene::Scene& world);
            void buildEditorSettingsMenu(tgui::Panel::Ptr& settingsPanel, EditorGrid& editorGrid, System::Cursor& cursor, tgui::ComboBox::Ptr& editMode);
            void buildEditorSpritesMenu(tgui::Panel::Ptr& spritesPanel);
            void buildEditorObjectsMenu(tgui::Panel::Ptr& objectsPanel, tgui::Panel::Ptr& requiresPanel);
            void buildObjectCreationMenu(tgui::Panel::Ptr& mainPanel);
        }
    }
}
