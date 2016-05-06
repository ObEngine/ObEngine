//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Script.hpp"

emorph::any::erasure::~erasure(){}
CoreHook hookCore;

void CoreHook::getValue(kaguya::State* lua, std::string name)
{
	if (containerMap.find(name) != containerMap.end())
	{
		std::string gt = containerMap[name].first;
		if      (gt == "Console*")            (*lua)["Hook"][name] = containerMap[name].second->as<Console*>();
		else if (gt == "Cursor*")			 (*lua)["Hook"][name] = containerMap[name].second->as<Cursor*>();
		else if (gt == "GameObjectHandler*")  (*lua)["Hook"][name] = containerMap[name].second->as<GameObjectHandler*>();
		else if (gt == "MathExp*")            (*lua)["Hook"][name] = containerMap[name].second->as<MathExp*>();
		else if (gt == "TextRenderer*")       (*lua)["Hook"][name] = containerMap[name].second->as<TextRenderer*>();
		else if (gt == "TriggerDatabase*")    (*lua)["Hook"][name] = containerMap[name].second->as<TriggerDatabase*>();
		else if (gt == "TriggerGroup*")       (*lua)["Hook"][name] = containerMap[name].second->as<TriggerGroup*>();
		else if (gt == "World*")              (*lua)["Hook"][name] = containerMap[name].second->as<World*>();
		else std::cout << "<Error:Script:CoreHook>[getValue] : Unknown type : '" << gt << "' for " << name << std::endl;
	}
	else
	{
		std::cout << "<Error:Script:CoreHook>[getValue] : Can't find Hook for : " << name << std::endl;
	}
}

emorph::any* CoreHook::getPointer(std::string name)
{
	if (containerMap.find(name) != containerMap.end())
	{
		return containerMap[name].second;
	}
	else
	{
		std::cout << "<Error:Script:CoreHook>[getPointer] : Can't find pointer of : " << name << std::endl;
	}
}

void loadLib(kaguya::State* lua, std::string lib)
{
	if (fn::String::occurencesInString(lib, ".") >= 1)
	{
		if (fn::String::split(lib, ".")[0] == "Core") loadCoreLib(lua, fn::Vector::getSubVector(fn::String::split(lib, "."), 1, 0));
	}
	else std::cout << "<Error:Script:*>[loadLib] : Please provide a namespace" << std::endl;
}

void loadHook(kaguya::State* lua, std::string hookname)
{
	hookCore.getValue(lua, hookname);
}

void loadCoreLib(kaguya::State* lua, std::vector<std::string> lib)
{
	std::vector<std::string> importedLibs = (*lua)["Core"]["ImportedLibs"];
	bool alreadyImported = false;
	for (int i = 0; i < importedLibs.size(); i++)
	{
		std::vector<std::string> cLibComp = fn::String::split(importedLibs[i], ".");
		if (lib == cLibComp)
		{
			alreadyImported = true;
			break;
		}
		else if (cLibComp.size() < lib.size())
		{
			bool sVecLibAF = true;
			for (int j = 0; j < cLibComp.size(); j++) { if (cLibComp[j] != lib[j]) sVecLibAF = false; }
			if (sVecLibAF) { alreadyImported = true; break; }
		}
	}
	if (!alreadyImported)
	{
		if        (lib[0] == "Animation")    CoreLib::loadAnimation(lua, lib);
		else if   (lib[0] == "Collision")    CoreLib::loadCollision(lua, lib);
		else if   (lib[0] == "Console")      CoreLib::loadConsole(lua, lib);
		else if   (lib[0] == "Cursor")		 CoreLib::loadCursor(lua, lib);
		else if   (lib[0] == "Dialog")       CoreLib::loadDialog(lua, lib);
		else if   (lib[0] == "LevelSprite")  CoreLib::loadLevelSprite(lua, lib);
		else if   (lib[0] == "Light")        CoreLib::loadLight(lua, lib);
		else if   (lib[0] == "MathExp")      CoreLib::loadMathExp(lua, lib);
		else if   (lib[0] == "Trigger")      CoreLib::loadTrigger(lua, lib);
		else if   (lib[0] == "Utils")        CoreLib::loadUtils(lua, lib);
		else if   (lib[0] == "World")        CoreLib::loadWorld(lua, lib);
		else
		{
			std::cout << "<Error:Script:*>[loadCoreLib] : Can't find Core.";
			for (int i = 0; i < lib.size(); i++)
			{
				if (i != lib.size() - 1) std::cout << lib[i] << ".";
				else std::cout << lib[i] << std::endl;
			}
		}
	}
	else
	{
		std::cout << "<Warning:Script:*>[loadCoreLib] : Core.";
		for (int i = 0; i < lib.size(); i++)
		{
			if (i != lib.size() - 1) std::cout << lib[i] << ".";
			else std::cout << lib[i];
		}
		std::cout << " is already loaded" << std::endl;
	}
}

void registerLib(kaguya::State* lua, std::string lib)
{
	std::string frag = std::string("table.insert(Core.ImportedLibs, ") + std::string("\"") + std::string(lib) + std::string("\")");
	(*lua)(frag);
}

void loadBaseLib(kaguya::State* lua)
{
	(*lua)["CPP_Import"] = &loadLib;
	(*lua)["CPP_Hook"] = &loadHook;
}

void CoreLib::loadAnimation(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["Animation"])) (*lua)["Core"]["Animation"] = kaguya::NewTable();
	if (importAll || args[1] == "AnimationGroup")
	{
		(*lua)["Core"]["Animation"]["AnimationGroup"].setClass(kaguya::ClassMetatable<anim::AnimationGroup>()
			.addMember("setGroupClock", &anim::AnimationGroup::setGroupClock)
			.addMember("setGroupLoop", &anim::AnimationGroup::setGroupLoop)
			.addMember("getGroupName", &anim::AnimationGroup::getGroupName)
			.addMember("getGroupClock", &anim::AnimationGroup::getGroupClock)
			.addMember("getGroupIndex", &anim::AnimationGroup::getGroupIndex)
			.addMember("isGroupOver", &anim::AnimationGroup::isGroupOver)
			.addMember("pushTexture", &anim::AnimationGroup::pushTexture)
			.addMember("removeTextureByIndex", &anim::AnimationGroup::removeTextureByIndex)
			.addMember("reset", &anim::AnimationGroup::reset)
			.addMember("next", &anim::AnimationGroup::next)
			.addMember("previous", &anim::AnimationGroup::previous)
			.addMember("forceNext", &anim::AnimationGroup::forceNext)
			.addMember("forcePrevious", &anim::AnimationGroup::forcePrevious)
		);
		foundPart = true;
	}
	if (importAll || args[1] == "Animation")
	{
		(*lua)["Core"]["Animation"]["Animation"].setClass(kaguya::ClassMetatable<anim::Animation>()
			.addMember("getAnimationName", &anim::Animation::getAnimationName)
			.addMember("getAnimationClock", &anim::Animation::getAnimationClock)
			.addMember("getAnimationGroup", &anim::Animation::getAnimationGroup)
			.addMember("getCurrentAnimationGroup", &anim::Animation::getCurrentAnimationGroup)
			.addMember("getAllAnimationGroupName", &anim::Animation::getAllAnimationGroupName)
			.addMember("getAnimationPlayMode", &anim::Animation::getAnimationPlayMode)
			.addMember("getAnimationStatus", &anim::Animation::getAnimationStatus)
			.addMember("isAnimationOver", &anim::Animation::isAnimationOver)
			.addMember("canSkipAnimation", &anim::Animation::canSkipAnimation)
			.addMember("getSpriteOffsetX", &anim::Animation::getSpriteOffsetX)
			.addMember("getSpriteOffsetY", &anim::Animation::getSpriteOffsetY)
			.addMember("getPriority", &anim::Animation::getPriority)
		);
		foundPart = true;
	}
	if (importAll || args[1] == "Animator")
	{
		(*lua)["Core"]["Animation"]["Animator"].setClass(kaguya::ClassMetatable<anim::Animator>()
			.addMember("setPath", &anim::Animator::setPath)
			.addMember("getAnimation", &anim::Animator::getAnimation)
			.addMember("getAllAnimationName", &anim::Animator::getAllAnimationName)
			.addMember("getKey", &anim::Animator::getKey)
			.addMember("setKey", &anim::Animator::setKey)
			.addMember("textureChanged", &anim::Animator::textureChanged)
			.addMember("getSpriteOffsetX", &anim::Animator::getSpriteOffsetX)
			.addMember("getSpriteOffsetY", &anim::Animator::getSpriteOffsetY)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadConsole] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}
void CoreLib::loadCollision(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["Collision"])) (*lua)["Core"]["Collision"] = kaguya::NewTable();
	if (importAll || args[1] == "PolygonalCollider")
	{
		(*lua)["Core"]["Collision"]["PolygonalCollider"].setClass(kaguya::ClassMetatable<Collision::PolygonalCollider>()
			.addMember("addPoint", &Collision::PolygonalCollider::addPoint)
			.addMember("clearHighlights", &Collision::PolygonalCollider::clearHighlights)
			.addMember("deletePoint", &Collision::PolygonalCollider::deletePoint)
			.addMember("doesCollide", &Collision::PolygonalCollider::doesCollide)
			.addMember("findClosestNode", &Collision::PolygonalCollider::findClosestNode)
			.addMember("getID", &Collision::PolygonalCollider::getID)
			.addMember("getMasterPointCoordinates", &Collision::PolygonalCollider::getMasterPointCoordinates)
			.addMember("getNodeDistance", &Collision::PolygonalCollider::getNodeDistance)
			.addMember("getPath", &Collision::PolygonalCollider::getPath)
			.addMember("getPointCoordinates", &Collision::PolygonalCollider::getPointCoordinates)
			.addMember("getPointsAmount", &Collision::PolygonalCollider::getPointsAmount)
			.addMember("getSelected", &Collision::PolygonalCollider::getSelected)
			.addMember("getSideAngle", &Collision::PolygonalCollider::getSideAngle)
			.addMember("getSideContainingPoint", &Collision::PolygonalCollider::getSideContainingPoint)
			.addMember("getSideLength", &Collision::PolygonalCollider::getSideLength)
			.addMember("getSidesAmount", &Collision::PolygonalCollider::getSidesAmount)
			.addMember("getSolid", &Collision::PolygonalCollider::getSolid)
			.addMember("getSortedNodesByDistance", &Collision::PolygonalCollider::getSortedNodesByDistance)
			.addMember("hasMasterPoint", &Collision::PolygonalCollider::hasMasterPoint)
			.addMember("hasPoint", &Collision::PolygonalCollider::hasPoint)
			.addMember("highlightLine", &Collision::PolygonalCollider::highlightLine)
			.addMember("highlightPoint", &Collision::PolygonalCollider::highlightPoint)
			.addMember("isPointInBoundingBox", &Collision::PolygonalCollider::isPointInBoundingBox)
			.addMember("move", &Collision::PolygonalCollider::move)
			.addMember("movePoint", &Collision::PolygonalCollider::movePoint)
			.addMember("setDrawOffset", &Collision::PolygonalCollider::setDrawOffset)
			.addMember("setPointPosition", &Collision::PolygonalCollider::setPointPosition)
			.addMember("setPointRelativePosition", &Collision::PolygonalCollider::setPointRelativePosition)
			.addMember("setPointPositionFromMaster", &Collision::PolygonalCollider::setPointPositionFromMaster)
			.addMember("setPosition", &Collision::PolygonalCollider::setPosition)
			.addMember("setPositionFromMaster", &Collision::PolygonalCollider::setPositionFromMaster)
			.addMember("setSelected", &Collision::PolygonalCollider::setSelected)
			.addMember("setSolid", &Collision::PolygonalCollider::setSolid)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadCollision] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}
void CoreLib::loadConsole(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["Console"])) (*lua)["Core"]["Console"] = kaguya::NewTable();
	if (importAll || args[1] == "Console")
	{
		(*lua)["Core"]["Console"]["Console"].setClass(kaguya::ClassMetatable<Console>()
			.addMember("getCommand", &Console::getCommand)
			.addMember("hasCommand", &Console::hasCommand)
			.addMember("scroll", &Console::scroll)
			.addMember("getInputBuffer", &Console::getInputBuffer)
			.addMember("createStream", &Console::createStream)
			.addMember("isConsoleVisible", &Console::isConsoleVisible)
			.addMember("setConsoleVisibility", &Console::setConsoleVisibility)
		);
		foundPart = true;
	}
	if (importAll || args[1] == "Stream")
	{
		(*lua)["Core"]["Console"]["Stream"].setClass(kaguya::ClassMetatable<Console::Stream>()
			.addMember("write", static_cast<Console::Message* (Console::Stream::*)(std::string)>(&Console::Stream::streamPush))
			.addMember("write", static_cast<Console::Message* (Console::Stream::*)(std::string, int, int, int, int)>(&Console::Stream::streamPush))
			.addMember("setColor", &Console::Stream::setColor)
			.addMember("getR", &Console::Stream::getR)
			.addMember("getG", &Console::Stream::getG)
			.addMember("getB", &Console::Stream::getB)
			.addMember("getA", &Console::Stream::getA)
		);
		foundPart = true;
	}
	if (importAll || args[1] == "Message")
	{
		(*lua)["Core"]["Console"]["Message"].setClass(kaguya::ClassMetatable<Console::Message>()
			.addMember("getFormattedMessage", &Console::Message::getFormatedMessage)
			.addMember("getHeader", &Console::Message::getHeader)
			.addMember("getMessage", &Console::Message::getMessage)
			.addMember("getR", &Console::Message::getR)
			.addMember("getG", &Console::Message::getG)
			.addMember("getB", &Console::Message::getB)
			.addMember("getA", &Console::Message::getA)
			.addMember("getType", &Console::Message::getType)
			.addMember("setMessage", &Console::Message::setMessage)
			.addMember("setColor", &Console::Message::setColor)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadConsole] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}
void CoreLib::loadCursor(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["Cursor"])) (*lua)["Core"]["Cursor"] = kaguya::NewTable();
	if (importAll || args[1] == "Cursor")
	{
		(*lua)["Core"]["Cursor"]["Cursor"].setClass(kaguya::ClassMetatable<Cursor>()
			.addMember("getClicked", &Cursor::getClicked)
			.addMember("getPressed", &Cursor::getPressed)
			.addMember("getReleased", &Cursor::getReleased)
			.addMember("getX", &Cursor::getX)
			.addMember("getY", &Cursor::getY)
			.addMember("selectCursor", &Cursor::selectCursor)
			.addMember("selectKey", &Cursor::selectKey)
			.addMember("setPosition", &Cursor::setPosition)
			.addMember("setX", &Cursor::setX)
			.addMember("setY", &Cursor::setY)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadCursor] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}
void CoreLib::loadDialog(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["Dialog"])) (*lua)["Core"]["Dialog"] = kaguya::NewTable();
	if (importAll || args[1] == "TextRenderer")
	{
		(*lua)["Core"]["Dialog"]["TextRenderer"].setClass(kaguya::ClassMetatable<TextRenderer>()
			.addMember("createRenderer", &TextRenderer::createRenderer)
			.addMember("sendToRenderer", &TextRenderer::sendToRenderer)
			.addMember("textRemaining", &TextRenderer::textRemaining)
			.addMember("next", &TextRenderer::next)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadDialog] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}
void CoreLib::loadLevelSprite(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["LevelSprite"])) (*lua)["Core"]["LevelSprite"] = kaguya::NewTable();
	if (importAll || args[1] == "LevelSprite")
	{
		(*lua)["Core"]["LevelSprite"]["LevelSprite"].setClass(kaguya::ClassMetatable<LevelSprite>()
			.addMember("addAtr", &LevelSprite::addAtr)
			.addMember("addRotation", &LevelSprite::addRotation)
			.addMember("calculateRealCoordinates", &LevelSprite::calculateRealCoordinates)
			.addMember("getAttributes", &LevelSprite::getAttributes)
			.addMember("getH", &LevelSprite::getH)
			.addMember("getW", &LevelSprite::getW)
			.addMember("getID", &LevelSprite::getID)
			.addMember("getLayer", &LevelSprite::getLayer)
			.addMember("getName", &LevelSprite::getName)
			.addMember("getRect", &LevelSprite::getRect)
			.addMember("getRotation", &LevelSprite::getRotation)
			.addMember("getScale", &LevelSprite::getScale)
			.addMember("getX", &LevelSprite::getX)
			.addMember("getY", &LevelSprite::getY)
			.addMember("getZDepth", &LevelSprite::getZDepth)
			.addMember("isDrawable", &LevelSprite::isDrawable)
			.addMember("move", &LevelSprite::move)
			.addMember("removeAtrByIndex", &LevelSprite::removeAtrByIndex)
			.addMember("removeAtrByName", &LevelSprite::removeAtrByName)
			.addMember("setAtr", &LevelSprite::setAtr)
			.addMember("setLayer", &LevelSprite::setLayer)
			.addMember("setPosition", &LevelSprite::setPosition)
			.addMember("setRotation", &LevelSprite::setRotation)
			.addMember("setRotationOrigin", &LevelSprite::setRotationOrigin)
			.addMember("setScale", &LevelSprite::setScale)
			.addMember("setTranslationOrigin", &LevelSprite::setTranslationOrigin)
			.addMember("setZDepth", &LevelSprite::setZDepth)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadLevelSprite] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}
void CoreLib::loadLight(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["Light"])) (*lua)["Core"]["Light"] = kaguya::NewTable();
	if (importAll || args[1] == "PointLight")
	{
		(*lua)["Core"]["Light"]["PointLight"].setClass(kaguya::ClassMetatable<Light::PointLight>()
			.addConstructor<std::string, int, int, int, int, double, int, int, int, int, bool>()
			.addMember("setPosition", &Light::PointLight::setPosition)
			.addMember("move", &Light::PointLight::move)
			.addMember("setOffset", &Light::PointLight::setOffset)
			.addMember("setSize", &Light::PointLight::setSize)
			.addMember("scale", &Light::PointLight::scale)
			.addMember("setColor", &Light::PointLight::setColor)
			.addMember("addColor", &Light::PointLight::addColor)
			.addMember("subColor", &Light::PointLight::subColor)
			.addMember("blendColor", &Light::PointLight::blendColor)
			.addMember("setBehind", &Light::PointLight::setBehind)
			.addMember("show", &Light::PointLight::show)
			.addMember("hide", &Light::PointLight::hide)
			.addMember("setVisible", &Light::PointLight::setVisible)
			.addMember("isVisible", &Light::PointLight::isVisible)
			.addMember("getX", &Light::PointLight::getX)
			.addMember("getY", &Light::PointLight::getX)
			.addMember("getSize", &Light::PointLight::getSize)
			.addMember("getR", &Light::PointLight::getR)
			.addMember("getG", &Light::PointLight::getG)
			.addMember("getB", &Light::PointLight::getB)
			.addMember("getA", &Light::PointLight::getA)
			.addMember("isBehind", &Light::PointLight::isBehind)
			.addMember("getType", &Light::PointLight::getType)
		);
		foundPart = true;
	}
	if (importAll || args[1] == "DynamicPointLight")
	{
		(*lua)["Core"]["Light"]["DynamicPointLight"].setClass(kaguya::ClassMetatable<Light::DynamicPointLight, kaguya::MultipleBase<Light::PointLight, MathExpObject>>()
			.addConstructor<std::string, int, int, double>()
			.addMember("setSizeExp", &Light::DynamicPointLight::setSizeExp)
			.addMember("setRExp", &Light::DynamicPointLight::setRExp)
			.addMember("setGExp", &Light::DynamicPointLight::setGExp)
			.addMember("setBExp", &Light::DynamicPointLight::setBExp)
			.addMember("setAExp", &Light::DynamicPointLight::setAExp)
			.addMember("setOffsetXExp", &Light::DynamicPointLight::setOffsetXExp)
			.addMember("setOffsetYExp", &Light::DynamicPointLight::setOffsetYExp)
			.addMember("getType", &Light::DynamicPointLight::getType)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadLight] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}
void CoreLib::loadMathExp(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["MathExp"])) (*lua)["Core"]["MathExp"] = kaguya::NewTable();
	if (importAll || args[1] == "MathExp")
	{
		(*lua)["Core"]["MathExp"]["MathExp"].setClass(kaguya::ClassMetatable<MathExp>()
			.addConstructor<std::string, bool>()
			.addConstructor<int, std::string, bool>()
			.addMember("buildMathExp", &MathExp::buildMathExp)
			.addMember("getResult", &MathExp::getResult)
			.addMember("isStatic", &MathExp::isStatic)
			.addMember("setVar", &MathExp::setVar)
			.addMember("setExpr", &MathExp::setExpr)
		);
		foundPart = true;
	}
	if (importAll || args[1] == "MathExpObject")
	{
		(*lua)["Core"]["MathExp"]["MathExpObject"].setClass(kaguya::ClassMetatable<MathExpObject>()
			.addConstructor<double>()
			.addConstructor<double, std::string, std::string>()
			.addMember("processAllExp", &MathExpObject::processAllExp)
			.addMember("registerMathExp", &MathExpObject::registerMathExp)
			.addMember("registerOutputVar", &MathExpObject::registerOutputVar)
			.addMember("setGlobalVar", &MathExpObject::setGlobalVar)
			.addMember("setLocalVar", &MathExpObject::setLocalVar)
			.addMember("setPrecision", &MathExpObject::setPrecision)
			.addMember("getPrecision", &MathExpObject::getPrecision)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadMathExp] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}
void CoreLib::loadTrigger(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["Trigger"])) (*lua)["Core"]["Trigger"] = kaguya::NewTable();
	if (importAll || args[1] == "TriggerDatabase")
	{
		(*lua)["Core"]["Trigger"]["TriggerDatabase"].setClass(kaguya::ClassMetatable<TriggerDatabase>()
			.addMember("getTrigger", &TriggerDatabase::getTrigger)
			.addMember("getCustomTrigger", &TriggerDatabase::getCustomTrigger)
			.addMember("createTriggerGroup", &TriggerDatabase::createTriggerGroup)
			.addMember("joinTriggerGroup", &TriggerDatabase::joinTriggerGroup)
			.addMember("doesTriggerGroupExists", &TriggerDatabase::doesTriggerGroupExists)
		);
		foundPart = true;
	}
	if (importAll || args[1] == "TriggerGroup")
	{
		(*lua)["Core"]["Trigger"]["TriggerGroup"].setClass(kaguya::ClassMetatable<TriggerGroup>()
			.addMember("getTrigger", &TriggerGroup::getTrigger)
			.addMember("addTrigger", &TriggerGroup::addTrigger)
			.addMember("delayTriggerState", &TriggerGroup::delayTriggerState)
			.addMember("enableTrigger", &TriggerGroup::enableTrigger)
			.addMember("disableTrigger", &TriggerGroup::disableTrigger)
			.addMember("setTriggerState", &TriggerGroup::setTriggerState)
			.addMember("getState", &TriggerGroup::getState)
			.addMember("setPermanent", &TriggerGroup::setPermanent)
			.addMember("getAllTriggersName", &TriggerGroup::getAllTriggersName)
			.addMember("getAllTriggers", &TriggerGroup::getAllTriggers)
			.addMember("pushParameter", &TriggerGroup::pushParameter<int>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<float>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::string>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<bool>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::map<int, int>>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::map<int, float>>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::map<int, std::string>>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::map<int, bool>>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::map<std::string, int>>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::map<std::string, float>>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::map<std::string, std::string>>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::map<std::string, bool>>)
		);
		foundPart = true;
	}
	if (importAll || args[1] == "Trigger")
	{
		(*lua)["Core"]["Trigger"]["Trigger"].setClass(kaguya::ClassMetatable<Trigger>()
			.addMember("getState", &Trigger::getState)
			.addMember("isPermanent", &Trigger::isPermanent)
			.addMember("getGroup", &Trigger::getGroup)
			.addMember("getName", &Trigger::getName)
			.addMember("getNamespace", &Trigger::getNamespace)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadTrigger] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}
void CoreLib::loadUtils(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["Utils"])) (*lua)["Core"]["Utils"] = kaguya::NewTable();
	if (importAll || args[1] == "File")
	{
		if (!(bool)((*lua)["Core"]["Utils"]["File"])) (*lua)["Core"]["Utils"]["File"] = kaguya::NewTable();
		(*lua)["Core"]["Utils"]["File"]["listDirInDir"] = kaguya::function(fn::File::listDirInDir);
		(*lua)["Core"]["Utils"]["File"]["listFileInDir"] = kaguya::function(fn::File::listFileInDir);
		foundPart = true;
	}
	if (importAll || args[1] == "Math")
	{
		if (!(bool)((*lua)["Core"]["Utils"]["Math"])) (*lua)["Core"]["Utils"]["Math"] = kaguya::NewTable();
		(*lua)["Core"]["Utils"]["Math"]["randint"] = kaguya::function(fn::Math::randint);
		(*lua)["Core"]["Utils"]["Math"]["randfloat"] = kaguya::function(fn::Math::randfloat);
		(*lua)["Core"]["Utils"]["Math"]["getMin"] = kaguya::function(fn::Math::getMin<double>);
		(*lua)["Core"]["Utils"]["Math"]["getMax"] = kaguya::function(fn::Math::getMax<double>);
		(*lua)["Core"]["Utils"]["Math"]["isBetween"] = kaguya::function(fn::Math::isBetween<double>);
		(*lua)["Core"]["Utils"]["Math"]["isDoubleInt"] = kaguya::function(fn::Math::isDoubleInt);
		foundPart = true;
	}
	//Add Others
}
void CoreLib::loadWorld(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["World"])) (*lua)["Core"]["World"] = kaguya::NewTable();
	if (importAll)
	{
		(*lua)["Core"]["World"]["World"].setClass(kaguya::ClassMetatable<World>()
			.addMember("addCharacter", &World::addCharacter)
			.addMember("addLevelSprite", &World::addLevelSprite)
			.addMember("addLight", &World::addLight)
			.addMember("loadFromFile", &World::loadFromFile)
			.addMember("getCamX", &World::getCamX)
			.addMember("getCamY", &World::getCamY)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadWorld] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}