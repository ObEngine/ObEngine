//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

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

		bool hasAnimator = false;
		bool hasCollider = false;
		bool colliderSolid = false;
		bool colliderClick = false;
		bool colliderRelative = true;
		bool hasLevelSprite = false;

		kaguya::State* scriptEngine;

		GameObject(std::string id);
		void registerTrigger(Trigger* trg);
		void loadGameObject(DataObject* obj);
		void hookLuaState(kaguya::State* lua);
		void update(double dt);
		friend void useLocalTrigger(std::string scrKey, std::string trName);
		friend void useGlobalTrigger(std::string scrKey, std::string trName);
		friend void useCustomTrigger(std::string scrKey, std::string trNsp, std::string trGrp, std::string trName, std::string useAs);
		friend void loadScrGameObjectLib(GameObject* obj, kaguya::State* lua, bool fullLoad);
		friend class GameObjectHandler;
	public:
		std::string getID();
		std::string getPublicKey();
		void setAnimationKey(std::string key);
		int getPriority();
		bool canDisplay();
		bool canCollide();
		bool canClick();
		bool isColliderRelative();
		LevelSprite* getLevelSprite();
		Collision::PolygonalCollider* getCollider();
		anim::Animator* getAnimator();
};

void loadScrGameObjectLib(GameObject* obj, kaguya::State* lua, bool fullLoad = false);
void loadScrGameObjectHandlerLib(kaguya::State* lua);
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
		kaguya::State* getLuaStateOfGameObject(std::string object);
		void setTriggerState(std::string object, std::string trigger, bool state);
		void setGlobalTriggerState(std::string trigger, bool state);
		void update(double dt);
};

template<typename U>
void GameObjectHandler::sendRequireArgument(std::string object, std::string argName, U value)
{
	std::cout << "Adding Parameter : " << argName << std::endl;
	(*this->scrHandlerMap[this->getGameObject(object)->key])["Lua_ReqList"][argName] = value;
}


extern GameObjectHandler gameObjectHandlerCore;
extern GameObject* mainGameObject;