#include <Editor/EditorGUI.hpp>
#include "Editor/MapEditorTools.hpp"
#include "Editor/TGUIFallback.hpp"

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
                baseTheme = tgui::Theme();
                baseTheme.load("Data/GUI/obe.style");
            }

            void scrollPanel(tgui::Panel::Ptr panel, tgui::Scrollbar::Ptr scrollbar)
            {
                static int previousScrolbarValue = 0;
                int distanceToMove = previousScrolbarValue - scrollbar->getValue();

                for (auto& widget : panel->getWidgets())
                    widget->setPosition(widget->getPosition().x, widget->getPosition().y + distanceToMove);

                previousScrolbarValue = scrollbar->getValue();
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
                tgui::HorizontalWrap::Ptr toolbarWrap = tgui::HorizontalWrap::create();

                mainPanel->add(titlePanel, "titlePanel");

                titlePanel->add(titleLabel, "titleLabel");
                titlePanel->add(infoLabel, "infoLabel");
                titlePanel->add(savedLabel, "savedLabel");
                titlePanel->add(editorButton, "editorButton");
                titlePanel->add(editMode, "editMode");
                titlePanel->add(cameraMode, "cameraMode");

                titlePanel->setRenderer(baseTheme.getRenderer("TransparentPanel"));
                titlePanel->setSize("100%", "38");
                titlePanel->setPosition(0, 0);

                titleLabel->setPosition(0, 0);
                titleLabel->setTextSize(bigFontSize);
                titleLabel->setRenderer(baseTheme.getRenderer("Label"));
                titleLabel->setText("ObEngine Map Editor");

                infoLabel->setPosition(tguif::bindRight(titleLabel) + 60, 5);
                infoLabel->setTextSize(mediumFontSize);
                infoLabel->setRenderer(baseTheme.getRenderer("Label"));
                infoLabel->setText("<>");

                cameraMode->addItem("Movable Camera");
                cameraMode->addItem("Free Camera");
                cameraMode->setSelectedItem("Movable Camera");
                cameraMode->setSize("200", "100%");
                cameraMode->setPosition("100% - 200", 0);
                cameraMode->setTextSize(mediumFontSize);
                cameraMode->setRenderer(baseTheme.getRenderer("ComboBox"));
                cameraMode->getRenderer()->getTextureArrowUp().setSmooth(true);
                cameraMode->getRenderer()->getTextureArrowDown().setSmooth(true);

                editMode->addItem("LevelSprites");
                editMode->addItem("Collisions");
                editMode->addItem("Play");
                editMode->addItem("None");
                editMode->setSelectedItem("None");
                editMode->setSize("200", "100%");
                editMode->setPosition(tguif::bindLeft(cameraMode) - tguif::bindWidth(editMode) - 1, 0);
                editMode->setTextSize(mediumFontSize);
                editMode->setRenderer(baseTheme.getRenderer("ComboBox"));
                editMode->getRenderer()->getTextureArrowUp().setSmooth(true);
                editMode->getRenderer()->getTextureArrowDown().setSmooth(true);

                editorButton->setSize(190, "100%");
                editorButton->setPosition(tguif::bindLeft(editMode) - tguif::bindWidth(editorButton) - 1, 0);
                editorButton->setText("Editor Menu");
                editorButton->setTextSize(mediumFontSize);
                editorButton->setRenderer(baseTheme.getRenderer("Button"));

                savedLabel->setPosition(tguif::bindLeft(editorButton) - 50, 5);
                savedLabel->setTextSize(smallFontSize);
                savedLabel->setRenderer(baseTheme.getRenderer("GreenLabel"));
                savedLabel->setText("Saved");
                savedLabel->hide();

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
                tgui::Scrollbar::Ptr spritesScrollbar = tgui::Scrollbar::create();
                tgui::Panel::Ptr objectsPanel = tgui::Panel::create();
                tgui::Scrollbar::Ptr objectsScrollbar = tgui::Scrollbar::create();
                tgui::Button::Ptr mapButton = tgui::Button::create();
                tgui::Button::Ptr settingsButton = tgui::Button::create();
                tgui::Button::Ptr spritesButton = tgui::Button::create();
                tgui::Button::Ptr objectsButton = tgui::Button::create();

                mainPanel->add(editorPanel, "editorPanel");
                editorPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                editorPanel->setSize("100% - 100", "100% - 100");
                editorPanel->setPosition(50, 70);
                editorPanel->hide();

                editorPanel->add(mapPanel, "mapPanel");
                editorPanel->add(settingsPanel, "settingsPanel");
                editorPanel->add(spritesPanel, "spritesPanel");
                editorPanel->add(spritesScrollbar, "spritesScrollbar");
                editorPanel->add(objectsPanel, "objectsPanel");
                editorPanel->add(objectsScrollbar, "objectsScrollbar");
                editorPanel->add(mapButton, "mapButton");
                editorPanel->add(settingsButton, "settingsButton");
                editorPanel->add(spritesButton, "spritesButton");
                editorPanel->add(objectsButton, "objectsButton");

                mapButton->setSize("10%", 30);
                mapButton->setPosition(0, 0);
                mapButton->setRenderer(baseTheme.getRenderer("Button"));
                mapButton->setText("Map");
                mapButton->setTextSize(mediumFontSize);

                settingsButton->setPosition(tguif::bindRight(mapButton), 0);
                settingsButton->setSize("10%", 30);
                settingsButton->setRenderer(baseTheme.getRenderer("Button"));
                settingsButton->setText("Settings");
                settingsButton->setTextSize(mediumFontSize);

                spritesButton->setPosition(tguif::bindRight(settingsButton), 0);
                spritesButton->setSize("10%", 30);
                spritesButton->setRenderer(baseTheme.getRenderer("Button"));
                spritesButton->setText("Sprites");
                spritesButton->setTextSize(mediumFontSize);

                objectsButton->setPosition(tguif::bindRight(spritesButton), 0);
                objectsButton->setSize("10%", 30);
                objectsButton->setRenderer(baseTheme.getRenderer("Button"));
                objectsButton->setText("Objects");
                objectsButton->setTextSize(mediumFontSize);

                mapPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                mapPanel->setSize("100%", "100% - 30");
                mapPanel->setPosition(0, 30);

                settingsPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                settingsPanel->setSize("100%", "100% - 30");
                settingsPanel->setPosition(0, 30);

                spritesPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                spritesPanel->setSize("100%", "100% - 30");
                spritesPanel->setPosition(0, 30);

                spritesScrollbar->setPosition("100% - 16", "30");
                spritesScrollbar->setSize("16", "100% - 30");
                spritesScrollbar->connect("ValueChanged", scrollPanel, spritesPanel, spritesScrollbar);
                spritesScrollbar->setLowValue(spritesPanel->getSize().y);

                objectsPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                objectsPanel->setSize("100%", "100% - 30");
                objectsPanel->setPosition(0, 30);

                objectsScrollbar->setPosition("100% - 16", "30");
                objectsScrollbar->setSize("16", "100% - 30");
                objectsScrollbar->connect("ValueChanged", scrollPanel, objectsPanel, objectsScrollbar);
                objectsScrollbar->setLowValue(objectsPanel->getSize().y);

                mapButton->setRenderer(baseTheme.getRenderer("SelectedButton"));
                settingsPanel->hide();
                spritesPanel->hide();
                objectsPanel->hide();

                mapButton->connect("pressed", [mainPanel, spritesScrollbar, objectsScrollbar]()
                {
                    mainPanel->get<tgui::Panel>("mapPanel")->show();
                    mainPanel->get<tgui::Panel>("settingsPanel")->hide();
                    mainPanel->get<tgui::Panel>("spritesPanel")->hide();
                    mainPanel->get<tgui::Panel>("objectsPanel")->hide();
                    mainPanel->get<tgui::Button>("mapButton")->setRenderer(baseTheme.getRenderer("SelectedButton"));
                    mainPanel->get<tgui::Button>("settingsButton")->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("spritesButton")->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("objectsButton")->setRenderer(baseTheme.getRenderer("Button"));
                    spritesScrollbar->hide();
                    objectsScrollbar->hide();
                });

                settingsButton->connect("pressed", [mainPanel, spritesScrollbar, objectsScrollbar]()
                {
                    mainPanel->get<tgui::Panel>("mapPanel")->hide();
                    mainPanel->get<tgui::Panel>("settingsPanel")->show();
                    mainPanel->get<tgui::Panel>("spritesPanel")->hide();
                    mainPanel->get<tgui::Panel>("objectsPanel")->hide();
                    mainPanel->get<tgui::Button>("mapButton")->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("settingsButton")->setRenderer(baseTheme.getRenderer("SelectedButton"));
                    mainPanel->get<tgui::Button>("spritesButton")->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("objectsButton")->setRenderer(baseTheme.getRenderer("Button"));
                    spritesScrollbar->hide();
                    objectsScrollbar->hide();
                });

                spritesButton->connect("pressed", [mainPanel, spritesScrollbar, objectsScrollbar]()
                {
                    mainPanel->get<tgui::Panel>("mapPanel")->hide();
                    mainPanel->get<tgui::Panel>("settingsPanel")->hide();
                    mainPanel->get<tgui::Panel>("spritesPanel")->show();
                    mainPanel->get<tgui::Panel>("objectsPanel")->hide();
                    mainPanel->get<tgui::Button>("mapButton")->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("settingsButton")->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("spritesButton")->setRenderer(baseTheme.getRenderer("SelectedButton"));
                    mainPanel->get<tgui::Button>("objectsButton")->setRenderer(baseTheme.getRenderer("Button"));
                    spritesScrollbar->show();
                    objectsScrollbar->hide();
                });

                objectsButton->connect("pressed", [mainPanel, spritesScrollbar, objectsScrollbar]()
                {
                    mainPanel->get<tgui::Panel>("mapPanel")->hide();
                    mainPanel->get<tgui::Panel>("settingsPanel")->hide();
                    mainPanel->get<tgui::Panel>("spritesPanel")->hide();
                    mainPanel->get<tgui::Panel>("objectsPanel")->show();
                    mainPanel->get<tgui::Button>("mapButton")->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("settingsButton")->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("spritesButton")->setRenderer(baseTheme.getRenderer("Button"));
                    mainPanel->get<tgui::Button>("objectsButton")->setRenderer(baseTheme.getRenderer("SelectedButton"));
                    spritesScrollbar->hide();
                    objectsScrollbar->show();
                });
            }

            void buildEditorMapMenu(tgui::Panel::Ptr& mapPanel, Scene::Scene& world)
            {
                tgui::Label::Ptr mapNameLabel = tgui::Label::create();
                tgui::EditBox::Ptr mapNameInput = tgui::EditBox::create();
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

                mapNameLabel->setPosition(60, tguif::bindBottom(mapCatLabel) + 20);
                mapNameLabel->setTextSize(mediumFontSize);
                mapNameLabel->setRenderer(baseTheme.getRenderer("Label"));
                mapNameLabel->setText("Map Name : ");

                auto changeMapNameLambda = [&world, mapPanel]()
                {
                    tgui::EditBox::Ptr mapNameInput = mapPanel->get<tgui::EditBox>("mapNameInput");
                    if (mapNameInput->getText() != "")
                    {
                        world.setLevelName(mapNameInput->getText());
                        mapNameInput->setRenderer(baseTheme.getRenderer("TextBox"));
                    }
                    else
                    {
                        mapNameInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
                    }
                };

                mapNameInput->setPosition(tguif::bindRight(mapNameLabel) + 20, tguif::bindTop(mapNameLabel));
                mapNameInput->setSize(160, mediumFontSize + 4);
                mapNameInput->setRenderer(baseTheme.getRenderer("TextBox"));
                mapNameInput->connect("returnkeypressed", changeMapNameLambda);

                mapNameButton->setPosition(tguif::bindRight(mapNameInput) + 20, tguif::bindTop(mapNameLabel) + 4);
                mapNameButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
                mapNameButton->setSize(16, 16);
                mapNameButton->connect("pressed", changeMapNameLambda);
            }

            void buildEditorSettingsMenu(tgui::Panel::Ptr& settingsPanel, EditorGrid& editorGrid, System::Cursor& cursor, tgui::ComboBox::Ptr& editMode)
            {
                tgui::Label::Ptr settingsCatLabel = tgui::Label::create();
                tgui::CheckBox::Ptr displayFramerateCheckbox = tgui::CheckBox::create();
                tgui::CheckBox::Ptr enableGridCheckbox = tgui::CheckBox::create();
                tgui::Label::Ptr gridDimensionLabel = tgui::Label::create();
                tgui::EditBox::Ptr gridDimensionXInput = tgui::EditBox::create();
                tgui::EditBox::Ptr gridDimensionYInput = tgui::EditBox::create();
                tgui::Button::Ptr gridDimensionButton = tgui::Button::create();
                tgui::Label::Ptr gridOffsetLabel = tgui::Label::create();
                tgui::EditBox::Ptr gridOffsetXInput = tgui::EditBox::create();
                tgui::EditBox::Ptr gridOffsetYInput = tgui::EditBox::create();
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

                displayFramerateCheckbox->setPosition(60, tguif::bindBottom(settingsCatLabel) + 20);
                displayFramerateCheckbox->setRenderer(baseTheme.getRenderer("CheckBox"));
                displayFramerateCheckbox->setSize(16, 16);
                displayFramerateCheckbox->setTextSize(mediumFontSize);
                displayFramerateCheckbox->setText("Display Framerate ?");

                enableGridCheckbox->setPosition(60, tguif::bindBottom(displayFramerateCheckbox) + 20);
                enableGridCheckbox->setRenderer(baseTheme.getRenderer("CheckBox"));
                enableGridCheckbox->setSize(16, 16);
                enableGridCheckbox->setTextSize(mediumFontSize);
                enableGridCheckbox->setText("Enabled Grid ?");

                enableGridCheckbox->connect("checked", [&editorGrid, snapGridCheckbox]()
                {
                    editorGrid.enable();
                    snapGridCheckbox->enable();
                    snapGridCheckbox->getRenderer()->setTextColor(sf::Color(255, 255, 255));
                });

                enableGridCheckbox->connect("unchecked", [&editorGrid, snapGridCheckbox]()
                {
                    editorGrid.disable();
                    snapGridCheckbox->getRenderer()->setTextColor(sf::Color(100, 100, 100));
                    snapGridCheckbox->uncheck();
                    snapGridCheckbox->disable();
                });

                gridDimensionLabel->setPosition(60, tguif::bindBottom(enableGridCheckbox) + 20);
                gridDimensionLabel->setTextSize(mediumFontSize);
                gridDimensionLabel->setRenderer(baseTheme.getRenderer("Label"));
                gridDimensionLabel->setText("Grid Cell Size : ");

                gridDimensionXInput->setPosition(tguif::bindRight(gridDimensionLabel) + 20, tguif::bindTop(gridDimensionLabel));
                gridDimensionXInput->setSize(80, mediumFontSize + 4);
                gridDimensionXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                gridDimensionXInput->setText(std::to_string(editorGrid.getCellWidth()));
                gridDimensionXInput->setInputValidator(tgui::EditBox::Validator::UInt);

                gridDimensionYInput->setPosition(tguif::bindRight(gridDimensionXInput) + 20, tguif::bindTop(gridDimensionLabel));
                gridDimensionYInput->setSize(80, mediumFontSize + 4);
                gridDimensionYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                gridDimensionYInput->setText(std::to_string(editorGrid.getCellHeight()));
                gridDimensionYInput->setInputValidator(tgui::EditBox::Validator::UInt);

                gridDimensionButton->setPosition(tguif::bindRight(gridDimensionYInput) + 20, tguif::bindTop(gridDimensionLabel) + 4);
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

                gridOffsetLabel->setPosition(60, tguif::bindBottom(gridDimensionLabel) + 20);
                gridOffsetLabel->setTextSize(mediumFontSize);
                gridOffsetLabel->setRenderer(baseTheme.getRenderer("Label"));
                gridOffsetLabel->setText("Grid Cell Offset : ");

                gridOffsetXInput->setPosition(tguif::bindRight(gridOffsetLabel) + 20, tguif::bindTop(gridOffsetLabel));
                gridOffsetXInput->setSize(80, mediumFontSize + 4);
                gridOffsetXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                gridOffsetXInput->setText(std::to_string(editorGrid.getOffsetX()));
                gridOffsetXInput->setInputValidator(tgui::EditBox::Validator::Int);

                gridOffsetYInput->setPosition(tguif::bindRight(gridOffsetXInput) + 20, tguif::bindTop(gridOffsetLabel));
                gridOffsetYInput->setSize(80, mediumFontSize + 4);
                gridOffsetYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                gridOffsetYInput->setText(std::to_string(editorGrid.getOffsetY()));
                gridOffsetYInput->setInputValidator(tgui::EditBox::Validator::Int);

                gridOffsetButton->setPosition(tguif::bindRight(gridOffsetYInput) + 20, tguif::bindTop(gridOffsetLabel) + 4);
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

                snapGridCheckbox->setPosition(60, tguif::bindBottom(gridOffsetLabel) + 20);
                snapGridCheckbox->setRenderer(baseTheme.getRenderer("DisabledCheckBox"));
                snapGridCheckbox->setSize(16, 16);
                snapGridCheckbox->setTextSize(mediumFontSize);
                snapGridCheckbox->setText("Snap to Grid ?");
                snapGridCheckbox->disable();

                snapGridCheckbox->connect("checked", [&editorGrid, &cursor, editMode]()
                {
                    cursor.setConstraint([editMode, &editorGrid](System::Cursor* cursor)
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

            void buildEditorSpritesMenu(tgui::Panel::Ptr& spritesPanel, tgui::Scrollbar::Ptr& spritesScrollbar)
            {
                tgui::Label::Ptr spritesCatLabel = tgui::Label::create();

                spritesPanel->add(spritesCatLabel, "spritesCatLabel");

                spritesCatLabel->setPosition(20, 20);
                spritesCatLabel->setTextSize(bigFontSize);
                spritesCatLabel->setRenderer(baseTheme.getRenderer("Label"));
                spritesCatLabel->setText("[ Sprites Settings ]");

                loadSpriteFolder(spritesPanel, spritesCatLabel, "", spritesScrollbar);
            }

            void buildEditorObjectsMenu(tgui::Panel::Ptr& objectsPanel, tgui::Panel::Ptr& requiresPanel, tgui::Scrollbar::Ptr& objectsScrollbar)
            {
                tgui::Label::Ptr objectsCatLabel = tgui::Label::create();

                objectsPanel->add(objectsCatLabel, "objectsCatLabel");

                objectsCatLabel->setPosition(20, 20);
                objectsCatLabel->setTextSize(bigFontSize);
                objectsCatLabel->setRenderer(baseTheme.getRenderer("Label"));
                objectsCatLabel->setText("[ Objects Settings ]");

                buildObjectTab(objectsPanel, requiresPanel, baseTheme, objectsScrollbar);
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
                requiresPanel->setSize("33%", "66%");
                requiresPanel->setPosition("33%", "17%");
                requiresPanel->hide();

                requiresCloseButton->setRenderer(baseTheme.getRenderer("CloseButton"));
                requiresCloseButton->setSize("32", "32");
                requiresCloseButton->setPosition("100% - 40", "8");
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
                requiresPanelContent->setSize("100% - 2", "100% - 62");
                requiresPanelContent->setPosition(0, 60);
            }
        }
    }
}
