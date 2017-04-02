//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "World.hpp"

namespace obe
{
	namespace World
	{
		World::World()
		{
			Coord::UnitVector::Init(m_size);
			m_worldScriptEngine = new kaguya::State();
			loadWorldScriptEngineBaseLib(m_worldScriptEngine);
			(*m_worldScriptEngine)["World"] = this;
			System::Path("Lib/GameLib/WScrInit.lua").loadResource(m_worldScriptEngine, System::Loaders::luaLoader);
			Script::loadLib(m_worldScriptEngine, "Core.*");
			Script::TriggerDatabase::GetInstance()->createNamespace("Map");
			m_showCollisionModes["drawLines"] = false;
			m_showCollisionModes["drawPoints"] = false;
			m_showCollisionModes["drawMasterPoint"] = false;
			m_showCollisionModes["drawSkel"] = false;
		}

		Graphics::LevelSprite* World::createLevelSprite(std::string id, std::string path)
		{
			std::unique_ptr<Graphics::LevelSprite> newLevelSprite;
			if (path == "")
				newLevelSprite = std::make_unique<Graphics::LevelSprite>(id);
			else
				newLevelSprite = std::make_unique<Graphics::LevelSprite>(path, id);

			Graphics::LevelSprite* returnLevelSprite = newLevelSprite.get();
			m_spriteArray.push_back(std::move(newLevelSprite));
			
			this->reorganizeLayers();
			return returnLevelSprite;
		}

		Collision::PolygonalCollider* World::createCollider(std::string id)
		{
			std::unique_ptr<Collision::PolygonalCollider> newCollider = std::make_unique<Collision::PolygonalCollider>(id);
			Collision::PolygonalCollider* returnCollider = newCollider.get();
			m_colliderArray.push_back(std::move(newCollider));
			return returnCollider;
		}

		void World::addLight(Light::PointLight* lgt)
		{
			m_lightMap[lgt->getID()] = std::unique_ptr<Light::PointLight>(lgt);
		}

		kaguya::State* World::getScriptEngine() const
		{
			return m_worldScriptEngine;
		}

		std::string World::getBaseFolder() const
		{
			return m_baseFolder;
		}

		void World::loadFromFile(std::string filename)
		{
			this->clearWorld();
			vili::DataParser mapParse;
			m_baseFolder = System::Path("Data/Maps").add(filename).loadResource(&mapParse, System::Loaders::dataLoader);

			if (mapParse->contains(vili::Types::ComplexAttribute, "Meta"))
			{
				vili::ComplexAttribute* meta = mapParse.at("Meta");
				m_levelName = meta->getBaseAttribute("name")->get<std::string>();
				m_size->w = meta->getListAttribute("size")->get(0)->get<int>();
				m_size->h = meta->getListAttribute("size")->get(1)->get<int>();

				m_camera.setSize(meta->getListAttribute("view")->get(0)->get<int>(), meta->getListAttribute("view")->get(1)->get<int>());

				//camera.setWorldSize(sizeX, sizeY);
				//camera.setSize(sizeX, sizeY);
				if (meta->contains(vili::Types::ListAttribute, "camera"))
				{
					int camW = meta->getListAttribute("camera")->get(0)->get<int>();
					int camH = meta->getListAttribute("camera")->get(1)->get<int>();
					m_camera.setSize(camW, camH);
				}
			}
			else
			{
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
					Coord::UnitVector spritePos;
					int spriteRot;
					double spriteSca;
					std::vector<std::string> spriteAtrList;
					int layer;
					int zdepth;
					spriteID = currentSpriteName;
					spriteUnits = currentSprite->contains(vili::Types::BaseAttribute, "unit") ?
						              currentSprite->getBaseAttribute("unit")->get<std::string>() : "WorldUnits";
					std::cout << "SpriteUnit : " << spriteUnits << std::endl;
					spritePath = currentSprite->getBaseAttribute("path")->get<std::string>();
					spritePos = Coord::UnitVector(currentSprite->getListAttribute("pos")->get(0)->get<double>(),
					                              currentSprite->getListAttribute("pos")->get(1)->get<double>());
					spriteRot = currentSprite->getBaseAttribute("rotation")->get<int>();
					spriteSca = currentSprite->getBaseAttribute("scale")->get<double>();
					layer = currentSprite->getBaseAttribute("layer")->get<int>();
					zdepth = currentSprite->getBaseAttribute("z-depth")->get<int>();
					if (currentSprite->contains(vili::Types::ListAttribute, "attributeList"))
					{
						for (vili::BaseAttribute* attribute : *currentSprite->at<vili::ListAttribute>("attributeList"))
							spriteAtrList.push_back(*attribute);
					}
					std::unique_ptr<Graphics::LevelSprite> tempSprite;
					if (spritePath != "None")
					{
						tempSprite = std::make_unique<Graphics::LevelSprite>(spritePath, spriteID);
					}
					else
						tempSprite = std::make_unique<Graphics::LevelSprite>(spriteID);
					tempSprite->setPosition(spritePos.x, spritePos.y);
					tempSprite->setRotation(spriteRot);
					tempSprite->setScale(spriteSca, spriteSca);
					tempSprite->setAtr(spriteAtrList);
					tempSprite->setLayer(layer);
					tempSprite->setZDepth(zdepth);
					m_spriteArray.push_back(std::move(tempSprite));
				}
			}

			this->reorganizeLayers();

			if (mapParse->contains(vili::Types::ComplexAttribute, "Collisions"))
			{
				vili::ComplexAttribute* collisions = mapParse.at("Collisions");
				for (std::string& collisionName : collisions->getAll(vili::Types::ComplexAttribute))
				{
					vili::ComplexAttribute* currentCollision = collisions->at(collisionName);
					std::unique_ptr<Collision::PolygonalCollider> tempCollider = std::make_unique<Collision::PolygonalCollider>(collisionName);

					bool pointExists = true;
					int pointIndex = 0;
					while (pointExists)
					{
						if (currentCollision->contains(vili::Types::ListAttribute, std::to_string(pointIndex)))
						{
							tempCollider->addPoint(currentCollision->getListAttribute(std::to_string(pointIndex))->get(0)->get<double>(),
							                       currentCollision->getListAttribute(std::to_string(pointIndex))->get(0)->get<double>());
						}
						else
						{
							pointExists = false;
						}
						pointIndex++;
					}
					m_colliderArray.push_back(std::move(tempCollider));
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
					if (currentObject->contains(vili::Types::ComplexAttribute, "Requires"))
					{
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
					System::Path(*scriptName).loadResource(m_worldScriptEngine, System::Loaders::luaLoader);
					m_scriptArray.push_back(*scriptName);
				}
			}
		}

		void World::clearWorld()
		{
			m_spriteArray.clear();
			m_colliderArray.clear();
			m_gameObjectMap.clear();
			m_updateObjArray.clear();
			m_lightMap.clear();
			m_particleArray.clear();
			m_scriptArray.clear();
		}

		vili::DataParser* World::saveData()
		{
			vili::DataParser* dataStore = new vili::DataParser;
			dataStore->createFlag("Map");
			dataStore->createFlag("Lock");
			(*dataStore)->createComplexAttribute("Meta");
			dataStore->at("Meta")->createBaseAttribute("Level", m_levelName);
			dataStore->at("Meta")->createBaseAttribute("SizeX", m_size->w);
			dataStore->at("Meta")->createBaseAttribute("SizeY", m_size->h);
			(*dataStore)->createComplexAttribute("LevelSprites");
			for (unsigned int i = 0; i < m_spriteArray.size(); i++)
			{
				if (m_spriteArray[i]->getParentID() == "")
				{
					dataStore->at("LevelSprites")->createComplexAttribute(m_spriteArray[i]->getID());
					dataStore->at("LevelSprites", m_spriteArray[i]->getID())->createBaseAttribute("path", m_spriteArray[i]->getPath());
					dataStore->at("LevelSprites", m_spriteArray[i]->getID())->createBaseAttribute("posX", static_cast<int>(m_spriteArray[i]->getX()));
					dataStore->at("LevelSprites", m_spriteArray[i]->getID())->createBaseAttribute("posY", static_cast<int>(m_spriteArray[i]->getY()));
					dataStore->at("LevelSprites", m_spriteArray[i]->getID())->createBaseAttribute("rotation", static_cast<int>(m_spriteArray[i]->getRotation()));
					dataStore->at("LevelSprites", m_spriteArray[i]->getID())->createBaseAttribute("scale", m_spriteArray[i]->getScaleX());
					dataStore->at("LevelSprites", m_spriteArray[i]->getID())->createBaseAttribute("layer", static_cast<int>(m_spriteArray[i]->getLayer()));
					dataStore->at("LevelSprites", m_spriteArray[i]->getID())->createBaseAttribute("z-depth", static_cast<int>(m_spriteArray[i]->getZDepth()));
					if (m_spriteArray[i]->getAttributes().size() != 0)
					{
						dataStore->at("LevelSprites", m_spriteArray[i]->getID())->createListAttribute("attributeList");
						for (unsigned int j = 0; j < m_spriteArray[i]->getAttributes().size(); j++)
							dataStore->at("LevelSprites", m_spriteArray[i]->getID())->getListAttribute("attributeList")->push(m_spriteArray[i]->getAttributes()[j]);
					}
				}
			}
			(*dataStore)->createComplexAttribute("Collisions");
			for (unsigned int i = 0; i < m_colliderArray.size(); i++)
			{
				if (m_colliderArray[i]->getParentID() == "")
				{
					dataStore->at("Collisions")->createComplexAttribute(m_colliderArray[i]->getID());
					dataStore->at("Collisions", m_colliderArray[i]->getID())->createListAttribute("polygonPoints");
					for (unsigned int j = 0; j < m_colliderArray[i]->getPointsAmount(); j++)
					{
						int px = m_colliderArray[i]->getPointPosition(j).first;
						int py = m_colliderArray[i]->getPointPosition(j).second;
						dataStore->at("Collisions", m_colliderArray[i]->getID())->getListAttribute("polygonPoints")->push(std::to_string(px) + "," + std::to_string(py));
					}
				}
			}
			(*dataStore)->createComplexAttribute("LevelObjects");
			for (auto it = m_gameObjectMap.begin(); it != m_gameObjectMap.end(); ++it)
			{
				dataStore->at("LevelObjects")->createComplexAttribute(it->first);
				dataStore->at("LevelObjects", it->first)->createBaseAttribute("type", it->second->getType());
				(*it->second->m_objectScript)("inspect = require('Lib/StdLib/Inspect');");
				kaguya::LuaTable saveTable = (*it->second->m_objectScript)["Local.Save"]();
				kaguya::LuaRef saveTableRef = (*it->second->m_objectScript)["Local.Save"]();
				(*it->second->m_objectScript)("print(inspect(Local.Save()));");
				vili::ComplexAttribute* saveRequirements = Data::DataBridge::luaTableToComplexAttribute(
					"Requires", saveTableRef);
				dataStore->at("LevelObjects", it->first)->pushComplexAttribute(saveRequirements);
			}
			if (m_scriptArray.size() > 0)
			{
				(*dataStore)->createComplexAttribute("Script");
				dataStore->at("Script")->createListAttribute("gameScripts");
				for (int i = 0; i < m_scriptArray.size(); i++)
				{
					dataStore->at("Script")->getListAttribute("gameScripts")->push(m_scriptArray[i]);
				}
			}
			return dataStore;
		}

		void World::update(double dt)
		{
			if (m_updateState)
			{
				m_gameSpeed = dt;
				for (int i = 0; i < m_updateObjArray.size(); i++)
				{
					std::cout << m_updateObjArray[i]->deletable << " / >> " << m_updateObjArray[i]->getID() << " s/AUp" << std::endl;
					if (!m_updateObjArray[i]->deletable)
						m_updateObjArray[i]->update(dt);
					else
					{
						//BUGGY
						/*if (updateObjArray[i]->hasCollider)
							this->deleteCollision(updateObjArray[i]->getCollider(), false);*/
						if (m_updateObjArray[i]->m_hasLevelSprite)
							this->deleteSprite(m_updateObjArray[i]->getLevelSprite());
						m_updateObjArray.erase(m_updateObjArray.begin() + i);
					}
				}

				for (auto iterator = m_lightMap.begin(); iterator != m_lightMap.end(); ++iterator)
				{
					if (iterator->second->getType() == "Dynamic")
					{
						dynamic_cast<Light::DynamicPointLight*>(iterator->second.get())->updateLight();
					}
				}
				for (unsigned int i = 0; i < m_particleArray.size(); i++)
				{
					m_particleArray[i]->update();
				}
			}
		}

		void World::display(sf::RenderWindow* surf)
		{
			displaySprites(surf);
			for (unsigned int i = 0; i < m_particleArray.size(); i++)
			{
				m_particleArray[i]->draw(surf);
			}
			if (m_showCollisionModes["drawLines"] || m_showCollisionModes["drawPoints"] || m_showCollisionModes["drawMasterPoint"] || m_showCollisionModes["drawSkel"])
			{
				for (unsigned int i = 0; i < m_colliderArray.size(); i++)
				{
					m_colliderArray[i]->setDrawOffset(-m_camera.getX(), -m_camera.getY());
					m_colliderArray[i]->draw(surf, m_showCollisionModes["drawLines"], 
						m_showCollisionModes["drawPoints"],
						m_showCollisionModes["drawMasterPoint"], 
						m_showCollisionModes["drawSkel"]);
				}
			}
		}

		void World::displaySprites(sf::RenderWindow* surf)
		{
			for (unsigned int i = 0; i < m_spriteArray.size(); i++)
			{
				int layeredX;
				int layeredY;

				bool lightHooked = m_lightMap.find(m_spriteArray[i]->getID()) != m_lightMap.end();
				Light::PointLight* cLight = nullptr;
				if (lightHooked) cLight = m_lightMap[m_spriteArray[i]->getID()].get();

				layeredX = (((m_spriteArray[i]->getX() + m_spriteArray[i]->getOffsetX()) * (m_spriteArray[i]->getLayer()) -
					m_camera.getX()) / m_spriteArray[i]->getLayer());
				layeredY = (((m_spriteArray[i]->getY() + m_spriteArray[i]->getOffsetY()) * (m_spriteArray[i]->getLayer()) -
					m_camera.getY()) / m_spriteArray[i]->getLayer());
				if (Functions::Vector::isInList(static_cast<std::string>("+FIX"), m_spriteArray[i]->getAttributes()))
				{
					layeredX = m_spriteArray[i]->getX() + m_spriteArray[i]->getOffsetX();
					layeredY = m_spriteArray[i]->getY() + m_spriteArray[i]->getOffsetY();
				}
				else if (Functions::Vector::isInList(static_cast<std::string>("+HFIX"), m_spriteArray[i]->getAttributes()))
				{
					layeredX = m_spriteArray[i]->getX() + m_spriteArray[i]->getOffsetX();
				}
				else if (Functions::Vector::isInList(static_cast<std::string>("+VFIX"), m_spriteArray[i]->getAttributes()))
				{
					layeredY = m_spriteArray[i]->getY() + m_spriteArray[i]->getOffsetY();
				}
				else if (Functions::Vector::isInList(static_cast<std::string>("+PHFIX"), m_spriteArray[i]->getAttributes()))
				{
					layeredX = m_spriteArray[i]->getX() + m_spriteArray[i]->getOffsetX() - m_camera.getX();
				}
				else if (Functions::Vector::isInList(static_cast<std::string>("+PVFIX"), m_spriteArray[i]->getAttributes()))
				{
					layeredY = m_spriteArray[i]->getY() + m_spriteArray[i]->getOffsetY() - m_camera.getY();
				}
				else if (Functions::Vector::isInList(static_cast<std::string>("+PFIX"), m_spriteArray[i]->getAttributes()))
				{
					layeredX = m_spriteArray[i]->getX() + m_spriteArray[i]->getOffsetX() - m_camera.getX();
					layeredY = m_spriteArray[i]->getY() + m_spriteArray[i]->getOffsetY() - m_camera.getY();
				}
				sfe::ComplexSprite tAffSpr;
				tAffSpr = *m_spriteArray[i]->getSprite();

				if (lightHooked) cLight->setPosition(layeredX, layeredY);
				Coord::UnitVector realPosition = Coord::UnitVector(layeredX, layeredY).to<Coord::WorldPixels>();
				tAffSpr.setPosition(realPosition.x, realPosition.y);
				if (lightHooked) { if (cLight->isBehind()) m_lightMap[m_spriteArray[i]->getID()]->draw(surf); }
				if (m_spriteArray[i]->isVisible())
					surf->draw(tAffSpr);
				if (lightHooked) { if (!cLight->isBehind()) m_lightMap[m_spriteArray[i]->getID()]->draw(surf); }
			}
		}

		void World::setSize(int sizeX, int sizeY) const
		{
			m_size->w = sizeX;
			m_size->h = sizeY;
		}

		int World::getSizeX() const
		{
			return m_size->w;
		}

		int World::getSizeY() const
		{
			return m_size->h;
		}

		std::string World::getLevelName() const
		{
			return m_levelName;
		}

		void World::setLevelName(std::string newName)
		{
			m_levelName = newName;
		}

		std::vector<Collision::PolygonalCollider*> World::getColliders() const
		{
			std::vector<Collision::PolygonalCollider*> allColliders;
			for (auto& collider : m_colliderArray)
				allColliders.push_back(collider.get());
			return allColliders;
		}

		Camera& World::getCamera()
		{
			return m_camera;
		}

		Camera& World::getCameraIfNotLocked()
		{
			if (!m_cameraLocked)
				return m_camera;
		}

		void World::setCameraLock(bool state)
		{
			m_cameraLocked = state;
		}

		bool World::isCameraLocked() const
		{
			return m_cameraLocked;
		}

		void World::setUpdateState(bool state)
		{
			m_updateState = state;
		}

		Script::GameObject* World::getGameObject(std::string id)
		{
			if (m_gameObjectMap.find(id) != m_gameObjectMap.end())
				return m_gameObjectMap[id].get();
			std::cout << "<Error:World:World>[getGameObject] : Can't find GameObject : " << id << std::endl;
			return nullptr;
		}

		std::vector<Script::GameObject*> World::getAllGameObjects(std::vector<std::string> filters)
		{
			std::vector<Script::GameObject*> returnVec;
			for (auto it = m_gameObjectMap.begin(); it != m_gameObjectMap.end(); ++it)
			{
				if (filters.size() == 0) returnVec.push_back(it->second.get());
				else
				{
					bool allFilters = true;
					if (Functions::Vector::isInList(std::string("Display"), filters)) { if (!it->second->canDisplay()) allFilters = false; }
					if (Functions::Vector::isInList(std::string("Collide"), filters)) { if (!it->second->canCollide()) allFilters = false; }
					if (Functions::Vector::isInList(std::string("Click"), filters)) { if (!it->second->canClick()) allFilters = false; }
					if (allFilters) returnVec.push_back(it->second.get());
				}
			}
			return returnVec;
		}

		Script::GameObject* World::createGameObject(std::string id, std::string obj)
		{
			std::unique_ptr<Script::GameObject> newGameObject = std::make_unique<Script::GameObject>(obj, id);
			vili::DataParser getGameObjectFile;
			System::Path("Data/GameObjects/").add(obj).add(obj + ".obj.vili").loadResource(&getGameObjectFile, System::Loaders::dataLoader);
			vili::ComplexAttribute* gameObjectData = getGameObjectFile.at(obj);
			newGameObject->loadGameObject(this, gameObjectData);
			if (newGameObject->m_hasScriptEngine)
			{
				loadWorldLib(newGameObject->m_objectScript.get());
				(*newGameObject.get()->m_objectScript)["World"] = this;
			}

			if (newGameObject->canDisplay())
			{
				if (newGameObject->canDisplay() && newGameObject->isLevelSpriteRelative())
					newGameObject->getLevelSprite()->setPosition(0, 0);
				newGameObject->getLevelSprite()->setParentID(id);
			}
			if (newGameObject->m_hasCollider)
			{
				newGameObject->getCollider()->setParentID(id);
			}

			m_gameObjectMap[id] = std::move(newGameObject);
			this->orderUpdateScrArray();
			std::cout << "<World> Created new object : " << id << " of type : " << obj << std::endl;

			return m_gameObjectMap[id].get();
		}

		void World::orderUpdateScrArray()
		{
			m_updateObjArray.clear();
			for (auto it = m_gameObjectMap.begin(); it != m_gameObjectMap.end(); ++it)
				m_updateObjArray.push_back(it->second.get());
			std::sort(m_updateObjArray.begin(), m_updateObjArray.end(), Script::orderScrPriority);
		}

		void World::addParticle(Graphics::MathParticle* particle)
		{
			m_particleArray.push_back(std::unique_ptr<Graphics::MathParticle>(particle));
		}

		void World::reorganizeLayers()
		{
			bool noChange = false;
			while (noChange == false)
			{
				noChange = true;
				for (unsigned int i = 0; i < m_spriteArray.size(); i++)
				{
					if (i != m_spriteArray.size() - 1 && m_spriteArray[i]->getLayer() < m_spriteArray[i + 1]->getLayer())
					{
						std::swap(m_spriteArray[i], m_spriteArray[i + 1]);
						noChange = false;
					}
				}
			}
			noChange = false;
			while (noChange == false)
			{
				noChange = true;
				for (unsigned int i = 0; i < m_spriteArray.size(); i++)
				{
					if (i != m_spriteArray.size() - 1 && m_spriteArray[i]->getLayer() == m_spriteArray[i + 1]->getLayer() && m_spriteArray[i]->getZDepth() < m_spriteArray[i + 1]->getZDepth())
					{
						std::swap(m_spriteArray[i], m_spriteArray[i + 1]);
						noChange = false;
					}
				}
			}
		}

		Graphics::LevelSprite* World::getSpriteByIndex(int index)
		{
			return m_spriteArray[index].get();
		}

		int World::getSpriteArraySize() const
		{
			return m_spriteArray.size();
		}

		std::vector<Graphics::LevelSprite*> World::getAllSprites()
		{
			std::vector<Graphics::LevelSprite*> allSprites;
			for (int i = 0; i < m_spriteArray.size(); i++)
				allSprites.push_back(m_spriteArray[i].get());
			return allSprites;
		}

		std::vector<Graphics::LevelSprite*> World::getSpritesByLayer(int layer)
		{
			std::vector<Graphics::LevelSprite*> returnLayer;

			for (unsigned int i = 0; i < m_spriteArray.size(); i++)
			{
				if (m_spriteArray[i]->getLayer() == layer)
					returnLayer.push_back(m_spriteArray[i].get());
			}

			return returnLayer;
		}

		Graphics::LevelSprite* World::getSpriteByPos(int x, int y, int layer)
		{
			Graphics::LevelSprite* returnSpr = nullptr;
			std::vector<Graphics::LevelSprite*> getSpriteVec = getSpritesByLayer(layer);
			for (unsigned int i = 0; i < getSpriteVec.size(); i++)
			{
				if (x > getSpriteVec[i]->getRect().left && x < getSpriteVec[i]->getRect().left + getSpriteVec[i]->getWidth())
				{
					if (y > getSpriteVec[i]->getRect().top && y < getSpriteVec[i]->getRect().top + getSpriteVec[i]->getHeight())
						returnSpr = getSpriteVec[i];
				}
			}
			return returnSpr;
		}

		Graphics::LevelSprite* World::getSpriteByID(std::string ID)
		{
			for (int i = 0; i < m_spriteArray.size(); i++)
			{
				if (m_spriteArray[i].get()->getID() == ID)
					return m_spriteArray[i].get();
			}
			std::cout << "<Error:World:World>[getSpriteByID] : Can't find Sprite : " << ID << std::endl;
			return nullptr;
		}

		void World::deleteSpriteByID(std::string sprID)
		{
			this->deleteSprite(this->getSpriteByID(sprID));
		}

		void World::deleteSprite(Graphics::LevelSprite* spriteToDelete)
		{
			for (int i = 0; i < m_spriteArray.size(); i++)
			{
				if (m_spriteArray[i].get()->getID() == spriteToDelete->getID())
					m_spriteArray.erase(m_spriteArray.begin() + i);
			}
		}

		void World::enableShowCollision(bool drawLines, bool drawPoints, bool drawMasterPoint, bool drawSkel)
		{
			m_showCollisionModes["drawLines"] = drawLines;
			m_showCollisionModes["drawPoints"] = drawPoints;
			m_showCollisionModes["drawMasterPoint"] = drawMasterPoint;
			m_showCollisionModes["drawSkel"] = drawSkel;
		}

		std::pair<Collision::PolygonalCollider*, int> World::getCollisionPointByPos(int x, int y)
		{
			for (unsigned int i = 0; i < m_colliderArray.size(); i++)
			{
				if (m_colliderArray[i]->hasPoint(x, y, 6, 6) != -1)
				{
					return std::pair<Collision::PolygonalCollider*, int>(m_colliderArray[i].get(), m_colliderArray[i]->hasPoint(x, y, 6, 6));
				}
			}
			return std::pair<Collision::PolygonalCollider*, int>(nullptr, 0);
		}

		Collision::PolygonalCollider* World::getCollisionMasterByPos(int x, int y)
		{
			for (unsigned int i = 0; i < m_colliderArray.size(); i++)
			{
				if (m_colliderArray[i]->hasMasterPoint(x, y, 6, 6))
					return m_colliderArray[i].get();
			}
			return nullptr;
		}

		Collision::PolygonalCollider* World::getCollisionByID(std::string id)
		{
			for (unsigned int i = 0; i < m_colliderArray.size(); i++)
			{
				if (id == m_colliderArray[i]->getID())
				{
					return m_colliderArray[i].get();
				}
			}
			return nullptr;
		}

		std::vector<Collision::PolygonalCollider*> World::getAllCollidersByCollision(Collision::PolygonalCollider* col, int offx, int offy)
		{
			std::vector<Collision::PolygonalCollider*> returnVec;
			for (int i = 0; i < m_colliderArray.size(); i++)
			{
				if (m_colliderArray[i]->doesCollide(col, offx, offy))
				{
					returnVec.push_back(m_colliderArray[i].get());
				}
			}
			return returnVec;
		}

		void World::deleteCollisionByID(std::string id)
		{
			this->deleteCollision(this->getCollisionByID(id));
		}

		void World::deleteCollision(Collision::PolygonalCollider* colToDelete)
		{
			int indexToDelete = 0;
			for (unsigned int i = 0; i < m_colliderArray.size(); i++)
			{
				if (colToDelete == m_colliderArray[i].get())
					indexToDelete = i;
			}
			m_colliderArray.erase(m_colliderArray.begin() + indexToDelete);
		}

		void World::createCollisionAtPos(int x, int y)
		{
			int i = 0;
			std::string testID = "collider" + std::to_string(m_colliderArray.size() + i);
			while (getCollisionByID(testID) != nullptr)
			{
				++i;
				testID = "collider" + std::to_string(m_colliderArray.size() + i);
			}
			Collision::PolygonalCollider* newCollider = this->createCollider(testID);
			newCollider->addPoint(50, 0);
			newCollider->addPoint(0, 50);
			newCollider->addPoint(100, 50);
			newCollider->setPositionFromMaster(x, y);
		}

		void loadWorldLib(kaguya::State* lua)
		{
			if (!static_cast<bool>((*lua)["Core"])) (*lua)["Core"] = kaguya::NewTable();
			(*lua)["Core"]["World"] = kaguya::NewTable();
			(*lua)["Core"]["World"]["World"].setClass(kaguya::UserdataMetatable<World>()
				.addFunction("addLevelSprite", &World::createLevelSprite)
				.addFunction("addLight", &World::addLight)
				.addFunction("addCollider", &World::createCollider)
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
