#include "Entity.hpp"

Entity::Entity()
{
	entityCollider = new Collision::PolygonalCollider("EntityCollider");
	entityCollider->addPoint(0, 0);
	entityCollider->addPoint(36, 0);
	entityCollider->addPoint(36, 89);
	entityCollider->addPoint(0, 89);
	entityType = "Entity";
}
void Entity::draw(sf::RenderWindow* surf)
{
	entitySprite->setPosition(x - worldCamX - entityAnimator.getSpriteOffsetX(), y - worldCamY - entityAnimator.getSpriteOffsetY());
	surf->draw(*entitySprite);
}
double Entity::getX()
{
	return x;
}

double Entity::getY()
{
	return y;
}

void Entity::update()
{
	this->textureUpdate();
	this->moveUpdate();

	entityAnimator.update();
	if (entityAnimator.textureChanged())
		entitySprite = entityAnimator.getSprite();
}
Collision::PolygonalCollider* Entity::getEntityCollider()
{
	return entityCollider;
}
void Entity::setColliders(std::vector<Collision::PolygonalCollider*>* collideList)
{
	this->collidersList = collideList;
}

bool Entity::collide(int tx, int ty)
{
	return Collision::testAllColliders(entityCollider, collidersList, tx, ty);
}

void Entity::getCamPos(int camX, int camY)
{
	this->worldCamX = camX;
	this->worldCamY = camY;
}

void Entity::textureUpdate()
{

}

void Entity::moveUpdate()
{

}

int Entity::getLife()
{
	return life;
}

int Entity::getMaxLife()
{
	return maxLife;
}

void Entity::setKey(std::string key)
{
	entityAnimator.setKey(key);
}

void Entity::setDeltaTime(double dt)
{
	currentDeltaTime = dt;
}
void Entity::setPos(double newx, double newy)
{
	x = newx;
	y = newy;
	entityCollider->setPosition(x, y);
}
void Entity::addPos(double addx, double addy)
{
	x += addx;
	y += addy;
	entityCollider->setPosition(x, y);
}
void Entity::addDtPos(double addx, double addy)
{
	x += addx * currentDeltaTime;
	y += addy * currentDeltaTime;
	entityCollider->setPosition(x, y);
}
void Entity::setStreamLink(Console::Stream* link)
{
	streamLink = link;
}
void Entity::setColliderDrawOffset(int x, int y)
{
	entityCollider->setDrawOffset(x, y);
}