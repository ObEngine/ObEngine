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

namespace mse
{
	namespace World
	{
		class World;
	}
	namespace Script
	{
		class GameObjectRequires
		{
			private:
				static GameObjectRequires* instance;
				Data::DataParser allRequires;
			public:
				static GameObjectRequires* getInstance();
				Data::ComplexAttribute* getRequiresForObjectType(std::string type);
				void applyBaseRequires(GameObject* obj, Data::ComplexAttribute& requires);
				static void ApplyRequirements(GameObject* obj, Data::ComplexAttribute& requires);
		};

		class GameObject
		{
			private:
				Animation::Animator objectAnimator;
				Graphics::LevelSprite objectLevelSprite;
				Collision::PolygonalCollider objectCollider;
				kaguya::State* scriptEngine;

				std::vector<Script::Trigger*> registeredTriggers;
				Script::TriggerGroup* localTriggers;
				std::vector<std::tuple<std::string, std::string, std::string>> registeredAliases;

				std::string id;
				std::string type;
				std::string privateKey;
				std::string publicKey;
				int scrPriority = 0;

				bool hasAnimator = false;
				bool hasCollider = false;
				bool colliderSolid = false;
				bool colliderClick = false;
				bool levelSpriteRelative = true;
				bool hasLevelSprite = false;
				bool initialised = false;
				bool updated = true;

				int queryCounter = 0;

				GameObject(std::string type, std::string id);
				void registerTrigger(Script::Trigger* trg);
				void loadGameObject(Data::ComplexAttribute* obj);
				void hookLuaState(kaguya::State* lua);
				void update(double dt);

				friend class World::World;
			public:
				std::string getID();
				std::string getType();
				std::string getPublicKey();
				void setAnimationKey(std::string key);
				int getPriority();
				bool canDisplay();
				bool canCollide();
				bool canClick();
				bool doesHaveCollider();
				bool doesHaveLevelSprite();
				bool isLevelSpriteRelative();
				bool getUpdateState();
				void setUpdateState(bool state);
				Graphics::LevelSprite* getLevelSprite();
				Collision::PolygonalCollider* getCollider();
				Animation::Animator* getAnimator();
				kaguya::State* getScriptEngine();
				Script::TriggerGroup* getLocalTriggers();
				void useLocalTrigger(std::string trName);
				void useExternalTrigger(std::string trNsp, std::string trGrp, std::string trName, std::string useAs = "");
				void setInitialised(bool init);
				bool getInitialised();
				void exec(std::string query);
				template <typename U>
				void sendQuery(U query);
				template <typename U>
				void sendRequireArgumentFromCPP(std::string argName, U value);
				void sendRequireArgumentFromLua(std::string argName, kaguya::LuaRef value);

				void deleteObject();
				bool deletable = false;
		};

		void loadScrGameObject(GameObject* obj, kaguya::State* lua);
		void loadScrGameObjectLib(kaguya::State* lua);
		bool orderScrPriority(GameObject* g1, GameObject* g2);
		void loadLibBridge(GameObject* object, std::string lib);
		void loadHookBridge(GameObject* object, std::string hookname);

		template<typename U>
		inline void GameObject::sendRequireArgumentFromCPP(std::string argName, U value)
		{
			(*this->scriptEngine)["LuaCore"]["Lua_ReqList"][argName] = value;
		}

		template<typename U>
		inline void GameObject::sendQuery(U query)
		{
			if (Functions::Vector::isInList(localTriggers->getTrigger("Query"), registeredTriggers))
			{
				localTriggers->pushParameter("Query", std::to_string(queryCounter), query);
				localTriggers->setTriggerState("Query", true);
				queryCounter++;
			}
		}
	};
};