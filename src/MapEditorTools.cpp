#include "MapEditorTools.hpp"

namespace mse
{
	namespace EditorTools
	{
		std::map<std::string, GUI::Button*> addSprBtnGUIMap;
		std::map<std::string, GUI::Button*> addObjBtnGUIMap;
		std::map<std::string, std::map<std::string, GUI::Button*>> addFileGUIMap;

		Thumbnailer* Thumbnailer::_instance = nullptr;
		Thumbnailer::Thumbnailer()
		{
			System::Path("Data/Fonts/arial.ttf").loadResource(&font, System::Loaders::fontLoader);
			renderer.create(256.0 * Functions::Coord::width / Functions::Coord::baseWidth, 256.0 * Functions::Coord::height / Functions::Coord::baseHeight);
			System::Path("Sprites/Others/folder.png").loadResource(&folderTexture, System::Loaders::textureLoader);
		}
		sf::Texture* Thumbnailer::GetSpriteThumbnail(std::string path)
		{
			std::cout << "ThumnailerLoad : " << path << std::endl;
			if (_instance == nullptr)
				_instance = new Thumbnailer();
			if (_instance->cache.find(path) != _instance->cache.end())
				return _instance->cache[path];
			else {
				sf::Texture sprTexture;
				System::Path("Sprites/LevelSprites/" + path).loadResource(&sprTexture, System::Loaders::textureLoader);
				sf::Sprite sprite;
				sprite.setTexture(sprTexture);
				double texW = sprTexture.getSize().x;
				double texH = sprTexture.getSize().y;
				double scale = (texW >= texH) ? 256 / texW : 256 / texH;
				sprite.setScale(scale, scale);
				sprite.setPosition(sf::Vector2f(128 - (sprite.getGlobalBounds().width / 2), 128 - (sprite.getGlobalBounds().height / 2)));
				_instance->renderer.clear(sf::Color(0, 0, 0, 0));
				sf::RectangleShape sprRec(sf::Vector2f(256, 256));
				sprRec.setFillColor(sf::Color(100, 100, 100));
				sprRec.setPosition(0, 0);
				_instance->renderer.draw(sprRec);
				_instance->renderer.draw(sprite);
				sf::RectangleShape titleRec(sf::Vector2f(256, 20));
				titleRec.setPosition(0, 0);
				titleRec.setFillColor(sf::Color(0, 0, 0, 200));
				_instance->renderer.draw(titleRec);
				sf::Text sprNameText;
				sprNameText.setFont(_instance->font);
				std::vector<std::string> splittedPath = Functions::String::split(path, "/");
				sprNameText.setString(splittedPath[splittedPath.size() - 1]);
				sprNameText.setCharacterSize(16);
				sprNameText.setColor(sf::Color(255, 255, 255));
				_instance->renderer.draw(sprNameText);
				_instance->renderer.display();
				_instance->cache[path] = new sf::Texture(_instance->renderer.getTexture());
				return _instance->cache[path];
			}
		}
		sf::Texture* Thumbnailer::GetFolderThumbnail(std::string path)
		{
			if (_instance == nullptr)
				_instance = new Thumbnailer();
			if (_instance->cache.find(path) != _instance->cache.end())
				return _instance->cache[path];
			else {
				sf::Sprite baseSpr;
				baseSpr.setTexture(_instance->folderTexture);
				baseSpr.setPosition(0, 0);
				_instance->renderer.clear(sf::Color(0, 0, 0, 0));
				_instance->renderer.draw(baseSpr);
				sf::Text folderText;
				folderText.setFont(_instance->font);
				folderText.setCharacterSize(16);
				std::vector<std::string> splittedPath = Functions::String::split(path, "/");
				folderText.setString(splittedPath[splittedPath.size() - 1]);
				folderText.setPosition(10, 50);
				_instance->renderer.draw(folderText);
				_instance->renderer.display();
				_instance->cache[path] = new sf::Texture(_instance->renderer.getTexture());
				return _instance->cache[path];
			}
			
		}

		void buildObjectTab()
		{
			GUI::Container* gui = Script::hookCore.getPointer("GUI")->as<GUI::Container*>();
			World::World* world = Script::hookCore.getPointer("World")->as<World::World*>();
			std::vector<std::string> allGameObjects;
			System::Path("Data/GameObjects").loadResource(&allGameObjects, System::Loaders::dirPathLoader);
			const int btnSize = 256;
			const int btnOff = 10;
			const int xOff = 15;
			const int yOff = 40;
			for (int i = 0; i < allGameObjects.size(); i++)
			{
				std::string currentObjName = allGameObjects[i];
				int xpos = (i * (btnSize + btnOff));
				int ypos = std::floor((double)xpos / (double)(1920 - (btnSize + btnOff))) * (btnSize + btnOff);
				while (xpos >(1920 - (btnSize + btnOff + xOff)))
					xpos -= (1920 - (btnSize + btnOff + xOff));
				xpos = std::floor((double)xpos / (double)(btnSize + btnOff)) * (btnSize + btnOff);
				xpos += xOff; ypos += yOff;
				GUI::Button* currentObj = gui->createButton("EditorObjects", currentObjName, xpos, ypos, true, true, "OBJECT");
				currentObj->setText(currentObjName, "weblysleekuil.ttf", sf::Color::White, 18, true);
				std::cout << "Adding Btn : " << currentObjName << " at pos : " << xpos << "," << ypos << std::endl;
				currentObj->bindFunction([currentObjName]() { 
					buildRequiresObjectTab(currentObjName);
				});
			}
		}

		void buildRequiresObjectTab(std::string objName)
		{
			std::cout << "Call Require Creation for : " << objName << std::endl;
			Data::ComplexAttribute* requires = Script::GameObjectRequires::getInstance()->getRequiresForObjectType(objName);
			if (requires != nullptr)
			{
				GUI::Container* gui = Script::hookCore.getPointer("GUI")->as<GUI::Container*>();
				std::string containerName = "Requires";
				if (gui->getContainerByContainerName(containerName) != nullptr)
				{
					gui->getContainerByContainerName(containerName)->removeAllWidget(true);
					gui->getContainerByContainerName(containerName)->setDisplayed(true);
					gui->getContainerByContainerName(containerName + "_Frame")->removeAllWidget(true);
					gui->getContainerByContainerName(containerName + "_Frame")->setDisplayed(true);
				}
				else
				{
					gui->createWidgetContainer(containerName + "_Frame", 1, 700, 200, 520, 680, GUI::ContainerMovement::Fixed);
					//gui->createWidgetContainer(containerName + "_Top", 1, 10, 10, 10, 10, GUI::ContainerMovement::Fixed); //Uncomment for REALLY WEIRD ERROR
					gui->createWidgetContainer(containerName, 2, 700, 300, 520, 530, GUI::ContainerMovement::Fixed);
				}
				gui->createLabel(containerName + "_Frame", objName + "_Title", 20, 20, objName + " Requirements", "weblysleekuil.ttf", 32, sf::Color::White);
				gui->getContainerByContainerName(containerName + "_Frame")->setBackground(sf::Color(0, 0, 0, 200));
				gui->getContainerByContainerName(containerName)->addScrollBar();
				int widgetVerticalPosition = 0;
				for (std::string& requireItem : requires->getAllComplexAttributes())
				{
					std::cout << "Require item is : " << requireItem << std::endl;
					std::cout << requires->containsComplexAttribute("Color") << std::endl;
					std::string lblName = requires->getPath(requireItem)->getBaseAttribute("name")->get<std::string>();
					gui->createLabel(containerName, objName + "_" + requireItem + "_Lbl", 50, widgetVerticalPosition, lblName, "weblysleekuil.ttf", 24, sf::Color::White);
					if (requires->getPath(requireItem)->containsBaseAttribute("type")) {
						gui->createTextInput(containerName, objName + "_" + requireItem + "_Input", 200, 
							widgetVerticalPosition + 5, "", "weblysleekuil.ttf", 16, sf::Color::White, false, "GREY");
						std::string reqType = requires->getPath(requireItem)->getBaseAttribute("type")->get<std::string>();
						if (reqType == "int")
							GUI::Widget::getWidgetByID<GUI::TextInput>(objName + "_" + requireItem + "_Input")->addFilter(GUI::TextInputFilters::Integer);
					}
					else if (requires->getPath(requireItem)->containsListAttribute("choices"))
					{
						std::vector<std::string> requireChoices;
						for (int reqI = 0; reqI < requires->getPath(requireItem)->getListAttribute("choices")->getSize(); reqI++)
							requireChoices.push_back(requires->getPath(requireItem)->getListAttribute("choices")->get(reqI)->get<std::string>());
						gui->createDroplist(containerName, objName + "_" + requireItem + "_Input", 200, 
							widgetVerticalPosition, 16, "", false, "weblysleekuil.ttf", "GREY", requireChoices);
					}
					widgetVerticalPosition += 50;
				}
				GUI::Button* createObjectAndCloseBtn = gui->createButton(containerName + "_Frame", "createObjectAndCloseAfterRequireBtn", 20, 640, true, true, "GREY");
				createObjectAndCloseBtn->setText("Create Object and Close", "weblysleekuil.ttf", sf::Color::White, 16, true);
				createObjectAndCloseBtn->bindFunction([objName, gui]() { 
					buildObjectThroughRequire(objName);
					gui->getContainerByContainerName("Requires")->setDisplayed(false);
					gui->getContainerByContainerName("Requires_Frame")->setDisplayed(false);
				});

				GUI::Button* createObjectBtn = gui->createButton(containerName + "_Frame", "createObjectAfterRequireBtn", 310, 640, true, true, "GREY");
				createObjectBtn->setText("Create Object", "weblysleekuil.ttf", sf::Color::White, 16, true);
				createObjectBtn->bindFunction([objName]() { buildObjectThroughRequire(objName); });

			}
			else
			{
				std::string key = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
				Script::GameObject* obj = Script::hookCore.getPointer("World")->as<World::World*>()->createGameObject(key, objName);
			}
		}

		void buildObjectThroughRequire(std::string objName)
		{
			Data::ComplexAttribute* requires = Script::GameObjectRequires::getInstance()->getRequiresForObjectType(objName);
			GUI::Container* gui = Script::hookCore.getPointer("GUI")->as<GUI::Container*>();
			Cursor::Cursor* cursor = Script::hookCore.getPointer("Cursor")->as<Cursor::Cursor*>();
			World::World* world = Script::hookCore.getPointer("World")->as<World::World*>();
			GUI::WidgetContainer* requireGUI = gui->getContainerByContainerName("Requires");
			std::string key = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
			Script::GameObject* newGameObject = world->createGameObject(key, objName);
				
			for (std::string& requireItem : requires->getAllComplexAttributes())
			{
				std::string requirementName = requires->getPath(requireItem)->getBaseAttribute("name")->get<std::string>();
				bool optionalRequirement = requires->getPath(requireItem)->containsBaseAttribute("optional");
				if (optionalRequirement)
					optionalRequirement = requires->getPath(requireItem)->getBaseAttribute("optional")->get<bool>();
				if (objName + "_" + requireItem + "_Input" != "" || optionalRequirement)
				{
					if (requires->getPath(requireItem)->containsListAttribute("choices"))
						newGameObject->sendRequireArgumentFromCPP(requirementName, GUI::Widget::getWidgetByID<GUI::Droplist>(objName + "_" + requireItem + "_Input")->getCurrentSelected());
				}
			}
			if (newGameObject->doesHaveCollider()) {
				std::cout << "Position of GO set !" << std::endl;
				//FIX CURSOR POS
			}
			else if (newGameObject->doesHaveLevelSprite()) {
				std::cout << "Position of GO::LS set !" << std::endl;
			}
		}

		void loadSpriteFolder(std::string path) 
		{
			GUI::Container* gui = Script::hookCore.getPointer("GUI")->as<GUI::Container*>();
			gui->getContainerByContainerName("EditorSprites")->removeAllWidget(true);
			gui->getContainerByContainerName("EditorSprites")->addScrollBar();
			std::vector<std::string> fileList;
			std::vector<std::string> folderList;
			System::Path("Sprites/LevelSprites" + path).loadResource(&folderList, System::Loaders::dirPathLoader);
			System::Path("Sprites/LevelSprites" + path).loadResource(&fileList, System::Loaders::filePathLoader);
			
			const int sprSize = 256;
			const int sprOff = 10;
			const int xOff = 15;
			const int yOff = 40;
			int elemIndex = 0;
			int xpos = (0 * (sprSize + sprOff)) + xOff;
			int ypos = std::floor((double)xpos / (double)(1920 - (sprSize + sprOff))) * (sprSize + sprOff);
			GUI::Button* backButton = gui->createButton("EditorSprites", "LS_ELEM_BACK", xpos, ypos, true, false, "GREY");
			backButton->bindFunction([path] {
				std::vector<std::string> splittedPath = Functions::String::split(path, "/");
				loadSpriteFolder(Functions::Vector::join(splittedPath, "/", 0, 1)); 
			});
			sf::Texture sprback; sprback.loadFromFile("Sprites/Others/back.png");
			
			backButton->setTextureAll(sprback);

			for (std::string element : folderList) {
				int xpos = (++elemIndex * (sprSize + sprOff)) + xOff;
				int ypos = std::floor((double)xpos / (double)(1920 - (sprSize + sprOff))) * (sprSize + sprOff);
				while (xpos > (1920 - (sprSize + sprOff)))
					xpos -= (1920 - (sprSize + sprOff));
				xpos = std::floor((double)xpos / (double)(sprSize + sprOff)) * (sprSize + sprOff);
				xpos += xOff;
				ypos += yOff;
				GUI::Button* currentFolder = gui->createButton("EditorSprites", "LS_FOLDER_" + element, xpos, ypos, true, false, "GREY");
				currentFolder->setTextureAll(*Thumbnailer::GetFolderThumbnail(path + "/" + element));
				currentFolder->bindFunction([path, element] {loadSpriteFolder(path + "/" + element); });
			}

			for (std::string element : fileList) {
				int xpos = (++elemIndex * (sprSize + sprOff)) + xOff;
				int ypos = std::floor((double)xpos / (double)(1920 - (sprSize + sprOff))) * (sprSize + sprOff);
				while (xpos > (1920 - (sprSize + sprOff)))
					xpos -= (1920 - (sprSize + sprOff));
				xpos = std::floor((double)xpos / (double)(sprSize + sprOff)) * (sprSize + sprOff);
				xpos += xOff;
				ypos += yOff;
				GUI::Button* currentFolder = gui->createButton("EditorSprites", "LS_FILE_" + element, xpos, ypos, true, false, "GREY");
				currentFolder->setTextureAll(*Thumbnailer::GetSpriteThumbnail(path + "/" + element));
				currentFolder->bindFunction([path, element] {addSpriteToWorld(path + "/" + element); });
			}
		}

		void addSpriteToWorld(std::string geid)
		{
			std::cout << "Recv geid : " << geid << std::endl;
			World::World* world = Script::hookCore.getPointer("World")->as<World::World*>();
			std::string key = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
			while (world->getSpriteByID(key) != NULL)
				key = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
			Graphics::LevelSprite* sprToAdd = new Graphics::LevelSprite("Sprites/LevelSprites/" + geid, key);
			sprToAdd->move(960 + world->getCamX(), 540 + world->getCamY());
			sprToAdd->setRotation(0);
			sprToAdd->setScale(1, 1);
			sprToAdd->setAtr(std::vector<std::string>());
			sprToAdd->setLayer(1);
			sprToAdd->setZDepth(1);
			world->addLevelSprite(sprToAdd);
		}
	}
}