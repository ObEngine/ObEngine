#include "Cursor.hpp"

void Cursor::initialize(int screenSizeX, int screenSizeY)
{
	this->screenSizeX = screenSizeX;
	this->screenSizeY = screenSizeY;
	cursorAnim.setPath("Sprites/Cursors/Round");
	cursorAnim.loadAnimator();
	cursorAnim.setKey("IDLE");
	cursorCollider = new Collision::PolygonalCollider("Cursor");
	cursorCollider->addPoint(0, 0);
	cursorCollider->addPoint(2, 0);
	cursorCollider->addPoint(2, 2);
	cursorCollider->addPoint(0, 2);
	cursorCollider->setPositionFromMaster(this->x, this->y);
}

void Cursor::selectCursor(std::string cursor)
{
	cursorAnim.setPath("Sprites/Cursors/" + cursor);
	cursorAnim.loadAnimator();
	cursorAnim.setKey("IDLE");
}

void Cursor::selectKey(std::string key)
{
	cursorAnim.setKey(key);
}

int Cursor::getX()
{
	return (x * 1920) / fn::Coord::baseWidth;
}

int Cursor::getY()
{
	return (y * 1080) / fn::Coord::baseHeight;
}

void Cursor::setX(int newx)
{
	this->x = newx;
	sf::Mouse::setPosition(sf::Vector2i(this->x, this->y));
}

void Cursor::setY(int newy)
{
	this->y = newy;
	sf::Mouse::setPosition(sf::Vector2i(this->x, this->y));
}

void Cursor::setPosition(int newx, int newy)
{
	this->x = newx;
	this->y = newy;
	sf::Mouse::setPosition(sf::Vector2i(this->x, this->y));
}

void Cursor::update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !leftclicked)
	{
			leftclicked = true;
			leftfirstclic = true;
			leftReleased = false;
			cursorAnim.setKey("CLIC");
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && leftclicked)
	{
		leftclicked = false;
		leftfirstclic = false;
		leftReleased = true;
		cursorAnim.setKey("RELEASE");
	}
	else
	{
		leftfirstclic = false;
		leftReleased = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !rightclicked)
	{
		rightclicked = true;
		rightfirstclic = true;
		rightReleased = false;
		cursorAnim.setKey("CLIC");
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && rightclicked)
	{
		rightclicked = false;
		rightfirstclic = false;
		rightReleased = true;
		cursorAnim.setKey("RELEASE");
	}
	else
	{
		rightfirstclic = false;
		rightReleased = false;
	}
	if (!leftclicked && !rightclicked && cursorAnim.getKey() == "HOLD")
		cursorAnim.setKey("RELEASE");
	cursorAnim.update();
	if (cursorAnim.textureChanged())
	{
		cursorSprite = cursorAnim.getSprite();
	}
	x = sf::Mouse::getPosition().x;
	y = sf::Mouse::getPosition().y;
	cursorSprite->setPosition(x, y);
	cursorCollider->setPositionFromMaster(this->x, this->y);
}

bool Cursor::getPressed(std::string clic)
{
	if (clic == "Left")
		return leftclicked;
	else if (clic == "Right")
		return rightclicked;
	else
		return false;
}

bool Cursor::getClicked(std::string clic)
{
	if (clic == "Left")
		return leftfirstclic;
	else if (clic == "Right")
		return rightfirstclic;
	else
		return false;
}

bool Cursor::getReleased(std::string clic)
{
	if (clic == "Left")
		return leftReleased;
	else if (clic == "Right")
		return rightReleased;
	else
		return false;
}

Collision::PolygonalCollider* Cursor::getCollider()
{
	return cursorCollider;
}

sf::Sprite* Cursor::getSprite()
{
	return cursorSprite;
}