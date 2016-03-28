#include "Spells.hpp"

Spells::Spell::Spell()
{

}


Spells::Projectile::Projectile(std::string id, std::string name, int rotation, DataParser* spellInfo, anim::RessourceManager* spellRessource)
{
	spellID = id;
	spellName = name;
	rotateAngle = rotation;
	std::cout << "Spell created !" << std::endl;
	spellInfo->getAttribute(spellName, "", "velocity")->getData(&velocity);
	spellInfo->getAttribute(spellName, "", "damage")->getData(&damage);
	spellInfo->getAttribute(spellName, "", "knockBack")->getData(&knockbackForce);
	spellInfo->getAttribute(spellName, "", "range")->getData(&range);
	spellInfo->getAttribute(spellName, "", "destroyedOnHit")->getData(&destroyedOnHit);
	spellInfo->getAttribute(spellName, "", "targetMode")->getData(&targetMode);
	spellAnimator.setPath("Sprites/Spells/"+name);
	spellAnimator.attachRessourceManager(spellRessource);
	spellAnimator.loadAnimator();
	spellAnimator.setKey("THROW");
}

void Spells::Projectile::update(double dt)
{
	spellAnimator.update();
	if (spellAnimator.textureChanged())
	{
		spellSprite = spellAnimator.getSprite();
		spellSprite->setOrigin(spellSprite->getGlobalBounds().width / 2, spellSprite->getGlobalBounds().height / 2);
		spellSprite->setRotation(rotateAngle);
	}
	if (targetMode == "POS")
	{
		if (currentRange >= range)
		{
			isAlive = false;
		}
		else
		{
			x += xVelocity * dt;
			y += yVelocity * dt;
		}
		currentRange += 1;
	}
}

int Spells::Projectile::getDamage()
{
	return damage;
}

void Spells::Projectile::specialOnHit()
{

}

void Spells::Projectile::setX(int newX)
{
	this->x = newX;
}

void Spells::Projectile::setY(int newY)
{
	this->y = newY;
}

int Spells::Projectile::getX()
{
	return x;
}

int Spells::Projectile::getY()
{
	return y;
}

bool Spells::Projectile::isSpellAlive()
{
	return isAlive;
}

void Spells::Projectile::setEntityTarget(Entity* target)
{
	entityTarget = target;
}

void Spells::Projectile::setPosTarget(int tx, int ty)
{
	xTarget = tx;
	yTarget = ty;
	xVelocity = ((tx - x) / velocity);
	yVelocity = ((ty - y) / velocity);
	std::cout << "Hey xVelocity is equal to " << xVelocity << std::endl;
	std::cout << "Hey yVelocity is equal to " << yVelocity << std::endl;
}

sf::Sprite* Spells::Projectile::getSprite()
{
	spellSprite->setPosition(x, y);
	return spellSprite;
}