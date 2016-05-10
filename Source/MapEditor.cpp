//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "MapEditor.hpp"

std::map<std::string, MapEditor::SpriteFolder*> addSprFolderMap;
std::map<std::string, GUI::Button*> addBtnGUIMap;
std::map<std::string, std::map<std::string, GUI::Button*>> addFileGUIMap;

//SpriteFolder
MapEditor::SpriteFolder::SpriteFolder(std::string category, std::string name, std::string folderIcon, sf::Font font)
{
	this->category = category;
	this->name = name;
	this->folderIcon = folderIcon;
	this->font = font;
}
void MapEditor::SpriteFolder::pushSprite(MapEditor::SpriteFile* spr)
{
	sprList.push_back(spr);
}
std::vector<MapEditor::SpriteFile*>* MapEditor::SpriteFolder::getSpriteList()
{
	return &sprList;
}
void MapEditor::SpriteFolder::render(sf::RenderTexture* rtexture)
{
	sf::Texture baseTexture;
	baseTexture.loadFromFile("Sprites/MapEditor/FolderIcons/" + folderIcon);
	sf::Sprite baseSpr;
	baseSpr.setTexture(baseTexture);
	baseSpr.setPosition(0, 0);
	rtexture->clear(sf::Color(0, 0, 0, 0));
	rtexture->draw(baseSpr);
	sf::Text folderText;
	folderText.setFont(font);
	folderText.setCharacterSize(16);
	folderText.setString(name);
	folderText.setPosition(10, 50);
	rtexture->draw(folderText);
	rtexture->display();
	texture = rtexture->getTexture();
	sprite.setTexture(texture);
}
sf::Sprite* MapEditor::SpriteFolder::getSprite()
{
	return &sprite;
}

sf::Texture MapEditor::SpriteFolder::getTexture()
{
	return texture;
}

//SpriteFile
MapEditor::SpriteFile::SpriteFile(std::string name, sf::Font font)
{
	this->name = name;
	this->font = font;
}

std::string MapEditor::SpriteFile::getName()
{
	if (name.substr(0, 1) == "@") return name.substr(1, name.size() - 1);
	else return name;
}

void MapEditor::SpriteFile::render(sf::RenderTexture* rtexture)
{
	std::string rname = name;
	if (name.substr(0, 1) == "@") rname = name.substr(1, name.size() - 1);
	texture.loadFromFile("Sprites/LevelSprites/" + rname + "/thumbnail.png");
	sf::Sprite texSpr;
	texSpr.setTexture(texture);
	texSpr.setPosition(sf::Vector2f(128 - (texSpr.getGlobalBounds().width / 2), 128 - (texSpr.getGlobalBounds().height / 2)));	
	if (name.substr(0, 1) != "@")
	{
		rtexture->clear(sf::Color(0, 0, 0, 0));
		sf::RectangleShape sprRec(sf::Vector2f(256, 256));
		sprRec.setFillColor(sf::Color(100, 100, 100));
		sprRec.setPosition(0, 0);
		rtexture->draw(sprRec);
		rtexture->draw(texSpr);
		sf::RectangleShape titleRec(sf::Vector2f(256, 20));
		titleRec.setPosition(0, 0);
		titleRec.setFillColor(sf::Color(0, 0, 0, 200));
		rtexture->draw(titleRec);
		sf::Text sprNameText;
		sprNameText.setFont(this->font);
		sprNameText.setString(rname);
		sprNameText.setCharacterSize(16);
		sprNameText.setColor(sf::Color(255, 255, 255));
		rtexture->draw(sprNameText);
		rtexture->display();
		texture = rtexture->getTexture();
	}
}

sf::Texture MapEditor::SpriteFile::getTexture()
{
	return texture;
}

void MapEditor::loadSpriteTab(DataObject* parameters)
{
	GUI::Container* gui = hookCore.getPointer("GUI")->as<GUI::Container*>();
	gui->getContainerByContainerName("EditorSprites")->removeAllWidget(false);
	std::string geid;
	parameters->getAttribute(convertPath(""), "id")->getData(&geid);
	if (addFileGUIMap.find(geid) == addFileGUIMap.end())
	{
		addFileGUIMap[geid] = std::map<std::string, GUI::Button*>();
		std::cout << "Load Folder : " << geid << std::endl;
		GUI::Container* gui = hookCore.getPointer("GUI")->as<GUI::Container*>();
		sf::Font font;
		font.loadFromFile("Data/Fonts/arial.ttf");
		std::vector<MapEditor::SpriteFile*> spritesInCat = *addSprFolderMap[geid]->getSpriteList();
		spritesInCat.insert(spritesInCat.begin(), new MapEditor::SpriteFile("@SprBack", font));
		spritesInCat[0]->render(nullptr);
		const int sprSize = 256;
		const int sprOff = 10;
		const int xOff = 15;
		const int yOff = 40;
		for (unsigned int i = 0; i < spritesInCat.size(); i++)
		{
			int xpos = (i * (sprSize + sprOff));
			int ypos = std::floor((double)xpos / (double)(1920 - (sprSize + sprOff))) * (sprSize + sprOff);
			while (xpos >(1920 - (sprSize + sprOff)))
			{
				xpos -= (1920 - (sprSize + sprOff));
			}
			xpos = std::floor((double)xpos / (double)(sprSize + sprOff)) * (sprSize + sprOff);
			xpos += xOff;
			ypos += yOff;
			gui->createButton("EditorSprites", "LS_SPR_" + spritesInCat[i]->getName(), xpos, ypos, true, false, "GREY");
			if (i == 0)
			{
				GUI::Widget::getWidgetByID<GUI::Button>("LS_SPR_" + spritesInCat[i]->getName())->bindFunction(&displayAddSpriteFolderList);
			}
			else
			{
				GUI::Widget::getWidgetByID<GUI::Button>("LS_SPR_" + spritesInCat[i]->getName())->bindFunction(
					&addSpriteToWorld, "string id = '" + spritesInCat[i]->getName() + "'");
			}
			GUI::Widget::getWidgetByID<GUI::Button>("LS_SPR_" + spritesInCat[i]->getName())->setTextureAll(spritesInCat[i]->getTexture());
			addFileGUIMap[geid]["LS_SPR_" + spritesInCat[i]->getName()] = 
				GUI::Widget::getWidgetByID<GUI::Button>("LS_SPR_" + spritesInCat[i]->getName());
		}
	}
	else
	{
		for (auto it = addFileGUIMap[geid].begin(); it != addFileGUIMap[geid].end(); it++)
		{
			gui->getContainerByContainerName("EditorSprites")->addWidget(it->second);
		}
	}
}

void MapEditor::buildAddSpriteFolderList()
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
	const int sprSize = 256;
	const int sprOff = 10;
	const int xOff = 15;
	const int yOff = 40;
	for (int i = 0; i < folderConfigList.size(); i++)
	{
		int xpos = (i * (sprSize + sprOff));
		int ypos = std::floor((double)xpos / (double)(1920 - (sprSize + sprOff))) * (sprSize + sprOff);
		while (xpos >(1920 - (sprSize + sprOff)))
		{
			xpos -= (1920 - (sprSize + sprOff));
		}
		xpos = std::floor((double)xpos / (double)(sprSize + sprOff)) * (sprSize + sprOff);
		xpos += xOff;
		ypos += yOff;
		gui->createButton("EditorSprites", "LS_CTG_" + folderConfigList[i], xpos, ypos, true, false, "GREY");
	}
	typedef std::map<std::string, std::vector<std::string>>::iterator it_type;
	sf::RenderTexture rtexture;
	rtexture.create(256, 256);
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
		MapEditor::SpriteFolder* tempFolder = new MapEditor::SpriteFolder(iterator->first, prefixEquivalent, "default.png", font);
		for (unsigned int i = 0; i < iterator->second.size(); i++)
		{
			tempFolder->pushSprite(new MapEditor::SpriteFile(iterator->first + "_" + iterator->second[i], font));
			tempFolder->getSpriteList()->at(i)->render(&rtexture);
		}
		tempFolder->render(&rtexture);
		GUI::Widget::getWidgetByID<GUI::Button>("LS_CTG_" + iterator->first)->setTextureAll(tempFolder->getTexture());
		GUI::Widget::getWidgetByID<GUI::Button>("LS_CTG_" + iterator->first)->bindFunction(
			&MapEditor::loadSpriteTab, "string id = '" + iterator->first + "'");
		addSprFolderMap[iterator->first] = tempFolder;
		addBtnGUIMap["LS_CTG_" + iterator->first] = GUI::Widget::getWidgetByID<GUI::Button>("LS_CTG_" + iterator->first);
	}
}

void MapEditor::displayAddSpriteFolderList()
{
	GUI::Container* gui = hookCore.getPointer("GUI")->as<GUI::Container*>();
	gui->getContainerByContainerName("EditorSprites")->removeAllWidget(false);
	for (auto it = addBtnGUIMap.begin(); it != addBtnGUIMap.end(); it++)
	{
		gui->getContainerByContainerName("EditorSprites")->addWidget(it->second);
	}
}

void MapEditor::addSpriteToWorld(DataObject* parameters)
{
	std::string geid;
	parameters->getAttribute(convertPath(""), "id")->getData(&geid);
	World* world = hookCore.getPointer("World")->as<World*>();
	std::string key = fn::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);;
	while (world->getSpriteByID(key) != NULL)
		key = fn::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
	LevelSprite* sprToAdd = new LevelSprite(geid, key, world->getRessourceManager());
	sprToAdd->move(960 + world->getCamX(), 540 + world->getCamY());
	sprToAdd->setRotation(0);
	sprToAdd->setScale(1);
	sprToAdd->setAtr(std::vector<std::string>());
	sprToAdd->setLayer(1);
	sprToAdd->setZDepth(1);
	sprToAdd->textureUpdate();
	world->addLevelSprite(sprToAdd);
}

void MapEditor::editMap(std::string mapName)
{
	double startLoadTime = getTickSinceEpoch();
	hookCore.dropValue("TriggerDatabase", &triggerDatabaseCore);
	TextRenderer textDisplay;
	hookCore.dropValue("TextDisplay", &textDisplay);
	std::cout << "Creation Chrono : " << "[Start]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	//Console
	Console gameConsole;
	hookCore.dropValue("Console", &gameConsole);
	std::cout << "Creation Chrono : " << "[Console]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	//Font
	sf::Font font;
	font.loadFromFile("Data/Fonts/arial.ttf");
	std::cout << "Creation Chrono : " << "[Font]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	//Resolution
	const int S_WIDTH = fn::Coord::baseWidth;
	const int S_HEIGHT = fn::Coord::baseHeight;
	int resX = fn::Coord::width;
	int resY = fn::Coord::height;
	std::cout << "Creation Chrono : " << "[Resolution]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	//Creating Window
	sf::RenderWindow window(sf::VideoMode(resX, resY), "Melting Saga", sf::Style::Fullscreen);
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);
	std::cout << "Creation Chrono : " << "[Window]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

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
	std::cout << "Creation Chrono : " << "[Config]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	//Cursor
	Cursor cursor;
	cursor.initialize(resX, resY);
	hookCore.dropValue("Cursor", &cursor);
	std::cout << "Creation Chrono : " << "[Cursor]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	//Character Initialisation
	Character character("Natsugi");
	std::cout << "Creation Chrono : " << "[Character]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	//World Creation / Loading
	World world;
	(*world.getScriptEngine())["stream"] = gameConsole.createStream("World", true);
	hookCore.dropValue("World", &world);
	world.loadFromFile(mapName);
	world.addCharacter(&character);
	bool depthOfFieldEnabled;
	configFile.getAttribute("GameConfig", "", "depthOfField")->getData(&depthOfFieldEnabled);
	if (!depthOfFieldEnabled)
		world.setBlurMul(0.0);
	std::cout << "Creation Chrono : " << "[World]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	//CastSystem
	Caster castSystem;
	castSystem.hookToChar(&character);
	castSystem.hookToCurs(&cursor);
	castSystem.hookToWorld(&world);
	std::cout << "Creation Chrono : " << "[CastSystem]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	//Keybinding
	KeyBinder keybind = KeyBinder();
	hookCore.dropValue("KeyBinder", &keybind);
	keybind.loadFromFile(&configFile);
	std::cout << "Gamepad Connected : " << sf::Joystick::isConnected(0) << std::endl;
	std::cout << "Gamepad has : " << sf::Joystick::getButtonCount(0) << " buttons" << std::endl;
	std::cout << "Creation Chrono : " << "[Keybind]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

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
	std::vector<std::string> editModeList = { "LevelSprites", "Collisions", "Play", "None" };
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

	gui->createWidgetContainer("EditorInfos", 3, 0, 0, 1350, 30, GUI::ContainerMovement::Fixed);
	gui->getContainerByContainerName("EditorInfos")->setBackground(sf::Color(0, 0, 0, 200));
	gui->createLabel("EditorInfos", "cursorPos", 150, 5, "Cursor : (0,0)", "arial.ttf", 16, sf::Color::White);
	gui->createLabel("EditorInfos", "camPos", 300, 5, "Camera : (0,0)", "arial.ttf", 16, sf::Color::White);
	gui->createLabel("EditorInfos", "currentLayer", 450, 5, "Layer : 0", "arial.ttf", 16, sf::Color::White);
	std::cout << "Creation Chrono : " << "[GUI]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();


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
	int currentLayer = 1;
	Collision::PolygonalCollider* selectedMasterCollider = NULL;
	int colliderPtGrabbed = -1;
	bool masterColliderGrabbed = false;
	sf::Text sprInfo;
	sprInfo.setFont(font);
	sprInfo.setCharacterSize(16);
	sprInfo.setColor(sf::Color::White);
	sf::RectangleShape sprInfoBackground(sf::Vector2f(100, 160));
	sprInfoBackground.setFillColor(sf::Color(0, 0, 0, 200));
	
	//Build Sprite List
	std::vector<std::string> allSprites;
	allSprites = fn::File::listDirInDir("Sprites/LevelSprites/");
	MapEditor::buildAddSpriteFolderList();
	std::cout << "Creation Chrono : " << "[MapEditor]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	//Framerate / DeltaTime
	FPSCounter fps;
	fps.loadFont(font);
	sf::Clock deltaClock;
	sf::Time sfDeltaTime;
	double deltaTime;
	double speedCoeff = 60.0;
	double gameSpeed = 0.0;
	double frameLimiterClock = getTickSinceEpoch();
	bool limitFPS = true;
	if (configFile.attributeExists("GameConfig", "", "framerateLimit"))
		configFile.getAttribute("GameConfig", "", "framerateLimit")->getData(&limitFPS);
	int framerateTarget = 60;
	if (configFile.attributeExists("GameConfig", "", "framerateTarget"))
		configFile.getAttribute("GameConfig", "", "framerateTarget")->getData(&framerateTarget);
	double reqFramerateInterval = 1.0 / (double)framerateTarget;
	int currentFrame = 0;
	int frameProgression = 0;
	bool needToRender = false;
	bool vsyncEnabled = false;
	if (configFile.attributeExists("GameConfig", "", "vsync"))
		configFile.getAttribute("GameConfig", "", "vsync")->getData(&vsyncEnabled);
	window.setVerticalSyncEnabled(vsyncEnabled);

	std::cout << "Creation Chrono : " << "[Framerate]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	Light::initLights();
	std::cout << "Creation Chrono : " << "[Lights]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	EditorGrid editorGrid(32, 32);
	keybind.setActionDelay("MagnetizeUp", 200);
	keybind.setActionDelay("MagnetizeRight", 200);
	keybind.setActionDelay("MagnetizeDown", 200);
	keybind.setActionDelay("MagnetizeLeft", 200);
	std::cout << "Creation Chrono : " << "[Grid]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	//Game Starts
	while (window.isOpen())
	{
		//DeltaTime
		sfDeltaTime = deltaClock.restart();
		deltaTime = std::min(1.0 / 60.0, (double)sfDeltaTime.asMicroseconds() / 1000000.0);
		gameSpeed = deltaTime * speedCoeff;
		if (limitFPS)
		{
			if (getTickSinceEpoch() - frameLimiterClock > 1000)
			{
				frameLimiterClock = getTickSinceEpoch();
				currentFrame = 0;
			}
			frameProgression = std::round((getTickSinceEpoch() - frameLimiterClock) / (reqFramerateInterval * 1000));
			needToRender = false;
			if (frameProgression > currentFrame)
			{
				currentFrame = frameProgression;
				needToRender = true;
			}
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
		else if (keybind.isActionToggled("CollisionMode"))
		{
			GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->setSelected(1);
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
			GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->setSelected(3);

		if (GUI::Widget::getWidgetByID<GUI::Droplist>("cameraMenuList")->getCurrentSelected() == "Following Camera")
			world.setCameraPosition(world.getCharacter(0)->getX() - (resX / 2) + 128, world.getCharacter(0)->getY() - (resY / 2) + 152, "FOLLOW");

		//Updates
		if (!gameConsole.isConsoleVisible())
		{
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
					hoveredSprite = world.getSpriteByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY(), currentLayer);
					sdBoundingRect = hoveredSprite->getRect();
					hoveredSprite->setSpriteColor(sf::Color(0, 60, 255));
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
				if (cursor.getX() + world.getCamX() < hoveredSprite->getX() || cursor.getX() + world.getCamX() > hoveredSprite->getX() + hoveredSprite->getW())
					outHover = true;
				if (cursor.getY() + world.getCamY() < hoveredSprite->getY() || cursor.getY() + world.getCamY() > hoveredSprite->getY() + hoveredSprite->getH())
					outHover = true;
				LevelSprite* testHoverSprite = world.getSpriteByPos(cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY(), currentLayer);
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
				selectedSprite->setPosition(cursor.getX() + world.getCamX() - selectedSpriteOffsetX,
					cursor.getY() + world.getCamY() - selectedSpriteOffsetY);
				if (selectedSprite->getCollisionHook() != nullptr)
				{
					selectedSprite->getCollisionHook()->setPosition(
						cursor.getX() + world.getCamX() - selectedSpriteOffsetX,
						cursor.getY() + world.getCamY() - selectedSpriteOffsetY, 1);
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

			//Sprite Layer / Z-Depth
			if (cursor.getPressed("Left") && selectedSprite != NULL && keybind.isActionToggled("ZInc"))
			{
				selectedSprite->setZDepth(selectedSprite->getZDepth() + 1);
				world.reorganizeLayers();
			}
			if (cursor.getPressed("Left") && selectedSprite != NULL && keybind.isActionToggled("ZDec")) 
			{
				selectedSprite->setZDepth(selectedSprite->getZDepth() - 1);
				world.reorganizeLayers();
			}
			if (cursor.getPressed("Left") && selectedSprite != NULL && keybind.isActionToggled("LayerInc"))
			{
				selectedSprite->setLayer(selectedSprite->getLayer() + 1);
				currentLayer += 1;
				world.reorganizeLayers();
			}
			if (cursor.getPressed("Left") && selectedSprite != NULL && keybind.isActionToggled("LayerDec"))
			{
				selectedSprite->setLayer(selectedSprite->getLayer() - 1);
				currentLayer -= 1;
				world.reorganizeLayers();
			}
				
			//Sprite Cancel Offset
			if (cursor.getPressed("Left") && selectedSprite != NULL && keybind.isActionToggled("CancelOffset"))
			{
				selectedSpriteOffsetX = 0;
				selectedSpriteOffsetY = 0;
			}

			//Sprite Delete
			if (cursor.getPressed("Left") && selectedSprite != NULL && keybind.isActionToggled("DeleteSprite"))
			{
				world.deleteSprite(selectedSprite);
				selectedSprite = NULL;
				sprInfo.setString("");
				hoveredSprite = NULL;
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
				selectedMasterCollider->setPointPosition(colliderPtGrabbed, cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY());
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
				selectedMasterCollider->setPositionFromMaster(
					cursor.getX() + world.getCamX(), cursor.getY() + world.getCamY(),
					2);
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
		GUI::Widget::getWidgetByID<GUI::Label>("cursorPos")->setComplexText("<color:255,255,255>Cursor : (<color:0,255,0>" + std::to_string(cursor.getX()) + "<color:255,255,255>"
			",<color:0,255,0>" + std::to_string(cursor.getY()) + "<color:255,255,255>)");
		GUI::Widget::getWidgetByID<GUI::Label>("camPos")->setComplexText("<color:255,255,255>Camera : (<color:0,255,0>" + std::to_string((int)world.getCamX()) + "<color:255,255,255>"
			",<color:0,255,0>" + std::to_string((int)world.getCamY()) + "<color:255,255,255>)");
		GUI::Widget::getWidgetByID<GUI::Label>("currentLayer")->setComplexText("<color:255,255,255>Layer : <color:0,255,0>" + std::to_string(currentLayer));
		gui->getContainerByContainerName("Editor")->setDisplayed(guiEditorEnabled);
		gui->updateAllContainer();

		//Events
		triggerDatabaseCore.update();
		world.update(gameSpeed);
		keybind.update();
		cursor.update();
		gameConsole.update();
		if (drawFPS) fps.tick();
		if (*isGridEnabled)
		{
			editorGrid.setOffsetX(-world.getCamX());
			editorGrid.setOffsetY(-world.getCamY());
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
				std::vector<GameObject*> clickableGameObjects = world.getAllGameObject({ "Click" });
				std::vector<Collision::PolygonalCollider*> elementsCollidedByCursor = world.getAllCollidersByCollision(
					cursor.getCollider(), -world.getCamX(), -world.getCamY());
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
					if (textDisplay.textRemaining() && !gameConsole.isConsoleVisible()) textDisplay.next();
				}
				if (event.key.code == sf::Keyboard::RShift)
				{
					world.saveData()->writeFile("Data/Maps/wg.map.msd", true);
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
		//Draw Everything Here
		if (!limitFPS || needToRender)
		{
			window.clear();
			world.display(&window);
			//Show Collision
			if (GUI::Widget::getWidgetByID<GUI::Droplist>("editModeList")->getCurrentSelected() == "Collisions")
				world.enableShowCollision(true);
			else
				world.enableShowCollision(false);
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
}
