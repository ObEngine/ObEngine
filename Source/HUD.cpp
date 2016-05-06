//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "HUD.hpp"

IntBar::IntBar(std::string barFilename, int x, int y, int w)
{
	barTexture.loadFromFile("Sprites/HUD/" + barFilename);
	barSprite = sprFunc::getCleanSprite(barTexture);
	barSprite.setTexture(barTexture);
	this->x = x;
	this->y = y;
	this->w = w;
}
void IntBar::setPosition(int x, int y)
{
	this->x = x; this->y = y;
}
void IntBar::setWidth(int w)
{
	this->w = w;
}
int IntBar::getX()
{
	return x;
}
int IntBar::getY()
{
	return y;
}
int IntBar::getW()
{
	return w;
}
void IntBar::setPercent(int percent)
{
	barPercent = percent;
}
void IntBar::addPercent(int percent)
{
	barPercent += percent;
}
int IntBar::getPercent()
{
	return barPercent;
}
void IntBar::update(double dt)
{
	float barModifier = std::floor((double)abs(oldPercent - barPercent) / (double)20.0) * dt;
	if (oldPercent > barPercent)
		barModifier *= -1;
	oldPercent += barModifier;
}
void IntBar::draw(sf::RenderWindow* surf)
{
	for (unsigned int i = 0; i < oldPercent * ((double)w / 100.0); i++)
	{
		barSprite.setPosition(x + i, y);
		surf->draw(barSprite);
	}
}

HUDOverlay::HUDOverlay()
{
	font.loadFromFile("Data/Fonts/DarkSka.ttf");
	textCD.setFont(font);
	textCD.setCharacterSize(36);
	textCD.setColor(sf::Color::White);
	selectTex = new sf::Texture;
	selectTex->loadFromFile("Sprites/Caster/select.png");
	selectTexSpr = sprFunc::getCleanSprite(*selectTex);
	selectTexSpr.setTexture(*selectTex);
	selectTexSpr.setOrigin(32, 32);
	elemTexture["Water"] = new sf::Texture;
	elemTexture["Water"]->loadFromFile("Sprites/Caster/Water.png");
	elemTexture["Fire"] = new sf::Texture;
	elemTexture["Fire"]->loadFromFile("Sprites/Caster/Fire.png");
	elemTexture["Wind"] = new sf::Texture;
	elemTexture["Wind"]->loadFromFile("Sprites/Caster/Wind.png");
	elemTexture["Earth"] = new sf::Texture;
	elemTexture["Earth"]->loadFromFile("Sprites/Caster/Earth.png");
	elemMap["Water"] = new sf::Sprite;
	elemMap["Water"]->setTexture(*elemTexture["Water"]);
	elemMap["Water"]->setPosition(-15, 5);
	elemMap["Fire"] = new sf::Sprite;
	elemMap["Fire"]->setTexture(*elemTexture["Fire"]);
	elemMap["Fire"]->setPosition(-15, 5);
	elemMap["Wind"] = new sf::Sprite;
	elemMap["Wind"]->setTexture(*elemTexture["Wind"]);
	elemMap["Wind"]->setPosition(-15, 5);
	elemMap["Earth"] = new sf::Sprite;
	elemMap["Earth"]->setTexture(*elemTexture["Earth"]);
	elemMap["Earth"]->setPosition(-15, 5);
	lifeBar = new IntBar("life.png", 124, 16, 700);
	manaBar = new IntBar("mana.png", 124, 41, 700);
	lifeBar->setPercent(0);
	manaBar->setPercent(0);
	casterOverlay.loadFromFile("Sprites/HUD/overlay.png");
	casterOverlaySpr = sprFunc::getCleanSprite(casterOverlay);
	casterOverlaySpr.setTexture(casterOverlay);
	casterOverlaySpr.setPosition(0, 0);
	std::vector<std::string> spellFolderIcon = fn::File::listDirInDir("Sprites/Spells");
	for (unsigned int i = 0; i < spellFolderIcon.size(); i++)
	{
		sf::Texture* tempIcon = new sf::Texture;
		tempIcon->loadFromFile("Sprites/Spells/" + spellFolderIcon[i] + "/icon.png");
		spellIconTextureMap[spellFolderIcon[i]] = tempIcon;
	}
}
void HUDOverlay::update(double dt)
{
	int lifePercent = ((float)entityHook->getLife() / (float)entityHook->getMaxLife()) * 100;
	int manaPercent = ((float)castHook->getBloodAmount() / (float)castHook->getMaxBloodAmount()) * 100;
	lifeBar->setPercent(lifePercent); manaBar->setPercent(manaPercent);
	lifeBar->update(dt); manaBar->update(dt);
	selectTexSpr.rotate(1 * dt);
}
void HUDOverlay::draw(sf::RenderWindow* surf)
{
	lifeBar->draw(surf);
	manaBar->draw(surf);
	std::vector<std::string> spellIconToDraw = castHook->getSpellList(castHook->getCurrentElement());
	sf::Sprite blitIcon;
	for (unsigned int i = 0; i < spellIconToDraw.size(); i++)
	{
		blitIcon = *spellIconSpriteMap[spellIconToDraw[i]];
		
		if (castHook->getSpellCooldown(spellIconToDraw[i]) != 0)
		{
			int colorFade = 150 - 120*((float)castHook->getSpellCooldown(spellIconToDraw[i]) / (float)castHook->getSpellMaxCooldown(spellIconToDraw[i]));
			blitIcon.setColor(sf::Color(colorFade, colorFade, colorFade));
			surf->draw(blitIcon);
			textCD.setString(std::to_string(castHook->getSpellCooldown(spellIconToDraw[i])/1000+1));
			int textSizePosition;
			textSizePosition = std::to_string(castHook->getSpellCooldown(spellIconToDraw[i]) / 1000 + 1).length();
			textCD.setPosition(137 + 70 * i - (5 * textSizePosition-1), 80);
			surf->draw(textCD);
		}
		else
		{
			surf->draw(blitIcon);
		}
		if (i == castHook->getCurrentSpellIndex())
		{

			selectTexSpr.setPosition(142 + 70 * i, 102);
			surf->draw(selectTexSpr);
		}
	}
	surf->draw(*elemMap[castHook->getCurrentElement()]);
	surf->draw(casterOverlaySpr);
}

void HUDOverlay::hookToCaster(Caster* castHk)
{
	castHook = castHk;
}

void HUDOverlay::hookToCharacter(Entity* entityHk)
{
	entityHook = entityHk;
}

void HUDOverlay::loadIconForElement(std::string element)
{
	std::vector<std::string> spellIconToDraw = castHook->getSpellList(element);
	sf::Sprite* blitIcon;
	std::cout << "CALLING LOAD ALL ICONS WITH SIZE : " << spellIconToDraw.size() << std::endl;
	for (unsigned int i = 0; i < spellIconToDraw.size(); i++)
	{
		std::cout << "Current spell being loaded : " << spellIconToDraw[i] << std::endl;
		blitIcon = new sf::Sprite;
		blitIcon->setTexture(*spellIconTextureMap[spellIconToDraw[i]]);
		blitIcon->setPosition(110 + 70 * i, 70);
		spellIconSpriteMap[spellIconToDraw[i]] = blitIcon;
	}
}

void HUDOverlay::loadAllIcons()
{
	std::vector<std::string> elementList = { "Fire", "Water", "Wind", "Earth" };
	for (unsigned int i = 0; i < elementList.size(); i++)
	{
		loadIconForElement(elementList[i]);
	}
}