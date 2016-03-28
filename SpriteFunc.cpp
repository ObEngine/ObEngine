#include "SpriteFunc.hpp"

sf::Sprite sprFunc::getCleanSprite(sf::Texture texture)
{
	sf::Sprite returnSprite;
	returnSprite.setTexture(texture);
	return returnSprite;
}