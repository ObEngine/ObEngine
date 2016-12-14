//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "GameObject.hpp"

namespace mse
{
	namespace Script
	{
		KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(useExternalTriggerProxy, GameObject, useExternalTrigger, 3, 4, 
			void(GameObject::*)(std::string, std::string, std::string, std::string));

		void loadScrGameObject(GameObject* obj, kaguya::State* lua)
		{
			(*lua)["CPP_Import"] = &loadLibBridge;
			(*lua)["CPP_Hook"] = &loadHookBridge;
			loadScrGameObjectLib(lua);
			(*lua)["This"] = obj;
		}

		void loadScrGameObjectLib(kaguya::State* lua)
		{
			(*lua)["CPP_GameObject"].setClass(kaguya::UserdataMetatable<GameObject>()
				.addFunction("LevelSprite", &GameObject::getLevelSprite)
				.addFunction("Collider", &GameObject::getCollider)
				.addFunction("Animator", &GameObject::getAnimator)
				.addFunction("canCollide", &GameObject::canCollide)
				.addFunction("canClick", &GameObject::canClick)
				.addFunction("canDisplay", &GameObject::canDisplay)
				.addFunction("delete", &GameObject::deleteObject)
				.addFunction("exec", &GameObject::exec)
				.addFunction("getID", &GameObject::getID)
				.addFunction("getInitialised", &GameObject::getInitialised)
				.addFunction("getPriority", &GameObject::getPriority)
				.addFunction("getPublicKey", &GameObject::getPublicKey)
				.addFunction("useLocalTrigger", &GameObject::useLocalTrigger)
				.addFunction("useExternalTrigger", useExternalTriggerProxy())
				.addOverloadedFunctions("sendQuery", 
					&GameObject::sendQuery<int>,
					&GameObject::sendQuery<float>,
					&GameObject::sendQuery<std::string>,
					&GameObject::sendQuery<bool>,
					&GameObject::sendQuery<std::vector<int>>,
					&GameObject::sendQuery<std::vector<float>>,
					&GameObject::sendQuery<std::vector<std::string>>,
					&GameObject::sendQuery<std::vector<bool>>,
					&GameObject::sendQuery<std::map<int, int>>,
					&GameObject::sendQuery<std::map<int, float>>,
					&GameObject::sendQuery<std::map<int, std::string>>,
					&GameObject::sendQuery<std::map<int, bool>>,
					&GameObject::sendQuery<std::map<std::string, int>>,
					&GameObject::sendQuery<std::map<std::string, float>>,
					&GameObject::sendQuery<std::map<std::string, std::string>>,
					&GameObject::sendQuery<std::map<std::string, bool>>
				)
				.addFunction("sendRequireArgument", &GameObject::sendRequireArgumentFromLua)
				.addFunction("setInitialised", &GameObject::setInitialised)
			);
		}

		void loadLibBridge(GameObject* object, std::string lib)
		{
			loadLib(object->getScriptEngine(), lib);
		}

		void loadHookBridge(GameObject* object, std::string hookname)
		{
			loadHook(object->getScriptEngine(), hookname);
		}

		bool orderScrPriority(GameObject* g1, GameObject* g2)
		{
			return (g1->getPriority() > g2->getPriority());
		}


		//GameObjectRequires
		GameObjectRequires* GameObjectRequires::instance = nullptr;
		GameObjectRequires* GameObjectRequires::getInstance()
		{
			if (!instance)
				instance = new GameObjectRequires();
			return instance;
		}
		Data::ComplexAttribute* GameObjectRequires::getRequiresForObjectType(std::string type)
		{
			if (!Functions::Vector::isInList(type, allRequires.getAllRootAttributes()))
			{
				Data::DataParser getGameObjectFile;
				System::Path("Data/GameObjects/").add(type).add(type + ".obj.msd").loadResource(&getGameObjectFile, System::Loaders::dataLoader);
				if (getGameObjectFile.containsRootAttribute("Requires"))
				{
					Data::ComplexAttribute* requiresData = getGameObjectFile.extractRootAttribute("Requires");
					requiresData->setID(type);
					allRequires.pushComplexAttribute(requiresData);
					return requiresData;
				}
				else
					return nullptr;
			}
			else
				return allRequires.getRootAttribute(type);
		}
		void GameObjectRequires::applyBaseRequires(GameObject* obj, Data::ComplexAttribute& requires) {
			for (std::string currentRequirement : requires.getAllComplexAttributes()) {
				std::cout << "Current Requirement : " << currentRequirement << std::endl;

			}
		}
		void GameObjectRequires::ApplyRequirements(GameObject* obj, Data::ComplexAttribute& requires)
		{
			for (std::string currentRequirement : requires.getAllAttributes()) {
				std::cout << "Current Requirement : " << currentRequirement << std::endl;
				//TODO : Expand to LIST / TABLE
				if (requires.getAttributeType(currentRequirement) == Data::Types::BaseAttribute) {
					if (requires.getBaseAttribute(currentRequirement)->getDataType() == "int") {
						(*obj->getScriptEngine())["LuaCore"]["Lua_ReqList"][currentRequirement] = requires.getBaseAttribute(currentRequirement)->get<int>();
					}
					else if (requires.getBaseAttribute(currentRequirement)->getDataType() == "string") {
						(*obj->getScriptEngine())["LuaCore"]["Lua_ReqList"][currentRequirement] = requires.getBaseAttribute(currentRequirement)->get<std::string>();
					}
					else if (requires.getBaseAttribute(currentRequirement)->getDataType() == "bool") {
						(*obj->getScriptEngine())["LuaCore"]["Lua_ReqList"][currentRequirement] = requires.getBaseAttribute(currentRequirement)->get<bool>();
					}
					else if (requires.getBaseAttribute(currentRequirement)->getDataType() == "float") {
						(*obj->getScriptEngine())["LuaCore"]["Lua_ReqList"][currentRequirement] = requires.getBaseAttribute(currentRequirement)->get<double>();
					}
				}
			}
		}

		//GameObject
		GameObject::GameObject(std::string type, std::string id) : objectCollider(id), objectLevelSprite(id)
		{
			this->type = type;
			this->id = id;
			objectLevelSprite.useDirtyAnimation(false, true);
		}
		void GameObject::registerTrigger(Trigger* trg)
		{
			this->registeredTriggers.push_back(trg);
		}
		void GameObject::loadGameObject(Data::ComplexAttribute* obj)
		{
			std::cout << "Currently Loading GameObject : " << id << std::endl;
			//Animator
			std::string animatorPath;
			if (obj->containsComplexAttribute("Animator"))
			{
				animatorPath = obj->at("Animator")->getBaseAttribute("path")->get<std::string>();
				if (animatorPath != "")
				{
					this->objectAnimator.attachRessourceManager(Animation::RessourceManager::GetInstance());
					this->objectAnimator.setPath(animatorPath);
					this->objectAnimator.loadAnimator();
				}
				hasAnimator = true;
			}
			//Collider
			if (obj->containsComplexAttribute("Collider"))
			{
				colliderSolid = obj->at("Collider")->getBaseAttribute("solid")->get<bool>();
				colliderClick = obj->at("Collider")->getBaseAttribute("click")->get<bool>();

				if (colliderSolid) objectCollider.addTag("Solid");
				int colliderPointSize;
				colliderPointSize = obj->at("Collider")->getListAttribute("polygonPoints")->getSize();
				for (int i = 0; i < colliderPointSize; i++)
				{
					std::string getPt = obj->at("Collider")->getListAttribute("polygonPoints")->getElement(i)->get<std::string>();
					std::vector<std::string> tPoint = Functions::String::split(getPt, ",");
					objectCollider.addPoint(std::stoi(tPoint[0]), std::stoi(tPoint[1]));
				}
				hasCollider = true;
			}
			//LevelSprite
			if (obj->containsComplexAttribute("LevelSprite"))
			{
				levelSpriteRelative = (obj->at("LevelSprite")->getBaseAttribute("position")->get<std::string>() == "relative") ? true : false;
				int decoRot = 0;
				int sprOffX = 0;
				int sprOffY = 0;
				double decoSca = 1.0;
				std::vector<std::string> decoAtrList;
				int layer;
				int zdepth;
				decoRot = obj->at("LevelSprite")->getBaseAttribute("rotation")->get<int>();
				decoSca = obj->at("LevelSprite")->getBaseAttribute("scale")->get<double>();
				layer = obj->at("LevelSprite")->getBaseAttribute("layer")->get<int>();
				zdepth = obj->at("LevelSprite")->getBaseAttribute("z-depth")->get<int>();
				if (obj->at("LevelSprite")->containsBaseAttribute("offsetX"))
					sprOffX = obj->at("LevelSprite")->getBaseAttribute("offsetX")->get<int>();
				if (obj->at("LevelSprite")->containsBaseAttribute("offsetY"))
					sprOffY = obj->at("LevelSprite")->getBaseAttribute("offsetY")->get<int>();
				if (obj->at("LevelSprite")->containsListAttribute("attributeList"))
				{
					int atrListSize = obj->getListAttribute("attributeList")->getSize();
					for (int j = 0; j < atrListSize; j++)
						decoAtrList.push_back(obj->at("LevelSprite")->getListAttribute("attributeList")->getElement(j)->get<std::string>());
				}
				objectLevelSprite.setRotation(decoRot);
				objectLevelSprite.setScale(decoSca, decoSca);
				objectLevelSprite.setAtr(decoAtrList);
				objectLevelSprite.setLayer(layer);
				objectLevelSprite.setZDepth(zdepth);
				objectLevelSprite.setOffset(sprOffX, sprOffY);
				hasLevelSprite = true;
			}
			//Script
			if (obj->containsComplexAttribute("Script"))
				if (obj->at("Script")->containsBaseAttribute("priority")) 
					scrPriority = obj->at("Script")->getBaseAttribute("priority")->get<int>();
		}
		void GameObject::hookLuaState(kaguya::State* lua)
		{
			this->scriptEngine = lua;
		}
		void GameObject::update(double dt)
		{
			if (updated)
			{
				for (int i = 0; i < registeredTriggers.size(); i++)
				{
					if (registeredTriggers[i]->getState())
					{
						std::string useGrp = registeredTriggers[i]->getGroup();
						for (int j = 0; j < registeredAliases.size(); j++)
						{
							std::string alNsp, alGrp, alRep;
							std::tie(alNsp, alGrp, alRep) = registeredAliases[j];
							if (alNsp == registeredTriggers[i]->getNamespace() && alGrp == registeredTriggers[i]->getGroup())
							{
								useGrp = alRep;
							}
						}
						std::string funcname = useGrp + "." + registeredTriggers[i]->getName();
						auto allParam = registeredTriggers[i]->getParameters();
						queryCounter = 0;
						(*this->scriptEngine)["cpp_param"] = kaguya::NewTable();
						(*this->scriptEngine)["cpp_param"]["dt"] = dt;
						for (auto it = allParam->begin(); it != allParam->end(); it++)
						{
							if (allParam->at(it->first).first == Functions::Type::getObjectType(int()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<int>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::string()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::string>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(bool()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<bool>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(float()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<float>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::vector<int>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::vector<int>>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::vector<float>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::vector<float>>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::vector<std::string>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::vector<std::string>>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::vector<bool>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::vector<bool>>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::map<int, int>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::map<int, int>>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::map<int, float>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::map<int, float>>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::map<int, bool>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::map<int, bool>>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::map<int, std::string>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::map<int, std::string>>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::map<std::string, int>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::map<std::string, int>>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::map<std::string, float>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::map<std::string, float>>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::map<std::string, bool>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::map<std::string, bool>>();
							else if (allParam->at(it->first).first == Functions::Type::getObjectType(std::map<std::string, std::string>()))
								(*this->scriptEngine)["cpp_param"][it->first] = allParam->at(it->first).second.as<std::map<std::string, std::string>>();
							else
								std::cout << "<Error:GameObject:GameObject>[update] Unknown Type for Parameter : " << it->first << "(" << allParam->at(it->first).first << ")" << std::endl;
						}

						if (funcname == "Local.Init") {
							std::cout << "INITIALISATION MIRROR INJECTION" << std::endl;
							this->scriptEngine->dostring("LuaCore.LocalInitMirrorInjector()");
						}
						else {
							this->scriptEngine->dostring("if type(" + funcname + ") == \"function\" then " + funcname + "(cpp_param) end");
						}
						(*this->scriptEngine)["cpp_param"] = nullptr;
					}
				}
				if (initialised)
				{
					if (hasAnimator)
						this->objectAnimator.update();
					if (hasLevelSprite)
						this->objectLevelSprite.setSprite(this->objectAnimator.getSprite());
				}
			}
		}
		std::string GameObject::getID()
		{
			return this->id;
		}
		std::string GameObject::getType()
		{
			return type;
		}
		std::string GameObject::getPublicKey()
		{
			return publicKey;
		}
		void GameObject::setAnimationKey(std::string key)
		{
			this->objectAnimator.setKey(key);
		}
		int GameObject::getPriority()
		{
			return scrPriority;
		}
		bool GameObject::canDisplay()
		{
			return (hasAnimator && hasLevelSprite);
		}
		bool GameObject::canCollide()
		{
			return (hasCollider && colliderSolid);
		}
		bool GameObject::canClick()
		{
			return (hasCollider && colliderClick);
		}
		bool GameObject::doesHaveCollider()
		{
			return hasCollider;
		}
		bool GameObject::doesHaveLevelSprite()
		{
			return hasLevelSprite;
		}
		bool GameObject::isLevelSpriteRelative()
		{
			return levelSpriteRelative;
		}
		bool GameObject::getUpdateState()
		{
			return this->updated;
		}
		void GameObject::setUpdateState(bool state)
		{
			this->updated = state;
		}
		Graphics::LevelSprite* GameObject::getLevelSprite()
		{
			return &objectLevelSprite;
		}
		Collision::PolygonalCollider* GameObject::getCollider()
		{
			if (hasCollider) return &objectCollider;
			else std::cout << "<Error:GameObject:GameObject>[getCollider] : GameObject " << id << " has no Collider" << std::endl;
		}
		Animation::Animator* GameObject::getAnimator()
		{
			return &objectAnimator;
		}
		kaguya::State* GameObject::getScriptEngine()
		{
			return this->scriptEngine;
		}
		TriggerGroup * GameObject::getLocalTriggers()
		{
			return localTriggers;
		}
		void GameObject::useLocalTrigger(std::string trName)
		{
			this->registerTrigger(TriggerDatabase::GetInstance()->getTrigger(this->privateKey, "Local", trName));
		}
		void GameObject::useExternalTrigger(std::string trNsp, std::string trGrp, std::string trName, std::string useAs)
		{
			if (trName == "*")
			{
				std::vector<std::string> allEv = TriggerDatabase::GetInstance()->getAllTriggersNameFromTriggerGroup(trNsp, trGrp);
				for (int i = 0; i < allEv.size(); i++) {
					this->registerTrigger(TriggerDatabase::GetInstance()->getTrigger(trNsp, trGrp, allEv[i]));
				}
			}
			else this->registerTrigger(TriggerDatabase::GetInstance()->getTrigger(trNsp, trGrp, trName));
			if (useAs != "") {
				this->registeredAliases.push_back(std::tuple<std::string, std::string, std::string>(trNsp, trGrp, useAs));
			}
		}

		void GameObject::setInitialised(bool init)
		{
			initialised = init;
		}

		bool GameObject::getInitialised()
		{
			return initialised;
		}

		void GameObject::exec(std::string query)
		{
			scriptEngine->dostring(query);
		}

		void GameObject::sendRequireArgumentFromLua(std::string argName, kaguya::LuaRef value)
		{
			(*this->scriptEngine)["LuaCore"]["Lua_ReqList"][argName] = value;
		}

		void GameObject::deleteObject()
		{
			this->deletable = true;
		}
	}
}