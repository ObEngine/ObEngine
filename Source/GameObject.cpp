//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "GameObject.hpp"

GameObject* mainGameObject;

void loadScrGameObject(GameObject* obj, kaguya::State* lua)
{
	(*lua)["CPP_Import"] = &loadLibBridge;
	(*lua)["CPP_Hook"] = &loadHookBridge;
	loadScrGameObjectLib(lua);
	(*lua)["This"] = obj;
}

void loadScrGameObjectLib(kaguya::State* lua)
{
	(*lua)["CPP_GameObject"].setClass(kaguya::ClassMetatable<GameObject>()
		.addMember("LevelSprite", &GameObject::getLevelSprite)
		.addMember("Collider", &GameObject::getCollider)
		.addMember("Animator", &GameObject::getAnimator)
		.addMember("canCollide", &GameObject::canCollide)
		.addMember("canClick", &GameObject::canClick)
		.addMember("canDisplay", &GameObject::canDisplay)
		.addMember("delete", &GameObject::deleteObject)
		.addMember("getID", &GameObject::getID)
		.addMember("getInitialised", &GameObject::getInitialised)
		.addMember("getPriority", &GameObject::getPriority)
		.addMember("getPublicKey", &GameObject::getPublicKey)
		.addMember("useLocalTrigger", &GameObject::useLocalTrigger)
		.addMember("useExternalTrigger", &GameObject::useExternalTrigger)
		.addMember("sendQuery", &GameObject::sendQuery<int>)
		.addMember("sendQuery", &GameObject::sendQuery<float>)
		.addMember("sendQuery", &GameObject::sendQuery<std::string>)
		.addMember("sendQuery", &GameObject::sendQuery<bool>)
		.addMember("sendQuery", &GameObject::sendQuery<std::vector<int>>)
		.addMember("sendQuery", &GameObject::sendQuery<std::vector<float>>)
		.addMember("sendQuery", &GameObject::sendQuery<std::vector<std::string>>)
		.addMember("sendQuery", &GameObject::sendQuery<std::vector<bool>>)
		.addMember("sendQuery", &GameObject::sendQuery<std::map<int, int>>)
		.addMember("sendQuery", &GameObject::sendQuery<std::map<int, float>>)
		.addMember("sendQuery", &GameObject::sendQuery<std::map<int, std::string>>)
		.addMember("sendQuery", &GameObject::sendQuery<std::map<int, bool>>)
		.addMember("sendQuery", &GameObject::sendQuery<std::map<std::string, int>>)
		.addMember("sendQuery", &GameObject::sendQuery<std::map<std::string, float>>)
		.addMember("sendQuery", &GameObject::sendQuery<std::map<std::string, std::string>>)
		.addMember("sendQuery", &GameObject::sendQuery<std::map<std::string, bool>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<int>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<float>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::string>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<bool>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::vector<int>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::vector<float>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::vector<std::string>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::vector<bool>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::map<int, int>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::map<int, float>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::map<int, std::string>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::map<int, bool>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::map<std::string, int>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::map<std::string, float>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::map<std::string, std::string>>)
		.addMember("sendRequireArgument", &GameObject::sendRequireArgument<std::map<std::string, bool>>)
		.addMember("setInitialised", &GameObject::setInitialised)
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
void GameObject::loadGameObject(DataObject* obj)
{
	std::cout << "Currently Loading GameObject : " << id << std::endl;
	//Animator
	std::string animatorPath;
	if (obj->complexExists(convertPath(""), "Animator"))
	{
		obj->getAttribute(convertPath("Animator"), "path")->getData(&animatorPath);
		this->objectAnimator.setPath(animatorPath);
		this->objectAnimator.loadAnimator();
		hasAnimator = true;
	}
	//Collider
	if (obj->complexExists(convertPath(""), "Collider"))
	{
		obj->getAttribute(convertPath("Collider"), "solid")->getData(&colliderSolid);
		obj->getAttribute(convertPath("Collider"), "click")->getData(&colliderClick);

		objectCollider.setSolid(colliderSolid);
		int colliderPointSize;
		colliderPointSize = obj->getListAttribute(convertPath("Collider"), "polygonPoints")->getSize();
		for (int i = 0; i < colliderPointSize; i++)
		{
			std::string getPt;
			obj->getListAttribute(convertPath("Collider"), "polygonPoints")->getElement(i)->getData(&getPt);
			std::vector<std::string> tPoint = fn::String::split(getPt, ",");
			objectCollider.addPoint(std::stoi(tPoint[0]), std::stoi(tPoint[1]));
		}
		hasCollider = true;
	}
	//LevelSprite
	if (obj->complexExists(convertPath(""), "LevelSprite"))
	{
		std::string sprRel;
		levelSpriteRelative = (obj->getAttribute(convertPath("LevelSprite"), "position")->getData(&sprRel) == "relative") ? true : false;
		int decoRot = 0;
		int sprOffX = 0;
		int sprOffY = 0;
		double decoSca = 1.0;
		std::vector<std::string> decoAtrList;
		std::string attrBuffer;
		int layer;
		int zdepth;
		obj->getAttribute(convertPath("LevelSprite"), "rotation")->getData(&decoRot);
		obj->getAttribute(convertPath("LevelSprite"), "scale")->getData(&decoSca);
		obj->getAttribute(convertPath("LevelSprite"), "layer")->getData(&layer);
		obj->getAttribute(convertPath("LevelSprite"), "z-depth")->getData(&zdepth);
		if (obj->attributeExists(convertPath("LevelSprite"), "offsetX"))
			obj->getAttribute(convertPath("LevelSprite"), "offsetX")->getData(&sprOffX);
		if (obj->attributeExists(convertPath("LevelSprite"), "offsetY"))
			obj->getAttribute(convertPath("LevelSprite"), "offsetY")->getData(&sprOffY);
		if (obj->listExists(convertPath("LevelSprite"), "attributeList"))
		{
			int atrListSize = obj->getListAttribute(convertPath("LevelSprite"), "attributeList")->getSize();
			for (int j = 0; j < atrListSize; j++)
				decoAtrList.push_back(obj->getListAttribute(convertPath("LevelSprite"), "attributeList")->getElement(j)->getData(&attrBuffer));
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
	if (obj->complexExists(convertPath(""), "Script"))
	{
		if (obj->attributeExists(convertPath("Script"), "priority")) obj->getAttribute(convertPath("Script"), "priority")->getData(&scrPriority);
	}
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
				for (auto it = allParam.begin(); it != allParam.end(); it++)
				{
					if (allParam[it->first].first == "int")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<int>();
					else if (allParam[it->first].first == "std::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::string>();
					else if (allParam[it->first].first == "bool")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<bool>();
					else if (allParam[it->first].first == "float")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<float>();
					else if (allParam[it->first].first == "std::vector<bool,classstd::allocator<int>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::vector<int>>();
					else if (allParam[it->first].first == "std::vector<bool,classstd::allocator<float>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::vector<float>>();
					else if (allParam[it->first].first == "std::vector<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>,"
						"classstd::allocator<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::vector<std::string>>();
					else if (allParam[it->first].first == "std::vector<bool,classstd::allocator<bool>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::vector<bool>>();
					else if (allParam[it->first].first == "std::map<int,int,structstd::less<int>,classstd::allocator<structstd::pair<intconst,int>>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::map<int, int>>();
					else if (allParam[it->first].first == "std::map<int,float,structstd::less<int>,classstd::allocator<structstd::pair<intconst,float>>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::map<int, float>>();
					else if (allParam[it->first].first == "std::map<int,bool,structstd::less<int>,classstd::allocator<structstd::pair<intconst,float>>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::map<int, float>>();
					else if (allParam[it->first].first == "std::map<int,classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>,"
						"structstd::less<int>,classstd::allocator<structstd::pair<intconst,classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>>>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::map<int, std::string>>();
					else if (allParam[it->first].first == "std::map<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>,"
						"int,structstd::less<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>>,"
						"classstd::allocator<structstd::pair<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>const,int>>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::map<std::string, int>>();
					else if (allParam[it->first].first == "std::map<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>,"
						"float,structstd::less<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>>,"
						"classstd::allocator<structstd::pair<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>const,float>>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::map<std::string, float>>();
					else if (allParam[it->first].first == "std::map<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>,"
						"bool,structstd::less<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>>,"
						"classstd::allocator<structstd::pair<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>const,bool>>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::map<std::string, bool>>();
					else if (allParam[it->first].first == "std::map<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>,"
						"classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>,"
						"structstd::less<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>>,"
						"classstd::allocator<structstd::pair<classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>const,"
						"classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char>>>>>")
						(*this->scriptEngine)["cpp_param"][it->first] = allParam[it->first].second->as<std::map<std::string, std::string>>();
					else
						std::cout << "<Error:GameObject:GameObject>[update] Unknown Type for Parameter : " << it->first << "(" << allParam[it->first].first << ")" << std::endl;

				}
				this->scriptEngine->dostring("if type(" + funcname + ") == \"function\" then " + funcname + "(cpp_param) end");
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
	std::cout << "@@Setting State : " << state << std::endl;
	this->updated = state;
}
LevelSprite* GameObject::getLevelSprite()
{
	return &objectLevelSprite;
}
Collision::PolygonalCollider* GameObject::getCollider()
{
	if (hasCollider) return &objectCollider;
	else std::cout << "<Error:GameObject:GameObject>[getCollider] : GameObject " << id << " has no Collider" << std::endl;
}
anim::Animator* GameObject::getAnimator()
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
	this->registerTrigger(triggerDatabaseCore.getTrigger(this->privateKey, "Local", trName));
}
void GameObject::useExternalTrigger(std::string trNsp, std::string trGrp, std::string trName, std::string useAs)
{
	if (trName == "*")
	{
		std::vector<std::string> allEv = triggerDatabaseCore.getAllTriggersNameFromTriggerGroup(trNsp, trGrp);
		for (int i = 0; i < allEv.size(); i++)
		{
			this->registerTrigger(triggerDatabaseCore.getTrigger(trNsp, trGrp, allEv[i]));
		}
	}
	else this->registerTrigger(triggerDatabaseCore.getTrigger(trNsp, trGrp, trName));
	if (useAs != "")
	{
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

void GameObject::deleteObject()
{
	this->deletable = true;
}
