//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <algorithm>
#include <kaguya/kaguya.hpp>

#include "Animation.hpp"
#include "Collisions.hpp"
#include "DataParser.hpp"
#include "LevelSprite.hpp"
#include "Script.hpp"
#include "Triggers.hpp"

class GameObject
{
	private:
		anim::Animator objectAnimator;
		LevelSprite objectLevelSprite;
		Collision::PolygonalCollider objectCollider;
		kaguya::State* scriptEngine;

		std::vector<Trigger*> registeredTriggers;
		TriggerGroup* localTriggers;
		std::vector<std::tuple<std::string, std::string, std::string>> registeredAliases;

		std::string id;
		std::string privateKey;
		std::string publicKey;
		int scrPriority = 0;

		bool hasAnimator = false;
		bool hasCollider = false;
		bool colliderSolid = false;
		bool colliderClick = false;
		bool colliderRelative = true;
		bool hasLevelSprite = false;

		GameObject(std::string id);
		void registerTrigger(Trigger* trg);
		void loadGameObject(DataObject* obj);
		void hookLuaState(kaguya::State* lua);
		void update(double dt);
		friend class GameObjectHandler;
		friend class World;
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
		kaguya::State* getScriptEngine();
		TriggerGroup* getLocalTriggers();
		void useLocalTrigger(std::string trName);
		void useGlobalTrigger(std::string trName);
		void useCustomTrigger(std::string trNsp, std::string trGrp, std::string trName, std::string useAs);
		template <typename U>
		void sendRequireArgument(std::string argName, U value);
};

void loadScrGameObjectLib(GameObject* obj, kaguya::State* lua);
bool orderScrPriority(GameObject* g1, GameObject* g2);
void loadLibBridge(GameObject* object, std::string lib);
void loadHookBridge(GameObject* object, std::string hookname);

template<typename U>
inline void GameObject::sendRequireArgument(std::string argName, U value)
{
	(*this->scriptEngine)["Lua_ReqList"][argName] = value;
}
