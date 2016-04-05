//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "World.hpp"

void World::addCharacter(Character* character)
{
	charArray.push_back(character);
	character->setColliders(&this->collidersArray);
	character->setPos(this->getStartX(), this->getStartY());
}

void World::addLevelSprite(LevelSprite* spr)
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
	lightMap[lgt->getID()] = lgt;
}

anim::RessourceManager* World::getRessourceManager()
{
	return &sprRsMan;
}

Character* World::getCharacter(int index)
{
	return charArray[index];
}

void World::loadFromFile(std::string filename)
{
	double startLoadTime = getTickSinceEpoch();
	int arrayLoad = 0;
	int arrayLoadFrontDeco = 0;
	int arrayLoadBackDeco = 0;
	int indexInFile = 0;
	DataParser mapParse;
	std::cout << "Creation Chrono : " << "[WorldStart]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();
	mapParse.parseFile("Data/Maps/"+filename);
	std::cout << "Creation Chrono : " << "[WorldParse]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	mapParse.getAttribute("Meta", "", "Level")->getData(&levelName);
	mapParse.getAttribute("Meta", "", "SizeX")->getData(&sizeX);
	mapParse.getAttribute("Meta", "", "SizeY")->getData(&sizeY);
	if (mapParse.attributeExists("Meta", "", "StartX"))
		mapParse.getAttribute("Meta", "", "StartX")->getData(&startX);
	if (mapParse.attributeExists("Meta", "", "StartY"))
		mapParse.getAttribute("Meta", "", "StartY")->getData(&startY);

	std::cout << "Creation Chrono : " << "[WorldMeta]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	if (mapParse.dataObjectExists("LevelSprites"))
	{
		std::vector<std::string> allDecos = mapParse.getAllComplex("LevelSprites", "");
		for (unsigned int i = 0; i < allDecos.size(); i++)
		{
			std::string decoID, decoType;
			int decoPosX, decoPosY;
			int decoRot = 0;
			double decoSca = 1.0;
			std::vector<std::string> decoAtrList;
			std::string attrBuffer;
			int layer;
			int zdepth;
			decoID = allDecos[i];
			mapParse.getAttribute("LevelSprites", allDecos[i], "type")->getData(&decoType);
			mapParse.getAttribute("LevelSprites", allDecos[i], "posX")->getData(&decoPosX);
			mapParse.getAttribute("LevelSprites", allDecos[i], "posY")->getData(&decoPosY);
			mapParse.getAttribute("LevelSprites", allDecos[i], "rotation")->getData(&decoRot);
			mapParse.getAttribute("LevelSprites", allDecos[i], "scale")->getData(&decoSca);
			mapParse.getAttribute("LevelSprites", allDecos[i], "layer")->getData(&layer);
			mapParse.getAttribute("LevelSprites", allDecos[i], "z-depth")->getData(&zdepth);
			if (mapParse.listExists("LevelSprites", allDecos[i], "attributeList"))
			{
				int atrListSize = mapParse.getListSize("LevelSprites", allDecos[i], "attributeList");
				for (int j = 0; j < atrListSize; j++)
					decoAtrList.push_back(mapParse.getListItem("LevelSprites", allDecos[i], "attributeList", j)->getData(&attrBuffer));
			}
			LevelSprite* tempDeco = new LevelSprite(decoID);
			if (decoType != "None")
			{
				delete tempDeco;
				tempDeco = new LevelSprite(decoType, decoID, &sprRsMan);
			}
			tempDeco->move(decoPosX, decoPosY);
			tempDeco->setRotation(decoRot);
			tempDeco->setScale(decoSca);
			tempDeco->setAtr(decoAtrList);
			tempDeco->setLayer(layer);
			tempDeco->setZDepth(zdepth);
			tempDeco->textureUpdate();
			if (layer >= 1)
				backSpriteArray.push_back(tempDeco);
			else if (layer <= -2)
				frontSpriteArray.push_back(tempDeco);
		}
	}
	std::cout << "Creation Chrono : " << "[WorldLevelSprites]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();


	this->reorganizeLayers();
	std::cout << "Creation Chrono : " << "[WorldReorganize]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();


	if (mapParse.dataObjectExists("Lights"))
	{
		std::vector<std::string> allLights = mapParse.getAllComplex("Lights", "");
		for (int i = 0; i < allLights.size(); i++)
		{
			std::string ltype;
			mapParse.getAttribute("Lights", allLights[i], "type")->getData(&ltype);
			if (ltype == "Static")
			{
				double lsize;
				double lr, lg, lb, la;
				std::string lsBind;
				bool lbehind;
				double loffX = 0;
				double loffY = 0;
				mapParse.getAttribute("Lights", allLights[i], "size")->getData(&lsize);
				mapParse.getAttribute("Lights", allLights[i], "r")->getData(&lr);
				mapParse.getAttribute("Lights", allLights[i], "g")->getData(&lg);
				mapParse.getAttribute("Lights", allLights[i], "b")->getData(&lb);
				mapParse.getAttribute("Lights", allLights[i], "a")->getData(&la);
				mapParse.getAttribute("Lights", allLights[i], "bind")->getData(&lsBind);
				mapParse.getAttribute("Lights", allLights[i], "behind")->getData(&lbehind);
				if (mapParse.attributeExists("Lights", allLights[i], "offsetX")) mapParse.getAttribute("Lights", allLights[i], "offsetX")->getData(&loffX);
				if (mapParse.attributeExists("Lights", allLights[i], "offsetY")) mapParse.getAttribute("Lights", allLights[i], "offsetY")->getData(&loffY);
				if (getSpriteByID(lsBind) != NULL)
				{
					lightMap[lsBind] = new Light::PointLight(allLights[i], sf::Vector2f(1920, 1080), sf::Vector2f(0, 0), lsize, sf::Color(lr, lg, lb, la));
					lightMap[lsBind]->setOffset(loffX, loffY);
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

				mapParse.getAttribute("Lights", allLights[i], "precision")->getData(&lprecision);
				mapParse.getAttribute("Lights", allLights[i], "size")->getData(&lsize);
				mapParse.getAttribute("Lights", allLights[i], "r")->getData(&lr);
				mapParse.getAttribute("Lights", allLights[i], "g")->getData(&lg);
				mapParse.getAttribute("Lights", allLights[i], "b")->getData(&lb);
				mapParse.getAttribute("Lights", allLights[i], "a")->getData(&la);
				mapParse.getAttribute("Lights", allLights[i], "bind")->getData(&lsBind);
				mapParse.getAttribute("Lights", allLights[i], "behind")->getData(&lbehind);
				if (mapParse.attributeExists("Lights", allLights[i], "offsetX")) mapParse.getAttribute("Lights", allLights[i], "offsetX")->getData(&loffX);
				if (mapParse.attributeExists("Lights", allLights[i], "offsetY")) mapParse.getAttribute("Lights", allLights[i], "offsetY")->getData(&loffY);
				if (getSpriteByID(lsBind) != NULL)
				{
					Light::DynamicPointLight* tdpl = new Light::DynamicPointLight(allLights[i], sf::Vector2f(1920, 1080), lprecision);
					tdpl->setSizeExp(lsize);
					tdpl->setRExp(lr); tdpl->setGExp(lg); tdpl->setBExp(lb);
					tdpl->setOffsetXExp(loffX);
					tdpl->setOffsetYExp(loffY);
					lightMap[lsBind] = tdpl;
				}
			}
		}
	}
	std::cout << "Creation Chrono : " << "[WorldLights]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	if (mapParse.dataObjectExists("Collisions"))
	{
		std::vector<std::string> allCol = mapParse.getAllComplex("Collisions", "");
		for (unsigned int i = 0; i < allCol.size(); i++)
		{
			std::string colID = allCol[i];
			Collision::PolygonalCollider* tempCollider = new Collision::PolygonalCollider(colID);
			for (unsigned int j = 0; j < mapParse.getListSize("Collisions", colID, "polygonPoints"); j++)
			{
				std::string getPt;
				mapParse.getListItem("Collisions", colID, "polygonPoints", j)->getData(&getPt);
				std::vector<std::string> tPoint = fn::String::split(getPt, ",");
				tempCollider->addPoint(std::stoi(tPoint[0]), std::stoi(tPoint[1]));
			}
			this->collidersArray.push_back(tempCollider);
		}
	}
	std::cout << "Creation Chrono : " << "[WorldCollisions]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();


	if (mapParse.dataObjectExists("LevelObjects"))
	{
		std::vector<std::string> allObjects = mapParse.getAllComplex("LevelObjects", "");
		for (unsigned int i = 0; i < allObjects.size(); i++)
		{
			std::string levelObjectType;
			mapParse.getAttribute("LevelObjects", allObjects[i], "type")->getData(&levelObjectType);
			gameObjectHandlerCore.createGameObject(allObjects[i], "LevelObjects", levelObjectType);
			bool hasSpr = false;
			int objX = 0;
			int objY = 0;
			if (gameObjectHandlerCore.getGameObject(allObjects[i])->canDisplay())
			{
				this->addLevelSprite(gameObjectHandlerCore.getGameObject(allObjects[i])->getLevelSprite());
				hasSpr = true;
				if (mapParse.attributeExists("LevelObjects", allObjects[i], "posX"))
					mapParse.getAttribute("LevelObjects", allObjects[i], "posX")->getData(&objX);
				if (mapParse.attributeExists("LevelObjects", allObjects[i], "posY"))
					mapParse.getAttribute("LevelObjects", allObjects[i], "posY")->getData(&objY);
				gameObjectHandlerCore.getGameObject(allObjects[i])->getLevelSprite()->setPosition(objX, objY);
			}
			if (gameObjectHandlerCore.getGameObject(allObjects[i])->canCollide() || gameObjectHandlerCore.getGameObject(allObjects[i])->canClick())
			{
				this->addCollider(gameObjectHandlerCore.getGameObject(allObjects[i])->getCollider());
				if (hasSpr && gameObjectHandlerCore.getGameObject(allObjects[i])->isColliderRelative())
					gameObjectHandlerCore.getGameObject(allObjects[i])->getCollider()->setPosition(objX, objY);
			}
		}
	}
	std::cout << "Creation Chrono : " << "[WorldLevelObjects]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();

	if (mapParse.dataObjectExists("Script"))
	{
		int scriptAmt = mapParse.getListAttribute("Script", "", "gameScripts")->getSize();
		for (int i = 0; i < scriptAmt; i++)
		{
			std::string scriptName;
			mapParse.getListAttribute("Script", "", "gameScripts")->getElement(i)->getData(&scriptName);
			gameObjectHandlerCore.executeFile("Main", scriptName);
		}
	}
	std::cout << "Creation Chrono : " << "[WorldScript]" << getTickSinceEpoch() - startLoadTime << std::endl; startLoadTime = getTickSinceEpoch();
}

DataParser* World::saveData()
{
	DataParser* dataStore = new DataParser;
	dataStore->createFlag("Map");
	dataStore->createFlag("Lock");
	dataStore->createDataObject("Meta");
	dataStore->createBaseAttribute("Meta", "", "Level", levelName);
	dataStore->createBaseAttribute("Meta", "", "SizeX", sizeX);
	dataStore->createBaseAttribute("Meta", "", "SizeY", sizeY);
	dataStore->createBaseAttribute("Meta", "", "StartX", startX);
	dataStore->createBaseAttribute("Meta", "", "StartY", startY);
	dataStore->createDataObject("Objects");
	dataStore->createDataObject("LevelSprites");
	for (unsigned int i = 0; i < backSpriteArray.size(); i++)
	{
		dataStore->createComplexAttribute("LevelSprites", "", backSpriteArray[i]->getID());
		dataStore->createBaseAttribute("LevelSprites", backSpriteArray[i]->getID(), "type", backSpriteArray[i]->getName());
		dataStore->createBaseAttribute("LevelSprites", backSpriteArray[i]->getID(), "posX", (int)backSpriteArray[i]->getX());
		dataStore->createBaseAttribute("LevelSprites", backSpriteArray[i]->getID(), "posY", (int)backSpriteArray[i]->getY());
		dataStore->createBaseAttribute("LevelSprites", backSpriteArray[i]->getID(), "rotation", (int)backSpriteArray[i]->getRotation());
		dataStore->createBaseAttribute("LevelSprites", backSpriteArray[i]->getID(), "scale", backSpriteArray[i]->getScale());
		dataStore->createBaseAttribute("LevelSprites", backSpriteArray[i]->getID(), "layer", (int)backSpriteArray[i]->getLayer());
		dataStore->createBaseAttribute("LevelSprites", backSpriteArray[i]->getID(), "z-depth", (int)backSpriteArray[i]->getZDepth());
		if (backSpriteArray[i]->getAttributes().size() != 0)
		{
			dataStore->createListAttribute("LevelSprites", backSpriteArray[i]->getID(), "attributeList", "str");
			for (unsigned int j = 0; j < backSpriteArray[i]->getAttributes().size(); j++)
				dataStore->createListItem("LevelSprites", backSpriteArray[i]->getID(), "attributeList", backSpriteArray[i]->getAttributes()[j]);
		}
	}
	dataStore->createDataObject("Collisions");
	for (unsigned int i = 0; i < collidersArray.size(); i++)
	{
		dataStore->createComplexAttribute("Collisions", "", collidersArray[i]->getID());
		dataStore->createListAttribute("Collisions", collidersArray[i]->getID(), "polygonPoints", "str");
		for (unsigned int j = 0; j < collidersArray[i]->getPointsAmount(); j++)
		{
			int px = collidersArray[i]->getPointCoordinates(j).first;
			int py = collidersArray[i]->getPointCoordinates(j).second;
			dataStore->createListItem("Collisions", collidersArray[i]->getID(), "polygonPoints", std::to_string(px) + "," + std::to_string(py));
		}

	}
	return dataStore;
}

void World::castSpell(Spells::Projectile* spellToCast)
{
	spellArray.push_back(spellToCast);
}

void World::update(double dt)
{
	this->gameSpeed = dt;
	typedef std::map<std::string, Light::PointLight*>::iterator it_mspl;
	for (it_mspl iterator = lightMap.begin(); iterator != lightMap.end(); iterator++)
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
	for (unsigned int i = 0; i < spellArray.size(); i++)
	{
		spellArray[i]->update(gameSpeed);
		if (!spellArray[i]->isSpellAlive())
		{
			spellArray.erase(spellArray.begin()+i);
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
		charArray[i]->getEntityCollider()->draw(surf);
	}
	for (unsigned int i = 0; i < particleArray.size(); i++)
	{
		particleArray[i]->draw(surf);
	}
	visualDisplayFront(surf);
	for (unsigned int i = 0; i < collidersArray.size(); i++)
	{
		collidersArray[i]->setDrawOffset(-camX, -camY);
		collidersArray[i]->draw(surf, showCollisionModes["drawLines"], showCollisionModes["drawPoints"], showCollisionModes["drawMasterPoint"], showCollisionModes["drawSkel"]);
	}
}

void World::visualDisplayBack(sf::RenderWindow* surf)
{
	for (unsigned int i = 0; i < backSpriteArray.size(); i++)
	{
		int layeredX = 0;
		int layeredY = 0;

		bool lightHooked = lightMap.find(backSpriteArray[i]->getID()) != lightMap.end();
		Light::PointLight* cLight = NULL;
		if (lightHooked) cLight = lightMap[backSpriteArray[i]->getID()];

		if (fn::Vector::isInList((std::string)"+FIX", backSpriteArray[i]->getAttributes()))
		{
			layeredX = backSpriteArray[i]->getX();
			layeredY = backSpriteArray[i]->getY();
		}
		else if (fn::Vector::isInList((std::string)"+VFIX", backSpriteArray[i]->getAttributes()))
		{
			layeredX = ((backSpriteArray[i]->getX()*(backSpriteArray[i]->getLayer()) - camX) / backSpriteArray[i]->getLayer());
			layeredY = backSpriteArray[i]->getY();
		}
		else if (fn::Vector::isInList((std::string)"+HFIX", backSpriteArray[i]->getAttributes()))
		{
			layeredX = backSpriteArray[i]->getX();
			layeredY = ((backSpriteArray[i]->getY()*(backSpriteArray[i]->getLayer()) - camY) / backSpriteArray[i]->getLayer());
		}
		else if (fn::Vector::isInList((std::string)"+PHFIX", backSpriteArray[i]->getAttributes()))
		{
			layeredX = backSpriteArray[i]->getX() - camX;
			layeredY = ((backSpriteArray[i]->getY()*(backSpriteArray[i]->getLayer()) - camY) / backSpriteArray[i]->getLayer());
		}
		else if (fn::Vector::isInList((std::string)"+PVFIX", backSpriteArray[i]->getAttributes()))
		{
			layeredX = ((backSpriteArray[i]->getX()*(backSpriteArray[i]->getLayer()) - camX) / backSpriteArray[i]->getLayer());
			layeredY = backSpriteArray[i]->getY() - camY;
		}
		else if (fn::Vector::isInList((std::string)"+PFIX", backSpriteArray[i]->getAttributes()))
		{
			layeredX = backSpriteArray[i]->getX() - camX;
			layeredY = backSpriteArray[i]->getY() - camY;
		}
		else
		{
			layeredX = ((backSpriteArray[i]->getX()*(backSpriteArray[i]->getLayer()) - camX) / backSpriteArray[i]->getLayer());
			layeredY = ((backSpriteArray[i]->getY()*(backSpriteArray[i]->getLayer()) - camY) / backSpriteArray[i]->getLayer());
		}
		backSpriteArray[i]->textureUpdate();
		if (layeredX + backSpriteArray[i]->getW() > 0 && layeredY + backSpriteArray[i]->getH() > 0)
		{
			if (layeredX < width && layeredY < height)
			{
				sfe::ComplexSprite tAffSpr;
				blurShader.setParameter("texture", sf::Shader::CurrentTexture);
				blurShader.setParameter("blur_radius", blurMul*(backSpriteArray[i]->getLayer() - 1));
				tAffSpr = *backSpriteArray[i]->getSprite();

				if (lightHooked) cLight->setPosition(layeredX, layeredY);
				tAffSpr.setPosition(layeredX, layeredY);
				if (lightHooked) { if (cLight->isBehind()) lightMap[backSpriteArray[i]->getID()]->draw(surf); }
				surf->draw(tAffSpr, &blurShader);
				if (lightHooked) { if (!cLight->isBehind()) lightMap[backSpriteArray[i]->getID()]->draw(surf); }
			}
		}
	}
	for (unsigned int i = 0; i < spellArray.size(); i++)
	{
		int blitSpellX = spellArray[i]->getX() - camX;
		int blitSpellY = spellArray[i]->getY() - camY;
		sf::Sprite tSpellSpr = *spellArray[i]->getSprite();
		tSpellSpr.setPosition(blitSpellX, blitSpellY);
		surf->draw(tSpellSpr);
	}
}

void World::visualDisplayFront(sf::RenderWindow* surf)
{
	for (unsigned int i = 0; i < frontSpriteArray.size(); i++)
	{
		int layeredX = 0;
		int layeredY = 0;

		bool lightHooked = lightMap.find(frontSpriteArray[i]->getID()) != lightMap.end();
		Light::PointLight* cLight = NULL;
		if (lightHooked) cLight = lightMap[frontSpriteArray[i]->getID()];

		if (fn::Vector::isInList((std::string)"+FIX", frontSpriteArray[i]->getAttributes()))
		{
			layeredX = frontSpriteArray[i]->getX();
			layeredY = frontSpriteArray[i]->getY();
		}
		else if (fn::Vector::isInList((std::string)"+VFIX", frontSpriteArray[i]->getAttributes()))
		{
			layeredX = ((frontSpriteArray[i]->getX() / (frontSpriteArray[i]->getLayer()) + camX) * frontSpriteArray[i]->getLayer());
			layeredY = frontSpriteArray[i]->getY();
		}
		else if (fn::Vector::isInList((std::string)"+HFIX", frontSpriteArray[i]->getAttributes()))
		{
			layeredX = frontSpriteArray[i]->getX();
			layeredY = ((frontSpriteArray[i]->getY() / (frontSpriteArray[i]->getLayer()) + camY) * frontSpriteArray[i]->getLayer());
		}
		else if (fn::Vector::isInList((std::string)"+PHFIX", frontSpriteArray[i]->getAttributes()))
		{
			layeredX = frontSpriteArray[i]->getX() - camX;
			layeredY = ((frontSpriteArray[i]->getY() / (frontSpriteArray[i]->getLayer()) + camY) * frontSpriteArray[i]->getLayer());
		}
		else if (fn::Vector::isInList((std::string)"+PVFIX", frontSpriteArray[i]->getAttributes()))
		{
			layeredX = ((frontSpriteArray[i]->getX() / (frontSpriteArray[i]->getLayer()) + camX) * frontSpriteArray[i]->getLayer());
			layeredY = frontSpriteArray[i]->getY() - camY;
		}
		else if (fn::Vector::isInList((std::string)"+PFIX", frontSpriteArray[i]->getAttributes()))
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
		if (layeredX + backSpriteArray[i]->getW() > 0 && layeredY + backSpriteArray[i]->getH() > 0)
		{
			if (layeredX < width && layeredY < height)
			{
				sfe::ComplexSprite tAffSpr;
				blurShader.setParameter("texture", sf::Shader::CurrentTexture);
				blurShader.setParameter("blur_radius", blurMul*(backSpriteArray[i]->getLayer() - 1));
				tAffSpr = *frontSpriteArray[i]->getSprite();

				if (lightHooked) cLight->setPosition(layeredX, layeredY);
				tAffSpr.setPosition(layeredX, layeredY);
				if (lightHooked) { if (cLight->isBehind()) lightMap[frontSpriteArray[i]->getID()]->draw(surf); }
				surf->draw(tAffSpr, &blurShader);
				if (lightHooked) { if (!cLight->isBehind()) lightMap[frontSpriteArray[i]->getID()]->draw(surf); }
			}
		}
	}
}

void World::init()
{
	triggerDatabaseCore.createCustomNamespace("Map");
	showCollisionModes["drawLines"] = false;
	showCollisionModes["drawPoints"] = false;
	showCollisionModes["drawMasterPoint"] = false;
	showCollisionModes["drawSkel"] = false;
	blurShader.loadFromFile("Data/Shaders/blur.frag", sf::Shader::Fragment);
	normalShader.loadFromFile("Data/Shaders/normalMap.frag", sf::Shader::Fragment);
	for (unsigned int i = 0; i < backSpriteArray.size(); i++)
	{
		backSpriteArray[i]->textureUpdate(true);
	}
	for (unsigned int i = 0; i < frontSpriteArray.size(); i++)
	{
		frontSpriteArray[i]->textureUpdate(true);
	}
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
	if (camX + width > sizeX)
		camX = sizeX - width;
	if (camY <= 0)
		camY = 0;
	if (camY + height > sizeY)
		camY = sizeY - height;
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

void World::addParticle(MathParticle* particle)
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
					LevelSprite* saveLayer = backSpriteArray[i];
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
						LevelSprite* saveLayer = backSpriteArray[i];
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
					LevelSprite* saveLayer = frontSpriteArray[i];
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
						LevelSprite* saveLayer = frontSpriteArray[i];
						frontSpriteArray[i] = frontSpriteArray[i + 1];
						frontSpriteArray[i + 1] = saveLayer;
						noChange = false;
					}
				}
			}
		}
	}
}

LevelSprite* World::getSpriteByIndex(std::string backOrFront, int index)
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

std::vector<LevelSprite*> World::getAllSprites()
{
	std::vector<LevelSprite*> allDec;
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
std::vector<LevelSprite*> World::getSpritesByLayer(int layer)
{
	std::vector<LevelSprite*> returnLayer;
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

LevelSprite* World::getSpriteByPos(int x, int y, int layer)
{
	LevelSprite* returnDeco = NULL;
	std::vector<LevelSprite*> getDecoVec = getSpritesByLayer(layer);
	for (unsigned int i = 0; i < getDecoVec.size(); i++)
	{
		if (x > getDecoVec[i]->getRect().left && x < getDecoVec[i]->getRect().left + getDecoVec[i]->getW())
		{
			if (y > getDecoVec[i]->getRect().top && y < getDecoVec[i]->getRect().top + getDecoVec[i]->getH())
				returnDeco = getDecoVec[i];
		}
	}
	return returnDeco;
}

LevelSprite* World::getSpriteByID(std::string ID)
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

void World::deleteSprite(LevelSprite* decoToDelete, bool freeMemory)
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
		if (collidersArray[i]->doesCollide(col, offx, offy, false))
		{
			returnVec.push_back(collidersArray[i]);
		}
	}
	return returnVec;
}

void World::deleteCollisionByID(std::string id)
{
	int indexToDelete;
	for (unsigned int i = 0; i < collidersArray.size(); i++)
	{
		if (id == collidersArray[i]->getID())
		{
			indexToDelete = i;
		}
	}
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
