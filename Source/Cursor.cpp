#include "Cursor.hpp"

void Cursor::initialize(sf::RenderWindow* window)
{
	this->window = window;
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
	cursorAnim = anim::Animator();
	cursorAnim.setPath("Sprites/Cursors/" + cursor);
	cursorAnim.loadAnimator();
	cursorAnim.setKey("IDLE");
	cursorAnim.update();
	cursorSprite = cursorAnim.getSprite();
}

void Cursor::selectKey(std::string key)
{
	cursorAnim.setKey(key);
}

int Cursor::getX()
{
	return x;
}

int Cursor::getY()
{
	return y;
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
	if (doesUpdateOutsideWindow)
	{
		x = sf::Mouse::getPosition().x - window->getPosition().x;
		y = sf::Mouse::getPosition().y - window->getPosition().y;
		if (x < 0) x = 0;
		if (x > window->getSize().x) x = window->getSize().x;
		if (y < 0) y = 0;
		if (y > window->getSize().y) y = window->getSize().y;
	}
	else
	{
		if (sf::Mouse::getPosition().x - window->getPosition().x > 0 && sf::Mouse::getPosition().y - window->getPosition().y > 0)
		{
			if (sf::Mouse::getPosition().x - window->getPosition().x < window->getSize().x && sf::Mouse::getPosition().y - window->getPosition().y < window->getSize().y)
			{
				x = sf::Mouse::getPosition().x - window->getPosition().x;
				y = sf::Mouse::getPosition().y - window->getPosition().y;
				if (x < 0) x = 0;
				if (x > window->getSize().x) x = window->getSize().x;
				if (y < 0) y = 0;
				if (y > window->getSize().y) y = window->getSize().y;
			}
		}
	}
	cursorSprite->setPosition(x, y);
	cursorCollider->setPositionFromMaster(this->x, this->y);
}

void Cursor::updateOutsideWindow(bool state)
{
	doesUpdateOutsideWindow = state;
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

sf::Sprite* Cursor::getSprite()
{
	return cursorSprite;
}

Collision::PolygonalCollider* Cursor::getCollider()
{
	return cursorCollider;
}