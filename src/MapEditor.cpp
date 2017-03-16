//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "MapEditor.hpp"

namespace obe
{
	namespace Editor
	{
		void editMap(std::string mapName)
		{
			double startLoadTime = Time::getTickSinceEpoch();

			std::cout << "<System> Creating window with resolution " << Functions::Coord::width << "x" << Functions::Coord::height << std::endl;

			//Creating Window
			sf::RenderWindow window(sf::VideoMode(Functions::Coord::width, Functions::Coord::height), "ObEngine", sf::Style::Fullscreen);
			window.setKeyRepeatEnabled(false);
			window.setMouseCursorVisible(false);
			sf::Texture loadingTexture; loadingTexture.loadFromFile("Sprites/Menus/loading.png"); loadingTexture.setSmooth(true);
			sf::Sprite loadingSprite; loadingSprite.setTexture(loadingTexture);
			loadingSprite.setScale((double)Functions::Coord::width / (double)Functions::Coord::viewWidth,
				(double)Functions::Coord::height / (double)Functions::Coord::viewHeight);
			sf::Font loadingFont; loadingFont.loadFromFile("Data/Fonts/weblysleekuil.ttf");
			sf::Text loadingText; loadingText.setFont(loadingFont);
			loadingText.setCharacterSize(70.0 * (double)Functions::Coord::height / (double)Functions::Coord::viewHeight);
			loadingText.setPosition(348.0 * (double)Functions::Coord::width / (double)Functions::Coord::viewWidth,
				595.0 * (double)Functions::Coord::height / (double)Functions::Coord::viewHeight);
			vili::DataParser loadingStrDP("Sprites/Menus/loading.vili");
			std::string loadingRandomStr = *loadingStrDP.at<vili::ListAttribute>("Loading", "loadingStr")->get(
				Functions::Math::randint(0, loadingStrDP.at<vili::ListAttribute>("Loading", "loadingStr")->getSize() - 1));
			loadingText.setString(loadingRandomStr);
			window.draw(loadingSprite); window.draw(loadingText); window.display();

			Script::hookCore.dropValue("TriggerDatabase", Script::TriggerDatabase::GetInstance());
			Graphics::TextRenderer textDisplay;
			textDisplay.createRenderer("Shade", "MapSaver");
			Script::hookCore.dropValue("TextDisplay", &textDisplay);

			//Console
			Console::Console gameConsole;
			Script::hookCore.dropValue("Console", &gameConsole);

			//Font
			sf::Font font;
			font.loadFromFile("Data/Fonts/arial.ttf");

			//Config
			vili::DataParser configFile;
			System::Path("Data/config.cfg.vili").loadResource(&configFile, System::Loaders::dataLoader);
			vili::ComplexAttribute* gameConfig = configFile->at("GameConfig");
			int scrollSensitive = *gameConfig->at<vili::BaseAttribute>("scrollSensibility");
			vili::ComplexAttribute* developpement = configFile->at("Developpement");
			bool showChar = *developpement->at<vili::BaseAttribute>("showCharacter");
			bool showCol = *developpement->at<vili::BaseAttribute>("showCollisions");
			bool showLSpr = *developpement->at<vili::BaseAttribute>("showLevelSprites");
			bool showOverlay = *developpement->at<vili::BaseAttribute>("showOverlay");
			bool showCursor = *developpement->at<vili::BaseAttribute>("showCursor");
			bool drawFPS = *developpement->at<vili::BaseAttribute>("showFPS");

			//Cursor
			Cursor::Cursor cursor(&window);
			cursor.selectCursor("RoundWhite");
			Collision::PolygonalCollider cursorCollider("cursor");
			cursorCollider.addPoint(0, 0); cursorCollider.addPoint(1, 0); cursorCollider.addPoint(1, 1); cursorCollider.addPoint(0, 1);
			cursor.updateOutsideWindow(true);
			Script::hookCore.dropValue("Cursor", &cursor);

			//World Creation / Loading
			World::World world;
			(*world.getScriptEngine())["stream"] = gameConsole.createStream("World", true);
			world.getScriptEngine()->setErrorHandler([&gameConsole](int statuscode, const char* message) {
				gameConsole.pushMessage("LuaError", std::string("<Main> :: ") + message, 255, 0, 0);
				std::cout << "[LuaError]<Main> : " << "[CODE::" << statuscode << "] : " << message << std::endl;
			});
			Script::hookCore.dropValue("World", &world);

			//Socket
			Input::NetworkHandler networkHandler;

			//Keybinding
			Input::KeyBinder keybind;
			Script::hookCore.dropValue("KeyBinder", &keybind);
			keybind.loadFromFile(&configFile);

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
			tgui::Label::Ptr cursorPosLabel = tgui::Label::create();
			tgui::Label::Ptr cameraPosLabel = tgui::Label::create();
			tgui::Label::Ptr absolutePosLabel = tgui::Label::create();
			tgui::Label::Ptr layerLabel = tgui::Label::create();
			tgui::Button::Ptr editorButton = tgui::Button::create();
			tgui::ComboBox::Ptr cameraMode = tgui::ComboBox::create();
			tgui::ComboBox::Ptr editMode = tgui::ComboBox::create();

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
			tgui::Label::Ptr mapSizeLabel = tgui::Label::create();
			tgui::Label::Ptr mapNameLabel = tgui::Label::create();
			tgui::TextBox::Ptr mapNameInput = tgui::TextBox::create();
			tgui::Button::Ptr mapNameButton = tgui::Button::create();
			tgui::TextBox::Ptr mapSizeXInput = tgui::TextBox::create();
			tgui::TextBox::Ptr mapSizeYInput = tgui::TextBox::create();
			tgui::Button::Ptr mapSizeButton = tgui::Button::create();

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

			//Map Editor
			Graphics::LevelSprite* hoveredSprite = nullptr;
			Graphics::LevelSprite* selectedSprite = nullptr;
			sf::FloatRect sdBoundingRect;
			int selectedSpriteOffsetX = 0;
			int selectedSpriteOffsetY = 0;
			int selectedSpritePickPosX = 0;
			int selectedSpritePickPosY = 0;
			bool guiEditorEnabled = false;
			bool addSpriteMode = false;
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

			//GUI Setup
			int saveEditMode = -1;
			gui.add(mainPanel);
			mainPanel->setSize(window.getSize().x, window.getSize().y);
			mainPanel->add(titlePanel);
			mainPanel->add(editorPanel);
			
			//Titlebar setup
			unsigned int bigFontSize = (double)window.getSize().y / (double)32.0 - 6;
			unsigned int mediumFontSize = (double)bigFontSize / 1.3;
			unsigned int smallFontSize = (double)bigFontSize / 2.0;

			titlePanel->add(titleLabel, "titleLabel");
			titlePanel->add(cursorPosLabel, "cursorPosLabel");
			titlePanel->add(cameraPosLabel, "cameraPosLabel");
			titlePanel->add(absolutePosLabel, "absolutePosLabel");
			titlePanel->add(layerLabel, "layerLabel");
			titlePanel->add(editorButton, "editorButton");
			titlePanel->add(editMode, "editMode");
			titlePanel->add(cameraMode, "cameraMode");

			titlePanel->setRenderer(baseTheme.getRenderer("TransparentPanel"));
			titlePanel->setSize("&.w", "&.h / 30");
			titlePanel->setPosition(0, 0);

			titleLabel->setPosition("120", 0);
			titleLabel->setTextSize(bigFontSize);
			titleLabel->setRenderer(baseTheme.getRenderer("Label"));
			titleLabel->setText("ÖbEngine Map Editor");

			cursorPosLabel->setPosition(tgui::bindRight(titleLabel) + 60, 5);
			cursorPosLabel->setTextSize(mediumFontSize);
			cursorPosLabel->setRenderer(baseTheme.getRenderer("Label"));
			cursorPosLabel->setText("Cursor : (1920, 1080)");

			cameraPosLabel->setPosition(tgui::bindRight(cursorPosLabel) + 60, 5);
			cameraPosLabel->setTextSize(mediumFontSize);
			cameraPosLabel->setRenderer(baseTheme.getRenderer("Label"));
			cameraPosLabel->setText("Camera : (10000, 10000)");

			absolutePosLabel->setPosition(tgui::bindRight(cameraPosLabel) + 60, 5);
			absolutePosLabel->setTextSize(mediumFontSize);
			absolutePosLabel->setRenderer(baseTheme.getRenderer("Label"));
			absolutePosLabel->setText("Sum : (10000, 10000)");

			layerLabel->setPosition(tgui::bindRight(absolutePosLabel) + 60, 5);
			layerLabel->setTextSize(mediumFontSize);
			layerLabel->setRenderer(baseTheme.getRenderer("Label"));
			layerLabel->setText("Layer : 10");

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
			editMode->setPosition(tgui::bindLeft(cameraMode) - tgui::bindWidth(editMode) - 1, 0);
			editMode->setSize("200", "&.h");
			editMode->setTextSize(mediumFontSize);
			editMode->setRenderer(baseTheme.getRenderer("ComboBox"));

			editorButton->setPosition(tgui::bindLeft(editMode) - tgui::bindWidth(editorButton) - 1, 0);
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

			settingsButton->setPosition(tgui::bindRight(mapButton), 0);
			settingsButton->setSize("&.w / 10", 30);
			settingsButton->setRenderer(baseTheme.getRenderer("Button"));
			settingsButton->setText("Settings");
			settingsButton->setTextSize(mediumFontSize);

			spritesButton->setPosition(tgui::bindRight(settingsButton), 0);
			spritesButton->setSize("&.w / 10", 30);
			spritesButton->setRenderer(baseTheme.getRenderer("Button"));
			spritesButton->setText("Sprites");
			spritesButton->setTextSize(mediumFontSize);

			objectsButton->setPosition(tgui::bindRight(spritesButton), 0);
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
				&mapPanel, &settingsPanel, &spritesPanel, &objectsPanel]() { 
				mapPanel->show(); settingsPanel->hide(); spritesPanel->hide(); objectsPanel->hide();
				mapButton->setRenderer(baseTheme.getRenderer("SelectedButton"));
				settingsButton->setRenderer(baseTheme.getRenderer("Button"));
				spritesButton->setRenderer(baseTheme.getRenderer("Button"));
				objectsButton->setRenderer(baseTheme.getRenderer("Button"));
			});

			settingsButton->connect("pressed", [&baseTheme, &mapButton, &settingsButton, &spritesButton, &objectsButton,
				&mapPanel, &settingsPanel, &spritesPanel, &objectsPanel]() {
				mapPanel->hide(); settingsPanel->show(); spritesPanel->hide(); objectsPanel->hide();
				mapButton->setRenderer(baseTheme.getRenderer("Button"));
				settingsButton->setRenderer(baseTheme.getRenderer("SelectedButton"));
				spritesButton->setRenderer(baseTheme.getRenderer("Button"));
				objectsButton->setRenderer(baseTheme.getRenderer("Button"));
			});

			spritesButton->connect("pressed", [&baseTheme, &mapButton, &settingsButton, &spritesButton, &objectsButton,
				&mapPanel, &settingsPanel, &spritesPanel, &objectsPanel]() {
				mapPanel->hide(); settingsPanel->hide(); spritesPanel->show(); objectsPanel->hide();
				mapButton->setRenderer(baseTheme.getRenderer("Button"));
				settingsButton->setRenderer(baseTheme.getRenderer("Button"));
				spritesButton->setRenderer(baseTheme.getRenderer("SelectedButton"));
				objectsButton->setRenderer(baseTheme.getRenderer("Button"));
			});

			objectsButton->connect("pressed", [&baseTheme, &mapButton, &settingsButton, &spritesButton, &objectsButton,
				&mapPanel, &settingsPanel, &spritesPanel, &objectsPanel]() {
				mapPanel->hide(); settingsPanel->hide(); spritesPanel->hide(); objectsPanel->show();
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
			mapPanel->add(mapSizeLabel);
			mapPanel->add(mapSizeXInput);
			mapPanel->add(mapSizeYInput);
			mapPanel->add(mapSizeButton);
			
			mapCatLabel->setPosition(20, 20);
			mapCatLabel->setTextSize(bigFontSize);
			mapCatLabel->setRenderer(baseTheme.getRenderer("Label"));
			mapCatLabel->setText("[ Map Settings ]");

			mapNameLabel->setPosition(60, tgui::bindBottom(mapCatLabel) + 20);
			mapNameLabel->setTextSize(mediumFontSize);
			mapNameLabel->setRenderer(baseTheme.getRenderer("Label"));
			mapNameLabel->setText("Map Name : ");

			mapNameInput->setPosition(tgui::bindRight(mapNameLabel) + 20, tgui::bindTop(mapNameLabel));
			mapNameInput->setSize(160, mediumFontSize + 4);
			mapNameInput->setRenderer(baseTheme.getRenderer("TextBox"));

			mapNameButton->setPosition(tgui::bindRight(mapNameInput) + 20, tgui::bindTop(mapNameLabel) + 4);
			mapNameButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
			mapNameButton->setSize(16, 16);
			mapNameButton->connect("pressed", [&baseTheme, &world, &mapNameInput]() {
				if (mapNameInput->getText() != "") {
					world.setLevelName(mapNameInput->getText());
					mapNameInput->setRenderer(baseTheme.getRenderer("TextBox"));
				}
				else {
					mapNameInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
				}
			});

			mapSizeLabel->setPosition(60, tgui::bindBottom(mapNameLabel) + 20);
			mapSizeLabel->setTextSize(mediumFontSize);
			mapSizeLabel->setRenderer(baseTheme.getRenderer("Label"));
			mapSizeLabel->setText("Map Size : ");

			mapSizeXInput->setPosition(tgui::bindRight(mapSizeLabel) + 20, tgui::bindTop(mapSizeLabel));
			mapSizeXInput->setSize(80, mediumFontSize + 4);
			mapSizeXInput->setRenderer(baseTheme.getRenderer("TextBox"));

			mapSizeYInput->setPosition(tgui::bindRight(mapSizeXInput) + 20, tgui::bindTop(mapSizeLabel));
			mapSizeYInput->setSize(80, mediumFontSize + 4);
			mapSizeYInput->setRenderer(baseTheme.getRenderer("TextBox"));

			mapSizeButton->setPosition(tgui::bindRight(mapSizeYInput) + 20, tgui::bindTop(mapSizeLabel) + 4);
			mapSizeButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
			mapSizeButton->setSize(16, 16);

			mapSizeButton->connect("pressed", [&baseTheme, &mapSizeXInput, &mapSizeYInput, &world]() {
				if (Functions::String::isStringInt(mapSizeXInput->getText()) && Functions::String::isStringInt(mapSizeYInput->getText())) {
					std::string xMapSize = mapSizeXInput->getText();
					std::string yMapSize = mapSizeYInput->getText();
					world.setSize(std::stoi(xMapSize), std::stoi(yMapSize));
					mapSizeXInput->setRenderer(baseTheme.getRenderer("TextBox"));
					mapSizeYInput->setRenderer(baseTheme.getRenderer("TextBox"));
					return;
				}
				if (!Functions::String::isStringInt(mapSizeXInput->getText())) {
					mapSizeXInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
				}
				if (!Functions::String::isStringInt(mapSizeYInput->getText())) {
					mapSizeYInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
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
			
			settingsCatLabel->setPosition(20, 20);
			settingsCatLabel->setTextSize(bigFontSize);
			settingsCatLabel->setRenderer(baseTheme.getRenderer("Label"));
			settingsCatLabel->setText("[ Global Settings ]");

			displayFramerateCheckbox->setPosition(60, tgui::bindBottom(settingsCatLabel) + 20);
			displayFramerateCheckbox->setRenderer(baseTheme.getRenderer("CheckBox"));
			displayFramerateCheckbox->setSize(16, 16);
			displayFramerateCheckbox->setTextSize(mediumFontSize);
			displayFramerateCheckbox->setText("Display Framerate ?");

			enableGridCheckbox->setPosition(60, tgui::bindBottom(displayFramerateCheckbox) + 20);
			enableGridCheckbox->setRenderer(baseTheme.getRenderer("CheckBox"));
			enableGridCheckbox->setSize(16, 16);
			enableGridCheckbox->setTextSize(mediumFontSize);
			enableGridCheckbox->setText("Enabled Grid ?");

			gridDimensionLabel->setPosition(60, tgui::bindBottom(enableGridCheckbox) + 20);
			gridDimensionLabel->setTextSize(mediumFontSize);
			gridDimensionLabel->setRenderer(baseTheme.getRenderer("Label"));
			gridDimensionLabel->setText("Grid Cell Size : ");

			gridDimensionXInput->setPosition(tgui::bindRight(gridDimensionLabel) + 20, tgui::bindTop(gridDimensionLabel));
			gridDimensionXInput->setSize(80, mediumFontSize + 4);
			gridDimensionXInput->setRenderer(baseTheme.getRenderer("TextBox"));

			gridDimensionYInput->setPosition(tgui::bindRight(gridDimensionXInput) + 20, tgui::bindTop(gridDimensionLabel));
			gridDimensionYInput->setSize(80, mediumFontSize + 4);
			gridDimensionYInput->setRenderer(baseTheme.getRenderer("TextBox"));

			gridDimensionButton->setPosition(tgui::bindRight(gridDimensionYInput) + 20, tgui::bindTop(gridDimensionLabel) + 4);
			gridDimensionButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
			gridDimensionButton->setSize(16, 16);

			gridDimensionButton->connect("pressed", [&baseTheme, &gridDimensionXInput, &gridDimensionYInput, &editorGrid]() {
				if (Functions::String::isStringInt(gridDimensionXInput->getText()) && Functions::String::isStringInt(gridDimensionYInput->getText())) {
					std::string xGridSize = gridDimensionXInput->getText();
					std::string yGridSize = gridDimensionYInput->getText();
					editorGrid.setSize(std::stoi(xGridSize), std::stoi(yGridSize));
					gridDimensionXInput->setRenderer(baseTheme.getRenderer("TextBox"));
					gridDimensionYInput->setRenderer(baseTheme.getRenderer("TextBox"));
					return;
				}
				if (!Functions::String::isStringInt(gridDimensionXInput->getText())) {
					gridDimensionXInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
				}
				if (!Functions::String::isStringInt(gridDimensionYInput->getText())) {
					gridDimensionYInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
				}
			});

			gridOffsetLabel->setPosition(60, tgui::bindBottom(gridDimensionLabel) + 20);
			gridOffsetLabel->setTextSize(mediumFontSize);
			gridOffsetLabel->setRenderer(baseTheme.getRenderer("Label"));
			gridOffsetLabel->setText("Grid Cell Offset : ");

			gridOffsetXInput->setPosition(tgui::bindRight(gridOffsetLabel) + 20, tgui::bindTop(gridOffsetLabel));
			gridOffsetXInput->setSize(80, mediumFontSize + 4);
			gridOffsetXInput->setRenderer(baseTheme.getRenderer("TextBox"));

			gridOffsetYInput->setPosition(tgui::bindRight(gridOffsetXInput) + 20, tgui::bindTop(gridOffsetLabel));
			gridOffsetYInput->setSize(80, mediumFontSize + 4);
			gridOffsetYInput->setRenderer(baseTheme.getRenderer("TextBox"));

			gridOffsetButton->setPosition(tgui::bindRight(gridOffsetYInput) + 20, tgui::bindTop(gridOffsetLabel) + 4);
			gridOffsetButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
			gridOffsetButton->setSize(16, 16);

			gridOffsetButton->connect("pressed", [&baseTheme, &gridOffsetXInput, &gridOffsetYInput, &editorGrid]() {
				if (Functions::String::isStringInt(gridOffsetXInput->getText()) && Functions::String::isStringInt(gridOffsetYInput->getText())) {
					std::string xGridOffset = gridOffsetXInput->getText();
					std::string yGridOffset = gridOffsetYInput->getText();
					editorGrid.setOffset(std::stoi(xGridOffset), std::stoi(yGridOffset));
					gridOffsetXInput->setRenderer(baseTheme.getRenderer("TextBox"));
					gridOffsetYInput->setRenderer(baseTheme.getRenderer("TextBox"));
					return;
				}
				if (!Functions::String::isStringInt(gridOffsetXInput->getText())) {
					gridOffsetXInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
				}
				if (!Functions::String::isStringInt(gridOffsetYInput->getText())) {
					gridOffsetYInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
				}
			});

			//Sprites Tab Setup
			spritesPanel->add(spritesCatLabel);

			spritesCatLabel->setPosition(20, 20);
			spritesCatLabel->setTextSize(bigFontSize);
			spritesCatLabel->setRenderer(baseTheme.getRenderer("Label"));
			spritesCatLabel->setText("[ Sprites Settings ]");

			EditorTools::loadSpriteFolder(spritesPanel, spritesCatLabel, "");

			//Objects Tab Setup
			objectsPanel->add(objectsCatLabel);

			objectsCatLabel->setPosition(20, 20);
			objectsCatLabel->setTextSize(bigFontSize);
			objectsCatLabel->setRenderer(baseTheme.getRenderer("Label"));
			objectsCatLabel->setText("[ Objects Settings ]");

			EditorTools::buildObjectTab(objectsPanel, baseTheme);

			//Framerate / DeltaTime
			Time::FPSCounter fps;
			fps.loadFont(font);
			FramerateManager framerateManager(*gameConfig);
			window.setVerticalSyncEnabled(framerateManager.isVSyncEnabled());

			Light::initLights();

			world.loadFromFile(mapName);
			
			mapNameInput->setText(world.getLevelName());
			mapSizeXInput->setText(std::to_string(world.getSizeX()));
			mapSizeYInput->setText(std::to_string(world.getSizeY()));

			mapSizeButton->connect("pressed", [&world, &mapSizeXInput, &mapSizeYInput]() {
				std::string dimSX = mapSizeXInput->getText();
				std::string dimSY = mapSizeYInput->getText();
				int dimX = std::stoi(dimSX != "" ? dimSX : "1920");
				int dimY = std::stoi(dimSY != "" ? dimSY : "1080");
				world.setSize(dimX, dimY);
			});

			//Game Starts
			while (window.isOpen())
			{
				framerateManager.update();

				//GUI Actions
				keybind.setEnabled(!gameConsole.isConsoleVisible());
				if (keybind.isActionToggled("CamMovable"))
					cameraMode->setSelectedItemByIndex(0);
				else if (keybind.isActionToggled("CamFree"))
					cameraMode->setSelectedItemByIndex(1);

				if (keybind.isActionToggled("SpriteMode"))
				{
					editMode->setSelectedItemByIndex(0);
					editMode = 0;
				}
				else if (keybind.isActionToggled("CollisionMode"))
				{
					editMode->setSelectedItemByIndex(1);
				}

				drawFPS = displayFramerateCheckbox->isChecked();

				if (guiEditorEnabled && saveEditMode < 0) {
					saveEditMode = editMode->getSelectedItemIndex();
					editMode->setSelectedItemByIndex(3);
				}
				else if (!guiEditorEnabled && saveEditMode > 0) {
					editMode->setSelectedItemByIndex(saveEditMode);
					saveEditMode = -1;
				}
					

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
							world.setCameraPosition(world.getCamX() - (cameraSpeed * framerateManager.getGameSpeed()), world.getCamY());
						else if (keybind.isActionEnabled("CamRight"))
							world.setCameraPosition(world.getCamX() + (cameraSpeed * framerateManager.getGameSpeed()), world.getCamY());

						if (keybind.isActionEnabled("CamUp") && keybind.isActionEnabled("CamDown"))
						{
						}
						else if (keybind.isActionEnabled("CamUp"))
							world.setCameraPosition(world.getCamX(), world.getCamY() - (cameraSpeed * framerateManager.getGameSpeed()));
						else if (keybind.isActionEnabled("CamDown"))
							world.setCameraPosition(world.getCamX(), world.getCamY() + (cameraSpeed * framerateManager.getGameSpeed()));

						if (keybind.isActionEnabled("CamDash"))
							cameraSpeed = 60;
						else
							cameraSpeed = 30;
					}
					else {
						world.setCameraLock(false);
					}

					if (keybind.isActionToggled("Reset"))
					{
						/*world.getCharacter(0)->setPos(world.getStartX(), world.getStartY());
						world.getCharacter(0)->cancelMoves();*/
					}
				}

				if (editMode->getSelectedItem() != "LevelSprites")
				{
					if (selectedSprite != nullptr)
						selectedSprite->setColor(sf::Color::White);
					selectedSprite = nullptr;
					hoveredSprite = nullptr;
					selectedSpriteOffsetX = 0;
					selectedSpriteOffsetY = 0;
					sprInfo.setString("");
				}

				//Sprite Editing
				if (editMode->getSelectedItem() == "LevelSprites")
				{
					world.enableShowCollision(true, true, false, false);

					//Layer Change
					if (selectedSprite == nullptr && keybind.isActionToggled("LayerInc"))
					{
						currentLayer += 1;
						if (hoveredSprite != nullptr)
						{
							hoveredSprite->setColor(sf::Color::White);
							hoveredSprite = nullptr;
							sprInfo.setString("");
						}
					}
					if (selectedSprite == nullptr && keybind.isActionToggled("LayerDec"))
					{
						currentLayer -= 1;
						if (hoveredSprite != nullptr)
						{
							hoveredSprite->setColor(sf::Color::White);
							hoveredSprite = nullptr;
							sprInfo.setString("");
						}
					}
					//Sprite Hover
					if (hoveredSprite == nullptr && selectedSprite == nullptr)
					{
						if (world.getSpriteByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY(), currentLayer) != nullptr)
						{
							hoveredSprite = world.getSpriteByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY(), currentLayer);
							sdBoundingRect = hoveredSprite->getRect();
							hoveredSprite->setColor(sf::Color(0, 60, 255));
							std::string sprInfoStr;
							sprInfoStr = "Hovered Sprite : \n";
							sprInfoStr += "    ID : " + hoveredSprite->getID() + "\n";
							sprInfoStr += "    Name : " + hoveredSprite->getName() + "\n";
							sprInfoStr += "    Pos : " + std::to_string(hoveredSprite->getX()) + "," + std::to_string(hoveredSprite->getY()) + "\n";
							sprInfoStr += "    Size : " + std::to_string(hoveredSprite->getW()) + "," + std::to_string(hoveredSprite->getH()) + "\n";
							sprInfoStr += "    Rot : " + std::to_string(hoveredSprite->getRotation()) + "\n";
							sprInfoStr += "    Layer / Z : " + std::to_string(hoveredSprite->getLayer()) + "," + std::to_string(hoveredSprite->getZDepth()) + "\n";
							sprInfo.setString(sprInfoStr);
							sprInfoBackground.setSize(sf::Vector2f(sprInfo.getGlobalBounds().width + 20, sprInfo.getGlobalBounds().height - 10));
						}
					}
					else if (hoveredSprite != nullptr && selectedSprite == nullptr)
					{
						sprInfoBackground.setPosition(cursor.getX() + 40, cursor.getY());
						sprInfo.setPosition(cursor.getX() + 50, cursor.getY());
						bool outHover = false;
						Graphics::LevelSprite* testHoverSprite = world.getSpriteByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY(), currentLayer);
						if (testHoverSprite != hoveredSprite)
							outHover = true;
						if (outHover)
						{
							hoveredSprite->setColor(sf::Color::White);
							hoveredSprite = nullptr;
							sprInfo.setString("");
						}
					}

					//Sprite Pick
					if (cursor.getClicked("Left"))
					{
						if (hoveredSprite != nullptr)
						{
							selectedSprite = hoveredSprite;
							selectedSpriteOffsetX = (cursor.getX() + world.getCamX()) - selectedSprite->getX();
							selectedSpriteOffsetY = (cursor.getY() + world.getCamY()) - selectedSprite->getY();
							selectedSpritePickPosX = selectedSprite->getX() - selectedSprite->getOffsetX();
							selectedSpritePickPosY = selectedSprite->getY() - selectedSprite->getOffsetY();

							sdBoundingRect = selectedSprite->getRect();
							selectedSprite->setColor(sf::Color(255, 0, 0));
						}
					}

					//Sprite Move
					if (cursor.getPressed("Left") && selectedSprite != nullptr)
					{
						if (selectedSprite->getParentID() == "")
						{
							selectedSprite->setPosition(cursor.getX() + world.getCamX() - selectedSpriteOffsetX,
								cursor.getY() + world.getCamY() - selectedSpriteOffsetY);
						}
						else
						{
							selectedSprite->setOffset(cursor.getX() + world.getCamX() - selectedSpriteOffsetX - selectedSpritePickPosX,
								cursor.getY() + world.getCamY() - selectedSpriteOffsetY - selectedSpritePickPosY);
						}
						sdBoundingRect = selectedSprite->getRect();
						std::string sprInfoStr;
						sprInfoStr = "Hovered Sprite : \n";
						sprInfoStr += "    ID : " + selectedSprite->getID() + "\n";
						sprInfoStr += "    Name : " + selectedSprite->getName() + "\n";
						sprInfoStr += "    Pos : " + std::to_string(selectedSprite->getX()) + "," + std::to_string(selectedSprite->getY()) + "\n";
						sprInfoStr += "    Size : " + std::to_string(selectedSprite->getW()) + "," + std::to_string(selectedSprite->getH()) + "\n";
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
							selectedSprite->rotate(-1 * framerateManager.getGameSpeed());
						if (keybind.isActionEnabled("RotateRight") && selectedSprite != nullptr)
							selectedSprite->rotate(1 * framerateManager.getGameSpeed());
					}

					//Sprite Scale
					if ((keybind.isActionEnabled("ScaleInc") || keybind.isActionEnabled("ScaleDec")) && selectedSprite != nullptr)
					{
						if (keybind.isActionEnabled("ScaleDec"))
							selectedSprite->scale(-0.05 * framerateManager.getGameSpeed() * selectedSprite->getScaleX(), -0.05 * framerateManager.getGameSpeed() * selectedSprite->getScaleY());
						if (keybind.isActionEnabled("ScaleInc"))
							selectedSprite->scale(0.05 * framerateManager.getGameSpeed()  * selectedSprite->getScaleX(), 0.05 * framerateManager.getGameSpeed() * selectedSprite->getScaleY());
					}

					//Sprite Drop
					if (cursor.getReleased("Left") && selectedSprite != nullptr)
					{
						selectedSprite->setColor(sf::Color::White);
						sprInfo.setString("");
						selectedSprite = nullptr;
						hoveredSprite = nullptr;
						selectedSpriteOffsetX = 0;
						selectedSpriteOffsetY = 0;
					}

					//Sprite Layer / Z-Depth
					if (cursor.getPressed("Left") && selectedSprite != nullptr && keybind.isActionToggled("ZInc"))
					{
						selectedSprite->setZDepth(selectedSprite->getZDepth() + 1);
						world.reorganizeLayers();
					}
					if (cursor.getPressed("Left") && selectedSprite != nullptr && keybind.isActionToggled("ZDec"))
					{
						selectedSprite->setZDepth(selectedSprite->getZDepth() - 1);
						world.reorganizeLayers();
					}
					if (cursor.getPressed("Left") && selectedSprite != nullptr && keybind.isActionToggled("LayerInc"))
					{
						selectedSprite->setLayer(selectedSprite->getLayer() + 1);
						currentLayer += 1;
						world.reorganizeLayers();
					}
					if (cursor.getPressed("Left") && selectedSprite != nullptr && keybind.isActionToggled("LayerDec"))
					{
						selectedSprite->setLayer(selectedSprite->getLayer() - 1);
						currentLayer -= 1;
						world.reorganizeLayers();
					}

					//Sprite Cancel Offset
					if (cursor.getPressed("Left") && selectedSprite != nullptr && keybind.isActionToggled("CancelOffset"))
					{
						selectedSpriteOffsetX = 0;
						selectedSpriteOffsetY = 0;
					}

					//Sprite Delete
					if (cursor.getPressed("Left") && selectedSprite != nullptr && keybind.isActionToggled("DeleteSprite"))
					{
						world.deleteSprite(selectedSprite);
						selectedSprite = nullptr;
						sprInfo.setString("");
						hoveredSprite = nullptr;
						selectedSpriteOffsetX = 0;
						selectedSpriteOffsetY = 0;
					}
				}

				//Collision Edition
				if (editMode->getSelectedItem() == "Collisions")
				{
					bool deletedCollision = false;
					world.enableShowCollision(true, true, true, true);
					if (selectedMasterCollider != nullptr)
					{
						selectedMasterCollider->clearHighlights();
						int cursCoordX = cursor.getX() + world.getCamX();
						int cursCoordY = cursor.getY() + world.getCamY();
						int clNode = selectedMasterCollider->findClosestPoint(cursCoordX, cursCoordY);
						selectedMasterCollider->highlightPoint(clNode);
						int gLeftNode = ((clNode - 1 != -1) ? clNode - 1 : selectedMasterCollider->getPointsAmount() - 1);
						int gRghtNode = ((clNode + 1 != selectedMasterCollider->getPointsAmount()) ? clNode + 1 : 0);
						int secondClosestNode = (selectedMasterCollider->getDistanceFromPoint(gLeftNode, cursCoordX, cursCoordY) >= selectedMasterCollider->getDistanceFromPoint(gRghtNode, cursCoordX, cursCoordY)) ? gRghtNode : gLeftNode;
						selectedMasterCollider->highlightPoint(secondClosestNode);
					}
					//Collision Point Grab
					if (cursor.getClicked("Left") && colliderPtGrabbed == -1 && world.getCollisionPointByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY()).first != nullptr)
					{
						std::pair<Collision::PolygonalCollider*, int> selectedPtCollider;
						selectedPtCollider = world.getCollisionPointByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
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
					if (cursor.getPressed("Left") && selectedMasterCollider != nullptr && !masterColliderGrabbed && colliderPtGrabbed != -1)
					{
						selectedMasterCollider->setPointPosition(colliderPtGrabbed, cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
						if (colliderPtGrabbed == 0 && selectedMasterCollider->getParentID() != "" && world.getGameObject(selectedMasterCollider->getParentID())->canDisplay())
						{
							world.getGameObject(selectedMasterCollider->getParentID())->getLevelSprite()->setPosition(
								cursor.getX() + world.getCamX(),
								cursor.getY() + world.getCamY());
						}
					}
					//Collision Point Release
					if (cursor.getReleased("Left"))
					{
						colliderPtGrabbed = -1;
					}
					//Collision Master Grab
					if (cursor.getClicked("Left") && world.getCollisionMasterByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY()) != nullptr)
					{
						Collision::PolygonalCollider* tempCol = world.getCollisionMasterByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
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
					if (cursor.getPressed("Left") && selectedMasterCollider != nullptr && masterColliderGrabbed)
					{
						selectedMasterCollider->setPositionFromMaster(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
						if (selectedMasterCollider->getParentID() != "" && world.getGameObject(selectedMasterCollider->getParentID())->canDisplay())
						{
							std::pair<int, int> zeroCoords = selectedMasterCollider->getPointPosition(0);
							std::pair<int, int> masterCoords = selectedMasterCollider->getMasterPointPosition();
							world.getGameObject(selectedMasterCollider->getParentID())->getLevelSprite()->setPosition(
								cursor.getX() + world.getCamX() + zeroCoords.first - masterCoords.first,
								cursor.getY() + world.getCamY() + zeroCoords.second - masterCoords.second);
						}
					}
					//Collision Master Release
					if (cursor.getReleased("Left") && masterColliderGrabbed)
					{
						masterColliderGrabbed = false;
						if (selectedMasterCollider->getParentID() != "") world.getGameObject(selectedMasterCollider->getParentID())->setUpdateState(true);
					}
					if (cursor.getClicked("Right") && selectedMasterCollider != nullptr && !masterColliderGrabbed)
					{
						int crPtX = cursor.getX() + world.getCamX();
						int crPtY = cursor.getY() + world.getCamY();
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
					if (cursor.getClicked("Left") && selectedMasterCollider != nullptr)
					{
						if (world.getCollisionMasterByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY()) == nullptr)
						{
							if (world.getCollisionPointByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY()).first == nullptr)
							{
								selectedMasterCollider->setSelected(false);
								selectedMasterCollider = nullptr;
								masterColliderGrabbed = false;
								colliderPtGrabbed = -1;
							}
						}
					}
					//Collision Delete
					if (cursor.getClicked("Right") && selectedMasterCollider != nullptr && masterColliderGrabbed)
					{
						selectedMasterCollider->setSelected(false);
						world.deleteCollisionByID(selectedMasterCollider->getID());
						selectedMasterCollider = nullptr;
						masterColliderGrabbed = false;
						colliderPtGrabbed = -1;
						deletedCollision = true;
					}
					//Collision Create
					if (cursor.getClicked("Right") && selectedMasterCollider == nullptr && !deletedCollision)
					{
						world.createCollisionAtPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
					}
				}

				//GUI Update
				/*GUI::Widget::getWidgetByID<GUI::Label>("cursorPos")->setComplexText("<color:255,255,255>Cursor : (<color:0,255,0>" + std::to_string(cursor.getX()) + "<color:255,255,255>"
					",<color:0,255,0>" + std::to_string(cursor.getY()) + "<color:255,255,255>)");
				GUI::Widget::getWidgetByID<GUI::Label>("camPos")->setComplexText("<color:255,255,255>Camera : (<color:0,255,0>" + std::to_string((int)world.getCamX()) + "<color:255,255,255>"
					",<color:0,255,0>" + std::to_string((int)world.getCamY()) + "<color:255,255,255>)");
				GUI::Widget::getWidgetByID<GUI::Label>("sumPos")->setComplexText("<color:255,255,255>Sum : (<color:0,255,0>" + 
					std::to_string((int)world.getCamX() + (int)cursor.getX()) + "<color:255,255,255>"
					",<color:0,255,0>" + std::to_string((int)world.getCamY() + (int)cursor.getY()) + "<color:255,255,255>)");
				GUI::Widget::getWidgetByID<GUI::Label>("currentLayer")->setComplexText("<color:255,255,255>Layer : <color:0,255,0>" + std::to_string(currentLayer));*/

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
				gameConsole.update();
				if (drawFPS) fps.uTick();
				if (drawFPS && framerateManager.doRender()) fps.tick();

				//Triggers Handling
				networkHandler.handleTriggers();
				cursor.handleTriggers();
				keybind.handleTriggers();

				if (enableGridCheckbox->isChecked())
				{
					editorGrid.setCamOffsetX(-world.getCamX());
					editorGrid.setCamOffsetY(-world.getCamY());
					editorGrid.sendCursorPosition(cursor.getX(), cursor.getY());
					if (keybind.isActionEnabled("MagnetizeUp")) editorGrid.moveMagnet(&cursor, 0, -1);
					if (keybind.isActionEnabled("MagnetizeRight")) editorGrid.moveMagnet(&cursor, 1, 0);
					if (keybind.isActionEnabled("MagnetizeDown")) editorGrid.moveMagnet(&cursor, 0, 1);
					if (keybind.isActionEnabled("MagnetizeLeft")) editorGrid.moveMagnet(&cursor, -1, 0);
					if (keybind.isActionEnabled("MagnetizeCursor"))
						editorGrid.magnetize(&cursor);
				}

				//Console Command Handle
				if (gameConsole.hasCommand())
					world.getScriptEngine()->dostring(gameConsole.getCommand());

				//Click&Press Trigger
				if (editMode->getSelectedItem() == "Play")
				{
					if (cursor.getClicked("Left") || cursor.getPressed("Left"))
					{
						std::vector<Script::GameObject*> clickableGameObjects = world.getAllGameObjects({ "Click" });
						std::vector<Collision::PolygonalCollider*> elementsCollidedByCursor = world.getAllCollidersByCollision(
							&cursorCollider, -world.getCamX(), -world.getCamY());
						for (int i = 0; i < elementsCollidedByCursor.size(); i++)
						{
							for (int j = 0; j < clickableGameObjects.size(); j++)
							{
								if (elementsCollidedByCursor[i] == clickableGameObjects[j]->getCollider())
								{
									if (cursor.getClicked("Left"))
										world.getGameObject(clickableGameObjects[j]->getID())->getLocalTriggers()->setTriggerState("Click", true);
									if (cursor.getPressed("Left"))
										world.getGameObject(clickableGameObjects[j]->getID())->getLocalTriggers()->setTriggerState("Press", true);
								}

							}
						}
					}
				}

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
									textDisplay.sendToRenderer("MapSaver", { { "text", "File <" + mapName + "> Saved !" } });
								}
							}
							if (event.key.code == sf::Keyboard::V)
							{
								if (event.key.control)
								{
									std::string clipboard_content;
									clip::get_text(clipboard_content);
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
					world.display(&window);
					//Show Collision
					if (editMode->getSelectedItem() == "Collisions")
						world.enableShowCollision(true);
					else
						world.enableShowCollision(false);
					//Game Display
					if (hoveredSprite != nullptr)
					{
						sf::RectangleShape sprBorder = sf::RectangleShape(sf::Vector2f(sdBoundingRect.width, sdBoundingRect.height));
						sprBorder.setPosition(sdBoundingRect.left - world.getCamX(), sdBoundingRect.top - world.getCamY());
						sprBorder.setFillColor(sf::Color(0, 0, 0, 0));
						sprBorder.setOutlineColor(sf::Color(255, 0, 0));
						sprBorder.setOutlineThickness(2);
						window.draw(sprBorder);
					}
					if (enableGridCheckbox->isChecked())
						editorGrid.draw(&window);
					//HUD & GUI
					if (sprInfo.getString() != "")
					{
						window.draw(sprInfoBackground);
						window.draw(sprInfo);
					}
					gui.draw();
					if (drawFPS)
						window.draw(fps.getFPS());

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