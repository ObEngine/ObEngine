//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "LevelSprite.hpp"

LevelSprite::LevelSprite(std::string decoName, std::string decoID, anim::RessourceManager* rsMan)
{
	this->sprName = decoName;
	this->sprID = decoID;
	this->returnSprite = new sfe::ComplexSprite;
	if (rsMan != NULL)
	{
		sprAnim.attachRessourceManager(rsMan);
	}
	sprAnim.loadAnimation("Sprites/LevelSprites/" + decoName);
}

LevelSprite::LevelSprite(std::string decoID)
{
	this->sprID = decoID;
	this->drawable = false;
	this->returnSprite = new sfe::ComplexSprite;
}

void LevelSprite::useDirtyAnimation(bool state, bool candraw)
{
	useDefaultAnimationSystem = state;
	drawable = candraw;
}

void LevelSprite::setSprite(sfe::ComplexSprite* spr)
{
	returnSprite = spr;
}

void LevelSprite::setSprite(sf::Sprite* spr)
{
	returnSprite->copyFromSprite(*spr);
}

void LevelSprite::setLayer(int layer){
	this->layer = layer;
}
void LevelSprite::setZDepth(int zdepth){
	this->zdepth = zdepth;
}

void LevelSprite::setAtr(std::vector<std::string> atrList) {
	currentAtr = atrList;
}
void LevelSprite::addAtr(std::string atr) {
	currentAtr.push_back(atr);
}
void LevelSprite::removeAtrByIndex(int index) {
	currentAtr.erase(currentAtr.begin() + index);
}
void LevelSprite::removeAtrByName(std::string name) {
	currentAtr.erase(remove(currentAtr.begin(), currentAtr.end(), name), currentAtr.end());
}

void LevelSprite::setRotation(double rotate) {
	rotation = rotate;
	returnSprite->setRotation(rotation);
	calculateRealCoordinates();
}

void LevelSprite::rotate(double addRotate) {
	rotation += addRotate;
	if (rotation < 0) rotation += 360;
	rotation = ((int)rotation % 360) + (rotation - std::floor(rotation));
	returnSprite->setRotation(rotation);
	calculateRealCoordinates();
}
void LevelSprite::scale(double scaleX, double scaleY) {
	this->scaleX += scaleX;
	this->scaleY += scaleY;
	returnSprite->setScale(this->scaleX, this->scaleY);
	calculateRealCoordinates();
}
void LevelSprite::setScale(double scaleX, double scaleY)
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	returnSprite->setScale(scaleX, scaleY);
	calculateRealCoordinates();
}
void LevelSprite::setTranslationOrigin(int x, int y) {
	originTraX = x;
	originTraY = y;
	returnSprite->setTranslationOrigin(originTraX, originTraY);
}

void LevelSprite::setRotationOrigin(int x, int y)
{
	originRotX = x;
	originRotY = y;
	returnSprite->setRotationOrigin(originRotX, originRotY);
}

void LevelSprite::textureUpdate(bool forceUpdate)
{
	if (useDefaultAnimationSystem)
	{
		if (drawable)
		{
			sprAnim.update();
			if (sprAnim.indexChanged() || forceUpdate)
			{
				actualTexture = *(sprAnim.getTexture());
				returnSprite->setTexture(actualTexture);
				returnSprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i((int)actualTexture.getSize().x, (int)actualTexture.getSize().y)));
				returnSprite->setPosition(absoluteX, absoluteY);
				returnSprite->setRotation(rotation);
				returnSprite->setScale(scaleX, scaleY);
				returnSprite->setColor(spriteColor);
				calculateRealCoordinates();
			}
		}
	}
	else
	{
		returnSprite->setPosition(absoluteX, absoluteY);
		returnSprite->setRotation(rotation);
		returnSprite->setScale(scaleX, scaleY);
		returnSprite->setColor(spriteColor);
		calculateRealCoordinates();
	}
}

void LevelSprite::setSpriteColor(sf::Color newColor)
{
	spriteColor = newColor;
	returnSprite->setColor(spriteColor);
}

sfe::ComplexSprite* LevelSprite::getSprite()
{
	return returnSprite;
}

void LevelSprite::setPosition(double x, double y)
{
	absoluteX =  x;
	absoluteY = y;
	returnSprite->setPosition(absoluteX, absoluteY);
}

void LevelSprite::move(double x, double y)
{
	absoluteX += x;
	absoluteY += y;
	if ((int)absoluteX != returnSprite->getPosition().x || (int)absoluteY != returnSprite->getPosition().y)
		returnSprite->setPosition(absoluteX, absoluteY);
}

double LevelSprite::getX() {
	return absoluteX;
}
double LevelSprite::getY() {
	return absoluteY;
}
double LevelSprite::getScaleX() {
	return scaleX;
}
double LevelSprite::getScaleY() {
	return scaleY;
}
float LevelSprite::getRotation() {
	return rotation;
}
int LevelSprite::getLayer() {
	return layer;
}
int LevelSprite::getZDepth() {
	return zdepth;
}
std::string LevelSprite::getID() {
	return sprID;
}
std::string LevelSprite::getName() {
	return sprName;
}
std::vector<std::string> LevelSprite::getAttributes(){
	return currentAtr;
}
int LevelSprite::getW() {
	return returnSprite->getGlobalBounds().width;
}
int LevelSprite::getH() {
	return returnSprite->getGlobalBounds().height;
}

void LevelSprite::calculateRealCoordinates()
{
	width = returnSprite->getGlobalBounds().width;
	height = returnSprite->getGlobalBounds().height;
}

sf::FloatRect LevelSprite::getRect()
{
	sf::FloatRect mrect = returnSprite->getGlobalBounds();
	/*sf::Transform transform = this->returnSprite->getTransform();
	sf::Vector2f ncoords;
	ncoords = transform.getInverse().transformPoint(sf::Vector2f(transform.transformPoint(sf::Vector2f(mrect.left, mrect.top))));
	mrect.left = ncoords.x;
	mrect.top = ncoords.y;*/
	return mrect;
}

bool LevelSprite::isDrawable()
{
	return drawable;
}

void LevelSprite::setVisible(bool visible)
{
	this->visible = visible;
}

bool LevelSprite::isVisible()
{
	return this->visible;
}

Collision::PolygonalCollider * LevelSprite::getCollisionHook()
{
	return collisionHook;
}

void LevelSprite::hookToCollision(Collision::PolygonalCollider* hook)
{
	collisionHook = hook;
}
