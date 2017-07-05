//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "MapEditor.hpp"

namespace obe
{
    namespace Editor
    {
        void editMap(std::string mapName)
        {
            std::cout << "<System> Creating window with resolution " << Coord::UnitVector::Screen.w << "x" << Coord::UnitVector::Screen.h << std::endl;

            //Creating Window
            sf::RenderWindow window(sf::VideoMode(Coord::UnitVector::Screen.w, Coord::UnitVector::Screen.h), "ObEngine", sf::Style::Fullscreen);
            window.setKeyRepeatEnabled(false);
            window.setMouseCursorVisible(false);
            sf::Texture loadingTexture;
            loadingTexture.loadFromFile("Sprites/Menus/loading.png");
            loadingTexture.setSmooth(true);
            sf::Sprite loadingSprite;
            loadingSprite.setTexture(loadingTexture);
            sf::Font loadingFont;
            loadingFont.loadFromFile("Data/Fonts/weblysleekuil.ttf");
            sf::Text loadingText;
            loadingText.setFont(loadingFont);
            loadingText.setCharacterSize(70.0);
            loadingText.setPosition(348.0, 595.0);
            vili::DataParser loadingStrDP("Sprites/Menus/loading.vili");
            std::string loadingRandomStr = loadingStrDP.at<vili::ListAttribute>("Loading", "loadingStr").get(
                Functions::Math::randint(0, loadingStrDP.at<vili::ListAttribute>("Loading", "loadingStr").size() - 1));
            loadingText.setString(loadingRandomStr);
            window.draw(loadingSprite);
            window.draw(loadingText);
            window.display();

            Script::hookCore.dropValue("TriggerDatabase", Script::TriggerDatabase::GetInstance());
            Graphics::TextRenderer textDisplay;
            textDisplay.createRenderer("Shade", "MapSaver");
            Script::hookCore.dropValue("TextDisplay", &textDisplay);

            //Console
            Debug::Console gameConsole;
            Script::hookCore.dropValue("Console", &gameConsole);

            //Font
            sf::Font font;
            font.loadFromFile("Data/Fonts/arial.ttf");

            //Config
            vili::DataParser configFile;
            System::Path("Data/config.cfg.vili").loadResource(&configFile, System::Loaders::dataLoader);
            vili::ComplexAttribute& gameConfig = configFile->at("GameConfig");
            int scrollSensitive = gameConfig.at<vili::BaseAttribute>("scrollSensibility");
            vili::ComplexAttribute& developpement = configFile.at("Developpement");
            bool showChar = developpement.at<vili::BaseAttribute>("showCharacter");
            bool showCol = developpement.at<vili::BaseAttribute>("showCollisions");
            bool showLSpr = developpement.at<vili::BaseAttribute>("showLevelSprites");
            bool showOverlay = developpement.at<vili::BaseAttribute>("showOverlay");
            bool showCursor = developpement.at<vili::BaseAttribute>("showCursor");
            bool drawFPS = developpement.at<vili::BaseAttribute>("showFPS");

            //Cursor
            System::Cursor cursor(&window);
            cursor.selectCursor("RoundWhite");
            Collision::PolygonalCollider cursorCollider("cursor");
            cursorCollider.addPoint(0, 0);
            cursorCollider.addPoint(1, 0);
            cursorCollider.addPoint(1, 1);
            cursorCollider.addPoint(0, 1);
            cursor.updateOutsideWindow(true);
            Script::hookCore.dropValue("Cursor", &cursor);

            //World Creation / Loading
            World::World world;
            (*world.getScriptEngine())["stream"] = gameConsole.createStream("World", true);
            world.getScriptEngine()->setErrorHandler([&gameConsole](int statuscode, const char* message)
            {
                gameConsole.pushMessage("LuaError", std::string("<Main> :: ") + message, 255, 0, 0);
                std::cout << "[LuaError]<Main> : " << "[CODE::" << statuscode << "] : " << message << std::endl;
            });
            Script::hookCore.dropValue("World", &world);

            //Socket
            Network::NetworkHandler networkHandler;

            //Keybinding
            Input::KeyBinder keybind;
            Script::hookCore.dropValue("KeyBinder", &keybind);
            keybind.loadFromFile(configFile);

            //Editor Grid
            EditorGrid editorGrid(32, 32);
            keybind.setActionDelay("MagnetizeUp", 200);
            keybind.setActionDelay("MagnetizeRight", 200);
            keybind.setActionDelay("MagnetizeDown", 200);
            keybind.setActionDelay("MagnetizeLeft", 200);

            //GUI
            sf::Event event;
            tgui::Gui gui(window);
            gui.setFont("Data/Fonts/weblysleekuil.ttf");
            tgui::Theme baseTheme;
            baseTheme.load("Data/GUI/obe.style");

            //Main Editor GUI
            tgui::Panel::Ptr mainPanel = tgui::Panel::create();

            //Toolbar
            tgui::Panel::Ptr titlePanel = tgui::Panel::create();
            tgui::Label::Ptr titleLabel = tgui::Label::create();
            tgui::Label::Ptr infoLabel = tgui::Label::create();
            tgui::Label::Ptr savedLabel = tgui::Label::create();
            tgui::Button::Ptr editorButton = tgui::Button::create();
            tgui::ComboBox::Ptr cameraMode = tgui::ComboBox::create();
            tgui::ComboBox::Ptr editMode = tgui::ComboBox::create();

            //Requires Panel
            tgui::Panel::Ptr requiresPanel = tgui::Panel::create();
            tgui::Button::Ptr requiresCloseButton = tgui::Button::create();
            tgui::Label::Ptr requiresTitleLabel = tgui::Label::create();
            tgui::Panel::Ptr requiresPanelContent = tgui::Panel::create();

            //Editor GUI
            tgui::Panel::Ptr editorPanel = tgui::Panel::create();
            tgui::Panel::Ptr mapPanel = tgui::Panel::create();
            tgui::Panel::Ptr settingsPanel = tgui::Panel::create();
            tgui::Panel::Ptr spritesPanel = tgui::Panel::create();
            tgui::Panel::Ptr objectsPanel = tgui::Panel::create();
            tgui::Button::Ptr mapButton = tgui::Button::create();
            tgui::Button::Ptr settingsButton = tgui::Button::create();
            tgui::Button::Ptr spritesButton = tgui::Button::create();
            tgui::Button::Ptr objectsButton = tgui::Button::create();
            tgui::Label::Ptr mapCatLabel = tgui::Label::create();
            tgui::Label::Ptr settingsCatLabel = tgui::Label::create();
            tgui::Label::Ptr spritesCatLabel = tgui::Label::create();
            tgui::Label::Ptr objectsCatLabel = tgui::Label::create();

            //Map Settings GUI
            tgui::Label::Ptr mapNameLabel = tgui::Label::create();
            tgui::TextBox::Ptr mapNameInput = tgui::TextBox::create();
            tgui::Button::Ptr mapNameButton = tgui::Button::create();

            //Editor Settings GUI
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

            //Map Editor
            Graphics::LevelSprite* hoveredSprite = nullptr;
            Graphics::LevelSprite* selectedSprite = nullptr;
            Graphics::LevelSprite::HandlePoint* selectedHandlePoint = nullptr;
            sf::FloatRect sdBoundingRect;
            int selectedSpriteOffsetX = 0;
            int selectedSpriteOffsetY = 0;
            int selectedSpritePickPosX = 0;
            int selectedSpritePickPosY = 0;
            bool guiEditorEnabled = false;
            int cameraSpeed = 30;
            int currentLayer = 1;
            Collision::PolygonalCollider* selectedMasterCollider = nullptr;
            int colliderPtGrabbed = -1;
            bool masterColliderGrabbed = false;
            sf::Text sprInfo;
            sprInfo.setFont(font);
            sprInfo.setCharacterSize(16);
            sprInfo.setFillColor(sf::Color::White);
            sf::RectangleShape sprInfoBackground(sf::Vector2f(100, 160));
            sprInfoBackground.setFillColor(sf::Color(0, 0, 0, 200));
            double waitForMapSaving = -1;

            //Font size setup
            unsigned int bigFontSize = static_cast<double>(window.getSize().y) / static_cast<double>(32.0) - 6;
            unsigned int mediumFontSize = static_cast<double>(bigFontSize) / 1.3;
            unsigned int smallFontSize = static_cast<double>(bigFontSize) / 2.0;

            //Requires Setup
            requiresPanel->add(requiresPanelContent, "content");
            requiresPanel->add(requiresTitleLabel, "label");
            requiresPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
            requiresPanel->setSize("&.w / 3", "&.h / 1.5");
            requiresPanel->setPosition("&.w / 2 - width / 2", "&.h / 2 - height / 2");
            requiresPanel->hide();

            requiresCloseButton->setRenderer(baseTheme.getRenderer("CloseButton"));
            requiresCloseButton->setSize("32", "32");
            requiresCloseButton->setPosition("&.width - 40", "8");
            requiresCloseButton->connect("pressed", [&requiresPanel]()
            {
                requiresPanel->hide();
            });
            requiresPanel->add(requiresCloseButton);

            requiresTitleLabel->setPosition(30, 15);
            requiresTitleLabel->setTextSize(bigFontSize);
            requiresTitleLabel->setRenderer(baseTheme.getRenderer("Label"));
            requiresTitleLabel->setText("Object builder Window");

            requiresPanelContent->setRenderer(baseTheme.getRenderer("TransparentPanel"));
            requiresPanelContent->setSize("&.w - 2", "&.h - 62");
            requiresPanelContent->setPosition(0, 60);

            //GUI Setup
            int saveEditMode = -1;
            gui.add(mainPanel);
            mainPanel->setSize(window.getSize().x, window.getSize().y);
            mainPanel->add(titlePanel);
            mainPanel->add(editorPanel);
            mainPanel->add(requiresPanel);

            //Titlebar setup
            titlePanel->add(titleLabel, "titleLabel");
            titlePanel->add(infoLabel, "cursorPosLabel");
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

            editorButton->connect("pressed", [&guiEditorEnabled]() { guiEditorEnabled = !guiEditorEnabled; });

            //Editor Menu Setup
            editorPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
            editorPanel->setSize("&.w - 100", "&.h - 100");
            editorPanel->setPosition(50, 70);

            editorPanel->add(mapPanel, "mapPanel");
            editorPanel->add(settingsPanel, "settingsPanel");
            editorPanel->add(spritesPanel, "spritesPanel");
            editorPanel->add(objectsPanel, "objectsPanel");
            editorPanel->add(mapButton, "mapButton");
            editorPanel->add(settingsButton, "settingsButton");
            editorPanel->add(spritesButton, "spritesPanel");
            editorPanel->add(objectsButton, "objectsPanel");

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

            mapButton->connect("pressed", [&baseTheme, &mapButton, &settingsButton, &spritesButton, &objectsButton,
                                   &mapPanel, &settingsPanel, &spritesPanel, &objectsPanel]()
            {
                mapPanel->show();
                settingsPanel->hide();
                spritesPanel->hide();
                objectsPanel->hide();
                mapButton->setRenderer(baseTheme.getRenderer("SelectedButton"));
                settingsButton->setRenderer(baseTheme.getRenderer("Button"));
                spritesButton->setRenderer(baseTheme.getRenderer("Button"));
                objectsButton->setRenderer(baseTheme.getRenderer("Button"));
            });

            settingsButton->connect("pressed", [&baseTheme, &mapButton, &settingsButton, &spritesButton, &objectsButton,
                                        &mapPanel, &settingsPanel, &spritesPanel, &objectsPanel]()
            {
                mapPanel->hide();
                settingsPanel->show();
                spritesPanel->hide();
                objectsPanel->hide();
                mapButton->setRenderer(baseTheme.getRenderer("Button"));
                settingsButton->setRenderer(baseTheme.getRenderer("SelectedButton"));
                spritesButton->setRenderer(baseTheme.getRenderer("Button"));
                objectsButton->setRenderer(baseTheme.getRenderer("Button"));
            });

            spritesButton->connect("pressed", [&baseTheme, &mapButton, &settingsButton, &spritesButton, &objectsButton,
                                       &mapPanel, &settingsPanel, &spritesPanel, &objectsPanel]()
            {
                mapPanel->hide();
                settingsPanel->hide();
                spritesPanel->show();
                objectsPanel->hide();
                mapButton->setRenderer(baseTheme.getRenderer("Button"));
                settingsButton->setRenderer(baseTheme.getRenderer("Button"));
                spritesButton->setRenderer(baseTheme.getRenderer("SelectedButton"));
                objectsButton->setRenderer(baseTheme.getRenderer("Button"));
            });

            objectsButton->connect("pressed", [&baseTheme, &mapButton, &settingsButton, &spritesButton, &objectsButton,
                                       &mapPanel, &settingsPanel, &spritesPanel, &objectsPanel]()
            {
                mapPanel->hide();
                settingsPanel->hide();
                spritesPanel->hide();
                objectsPanel->show();
                mapButton->setRenderer(baseTheme.getRenderer("Button"));
                settingsButton->setRenderer(baseTheme.getRenderer("Button"));
                spritesButton->setRenderer(baseTheme.getRenderer("Button"));
                objectsButton->setRenderer(baseTheme.getRenderer("SelectedButton"));
            });

            //Map Tab Setup
            mapPanel->add(mapCatLabel);
            mapPanel->add(mapNameLabel);
            mapPanel->add(mapNameInput);
            mapPanel->add(mapNameButton);

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
            mapNameButton->connect("pressed", [&baseTheme, &world, &mapNameInput]()
            {
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


            //Settings Tab Setup
            settingsPanel->add(settingsCatLabel);

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

            enableGridCheckbox->connect("checked", [&baseTheme, &snapGridCheckbox]()
            {
                snapGridCheckbox->enable();
                snapGridCheckbox->setRenderer(baseTheme.getRenderer("CheckBox"));
            });

            enableGridCheckbox->connect("unchecked", [&baseTheme, &snapGridCheckbox]()
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

            gridDimensionButton->connect("pressed", [&baseTheme, &gridDimensionXInput, &gridDimensionYInput, &editorGrid]()
            {
                gridDimensionXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                gridDimensionYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                if (Functions::String::isStringInt(gridDimensionXInput->getText()) && Functions::String::isStringInt(gridDimensionYInput->getText()))
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
                if (!Functions::String::isStringInt(gridDimensionXInput->getText()))
                {
                    gridDimensionXInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
                }
                if (!Functions::String::isStringInt(gridDimensionYInput->getText()))
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

            gridOffsetButton->connect("pressed", [&baseTheme, &gridOffsetXInput, &gridOffsetYInput, &editorGrid]()
            {
                if (Functions::String::isStringInt(gridOffsetXInput->getText()) && Functions::String::isStringInt(gridOffsetYInput->getText()))
                {
                    std::string xGridOffset = gridOffsetXInput->getText();
                    std::string yGridOffset = gridOffsetYInput->getText();
                    editorGrid.setOffset(stoi(xGridOffset), stoi(yGridOffset));
                    gridOffsetXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                    gridOffsetYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                    return;
                }
                if (!Functions::String::isStringInt(gridOffsetXInput->getText()))
                {
                    gridOffsetXInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
                }
                if (!Functions::String::isStringInt(gridOffsetYInput->getText()))
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

            snapGridCheckbox->connect("checked", [&editMode, &editorGrid, &cursor]()
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

            //Sprites Tab Setup
            spritesPanel->add(spritesCatLabel);

            spritesCatLabel->setPosition(20, 20);
            spritesCatLabel->setTextSize(bigFontSize);
            spritesCatLabel->setRenderer(baseTheme.getRenderer("Label"));
            spritesCatLabel->setText("[ Sprites Settings ]");

            Editor::loadSpriteFolder(spritesPanel, spritesCatLabel, "");

            //Objects Tab Setup
            objectsPanel->add(objectsCatLabel);

            objectsCatLabel->setPosition(20, 20);
            objectsCatLabel->setTextSize(bigFontSize);
            objectsCatLabel->setRenderer(baseTheme.getRenderer("Label"));
            objectsCatLabel->setText("[ Objects Settings ]");

            Editor::buildObjectTab(objectsPanel, requiresPanel, baseTheme);

            //Framerate / DeltaTime
            Time::FPSCounter fps;
            fps.loadFont(font);
            Time::FramerateManager framerateManager(gameConfig);
            window.setVerticalSyncEnabled(framerateManager.isVSyncEnabled());

            Light::initLights();

            world.loadFromFile(mapName);

            mapNameInput->setText(world.getLevelName());

            //Game Starts
            while (window.isOpen())
            {
                framerateManager.update();
                if (waitForMapSaving >= 0)
                {
                    waitForMapSaving += framerateManager.getDeltaTime();
                    if (waitForMapSaving > 1 && waitForMapSaving < 2)
                    {
                        savedLabel->hideWithEffect(tgui::ShowAnimationType::SlideFromTop, sf::Time(sf::seconds(0.5)));
                        waitForMapSaving = 2;
                    }
                    else if (waitForMapSaving > 3)
                        waitForMapSaving = -1;
                }
                    

                //GUI Actions
                keybind.setEnabled(!gameConsole.isConsoleVisible());
                if (keybind.isActionToggled("CamMovable"))
                    cameraMode->setSelectedItemByIndex(0);
                else if (keybind.isActionToggled("CamFree"))
                    cameraMode->setSelectedItemByIndex(1);

                if (keybind.isActionToggled("SpriteMode"))
                {
                    editMode->setSelectedItemByIndex(0);
                }
                else if (keybind.isActionToggled("CollisionMode"))
                {
                    editMode->setSelectedItemByIndex(1);
                }

                drawFPS = displayFramerateCheckbox->isChecked();

                if (guiEditorEnabled && saveEditMode < 0)
                {
                    saveEditMode = editMode->getSelectedItemIndex();
                    editMode->setSelectedItemByIndex(3);
                }
                else if (!guiEditorEnabled && saveEditMode > 0)
                {
                    editMode->setSelectedItemByIndex(saveEditMode);
                    saveEditMode = -1;
                }

                Coord::UnitVector pixelCamera = world.getCamera()->getPosition().to<Coord::Units::WorldPixels>();
                //Updates
                if (!gameConsole.isConsoleVisible())
                {
                    if (cameraMode->getSelectedItem() == "Movable Camera")
                    {
                        world.setCameraLock(true);
                        if (keybind.isActionEnabled("CamLeft") && keybind.isActionEnabled("CamRight"))
                        {
                        }
                        else if (keybind.isActionEnabled("CamLeft"))
                            world.getCamera()->move(Coord::UnitVector(-cameraSpeed * framerateManager.getGameSpeed(), 0, Coord::Units::WorldPixels));
                        else if (keybind.isActionEnabled("CamRight"))
                            world.getCamera()->move(Coord::UnitVector(cameraSpeed * framerateManager.getGameSpeed(), 0, Coord::Units::WorldPixels));

                        if (keybind.isActionEnabled("CamUp") && keybind.isActionEnabled("CamDown"))
                        {
                        }
                        else if (keybind.isActionEnabled("CamUp"))
                            world.getCamera()->move(Coord::UnitVector(0, -cameraSpeed * framerateManager.getGameSpeed(), Coord::Units::WorldPixels));
                        else if (keybind.isActionEnabled("CamDown"))
                            world.getCamera()->move(Coord::UnitVector(0, cameraSpeed * framerateManager.getGameSpeed(), Coord::Units::WorldPixels));

                        if (keybind.isActionEnabled("CamDash"))
                            cameraSpeed = 3000;
                        else
                            cameraSpeed = 900;
                    }
                    else
                    {
                        world.setCameraLock(false);
                    }
                }

                //Sprite Editing
                if (editMode->getSelectedItem() == "LevelSprites")
                {
                    world.enableShowCollision(true, true, false, false);

                    if (selectedHandlePoint != nullptr && cursor.getPressed(System::CursorButton::Left))
                    {
                        std::cout << "Moving ref : " << selectedHandlePoint->getReferencial() << std::endl;
                        selectedHandlePoint->moveTo(cursor.getX(), cursor.getY());
                        
                    }
                    else if (selectedHandlePoint != nullptr && cursor.getReleased(System::CursorButton::Left))
                    {
                        selectedHandlePoint = nullptr;
                    }
                    else
                    {
                        //Layer Change
                        if (selectedSprite == nullptr && keybind.isActionToggled("LayerInc"))
                        {
                            currentLayer += 1;
                            world.getCamera()->scale(1.1);
                            if (hoveredSprite != nullptr)
                            {
                                hoveredSprite->setColor(sf::Color::White);
                                hoveredSprite = nullptr;
                                sprInfo.setString("");
                            }
                        }
                        if (selectedSprite == nullptr && keybind.isActionToggled("LayerDec"))
                        {
                            world.getCamera()->scale(0.9);
                            currentLayer -= 1;
                            if (hoveredSprite != nullptr)
                            {
                                hoveredSprite->setColor(sf::Color::White);
                                hoveredSprite = nullptr;
                                sprInfo.setString("");
                            }
                        }
                        //Sprite Hover
                        if (hoveredSprite == nullptr)
                        {
                            hoveredSprite = world.getSpriteByPos(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, currentLayer);
                            if (hoveredSprite != nullptr && hoveredSprite != selectedSprite)
                            {
                                hoveredSprite = world.getSpriteByPos(cursor.getX() + pixelCamera.x,
                                    cursor.getY() + pixelCamera.y, currentLayer);
                                sdBoundingRect = hoveredSprite->getRect();
                                hoveredSprite->setColor(sf::Color(0, 255, 255));
                                std::string sprInfoStr;
                                sprInfoStr = "Hovered Sprite : \n";
                                sprInfoStr += "    ID : " + hoveredSprite->getID() + "\n";
                                sprInfoStr += "    Name : " + hoveredSprite->getPath() + "\n";
                                sprInfoStr += "    Pos : " + std::to_string(hoveredSprite->getX()) + "," + std::to_string(hoveredSprite->getY()) + "\n";
                                sprInfoStr += "    Size : " + std::to_string(hoveredSprite->getWidth()) + "," + std::to_string(hoveredSprite->getHeight()) + "\n";
                                sprInfoStr += "    Rot : " + std::to_string(hoveredSprite->getRotation()) + "\n";
                                sprInfoStr += "    Layer / Z : " + std::to_string(hoveredSprite->getLayer()) + "," + std::to_string(hoveredSprite->getZDepth()) + "\n";
                                sprInfo.setString(sprInfoStr);
                                sprInfoBackground.setSize(sf::Vector2f(sprInfo.getGlobalBounds().width + 20, sprInfo.getGlobalBounds().height - 10));
                            }
                            else
                                hoveredSprite == nullptr;
                        }
                        else if (hoveredSprite != nullptr)
                        {
                            sprInfoBackground.setPosition(cursor.getX() + 40, cursor.getY());
                            sprInfo.setPosition(cursor.getX() + 50, cursor.getY());
                            bool outHover = false;
                            Graphics::LevelSprite* testHoverSprite = world.getSpriteByPos(cursor.getX() + pixelCamera.x,
                                                                                        cursor.getY() + pixelCamera.y, currentLayer);
                            if (testHoverSprite != hoveredSprite)
                                outHover = true;
                            if (outHover)
                            {
                                if (hoveredSprite != selectedSprite)
                                    hoveredSprite->setColor(sf::Color::White);
                                hoveredSprite = nullptr;
                                sprInfo.setString("");
                            }
                        }

                        //Sprite Pick
                        if (cursor.getClicked(System::CursorButton::Left))
                        {
                            if (selectedSprite != nullptr)
                            {
                                std::cout << "Picky picky :D" << std::endl;
                                selectedHandlePoint = selectedSprite->getHandlePoint(pixelCamera, cursor.getX(), cursor.getY());
                                std::cout << selectedHandlePoint << ", " << hoveredSprite << ", " << selectedSprite << std::endl;
                                if (selectedHandlePoint != nullptr)
                                {
                                    std::cout << "POINT POINT POINT" << std::endl;
                                    hoveredSprite = nullptr;
                                }
                                else if (hoveredSprite != selectedSprite)
                                {
                                    std::cout << "Unselect" << std::endl;
                                    selectedSprite->setColor(sf::Color::White);
                                    selectedSprite->unselect();
                                    sprInfo.setString("");
                                    selectedSprite = nullptr;
                                    selectedSpriteOffsetX = 0;
                                    selectedSpriteOffsetY = 0;
                                }
                                std::cout << "Ended NonEf" << std::endl;
                            }
                            if (hoveredSprite != nullptr)
                            {
                                std::cout << "MUCH WOW" << std::endl;
                                selectedSprite = hoveredSprite;
                                selectedSpriteOffsetX = (cursor.getX() + pixelCamera.x) - selectedSprite->getPosition().to<Coord::Units::WorldPixels>().x;
                                selectedSpriteOffsetY = (cursor.getY() + pixelCamera.y) - selectedSprite->getPosition().to<Coord::Units::WorldPixels>().y;
                                selectedSpritePickPosX = selectedSprite->getPosition().to<Coord::Units::WorldPixels>().x;
                                selectedSpritePickPosY = selectedSprite->getPosition().to<Coord::Units::WorldPixels>().y;
                                selectedSprite->select();

                                sdBoundingRect = selectedSprite->getRect();
                                selectedSprite->setColor(sf::Color(100, 255, 100));
                            }
                        }

                        
                        //Sprite Scale
                        /*if (cursor.getPressed("Left") && selectedSprite != nullptr)
                        {
                            selectedSprite->setZDepth(selectedSprite->getZDepth() + 1);
                            world.reorganizeLayers();
                        }*/
                        //Sprite Move
                        if (cursor.getPressed(System::CursorButton::Left) && selectedSprite != nullptr && selectedHandlePoint == nullptr)
                        {
                            if (selectedSprite->getParentID().empty())
                            {
                                selectedSprite->setPosition(Coord::UnitVector(cursor.getX() + pixelCamera.x - selectedSpriteOffsetX,
                                                                                    cursor.getY() + pixelCamera.y - selectedSpriteOffsetY, Coord::Units::WorldPixels));
                            }
                            else
                            {
                                std::cout << "Not empty : '" << selectedSprite->getParentID() << "'" << std::endl;
                                // What to do here ?
                            }
                            sdBoundingRect = selectedSprite->getRect();
                            std::string sprInfoStr;
                            sprInfoStr = "Hovered Sprite : \n";
                            sprInfoStr += "    ID : " + selectedSprite->getID() + "\n";
                            sprInfoStr += "    Name : " + selectedSprite->getPath() + "\n";
                            sprInfoStr += "    Pos : " + std::to_string(selectedSprite->getX()) + "," + std::to_string(selectedSprite->getY()) + "\n";
                            sprInfoStr += "    Size : " + std::to_string(selectedSprite->getWidth()) + "," + std::to_string(selectedSprite->getHeight()) + "\n";
                            sprInfoStr += "    Rot : " + std::to_string(selectedSprite->getRotation()) + "\n";
                            sprInfoStr += "    Layer / Z : " + std::to_string(selectedSprite->getLayer()) + "," + std::to_string(selectedSprite->getZDepth()) + "\n";
                            sprInfo.setString(sprInfoStr);
                            sprInfoBackground.setSize(sf::Vector2f(sprInfo.getGlobalBounds().width + 20, sprInfo.getGlobalBounds().height - 10));
                            sprInfoBackground.setPosition(cursor.getX() + 40, cursor.getY());
                            sprInfo.setPosition(cursor.getX() + 50, cursor.getY());
                        }

                        //Sprite Rotate (Non-fonctionnal)
                        if ((keybind.isActionEnabled("RotateLeft") || keybind.isActionEnabled("RotateRight")) && selectedSprite != nullptr)
                        {
                            if (keybind.isActionEnabled("RotateLeft") && selectedSprite != nullptr)
                            {
                                //selectedSprite->rotate(-1 * framerateManager.getGameSpeed());
                                selectedSprite->scale(2 * framerateManager.getGameSpeed(), 2 * framerateManager.getGameSpeed());
                            }
                                
                            if (keybind.isActionEnabled("RotateRight") && selectedSprite != nullptr)
                            {
                                //selectedSprite->rotate(1 * framerateManager.getGameSpeed());
                                selectedSprite->scale(-2 * framerateManager.getGameSpeed(), -2 * framerateManager.getGameSpeed());
                            }
                        }

                        /*if ((keybind.isActionEnabled("ScaleInc") || keybind.isActionEnabled("ScaleDec")) && selectedSprite != nullptr)
                        {
                            if (keybind.isActionEnabled("ScaleDec"))
                                selectedSprite->scale(-0.05 * framerateManager.getGameSpeed() * selectedSprite->getScaleX(), -0.05 * framerateManager.getGameSpeed() * selectedSprite->getScaleY());
                            if (keybind.isActionEnabled("ScaleInc"))
                                selectedSprite->scale(0.05 * framerateManager.getGameSpeed() * selectedSprite->getScaleX(), 0.05 * framerateManager.getGameSpeed() * selectedSprite->getScaleY());
                        }*/

                        //Sprite Layer / Z-Depth
                        if (cursor.getPressed(System::CursorButton::Left) && selectedSprite != nullptr && keybind.isActionToggled("ZInc"))
                        {
                            selectedSprite->setZDepth(selectedSprite->getZDepth() + 1);
                            world.reorganizeLayers();
                        }
                        if (cursor.getPressed(System::CursorButton::Left) && selectedSprite != nullptr && keybind.isActionToggled("ZDec"))
                        {
                            selectedSprite->setZDepth(selectedSprite->getZDepth() - 1);
                            world.reorganizeLayers();
                        }
                        if (cursor.getPressed(System::CursorButton::Left) && selectedSprite != nullptr && keybind.isActionToggled("LayerInc"))
                        {
                            selectedSprite->setLayer(selectedSprite->getLayer() + 1);
                            currentLayer += 1;
                            world.reorganizeLayers();
                        }
                        if (cursor.getPressed(System::CursorButton::Left) && selectedSprite != nullptr && keybind.isActionToggled("LayerDec"))
                        {
                            selectedSprite->setLayer(selectedSprite->getLayer() - 1);
                            currentLayer -= 1;
                            world.reorganizeLayers();
                        }

                        //Sprite Cancel Offset
                        if (cursor.getPressed(System::CursorButton::Left) && selectedSprite != nullptr && keybind.isActionToggled("CancelOffset"))
                        {
                            selectedSpriteOffsetX = 0;
                            selectedSpriteOffsetY = 0;
                        }

                        //Sprite Delete
                        if (selectedSprite != nullptr && keybind.isActionToggled("DeleteSprite"))
                        {
                            world.deleteSprite(selectedSprite);
                            selectedSprite = nullptr;
                            sprInfo.setString("");
                            hoveredSprite = nullptr;
                            selectedSpriteOffsetX = 0;
                            selectedSpriteOffsetY = 0;
                        }
                    }
                }
                else
                {
                    if (selectedSprite != nullptr)
                        selectedSprite->setColor(sf::Color::White);
                    selectedSprite = nullptr;
                    hoveredSprite = nullptr;
                    selectedSpriteOffsetX = 0;
                    selectedSpriteOffsetY = 0;
                    sprInfo.setString("");
                }

                //Collision Edition
                if (editMode->getSelectedItem() == "Collisions")
                {
                    bool deletedCollision = false;
                    world.enableShowCollision(true, true, true, true);
                    if (selectedMasterCollider != nullptr)
                    {
                        selectedMasterCollider->clearHighlights();
                        int cursCoordX = cursor.getX() + pixelCamera.x;
                        int cursCoordY = cursor.getY() + pixelCamera.y;
                        int clNode = selectedMasterCollider->findClosestPoint(cursCoordX, cursCoordY);
                        selectedMasterCollider->highlightPoint(clNode);
                        int gLeftNode = ((clNode - 1 != -1) ? clNode - 1 : selectedMasterCollider->getPointsAmount() - 1);
                        int gRghtNode = ((clNode + 1 != selectedMasterCollider->getPointsAmount()) ? clNode + 1 : 0);
                        int secondClosestNode = (selectedMasterCollider->getDistanceFromPoint(gLeftNode, cursCoordX, cursCoordY) >= selectedMasterCollider->getDistanceFromPoint(gRghtNode, cursCoordX, cursCoordY)) ? gRghtNode : gLeftNode;
                        selectedMasterCollider->highlightPoint(secondClosestNode);
                    }
                    //Collision Point Grab
                    if (cursor.getClicked(System::CursorButton::Left) && colliderPtGrabbed == -1 &&
                        world.getCollisionPointByPos(cursor.getX() + pixelCamera.x,
                                                     cursor.getY() + pixelCamera.y).first != nullptr)
                    {
                        std::pair<Collision::PolygonalCollider*, int> selectedPtCollider;
                        selectedPtCollider = world.getCollisionPointByPos(cursor.getX() + pixelCamera.x,
                                                                          cursor.getY() + pixelCamera.y);
                        if (selectedMasterCollider != nullptr && selectedMasterCollider != selectedPtCollider.first)
                        {
                            selectedMasterCollider->setSelected(false);
                            selectedMasterCollider = nullptr;
                            masterColliderGrabbed = false;
                            colliderPtGrabbed = -1;
                        }
                        selectedMasterCollider = selectedPtCollider.first;
                        selectedMasterCollider->setSelected(true);
                        colliderPtGrabbed = selectedPtCollider.second;
                    }
                    //Collision Point Move
                    if (cursor.getPressed(System::CursorButton::Left) && selectedMasterCollider != nullptr && !masterColliderGrabbed && colliderPtGrabbed != -1)
                    {
                        selectedMasterCollider->setPointPosition(colliderPtGrabbed, cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y);
                        if (colliderPtGrabbed == 0 && selectedMasterCollider->getParentID() != "" && world.getGameObject(selectedMasterCollider->getParentID())->canDisplay())
                        {
                            world.getGameObject(selectedMasterCollider->getParentID())->getLevelSprite()->setPosition(
                                cursor.getX() + pixelCamera.x,
                                cursor.getY() + pixelCamera.y);
                        }
                    }
                    //Collision Point Release
                    if (cursor.getReleased(System::CursorButton::Left))
                    {
                        colliderPtGrabbed = -1;
                    }
                    //Collision Master Grab
                    if (cursor.getClicked(System::CursorButton::Left) && world.getCollisionMasterByPos(cursor.getX() + pixelCamera.x,
                                                                                   cursor.getY() + pixelCamera.y) != nullptr)
                    {
                        Collision::PolygonalCollider* tempCol = world.getCollisionMasterByPos(cursor.getX() + pixelCamera.x,
                                                                                              cursor.getY() + pixelCamera.y);
                        if (selectedMasterCollider != nullptr && selectedMasterCollider != tempCol)
                        {
                            selectedMasterCollider->setSelected(false);
                            selectedMasterCollider = nullptr;
                            masterColliderGrabbed = false;
                            colliderPtGrabbed = -1;
                        }
                        selectedMasterCollider = tempCol;
                        selectedMasterCollider->setSelected(true);
                        if (selectedMasterCollider->getParentID() != "") world.getGameObject(selectedMasterCollider->getParentID())->setUpdateState(false);
                        masterColliderGrabbed = true;
                    }
                    //Collision Master Move
                    if (cursor.getPressed(System::CursorButton::Left) && selectedMasterCollider != nullptr && masterColliderGrabbed)
                    {
                        selectedMasterCollider->setPositionFromMaster(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y);
                        if (selectedMasterCollider->getParentID() != "" && world.getGameObject(selectedMasterCollider->getParentID())->canDisplay())
                        {
                            ClipperLib::IntPoint zeroCoords = selectedMasterCollider->getPointPosition(0);
                            ClipperLib::IntPoint masterCoords = selectedMasterCollider->getMasterPointPosition();
                            world.getGameObject(selectedMasterCollider->getParentID())->getLevelSprite()->setPosition(
                                cursor.getX() + pixelCamera.x + zeroCoords.X - masterCoords.X,
                                cursor.getY() + pixelCamera.y + zeroCoords.Y - masterCoords.Y);
                        }
                    }
                    //Collision Master Release
                    if (cursor.getReleased(System::CursorButton::Left) && masterColliderGrabbed)
                    {
                        masterColliderGrabbed = false;
                        if (selectedMasterCollider->getParentID() != "") world.getGameObject(selectedMasterCollider->getParentID())->setUpdateState(true);
                    }
                    if (cursor.getClicked(System::CursorButton::Right) && selectedMasterCollider != nullptr && !masterColliderGrabbed)
                    {
                        int crPtX = cursor.getX() + pixelCamera.x;
                        int crPtY = cursor.getY() + pixelCamera.y;
                        int rqPtRes = selectedMasterCollider->hasPoint(crPtX, crPtY, 6, 6);
                        //Collision Point Create
                        if (rqPtRes == -1)
                        {
                            selectedMasterCollider->addPoint(crPtX, crPtY, selectedMasterCollider->findClosestPoint(crPtX, crPtY, true));
                        }
                        //Collision Point Delete
                        else
                        {
                            selectedMasterCollider->deletePoint(rqPtRes);
                            if (selectedMasterCollider->getPointsAmount() <= 2)
                            {
                                selectedMasterCollider->setSelected(false);
                                world.deleteCollisionByID(selectedMasterCollider->getID());
                                selectedMasterCollider = nullptr;
                                masterColliderGrabbed = false;
                                colliderPtGrabbed = -1;
                                deletedCollision = true;
                            }
                        }
                    }
                    //Collision Release
                    if (cursor.getClicked(System::CursorButton::Left) && selectedMasterCollider != nullptr)
                    {
                        if (world.getCollisionMasterByPos(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y) == nullptr)
                        {
                            if (world.getCollisionPointByPos(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y).first == nullptr)
                            {
                                selectedMasterCollider->setSelected(false);
                                selectedMasterCollider = nullptr;
                                masterColliderGrabbed = false;
                                colliderPtGrabbed = -1;
                            }
                        }
                    }
                    //Collision Delete
                    if (cursor.getClicked(System::CursorButton::Right) && selectedMasterCollider != nullptr && masterColliderGrabbed)
                    {
                        selectedMasterCollider->setSelected(false);
                        world.deleteCollisionByID(selectedMasterCollider->getID());
                        selectedMasterCollider = nullptr;
                        masterColliderGrabbed = false;
                        colliderPtGrabbed = -1;
                        deletedCollision = true;
                    }
                    //Collision Create
                    if (cursor.getClicked(System::CursorButton::Right) && selectedMasterCollider == nullptr && !deletedCollision)
                    {
                        world.createCollisionAtPos(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y);
                    }
                }

                //GUI Update
                infoLabel->setText(
                    "Cursor : (" + 
                        std::to_string(cursor.getX()) + ", " + std::to_string(cursor.getY()) + 
                    ")" +
                    std::string("   Camera : (") + 
                        std::to_string(int(pixelCamera.x)) + ", " + std::to_string(int(pixelCamera.y)) + 
                    ")" +
                    std::string("   Sum : (") + 
                        std::to_string(int(pixelCamera.x) + int(cursor.getX())) + ", " + std::to_string(int(pixelCamera.y) + int(cursor.getY())) + 
                    ")" +
                    std::string("   Layer : ") + std::to_string(currentLayer)
                );

                if (enableGridCheckbox->isChecked())
                {
                    if (keybind.isActionEnabled("MagnetizeUp")) editorGrid.moveMagnet(cursor, 0, -1);
                    if (keybind.isActionEnabled("MagnetizeRight")) editorGrid.moveMagnet(cursor, 1, 0);
                    if (keybind.isActionEnabled("MagnetizeDown")) editorGrid.moveMagnet(cursor, 0, 1);
                    if (keybind.isActionEnabled("MagnetizeLeft")) editorGrid.moveMagnet(cursor, -1, 0);
                    if (keybind.isActionEnabled("MagnetizeCursor"))
                        editorGrid.magnetize(cursor);
                }

                //Console Command Handle
                if (gameConsole.hasCommand())
                    world.getScriptEngine()->dostring(gameConsole.getCommand());

                //Click&Press Trigger
                if (editMode->getSelectedItem() == "Play")
                {
                    if (cursor.getClicked(System::CursorButton::Left) || cursor.getPressed(System::CursorButton::Left))
                    {
                        std::vector<Script::GameObject*> clickableGameObjects = world.getAllGameObjects({"Click"});
                        std::vector<Collision::PolygonalCollider*> elementsCollidedByCursor = world.getAllCollidersByCollision(
                            &cursorCollider, -pixelCamera.x, -pixelCamera.y);
                        for (int i = 0; i < elementsCollidedByCursor.size(); i++)
                        {
                            for (int j = 0; j < clickableGameObjects.size(); j++)
                            {
                                if (elementsCollidedByCursor[i] == clickableGameObjects[j]->getCollider())
                                {
                                    if (cursor.getClicked(System::CursorButton::Left))
                                        world.getGameObject(clickableGameObjects[j]->getID())->getLocalTriggers()->setTriggerState("Click", true);
                                    if (cursor.getPressed(System::CursorButton::Left))
                                        world.getGameObject(clickableGameObjects[j]->getID())->getLocalTriggers()->setTriggerState("Press", true);
                                }
                            }
                        }
                    }
                }

                if (guiEditorEnabled)
                    editorPanel->show();
                else
                    editorPanel->hide();

                //Events
                Script::TriggerDatabase::GetInstance()->update();
                world.update(framerateManager.getGameSpeed());
                textDisplay.update(framerateManager.getGameSpeed());
                keybind.update();
                cursor.update();
                if (drawFPS) fps.uTick();
                if (drawFPS && framerateManager.doRender()) fps.tick();

                //Triggers Handling
                networkHandler.handleTriggers();
                cursor.handleTriggers();
                keybind.handleTriggers();

                while (window.pollEvent(event))
                {
                    switch (event.type)
                    {
                    case sf::Event::Closed:
                        window.close();
                        break;

                    case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Escape)
                            window.close();
                        if (event.key.code == sf::Keyboard::Return)
                        {
                            if (textDisplay.textRemaining() && !gameConsole.isConsoleVisible())
                                textDisplay.next();
                        }
                        if (event.key.code == sf::Keyboard::S)
                        {
                            if (event.key.control)
                            {
                                world.saveData()->writeFile(world.getBaseFolder() + "/Data/Maps/" + mapName, true);
                                if (waitForMapSaving < 0)
                                {
                                    savedLabel->showWithEffect(tgui::ShowAnimationType::SlideFromTop, sf::Time(sf::seconds(0.5)));
                                    waitForMapSaving = 0;
                                }
                                    
                            }
                        }
                        if (event.key.code == sf::Keyboard::V)
                        {
                            if (event.key.control)
                            {
                                std::string clipboard_content = "";
                                gameConsole.insertInputBufferContent(clipboard_content);
                            }
                        }
                        if (event.key.code == sf::Keyboard::F1)
                            gameConsole.setConsoleVisibility(!gameConsole.isConsoleVisible());
                        if (event.key.code == sf::Keyboard::Up)
                            gameConsole.upHistory();
                        if (event.key.code == sf::Keyboard::Down)
                            gameConsole.downHistory();
                        if (event.key.code == sf::Keyboard::Left && gameConsole.isConsoleVisible())
                            gameConsole.moveCursor(-1);
                        if (event.key.code == sf::Keyboard::Right && gameConsole.isConsoleVisible())
                            gameConsole.moveCursor(1);
                        break;
                    case sf::Event::TextEntered:
                        if (gameConsole.isConsoleVisible())
                            gameConsole.inputKey(event.text.unicode);
                        break;
                    case sf::Event::MouseWheelMoved:
                        if (event.mouseWheel.delta >= scrollSensitive)
                        {
                            gameConsole.scroll(-1);
                        }
                        else if (event.mouseWheel.delta <= -scrollSensitive)
                        {
                            gameConsole.scroll(1);
                        }
                        break;
                    }
                    gui.handleEvent(event);
                }
                //Draw Everything Here
                if (framerateManager.doRender())
                {
                    window.clear();
                    world.display(window);
                    //Show Collision
                    if (editMode->getSelectedItem() == "Collisions")
                        world.enableShowCollision(true);
                    else
                        world.enableShowCollision(false);
                    //Game Display
                    if (hoveredSprite != nullptr)
                    {
                        sf::RectangleShape sprBorder = sf::RectangleShape(sf::Vector2f(sdBoundingRect.width, sdBoundingRect.height));
                        sprBorder.setPosition(sdBoundingRect.left - pixelCamera.x, sdBoundingRect.top - pixelCamera.y);
                        sprBorder.setFillColor(sf::Color(0, 0, 0, 0));
                        sprBorder.setOutlineColor(sf::Color(255, 0, 0));
                        sprBorder.setOutlineThickness(2);
                        window.draw(sprBorder);
                    }
                    if (enableGridCheckbox->isChecked())
                        editorGrid.draw(window, cursor, -pixelCamera.x, -pixelCamera.y);
                    //HUD & GUI
                    if (sprInfo.getString() != "")
                    {
                        window.draw(sprInfoBackground);
                        window.draw(sprInfo);
                    }
                    gui.draw();
					if (drawFPS)
						fps.draw(window);

                    if (textDisplay.textRemaining())
                        textDisplay.render(&window);

                    //Console
                    if (gameConsole.isConsoleVisible())
                        gameConsole.display(&window);

                    //Cursor
                    if (showCursor)
                        window.draw(*cursor.getSprite());
                        
                    window.display();
                }
            }
            window.close();
        }
    }
}
