#include "MapEditorTools.hpp"

namespace obe
{
	namespace EditorTools
	{
		Thumbnailer* Thumbnailer::_instance = nullptr;
		Thumbnailer::Thumbnailer()
		{
			System::Path("Data/Fonts/arial.ttf").loadResource(&font, System::Loaders::fontLoader);
			renderer.create(246, 246);
			System::Path("Sprites/Others/folder.png").loadResource(&folderTexture, System::Loaders::textureLoader);
		}
		sf::Texture* Thumbnailer::GetSpriteThumbnail(std::string path)
		{
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
				double scale = (texW >= texH) ? size / texW : size / texH;
				sprite.setScale(scale, scale);
				sprite.setPosition(sf::Vector2f((size / 2) - (sprite.getGlobalBounds().width / 2), (size / 2) - (sprite.getGlobalBounds().height / 2)));
				_instance->renderer.clear(sf::Color(0, 0, 0, 0));
				sf::RectangleShape sprRec(sf::Vector2f(size, size));
				sprRec.setFillColor(sf::Color(100, 100, 100));
				sprRec.setPosition(0, 0);
				_instance->renderer.draw(sprRec);
				_instance->renderer.draw(sprite);
				sf::RectangleShape titleRec(sf::Vector2f(size, 20));
				titleRec.setPosition(0, 0);
				titleRec.setFillColor(sf::Color(0, 0, 0, 200));
				_instance->renderer.draw(titleRec);
				sf::Text sprNameText;
				sprNameText.setFont(_instance->font);
				std::vector<std::string> splittedPath = Functions::String::split(path, "/");
				sprNameText.setString(splittedPath[splittedPath.size() - 1]);
				sprNameText.setCharacterSize(16);
				sprNameText.setFillColor(sf::Color(255, 255, 255));
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
				folderText.setPosition(10, 45);
				_instance->renderer.draw(folderText);
				_instance->renderer.display();
				_instance->cache[path] = new sf::Texture(_instance->renderer.getTexture());
				return _instance->cache[path];
			}
			
		}

		void buildObjectTab(tgui::Panel::Ptr& objectTab, tgui::Panel::Ptr& requiresPanel, tgui::Theme& baseTheme)
		{
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
				int ypos = std::floor((double)xpos / (double)(1920 - (btnSize + btnOff))) * (btnSize + btnOff) + yOff;
				while (xpos >(1920 - (btnSize + btnOff + xOff)))
					xpos -= (1920 - (btnSize + btnOff + xOff));
				xpos = std::floor((double)xpos / (double)(btnSize + btnOff)) * (btnSize + btnOff);
				xpos += xOff; ypos += yOff;
				tgui::Button::Ptr currentObj = tgui::Button::create();
				currentObj->setRenderer(baseTheme.getRenderer("ObjectButton"));
				currentObj->setTextSize(18);
				currentObj->setText(currentObjName);
				currentObj->setPosition(xpos, ypos);
				currentObj->setSize(256, 256);
				objectTab->add(currentObj);
				currentObj->connect("pressed", [&requiresPanel, currentObjName]() {
					std::cout << "Trying to build : " << currentObjName << std::endl;
					buildRequiresObjectTab(requiresPanel, currentObjName);
				});

			}
		}

		void buildRequiresObjectTab(tgui::Panel::Ptr& requiresPanel, std::string objName)
		{
			std::cout << "Call Require Creation for : " << objName << std::endl;
			vili::ComplexAttribute* requires = Script::GameObjectRequires::getInstance()->getRequiresForObjectType(objName);
			if (requires != nullptr)
			{
				requiresPanel->show();
				requiresPanel->removeAllWidgets();
				tgui::Label::Ptr newObjectTitleLabel = tgui::Label::create();

				//newObjectTitleLabel->setRenderer()
			}
				/*if (gui.getContainer(containerName)-> != nullptr)

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
				for (std::string& requireItem : requires->getAll(vili::Types::ComplexAttribute))
				{
					std::cout << "Require item is : " << requireItem << std::endl;
					std::cout << requires->contains(vili::Types::ComplexAttribute, "Color") << std::endl;
					std::string lblName = requires->getPath(requireItem)->getBaseAttribute("name")->get<std::string>();
					gui->createLabel(containerName, objName + "_" + requireItem + "_Lbl", 50, widgetVerticalPosition, lblName, "weblysleekuil.ttf", 24, sf::Color::White);
					if (requires->getPath(requireItem)->contains(vili::Types::BaseAttribute, "type")) {
						gui->createTextInput(containerName, objName + "_" + requireItem + "_Input", 200, 
							widgetVerticalPosition + 5, "", "weblysleekuil.ttf", 16, sf::Color::White, false, "GREY");
						std::string reqType = requires->getPath(requireItem)->getBaseAttribute("type")->get<std::string>();
						if (reqType == "int")
							GUI::Widget::getWidgetByID<GUI::TextInput>(objName + "_" + requireItem + "_Input")->addFilter(GUI::TextInputFilters::Integer);
					}
					else if (requires->getPath(requireItem)->contains(vili::Types::ListAttribute, "choices"))
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
			}*/
		}

		void buildObjectThroughRequire(std::string objName)
		{
			/*vili::ComplexAttribute* requires = Script::GameObjectRequires::getInstance()->getRequiresForObjectType(objName);
			GUI::Container* gui = Script::hookCore.getPointer("GUI")->as<GUI::Container*>();
			Cursor::Cursor* cursor = Script::hookCore.getPointer("Cursor")->as<Cursor::Cursor*>();
			World::World* world = Script::hookCore.getPointer("World")->as<World::World*>();
			GUI::WidgetContainer* requireGUI = gui->getContainerByContainerName("Requires");
			std::string key = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
			Script::GameObject* newGameObject = world->createGameObject(key, objName);
				
			for (std::string& requireItem : requires->getAll(vili::Types::ComplexAttribute))
			{
				std::string requirementName = requires->getPath(requireItem)->getBaseAttribute("name")->get<std::string>();
				bool optionalRequirement = requires->getPath(requireItem)->contains(vili::Types::BaseAttribute, "optional");
				if (optionalRequirement)
					optionalRequirement = requires->getPath(requireItem)->getBaseAttribute("optional")->get<bool>();
				if (objName + "_" + requireItem + "_Input" != "" || optionalRequirement)
				{
					if (requires->getPath(requireItem)->contains(vili::Types::ListAttribute, "choices"))
						newGameObject->sendRequireArgumentFromCPP(requirementName, GUI::Widget::getWidgetByID<GUI::Droplist>(objName + "_" + requireItem + "_Input")->getCurrentSelected());
				}
			}
			if (newGameObject->doesHaveCollider()) {
				std::cout << "Position of GO set !" << std::endl;
				//FIX CURSOR POS
			}
			else if (newGameObject->doesHaveLevelSprite()) {
				std::cout << "Position of GO::LS set !" << std::endl;
			}*/
		}

		void loadSpriteFolder(tgui::Panel::Ptr& spritesPanel, tgui::Label::Ptr& spritesCatLabel, std::string path)
		{
			spritesPanel->removeAllWidgets();
			spritesPanel->add(spritesCatLabel);

			std::vector<std::string> fileList;
			std::vector<std::string> folderList;
			System::Path("Sprites/LevelSprites" + path).loadResource(&folderList, System::Loaders::dirPathLoader);
			System::Path("Sprites/LevelSprites" + path).loadResource(&fileList, System::Loaders::filePathLoader);
			
			const int sprSize = 246;
			const int sprOff = 10;
			const int xOff = 15;
			const int yOff = 40;
			int elemIndex = 0;
			int xpos = (0 * (sprSize + sprOff)) + xOff;
			int ypos = std::floor(static_cast<double>(xpos) / static_cast<double>(1920 - (sprSize + sprOff))) * (sprSize + sprOff) + yOff;
			tgui::Button::Ptr backButton = tgui::Button::create();
			spritesPanel->add(backButton, "LS_ELEM_BACK");
			sf::Texture sprback; sprback.loadFromFile("Sprites/Others/back.png");
			backButton->getRenderer()->setTexture(sprback);
			backButton->setSize(sprSize, sprSize);
			backButton->setPosition(xpos, ypos);

			backButton->connect("pressed", [&spritesPanel, &spritesCatLabel, path] {
				std::vector<std::string> splittedPath = Functions::String::split(path, "/");
				loadSpriteFolder(spritesPanel, spritesCatLabel, "/" + Functions::Vector::join(splittedPath, "/", 0, 1));
			});

			for (std::string element : folderList) {
				int xpos = (++elemIndex * (sprSize + sprOff)) + xOff;
				int ypos = std::floor(static_cast<double>(xpos) / static_cast<double>(1920 - (sprSize + sprOff))) * (sprSize + sprOff);
				while (xpos > (1920 - (sprSize + sprOff)))
					xpos -= (1920 - (sprSize + sprOff));
				xpos = std::floor(static_cast<double>(xpos) / static_cast<double>(sprSize + sprOff)) * (sprSize + sprOff);
				xpos += xOff;
				ypos += yOff;
				tgui::Button::Ptr currentFolder = tgui::Button::create();
				spritesPanel->add(currentFolder, "LS_FOLDER_" + element);
				currentFolder->setPosition(xpos, ypos);
				currentFolder->setSize(sprSize, sprSize);
				currentFolder->getRenderer()->setTexture(*Thumbnailer::GetFolderThumbnail(path + "/" + element));
				currentFolder->connect("pressed", [&spritesPanel, &spritesCatLabel, path, element]() {
					loadSpriteFolder(spritesPanel, spritesCatLabel, path + "/" + element);
				});
			}

			for (std::string element : fileList) {
				sf::Texture textureLoadChecker;
				System::Path("Sprites/LevelSprites").add(path).add(element).loadResource(&textureLoadChecker, System::Loaders::textureLoader);
				if (textureLoadChecker.getSize().x != 0)
				{
					int xpos = (++elemIndex * (sprSize + sprOff)) + xOff;
					int ypos = std::floor(static_cast<double>(xpos) / static_cast<double>(1920 - (sprSize + sprOff))) * (sprSize + sprOff);
					while (xpos > (1920 - (sprSize + sprOff)))
						xpos -= (1920 - (sprSize + sprOff));
					xpos = std::floor(static_cast<double>(xpos) / static_cast<double>(sprSize + sprOff)) * (sprSize + sprOff);
					xpos += xOff;
					ypos += yOff;
					std::cout << "MAMIA1 : " << xpos << ", " << ypos << std::endl;
					tgui::Button::Ptr currentSprite = tgui::Button::create();
					spritesPanel->add(currentSprite, "LS_FILE_" + element);
					currentSprite->setPosition(xpos, ypos);
					currentSprite->getRenderer()->setTexture(*Thumbnailer::GetSpriteThumbnail(path + "/" + element));
					currentSprite->setSize(sprSize, sprSize);
					currentSprite->connect("pressed", [path, element] {addSpriteToWorld(path + "/" + element); });
				}
			}
		}

		void addSpriteToWorld(std::string geid)
		{
			std::cout << "Recv geid : " << geid << std::endl;
			World::World* world = Script::hookCore.getPointer("World")->as<World::World*>();
			std::string key = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
			while (world->doesSpriteExists(key))
				key = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
			Graphics::LevelSprite* sprToAdd = world->createLevelSprite(key);
			Coord::UnitVector pixelCamera = world->getCamera().getPosition().to<Coord::WorldPixels>();
			sprToAdd->load("Sprites/LevelSprites/" + geid);
			sprToAdd->setWorkingUnit(Coord::WorldPixels);
			sprToAdd->move(960 + pixelCamera.x, 540 + pixelCamera.y);
			sprToAdd->setRotation(0);
			sprToAdd->setScale(1, 1);
			sprToAdd->setAtr(std::vector<std::string>());
			sprToAdd->setLayer(1);
			sprToAdd->setZDepth(1);
		}
	}
}