//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "MapEditor.hpp"

std::map<std::string, me::SpriteFolder*> addSprFolderMap;

//SpriteFolder
me::SpriteFolder::SpriteFolder(std::string cat, std::string name, std::string folderIcon, sf::Font font)
{
	this->cat = cat;
	this->name = name;
	this->folderIcon = folderIcon;
	this->font = font;
}
void me::SpriteFolder::pushSprite(me::SpriteFile* spr)
{
	sprList.push_back(spr);
}
std::vector<me::SpriteFile*>* me::SpriteFolder::getSpriteList()
{
	return &sprList;
}
void me::SpriteFolder::render()
{
	sf::Texture baseTexture;
	baseTexture.loadFromFile("Sprites/MapEditor/FolderIcons/" + folderIcon);
	sf::Sprite baseSpr;
	baseSpr.setTexture(baseTexture);
	baseSpr.setPosition(0, 0);
	sf::RenderTexture rendText;
	rendText.create(256, 256);
	rendText.clear(sf::Color(0, 0, 0, 0));
	rendText.draw(baseSpr);
	sf::Text folderText;
	folderText.setFont(font);
	folderText.setCharacterSize(16);
	folderText.setString(name);
	folderText.setPosition(10, 50);
	rendText.draw(folderText);
	rendText.display();
	texture = rendText.getTexture();
	sprite.setTexture(texture);
}
sf::Sprite* me::SpriteFolder::getSprite()
{
	return &sprite;
}

sf::Texture me::SpriteFolder::getTexture()
{
	return texture;
}

//SpriteFile
me::SpriteFile::SpriteFile(std::string name, sf::Font font)
{
	this->name = name;
	this->font = font;
}

std::string me::SpriteFile::getName()
{
	return name;
}

void loadSpriteTab(DataObject* parameters)
{
	hookCore.getPointer("GUI")->as<GUI::Container*>()->getContainerByContainerName("EditorSprites")->removeAllWidget();
	std::string geid;
	parameters->getAttribute(convertPath(""), "id")->getData(&geid);
	std::cout << "Load Folder : " << geid << std::endl;
	GUI::Container* gui = hookCore.getPointer("GUI")->as<GUI::Container*>();
	sf::Font font;
	font.loadFromFile("Data/Fonts/arial.ttf");
	std::vector<me::SpriteFile*> spritesInCat = *addSprFolderMap[geid]->getSpriteList();
	for (unsigned int i = 0; i < spritesInCat.size(); i++)
	{
		int xpos = 20 + (i * 266);
		int yiter = 0;
		while (xpos > 1920 - 266)
		{
			xpos -= (1920 - 266);
			yiter += 1;
		}
		int ypos = 25 + (266 * yiter);
		gui->createButton("EditorSprites", "LS_SPR_" + spritesInCat[i]->getName(), 0, 0, true, false, "GREY");
	}
}

void buildAddSpriteFolderList()
{
	GUI::Container* gui = hookCore.getPointer("GUI")->as<GUI::Container*>();
	sf::Font font;
	font.loadFromFile("Data/Fonts/arial.ttf");
	DataParser addSprFolderConfigFile;
	addSprFolderConfigFile.parseFile("Sprites/LevelSprites/config.cfg.msd");
	

	std::vector<std::string> sprNameList = fn::File::listDirInDir("Sprites/LevelSprites/");
	std::map<std::string, std::vector<std::string>> addSprMap;
	for (unsigned int i = 0; i < sprNameList.size(); i++)
	{
		if (fn::String::occurencesInString(sprNameList[i], "_") == 1)
		{
			std::string currentPrefix = fn::String::split(sprNameList[i], "_")[0];
			addSprMap[currentPrefix].push_back(fn::String::split(sprNameList[i], "_")[1]);
		}
		else
		{
			addSprMap["OTHR"].push_back(sprNameList[i]);
		}
	}
	std::vector<std::string> folderConfigList = addSprFolderConfigFile.getAllComplex("SpritePrefix", "");
	for (int i = 0; i < folderConfigList.size(); i++)
	{
		gui->createButton("EditorSprites", "LS_CTG_" + folderConfigList[i], 20 + (i * 266), 25, true, false, "GREY");
	}
	typedef std::map<std::string, std::vector<std::string>>::iterator it_type;
	for (it_type iterator = addSprMap.begin(); iterator != addSprMap.end(); iterator++)
	{
		std::string prefixEquivalent;
		if (fn::Vector::isInList(iterator->first, folderConfigList))
		{
			if (addSprFolderConfigFile.attributeExists("SpritePrefix", iterator->first, "name"))
				addSprFolderConfigFile.getAttribute("SpritePrefix", iterator->first, "name")->getData(&prefixEquivalent);
			else
				prefixEquivalent = iterator->first;
		}
		else
			prefixEquivalent = iterator->first;
		me::SpriteFolder* tempFolder = new me::SpriteFolder(iterator->first, prefixEquivalent, "default.png", font);
		for (unsigned int i = 0; i < iterator->second.size(); i++)
		{
			tempFolder->pushSprite(new me::SpriteFile(iterator->first + "_" + iterator->second[i], font));
		}
		tempFolder->render();
		GUI::Widget::getWidgetByID<GUI::Button>("LS_CTG_" + iterator->first)->setTextureIdle(tempFolder->getTexture());
		GUI::Widget::getWidgetByID<GUI::Button>("LS_CTG_" + iterator->first)->setTexturePushed(tempFolder->getTexture());
		GUI::Widget::getWidgetByID<GUI::Button>("LS_CTG_" + iterator->first)->setTextureHover(tempFolder->getTexture());
		GUI::Widget::getWidgetByID<GUI::Button>("LS_CTG_" + iterator->first)->bindFunction(&loadSpriteTab, "string id = '" + iterator->first + "'");
		addSprFolderMap[iterator->first] = tempFolder;
	}
}

void editMap(std::string mapName)
{
	funtest();
	hookCore.dropValue("TriggerDatabase", &triggerDatabaseCore);
	TextRenderer textDisplay;
	hookCore.dropValue("TextDisplay", &textDisplay);
	textDisplay.setPos(0, 0);

	//Console
	Console gameConsole;
	hookCore.dropValue("Console", &gameConsole);
	Console::Stream* charStream = gameConsole.createStream("CharStream");

	//Font
	sf::Font font;
	font.loadFromFile("Data/Fonts/arial.ttf");

	//Resolution
	const int S_WIDTH = fn::Coord::baseWidth;
	const int S_HEIGHT = fn::Coord::baseHeight;
	int resX = fn::Coord::width;
	int resY = fn::Coord::height;

	//Creating Window / Camera / RenderTexture
	sf::RenderWindow window(sf::VideoMode(resX, resY), "Melting Saga", sf::Style::Fullscreen);
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);

	//Config
	DataParser configFile;
	configFile.parseFile("Data/config.cfg.msd");
	int scrollSensitive;
	configFile.getAttribute("GameConfig", "", "scrollSensibility")->getData(&scrollSensitive);
	bool showChar, showCol, showLSpr, showOverlay, showCursor, showFPS;
	configFile.getAttribute("Developpement", "", "showCharacter")->getData(&showChar);
	configFile.getAttribute("Developpement", "", "showCollisions")->getData(&showCol);
	configFile.getAttribute("Developpement", "", "showLevelSprites")->getData(&showLSpr);
	configFile.getAttribute("Developpement", "", "showOverlay")->getData(&showOverlay);
	configFile.getAttribute("Developpement", "", "showCursor")->getData(&showCursor);
	configFile.getAttribute("Developpement", "", "showFPS")->getData(&showFPS);
	bool drawFPS = true;

	//Cursor
	Cursor cursor;
	cursor.initialize(resX, resY);

	//Character Initialisation
	Character character("Natsugi");
	character.setStreamLink(charStream);

	//World Creation / Loading
	World world;
	hookCore.dropValue("World", &world);
	world.loadFromFile(mapName);
	world.addCharacter(&character);
	world.init();
	bool depthOfFieldEnabled;
	configFile.getAttribute("GameConfig", "", "depthOfField")->getData(&depthOfFieldEnabled);
	if (!depthOfFieldEnabled)
		world.setBlurMul(0.0);

	//CastSystem
	Caster castSystem;
	castSystem.hookToChar(&character);
	castSystem.hookToCurs(&cursor);
	castSystem.hookToWorld(&world);

	//Keybinding
	KeyBinder keybind = KeyBinder();
	keybind.loadFromFile(&configFile);
	std::cout << "Gamepad Connected : " << sf::Joystick::isConnected(0) << std::endl;
	std::cout << "Gamepad has : " << sf::Joystick::getButtonCount(0) << " buttons" << std::endl;

	//GUI
	sf::Event event;
	GUI::Container* gui = new GUI::Container(&event, &window, 1920, 1080);
	std::cout << "Pointer to (init) : " << gui << std::endl;
	hookCore.dropValue("GUI", gui);
	gui->createWidgetContainer("Main", 1, 0, 0, fn::Coord::width, fn::Coord::height, GUI::ContainerMovement::Fixed);
	gui->createLabel("Main", "title", resX - 800, 5, "Melting Saga Level Editor", "arial.ttf", 16, sf::Color(255, 255, 255));
	gui->createButton("Main", "editorMenuBtn", resX - 570, 0, true, true, "GREY");
	GUI::ButtonEvent* menuOpened = GUI::Widget::getWidgetByID<GUI::Button>(std::string("editorMenuBtn"))->getHook();
	GUI::Widget::getWidgetByID<GUI::Button>(std::string("editorMenuBtn"))->setText("Menu Editeur", "arial.ttf", sf::Color(255, 255, 255), 14, true);
	std::vector<std::string> cameraMenuList = { "Fixed Camera", "Following Camera", "Zone Camera" };
	gui->createDroplist("Main", "cameraMenuList", resX - 190, 0, 12, "", false, "arial.ttf", "GREY", cameraMenuList);
	std::vector<std::string> editModeList = { "LevelSprites", "Objects", "Collisions", "Play", "None" };
	gui->createDroplist("Main", "editModeList", resX - 380, 0, 12, "", false, "arial.ttf", "GREY", editModeList);
	GUI::Widget::getWidgetByID<GUI::Droplist>("cameraMenuList")->setSelected(1);
	gui->createWidgetContainer("Editor", 2, 20, 40, resX - 40, resY - 80, GUI::ContainerMovement::Fixed);
	gui->getContainerByContainerName("Editor")->setBackground(sf::Color(0, 0, 0, 200));

	gui->createWidgetContainer("EditorSettings", 2, 20, 40, resX - 40, resY - 80, GUI::ContainerMovement::Fixed);
	gui->getContainerByContainerName("EditorSettings")->setBackground(sf::Color(0, 0, 0, 0));
	gui->createLabel("EditorSettings", "displayCatLbl", 25, 40, "Display Options", "arial.ttf", 25, sf::Color(255, 255, 255));
	gui->createLabel("EditorSettings", "editorCatLbl", 400, 40, "Editor Options", "arial.ttf", 25, sf::Color(255, 255, 255));
	gui->createCheckbox("EditorSettings", "enableCharacterCB", 425, 80, "GREY", true);
	gui->createLabel("EditorSettings", "enableCharacterLbl", 450, 80, "Enable Character in Edit Mode", "arial.ttf", 12, sf::Color(255, 255, 255));
	gui->createCheckbox("EditorSettings", "enableDOFCB", 40, 80, "GREY", true);
	gui->createLabel("EditorSettings", "enableDOFLbl", 65, 80, "Enable Depth Of Field", "arial.ttf", 12, sf::Color(255, 255, 255));
	gui->createCheckbox("EditorSettings", "enableFPSCB", 40, 105, "GREY", true);
	gui->createLabel("EditorSettings", "enableFPSLbl", 65, 105, "Enable FPS Counter", "arial.ttf", 12, sf::Color(255, 255, 255));
	gui->createCheckbox("EditorSettings", "enableGridCB", 40, 130, "GREY", true);
	bool* isGridEnabled = GUI::Widget::getWidgetByID<GUI::Checkbox>("enableGridCB")->getHook();
	gui->createLabel("EditorSettings", "enableGridLbl", 65, 130, "Enable Grid", "arial.ttf", 12, sf::Color(255, 255, 255));
	gui->createLabel("EditorSettings", "gridDimensionsLbl", 40, 155, "Dimensions :", "arial.ttf", 12, sf::Color(255, 255, 255));
	gui->createLabel("EditorSettings", "gridDimensionsMULbl", 160, 155, "x", "arial.ttf", 12, sf::Color(255, 255, 255));

	gui->createWidgetContainer("EditorSprites", 2, 20, 40, resX - 40, resY - 80, GUI::ContainerMovement::Fixed);
	gui->getContainerByContainerName("EditorSprites")->setBackground(sf::Color(0, 0, 0, 0));

	gui->createWidgetContainer("EditorCollisions", 2, 20, 40, resX - 40, resY - 80, GUI::ContainerMovement::Fixed);
	gui->getContainerByContainerName("EditorCollisions")->setBackground(sf::Color(0, 0, 0, 0));

	std::vector<std::string> tabList = { "Settings", "LevelSprites", "Collisions" };
	std::vector<GUI::WidgetContainer*> tabPtrList = { gui->getContainerByContainerName("EditorSettings"), gui->getContainerByContainerName("EditorSprites"), gui->getContainerByContainerName("EditorCollisions") };
	gui->createTab("Editor", "editorTab", 0, 0, 16, sf::Color(255, 255, 255), "arial.ttf", tabList, tabPtrList, "GREY");


	//Map Editor
	LevelSprite* hoveredSprite = NULL;
	LevelSprite* selectedSprite = NULL;
	sf::FloatRect sdBoundingRect;
	int selectedSpriteOffsetX = 0;
	int selectedSpriteOffsetY = 0;
	bool guiEditorEnabled = false;
	bool addSpriteMode = false;
	int editMode = 0;
	int cameraSpeed = 30;
	Collision::PolygonalCollider* selectedMasterCollider = NULL;
	int colliderPtGrabbed = -1;
	bool masterColliderGrabbed = false;
	sf::Text sprInfo;
	sprInfo.setFont(font);
	sprInfo.setCharacterSize(16);
	sprInfo.setColor(sf::Color::White);
	sf::RectangleShape sprInfoBackground(sf::Vector2f(100, 120));
	sprInfoBackground.setFillColor(sf::Color(0, 0, 0, 200));
	//Build Sprite List
	std::vector<std::string> allSprites;
	allSprites = fn::File::listDirInDir("Sprites/LevelSprites/");
	buildAddSpriteFolderList();

	//Framerate / DeltaTime
	FPSCounter fps;
	fps.loadFont(font);

	sf::Clock deltaClock;
	sf::Time sfDeltaTime;
	double deltaTime;
	float speedCoeff = 60.0;
	double gameSpeed = 0.0;
	Chronostasis gameClock;

	Light::initLights();

	gameObjectHandlerCore.createGameObject("switch", "LevelObjects", "Switch");
	gameObjectHandlerCore.createGameObject("light", "LevelObjects", "Light");
	gameObjectHandlerCore.createGameObject("button", "LevelObjects", "Button");
	gameObjectHandlerCore.sendRequireArgument<std::string>("light", "switchKey", gameObjectHandlerCore.getGameObject("switch")->getPublicKey());
	gameObjectHandlerCore.sendRequireArgument<std::string>("light", "buttonKey", gameObjectHandlerCore.getGameObject("button")->getPublicKey());
	world.addLevelSprite(gameObjectHandlerCore.getGameObject("switch")->getLevelSprite());
	world.addLevelSprite(gameObjectHandlerCore.getGameObject("light")->getLevelSprite());
	world.addLevelSprite(gameObjectHandlerCore.getGameObject("button")->getLevelSprite());
	world.addCollider(gameObjectHandlerCore.getGameObject("switch")->getCollider());
	world.addCollider(gameObjectHandlerCore.getGameObject("button")->getCollider());

	EditorGrid editorGrid(32, 32);
	keybind.setActionDelay("MagnetizeUp", 30);
	keybind.setActionDelay("MagnetizeRight", 30);
	keybind.setActionDelay("MagnetizeDown", 30);
	keybind.setActionDelay("MagnetizeLeft", 30);

	//Game Starts
	while (window.isOpen())
	{
		//DeltaTime
		sfDeltaTime = deltaClock.restart();
		deltaTime = std::min(1.0 / 30.0, (double)sfDeltaTime.asMicroseconds() / 1000000.0);
		gameSpeed = deltaTime * speedCoeff;

		if (keybind.isActionToggled("AddSprite"))
		{
			gui->getContainerByContainerName("EditorSprites")->removeAllWidget();
		}

		//GUI Actions
		keybind.setEnabled(!gameConsole.isConsoleVisible());
		if (keybind.isActionToggled("CamFixed"))
			GUI::Widget::getWidgetByID<GUI::Droplist>("cameraMenuList")->setSelected(0);
		else if (keybind.isActionToggled("CamFollow"))
			GUI::Widget::getWidgetByID<GUI::Droplist>("cameraMenuList")->setSelected(1);
		else if (keybind.isActionToggled("CamZone"))
			GUI::Widget::getWidgetByID<GUI::Droplist>("cameraMenuList")->setSelected(2);

		if (keybind.isActionToggled("SpriteMode"))
		{
			GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->setSelected(0);
			editMode = 0;
		}
		else if (keybind.isActionToggled("ObjectMode"))
		{
			GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->setSelected(1);
			editMode = 1;
		}
		else if (keybind.isActionToggled("CollisionMode"))
		{
			GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->setSelected(2);
			editMode = 2;
		}

		if (GUI::Widget::getWidgetByID<GUI::Button>("editorMenuBtn")->getJustClicked())
		{
			guiEditorEnabled = !guiEditorEnabled;
		}

		if (GUI::Widget::getWidgetByID<GUI::Checkbox>("enableDOFCB")->getToggled())
		{
			if (GUI::Widget::getWidgetByID<GUI::Checkbox>("enableDOFCB")->isChecked())
				world.setBlurMul(0.0003);
			else
				world.setBlurMul(0);
		}
		if (GUI::Widget::getWidgetByID<GUI::Checkbox>("enableFPSCB")->getToggled())
			drawFPS = GUI::Widget::getWidgetByID<GUI::Checkbox>("enableFPSCB")->isChecked();

		if (guiEditorEnabled)
			GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->setSelected(4);

		if (GUI::Widget::getWidgetByID<GUI::Droplist>("cameraMenuList")->getCurrentSelected() == "Following Camera")
			world.setCameraPosition(world.getCharacter(0)->getX() - (resX / 2) + 128, world.getCharacter(0)->getY() - (resY / 2) + 152, "FOLLOW");

		//Updates
		if (!gameConsole.isConsoleVisible())
		{
			world.update(gameSpeed);
			//Keybinds
			if (GUI::Widget::getWidgetByID<GUI::Droplist>("cameraMenuList")->getCurrentSelected() != "Fixed Camera")
			{
				if (keybind.isActionEnabled("Left") && keybind.isActionEnabled("Right"))
				{
				}
				else if (keybind.isActionEnabled("Left"))
					world.getCharacter(0)->move("Left");
				else if (keybind.isActionEnabled("Right"))
					world.getCharacter(0)->move("Right");

				if (keybind.isActionEnabled("Crouch"))
				{
					world.getCharacter(0)->triggerCrouch(true);
				}
				if (keybind.isActionReleased("Crouch"))
				{
					world.getCharacter(0)->triggerCrouch(false);
				}

				if (keybind.isActionToggled("Jump"))
					world.getCharacter(0)->jump();
				if (keybind.isActionEnabled("Sprint"))
					world.getCharacter(0)->sprint(true);
				else
					world.getCharacter(0)->sprint(false);
			}
			else
			{
				if (keybind.isActionEnabled("CamLeft") && keybind.isActionEnabled("CamRight"))
				{
				}
				else if (keybind.isActionEnabled("CamLeft"))
					world.setCameraPosition(world.getCamX() - (cameraSpeed * gameSpeed), world.getCamY());
				else if (keybind.isActionEnabled("CamRight"))
					world.setCameraPosition(world.getCamX() + (cameraSpeed * gameSpeed), world.getCamY());

				if (keybind.isActionEnabled("CamUp") && keybind.isActionEnabled("CamDown"))
				{
				}
				else if (keybind.isActionEnabled("CamUp"))
					world.setCameraPosition(world.getCamX(), world.getCamY() - (cameraSpeed * gameSpeed));
				else if (keybind.isActionEnabled("CamDown"))
					world.setCameraPosition(world.getCamX(), world.getCamY() + (cameraSpeed * gameSpeed));

				if (keybind.isActionEnabled("CamDash"))
					cameraSpeed = 60;
				else
					cameraSpeed = 30;
			}

			if (keybind.isActionToggled("Reset"))
			{
				world.getCharacter(0)->setPos(world.getStartX(), world.getStartY());
				world.getCharacter(0)->cancelMoves();
			}
		}

		if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() != "LevelSprites" && selectedSprite != NULL)
		{
			selectedSprite->setSpriteColor(sf::Color::White);
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

			//Sprite Hover
			if (hoveredSprite == NULL && selectedSprite == NULL)
			{
				if (world.getSpriteByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY(), 1) != NULL)
				{
					hoveredSprite = world.getSpriteByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY(), 1);
					sdBoundingRect = hoveredSprite->getRect();
					hoveredSprite->setSpriteColor(sf::Color(0, 60, 255));
					std::string sprInfoStr;
					sprInfoStr = "Hovered Sprite : \n";
					sprInfoStr += "    ID : " + hoveredSprite->getID() + "\n";
					sprInfoStr += "    Name : " + hoveredSprite->getName() + "\n";
					sprInfoStr += "    Pos : " + std::to_string(hoveredSprite->getX()) + "," + std::to_string(hoveredSprite->getY()) + "\n";
					sprInfoStr += "    Size : " + std::to_string(hoveredSprite->getW()) + "," + std::to_string(hoveredSprite->getH()) + "\n";
					sprInfoStr += "    Rot : " + std::to_string(hoveredSprite->getRotation()) + "\n";
					sprInfo.setString(sprInfoStr);
					sprInfoBackground.setSize(sf::Vector2f(sprInfo.getGlobalBounds().width + 20, sprInfo.getGlobalBounds().height - 10));
				}
			}
			else if (hoveredSprite != NULL && selectedSprite == NULL)
			{
				sprInfoBackground.setPosition(cursor.getX() + 40, cursor.getY());
				sprInfo.setPosition(cursor.getX() + 50, cursor.getY());
				bool outHover = false;
				if (cursor.getX() + world.getCamX() < hoveredSprite->getX() || cursor.getX() + world.getCamX() > hoveredSprite->getX() + hoveredSprite->getW())
					outHover = true;
				if (cursor.getY() + world.getCamY() < hoveredSprite->getY() || cursor.getY() + world.getCamY() > hoveredSprite->getY() + hoveredSprite->getH())
					outHover = true;
				LevelSprite* testHoverSprite = world.getSpriteByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY(), 1);
				if (testHoverSprite != NULL && testHoverSprite != hoveredSprite)
					outHover = true;
				if (outHover)
				{
					hoveredSprite->setSpriteColor(sf::Color::White);
					hoveredSprite = NULL;
					sprInfo.setString("");
				}
			}

			//Sprite Pick
			if (cursor.getClicked("Left"))
			{
				if (hoveredSprite != NULL)
				{
					selectedSprite = hoveredSprite;
					selectedSpriteOffsetX = (cursor.getX() + world.getCamX()) - selectedSprite->getX();
					selectedSpriteOffsetY = (cursor.getY() + world.getCamY()) - selectedSprite->getY();
					sdBoundingRect = selectedSprite->getRect();
					selectedSprite->setRotationOrigin(selectedSpriteOffsetX, selectedSpriteOffsetY);
					selectedSprite->setSpriteColor(sf::Color(255, 0, 0));
				}
			}

			//Sprite Move
			if (cursor.getPressed("Left") && selectedSprite != NULL)
			{
				selectedSprite->setPosition(cursor.getX() + world.getCamX() - selectedSpriteOffsetX, cursor.getY() + world.getCamY() - selectedSpriteOffsetY);
				sdBoundingRect = selectedSprite->getRect();
				std::string sprInfoStr;
				sprInfoStr = "Hovered Sprite : \n";
				sprInfoStr += "    ID : " + selectedSprite->getID() + "\n";
				sprInfoStr += "    Name : " + selectedSprite->getName() + "\n";
				sprInfoStr += "    Pos : " + std::to_string(selectedSprite->getX()) + "," + std::to_string(selectedSprite->getY()) + "\n";
				sprInfoStr += "    Size : " + std::to_string(selectedSprite->getW()) + "," + std::to_string(selectedSprite->getH()) + "\n";
				sprInfoStr += "    Rot : " + std::to_string(selectedSprite->getRotation()) + "\n";
				sprInfo.setString(sprInfoStr);
				sprInfoBackground.setSize(sf::Vector2f(sprInfo.getGlobalBounds().width + 20, sprInfo.getGlobalBounds().height - 10));
				sprInfoBackground.setPosition(cursor.getX() + 40, cursor.getY());
				sprInfo.setPosition(cursor.getX() + 50, cursor.getY());
			}

			//Decoration Rotate (Non-fonctionnal)
			if ((keybind.isActionEnabled("RotateLeft") || keybind.isActionEnabled("RotateRight")) && selectedSprite != NULL)
			{
				//selectedDecoration->setOrigin(sdBoundingRect.width / 2, sdBoundingRect.height / 2);
				if (keybind.isActionEnabled("RotateLeft") && selectedSprite != NULL)
					selectedSprite->addRotation(-1 * gameSpeed);
				if (keybind.isActionEnabled("RotateRight") && selectedSprite != NULL)
					selectedSprite->addRotation(1 * gameSpeed);
			}

			//Sprite Scale
			if ((keybind.isActionEnabled("ScaleInc") || keybind.isActionEnabled("ScaleDec")) && selectedSprite != NULL)
			{
				if (keybind.isActionEnabled("ScaleDec"))
					selectedSprite->setScale(selectedSprite->getScale() + (-0.05 * gameSpeed * (selectedSprite->getScale() / 2)));
				if (keybind.isActionEnabled("ScaleInc"))
					selectedSprite->setScale(selectedSprite->getScale() + (0.05 * gameSpeed * (selectedSprite->getScale() / 2)));
			}

			//Sprite Drop
			if (cursor.getReleased("Left") && selectedSprite != NULL)
			{
				selectedSprite->setSpriteColor(sf::Color::White);
				sprInfo.setString("");
				selectedSprite->setRotationOrigin(0, 0);
				selectedSprite = NULL;
				hoveredSprite = NULL;
				selectedSpriteOffsetX = 0;
				selectedSpriteOffsetY = 0;
			}

			//Sprite Cancel Offset
			if (cursor.getPressed("Left") && selectedSprite != NULL && keybind.isActionToggled("CancelOffset"))
			{
				selectedSpriteOffsetX = 0;
				selectedSpriteOffsetY = 0;
			}
		}
		//Collision Edition
		if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() == "Collisions")
		{
			bool deletedCollision = false;
			world.enableShowCollision(true, true, true, true);
			if (selectedMasterCollider != NULL)
			{
				selectedMasterCollider->clearHighlights();
				int cursCoordX = cursor.getX() + world.getCamX();
				int cursCoordY = cursor.getY() + world.getCamY();
				int clNode = selectedMasterCollider->findClosestNode(cursCoordX, cursCoordY);
				selectedMasterCollider->highlightPoint(clNode);
				int gLeftNode = ((clNode - 1 != -1) ? clNode - 1 : selectedMasterCollider->getPointsAmount() - 1);
				int gRghtNode = ((clNode + 1 != selectedMasterCollider->getPointsAmount()) ? clNode + 1 : 0);
				int secondClosestNode = (selectedMasterCollider->getNodeDistance(gLeftNode, cursCoordX, cursCoordY) >= selectedMasterCollider->getNodeDistance(gRghtNode, cursCoordX, cursCoordY)) ? gRghtNode : gLeftNode;
				selectedMasterCollider->highlightPoint(secondClosestNode);
			}
			//Collision Point Grab
			if (cursor.getClicked("Left") && colliderPtGrabbed == -1 && world.getCollisionPointByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY()).first != NULL)
			{
				std::pair<Collision::PolygonalCollider*, int> selectedPtCollider;
				selectedPtCollider = world.getCollisionPointByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
				if (selectedMasterCollider != NULL && selectedMasterCollider != selectedPtCollider.first)
				{
					selectedMasterCollider->setSelected(false);
					selectedMasterCollider = NULL;
					masterColliderGrabbed = false;
					colliderPtGrabbed = -1;
				}
				selectedMasterCollider = selectedPtCollider.first;
				selectedMasterCollider->setSelected(true);
				colliderPtGrabbed = selectedPtCollider.second;
			}
			//Collision Point Move
			if (cursor.getPressed("Left") && selectedMasterCollider != NULL && !masterColliderGrabbed && colliderPtGrabbed != -1)
			{
				selectedMasterCollider->movePoint(colliderPtGrabbed, cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
			}
			//Collision Point Release
			if (cursor.getReleased("Left"))
			{
				colliderPtGrabbed = -1;
			}
			//Collision Master Grab
			if (cursor.getClicked("Left") && world.getCollisionMasterByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY()) != NULL)
			{
				Collision::PolygonalCollider* tempCol = world.getCollisionMasterByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
				if (selectedMasterCollider != NULL && selectedMasterCollider != tempCol)
				{
					selectedMasterCollider->setSelected(false);
					selectedMasterCollider = NULL;
					masterColliderGrabbed = false;
					colliderPtGrabbed = -1;
				}
				selectedMasterCollider = tempCol;
				selectedMasterCollider->setSelected(true);
				masterColliderGrabbed = true;
			}
			//Collision Master Move
			if (cursor.getPressed("Left") && selectedMasterCollider != NULL && masterColliderGrabbed)
			{
				selectedMasterCollider->setPositionFromMaster(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
			}
			//Collision Master Release
			if (cursor.getReleased("Left") && masterColliderGrabbed)
			{
				masterColliderGrabbed = false;
			}
			if (cursor.getClicked("Right") && selectedMasterCollider != NULL && !masterColliderGrabbed)
			{
				int crPtX = cursor.getX() + world.getCamX();
				int crPtY = cursor.getY() + world.getCamY();
				int rqPtRes = selectedMasterCollider->hasPoint(crPtX, crPtY, 6, 6);
				//Collision Point Create
				if (rqPtRes == -1)
				{
					selectedMasterCollider->addPoint(crPtX, crPtY, selectedMasterCollider->findClosestNode(crPtX, crPtY, true));
				}
				//Collision Point Delete
				else
				{
					selectedMasterCollider->deletePoint(rqPtRes);
					if (selectedMasterCollider->getPointsAmount() <= 2)
					{
						selectedMasterCollider->setSelected(false);
						world.deleteCollisionByID(selectedMasterCollider->getID());
						selectedMasterCollider = NULL;
						masterColliderGrabbed = false;
						colliderPtGrabbed = -1;
						deletedCollision = true;
					}
				}
			}
			//Collision Release
			if (cursor.getClicked("Left") && selectedMasterCollider != NULL)
			{
				if (world.getCollisionMasterByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY()) == NULL)
				{
					if (world.getCollisionPointByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY()).first == NULL)
					{
						selectedMasterCollider->setSelected(false);
						selectedMasterCollider = NULL;
						masterColliderGrabbed = false;
						colliderPtGrabbed = -1;
					}
				}
			}
			//Collision Delete
			if (cursor.getClicked("Right") && selectedMasterCollider != NULL && masterColliderGrabbed)
			{
				selectedMasterCollider->setSelected(false);
				world.deleteCollisionByID(selectedMasterCollider->getID());
				selectedMasterCollider = NULL;
				masterColliderGrabbed = false;
				colliderPtGrabbed = -1;
				deletedCollision = true;
			}
			//Collision Create
			if (cursor.getClicked("Right") && selectedMasterCollider == NULL && !deletedCollision)
			{
				world.createCollisionAtPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
			}
		}

		//GUI Update
		gui->getContainerByContainerName("Editor")->setDisplayed(guiEditorEnabled);
		gui->updateAllContainer();
		std::cout << "CAN PASS" << std::endl;

		//Events
		keybind.update();
		cursor.update();
		triggerDatabaseCore.update();
		gameObjectHandlerCore.update();

		//Click Trigger
		if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() == "Play")
		{
			if (cursor.getClicked("Left"))
			{
				std::vector<GameObject*> clickableGameObjects;
				std::vector<Collision::PolygonalCollider*> elementsCollidedByCursor;
				clickableGameObjects = gameObjectHandlerCore.getAllGameObject({ "Click" });
				elementsCollidedByCursor = world.getAllCollidersByCollision(cursor.getCollider(), -world.getCamX(), -world.getCamY());
				for (int i = 0; i < elementsCollidedByCursor.size(); i++)
				{
					for (int j = 0; j < clickableGameObjects.size(); j++)
					{
						if (elementsCollidedByCursor[i] == clickableGameObjects[j]->getCollider())
						{
							gameObjectHandlerCore.setTriggerState(clickableGameObjects[j]->getID(), "Click", true);
						}
					}
				}
			}
		}

		//Press Trigger
		if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() == "Play")
		{
			if (cursor.getPressed("Left"))
			{
				std::vector<GameObject*> clickableGameObjects;
				std::vector<Collision::PolygonalCollider*> elementsCollidedByCursor;
				clickableGameObjects = gameObjectHandlerCore.getAllGameObject({ "Click" });
				elementsCollidedByCursor = world.getAllCollidersByCollision(cursor.getCollider(), -world.getCamX(), -world.getCamY());
				for (int i = 0; i < elementsCollidedByCursor.size(); i++)
				{
					for (int j = 0; j < clickableGameObjects.size(); j++)
					{
						if (elementsCollidedByCursor[i] == clickableGameObjects[j]->getCollider())
						{
							gameObjectHandlerCore.setTriggerState(clickableGameObjects[j]->getID(), "Press", true);
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
					if (textDisplay.textRemaining() && !gameConsole.isConsoleVisible()) textDisplay.next();
				}
				if (event.key.code == sf::Keyboard::RShift)
				{
					world.saveData()->writeFile("Data/Maps/poly2.map.msd", true);
				}
				if (event.key.code == sf::Keyboard::F1)
					gameConsole.setConsoleVisibility(!gameConsole.isConsoleVisible());
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

		window.clear();
		world.display(&window);

		//Show Collision
		if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() == "Collisions")
		{
			world.enableShowCollision(true);
		}
		else
		{
			world.enableShowCollision(false);
		}

		//Game Display
		if (hoveredSprite != NULL)
		{
			sf::RectangleShape sprBorder = sf::RectangleShape(sf::Vector2f(sdBoundingRect.width, sdBoundingRect.height));
			sprBorder.setPosition(sdBoundingRect.left - world.getCamX(), sdBoundingRect.top - world.getCamY());
			sprBorder.setFillColor(sf::Color(0, 0, 0, 0));
			sprBorder.setOutlineColor(sf::Color(255, 0, 0));
			sprBorder.setOutlineThickness(2);
			window.draw(sprBorder);
		}

		//EditorGrid
		editorGrid.setOffsetX(-world.getCamX());
		editorGrid.setOffsetY(-world.getCamY());
		if (*isGridEnabled)
		{
			editorGrid.sendCursorPosition(cursor.getX(), cursor.getY());
			editorGrid.draw(&window);
			if (keybind.isActionEnabled("MagnetizeCursor"))
			{
				editorGrid.magnetize(&cursor);
			}
			if (keybind.isActionEnabled("MagnetizeUp")) editorGrid.moveMagnet(&cursor, 0, -1);
			if (keybind.isActionEnabled("MagnetizeRight")) editorGrid.moveMagnet(&cursor, 1, 0);
			if (keybind.isActionEnabled("MagnetizeDown")) editorGrid.moveMagnet(&cursor, 0, 1);
			if (keybind.isActionEnabled("MagnetizeLeft")) editorGrid.moveMagnet(&cursor, -1, 0);
		}

		//HUD & GUI
		if (sprInfo.getString() != "")
		{
			window.draw(sprInfoBackground);
			window.draw(sprInfo);
		}

		if (drawFPS)
		{
			fps.tick();
			window.draw(fps.getFPS());
		}

		gui->drawAllContainer(&window);

		if (textDisplay.textRemaining())
			textDisplay.render(&window);

		//Console
		gameConsole.update();
		if (gameConsole.isConsoleVisible())
			gameConsole.display(&window);

		//Cursor
		if (showCursor)
			window.draw(*cursor.getSprite());

		/*std::vector<sf::RectangleShape> dapp;
		Collision::PolygonalCollider* nik = world.getCollisionMasterByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
		if (nik != NULL)
		{
			dapp = world.getCharacter(0)->getEntityCollider()->returnCollisionSolution(nik);
			for (int k = 0; k < dapp.size(); k++)
			{
				window.draw(dapp[k]);
			}
		}*/

		window.display();
	}
}
