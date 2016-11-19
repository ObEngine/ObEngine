#include "MapEditorTools.hpp"

namespace mse
{
	namespace EditorTools
	{
		std::map<std::string, SpriteFolder*> addSprFolderMap;
		std::map<std::string, GUI::Button*> addSprBtnGUIMap;
		std::map<std::string, GUI::Button*> addObjBtnGUIMap;
		std::map<std::string, std::map<std::string, GUI::Button*>> addFileGUIMap;


		//SpriteFolder
		SpriteFolder::SpriteFolder(std::string category, std::string name, std::string folderIcon, sf::Font font)
		{
			this->category = category;
			this->name = name;
			this->folderIcon = folderIcon;
			this->font = font;
		}
		void SpriteFolder::pushSprite(SpriteFile* spr)
		{
			sprList.push_back(spr);
		}
		std::vector<SpriteFile*>* SpriteFolder::getSpriteList()
		{
			return &sprList;
		}
		void SpriteFolder::render(sf::RenderTexture* rtexture)
		{
			sf::Texture baseTexture;
			System::Path("Sprites/MapEditor/FolderIcons").add(folderIcon).loadResource(&baseTexture, System::Loaders::textureLoader);
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
		sf::Sprite* SpriteFolder::getSprite()
		{
			return &sprite;
		}

		sf::Texture SpriteFolder::getTexture()
		{
			return texture;
		}

		//SpriteFile
		SpriteFile::SpriteFile(std::string name, sf::Font font)
		{
			this->name = name;
			this->font = font;
		}
		SpriteFile::SpriteFile(std::string name, sf::Texture texture)
		{
			this->name = name;
			this->texture = texture;
			sf::Sprite texSpr;
			texSpr.setTexture(texture);
		}
		std::string SpriteFile::getName()
		{
			if (name.substr(0, 1) == "@") return name.substr(1, name.size() - 1);
			else return name;
		}

		void SpriteFile::render(sf::RenderTexture* rtexture)
		{
			std::string loadRes = System::Path("Sprites/LevelSprites").add(name).add("thumbnail.png").loadResource(&texture, System::Loaders::textureLoader);
			if (loadRes == "")
			{
				std::vector<std::string> allSprites;
				System::Path("Sprites/LevelSprites").add(name).loadResource(&allSprites, System::Loaders::filePathLoader);
				for (int i = 0; i < allSprites.size(); i++)
				{
					if (Functions::String::split(allSprites[i], ".")[1] == "png")
					{
						std::string gotTex = System::Path("Sprites/LevelSprites").add(name).add(allSprites[i]).loadResource(&texture, System::Loaders::textureLoader);
						int texW = texture.getSize().x;
						int texH = texture.getSize().y;
						break;
					}
				}
			}

			sf::Sprite texSpr;
			texSpr.setTexture(texture);
			double texW = texture.getSize().x;
			double texH = texture.getSize().y;
			double scale = (texW >= texH) ? 256 / texW : 256 / texH;
			texSpr.setScale(scale, scale);
			texSpr.setPosition(sf::Vector2f(128 - (texSpr.getGlobalBounds().width / 2), 128 - (texSpr.getGlobalBounds().height / 2)));
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
			sprNameText.setString(name);
			sprNameText.setCharacterSize(16);
			sprNameText.setColor(sf::Color(255, 255, 255));
			rtexture->draw(sprNameText);
			rtexture->display();
			texture = rtexture->getTexture();
		}

		sf::Texture SpriteFile::getTexture()
		{
			return texture;
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
							requireChoices.push_back(requires->getPath(requireItem)->getListAttribute("choices")->getElement(reqI)->get<std::string>());
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
			GUI::WidgetContainer* requireGUI = gui->getContainerByContainerName("Requires");
			std::string key = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
			Script::GameObject* newGameObject = Script::hookCore.getPointer("World")->as<World::World*>()->createGameObject(key, objName);
			for (std::string& requireItem : requires->getAllComplexAttributes())
			{
				std::string requirementName = requires->getPath(requireItem)->getBaseAttribute("name")->get<std::string>();
				bool optionalRequirement = requires->getPath(requireItem)->containsBaseAttribute("optional");
				if (optionalRequirement)
					optionalRequirement = requires->getPath(requireItem)->getBaseAttribute("optional")->get<bool>();
				if (objName + "_" + requireItem + "_Input" != "" || optionalRequirement)
				{
					if (requires->getPath(requireItem)->containsListAttribute("choices"))
						newGameObject->sendRequireArgument(requirementName, GUI::Widget::getWidgetByID<GUI::Droplist>(objName + "_" + requireItem + "_Input")->getCurrentSelected());
				}
					
			}
		}

		void loadSpriteFolder(std::string geid)
		{
			GUI::Container* gui = Script::hookCore.getPointer("GUI")->as<GUI::Container*>();
			gui->getContainerByContainerName("EditorSprites")->removeAllWidget(false);
			gui->getContainerByContainerName("EditorSprites")->addScrollBar();
			if (addFileGUIMap.find(geid) == addFileGUIMap.end())
			{
				addFileGUIMap[geid] = std::map<std::string, GUI::Button*>();
				std::cout << "Load Folder : " << geid << std::endl;
				GUI::Container* gui = Script::hookCore.getPointer("GUI")->as<GUI::Container*>();
				sf::Font font;
				System::Path("Data/Fonts/arial.ttf").loadResource(&font, System::Loaders::fontLoader);
				std::vector<SpriteFile*> spritesInCat = *addSprFolderMap[geid]->getSpriteList();
				sf::Texture sprback; sprback.loadFromFile("Sprites/Others/SprBack/arrows.png");
				spritesInCat.insert(spritesInCat.begin(), new SpriteFile("SprBack", sprback));
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
						GUI::Widget::getWidgetByID<GUI::Button>("LS_SPR_" + spritesInCat[i]->getName())->bindFunction(
							[] {displayAddSpriteFolderList(); });
					}
					else
					{
						GUI::Widget::getWidgetByID<GUI::Button>("LS_SPR_" + spritesInCat[i]->getName())->bindFunction(
							[spritesInCat, i] {addSpriteToWorld(spritesInCat[i]->getName()); });
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

		void buildAddSpriteFolderList()
		{
			GUI::Container* gui = Script::hookCore.getPointer("GUI")->as<GUI::Container*>();
			sf::Font font;
			System::Path("Data/Fonts/arial.ttf").loadResource(&font, System::Loaders::fontLoader);
			Data::DataParser addSprFolderConfigFile;
			System::Path("Sprites/LevelSprites/config.cfg.msd").loadResource(&addSprFolderConfigFile, System::Loaders::dataLoader);

			std::vector<std::string> sprNameList;
			System::Path("Sprites/LevelSprites/").loadResource(&sprNameList, System::Loaders::dirPathLoader);
			std::map<std::string, std::vector<std::string>> addSprMap;
			for (unsigned int i = 0; i < sprNameList.size(); i++)
			{
				if (Functions::String::occurencesInString(sprNameList[i], "_") == 1)
				{
					std::string currentPrefix = Functions::String::split(sprNameList[i], "_")[0];
					addSprMap[currentPrefix].push_back(Functions::String::split(sprNameList[i], "_")[1]);
				}
				else
				{
					addSprMap["OTHR"].push_back(sprNameList[i]);
				}
			}
			std::vector<std::string> folderConfigList = addSprFolderConfigFile.getPath("SpritePrefix")->getAllComplexAttributes();
			const int sprSize = 256;
			const int sprOff = 10;
			const int xOff = 15;
			const int yOff = 40;
			for (int i = 0; i < folderConfigList.size(); i++)
			{
				int xpos = (i * (sprSize + sprOff));
				int ypos = std::floor((double)xpos / (double)(1920 - (sprSize + sprOff))) * (sprSize + sprOff);
				while (xpos >(1920 - (sprSize + sprOff + xOff)))
				{
					xpos -= (1920 - (sprSize + sprOff + xOff));
				}
				xpos = std::floor((double)xpos / (double)(sprSize + sprOff)) * (sprSize + sprOff);
				xpos += xOff;
				ypos += yOff;
				gui->createButton("EditorSprites", "LS_CTG_" + folderConfigList[i], xpos, ypos, true, false, "GREY");
			}
			typedef std::map<std::string, std::vector<std::string>>::iterator it_type;
			sf::RenderTexture rtexture;
			rtexture.create(256.0 * Functions::Coord::width / Functions::Coord::baseWidth, 256.0 * Functions::Coord::height / Functions::Coord::baseHeight);
			for (it_type iterator = addSprMap.begin(); iterator != addSprMap.end(); iterator++)
			{
				std::string prefixEquivalent;
				if (Functions::Vector::isInList(iterator->first, folderConfigList))
				{
					if (addSprFolderConfigFile.getPath(Data::Path("SpritePrefix", iterator->first))->containsBaseAttribute("name"))
						prefixEquivalent = addSprFolderConfigFile.getPath(Data::Path("SpritePrefix", iterator->first))->getBaseAttribute("name")->get<std::string>();
					else
						prefixEquivalent = iterator->first;
				}
				else
					prefixEquivalent = iterator->first;
				SpriteFolder* tempFolder = new SpriteFolder(iterator->first, prefixEquivalent, "default.png", font);
				for (unsigned int i = 0; i < iterator->second.size(); i++)
				{
					tempFolder->pushSprite(new SpriteFile(iterator->first + "_" + iterator->second[i], font));
					tempFolder->getSpriteList()->at(i)->render(&rtexture);
				}
				tempFolder->render(&rtexture);
				GUI::Widget::getWidgetByID<GUI::Button>("LS_CTG_" + iterator->first)->setTextureAll(tempFolder->getTexture());
				std::string sendFolderName = iterator->first;
				GUI::Widget::getWidgetByID<GUI::Button>("LS_CTG_" + iterator->first)->bindFunction(
					[sendFolderName] {std::cout << sendFolderName << std::endl; loadSpriteFolder(sendFolderName); });
				addSprFolderMap[iterator->first] = tempFolder;
				addSprBtnGUIMap["LS_CTG_" + iterator->first] = GUI::Widget::getWidgetByID<GUI::Button>("LS_CTG_" + iterator->first);
			}
		}

		void displayAddSpriteFolderList()
		{
			GUI::Container* gui = Script::hookCore.getPointer("GUI")->as<GUI::Container*>();
			gui->getContainerByContainerName("EditorSprites")->removeAllWidget(false);
			gui->getContainerByContainerName("EditorSprites")->addScrollBar();
			for (auto it = addSprBtnGUIMap.begin(); it != addSprBtnGUIMap.end(); it++)
			{
				gui->getContainerByContainerName("EditorSprites")->addWidget(it->second);
			}
		}

		void addSpriteToWorld(std::string geid)
		{
			std::cout << "Recv geid : " << geid << std::endl;
			World::World* world = Script::hookCore.getPointer("World")->as<World::World*>();
			std::string key = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
			while (world->getSpriteByID(key) != NULL)
				key = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
			Graphics::LevelSprite* sprToAdd = new Graphics::LevelSprite(geid, key);
			sprToAdd->move(960 + world->getCamX(), 540 + world->getCamY());
			sprToAdd->setRotation(0);
			sprToAdd->setScale(1, 1);
			sprToAdd->setAtr(std::vector<std::string>());
			sprToAdd->setLayer(1);
			sprToAdd->setZDepth(1);
			sprToAdd->textureUpdate();
			world->addLevelSprite(sprToAdd);
		}
	}
}