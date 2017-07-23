#include <Editor/EditorGUI.hpp>
#include "Editor/MapEditorTools.hpp"

namespace obe
{
    namespace Editor
    {
        namespace GUI
        {
            unsigned int bigFontSize;
            unsigned int mediumFontSize;
            unsigned int smallFontSize;
            tgui::Theme baseTheme;

            void init(sf::RenderWindow& window)
            {
                bigFontSize = static_cast<double>(window.getSize().y) / static_cast<double>(32.0) - 6;
                mediumFontSize = static_cast<double>(bigFontSize) / 1.3;
                smallFontSize = static_cast<double>(bigFontSize) / 2.0;
                baseTheme.load("Data/GUI/obe.style");
            }

            void buildToolbar(tgui::Panel::Ptr& mainPanel, tgui::Panel::Ptr& editorPanel)
            {
                tgui::Panel::Ptr titlePanel = tgui::Panel::create();
                tgui::Label::Ptr titleLabel = tgui::Label::create();
                tgui::Label::Ptr infoLabel = tgui::Label::create();
                tgui::Label::Ptr savedLabel = tgui::Label::create();
                tgui::Button::Ptr editorButton = tgui::Button::create();
                tgui::ComboBox::Ptr cameraMode = tgui::ComboBox::create();
                tgui::ComboBox::Ptr editMode = tgui::ComboBox::create();

                mainPanel->add(titlePanel, "titlePanel");

                titlePanel->add(titleLabel, "titleLabel");
                titlePanel->add(infoLabel, "infoLabel");
                titlePanel->add(savedLabel, "savedLabel");
                titlePanel->add(editorButton, "editorButton");
                titlePanel->add(editMode, "editMode");
                titlePanel->add(cameraMode, "cameraMode");

                titlePanel->setRenderer(baseTheme.getRenderer("TransparentPanel"));
                titlePanel->setSize("&.w", "&.h / 30");
                titlePanel->setPosition(0, 0);

                titleLabel->setPosition(0, 0);
                titleLabel->setTextSize(bigFontSize);
                titleLabel->setRenderer(baseTheme.getRenderer("Label"));
                titleLabel->setText("ObEngine Map Editor");

                infoLabel->setPosition(bindRight(titleLabel) + 60, 5);
                infoLabel->setTextSize(mediumFontSize);
                infoLabel->setRenderer(baseTheme.getRenderer("Label"));
                infoLabel->setText("<>");

                savedLabel->setPosition(bindLeft(editorButton) - 50, 5);
                savedLabel->setTextSize(smallFontSize);
                savedLabel->setRenderer(baseTheme.getRenderer("GreenLabel"));
                savedLabel->setText("Saved");
                savedLabel->hide();

                cameraMode->addItem("Movable Camera");
                cameraMode->addItem("Free Camera");
                cameraMode->setSelectedItem("Movable Camera");
                cameraMode->setSize("200", "&.h");
                cameraMode->setPosition("&.w - w", 0);
                cameraMode->setTextSize(mediumFontSize);
                cameraMode->setRenderer(baseTheme.getRenderer("ComboBox"));

                editMode->addItem("LevelSprites");
                editMode->addItem("Collisions");
                editMode->addItem("Play");
                editMode->addItem("None");
                editMode->setSelectedItem("None");
                editMode->setPosition(bindLeft(cameraMode) - bindWidth(editMode) - 1, 0);
                editMode->setSize("200", "&.h");
                editMode->setTextSize(mediumFontSize);
                editMode->setRenderer(baseTheme.getRenderer("ComboBox"));

                editorButton->setPosition(bindLeft(editMode) - bindWidth(editorButton) - 1, 0);
                editorButton->setSize(190, "&.h");
                editorButton->setText("Editor Menu");
                editorButton->setTextSize(mediumFontSize);
                editorButton->setRenderer(baseTheme.getRenderer("Button"));

                editorButton->connect("pressed", [editorPanel]()
                {
                    editorPanel->isVisible() ? editorPanel->hide() : editorPanel->show();
                });
            }

            void buildEditorMenu(tgui::Panel::Ptr& mainPanel)
            {
                tgui::Panel::Ptr editorPanel = tgui::Panel::create();
                tgui::Panel::Ptr mapPanel = tgui::Panel::create();
                tgui::Panel::Ptr settingsPanel = tgui::Panel::create();
                tgui::Panel::Ptr spritesPanel = tgui::Panel::create();
                tgui::Panel::Ptr objectsPanel = tgui::Panel::create();
                tgui::Button::Ptr mapButton = tgui::Button::create();
                tgui::Button::Ptr settingsButton = tgui::Button::create();
                tgui::Button::Ptr spritesButton = tgui::Button::create();
                tgui::Button::Ptr objectsButton = tgui::Button::create();

                mainPanel->add(editorPanel, "editorPanel");
                editorPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                editorPanel->setSize("&.w - 100", "&.h - 100");
                editorPanel->setPosition(50, 70);
                editorPanel->hide();

                editorPanel->add(mapPanel, "mapPanel");
                editorPanel->add(settingsPanel, "settingsPanel");
                editorPanel->add(spritesPanel, "spritesPanel");
                editorPanel->add(objectsPanel, "objectsPanel");
                editorPanel->add(mapButton, "mapButton");
                editorPanel->add(settingsButton, "settingsButton");
                editorPanel->add(spritesButton, "spritesButton");
                editorPanel->add(objectsButton, "objectsButton");

                mapButton->setPosition(0, 0);
                mapButton->setSize("&.w / 10", 30);
                mapButton->setRenderer(baseTheme.getRenderer("Button"));
                mapButton->setText("Map");
                mapButton->setTextSize(mediumFontSize);

                settingsButton->setPosition(bindRight(mapButton), 0);
                settingsButton->setSize("&.w / 10", 30);
                settingsButton->setRenderer(baseTheme.getRenderer("Button"));
                settingsButton->setText("Settings");
                settingsButton->setTextSize(mediumFontSize);

                spritesButton->setPosition(bindRight(settingsButton), 0);
                spritesButton->setSize("&.w / 10", 30);
                spritesButton->setRenderer(baseTheme.getRenderer("Button"));
                spritesButton->setText("Sprites");
                spritesButton->setTextSize(mediumFontSize);

                objectsButton->setPosition(bindRight(spritesButton), 0);
                objectsButton->setSize("&.w / 10", 30);
                objectsButton->setRenderer(baseTheme.getRenderer("Button"));
                objectsButton->setText("Objects");
                objectsButton->setTextSize(mediumFontSize);

                mapPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                mapPanel->setSize("&.w", "&.h - 30");
                mapPanel->setPosition(0, 30);

                settingsPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                settingsPanel->setSize("&.w", "&.h - 30");
                settingsPanel->setPosition(0, 30);

                spritesPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                spritesPanel->setSize("&.w", "&.h - 30");
                spritesPanel->setPosition(0, 30);

                objectsPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                objectsPanel->setSize("&.w", "&.h - 30");
                objectsPanel->setPosition(0, 30);

                mapButton->setRenderer(baseTheme.getRenderer("SelectedButton"));
                settingsPanel->hide();
                spritesPanel->hide();
                objectsPanel->hide();

                mapButton->connect("pressed", [mainPanel]()
                {
                    mainPanel->get<tgui::Panel>("mapPanel", true)->show();
                    mainPanel->get<tgui::Panel>("settingsPanel", true)->hide();
                    mainPanel->get<tgui::Panel>("spritesPanel", true)->hide();
                    mainPanel->get<tgui::Panel>("objectsPanel", true)->hide();
                    mainPanel->get<tgui::Button>("mapButton", true)->setRenderer(baseTheme.getRenderer("SelectedButton"));
                    mainPanel->get<tgui::Button>("settingsButton", true)->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("spritesButton", true)->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("objectsButton", true)->setRenderer(baseTheme.getRenderer("Button"));
                });

                settingsButton->connect("pressed", [mainPanel]()
                {
                    mainPanel->get<tgui::Panel>("mapPanel", true)->hide();
                    mainPanel->get<tgui::Panel>("settingsPanel", true)->show();
                    mainPanel->get<tgui::Panel>("spritesPanel", true)->hide();
                    mainPanel->get<tgui::Panel>("objectsPanel", true)->hide();
                    mainPanel->get<tgui::Button>("mapButton", true)->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("settingsButton", true)->setRenderer(baseTheme.getRenderer("SelectedButton"));
                    mainPanel->get<tgui::Button>("spritesButton", true)->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("objectsButton", true)->setRenderer(baseTheme.getRenderer("Button"));
                });

                spritesButton->connect("pressed", [mainPanel]()
                {
                    mainPanel->get<tgui::Panel>("mapPanel", true)->hide();
                    mainPanel->get<tgui::Panel>("settingsPanel", true)->hide();
                    mainPanel->get<tgui::Panel>("spritesPanel", true)->show();
                    mainPanel->get<tgui::Panel>("objectsPanel", true)->hide();
                    mainPanel->get<tgui::Button>("mapButton", true)->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("settingsButton", true)->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("spritesButton", true)->setRenderer(baseTheme.getRenderer("SelectedButton"));
                    mainPanel->get<tgui::Button>("objectsButton", true)->setRenderer(baseTheme.getRenderer("Button"));
                });

                objectsButton->connect("pressed", [mainPanel]()
                {
                    mainPanel->get<tgui::Panel>("mapPanel", true)->hide();
                    mainPanel->get<tgui::Panel>("settingsPanel", true)->hide();
                    mainPanel->get<tgui::Panel>("spritesPanel", true)->hide();
                    mainPanel->get<tgui::Panel>("objectsPanel", true)->show();
                    mainPanel->get<tgui::Button>("mapButton", true)->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("settingsButton", true)->setRenderer(baseTheme.getRenderer("SelectedButton"));
                    mainPanel->get<tgui::Button>("spritesButton", true)->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("objectsButton", true)->setRenderer(baseTheme.getRenderer("SelectedButton"));
                });
            }

            void buildEditorMapMenu(tgui::Panel::Ptr& mapPanel, Scene::Scene& world)
            {
                tgui::Label::Ptr mapNameLabel = tgui::Label::create();
                tgui::TextBox::Ptr mapNameInput = tgui::TextBox::create();
                tgui::Button::Ptr mapNameButton = tgui::Button::create();
                tgui::Label::Ptr mapCatLabel = tgui::Label::create();

                mapPanel->add(mapCatLabel, "mapCatLabel");
                mapPanel->add(mapNameLabel, "mapNameLabel");
                mapPanel->add(mapNameInput, "mapNameInput");
                mapPanel->add(mapNameButton, "mapNameButton");

                mapCatLabel->setPosition(20, 20);
                mapCatLabel->setTextSize(bigFontSize);
                mapCatLabel->setRenderer(baseTheme.getRenderer("Label"));
                mapCatLabel->setText("[ Map Settings ]");

                mapNameLabel->setPosition(60, bindBottom(mapCatLabel) + 20);
                mapNameLabel->setTextSize(mediumFontSize);
                mapNameLabel->setRenderer(baseTheme.getRenderer("Label"));
                mapNameLabel->setText("Map Name : ");

                mapNameInput->setPosition(bindRight(mapNameLabel) + 20, bindTop(mapNameLabel));
                mapNameInput->setSize(160, mediumFontSize + 4);
                mapNameInput->setRenderer(baseTheme.getRenderer("TextBox"));

                mapNameButton->setPosition(bindRight(mapNameInput) + 20, bindTop(mapNameLabel) + 4);
                mapNameButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
                mapNameButton->setSize(16, 16);
                mapNameButton->connect("pressed", [&world, mapPanel]()
                {
                    tgui::TextBox::Ptr mapNameInput = mapPanel->get<tgui::TextBox>("mapNameInput", true);
                    if (mapNameInput->getText() != "")
                    {
                        world.setLevelName(mapNameInput->getText());
                        mapNameInput->setRenderer(baseTheme.getRenderer("TextBox"));
                    }
                    else
                    {
                        mapNameInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
                    }
                });
            }

            void buildEditorSettingsMenu(tgui::Panel::Ptr& settingsPanel, EditorGrid& editorGrid, System::Cursor& cursor, tgui::ComboBox::Ptr& editMode)
            {
                tgui::Label::Ptr settingsCatLabel = tgui::Label::create();
                tgui::CheckBox::Ptr displayFramerateCheckbox = tgui::CheckBox::create();
                tgui::CheckBox::Ptr enableGridCheckbox = tgui::CheckBox::create();
                tgui::Label::Ptr gridDimensionLabel = tgui::Label::create();
                tgui::TextBox::Ptr gridDimensionXInput = tgui::TextBox::create();
                tgui::TextBox::Ptr gridDimensionYInput = tgui::TextBox::create();
                tgui::Button::Ptr gridDimensionButton = tgui::Button::create();
                tgui::Label::Ptr gridOffsetLabel = tgui::Label::create();
                tgui::TextBox::Ptr gridOffsetXInput = tgui::TextBox::create();
                tgui::TextBox::Ptr gridOffsetYInput = tgui::TextBox::create();
                tgui::Button::Ptr gridOffsetButton = tgui::Button::create();
                tgui::CheckBox::Ptr snapGridCheckbox = tgui::CheckBox::create();

                settingsPanel->add(settingsCatLabel, "settingsCatLabel");

                settingsPanel->add(displayFramerateCheckbox, "displayFramerateCheckbox");
                settingsPanel->add(enableGridCheckbox, "enableGridCheckbox");
                settingsPanel->add(gridDimensionLabel, "gridDimensionLabel");
                settingsPanel->add(gridDimensionXInput, "gridDimensionXInput");
                settingsPanel->add(gridDimensionYInput, "gridDimensionYInput");
                settingsPanel->add(gridDimensionButton, "gridDimensionButton");
                settingsPanel->add(gridOffsetLabel, "gridOffsetLabel");
                settingsPanel->add(gridOffsetXInput, "gridOffsetXInput");
                settingsPanel->add(gridOffsetYInput, "gridOffsetYInput");
                settingsPanel->add(gridOffsetButton, "gridOffsetButton");
                settingsPanel->add(snapGridCheckbox, "snapGridCheckbox");

                settingsCatLabel->setPosition(20, 20);
                settingsCatLabel->setTextSize(bigFontSize);
                settingsCatLabel->setRenderer(baseTheme.getRenderer("Label"));
                settingsCatLabel->setText("[ Global Settings ]");

                displayFramerateCheckbox->setPosition(60, bindBottom(settingsCatLabel) + 20);
                displayFramerateCheckbox->setRenderer(baseTheme.getRenderer("CheckBox"));
                displayFramerateCheckbox->setSize(16, 16);
                displayFramerateCheckbox->setTextSize(mediumFontSize);
                displayFramerateCheckbox->setText("Display Framerate ?");

                enableGridCheckbox->setPosition(60, bindBottom(displayFramerateCheckbox) + 20);
                enableGridCheckbox->setRenderer(baseTheme.getRenderer("CheckBox"));
                enableGridCheckbox->setSize(16, 16);
                enableGridCheckbox->setTextSize(mediumFontSize);
                enableGridCheckbox->setText("Enabled Grid ?");

                enableGridCheckbox->connect("checked", [snapGridCheckbox]()
                {
                    snapGridCheckbox->enable();
                    snapGridCheckbox->setRenderer(baseTheme.getRenderer("CheckBox"));
                });

                enableGridCheckbox->connect("unchecked", [snapGridCheckbox]()
                {
                    snapGridCheckbox->disable();
                    snapGridCheckbox->setRenderer(baseTheme.getRenderer("DisabledCheckBox"));
                });

                gridDimensionLabel->setPosition(60, bindBottom(enableGridCheckbox) + 20);
                gridDimensionLabel->setTextSize(mediumFontSize);
                gridDimensionLabel->setRenderer(baseTheme.getRenderer("Label"));
                gridDimensionLabel->setText("Grid Cell Size : ");

                gridDimensionXInput->setPosition(bindRight(gridDimensionLabel) + 20, bindTop(gridDimensionLabel));
                gridDimensionXInput->setSize(80, mediumFontSize + 4);
                gridDimensionXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                gridDimensionXInput->setText(std::to_string(editorGrid.getCellWidth()));

                gridDimensionYInput->setPosition(bindRight(gridDimensionXInput) + 20, bindTop(gridDimensionLabel));
                gridDimensionYInput->setSize(80, mediumFontSize + 4);
                gridDimensionYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                gridDimensionYInput->setText(std::to_string(editorGrid.getCellHeight()));

                gridDimensionButton->setPosition(bindRight(gridDimensionYInput) + 20, bindTop(gridDimensionLabel) + 4);
                gridDimensionButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
                gridDimensionButton->setSize(16, 16);

                gridDimensionButton->connect("pressed", [gridDimensionXInput, gridDimensionYInput, &editorGrid]()
                {
                    gridDimensionXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                    gridDimensionYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                    if (Utils::String::isStringInt(gridDimensionXInput->getText()) && Utils::String::isStringInt(gridDimensionYInput->getText()))
                    {
                        std::string xGridSize = gridDimensionXInput->getText();
                        std::string yGridSize = gridDimensionYInput->getText();
                        if (stoi(xGridSize) < 2 || stoi(yGridSize) < 2)
                        {
                            editorGrid.setSize(2, 2);
                            gridDimensionXInput->setText("2");
                            gridDimensionYInput->setText("2");
                        }
                        else
                            editorGrid.setSize(stoi(xGridSize), stoi(yGridSize));
                        gridDimensionXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                        gridDimensionYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                        return;
                    }
                    if (!Utils::String::isStringInt(gridDimensionXInput->getText()))
                    {
                        gridDimensionXInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
                    }
                    if (!Utils::String::isStringInt(gridDimensionYInput->getText()))
                    {
                        gridDimensionYInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
                    }
                });

                gridOffsetLabel->setPosition(60, bindBottom(gridDimensionLabel) + 20);
                gridOffsetLabel->setTextSize(mediumFontSize);
                gridOffsetLabel->setRenderer(baseTheme.getRenderer("Label"));
                gridOffsetLabel->setText("Grid Cell Offset : ");

                gridOffsetXInput->setPosition(bindRight(gridOffsetLabel) + 20, bindTop(gridOffsetLabel));
                gridOffsetXInput->setSize(80, mediumFontSize + 4);
                gridOffsetXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                gridOffsetXInput->setText(std::to_string(editorGrid.getOffsetX()));

                gridOffsetYInput->setPosition(bindRight(gridOffsetXInput) + 20, bindTop(gridOffsetLabel));
                gridOffsetYInput->setSize(80, mediumFontSize + 4);
                gridOffsetYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                gridOffsetYInput->setText(std::to_string(editorGrid.getOffsetY()));

                gridOffsetButton->setPosition(bindRight(gridOffsetYInput) + 20, bindTop(gridOffsetLabel) + 4);
                gridOffsetButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
                gridOffsetButton->setSize(16, 16);

                gridOffsetButton->connect("pressed", [gridOffsetXInput, gridOffsetYInput, &editorGrid]()
                {
                    if (Utils::String::isStringInt(gridOffsetXInput->getText()) && Utils::String::isStringInt(gridOffsetYInput->getText()))
                    {
                        std::string xGridOffset = gridOffsetXInput->getText();
                        std::string yGridOffset = gridOffsetYInput->getText();
                        editorGrid.setOffset(stoi(xGridOffset), stoi(yGridOffset));
                        gridOffsetXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                        gridOffsetYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                        return;
                    }
                    if (!Utils::String::isStringInt(gridOffsetXInput->getText()))
                    {
                        gridOffsetXInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
                    }
                    if (!Utils::String::isStringInt(gridOffsetYInput->getText()))
                    {
                        gridOffsetYInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
                    }
                });

                snapGridCheckbox->setPosition(60, bindBottom(gridOffsetLabel) + 20);
                snapGridCheckbox->setRenderer(baseTheme.getRenderer("DisabledCheckBox"));
                snapGridCheckbox->setSize(16, 16);
                snapGridCheckbox->setTextSize(mediumFontSize);
                snapGridCheckbox->setText("Snap to Grid ?");
                snapGridCheckbox->disable();

                snapGridCheckbox->connect("checked", [&editorGrid, &cursor, &editMode]()
                {
                    cursor.setConstraint([&editMode, &editorGrid](System::Cursor* cursor)
                    {
                        if (editMode->getSelectedItem() == "LevelSprites" || editMode->getSelectedItem() == "Collisions")
                        {
                            int snappedX = cursor->getRawX() / editorGrid.getCellWidth() * editorGrid.getCellWidth() + editorGrid.getOffsetX();
                            int snappedY = cursor->getRawY() / editorGrid.getCellHeight() * editorGrid.getCellHeight() + editorGrid.getOffsetY();
                            return std::pair<int, int>(snappedX, snappedY);
                        }
                        else
                        {
                            return System::Constraints::Default(cursor);
                        }
                    });
                });

                snapGridCheckbox->connect("unchecked", [&cursor]()
                {
                    cursor.setConstraint(System::Constraints::Default);
                });
            }

            void buildEditorSpritesMenu(tgui::Panel::Ptr& spritesPanel)
            {
                tgui::Label::Ptr spritesCatLabel = tgui::Label::create();

                spritesPanel->add(spritesCatLabel, "spritesCatLabel");

                spritesCatLabel->setPosition(20, 20);
                spritesCatLabel->setTextSize(bigFontSize);
                spritesCatLabel->setRenderer(baseTheme.getRenderer("Label"));
                spritesCatLabel->setText("[ Sprites Settings ]");

                loadSpriteFolder(spritesPanel, spritesCatLabel, "");
            }

            void buildEditorObjectsMenu(tgui::Panel::Ptr& objectsPanel, tgui::Panel::Ptr& requiresPanel)
            {
                tgui::Label::Ptr objectsCatLabel = tgui::Label::create();

                objectsPanel->add(objectsCatLabel, "objectsCatLabel");

                objectsCatLabel->setPosition(20, 20);
                objectsCatLabel->setTextSize(bigFontSize);
                objectsCatLabel->setRenderer(baseTheme.getRenderer("Label"));
                objectsCatLabel->setText("[ Objects Settings ]");

                buildObjectTab(objectsPanel, requiresPanel, baseTheme);
            }

            void buildObjectCreationMenu(tgui::Panel::Ptr& mainPanel)
            {
                tgui::Panel::Ptr requiresPanel = tgui::Panel::create();
                tgui::Button::Ptr requiresCloseButton = tgui::Button::create();
                tgui::Label::Ptr requiresTitleLabel = tgui::Label::create();
                tgui::Panel::Ptr requiresPanelContent = tgui::Panel::create();

                mainPanel->add(requiresPanel, "requiresPanel");
                requiresPanel->add(requiresPanelContent, "content");
                requiresPanel->add(requiresTitleLabel, "label");
                requiresPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                requiresPanel->setSize("&.w / 3", "&.h / 1.5");
                requiresPanel->setPosition("&.w / 2 - width / 2", "&.h / 2 - height / 2");
                requiresPanel->hide();

                requiresCloseButton->setRenderer(baseTheme.getRenderer("CloseButton"));
                requiresCloseButton->setSize("32", "32");
                requiresCloseButton->setPosition("&.width - 40", "8");
                requiresCloseButton->connect("pressed", [requiresPanel]()
                {
                    requiresPanel->hide();
                });
                requiresPanel->add(requiresCloseButton, "requiresCloseButton");

                requiresTitleLabel->setPosition(30, 15);
                requiresTitleLabel->setTextSize(bigFontSize);
                requiresTitleLabel->setRenderer(baseTheme.getRenderer("Label"));
                requiresTitleLabel->setText("Object builder Window");

                requiresPanelContent->setRenderer(baseTheme.getRenderer("TransparentPanel"));
                requiresPanelContent->setSize("&.w - 2", "&.h - 62");
                requiresPanelContent->setPosition(0, 60);
            }
        }
    }
}
