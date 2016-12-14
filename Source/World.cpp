//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "World.hpp"

namespace mse
{
	namespace World
	{
		World::World()
		{
			worldScriptEngine = new kaguya::State();
			loadWorldScriptEngineBaseLib(worldScriptEngine);
			(*worldScriptEngine)["World"] = this;
			System::Path("Lib/GameLib/WScrInit.lua").loadResource(worldScriptEngine, System::Loaders::luaLoader);
			Script::loadLib(worldScriptEngine, "Core.*");
			Script::TriggerDatabase::GetInstance()->createNamespace("Map");
			showCollisionModes["drawLines"] = false;
			showCollisionModes["drawPoints"] = false;
			showCollisionModes["drawMasterPoint"] = false;
			showCollisionModes["drawSkel"] = false;
			blurShader.loadFromFile("Data/Shaders/blur.frag", sf::Shader::Fragment);
			normalShader.loadFromFile("Data/Shaders/normalMap.frag", sf::Shader::Fragment);
			worldScriptEngine->dofile("boot.lua");
		}

		void World::addCharacter(Character* character)
		{
			charArray.push_back(character);
			character->setColliders(&this->collidersArray);
			character->setPos(this->getStartX(), this->getStartY());
			character->update();
		}

		void World::addLevelSprite(Graphics::LevelSprite* spr)
		{
			if (spr->getLayer() >= 1)
				backSpriteArray.push_back(spr);
			else if (spr->getLayer() <= -2)
				frontSpriteArray.push_back(spr);
			this->reorganizeLayers();
		}

		void World::addCollider(Collision::PolygonalCollider* col)
		{
			this->collidersArray.push_back(col);
		}

		void World::addLight(Light::PointLight* lgt)
		{
			lightsMap[lgt->getID()] = lgt;
		}

		kaguya::State * World::getScriptEngine()
		{
			return worldScriptEngine;
		}

		std::string World::getBaseFolder()
		{
			return baseFolder;
		}

		Character* World::getCharacter(int index)
		{
			return charArray[index];
		}

		void World::loadFromFile(std::string filename)
		{
			this->clearWorld();
			double startLoadTime = Time::getTickSinceEpoch();
			int arrayLoad = 0;
			int arrayLoadFrontDeco = 0;
			int arrayLoadBackDeco = 0;
			int indexInFile = 0;
			Data::DataParser mapParse;
			std::cout << "Creation Chrono : " << "[WorldStart]" << Time::getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = Time::getTickSinceEpoch();
			baseFolder = System::Path("Data/Maps").add(filename).loadResource(&mapParse, System::Loaders::dataLoader);
			mapParse.writeFile("rewrite.msd");
			std::cout << "Creation Chrono : " << "[WorldParse]" << Time::getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = Time::getTickSinceEpoch();
			mapParse.hookNavigator(new Data::DataParserNavigator())->setCurrentRootAttribute("Meta");

			levelName = mapParse.getBaseAttribute("Level")->get<std::string>();
			sizeX = mapParse.getBaseAttribute("SizeX")->get<int>();
			sizeY = mapParse.getBaseAttribute("SizeY")->get<int>();
			if (mapParse.containsBaseAttribute("StartX"))
				startX = mapParse.getBaseAttribute("StartX")->get<int>();
			if (mapParse.containsBaseAttribute("StartY"))
				startY = mapParse.getBaseAttribute("StartY")->get<int>();

			std::cout << "Creation Chrono : " << "[WorldMeta]" << Time::getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = Time::getTickSinceEpoch();

			if (mapParse.containsRootAttribute("LevelSprites"))
			{
				std::vector<std::string> allDecos = mapParse.getPath("LevelSprites")->getAllComplexAttributes();
				for (unsigned int i = 0; i < allDecos.size(); i++)
				{
					mapParse.accessNavigator()->setCurrentRootAttribute("LevelSprites", allDecos[i]);
					std::string decoID, decoType;
					int decoPosX, decoPosY;
					int decoRot = 0;
					double decoSca = 1.0;
					std::vector<std::string> decoAtrList;
					int layer;
					int zdepth;
					decoID = allDecos[i];
					decoType = mapParse.getBaseAttribute("type")->get<std::string>();
					decoPosX = mapParse.getBaseAttribute("posX")->get<int>();
					decoPosY = mapParse.getBaseAttribute("posY")->get<int>();
					decoRot = mapParse.getBaseAttribute("rotation")->get<int>();
					decoSca = mapParse.getBaseAttribute("scale")->get<double>();
					layer = mapParse.getBaseAttribute("layer")->get<int>();
					zdepth = mapParse.getBaseAttribute("z-depth")->get<int>();
					if (mapParse.containsListAttribute("attributeList"))
					{
						int atrListSize = mapParse.getListSize("attributeList");
						for (int j = 0; j < atrListSize; j++)
							decoAtrList.push_back(mapParse.getListItem("attributeList", j)->get<std::string>());
					}
					Graphics::LevelSprite* tempDeco = new Graphics::LevelSprite(decoID);
					if (decoType != "None")
					{
						delete tempDeco;
						tempDeco = new Graphics::LevelSprite(decoType, decoID);
					}
					tempDeco->move(decoPosX, decoPosY);
					tempDeco->setRotation(decoRot);
					tempDeco->setScale(decoSca, decoSca);
					tempDeco->setAtr(decoAtrList);
					tempDeco->setLayer(layer);
					tempDeco->setZDepth(zdepth);
					tempDeco->textureUpdate();
					if (layer >= 1)
						backSpriteArray.push_back(tempDeco);
					else if (layer <= -1)
						frontSpriteArray.push_back(tempDeco);
				}
			}
			std::cout << "Creation Chrono : " << "[WorldLevelSprites]" << Time::getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = Time::getTickSinceEpoch();


			this->reorganizeLayers();
			std::cout << "Creation Chrono : " << "[WorldReorganize]" << Time::getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = Time::getTickSinceEpoch();


			if (mapParse.containsRootAttribute("Lights"))
			{
				mapParse.accessNavigator()->setCurrentRootAttribute("Lights");
				std::vector<std::string> allLights = mapParse.getAllComplexAttributes();
				for (int i = 0; i < allLights.size(); i++)
				{
					mapParse.accessNavigator()->setCurrentRootAttribute("Lights", allLights[i]);
					std::string ltype = mapParse.getBaseAttribute("type")->get<std::string>();
					if (ltype == "Static")
					{
						double lsize;
						double lr, lg, lb, la;
						std::string lsBind;
						bool lbehind;
						double loffX = 0;
						double loffY = 0;
						lsize = mapParse.getBaseAttribute("size")->get<double>();
						lr = mapParse.getBaseAttribute("r")->get<double>();
						lg = mapParse.getBaseAttribute("g")->get<double>();
						lb = mapParse.getBaseAttribute("b")->get<double>();
						la = mapParse.getBaseAttribute("a")->get<double>();
						lsBind = mapParse.getBaseAttribute("bind")->get<std::string>();
						lbehind = mapParse.getBaseAttribute("behind")->get<bool>();
						if (mapParse.containsBaseAttribute("offsetX")) loffX = mapParse.getBaseAttribute("offsetX")->get<double>();
						if (mapParse.containsBaseAttribute("offsetY")) loffY = mapParse.getBaseAttribute("offsetY")->get<double>();
						if (getSpriteByID(lsBind) != NULL)
						{
							lightsMap[lsBind] = new Light::PointLight(allLights[i], sf::Vector2f(1920, 1080), sf::Vector2f(0, 0), lsize, sf::Color(lr, lg, lb, la));
							lightsMap[lsBind]->setOffset(loffX, loffY);
						}
					}
					else if (ltype == "Dynamic")
					{
						double lprecision;
						std::string lsize;
						std::string lr, lg, lb, la;
						std::string lsBind;
						bool lbehind;
						std::string loffX = "0";
						std::string loffY = "0";

						lprecision = mapParse.getBaseAttribute("precision")->get<double>();
						lsize = mapParse.getBaseAttribute("size")->get<std::string>();
						lr = mapParse.getBaseAttribute("r")->get<std::string>();
						lg = mapParse.getBaseAttribute("g")->get<std::string>();
						lb = mapParse.getBaseAttribute("b")->get<std::string>();
						la = mapParse.getBaseAttribute("a")->get<std::string>();
						lsBind = mapParse.getBaseAttribute("bind")->get<std::string>();
						lbehind = mapParse.getBaseAttribute("behind")->get<bool>();
						if (mapParse.containsBaseAttribute("offsetX")) loffX = mapParse.getBaseAttribute("offsetX")->get<std::string>();
						if (mapParse.containsBaseAttribute("offsetY")) loffY = mapParse.getBaseAttribute("offsetY")->get<std::string>();
						if (getSpriteByID(lsBind) != NULL)
						{
							Light::DynamicPointLight* tdpl = new Light::DynamicPointLight(allLights[i], sf::Vector2f(1920, 1080), lprecision);
							tdpl->setSizeExp(lsize);
							tdpl->setRExp(lr); tdpl->setGExp(lg); tdpl->setBExp(lb);
							tdpl->setOffsetXExp(loffX);
							tdpl->setOffsetYExp(loffY);
							lightsMap[lsBind] = tdpl;
						}
					}
				}
			}
			std::cout << "Creation Chrono : " << "[WorldLights]" << Time::getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = Time::getTickSinceEpoch();

			if (mapParse.containsRootAttribute("Collisions"))
			{
				mapParse.accessNavigator()->setCurrentRootAttribute("Collisions");
				std::vector<std::string> allCol = mapParse.getAllComplexAttributes();
				for (unsigned int i = 0; i < allCol.size(); i++)
				{
					mapParse.accessNavigator()->setCurrentRootAttribute("Collisions", allCol[i]);
					Collision::PolygonalCollider* tempCollider = new Collision::PolygonalCollider(allCol[i]);
					std::cout << "[World] Creating Collider : " << allCol[i] << std::endl;
					for (unsigned int j = 0; j < mapParse.getListSize("polygonPoints"); j++)
					{
						std::string getPt = mapParse.getListItem("polygonPoints", j)->get<std::string>();
						std::vector<std::string> tPoint = Functions::String::split(getPt, ",");
						tempCollider->addPoint(std::stoi(tPoint[0]), std::stoi(tPoint[1]));
						std::cout << "[World::Collider] Add Point : " << tPoint[0] << " ," << tPoint[1] << std::endl;
					}
					this->collidersArray.push_back(tempCollider);
				}
			}
			std::cout << "Creation Chrono : " << "[WorldCollisions]" << Time::getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = Time::getTickSinceEpoch();


			if (mapParse.containsRootAttribute("LevelObjects"))
			{
				mapParse.accessNavigator()->setCurrentRootAttribute("LevelObjects");
				std::vector<std::string> allObjects = mapParse.getAllComplexAttributes();
				for (unsigned int i = 0; i < allObjects.size(); i++)
				{
					mapParse.accessNavigator()->setCurrentRootAttribute("LevelObjects", allObjects[i]);
					std::string levelObjectType = mapParse.getBaseAttribute("type")->get<std::string>();
					this->createGameObject(allObjects[i], levelObjectType);
					int objX = 0;
					int objY = 0;
					int colOffX = 0;
					int colOffY = 0;
					if (mapParse.containsComplexAttribute("Requires"))
						Script::GameObjectRequires::ApplyRequirements(this->getGameObject(allObjects[i]), *mapParse.getComplexAttribute("Requires"));
					/*if (this->getGameObject(allObjects[i])->canDisplay())
					{
						if (mapParse.containsBaseAttribute("posX"))
							objX = mapParse.getBaseAttribute("posX")->get<int>();
						if (mapParse.containsBaseAttribute("posY"))
							objY = mapParse.getBaseAttribute("posY")->get<int>();
						this->getGameObject(allObjects[i])->getLevelSprite()->setPosition(objX, objY);
					}
					if (getGameObject(allObjects[i])->hasCollider)
					{
						this->getGameObject(allObjects[i])->getCollider()->setPosition(objX, objY);
					}*/
				}
			}
			std::cout << "Creation Chrono : " << "[WorldLevelObjects]" << Time::getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = Time::getTickSinceEpoch();

			if (mapParse.containsRootAttribute("Script"))
			{
				mapParse.accessNavigator()->setCurrentRootAttribute("Script");
				int scriptAmt = mapParse.getListAttribute("gameScripts")->getSize();
				for (int i = 0; i < scriptAmt; i++)
				{
					std::string scriptName = mapParse.getListAttribute("gameScripts")->getElement(i)->get<std::string>();
					System::Path(scriptName).loadResource(worldScriptEngine, System::Loaders::luaLoader);
					scriptArray.push_back(scriptName);
				}
			}
			std::cout << "Creation Chrono : " << "[WorldScript]" << Time::getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = Time::getTickSinceEpoch();
			Script::TriggerDatabase::GetInstance()->update();
			for (int i = 0; i < updateObjArray.size(); i++)
			{
				updateObjArray[i]->update(gameSpeed);
			}
		}

		void World::clearWorld()
		{
			std::cout << "Clearing World" << std::endl;
			/*for (int i = 0; i < backSpriteArray.size(); i++)
			delete backSpriteArray[i];*/
			std::cout << "Clearing bSpriteArray [Done]" << std::endl;
			backSpriteArray.clear();
			/*for (int i = 0; i < frontSpriteArray.size(); i++)
			delete frontSpriteArray[i];*/
			frontSpriteArray.clear();
			std::cout << "Clearing fSpriteArray [Done]" << std::endl;
			/*for (int i = 0; i < collidersArray.size(); i++)
			delete collidersArray[i];*/
			collidersArray.clear();
			std::cout << "Clearing collidersArray [Done]" << std::endl;
			/*for (auto it = gameObjectsMap.begin(); it != gameObjectsMap.end(); it++)
			delete it->second;*/
			gameObjectsMap.clear();
			updateObjArray.clear();
			std::cout << "Clearing gameObjectsMap [Done]" << std::endl;
			/*for (auto it = lightsMap.begin(); it != lightsMap.end(); it++)
			delete it->second;*/
			lightsMap.clear();
			std::cout << "Clearing lightsMapArray [Done]" << std::endl;
			/*for (int i = 0; i < particleArray.size(); i++)
			delete particleArray[i];*/
			particleArray.clear();
			std::cout << "Clearing particlesArray [Done]" << std::endl;
			scriptArray.clear();
			std::cout << "Clearing scriptArray [Done]" << std::endl;
		}

		Data::DataParser* World::saveData()
		{
			Data::DataParser* dataStore = new Data::DataParser;
			dataStore->createFlag("Map");
			dataStore->createFlag("Lock");
			dataStore->createRootAttribute("Meta");
			dataStore->getPath("Meta")->createBaseAttribute("Level", levelName);
			dataStore->getPath("Meta")->createBaseAttribute("SizeX", sizeX);
			dataStore->getPath("Meta")->createBaseAttribute("SizeY", sizeY);
			dataStore->getPath("Meta")->createBaseAttribute("StartX", startX);
			dataStore->getPath("Meta")->createBaseAttribute("StartY", startY);
			dataStore->createRootAttribute("LevelSprites");
			for (unsigned int i = 0; i < backSpriteArray.size(); i++)
			{
				if (backSpriteArray[i]->getParent() == nullptr)
				{
					dataStore->getPath("LevelSprites")->createComplexAttribute(backSpriteArray[i]->getID());
					dataStore->getPath(Data::Path("LevelSprites", backSpriteArray[i]->getID()))->createBaseAttribute("type", backSpriteArray[i]->getName());
					dataStore->getPath(Data::Path("LevelSprites", backSpriteArray[i]->getID()))->createBaseAttribute("posX", (int)backSpriteArray[i]->getX());
					dataStore->getPath(Data::Path("LevelSprites", backSpriteArray[i]->getID()))->createBaseAttribute("posY", (int)backSpriteArray[i]->getY());
					dataStore->getPath(Data::Path("LevelSprites", backSpriteArray[i]->getID()))->createBaseAttribute("rotation", (int)backSpriteArray[i]->getRotation());
					dataStore->getPath(Data::Path("LevelSprites", backSpriteArray[i]->getID()))->createBaseAttribute("scale", backSpriteArray[i]->getScaleX());
					dataStore->getPath(Data::Path("LevelSprites", backSpriteArray[i]->getID()))->createBaseAttribute("layer", (int)backSpriteArray[i]->getLayer());
					dataStore->getPath(Data::Path("LevelSprites", backSpriteArray[i]->getID()))->createBaseAttribute("z-depth", (int)backSpriteArray[i]->getZDepth());
					if (backSpriteArray[i]->getAttributes().size() != 0)
					{
						dataStore->getPath(Data::Path("LevelSprites", backSpriteArray[i]->getID()))->createListAttribute("attributeList", "string");
						for (unsigned int j = 0; j < backSpriteArray[i]->getAttributes().size(); j++)
							dataStore->getPath(Data::Path("LevelSprites", backSpriteArray[i]->getID()))->createListItem("attributeList", backSpriteArray[i]->getAttributes()[j]);
					}
				}
			}
			for (unsigned int i = 0; i < frontSpriteArray.size(); i++)
			{
				if (frontSpriteArray[i]->getParent() == nullptr)
				{
					dataStore->getPath("LevelSprites")->createComplexAttribute(frontSpriteArray[i]->getID());
					dataStore->getPath(Data::Path("LevelSprites", frontSpriteArray[i]->getID()))->createBaseAttribute("type", frontSpriteArray[i]->getName());
					dataStore->getPath(Data::Path("LevelSprites", frontSpriteArray[i]->getID()))->createBaseAttribute("posX", (int)frontSpriteArray[i]->getX());
					dataStore->getPath(Data::Path("LevelSprites", frontSpriteArray[i]->getID()))->createBaseAttribute("posY", (int)frontSpriteArray[i]->getY());
					dataStore->getPath(Data::Path("LevelSprites", frontSpriteArray[i]->getID()))->createBaseAttribute("rotation", (int)frontSpriteArray[i]->getRotation());
					dataStore->getPath(Data::Path("LevelSprites", frontSpriteArray[i]->getID()))->createBaseAttribute("scale", frontSpriteArray[i]->getScaleX());
					dataStore->getPath(Data::Path("LevelSprites", frontSpriteArray[i]->getID()))->createBaseAttribute("layer", (int)frontSpriteArray[i]->getLayer());
					dataStore->getPath(Data::Path("LevelSprites", frontSpriteArray[i]->getID()))->createBaseAttribute("z-depth", (int)frontSpriteArray[i]->getZDepth());
					if (frontSpriteArray[i]->getAttributes().size() != 0)
					{
						dataStore->getPath(Data::Path("LevelSprites", frontSpriteArray[i]->getID()))->createListAttribute("attributeList", "string");
						for (unsigned int j = 0; j < frontSpriteArray[i]->getAttributes().size(); j++)
							dataStore->getPath(Data::Path("LevelSprites", frontSpriteArray[i]->getID()))->createListItem("attributeList", frontSpriteArray[i]->getAttributes()[j]);
					}
				}
			}
			dataStore->createRootAttribute("Collisions");
			for (unsigned int i = 0; i < collidersArray.size(); i++)
			{
				if (collidersArray[i]->getParent() == nullptr)
				{
					dataStore->getPath("Collisions")->createComplexAttribute(collidersArray[i]->getID());
					dataStore->getPath(Data::Path("Collisions", collidersArray[i]->getID()))->createListAttribute("polygonPoints", "string");
					for (unsigned int j = 0; j < collidersArray[i]->getPointsAmount(); j++)
					{
						int px = collidersArray[i]->getPointPosition(j).first;
						int py = collidersArray[i]->getPointPosition(j).second;
						dataStore->getPath(Data::Path("Collisions", collidersArray[i]->getID()))->createListItem("polygonPoints", std::to_string(px) + "," + std::to_string(py));
					}
				}
			}
			dataStore->createRootAttribute("LevelObjects");
			for (auto it = gameObjectsMap.begin(); it != gameObjectsMap.end(); it++)
			{
				dataStore->getPath("LevelObjects")->createComplexAttribute(it->first);
				dataStore->getPath(Data::Path("LevelObjects", it->first))->createBaseAttribute("type", it->second->getType());
				(*it->second->getScriptEngine())("inspect = require('Lib/StdLib/Inspect');");
				kaguya::LuaTable saveTable = (*it->second->getScriptEngine())["Local.Save"]();
				(*it->second->getScriptEngine())("tnt = Local.Save()");
				kaguya::LuaRef saveTableRef = (*it->second->getScriptEngine())["tnt"];
				std::cout << "GNGN Type : " << saveTable.type() << std::endl;
				(*it->second->getScriptEngine())("print(inspect(Local.Save()));");
				Data::ComplexAttribute* saveRequirements = Data::DataBridge::luaTableToComplexAttribute(
					"Requires", saveTableRef);
				dataStore->getPath(Data::Path("LevelObjects", it->first))->pushComplexAttribute(saveRequirements);
				//(*it->second->getScriptEngine())["Lua_ReqList"];
				//dataStore->getPath(Data::Path("LevelObjects", it->first, "Requires"))->createBaseAttribute("posX", (int)it->second->getLevelSprite()->getX());
				//dataStore->getPath(Data::Path("LevelObjects", it->first, "Requires"))->createBaseAttribute("posY", (int)it->second->getLevelSprite()->getY());
			}
			if (scriptArray.size() > 0)
			{
				dataStore->createRootAttribute("Script");
				dataStore->getPath("Script")->createListAttribute("gameScripts", "string");
				for (int i = 0; i < scriptArray.size(); i++) {
					dataStore->getPath("Script")->createListItem("gameScripts", scriptArray[i]);
				}
			}
			return dataStore;
		}

		void World::update(double dt)
		{
			if (updateState)
			{
				this->gameSpeed = dt;
				for (int i = 0; i < updateObjArray.size(); i++)
				{
					if (!updateObjArray[i]->deletable)
						updateObjArray[i]->update(dt);
					else
					{
						if (updateObjArray[i]->hasAnimator)
							this->deleteCollision(updateObjArray[i]->getCollider(), false);
						if (updateObjArray[i]->hasLevelSprite)
							this->deleteSprite(updateObjArray[i]->getLevelSprite(), false);
						updateObjArray.erase(updateObjArray.begin() + i);
					}
				}
				typedef std::map<std::string, Light::PointLight*>::iterator it_mspl;
				for (it_mspl iterator = lightsMap.begin(); iterator != lightsMap.end(); iterator++)
				{
					if (iterator->second->getType() == "Dynamic")
					{
						dynamic_cast<Light::DynamicPointLight*>(iterator->second)->updateLight();
					}
				}
				for (unsigned int i = 0; i < charArray.size(); i++)
				{
					charArray[i]->setDeltaTime(gameSpeed);
					charArray[i]->getCamPos(camX, camY);
					charArray[i]->update();
				}
				for (unsigned int i = 0; i < particleArray.size(); i++)
				{
					particleArray[i]->update();
				}
			}
		}

		void World::display(sf::RenderWindow* surf)
		{
			visualDisplayBack(surf);
			for (unsigned int i = 0; i < charArray.size(); i++)
			{
				charArray[i]->setColliderDrawOffset(-camX, -camY);
				charArray[i]->draw(surf);
				if (showCollisionModes["drawLines"]) charArray[i]->getEntityCollider()->draw(surf);
			}
			for (unsigned int i = 0; i < particleArray.size(); i++)
			{
				particleArray[i]->draw(surf);
			}
			visualDisplayFront(surf);
			if (showCollisionModes["drawLines"] || showCollisionModes["drawPoints"] || showCollisionModes["drawMasterPoint"] || showCollisionModes["drawSkel"])
			{
				for (unsigned int i = 0; i < collidersArray.size(); i++)
				{
					collidersArray[i]->setDrawOffset(-camX, -camY);
					collidersArray[i]->draw(surf, showCollisionModes["drawLines"], showCollisionModes["drawPoints"], showCollisionModes["drawMasterPoint"], showCollisionModes["drawSkel"]);
				}
			}
		}

		void World::visualDisplayBack(sf::RenderWindow* surf)
		{
			for (unsigned int i = 0; i < backSpriteArray.size(); i++)
			{
				int layeredX = 0;
				int layeredY = 0;

				bool lightHooked = lightsMap.find(backSpriteArray[i]->getID()) != lightsMap.end();
				Light::PointLight* cLight = NULL;
				if (lightHooked) cLight = lightsMap[backSpriteArray[i]->getID()];

				layeredX = (((backSpriteArray[i]->getX() + backSpriteArray[i]->getOffsetX()) * (backSpriteArray[i]->getLayer()) - camX) / backSpriteArray[i]->getLayer());
				layeredY = (((backSpriteArray[i]->getY() + backSpriteArray[i]->getOffsetY()) * (backSpriteArray[i]->getLayer()) - camY) / backSpriteArray[i]->getLayer());
				if (Functions::Vector::isInList((std::string)"+FIX", backSpriteArray[i]->getAttributes()))
				{
					layeredX = backSpriteArray[i]->getX() + backSpriteArray[i]->getOffsetX();
					layeredY = backSpriteArray[i]->getY() + backSpriteArray[i]->getOffsetY();
				}
				else if (Functions::Vector::isInList((std::string)"+HFIX", backSpriteArray[i]->getAttributes()))
				{
					layeredX = backSpriteArray[i]->getX() + backSpriteArray[i]->getOffsetX();
				}
				else if (Functions::Vector::isInList((std::string)"+VFIX", backSpriteArray[i]->getAttributes()))
				{
					layeredY = backSpriteArray[i]->getY() + backSpriteArray[i]->getOffsetY();
				}
				else if (Functions::Vector::isInList((std::string)"+PHFIX", backSpriteArray[i]->getAttributes()))
				{
					layeredX = backSpriteArray[i]->getX() + backSpriteArray[i]->getOffsetX() - camX;
				}
				else if (Functions::Vector::isInList((std::string)"+PVFIX", backSpriteArray[i]->getAttributes()))
				{
					layeredY = backSpriteArray[i]->getY() + backSpriteArray[i]->getOffsetY() - camY;
				}
				else if (Functions::Vector::isInList((std::string)"+PFIX", backSpriteArray[i]->getAttributes()))
				{
					layeredX = backSpriteArray[i]->getX() + backSpriteArray[i]->getOffsetX() - camX;
					layeredY = backSpriteArray[i]->getY() + backSpriteArray[i]->getOffsetY() - camY;
				}
				backSpriteArray[i]->textureUpdate();
				sfe::ComplexSprite tAffSpr;
				blurShader.setParameter("texture", sf::Shader::CurrentTexture);
				blurShader.setParameter("blur_radius", blurMul*(backSpriteArray[i]->getLayer() - 1));
				tAffSpr = *backSpriteArray[i]->getSprite();

				if (lightHooked) cLight->setPosition(layeredX, layeredY);
				tAffSpr.setPosition(layeredX, layeredY);
				if (lightHooked) { if (cLight->isBehind()) lightsMap[backSpriteArray[i]->getID()]->draw(surf); }
				if (backSpriteArray[i]->isVisible())
				{
					//std::cout << "Displaying : " << backSpriteArray[i]->getID() << " at " << layeredX << "," << layeredY << " >> " << tAffSpr.getGlobalBounds().width << "," << tAffSpr.getGlobalBounds().height << std::endl;
					surf->draw(tAffSpr, &blurShader);
				}
				if (lightHooked) { if (!cLight->isBehind()) lightsMap[backSpriteArray[i]->getID()]->draw(surf); }
			}
		}

		void World::visualDisplayFront(sf::RenderWindow* surf)
		{
			for (unsigned int i = 0; i < frontSpriteArray.size(); i++)
			{
				int layeredX = 0;
				int layeredY = 0;

				bool lightHooked = lightsMap.find(frontSpriteArray[i]->getID()) != lightsMap.end();
				Light::PointLight* cLight = NULL;
				if (lightHooked) cLight = lightsMap[frontSpriteArray[i]->getID()];

				if (Functions::Vector::isInList((std::string)"+FIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = frontSpriteArray[i]->getX();
					layeredY = frontSpriteArray[i]->getY();
				}
				else if (Functions::Vector::isInList((std::string)"+VFIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = ((frontSpriteArray[i]->getX() / (frontSpriteArray[i]->getLayer()) + camX) * frontSpriteArray[i]->getLayer());
					layeredY = frontSpriteArray[i]->getY();
				}
				else if (Functions::Vector::isInList((std::string)"+HFIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = frontSpriteArray[i]->getX();
					layeredY = ((frontSpriteArray[i]->getY() / (frontSpriteArray[i]->getLayer()) + camY) * frontSpriteArray[i]->getLayer());
				}
				else if (Functions::Vector::isInList((std::string)"+PHFIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = frontSpriteArray[i]->getX() - camX;
					layeredY = ((frontSpriteArray[i]->getY() / (frontSpriteArray[i]->getLayer()) + camY) * frontSpriteArray[i]->getLayer());
				}
				else if (Functions::Vector::isInList((std::string)"+PVFIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = ((frontSpriteArray[i]->getX() / (frontSpriteArray[i]->getLayer()) + camX) * frontSpriteArray[i]->getLayer());
					layeredY = frontSpriteArray[i]->getY() - camY;
				}
				else if (Functions::Vector::isInList((std::string)"+PFIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = frontSpriteArray[i]->getX() - camX;
					layeredY = frontSpriteArray[i]->getY() - camY;
				}
				else
				{
					layeredX = ((frontSpriteArray[i]->getX() / (frontSpriteArray[i]->getLayer()) + camX) * frontSpriteArray[i]->getLayer());
					layeredY = ((frontSpriteArray[i]->getY() / (frontSpriteArray[i]->getLayer()) + camY) * frontSpriteArray[i]->getLayer());
				}

				frontSpriteArray[i]->textureUpdate();
				sfe::ComplexSprite tAffSpr;
				blurShader.setParameter("texture", sf::Shader::CurrentTexture);
				blurShader.setParameter("blur_radius", blurMul*(backSpriteArray[i]->getLayer() - 1));
				tAffSpr = *frontSpriteArray[i]->getSprite();

				if (lightHooked) cLight->setPosition(layeredX, layeredY);
				tAffSpr.setPosition(layeredX, layeredY);
				if (lightHooked) { if (cLight->isBehind()) lightsMap[frontSpriteArray[i]->getID()]->draw(surf); }
				if (frontSpriteArray[i]->isVisible())
					surf->draw(tAffSpr, &blurShader);
				if (lightHooked) { if (!cLight->isBehind()) lightsMap[frontSpriteArray[i]->getID()]->draw(surf); }
			}
		}

		void World::setSize(int sizeX, int sizeY)
		{
			this->sizeX = sizeX;
			this->sizeY = sizeY;
		}

		int World::getSizeX()
		{
			return sizeX;
		}

		int World::getSizeY()
		{
			return sizeY;
		}

		std::vector<Collision::PolygonalCollider*> World::getColliders()
		{
			return collidersArray;
		}

		void World::setCameraPosition(double tX, double tY, std::string setMode)
		{
			if (setMode == "SET")
			{
				camX = tX;
				camY = tY;
			}
			if (setMode == "FOLLOW")
			{
				double camInerty = 0.2;
				camX += (tX - camX) * camInerty * gameSpeed;
				camY += (tY - camY) * camInerty * gameSpeed;
			}

			if (camX < 0)
				camX = 0;
			if (camX + Functions::Coord::width > sizeX)
				camX = sizeX - Functions::Coord::width;
			if (camY <= 0)
				camY = 0;
			if (camY + Functions::Coord::height > sizeY)
				camY = sizeY - Functions::Coord::height;
		}

		double World::getCamX()
		{
			return camX;
		}

		double World::getCamY()
		{
			return camY;
		}

		void World::setBlurMul(double newBlur)
		{
			blurMul = newBlur;
		}

		int World::getStartX()
		{
			return startX;
		}

		int World::getStartY()
		{
			return startY;
		}

		void World::setUpdateState(bool state)
		{
			updateState = state;
		}

		Script::GameObject* World::getGameObject(std::string id)
		{
			if (gameObjectsMap.find(id) != gameObjectsMap.end())
				return gameObjectsMap[id];
			else
				std::cout << "<Error:World:World>[getGameObject] : Can't find GameObject : " << id << std::endl;
		}

		std::vector<Script::GameObject*> World::getAllGameObjects(std::vector<std::string> filters)
		{
			std::vector<Script::GameObject*> returnVec;
			for (auto it = gameObjectsMap.begin(); it != gameObjectsMap.end(); it++)
			{
				if (filters.size() == 0) returnVec.push_back(it->second);
				else
				{

					bool allFilters = true;
					if (Functions::Vector::isInList(std::string("Display"), filters)) { if (!it->second->canDisplay()) allFilters = false; }
					if (Functions::Vector::isInList(std::string("Collide"), filters)) { if (!it->second->canCollide()) allFilters = false; }
					if (Functions::Vector::isInList(std::string("Click"), filters)) { if (!it->second->canClick()) allFilters = false; }
					if (allFilters) returnVec.push_back(it->second);
				}
			}
			return returnVec;
		}

		Script::GameObject* World::createGameObject(std::string id, std::string obj)
		{
			Script::GameObject* newGameObject = new Script::GameObject(obj, id);
			Data::DataParser getGameObjectFile;
			System::Path("Data/GameObjects/").add(obj).add(obj + ".obj.msd").loadResource(&getGameObjectFile, System::Loaders::dataLoader);
			Data::ComplexAttribute* gameObjectData = getGameObjectFile.getRootAttribute(obj);
			newGameObject->loadGameObject(gameObjectData);
			newGameObject->scriptEngine = new kaguya::State;
			this->gameObjectsMap[id] = newGameObject;
			newGameObject->privateKey = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 12);
			newGameObject->publicKey = Functions::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 12);
			Script::TriggerDatabase::GetInstance()->createNamespace(newGameObject->privateKey);
			Script::TriggerDatabase::GetInstance()->createNamespace(newGameObject->publicKey);
			newGameObject->localTriggers = Script::TriggerDatabase::GetInstance()->createTriggerGroup(newGameObject->privateKey, "Local");
			//Script Loading
			System::Path("Lib/GameLib/ScrInit.lua").loadResource(newGameObject->scriptEngine, System::Loaders::luaLoader);
			System::Path("Lib/GameLib/ObjectInit.lua").loadResource(newGameObject->scriptEngine, System::Loaders::luaLoader);
			loadScrGameObject(newGameObject, newGameObject->scriptEngine);
			(*newGameObject->scriptEngine)["ID"] = id;
			(*newGameObject->scriptEngine)["Private"] = newGameObject->privateKey;
			(*newGameObject->scriptEngine)["Public"] = newGameObject->publicKey;
			(*newGameObject->scriptEngine)("protect(\"ID\")");
			(*newGameObject->scriptEngine)("protect(\"Private\")");
			(*newGameObject->scriptEngine)("protect(\"Public\")");
			loadWorldLib(newGameObject->scriptEngine);
			newGameObject->localTriggers->addTrigger("Init");
			newGameObject->localTriggers->setTriggerState("Init", true); // Supposed to be triggered by UseLocalTrigger ??
			newGameObject->localTriggers->addTrigger("Update");
			newGameObject->localTriggers->setPermanent("Update", true);
			newGameObject->localTriggers->setTriggerState("Update", true);
			newGameObject->localTriggers->addTrigger("Query");
			newGameObject->localTriggers->addTrigger("Collide");
			newGameObject->localTriggers->addTrigger("Click");
			newGameObject->localTriggers->addTrigger("Press");
			newGameObject->localTriggers->addTrigger("Delete");
			int scriptListSize = gameObjectData->getPath("Script")->getListAttribute("scriptList")->getSize();
			for (int i = 0; i < scriptListSize; i++)
			{
				std::string getScrName = gameObjectData->getPath("Script")->getListAttribute("scriptList")->getElement(i)->get<std::string>();
				System::Path(getScrName).loadResource(newGameObject->scriptEngine, System::Loaders::luaLoader);
			}
			this->orderUpdateScrArray();
			if (newGameObject->canDisplay())
			{
				this->addLevelSprite(newGameObject->getLevelSprite());
				if (newGameObject->canDisplay() && newGameObject->isLevelSpriteRelative())
					newGameObject->getLevelSprite()->setPosition(0, 0);
			}
			if (newGameObject->hasCollider)
			{
				this->addCollider(newGameObject->getCollider());
			}
			newGameObject->getLevelSprite()->setParent(newGameObject);
			newGameObject->getCollider()->setParent(newGameObject);
			(*newGameObject->scriptEngine)["World"] = this;
			delete gameObjectData;
			return newGameObject;
		}

		void World::orderUpdateScrArray()
		{
			updateObjArray.clear();
			for (auto it = gameObjectsMap.begin(); it != gameObjectsMap.end(); it++)
			{
				updateObjArray.push_back(it->second);
			}
			std::sort(updateObjArray.begin(), updateObjArray.end(), Script::orderScrPriority);
		}

		void World::addParticle(Graphics::MathParticle* particle)
		{
			particleArray.push_back(particle);
		}

		void World::reorganizeLayers()
		{
			bool noChange = false;
			while (noChange == false)
			{
				noChange = true;
				for (unsigned int i = 0; i < backSpriteArray.size(); i++)
				{
					if (i != backSpriteArray.size() - 1)
					{
						if (backSpriteArray[i]->getLayer() < backSpriteArray[i + 1]->getLayer())
						{
							Graphics::LevelSprite* saveLayer = backSpriteArray[i];
							backSpriteArray[i] = backSpriteArray[i + 1];
							backSpriteArray[i + 1] = saveLayer;
							noChange = false;
						}
					}
				}
			}
			noChange = false;
			while (noChange == false)
			{
				noChange = true;
				for (unsigned int i = 0; i < backSpriteArray.size(); i++)
				{
					if (i != backSpriteArray.size() - 1)
					{
						if (backSpriteArray[i]->getLayer() == backSpriteArray[i + 1]->getLayer())
						{
							if (backSpriteArray[i]->getZDepth() < backSpriteArray[i + 1]->getZDepth())
							{
								Graphics::LevelSprite* saveLayer = backSpriteArray[i];
								backSpriteArray[i] = backSpriteArray[i + 1];
								backSpriteArray[i + 1] = saveLayer;
								noChange = false;
							}
						}
					}
				}
			}


			noChange = false;
			while (noChange == false)
			{
				noChange = true;
				for (unsigned int i = 0; i < frontSpriteArray.size(); i++)
				{
					if (i != frontSpriteArray.size() - 1)
					{
						if (frontSpriteArray[i]->getLayer() < frontSpriteArray[i + 1]->getLayer())
						{
							Graphics::LevelSprite* saveLayer = frontSpriteArray[i];
							frontSpriteArray[i] = frontSpriteArray[i + 1];
							frontSpriteArray[i + 1] = saveLayer;
							noChange = false;
						}
					}
				}
			}
			noChange = false;
			while (noChange == false)
			{
				noChange = true;
				for (unsigned int i = 0; i < frontSpriteArray.size(); i++)
				{
					if (i != frontSpriteArray.size() - 1)
					{
						if (frontSpriteArray[i]->getLayer() == frontSpriteArray[i + 1]->getLayer())
						{
							if (frontSpriteArray[i]->getZDepth() < frontSpriteArray[i + 1]->getZDepth())
							{
								Graphics::LevelSprite* saveLayer = frontSpriteArray[i];
								frontSpriteArray[i] = frontSpriteArray[i + 1];
								frontSpriteArray[i + 1] = saveLayer;
								noChange = false;
							}
						}
					}
				}
			}
		}

		Graphics::LevelSprite* World::getSpriteByIndex(std::string backOrFront, int index)
		{
			if (backOrFront == "Back")
				return backSpriteArray[index];
			else if (backOrFront == "Front")
				return frontSpriteArray[index];
		}
		int World::getSpriteArraySize(std::string backOrFront)
		{
			if (backOrFront == "Back")
				return backSpriteArray.size();
			else if (backOrFront == "Front")
				return frontSpriteArray.size();
		}

		std::vector<Graphics::LevelSprite*> World::getAllSprites()
		{
			std::vector<Graphics::LevelSprite*> allDec;
			for (int i = 0; i < backSpriteArray.size(); i++)
			{
				allDec.push_back(backSpriteArray[i]);
			}
			for (int i = 0; i < frontSpriteArray.size(); i++)
			{
				allDec.push_back(frontSpriteArray[i]);
			}
			return allDec;
		}
		std::vector<Graphics::LevelSprite*> World::getSpritesByLayer(int layer)
		{
			std::vector<Graphics::LevelSprite*> returnLayer;
			if (layer >= 0)
			{
				for (unsigned int i = 0; i < backSpriteArray.size(); i++)
				{
					if (backSpriteArray[i]->getLayer() == layer)
						returnLayer.push_back(backSpriteArray[i]);
				}
			}
			else if (layer < 0)
			{
				for (unsigned int i = 0; i < frontSpriteArray.size(); i++)
				{
					if (frontSpriteArray[i]->getLayer() == layer)
						returnLayer.push_back(frontSpriteArray[i]);
				}
			}
			return returnLayer;
		}

		Graphics::LevelSprite* World::getSpriteByPos(int x, int y, int layer)
		{
			Graphics::LevelSprite* returnSpr = nullptr;
			std::vector<Graphics::LevelSprite*> getDecoVec = getSpritesByLayer(layer);
			for (unsigned int i = 0; i < getDecoVec.size(); i++)
			{
				if (x > getDecoVec[i]->getRect().left && x < getDecoVec[i]->getRect().left + getDecoVec[i]->getW())
				{
					if (y > getDecoVec[i]->getRect().top && y < getDecoVec[i]->getRect().top + getDecoVec[i]->getH())
						returnSpr = getDecoVec[i];
				}
			}
			return returnSpr;
		}

		Graphics::LevelSprite* World::getSpriteByID(std::string ID)
		{
			for (int i = 0; i < backSpriteArray.size(); i++)
			{
				if (backSpriteArray[i]->getID() == ID)
					return backSpriteArray[i];
			}
			for (int i = 0; i < frontSpriteArray.size(); i++)
			{
				if (frontSpriteArray[i]->getID() == ID)
					return frontSpriteArray[i];
			}
			std::cout << "<Error:World:World>[getDecoByID] : Can't find Decoration : " << ID << std::endl;
			return NULL;
		}

		void World::deleteSpriteByID(std::string sprID, bool freeMemory)
		{
			this->deleteSprite(this->getSpriteByID(sprID), freeMemory);
		}

		void World::deleteSprite(Graphics::LevelSprite* decoToDelete, bool freeMemory)
		{
			if (decoToDelete->getLayer() > 0)
			{
				for (int i = 0; i < backSpriteArray.size(); i++)
				{
					if (backSpriteArray[i]->getID() == decoToDelete->getID())
					{
						if (freeMemory) delete backSpriteArray[i];
						backSpriteArray.erase(backSpriteArray.begin() + i);
					}
				}
			}
			else
			{
				for (int i = 0; i < frontSpriteArray.size(); i++)
				{
					if (frontSpriteArray[i]->getID() == decoToDelete->getID())
					{
						if (freeMemory) delete frontSpriteArray[i];
						frontSpriteArray.erase(frontSpriteArray.begin() + i);
					}
				}
			}
		}

		void World::enableShowCollision(bool drawLines, bool drawPoints, bool drawMasterPoint, bool drawSkel)
		{
			showCollisionModes["drawLines"] = drawLines;
			showCollisionModes["drawPoints"] = drawPoints;
			showCollisionModes["drawMasterPoint"] = drawMasterPoint;
			showCollisionModes["drawSkel"] = drawSkel;
		}

		std::pair<Collision::PolygonalCollider*, int> World::getCollisionPointByPos(int x, int y)
		{
			for (unsigned int i = 0; i < collidersArray.size(); i++)
			{
				if (collidersArray[i]->hasPoint(x, y, 6, 6) != -1)
				{
					return std::pair<Collision::PolygonalCollider*, int>(collidersArray[i], collidersArray[i]->hasPoint(x, y, 6, 6));
				}
			}
			return std::pair<Collision::PolygonalCollider*, int>(NULL, 0);
		}

		Collision::PolygonalCollider* World::getCollisionMasterByPos(int x, int y)
		{
			for (unsigned int i = 0; i < collidersArray.size(); i++)
			{
				if (collidersArray[i]->hasMasterPoint(x, y, 6, 6))
				{
					return collidersArray[i];
				}
			}
			return NULL;
		}

		Collision::PolygonalCollider* World::getCollisionByID(std::string id)
		{
			for (unsigned int i = 0; i < collidersArray.size(); i++)
			{
				if (id == collidersArray[i]->getID())
				{
					return collidersArray[i];
				}
			}
			return NULL;
		}

		std::vector<Collision::PolygonalCollider*> World::getAllCollidersByCollision(Collision::PolygonalCollider* col, int offx, int offy)
		{
			std::vector<Collision::PolygonalCollider*> returnVec;
			for (int i = 0; i < collidersArray.size(); i++)
			{
				if (collidersArray[i]->doesCollide(col, offx, offy))
				{
					returnVec.push_back(collidersArray[i]);
				}
			}
			return returnVec;
		}

		void World::deleteCollisionByID(std::string id, bool freeMemory)
		{
			this->deleteCollision(this->getCollisionByID(id), freeMemory);
		}

		void World::deleteCollision(Collision::PolygonalCollider* colToDelete, bool freeMemory)
		{
			int indexToDelete;
			for (unsigned int i = 0; i < collidersArray.size(); i++)
			{
				if (colToDelete == collidersArray[i])
					indexToDelete = i;
			}
			if (freeMemory)
				delete(collidersArray[indexToDelete]);
			collidersArray.erase(collidersArray.begin() + indexToDelete);
		}

		void World::createCollisionAtPos(int x, int y)
		{
			int i = 0;
			std::string testID = "collider" + std::to_string(collidersArray.size() + i);
			while (getCollisionByID(testID) != NULL)
			{
				++i;
				testID = "collider" + std::to_string(collidersArray.size() + i);
			}
			Collision::PolygonalCollider* newCollider = new Collision::PolygonalCollider(testID);
			newCollider->addPoint(50, 0);
			newCollider->addPoint(0, 50);
			newCollider->addPoint(100, 50);
			newCollider->setPositionFromMaster(x, y);
			collidersArray.push_back(newCollider);
		}

		void loadWorldLib(kaguya::State* lua)
		{
			if (!(bool)((*lua)["Core"])) (*lua)["Core"] = kaguya::NewTable();
			(*lua)["Core"]["World"] = kaguya::NewTable();
			(*lua)["Core"]["World"]["World"].setClass(kaguya::UserdataMetatable<World>()
				.addFunction("addCharacter", &World::addCharacter)
				.addFunction("addLevelSprite", &World::addLevelSprite)
				.addFunction("addLight", &World::addLight)
				.addFunction("addCollider", &World::addCollider)
				.addFunction("addParticle", &World::addParticle)
				.addFunction("clearWorld", &World::clearWorld)
				.addFunction("createCollisionAtPos", &World::createCollisionAtPos)
				.addFunction("createGameObject", &World::createGameObject)
				.addFunction("deleteCollisionByID", &World::deleteCollisionByID)
				.addFunction("deleteSprite", &World::deleteSprite)
				.addFunction("enableShowCollision", &World::enableShowCollision)
				.addFunction("getAllCollidersByCollision", &World::getAllCollidersByCollision)
				.addFunction("getAllGameObjects", &World::getAllGameObjects)
				.addFunction("getAllSprites", &World::getAllSprites)
				.addFunction("getCamX", &World::getCamX)
				.addFunction("getCamY", &World::getCamY)
				.addFunction("getCharacter", &World::getCharacter)
				.addFunction("getColliders", &World::getColliders)
				.addFunction("getCollisionByID", &World::getCollisionByID)
				.addFunction("getCollisionMasterByPos", &World::getCollisionMasterByPos)
				.addFunction("getCollisionPointByPos", &World::getCollisionPointByPos)
				.addFunction("getGameObject", &World::getGameObject)
				.addFunction("getScriptEngine", &World::getScriptEngine)
				.addFunction("getSizeX", &World::getSizeX)
				.addFunction("getSizeY", &World::getSizeY)
				.addFunction("getSpriteArraySize", &World::getSpriteArraySize)
				.addFunction("getSpriteByID", &World::getSpriteByID)
				.addFunction("getSpriteByIndex", &World::getSpriteByIndex)
				.addFunction("getSpriteByPos", &World::getSpriteByPos)
				.addFunction("getSpritesByLayer", &World::getSpritesByLayer)
				.addFunction("getStartX", &World::getStartX)
				.addFunction("getStartY", &World::getStartY)
				.addFunction("loadFromFile", &World::loadFromFile)
				.addFunction("orderUpdateScrArray", &World::orderUpdateScrArray)
				.addFunction("reorganizeLayers", &World::reorganizeLayers)
				.addFunction("saveData", &World::saveData)
				.addFunction("setBlurMul", &World::setBlurMul)
				.addFunction("setCameraPosition", &World::setCameraPosition)
				.addFunction("setUpdateState", &World::setUpdateState)
				);
			std::cout << "World Lib Loaded" << std::endl;
		}

		void loadWorldScriptEngineBaseLib(kaguya::State* lua)
		{
			(*lua)["CPP_Import"] = &Script::loadLib;
			(*lua)["CPP_Hook"] = &Script::loadHook;
			loadWorldLib(lua);
			Script::loadScrGameObjectLib(lua);
			(*lua)["This"] = lua;
		}
	};
};