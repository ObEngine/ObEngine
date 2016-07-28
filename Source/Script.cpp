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
		if (gt == "Console*")                 (*lua)["Hook"][name] = containerMap[name].second->as<Console*>();
		else if (gt == "Cursor*")			  (*lua)["Hook"][name] = containerMap[name].second->as<Cursor*>();
		else if (gt == "GUI::Container*")     (*lua)["Hook"][name] = containerMap[name].second->as<GUI::Container*>();
		else if (gt == "KeyBinder*")          (*lua)["Hook"][name] = containerMap[name].second->as<KeyBinder*>();
		else if (gt == "MathExp*")            (*lua)["Hook"][name] = containerMap[name].second->as<MathExp*>();
		else if (gt == "Serial*")             (*lua)["Hook"][name] = containerMap[name].second->as<Serial*>();
		else if (gt == "TextRenderer*")       (*lua)["Hook"][name] = containerMap[name].second->as<TextRenderer*>();
		else if (gt == "TriggerDatabase*")    (*lua)["Hook"][name] = containerMap[name].second->as<TriggerDatabase*>();
		else if (gt == "TriggerGroup*")       (*lua)["Hook"][name] = containerMap[name].second->as<TriggerGroup*>();
		//else if (gt == "World*")              (*lua)["Hook"][name] = containerMap[name].second->as<World*>();
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
			if (cLibComp.size() > 0)
			{
				for (int j = 0; j < cLibComp.size(); j++)
					if (cLibComp[j] != lib[j]) { sVecLibAF = false; }
			}
			else
				sVecLibAF = false;
			if (sVecLibAF) { alreadyImported = true; break; }
		}
	}
	if (!alreadyImported)
	{
		bool all = lib[0] == "*";
		if (all) { lib.clear(); lib.push_back("*"); }
		bool found = false;
		if (lib[0] == "Animation" || all)        { CoreLib::loadAnimation(lua,   (all) ? std::vector<std::string>{"Animation"}   : lib);    found = true; }
		if   (lib[0] == "Collision" || all)      { CoreLib::loadCollision(lua,   (all) ? std::vector<std::string>{"Collision"}   : lib);    found = true; }
		if   (lib[0] == "Console" || all)        { CoreLib::loadConsole(lua,     (all) ? std::vector<std::string>{"Console"}     : lib);    found = true; }
		if   (lib[0] == "Constants" || all)      { CoreLib::loadConstants(lua,   (all) ? std::vector<std::string>{"Constants"}   : lib);    found = true; }
		if   (lib[0] == "Cursor" || all)         { CoreLib::loadCursor(lua,      (all) ? std::vector<std::string>{"Cursor"}      : lib);    found = true; }
		if   (lib[0] == "Dialog" || all)         { CoreLib::loadDialog(lua,      (all) ? std::vector<std::string>{"Dialog"}      : lib);    found = true; }
		if   (lib[0] == "Entity" || all)         { CoreLib::loadEntity(lua,      (all) ? std::vector<std::string>{"Entity"}      : lib);    found = true; }
		if   (lib[0] == "GUI" || all)            { CoreLib::loadGUI(lua,         (all) ? std::vector<std::string>{"GUI"}         : lib);    found = true; }
		if   (lib[0] == "KeyBind" || all)        { CoreLib::loadKeyBind(lua,     (all) ? std::vector<std::string>{"KeyBind"}     : lib);    found = true; }
		if   (lib[0] == "LevelSprite" || all)    { CoreLib::loadLevelSprite(lua, (all) ? std::vector<std::string>{"LevelSprite"} : lib);    found = true; }
		if   (lib[0] == "Light" || all)          { CoreLib::loadLight(lua,       (all) ? std::vector<std::string>{"Light"}       : lib);    found = true; }
		if   (lib[0] == "MathExp" || all)        { CoreLib::loadMathExp(lua,     (all) ? std::vector<std::string>{"MathExp"}     : lib);    found = true; }
		if   (lib[0] == "Serial" || all)         { CoreLib::loadSerial(lua,      (all) ? std::vector<std::string>{"Serial"}      : lib);    found = true; }
		if	 (lib[0] == "SFML" || all)		     { CoreLib::loadSFML(lua,        (all) ? std::vector<std::string>{"SFML"}        : lib);    found = true; }
		if   (lib[0] == "STD" || all)            { CoreLib::loadSTD(lua,         (all) ? std::vector<std::string>{"STD"}         : lib);    found = true; }
		if   (lib[0] == "Trigger" || all)        { CoreLib::loadTrigger(lua,     (all) ? std::vector<std::string>{"Trigger"}     : lib);    found = true; }
		if   (lib[0] == "Utils" || all)          { CoreLib::loadUtils(lua,       (all) ? std::vector<std::string>{"Utils"}       : lib);    found = true; }
		if (!found)
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
			.addConstructor<std::string>()
			.addMember("addPoint", &Collision::PolygonalCollider::addPoint)
			.addMember("clearHighlights", &Collision::PolygonalCollider::clearHighlights)
			.addMember("deletePoint", &Collision::PolygonalCollider::deletePoint)
			.addMember("doesCollide", &Collision::PolygonalCollider::doesCollide)
			.addMember("doesPathCollide", &Collision::PolygonalCollider::doesPathCollide)
			.addMember("findClosestPoint", &Collision::PolygonalCollider::findClosestPoint)
			.addMember("getDistanceFromPoint", &Collision::PolygonalCollider::getDistanceFromPoint)
			.addMember("getID", &Collision::PolygonalCollider::getID)
			.addMember("getMasterPointCoordinates", &Collision::PolygonalCollider::getMasterPointCoordinates)
			.addMember("getPath", &Collision::PolygonalCollider::getPath)
			.addMember("getPointCoordinates", &Collision::PolygonalCollider::getPointCoordinates)
			.addMember("getPointsAmount", &Collision::PolygonalCollider::getPointsAmount)
			.addMember("getSelected", &Collision::PolygonalCollider::getSelected)
			.addMember("getSideAngle", &Collision::PolygonalCollider::getSideAngle)
			.addMember("getSideContainingPoint", &Collision::PolygonalCollider::getSideContainingPoint)
			.addMember("getSideLength", &Collision::PolygonalCollider::getSideLength)
			.addMember("getSolid", &Collision::PolygonalCollider::getSolid)
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
			.addMember("testAllColliders", &Collision::PolygonalCollider::testAllColliders)
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
			.addMember("getInputBufferContent", &Console::getInputBufferContent)
			.addMember("setInputBufferContent", &Console::setInputBufferContent)
			.addMember("insertInputBufferContent", &Console::insertInputBufferContent)
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
			.addMember("getFormatedMessage", &Console::Message::getFormatedMessage)
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
void CoreLib::loadConstants(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["Constants"])) (*lua)["Core"]["Constants"] = kaguya::NewTable();
	if (importAll)
	{
		(*lua)["Core"]["Constants"]["ResX"] = fn::Coord::width;
		(*lua)["Core"]["Constants"]["ResY"] = fn::Coord::height;
		(*lua)["Core"]["Constants"]["BaseResX"] = fn::Coord::baseWidth;
		(*lua)["Core"]["Constants"]["BaseResY"] = fn::Coord::baseHeight;
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadConstants] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
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
void CoreLib::loadDataParser(kaguya::State * lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["DataParser"])) (*lua)["Core"]["DataParser"] = kaguya::NewTable();
	if (importAll || args[1] == "DataParser")
	{
		(*lua)["Core"]["DataParser"]["DataParser"].setClass(kaguya::ClassMetatable<DataParser>()
			.addMember("accessDataObject", &DataParser::accessDataObject)
			.addMember("accessNavigator", &DataParser::accessNavigator)
			.addMember("attributeExists", static_cast<bool (DataParser::*)(std::string)>(&DataParser::attributeExists))
			.addMember("attributeExists", static_cast<bool (DataParser::*)(std::string, std::string, std::string)>(&DataParser::attributeExists))
			.addMember("complexExists", static_cast<bool (DataParser::*)(std::string)>(&DataParser::complexExists))
			.addMember("complexExists", static_cast<bool (DataParser::*)(std::string, std::string, std::string)>(&DataParser::complexExists))
			.addMember("createBaseAttribute", static_cast<void (DataParser::*)(std::string, double)>(&DataParser::createBaseAttribute))
			.addMember("createBaseAttribute", static_cast<void (DataParser::*)(std::string, int)>(&DataParser::createBaseAttribute))
			.addMember("createBaseAttribute", static_cast<void (DataParser::*)(std::string, bool)>(&DataParser::createBaseAttribute))
			.addMember("createBaseAttribute", static_cast<void (DataParser::*)(std::string, std::string)>(&DataParser::createBaseAttribute))
			.addMember("createBaseAttribute", static_cast<void (DataParser::*)(std::string, std::string, std::string, double)>(&DataParser::createBaseAttribute))
			.addMember("createBaseAttribute", static_cast<void (DataParser::*)(std::string, std::string, std::string, int)>(&DataParser::createBaseAttribute))
			.addMember("createBaseAttribute", static_cast<void (DataParser::*)(std::string, std::string, std::string, bool)>(&DataParser::createBaseAttribute))
			.addMember("createBaseAttribute", static_cast<void (DataParser::*)(std::string, std::string, std::string, std::string)>(&DataParser::createBaseAttribute))
			.addMember("createComplexAttribute", static_cast<void (DataParser::*)(std::string)>(&DataParser::createComplexAttribute))
			.addMember("createComplexAttribute", static_cast<void (DataParser::*)(std::string, std::string, std::string)>(&DataParser::createComplexAttribute))
			.addMember("createDataObject", &DataParser::createDataObject)
			.addMember("createFlag", &DataParser::createFlag)
			.addMember("createHeritComplexAttribute", static_cast<void (DataParser::*)(std::string)>(&DataParser::createHeritComplexAttribute))
			.addMember("createHeritComplexAttribute", static_cast<void (DataParser::*)(std::string, std::string)>(&DataParser::createHeritComplexAttribute))
			.addMember("createListAttribute", static_cast<void (DataParser::*)(std::string, std::string)>(&DataParser::createListAttribute))
			.addMember("createListAttribute", static_cast<void (DataParser::*)(std::string, std::string, std::string, std::string)>(&DataParser::createListAttribute))
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadDataParser] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
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
void CoreLib::loadEntity(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["Entity"])) (*lua)["Core"]["Entity"] = kaguya::NewTable();
	if (importAll || args[1] == "Entity")
	{
		(*lua)["Core"]["Entity"]["Entity"].setClass(kaguya::ClassMetatable<Entity>()
			.addMember("addDtPos", &Entity::addDtPos)
			.addMember("addPos", &Entity::addPos)
			.addMember("collide", &Entity::collide)
			.addMember("getCamPos", &Entity::getCamPos)
			.addMember("getEntityCollider", &Entity::getEntityCollider)
			.addMember("getLife", &Entity::getLife)
			.addMember("getMaxLife", &Entity::getMaxLife)
			.addMember("getX", &Entity::getX)
			.addMember("getY", &Entity::getY)
			.addMember("setColliderDrawOffset", &Entity::setColliderDrawOffset)
			.addMember("setColliders", &Entity::setColliders)
			.addMember("setDeltaTime", &Entity::setDeltaTime)
			.addMember("setKey", &Entity::setKey)
			.addMember("setPos", &Entity::setPos)
		);
		foundPart = true;
	}
	if (importAll || args[1] == "Character")
	{
		(*lua)["Core"]["Entity"]["Character"].setClass(kaguya::ClassMetatable<Character, Entity>()
			.addMember("addVelocity", &Character::addVelocity)
			.addMember("applyMove", &Character::applyMove)
			.addMember("cancelMoves", &Character::cancelMoves)
			.addMember("getDirection", &Character::getDirection)
			.addMember("getHSpeed", &Character::getHSpeed)
			.addMember("getVelocity", &Character::getVelocity)
			.addMember("getVSpeed", &Character::getVSpeed)
			.addMember("jump", &Character::jump)
			.addMember("melee", &Character::melee)
			.addMember("move", &Character::move)
			.addMember("setDirectionAnimation", &Character::setDirectionAnimation)
			.addMember("setJumpHeight", &Character::setJumpHeight)
			.addMember("setVelocity", &Character::setVelocity)
			.addMember("sprint", &Character::sprint)
			.addMember("textureUpdate", &Character::textureUpdate)
			.addMember("triggerCrouch", &Character::triggerCrouch)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadEntity] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}
void CoreLib::loadGUI(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["GUI"])) (*lua)["Core"]["GUI"] = kaguya::NewTable();
	if (importAll || args[1] == "Container")
	{
		(*lua)["Core"]["GUI"]["Container"].setClass(kaguya::ClassMetatable<GUI::Container>()
			.addMember("createWidgetContainer", &GUI::Container::createWidgetContainer)
			.addMember("getContainerByContainerName", &GUI::Container::getContainerByContainerName)
			.addMember("resizeWidgetContainer", &GUI::Container::resizeWidgetContainer)
			.addMember("setFocus", static_cast<void (GUI::Container::*)(std::string)>(&GUI::Container::setFocus))
			.addMember("setLayer", &GUI::Container::setLayer)
			.addMember("setAlreadyClicked", &GUI::Container::setAlreadyClicked)
			.addMember("hasFocus", static_cast<bool (GUI::Container::*)(std::string)>(&GUI::Container::hasFocus))
			.addMember("getAlreadyClicked", &GUI::Container::getAlreadyClicked)
			.addMember("autoFocus", &GUI::Container::autoFocus)
			.addMember("autoMove", &GUI::Container::autoMove)
			.addMember("setWindowSize", &GUI::Container::setWindowSize)
			.addMember("createLabel", &GUI::Container::createLabel)
			.addMember("createScrollBar", static_cast<GUI::ScrollBar* (GUI::Container::*)(std::string containerName, std::string ID, int posX, int posY, int size, int minHeightBar, bool needButtons, std::vector<GUI::Widget*>* widgetsLinked, std::string style)> (&GUI::Container::createScrollBar))
			.addMember("createLoadingBar", &GUI::Container::createLoadingBar)
			.addMember("createCheckbox", &GUI::Container::createCheckbox)
			.addMember("createButton", &GUI::Container::createButton)
			.addMember("createDroplist", static_cast<GUI::Droplist* (GUI::Container::*)(std::string containerName, std::string ID, int posX, int posY, int charSize, std::string titleOrDefaultValue, bool dropListMenu, std::string font, std::string style, \
				std::vector<std::string> list, sf::Color fontColorIdle, sf::Color fontColorHover)> (&GUI::Container::createDroplist))
			.addMember("createTab", &GUI::Container::createTab)
			.addMember("createDropbox", &GUI::Container::createDropbox)
			.addMember("createRadioButton", &GUI::Container::createRadioButton)
			.addMember("createTextInput", static_cast<GUI::TextInput* (GUI::Container::*)(std::string containerName, std::string ID, int posX, int posY, std::string defaultText, std::string font, int fontSize, sf::Color fontColor, bool multiLine, std::string style)> (&GUI::Container::createTextInput))
			.addMember("createMovable", static_cast<GUI::Movable* (GUI::Container::*)(std::string containerName, std::string ID, int posX, int posY, std::string style)> (&GUI::Container::createMovable))
			.addMember("loadWidgetContainerFromFile", &GUI::Container::loadWidgetContainerFromFile)
			.addMember("loadWidContFromFileInWidCont", &GUI::Container::loadWidContFromFileInWidCont)
			.addMember("removeWidget", &GUI::Container::removeWidget)
			.addMember("removeWidgetContainer", &GUI::Container::removeWidgetContainer)
			);
		foundPart = true;
	}
	if (importAll || args[1] == "Widget")
	{
		(*lua)["Core"]["GUI"]["Widget"].setClass(kaguya::ClassMetatable<GUI::Widget>()
			.addMember("isClicked", &GUI::Widget::isClicked)
			.addMember("isClickedOutside", &GUI::Widget::isClickedOutside)
			.addMember("isRectClicked", &GUI::Widget::isRectClicked)
			.addMember("isRectClickedOutside", &GUI::Widget::isRectClickedOutside)
			.addMember("isRectHovering", &GUI::Widget::isRectHovering)
			.addMember("isHovering", &GUI::Widget::isHovering)
			.addMember("setPosition", &GUI::Widget::setPosition)
			.addMember("move", &GUI::Widget::move)
			.addMember("getID", &GUI::Widget::getID)
			.addMember("getWidgetType", &GUI::Widget::getWidgetType)
			.addMember("getWidgetStyle", &GUI::Widget::getWidgetStyle)
			.addMember("getTexts", &GUI::Widget::getTexts)
			.addMember("getRect", &GUI::Widget::getRect)
			.addMember("getRelativePosX", &GUI::Widget::getRelativePosX)
			.addMember("getRelativePosY", &GUI::Widget::getRelativePosY)
			.addMember("getDisplayed", &GUI::Widget::getDisplayed)
			.addMember("setDisplayed", &GUI::Widget::setDisplayed)
			.addMember("setAbsolute", &GUI::Widget::setAbsolute)
			.addMember("containerChangePos", &GUI::Widget::containerChangePos)
			.addMember("removeWidget", &GUI::Widget::removeWidget)
			);
		foundPart = true;
	}
	if (importAll || args[1] == "TextInput")
	{
		(*lua)["Core"]["GUI"]["TextInput"].setClass(kaguya::ClassMetatable<GUI::TextInput, GUI::Widget>()
			.addMember("addFilter", &GUI::TextInput::addFilter)
			.addMember("getText", &GUI::TextInput::getText)
			.addMember("setText", &GUI::TextInput::setText)
			.addMember("getEnterPressed", &GUI::TextInput::getEnterPressed)
			.addMember("getHasFocus", &GUI::TextInput::getHasFocus)
			.addMember("getLabel", &GUI::TextInput::getLabel)
			);
		foundPart = true;
	}
	if (importAll || args[1] == "Label")
	{
		(*lua)["Core"]["GUI"]["Label"].setClass(kaguya::ClassMetatable<GUI::Label, GUI::Widget>()
			.addMember("resetFontVars", &GUI::Label::resetFontVars)
			.addMember("setFont", &GUI::Label::setFont)
			.addMember("setText", &GUI::Label::setText)
			.addMember("setComplexText", &GUI::Label::setComplexText)
			.addMember("addText", &GUI::Label::addText)
			.addMember("setFontSize", &GUI::Label::setFontSize)
			.addMember("centerInRect", &GUI::Label::centerInRect)
			.addMember("getFontName", &GUI::Label::getFontName)
			.addMember("getString", &GUI::Label::getString)
			.addMember("getFontSize", &GUI::Label::getfontSize)
			.addMember("getHook", &GUI::Label::getHook)
			.addMember("getRichText", &GUI::Label::getRichText)
			);
		foundPart = true;
	}
	if (importAll || args[1] == "WidgetContainer")
	{
		(*lua)["Core"]["GUI"]["WidgetContainer"].setClass(kaguya::ClassMetatable<GUI::WidgetContainer>()
			.addMember("addWidget", &GUI::WidgetContainer::addWidget)
			.addMember("resize", &GUI::WidgetContainer::resize)
			.addMember("getRect", &GUI::WidgetContainer::getRect)
			.addMember("move", &GUI::WidgetContainer::move)
			.addMember("setPosition", &GUI::WidgetContainer::setPosition)
			.addMember("setBackground", &GUI::WidgetContainer::setBackground)
			.addMember("setDisplayed", &GUI::WidgetContainer::setDisplayed)
			.addMember("getDisplayed", &GUI::WidgetContainer::getDisplayed)
			.addMember("addScrollBar", &GUI::WidgetContainer::addScrollBar)
			);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadGUI] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}
void CoreLib::loadKeyBind(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["KeyBind"])) (*lua)["Core"]["KeyBind"] = kaguya::NewTable();
	if (importAll || args[1] == "KeyBinder")
	{
		(*lua)["Core"]["KeyBind"]["KeyBinder"].setClass(kaguya::ClassMetatable<KeyBinder>()
			.addMember("connectAction", &KeyBinder::connectAction)
			.addMember("isActionDisabled", &KeyBinder::isActionDisabled)
			.addMember("isActionEnabled", &KeyBinder::isActionEnabled)
			.addMember("isActionReleased", &KeyBinder::isActionReleased)
			.addMember("isActionToggled", &KeyBinder::isActionToggled)
			.addMember("isKeyPressed", &KeyBinder::isKeyPressed)
			.addMember("loadFromFile", &KeyBinder::loadFromFile)
			.addMember("setActionDelay", &KeyBinder::setActionDelay)
			.addMember("setEnabled", &KeyBinder::setEnabled)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadKeyBind] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
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
			.addConstructor<std::string>()
			.addMember("addAtr", &LevelSprite::addAtr)
			.addMember("calculateRealCoordinates", &LevelSprite::calculateRealCoordinates)
			.addMember("getAttributes", &LevelSprite::getAttributes)
			.addMember("getH", &LevelSprite::getH)
			.addMember("getW", &LevelSprite::getW)
			.addMember("getID", &LevelSprite::getID)
			.addMember("getLayer", &LevelSprite::getLayer)
			.addMember("getName", &LevelSprite::getName)
			.addMember("getOffsetX", &LevelSprite::getOffsetX)
			.addMember("getOffsetY", &LevelSprite::getOffsetY)
			.addMember("getRect", &LevelSprite::getRect)
			.addMember("getRotation", &LevelSprite::getRotation)
			.addMember("getScaleX", &LevelSprite::getScaleX)
			.addMember("getScaleY", &LevelSprite::getScaleY)
			.addMember("getX", &LevelSprite::getX)
			.addMember("getY", &LevelSprite::getY)
			.addMember("getZDepth", &LevelSprite::getZDepth)
			.addMember("isDrawable", &LevelSprite::isDrawable)
			.addMember("move", &LevelSprite::move)
			.addMember("removeAtrByIndex", &LevelSprite::removeAtrByIndex)
			.addMember("removeAtrByName", &LevelSprite::removeAtrByName)
			.addMember("rotate", &LevelSprite::rotate)
			.addMember("scale", &LevelSprite::scale)
			.addMember("setAtr", &LevelSprite::setAtr)
			.addMember("setColor", &LevelSprite::setColor)
			.addMember("setLayer", &LevelSprite::setLayer)
			.addMember("setOffset", &LevelSprite::setOffset)
			.addMember("setPosition", &LevelSprite::setPosition)
			.addMember("setRotation", &LevelSprite::setRotation)
			.addMember("setRotationOrigin", &LevelSprite::setRotationOrigin)
			.addMember("setScale", &LevelSprite::setScale)
			.addMember("setTranslationOrigin", &LevelSprite::setTranslationOrigin)
			.addMember("setZDepth", &LevelSprite::setZDepth)
			.addMember("setVisible", &LevelSprite::setVisible)
			.addMember("isVisible", &LevelSprite::isVisible)
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
void CoreLib::loadSerial(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["Serial"])) (*lua)["Core"]["Serial"] = kaguya::NewTable();
	if (importAll || args[1] == "Serial")
	{
		(*lua)["Core"]["Serial"]["Serial"].setClass(kaguya::ClassMetatable<Serial>()
			.addMember("IsConnected", &Serial::IsConnected)
			.addMember("readData", &Serial::readData)
			.addMember("getPortName", &Serial::getPortName)
			.addMember("ReadData", &Serial::ReadData)
			.addMember("WriteData", &Serial::WriteData)
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadSerial] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}

void CoreLib::loadSFML(kaguya::State* lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["SFML"])) (*lua)["Core"]["SFML"] = kaguya::NewTable();
	if (importAll || args[1] == "Color")
	{
		(*lua)["Core"]["SFML"]["Color"].setClass(kaguya::ClassMetatable<sf::Color>()
			.addConstructor<UINT8, UINT8, UINT8, UINT8>()
			.addConstructor<int, int, int, int>()
			.addMember("a", &sf::Color::a)
			.addMember("r", &sf::Color::r)
			.addMember("g", &sf::Color::b)
			.addMember("b", &sf::Color::b)
		);
		foundPart = true;
	}
	if (importAll || args[1] == "Drawable")
	{
		(*lua)["Core"]["SFML"]["Drawable"].setClass(kaguya::ClassMetatable<sf::Drawable>()
		);
		foundPart = true;
	}
	if (importAll || args[1] == "Transformable")
	{
		(*lua)["Core"]["SFML"]["Transformable"].setClass(kaguya::ClassMetatable<sf::Transformable>()
			.addMember("getInverseTransform", &sf::Transformable::getInverseTransform)
			.addMember("getOrigin", &sf::Transformable::getOrigin)
			.addMember("getPosition", &sf::Transformable::getPosition)
			.addMember("getRotation", &sf::Transformable::getRotation)
			.addMember("getScale", &sf::Transformable::getScale)
			.addMember("getTransform", &sf::Transformable::getTransform)
			.addMember("move", static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::move))
			.addMember("move", static_cast<void (sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::move))
			.addMember("rotate", &sf::Transformable::rotate)
			.addMember("scale", static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::scale))
			.addMember("scale", static_cast<void (sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::scale))
			.addMember("setOrigin", static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::setOrigin))
			.addMember("setOrigin", static_cast<void (sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::setOrigin))
		);
		foundPart = true;
	}
	if (importAll || args[1] == "Sprite")
	{
		(*lua)["Core"]["SFML"]["Sprite"].setClass(kaguya::ClassMetatable<sf::Sprite, kaguya::MultipleBase<sf::Drawable, sf::Transformable>>()
		);
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadSFML] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
}

void CoreLib::loadSTD(kaguya::State * lua, std::vector<std::string> args)
{
	registerLib(lua, fn::Vector::join(args, "."));
	bool importAll = args.size() == 1;
	bool foundPart = false;
	if (!(bool)((*lua)["Core"]["STD"])) (*lua)["Core"]["STD"] = kaguya::NewTable();
	if (importAll || args[1] == "Pair")
	{
		(*lua)["Core"]["STD"]["IntPair"].setClass(kaguya::ClassMetatable<std::pair<int, int>>()
			.addConstructor<int, int>()
			.addMember("first", &std::pair<int, int>::first)
			.addMember("second", &std::pair<int, int>::second)
			.addMember("swap", &std::pair<int, int>::swap)
		);
		(*lua)["Core"]["STD"]["DoublePair"].setClass(kaguya::ClassMetatable<std::pair<double, double>>()
			.addConstructor<double, double>()
			.addMember("first", &std::pair<double, double>::first)
			.addMember("second", &std::pair<double, double>::second)
			.addMember("swap", &std::pair<double, double>::swap)
			);
		foundPart = true;
	}
	if (importAll || args[1] == "Print")
	{
		(*lua)["Core"]["STD"]["Print"] = kaguya::function([](std::string disp) { std::cout << "[Lua] : " << disp << std::endl; });
		foundPart = true;
	}
	if (!foundPart) std::cout << "<Error:Script:CoreLib>[loadSTD] : Can't import : " << fn::Vector::join(args, ".") << std::endl;
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
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::vector<int>>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::vector<float>>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::vector<std::string>>)
			.addMember("pushParameter", &TriggerGroup::pushParameter<std::vector<bool>>)
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