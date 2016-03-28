#include "Caster.hpp"

Caster::Caster()
{
	elemList = { "Water", "Wind", "Fire", "Earth" };
	currentElement = elemList[elemIndex];
	castInfos.parseFile("Data/Stats/Player/Caster.sta.msd");
	for (unsigned int i = 0; i < castInfos.getListSize("SpellsUnlocked", "", "SpellList"); i++)
	{
		std::string gatherName;
		castInfos.getListItem("SpellsUnlocked", "", "SpellList", i)->getData(&gatherName);
		spellList.push_back(gatherName);
		cooldownTimer[gatherName] = 0;
	}
	spellInfos.parseFile("Data/Stats/Player/Spells.sta.msd");
	for (unsigned int i = 0; i < spellList.size(); i++)
	{
		std::string gatherElem;
		spellInfos.getAttribute(spellList[i], "", "element")->getData(&gatherElem);
		spellElemList[gatherElem].push_back(spellList[i]);
	}
	typedef std::map<std::string, std::vector<std::string>>::iterator it_type;
	for (it_type iterator = spellElemList.begin(); iterator != spellElemList.end(); iterator++) {
		std::string key = iterator->first;
		std::vector<std::string> spellForElem = iterator->second;
	}
	currentSpell = spellElemList[currentElement][spellIndex];
}

void Caster::castSpell()
{
	int bloodCost;
	spellInfos.getAttribute(currentSpell, "", "bloodCost")->getData(&bloodCost);
	if (bloodAmount - bloodCost > 0 && cooldownTimer[currentSpell] < GetTickCount64())
	{
		int spCoolDown;
		spellInfos.getAttribute(currentSpell, "", "cooldown")->getData(&spCoolDown);
		cooldownTimer[currentSpell] = GetTickCount64() + spCoolDown;
		this->addBlood(-bloodCost);
		int spellInclinaison = 0;
		int offsetX = 0;
		int offsetY = 0;
		if (spellInfos.attributeExists(currentSpell, "", "offsetX"))
			spellInfos.getAttribute(currentSpell, "", "offsetX")->getData(&offsetX);
		if (spellInfos.attributeExists(currentSpell, "", "offsetY"))
			spellInfos.getAttribute(currentSpell, "", "offsetY")->getData(&offsetY);
		int startSpX = charHook->getX() + 120;
		int startSpY = charHook->getY() + 190;
		int endSpX = cursHook->getX() + worldHook->getCamX();
		int endSpY = cursHook->getY() + worldHook->getCamY();
		int xAbs = endSpX - startSpX;
		int yAbs = endSpY - startSpY;
		int hypo = sqrt((xAbs*xAbs) + (yAbs*yAbs));
		float sDiv = (float)yAbs / (float)hypo;
		if (xAbs >= 0)
			spellInclinaison = asin(sDiv) * (180.0 / 3.14) + 90;
		else
			spellInclinaison = acos(sDiv) * (180.0 / 3.14) + 180;
		Spells::Projectile* tempSpell = new Spells::Projectile(std::to_string(fn::Math::randint(0, 100000)), currentSpell, spellInclinaison, &spellInfos, &castRessource);
		int spellModulo = spellInclinaison % 90;
		int spellQuadrant = (int)spellInclinaison / 90;
		int invOffX = 1;
		int invOffY = 1;
		int realOffsetX = (offsetX*fabs(cos(spellInclinaison)) + offsetY*fabs(sin(spellInclinaison)));
		int realOffsetY = (offsetX*fabs(sin(spellInclinaison)) + offsetY*fabs(cos(spellInclinaison)));
		tempSpell->setX(startSpX+realOffsetX);
		tempSpell->setY(startSpY+realOffsetY);
		tempSpell->setPosTarget(endSpX+realOffsetX, endSpY+realOffsetY);
		worldHook->castSpell(tempSpell);
		if (charHook->getX() - worldHook->getCamX() + 120 > cursHook->getX())
			charHook->setKey("CAST_LEFT");
		else
			charHook->setKey("CAST_RIGHT");
	}
}

long int Caster::getSpellCooldown(std::string spellName)
{
	if (cooldownTimer[spellName] - GetTickCount64() >= 0)
		return cooldownTimer[spellName] - GetTickCount64();
	else
		return 0;
}

long int Caster::getSpellMaxCooldown(std::string spellName)
{
	int returnMaxCD;
	spellInfos.getAttribute(spellName, "", "cooldown")->getData(&returnMaxCD);
	return returnMaxCD;
}

int Caster::getBloodAmount()
{
	return bloodAmount;
}

int Caster::getMaxBloodAmount()
{
	return maxBloodAmount;
}

void Caster::addBlood(int blood)
{
	bloodAmount += blood;
	if (bloodAmount > maxBloodAmount)
		bloodAmount = maxBloodAmount;
	else if (bloodAmount < 0)
		bloodAmount = 0;
}

void Caster::setBlood(int blood)
{
	bloodAmount = blood;
	if (bloodAmount > maxBloodAmount)
		bloodAmount = maxBloodAmount;
	else if (bloodAmount < 0)
		bloodAmount = 0;
}

void Caster::switchElement(std::string rotation)
{
	if (rotation == "Up")
	{
		elemIndex++;
	}
	else if (rotation == "Down")
		elemIndex--;
	if (elemIndex < 0)
		elemIndex = elemList.size() - 1;
	if (elemIndex > elemList.size() - 1)
		elemIndex = 0;
	currentElement = elemList[elemIndex];
	spellIndex = 0;
	currentSpell = spellElemList[currentElement][spellIndex];
}

void Caster::switchSpell(std::string rotation)
{
	if (rotation == "Up")
		spellIndex++;
	else if (rotation == "Down")
		spellIndex--;
	if (spellIndex < 0)
		spellIndex = spellElemList[currentElement].size() - 1;
	if (spellIndex > spellElemList[currentElement].size())
		spellIndex = 0;
	currentSpell = spellElemList[currentElement][spellIndex];
}

void Caster::selectSpell(int slot)
{
	spellIndex = slot;
	if (spellIndex > spellElemList[currentElement].size() - 1)
		spellIndex = spellElemList[currentElement].size() - 1;
	else if (spellIndex < 0)
		spellIndex = 0;
	currentSpell = spellElemList[currentElement][spellIndex];
}

std::string Caster::getCurrentElement()
{
	return currentElement;
}

int Caster::getCurrentSpellIndex()
{
	return spellIndex;
}

std::string Caster::getCurrentSpell()
{
	return currentSpell;
}

std::vector<std::string> Caster::getSpellList(std::string element)
{
	return spellElemList[element];
}

void Caster::hookToWorld(World* hook)
{
	worldHook = hook;
}

void Caster::hookToChar(Character* chook)
{
	charHook = chook;
}

void Caster::hookToCurs(Cursor* curs)
{
	cursHook = curs;
}

void Caster::resetCooldown(std::string spellName)
{
	if (spellName == "ALL")
	{
		typedef std::map<std::string, double>::iterator it_type;
		for (it_type iterator = cooldownTimer.begin(); iterator != cooldownTimer.end(); iterator++) {
			cooldownTimer[iterator->first] = 0;
		}
	}
	else
	{
		cooldownTimer[spellName] = 0;
	}
}