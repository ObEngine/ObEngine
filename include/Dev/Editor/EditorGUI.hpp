#pragma once

#include "Grid.hpp"
#include "Scene/Scene.hpp"
#include <TGUI/TGUI.hpp>

namespace obe::Editor::GUI
{
    static unsigned int bigFontSize;
    static unsigned int mediumFontSize;
    static unsigned int smallFontSize;

    extern tgui::Theme baseTheme;
    void init();
    void calculateFontSize();
    void applyFontSize(tgui::Panel::Ptr& mainPanel);
    void applyScrollbarMaxValue(tgui::Panel::Ptr& mainPanel);
    void buildToolbar(tgui::Panel::Ptr& mainPanel,
                      tgui::Panel::Ptr& editorPanel, Scene::Scene& scene);
    void buildEditorMenu(tgui::Panel::Ptr& mainPanel);
    void buildEditorMapMenu(tgui::Panel::Ptr& mapPanel, Scene::Scene& scene);
    void buildEditorSettingsMenu(tgui::Panel::Ptr& settingsPanel,
                                 EditorGrid& editorGrid, System::Cursor& cursor,
                                 tgui::ComboBox::Ptr& editMode,
                                 Scene::Scene& scene);
    void buildEditorSpritesMenu(tgui::Panel::Ptr& spritesPanel,
                                tgui::Scrollbar::Ptr& spritesScrollbar,
                                Scene::Scene& scene);
    void buildEditorObjectsMenu(tgui::Panel::Ptr& objectsPanel,
                                tgui::Panel::Ptr& requiresPanel,
                                tgui::Scrollbar::Ptr& objectsScrollbar,
                                Scene::Scene& scene);
    void buildObjectCreationMenu(tgui::Panel::Ptr& mainPanel);
    void buildKeyBindingMenu(tgui::Panel::Ptr& keybindingPanel,
                             tgui::Scrollbar::Ptr& keybindingScrollbar);
} // namespace obe::Editor::GUI