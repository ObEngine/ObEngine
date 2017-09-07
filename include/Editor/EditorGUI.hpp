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
            void calculateFontSize(sf::RenderWindow& window);
            void applyFontSize(tgui::Panel::Ptr& mainPanel);
            void applyScrollbarMaxValue(tgui::Panel::Ptr& mainPanel);
            void buildToolbar(tgui::Panel::Ptr& mainPanel, tgui::Panel::Ptr& editorPanel, Scene::Scene& scene);
            void buildEditorMenu(tgui::Panel::Ptr& mainPanel);
            void buildEditorMapMenu(tgui::Panel::Ptr& mapPanel, Scene::Scene& world);
            void buildEditorSettingsMenu(tgui::Panel::Ptr& settingsPanel, EditorGrid& editorGrid, System::Cursor& cursor, tgui::ComboBox::Ptr& editMode, Scene::Scene& scene);
            void buildEditorSpritesMenu(tgui::Panel::Ptr& spritesPanel, tgui::Scrollbar::Ptr& spritesScrollbar);
            void buildEditorObjectsMenu(tgui::Panel::Ptr& objectsPanel, tgui::Panel::Ptr& requiresPanel, tgui::Scrollbar::Ptr& objectsScrollbar);
            void buildObjectCreationMenu(tgui::Panel::Ptr& mainPanel);
            void buildKeyBindingMenu(tgui::Panel::Ptr& keybindingPanel, tgui::Scrollbar::Ptr& keybindingScrollbar);
        }
    }
}
