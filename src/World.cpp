//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "World.hpp"

namespace obe
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

		void World::loadFromFile(std::string filename)
		{
			this->clearWorld();
			double startLoadTime = Time::getTickSinceEpoch();
			int indexInFile = 0;
			vili::DataParser mapParse;
			baseFolder = System::Path("Data/Maps").add(filename).loadResource(&mapParse, System::Loaders::dataLoader);

			if (mapParse->contains(vili::Types::ComplexAttribute, "Meta")) {
				vili::ComplexAttribute* meta = mapParse.at("Meta");
				levelName = meta->getBaseAttribute("name")->get<std::string>();
				sizeX = meta->getListAttribute("size")->get(0)->get<int>();
				sizeY = meta->getListAttribute("size")->get(1)->get<int>();
				camera.setWorldSize(sizeX, sizeY);
				camera.setSize(sizeX, sizeY);
				if (meta->contains(vili::Types::ListAttribute, "camera")) {
					int camW = meta->getListAttribute("camera")->get(0)->get<int>();
					int camH = meta->getListAttribute("camera")->get(1)->get<int>();
					camera.setSize(camW, camH);
				}
			}
			else {
				std::cout << "<Error:World:World>[loadFromFile] : Map file : " << filename << " does not have any 'Meta' Root Attribute" << std::endl;
				return;
			}

			if (mapParse->contains(vili::Types::ComplexAttribute, "LevelSprites"))
			{
				vili::ComplexAttribute* levelSprites = mapParse.at("LevelSprites");
				for (std::string& currentSpriteName : levelSprites->getAll(vili::Types::ComplexAttribute))
				{
					vili::ComplexAttribute* currentSprite = levelSprites->at(currentSpriteName);
					std::string spriteID, spritePath, spriteUnits;
					double spritePosX, spritePosY;
					int spriteRot = 0;
					double spriteSca = 1.0;
					std::vector<std::string> spriteAtrList;
					int layer;
					int zdepth;
					spriteID = currentSpriteName;
					spriteUnits = currentSprite->contains(vili::Types::BaseAttribute, "unit") ? 
						currentSprite->getBaseAttribute("unit")->get<std::string>() : "WorldUnits";
					std::cout << "SpriteUnit : " << spriteUnits << std::endl;
					spritePath = currentSprite->getBaseAttribute("path")->get<std::string>();
					spritePosX = currentSprite->getListAttribute("pos")->get(0)->get<double>();
					spritePosY = currentSprite->getListAttribute("pos")->get(1)->get<double>();
					if (spriteUnits == "WorldUnits") {
						spritePosX = (spritePosX * Functions::Coord::width) / ((double) sizeX);
						spritePosY = (spritePosY * Functions::Coord::height) / ((double)sizeY);
					}
					else if (spriteUnits == "WorldPercentage") {
						spritePosX = (spritePosX * (double)sizeX) / 100.0;
						spritePosY = (spritePosY * (double)sizeY) / 100.0;
					}
					spriteRot = currentSprite->getBaseAttribute("rotation")->get<int>();
					spriteSca = currentSprite->getBaseAttribute("scale")->get<double>();
					layer = currentSprite->getBaseAttribute("layer")->get<int>();
					zdepth = currentSprite->getBaseAttribute("z-depth")->get<int>();
					if (currentSprite->contains(vili::Types::ListAttribute, "attributeList"))
					{
						for (vili::BaseAttribute* attribute : *currentSprite->at<vili::ListAttribute>("attributeList"))
							spriteAtrList.push_back(*attribute);
					}
					Graphics::LevelSprite* tempSprite;
					if (spritePath != "None") {
						tempSprite = new Graphics::LevelSprite(spritePath, spriteID);
					}
					else
						tempSprite = new Graphics::LevelSprite(spriteID);
					tempSprite->move(spritePosX, spritePosY);
					tempSprite->setRotation(spriteRot);
					tempSprite->setScale(spriteSca, spriteSca);
					tempSprite->setAtr(spriteAtrList);
					tempSprite->setLayer(layer);
					tempSprite->setZDepth(zdepth);
					if (layer >= 1)
						backSpriteArray.push_back(tempSprite);
					else if (layer <= -1)
						frontSpriteArray.push_back(tempSprite);
				}
			}

			this->reorganizeLayers();

			if (mapParse->contains(vili::Types::ComplexAttribute, "Collisions"))
			{
				vili::ComplexAttribute* collisions = mapParse.at("Collisions");
				for (std::string& collisionName : collisions->getAll(vili::Types::ComplexAttribute))
				{
					vili::ComplexAttribute* currentCollision = collisions->at(collisionName);
					Collision::PolygonalCollider* tempCollider = new Collision::PolygonalCollider(collisionName);

					bool pointExists = true;
					int pointIndex = 0;
					while (pointExists) {
						if (currentCollision->contains(vili::Types::ListAttribute, std::to_string(pointIndex))) {
							tempCollider->addPoint(currentCollision->getListAttribute(std::to_string(pointIndex))->get(0)->get<double>(), 
								currentCollision->getListAttribute(std::to_string(pointIndex))->get(0)->get<double>());
						}
						else {
							pointExists = false;
						}
						pointIndex++;
					}
					this->collidersArray.push_back(tempCollider);
				}
			}

			if (mapParse->contains(vili::Types::ComplexAttribute, "LevelObjects"))
			{
				vili::ComplexAttribute* levelObjects = mapParse.at("LevelObjects");
				for (std::string& currentObjectName : levelObjects->getAll(vili::Types::ComplexAttribute))
				{
					vili::ComplexAttribute* currentObject = levelObjects->at(currentObjectName);
					std::string levelObjectType = currentObject->getBaseAttribute("type")->get<std::string>();
					this->createGameObject(currentObjectName, levelObjectType);
					int objX = 0;
					int objY = 0;
					int colOffX = 0;
					int colOffY = 0;
					if (currentObject->contains(vili::Types::ComplexAttribute, "Requires")) {
						vili::ComplexAttribute* objectRequirements = currentObject->at("Requires");
						currentObject->removeOwnership(objectRequirements);
						Script::GameObjectRequires::ApplyRequirements(this->getGameObject(currentObjectName), *objectRequirements);
						objectRequirements->setParent(currentObject);
					}
				}
			}

			if (mapParse->contains(vili::Types::ComplexAttribute, "Script"))
			{
				vili::ComplexAttribute* script = mapParse.at("Script");
				for (vili::BaseAttribute* scriptName : *script->getListAttribute("gameScripts"))
				{
					System::Path(*scriptName).loadResource(worldScriptEngine, System::Loaders::luaLoader);
					scriptArray.push_back(*scriptName);
				}
			}
		}

		void World::clearWorld()
		{
			/*for (int i = 0; i < backSpriteArray.size(); i++)
			delete backSpriteArray[i];*/
			backSpriteArray.clear();
			/*for (int i = 0; i < frontSpriteArray.size(); i++)
			delete frontSpriteArray[i];*/
			frontSpriteArray.clear();
			/*for (int i = 0; i < collidersArray.size(); i++)
			delete collidersArray[i];*/
			collidersArray.clear();
			/*for (auto it = gameObjectsMap.begin(); it != gameObjectsMap.end(); it++)
			delete it->second;*/
			gameObjectsMap.clear();
			updateObjArray.clear();
			/*for (auto it = lightsMap.begin(); it != lightsMap.end(); it++)
			delete it->second;*/
			lightsMap.clear();
			/*for (int i = 0; i < particleArray.size(); i++)
			delete particleArray[i];*/
			particleArray.clear();
			scriptArray.clear();
		}

		vili::DataParser* World::saveData()
		{
			vili::DataParser* dataStore = new vili::DataParser;
			dataStore->createFlag("Map");
			dataStore->createFlag("Lock");
			(*dataStore)->createComplexAttribute("Meta");
			dataStore->at("Meta")->createBaseAttribute("Level", levelName);
			dataStore->at("Meta")->createBaseAttribute("SizeX", sizeX);
			dataStore->at("Meta")->createBaseAttribute("SizeY", sizeY);
			(*dataStore)->createComplexAttribute("LevelSprites");
			for (unsigned int i = 0; i < backSpriteArray.size(); i++)
			{
				if (backSpriteArray[i]->getParentID() == "")
				{
					dataStore->at("LevelSprites")->createComplexAttribute(backSpriteArray[i]->getID());
					dataStore->at("LevelSprites", backSpriteArray[i]->getID())->createBaseAttribute("path", backSpriteArray[i]->getName());
					dataStore->at("LevelSprites", backSpriteArray[i]->getID())->createBaseAttribute("posX", (int)backSpriteArray[i]->getX());
					dataStore->at("LevelSprites", backSpriteArray[i]->getID())->createBaseAttribute("posY", (int)backSpriteArray[i]->getY());
					dataStore->at("LevelSprites", backSpriteArray[i]->getID())->createBaseAttribute("rotation", (int)backSpriteArray[i]->getRotation());
					dataStore->at("LevelSprites", backSpriteArray[i]->getID())->createBaseAttribute("scale", backSpriteArray[i]->getScaleX());
					dataStore->at("LevelSprites", backSpriteArray[i]->getID())->createBaseAttribute("layer", (int)backSpriteArray[i]->getLayer());
					dataStore->at("LevelSprites", backSpriteArray[i]->getID())->createBaseAttribute("z-depth", (int)backSpriteArray[i]->getZDepth());
					if (backSpriteArray[i]->getAttributes().size() != 0)
					{
						dataStore->at("LevelSprites", backSpriteArray[i]->getID())->createListAttribute("attributeList");
						for (unsigned int j = 0; j < backSpriteArray[i]->getAttributes().size(); j++)
							dataStore->at("LevelSprites", backSpriteArray[i]->getID())->getListAttribute("attributeList")->push(backSpriteArray[i]->getAttributes()[j]);
					}
				}
			}
			for (unsigned int i = 0; i < frontSpriteArray.size(); i++)
			{
				if (frontSpriteArray[i]->getParentID() == "")
				{
					dataStore->at("LevelSprites")->createComplexAttribute(frontSpriteArray[i]->getID());
					dataStore->at("LevelSprites", frontSpriteArray[i]->getID())->createBaseAttribute("path", frontSpriteArray[i]->getName());
					dataStore->at("LevelSprites", frontSpriteArray[i]->getID())->createBaseAttribute("posX", (int)frontSpriteArray[i]->getX());
					dataStore->at("LevelSprites", frontSpriteArray[i]->getID())->createBaseAttribute("posY", (int)frontSpriteArray[i]->getY());
					dataStore->at("LevelSprites", frontSpriteArray[i]->getID())->createBaseAttribute("rotation", (int)frontSpriteArray[i]->getRotation());
					dataStore->at("LevelSprites", frontSpriteArray[i]->getID())->createBaseAttribute("scale", frontSpriteArray[i]->getScaleX());
					dataStore->at("LevelSprites", frontSpriteArray[i]->getID())->createBaseAttribute("layer", (int)frontSpriteArray[i]->getLayer());
					dataStore->at("LevelSprites", frontSpriteArray[i]->getID())->createBaseAttribute("z-depth", (int)frontSpriteArray[i]->getZDepth());
					if (frontSpriteArray[i]->getAttributes().size() != 0)
					{
						dataStore->at("LevelSprites", frontSpriteArray[i]->getID())->createListAttribute("attributeList");
						for (unsigned int j = 0; j < frontSpriteArray[i]->getAttributes().size(); j++)
							dataStore->at("LevelSprites", frontSpriteArray[i]->getID())->getListAttribute("attributeList")->push(frontSpriteArray[i]->getAttributes()[j]);
					}
				}
			}
			(*dataStore)->createComplexAttribute("Collisions");
			for (unsigned int i = 0; i < collidersArray.size(); i++)
			{
				if (collidersArray[i]->getParentID() == "")
				{
					dataStore->at("Collisions")->createComplexAttribute(collidersArray[i]->getID());
					dataStore->at("Collisions", collidersArray[i]->getID())->createListAttribute("polygonPoints");
					for (unsigned int j = 0; j < collidersArray[i]->getPointsAmount(); j++)
					{
						int px = collidersArray[i]->getPointPosition(j).first;
						int py = collidersArray[i]->getPointPosition(j).second;
						dataStore->at("Collisions", collidersArray[i]->getID())->getListAttribute("polygonPoints")->push(std::to_string(px) + "," + std::to_string(py));
					}
				}
			}
			(*dataStore)->createComplexAttribute("LevelObjects");
			for (auto it = gameObjectsMap.begin(); it != gameObjectsMap.end(); it++)
			{
				dataStore->at("LevelObjects")->createComplexAttribute(it->first);
				dataStore->at("LevelObjects", it->first)->createBaseAttribute("type", it->second->getType());
				(*it->second->getScriptEngine())("inspect = require('Lib/StdLib/Inspect');");
				kaguya::LuaTable saveTable = (*it->second->getScriptEngine())["Local.Save"]();
				(*it->second->getScriptEngine())("tnt = Local.Save()");
				kaguya::LuaRef saveTableRef = (*it->second->getScriptEngine())["tnt"];
				(*it->second->getScriptEngine())("print(inspect(Local.Save()));");
				vili::ComplexAttribute* saveRequirements = Data::DataBridge::luaTableToComplexAttribute(
					"Requires", saveTableRef);
				dataStore->at("LevelObjects", it->first)->pushComplexAttribute(saveRequirements);
			}
			if (scriptArray.size() > 0)
			{
				(*dataStore)->createComplexAttribute("Script");
				dataStore->at("Script")->createListAttribute("gameScripts");
				for (int i = 0; i < scriptArray.size(); i++) {
					dataStore->at("Script")->getListAttribute("gameScripts")->push(scriptArray[i]);
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
						//BUGGY
						/*if (updateObjArray[i]->hasCollider)
							this->deleteCollision(updateObjArray[i]->getCollider(), false);*/
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
				for (unsigned int i = 0; i < particleArray.size(); i++)
				{
					particleArray[i]->update();
				}
			}
		}

		void World::display(sf::RenderWindow* surf)
		{
			visualDisplayBack(surf);
			for (unsigned int i = 0; i < particleArray.size(); i++)
			{
				particleArray[i]->draw(surf);
			}
			visualDisplayFront(surf);
			if (showCollisionModes["drawLines"] || showCollisionModes["drawPoints"] || showCollisionModes["drawMasterPoint"] || showCollisionModes["drawSkel"])
			{
				for (unsigned int i = 0; i < collidersArray.size(); i++)
				{
					collidersArray[i]->setDrawOffset(-camera.getX(), -camera.getY());
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
				Light::PointLight* cLight = nullptr;
				if (lightHooked) cLight = lightsMap[backSpriteArray[i]->getID()];

				layeredX = (((backSpriteArray[i]->getX() + backSpriteArray[i]->getOffsetX()) * (backSpriteArray[i]->getLayer()) - 
					camera.getX()) / backSpriteArray[i]->getLayer());
				layeredY = (((backSpriteArray[i]->getY() + backSpriteArray[i]->getOffsetY()) * (backSpriteArray[i]->getLayer()) - 
					camera.getY()) / backSpriteArray[i]->getLayer());
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
					layeredX = backSpriteArray[i]->getX() + backSpriteArray[i]->getOffsetX() - camera.getX();
				}
				else if (Functions::Vector::isInList((std::string)"+PVFIX", backSpriteArray[i]->getAttributes()))
				{
					layeredY = backSpriteArray[i]->getY() + backSpriteArray[i]->getOffsetY() - camera.getY();
				}
				else if (Functions::Vector::isInList((std::string)"+PFIX", backSpriteArray[i]->getAttributes()))
				{
					layeredX = backSpriteArray[i]->getX() + backSpriteArray[i]->getOffsetX() - camera.getX();
					layeredY = backSpriteArray[i]->getY() + backSpriteArray[i]->getOffsetY() - camera.getY();
				}
				sfe::ComplexSprite tAffSpr;
				tAffSpr = *backSpriteArray[i]->getSprite();

				if (lightHooked) cLight->setPosition(layeredX, layeredY);
				tAffSpr.setPosition(layeredX, layeredY);
				if (lightHooked) { if (cLight->isBehind()) lightsMap[backSpriteArray[i]->getID()]->draw(surf); }
				if (backSpriteArray[i]->isVisible())
					surf->draw(tAffSpr);
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
				Light::PointLight* cLight = nullptr;
				if (lightHooked) cLight = lightsMap[frontSpriteArray[i]->getID()];

				if (Functions::Vector::isInList((std::string)"+FIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = frontSpriteArray[i]->getX();
					layeredY = frontSpriteArray[i]->getY();
				}
				else if (Functions::Vector::isInList((std::string)"+VFIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = ((frontSpriteArray[i]->getX() / (frontSpriteArray[i]->getLayer()) + camera.getX()) * frontSpriteArray[i]->getLayer());
					layeredY = frontSpriteArray[i]->getY();
				}
				else if (Functions::Vector::isInList((std::string)"+HFIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = frontSpriteArray[i]->getX();
					layeredY = ((frontSpriteArray[i]->getY() / (frontSpriteArray[i]->getLayer()) + camera.getY()) * frontSpriteArray[i]->getLayer());
				}
				else if (Functions::Vector::isInList((std::string)"+PHFIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = frontSpriteArray[i]->getX() - camera.getX();
					layeredY = ((frontSpriteArray[i]->getY() / (frontSpriteArray[i]->getLayer()) + camera.getY()) * frontSpriteArray[i]->getLayer());
				}
				else if (Functions::Vector::isInList((std::string)"+PVFIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = ((frontSpriteArray[i]->getX() / (frontSpriteArray[i]->getLayer()) + camera.getX()) * frontSpriteArray[i]->getLayer());
					layeredY = frontSpriteArray[i]->getY() - camera.getY();
				}
				else if (Functions::Vector::isInList((std::string)"+PFIX", frontSpriteArray[i]->getAttributes()))
				{
					layeredX = frontSpriteArray[i]->getX() - camera.getX();
					layeredY = frontSpriteArray[i]->getY() - camera.getY();
				}
				else
				{
					layeredX = ((frontSpriteArray[i]->getX() / (frontSpriteArray[i]->getLayer()) + camera.getX()) * frontSpriteArray[i]->getLayer());
					layeredY = ((frontSpriteArray[i]->getY() / (frontSpriteArray[i]->getLayer()) + camera.getY()) * frontSpriteArray[i]->getLayer());
				}

				sfe::ComplexSprite tAffSpr;
				tAffSpr = *frontSpriteArray[i]->getSprite();

				if (lightHooked) cLight->setPosition(layeredX, layeredY);
				tAffSpr.setPosition(layeredX, layeredY);
				if (lightHooked) { if (cLight->isBehind()) lightsMap[frontSpriteArray[i]->getID()]->draw(surf); }
				if (frontSpriteArray[i]->isVisible())
					surf->draw(tAffSpr);
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

		std::string World::getLevelName()
		{
			return levelName;
		}

		void World::setLevelName(std::string newName)
		{
			this->levelName = newName;
		}

		std::vector<Collision::PolygonalCollider*> World::getColliders()
		{
			return collidersArray;
		}

		Camera& World::getCamera()
		{
			return camera;
		}

		Camera& World::getCameraIfNotLocked()
		{
			if (cameraLocked)
				return Camera(camera);
			else
				return camera;
		}

		void World::setCameraLock(bool state)
		{
			this->cameraLocked = state;
		}

		bool World::isCameraLocked()
		{
			return cameraLocked;
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
			vili::DataParser getGameObjectFile;
			System::Path("Data/GameObjects/").add(obj).add(obj + ".obj.vili").loadResource(&getGameObjectFile, System::Loaders::dataLoader);
			vili::ComplexAttribute* gameObjectData = getGameObjectFile.at(obj);
			newGameObject->loadGameObject(gameObjectData);
			this->gameObjectsMap[id] = newGameObject;
			if (newGameObject->hasScriptEngine) {
				loadWorldLib(newGameObject->scriptEngine);
				(*newGameObject->scriptEngine)["World"] = this;
			}
				
			this->orderUpdateScrArray();
			if (newGameObject->canDisplay())
			{
				this->addLevelSprite(newGameObject->getLevelSprite());
				if (newGameObject->canDisplay() && newGameObject->isLevelSpriteRelative())
					newGameObject->getLevelSprite()->setPosition(0, 0);
				newGameObject->getLevelSprite()->setParentID(id);
			}
			if (newGameObject->hasCollider)
			{
				this->addCollider(newGameObject->getCollider());
				newGameObject->getCollider()->setParentID(id);
			}

			std::cout << "<World> Created new object : " << id << " of type : " << obj << std::endl;

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
			std::vector<Graphics::LevelSprite*> getSpriteVec = getSpritesByLayer(layer);
			for (unsigned int i = 0; i < getSpriteVec.size(); i++)
			{
				if (x > getSpriteVec[i]->getRect().left && x < getSpriteVec[i]->getRect().left + getSpriteVec[i]->getW())
				{
					if (y > getSpriteVec[i]->getRect().top && y < getSpriteVec[i]->getRect().top + getSpriteVec[i]->getH())
						returnSpr = getSpriteVec[i];
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
			std::cout << "<Error:World:World>[getSpriteByID] : Can't find Sprite : " << ID << std::endl;
			return nullptr;
		}

		void World::deleteSpriteByID(std::string sprID, bool freeMemory)
		{
			this->deleteSprite(this->getSpriteByID(sprID), freeMemory);
		}

		void World::deleteSprite(Graphics::LevelSprite* spriteToDelete, bool freeMemory)
		{
			if (spriteToDelete->getLayer() > 0)
			{
				for (int i = 0; i < backSpriteArray.size(); i++)
				{
					if (backSpriteArray[i]->getID() == spriteToDelete->getID())
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
					if (frontSpriteArray[i]->getID() == spriteToDelete->getID())
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
			return std::pair<Collision::PolygonalCollider*, int>(nullptr, 0);
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
			return nullptr;
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
			return nullptr;
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
			while (getCollisionByID(testID) != nullptr)
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
				.addFunction("getCamera", &World::getCameraIfNotLocked)
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
				.addFunction("loadFromFile", &World::loadFromFile)
				.addFunction("orderUpdateScrArray", &World::orderUpdateScrArray)
				.addFunction("reorganizeLayers", &World::reorganizeLayers)
				.addFunction("saveData", &World::saveData)
				.addFunction("setUpdateState", &World::setUpdateState)
				);
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