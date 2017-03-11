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

			//GUI
			sf::Event event;
			GUI::Container* gui = new GUI::Container(&event, &window, Functions::Coord::viewWidth, Functions::Coord::viewHeight);
			Script::hookCore.dropValue("GUI", gui);
			gui->createWidgetContainer("Main", 2, 0, 0, Functions::Coord::viewWidth, Functions::Coord::viewHeight, GUI::ContainerMovement::Fixed);
			gui->createWidgetContainer("Score", 2, 0, 0, 1920, 1080, GUI::ContainerMovement::Fixed); //DELETE THIS IT WAS FOR PONG
			gui->createLabel("Main", "title", Functions::Coord::width - 800, 5, "ObEngine Level Editor", "arial.ttf", 16, sf::Color(255, 255, 255));
			gui->createButton("Main", "editorMenuBtn", Functions::Coord::width - 570, 0, true, true, "GREY");
			GUI::ButtonEvent* menuOpened = GUI::Widget::getWidgetByID<GUI::Button>(std::string("editorMenuBtn"))->getHook();
			GUI::Widget::getWidgetByID<GUI::Button>(std::string("editorMenuBtn"))->setText("Menu Editeur", "arial.ttf", sf::Color(255, 255, 255), 14, true);
			std::vector<std::string> cameraMenuList = { "Movable Camera", "Free Camera" };
			gui->createDroplist("Main", "cameraMenuList", Functions::Coord::width - 190, 0, 12, "", false, "arial.ttf", "GREY", cameraMenuList);
			std::vector<std::string> editModeList = { "LevelSprites", "Collisions", "Play", "None" };
			gui->createDroplist("Main", "editModeList", Functions::Coord::width - 380, 0, 12, "", false, "arial.ttf", "GREY", editModeList);
			GUI::Widget::getWidgetByID<GUI::Droplist>("cameraMenuList")->setSelected(0);
			gui->createWidgetContainer("Editor", 3, 20, 40, Functions::Coord::viewWidth - 40, Functions::Coord::viewHeight - 80, GUI::ContainerMovement::Fixed);
			gui->getContainerByContainerName("Editor")->setBackground(sf::Color(0, 0, 0, 200));

			gui->createWidgetContainer("EditorSettings", 4, 20, 40, Functions::Coord::viewWidth - 40, Functions::Coord::viewHeight - 80, GUI::ContainerMovement::Fixed);
			gui->getContainerByContainerName("EditorSettings")->setBackground(sf::Color(0, 0, 0, 0));
			gui->createLabel("EditorSettings", "displayCatLbl", 25, 40, "Display Options", "arial.ttf", 25, sf::Color(255, 255, 255));
			gui->createLabel("EditorSettings", "editorCatLbl", 400, 40, "Editor Options", "arial.ttf", 25, sf::Color(255, 255, 255));
			gui->createLabel("EditorSettings", "mapCatLbl", 775, 40, "Map Options", "arial.ttf", 25, sf::Color(255, 255, 255));
			gui->createCheckbox("EditorSettings", "enableCharacterCB", 425, 80, "GREY", true);
			gui->createLabel("EditorSettings", "enableCharacterLbl", 450, 80, "Enable Character in Edit Mode", "arial.ttf", 12, sf::Color(255, 255, 255));
			gui->createCheckbox("EditorSettings", "enableFPSCB", 40, 105, "GREY", true);
			gui->createLabel("EditorSettings", "enableFPSLbl", 65, 105, "Enable FPS Counter", "arial.ttf", 12, sf::Color(255, 255, 255));
			gui->createCheckbox("EditorSettings", "enableGridCB", 425, 105, "GREY", false);
			bool* isGridEnabled = GUI::Widget::getWidgetByID<GUI::Checkbox>("enableGridCB")->getHook();
			gui->createLabel("EditorSettings", "enableGridLbl", 450, 105, "Enable Grid", "arial.ttf", 12, sf::Color(255, 255, 255));
			gui->createLabel("EditorSettings", "gridDimensionsLbl", 425, 130, "Dimensions :", "arial.ttf", 12, sf::Color(255, 255, 255));
			GUI::TextInput* guiGridDimX = gui->createTextInput("EditorSettings", "gridDimensionsEX", 505, 130, "", "arial.ttf", 13, sf::Color::White, false, "TINYGREY");
			guiGridDimX->addFilter(GUI::TextInputFilters::Integer);
			guiGridDimX->setText("32");
			gui->createLabel("EditorSettings", "gridDimensionsMULbl", 550, 130, "x", "arial.ttf", 12, sf::Color(255, 255, 255));
			GUI::TextInput* guiGridDimY = gui->createTextInput("EditorSettings", "gridDimensionsEY", 560, 130, "", "arial.ttf", 13, sf::Color::White, false, "TINYGREY");
			guiGridDimY->addFilter(GUI::TextInputFilters::Integer);
			guiGridDimY->setText("32");
			gui->createButton("EditorSettings", "gridDimensionsBtn", 610, 130, true, true, "APPLY");
			gui->createLabel("EditorSettings", "gridOffsetLbl", 425, 155, "Offset :", "arial.ttf", 12, sf::Color(255, 255, 255));
			GUI::TextInput* guiGridOffX = gui->createTextInput("EditorSettings", "gridOffsetEX", 505, 155, "", "arial.ttf", 13, sf::Color::White, false, "TINYGREY");
			guiGridOffX->addFilter(GUI::TextInputFilters::Integer);
			guiGridOffX->setText("0");
			gui->createLabel("EditorSettings", "gridOffsetMULbl", 550, 155, "x", "arial.ttf", 12, sf::Color(255, 255, 255));
			GUI::TextInput* guiGridOffY = gui->createTextInput("EditorSettings", "gridOffsetEY", 560, 155, "", "arial.ttf", 13, sf::Color::White, false, "TINYGREY");
			guiGridOffY->addFilter(GUI::TextInputFilters::Integer);
			guiGridOffY->setText("0");
			gui->createButton("EditorSettings", "gridOffsetBtn", 610, 155, true, true, "APPLY");
			gui->createLabel("EditorSettings", "mapDimensionsLbl", 800, 80, "Dimensions :", "arial.ttf", 12, sf::Color(255, 255, 255));
			GUI::TextInput* guiMapDimX = gui->createTextInput("EditorSettings", "mapDimensionsEX", 880, 80, "", "arial.ttf", 13, sf::Color::White, false, "TINYGREY");
			guiMapDimX->addFilter(GUI::TextInputFilters::Integer);
			gui->createLabel("EditorSettings", "mapDimensionsMULbl", 925, 80, "x", "arial.ttf", 12, sf::Color(255, 255, 255));
			GUI::TextInput* guiMapDimY = gui->createTextInput("EditorSettings", "mapDimensionsEY", 935, 80, "", "arial.ttf", 13, sf::Color::White, false, "TINYGREY");
			guiMapDimY->addFilter(GUI::TextInputFilters::Integer);
			gui->createButton("EditorSettings", "mapDimensionsBtn", 985, 80, true, true, "APPLY");

			GUI::WidgetContainer* editorSprites = gui->createWidgetContainer("EditorSprites", 4, 20, 40, Functions::Coord::viewWidth - 20, 
				Functions::Coord::viewHeight - 80, GUI::ContainerMovement::Fixed);
			editorSprites->setBackground(sf::Color(0, 0, 0, 0));
			editorSprites->addScrollBar();

			GUI::WidgetContainer* editorObjects = gui->createWidgetContainer("EditorObjects", 4, 20, 40, Functions::Coord::viewWidth - 20,
				Functions::Coord::viewHeight - 80, GUI::ContainerMovement::Fixed);
			editorObjects->setBackground(sf::Color(0, 0, 0, 0));
			editorObjects->addScrollBar();

			std::vector<std::string> tabList = { "Settings", "LevelSprites", "Objects" };
			std::vector<GUI::WidgetContainer*> tabPtrList = { gui->getContainerByContainerName("EditorSettings"), 
				gui->getContainerByContainerName("EditorSprites"), gui->getContainerByContainerName("EditorObjects") };
			gui->createTab("Editor", "editorTab", 0, 0, 16, sf::Color(255, 255, 255), "arial.ttf", tabList, tabPtrList, "GREY");

			gui->createWidgetContainer("EditorInfos", 1, 0, 0, 1350, 30, GUI::ContainerMovement::Fixed);
			gui->getContainerByContainerName("EditorInfos")->setBackground(sf::Color(0, 0, 0, 200));
			gui->createLabel("EditorInfos", "cursorPos", 150, 5, "Cursor : (0,0)", "arial.ttf", 16, sf::Color::White);
			gui->createLabel("EditorInfos", "camPos", 350, 5, "Camera : (0,0)", "arial.ttf", 16, sf::Color::White);
			gui->createLabel("EditorInfos", "sumPos", 550, 5, "Sum : (0,0)", "arial.ttf", 16, sf::Color::White);
			gui->createLabel("EditorInfos", "currentLayer", 750, 5, "Layer : 0", "arial.ttf", 16, sf::Color::White);

			//Map Editor
			Graphics::LevelSprite* hoveredSprite = NULL;
			Graphics::LevelSprite* selectedSprite = NULL;
			sf::FloatRect sdBoundingRect;
			int selectedSpriteOffsetX = 0;
			int selectedSpriteOffsetY = 0;
			int selectedSpritePickPosX = 0;
			int selectedSpritePickPosY = 0;
			bool guiEditorEnabled = false;
			bool addSpriteMode = false;
			int editMode = 0;
			int cameraSpeed = 30;
			int currentLayer = 1;
			Collision::PolygonalCollider* selectedMasterCollider = NULL;
			int colliderPtGrabbed = -1;
			bool masterColliderGrabbed = false;
			sf::Text sprInfo;
			sprInfo.setFont(font);
			sprInfo.setCharacterSize(16);
			sprInfo.setFillColor(sf::Color::White);
			sf::RectangleShape sprInfoBackground(sf::Vector2f(100, 160));
			sprInfoBackground.setFillColor(sf::Color(0, 0, 0, 200));

			//Build Tabs
			EditorTools::loadSpriteFolder("");
			EditorTools::buildObjectTab();

			//Framerate / DeltaTime
			Time::FPSCounter fps;
			fps.loadFont(font);
			FramerateManager framerateManager(*gameConfig);
			window.setVerticalSyncEnabled(framerateManager.isVSyncEnabled());

			Light::initLights();

			EditorGrid editorGrid(32, 32);
			keybind.setActionDelay("MagnetizeUp", 200);
			keybind.setActionDelay("MagnetizeRight", 200);
			keybind.setActionDelay("MagnetizeDown", 200);
			keybind.setActionDelay("MagnetizeLeft", 200);
			GUI::Widget::getWidgetByID<GUI::Button>("gridDimensionsBtn")->bindFunction([&editorGrid]() {
				std::string dimSX = GUI::Widget::getWidgetByID<GUI::TextInput>("gridDimensionsEX")->getText();
				std::string dimSY = GUI::Widget::getWidgetByID<GUI::TextInput>("gridDimensionsEY")->getText();
				int dimX = std::stoi(dimSX != "" ? dimSX : "32");
				int dimY = std::stoi(dimSY != "" ? dimSY : "32");
				editorGrid.setSize(dimX, dimY);
			});
			GUI::Widget::getWidgetByID<GUI::Button>("gridOffsetBtn")->bindFunction([&editorGrid]() {
				std::string offSX = GUI::Widget::getWidgetByID<GUI::TextInput>("gridOffsetEX")->getText();
				std::string offSY = GUI::Widget::getWidgetByID<GUI::TextInput>("gridOffsetEY")->getText();
				int offX = std::stoi(offSX != "" ? offSX : "0");
				int offY = std::stoi(offSY != "" ? offSY : "0");
				editorGrid.setOffset(offX, offY);
			});

			world.loadFromFile(mapName);

			guiMapDimX->setText(std::to_string(world.getSizeX()));
			guiMapDimY->setText(std::to_string(world.getSizeY()));

			GUI::Widget::getWidgetByID<GUI::Button>("mapDimensionsBtn")->bindFunction([&world]() {
				std::string dimSX = GUI::Widget::getWidgetByID<GUI::TextInput>("mapDimensionsEX")->getText();
				std::string dimSY = GUI::Widget::getWidgetByID<GUI::TextInput>("mapDimensionsEY")->getText();
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
					GUI::Widget::getWidgetByID<GUI::Droplist>("cameraMenuList")->setSelected(0);
				else if (keybind.isActionToggled("CamFree"))
					GUI::Widget::getWidgetByID<GUI::Droplist>("cameraMenuList")->setSelected(1);

				if (keybind.isActionToggled("SpriteMode"))
				{
					GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->setSelected(0);
					editMode = 0;
				}
				else if (keybind.isActionToggled("CollisionMode"))
				{
					GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->setSelected(1);
					editMode = 2;
				}

				if (GUI::Widget::getWidgetByID<GUI::Button>("editorMenuBtn")->getJustClicked())
				{
					guiEditorEnabled = !guiEditorEnabled;
				}

				if (GUI::Widget::getWidgetByID<GUI::Checkbox>("enableFPSCB")->getToggled())
					drawFPS = GUI::Widget::getWidgetByID<GUI::Checkbox>("enableFPSCB")->isChecked();

				if (guiEditorEnabled)
					GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->setSelected(3);

				//Updates
				if (!gameConsole.isConsoleVisible())
				{
					if (GUI::Widget::getWidgetByID<GUI::Droplist>("cameraMenuList")->getCurrentSelected() == "Movable Camera")
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

				if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() != "LevelSprites" && selectedSprite != NULL)
				{
					selectedSprite->setColor(sf::Color::White);
					selectedSprite = NULL;
					hoveredSprite = NULL;
					selectedSpriteOffsetX = 0;
					selectedSpriteOffsetY = 0;
					sprInfo.setString("");
				}

				//Sprite Editing
				if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() == "LevelSprites")
				{
					world.enableShowCollision(true, true, false, false);

					//Layer Change
					if (selectedSprite == NULL && keybind.isActionToggled("LayerInc"))
					{
						currentLayer += 1;
						if (hoveredSprite != nullptr)
						{
							hoveredSprite->setColor(sf::Color::White);
							hoveredSprite = NULL;
							sprInfo.setString("");
						}
					}
					if (selectedSprite == NULL && keybind.isActionToggled("LayerDec"))
					{
						currentLayer -= 1;
						if (hoveredSprite != nullptr)
						{
							hoveredSprite->setColor(sf::Color::White);
							hoveredSprite = NULL;
							sprInfo.setString("");
						}
					}
					//Sprite Hover
					if (hoveredSprite == NULL && selectedSprite == NULL)
					{
						if (world.getSpriteByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY(), currentLayer) != NULL)
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
					else if (hoveredSprite != NULL && selectedSprite == NULL)
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
							hoveredSprite = NULL;
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
				if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() == "Collisions")
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
				//Play Edition
				if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() == "Play")
				{
					if (cursor.getClicked("Right"))
					{
						/*character.cancelMoves();
						character.setPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());*/
					}
				}

				//GUI Update
				GUI::Widget::getWidgetByID<GUI::Label>("cursorPos")->setComplexText("<color:255,255,255>Cursor : (<color:0,255,0>" + std::to_string(cursor.getX()) + "<color:255,255,255>"
					",<color:0,255,0>" + std::to_string(cursor.getY()) + "<color:255,255,255>)");
				GUI::Widget::getWidgetByID<GUI::Label>("camPos")->setComplexText("<color:255,255,255>Camera : (<color:0,255,0>" + std::to_string((int)world.getCamX()) + "<color:255,255,255>"
					",<color:0,255,0>" + std::to_string((int)world.getCamY()) + "<color:255,255,255>)");
				GUI::Widget::getWidgetByID<GUI::Label>("sumPos")->setComplexText("<color:255,255,255>Sum : (<color:0,255,0>" + 
					std::to_string((int)world.getCamX() + (int)cursor.getX()) + "<color:255,255,255>"
					",<color:0,255,0>" + std::to_string((int)world.getCamY() + (int)cursor.getY()) + "<color:255,255,255>)");
				GUI::Widget::getWidgetByID<GUI::Label>("currentLayer")->setComplexText("<color:255,255,255>Layer : <color:0,255,0>" + std::to_string(currentLayer));
				gui->getContainerByContainerName("Editor")->setDisplayed(guiEditorEnabled);
				gui->updateAllContainer();

				//Events
				Script::TriggerDatabase::GetInstance()->update();
				world.update(framerateManager.getGameSpeed());
				textDisplay.update(framerateManager.getGameSpeed());
				keybind.update();
				cursor.update();
				gameConsole.update();
				if (drawFPS) fps.tick();

				//Triggers Handling
				networkHandler.handleTriggers();
				cursor.handleTriggers();
				keybind.handleTriggers();

				if (*isGridEnabled)
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
				if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() == "Play")
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
						//triggerDatabaseCore.setTriggerState("KeyPress", true);
						if (gameConsole.isConsoleVisible())
							gameConsole.inputKey(event.text.unicode);
						break;
					case sf::Event::MouseWheelMoved:
						//triggerDatabaseCore.setTriggerState("MouseWheelScroll", true);
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
				}
				//Draw Everything Here
				if (framerateManager.doRender())
				{
					window.clear();
					world.display(&window);
					//Show Collision
					if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() == "Collisions")
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
					if (*isGridEnabled)
						editorGrid.draw(&window);
					//HUD & GUI
					if (sprInfo.getString() != "")
					{
						window.draw(sprInfoBackground);
						window.draw(sprInfo);
					}
					gui->drawAllContainer(&window);
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
			delete gui;
			window.close();
		}

	}
}