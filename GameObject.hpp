#pragma once

#include <algorithm>
#include <kaguya/kaguya.hpp>

#include "Animation.hpp"
#include "Collisions.hpp"
#include "Console.hpp"
#include "DataParser.hpp"
#include "Triggers.hpp"
#include "LevelSprite.hpp"
#include "Script.hpp"

void useLocalTrigger(std::string scrKey, std::string trName);
void useGlobalTrigger(std::string scrKey, std::string trName);
void useCustomTrigger(std::string scrKey, std::string trNsp, std::string trGrp, std::string trName, std::string useAs);
void loadLibBridge(std::string scrKey, std::string lib);
void loadHookBridge(std::string scrKey, std::string hookname);

class GameObject
{
	private:
		anim::Animator objectAnimator;
		LevelSprite objectLevelSprite;
		Collision::PolygonalCollider objectCollider;
		std::vector<Trigger*> registeredTriggers;
		std::vector<std::tuple<std::string, std::string, std::string>> registeredAliases;
		std::vector<std::string> a;
		DataObject* objFile;
		std::string id;
		std::string key;
		std::string publicKey;
		int scrPriority = 0;
		double currentDeltaTime = 0.0;

		bool hasAnimator = true;
		bool hasCollider = true;
		bool colliderSolid = false;
		bool colliderClick = false;
		bool hasLevelSprite = true;

		kaguya::State* scriptEngine;

		GameObject(std::string id);
		void registerTrigger(Trigger* trg);
		void loadGameObject(DataObject* obj);
		void hookLuaState(kaguya::State* lua);
		void update();
		void setDeltaTime(double dt);
		friend void useLocalTrigger(std::string scrKey, std::string trName);
		friend void useGlobalTrigger(std::string scrKey, std::string trName);
		friend void useCustomTrigger(std::string scrKey, std::string trNsp, std::string trGrp, std::string trName, std::string useAs);
		friend void loadScrGameObjectLib(GameObject* obj, kaguya::State* lua);
		friend class GameObjectHandler;
	public:
		std::string getID();
		std::string getPublicKey();
		double getDeltaTime();
		void setAnimationKey(std::string key);
		int getPriority();
		bool canDisplay();
		bool canCollide();
		bool canClick();
		LevelSprite* getLevelSprite();
		Collision::PolygonalCollider* getCollider();
};

void loadScrGameObjectLib(GameObject* obj, kaguya::State* lua);
bool orderScrPriority(GameObject* g1, GameObject* g2);
	
class GameObjectHandler
{
	private:
		std::map<std::string, GameObject*> objHandlerMap;
		std::map<std::string, kaguya::State*> scrHandlerMap;
		std::map<std::string, TriggerGroup*> trgHandlerMap;
		std::vector<GameObject*> updateObjArray;
		std::vector<std::pair<std::string, std::string>*> triggerToDisable;

		void orderUpdateScrArray();

		friend void useLocalTrigger(std::string scrKey, std::string trName);
		friend void useGlobalTrigger(std::string scrKey, std::string trName);
		friend void useCustomTrigger(std::string scrKey, std::string trNsp, std::string trGrp, std::string trName, std::string useAs);
		friend void loadLibBridge(std::string scrKey, std::string lib);
		friend void loadHookBridge(std::string scrKey, std::string hookname);
	public:
		GameObject* getGameObject(std::string id);
		std::vector<GameObject*> getAllGameObject(std::vector<std::string> filters = std::vector<std::string>());
		GameObject* createGameObject(std::string id, std::string type, std::string obj);
		template <typename U>
		void sendRequireArgument(std::string object, std::string argName, U value);
		void executeFile(std::string object, std::string path);
		void executeLine(std::string object, std::string line);
		void setTriggerState(std::string object, std::string trigger, bool state);
		void setGlobalTriggerState(std::string trigger, bool state);
		void update();
};

template<typename U>
void GameObjectHandler::sendRequireArgument(std::string object, std::string argName, U value)
{
	std::cout << "Adding Parameter : " << argName << std::endl;
	(*this->scrHandlerMap[this->getGameObject(object)->key])["Lua_ReqList"][argName] = value;
}


extern GameObjectHandler gameObjectHandlerCore;