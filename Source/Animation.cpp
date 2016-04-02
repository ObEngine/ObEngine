//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Animation.hpp"

//ANIMATION GROUP
anim::AnimationGroup::AnimationGroup(std::string pgroupname) {
	this->groupName = pgroupname;
}
void anim::AnimationGroup::build() {
	sf::RenderTexture buildTex;
	int highestHeight = 0;
	int totalWidth = 0;
	for (int i = 0; i < groupList.size(); i++)
	{
		if (groupList[i]->getSize().y > highestHeight)
			highestHeight = groupList[i]->getSize().y;
		texturePos.push_back(new sf::IntRect(totalWidth, 0, groupList[i]->getSize().x, groupList[i]->getSize().y));
		totalWidth += groupList[i]->getSize().x;
	}
	buildTex.create(totalWidth, highestHeight);
	buildTex.clear(sf::Color(0, 0, 0, 0));
	int currentXblit = 0;
	for (int i = 0; i < groupList.size(); i++)
	{
		sf::Sprite sprBuffer;
		sprBuffer.setTexture(*groupList[i]);
		sprBuffer.setPosition(currentXblit, 0);
		buildTex.draw(sprBuffer);
		buildTex.display();
		currentXblit += groupList[i]->getSize().x;
	}
	buildTex.display();
	spriteSheet = buildTex.getTexture();
	currentSprite = sf::Sprite(spriteSheet, *texturePos[0]);
}
void anim::AnimationGroup::setGroupClock(int clock) {
	this->groupClock = clock;
}
void anim::AnimationGroup::setGroupLoop(int loops) {
	this->loopTime = loops;
}
void anim::AnimationGroup::pushTexture(sf::Texture* texture) {
	groupList.push_back(texture);
	groupSize++;
}
void anim::AnimationGroup::removeTextureByIndex(int index) {
	if (groupSize > 0)
	{
		groupList.erase(groupList.begin() + index);
		groupSize--;
	}
}
sf::Sprite* anim::AnimationGroup::returnSprite() {
	return &currentSprite;
}
sf::IntRect* anim::AnimationGroup::getSpriteRect() {
	return texturePos[groupIndex];
}
void anim::AnimationGroup::updateSprite() {
	currentSprite.setTextureRect(*texturePos[groupIndex]);
}
void anim::AnimationGroup::reset() {
	groupIndex = 0;
	groupOver = false;
	currentLoop = 0;
	loopTime = 0;
}
void anim::AnimationGroup::next() {
	if (getTickSinceEpoch() - startDelayClock > groupClock)
	{
		startDelayClock = getTickSinceEpoch();
		groupIndex++;
		if (groupIndex > groupList.size() - 1)
		{
			if (currentLoop != loopTime - 1)
			{
				groupIndex = 0;
				currentLoop++;
				this->updateSprite();
			}
			else
			{
				groupOver = true;
			}
		}
	}
}
void anim::AnimationGroup::previous() {
	if (getTickSinceEpoch() - startDelayClock > groupClock)
	{
		startDelayClock = getTickSinceEpoch();
		groupIndex--;
		if (groupIndex < 0)
		{
			if (currentLoop != 0)
				groupIndex = groupList.size() - 1;
			else
			{
				groupIndex = 0;
				currentLoop = 0;
			}
		}
	}
	this->updateSprite();
}
void anim::AnimationGroup::forcePrevious() {
	groupIndex--;
}
void anim::AnimationGroup::forceNext() {
	groupIndex++;
}
bool anim::AnimationGroup::isGroupOver() {
	return groupOver;
}
int anim::AnimationGroup::getGroupIndex() {
	return groupIndex;
}
int anim::AnimationGroup::getGroupSize(){
	return groupList.size();
}
std::string anim::AnimationGroup::getGroupName() {
	return groupName;
}


//RESSOURCE MANAGER
anim::RessourceManager::RessourceManager()
{
	textureDatabase = std::map<std::string, sf::Texture*>();
}
sf::Texture* anim::RessourceManager::getTexture(std::string path)
{
	if (textureDatabase.size() != 0)
	{
		if (textureDatabase.find(path) == textureDatabase.end())
		{
			sf::Texture* tempTexture = new sf::Texture;
			if (tempTexture->loadFromFile(path))
			{
				textureDatabase[path] = tempTexture;
				return textureDatabase[path];
			}
			else
			{
				std::cout << "<Error:Animation:RessourceManager>[getTexture] : Can't open file : " << path << std::endl;
			}
		}
		else return textureDatabase[path];
	}
	else
	{
		sf::Texture* tempTexture = new sf::Texture;
		if (tempTexture->loadFromFile(path))
		{
			textureDatabase[path] = tempTexture;
			return textureDatabase[path];
		}
		else
		{
			std::cout << "<Error:Animation:RessourceManager>[getTexture] : Can't open file : " << path << std::endl;
		}
	}
}

//ANIMATION
std::string anim::Animation::getAnimationName() {
	return animationName;
}
void anim::Animation::attachRessourceManager(RessourceManager* rsMan) {
	animatorRsHook = rsMan;
}
void anim::Animation::deleteRessourceManager() {
	animatorRsHook = NULL;
}
float anim::Animation::getAnimationClock() {
	return animationClock;
}
std::string anim::Animation::getCurrentAnimationGroup() {
	return currentGroupName;
}
std::string anim::Animation::getAnimationPlayMode() {
	return animationPlaymode;
}
std::string anim::Animation::getAnimationStatus() {
	return currentStatus;
}
bool anim::Animation::canSkipAnimation() {
	return canSkip;
}
bool anim::Animation::isAnimationOver() {
	return isOver;
}
void anim::Animation::loadAnimation(std::string path, std::string filename) {
	DataParser animFile;
	animFile.parseFile(path + filename, true);
	//Meta
	animFile.getAttribute("Meta", "", "name")->getData(&animationName);
	if (animFile.attributeExists("Meta", "", "clock"))
		animFile.getAttribute("Meta", "", "clock")->getData(&animationClock);
	if (animFile.attributeExists("Meta", "", "play-mode"))
	{
		animFile.getAttribute("Meta", "", "play-mode")->getData(&animationPlaymode);
		if (animationPlaymode == "FORCE")
		{
			canSkip = false;
			animationPlaymode = "ONETIME";
		}
	}
	//Images
	for (unsigned int i = 0; i < animFile.getListSize("Images", "", "ImageList"); i++)
	{
		std::string textureName;
		animFile.getListItem("Images", "", "ImageList", i)->getData(&textureName);
		if (animatorRsHook == NULL)
		{
			sf::Texture* tempTexture = new sf::Texture;
			tempTexture->loadFromFile(path + textureName);
			tempTexture->setSmooth(true);
			animationTextures[i] = tempTexture;
		}
		else
		{
			animationTextures[i] = animatorRsHook->getTexture(path + textureName);
		}
	}
	//Groups
	std::vector<std::string> allGroups;
	allGroups = animFile.getAllComplex("Groups", "");
	for (unsigned int i = 0; i < allGroups.size(); i++)
	{
		anim::AnimationGroup* tempGroup = new anim::AnimationGroup(allGroups[i]);
		animationGroupMap.insert(std::pair<std::string, anim::AnimationGroup*>(allGroups[i], tempGroup));
		for (unsigned int j = 0; j < animFile.getListSize("Groups", allGroups[i], "content"); j++)
		{
			int curNum;
			animFile.getListItem("Groups", allGroups[i], "content", j)->getData(&curNum);
			animationGroupMap[allGroups[i]]->pushTexture(animationTextures[curNum]);
		}
		if (animFile.attributeExists("Groups", allGroups[i], "clock"))
		{
			int curClock;
			animFile.getAttribute("Groups", allGroups[i], "clock")->getData(&curClock);
			animationGroupMap[allGroups[i]]->setGroupClock(curClock);
		}
		animationGroupMap[allGroups[i]]->build();
	}
	//Animation Code
	for (unsigned int i = 0; i < animFile.getListSize("Animation", "", "AnimationCode"); i++)
	{
		std::string curCom;
		std::vector<std::string> vecCurCom;
		animFile.getListItem("Animation", "", "AnimationCode", i)->getData(&curCom);
		fn::String::replaceStringInPlace(curCom, " ", "");
		fn::String::replaceStringInPlace(curCom, ")", "");
		fn::String::replaceStringInPlace(curCom, "(", ",");
		vecCurCom = fn::String::split(curCom, ",");
		animationCode.push_back(vecCurCom);
	}
}
void anim::Animation::applyParameters(ComplexAttribute* parameters) {
	if (parameters->attributeExists("spriteOffsetX")) parameters->getAttribute("spriteOffsetX")->getData(&sprOffsetX);
	if (parameters->attributeExists("spriteOffsetY")) parameters->getAttribute("spriteOffsetY")->getData(&sprOffsetY);
	if (parameters->attributeExists("priority")) parameters->getAttribute("priority")->getData(&priority);
}
void anim::Animation::playAnimation() {
	if (animationCode.size() > 0)
	{
		if (codeIndex > animationCode.size() - 1 && animationPlaymode != "ONETIME")
			codeIndex = 0;
		if (getTickSinceEpoch() - lastTick > animationClock)
		{
			lastTick = getTickSinceEpoch();
			if (getTickSinceEpoch() - startDelay > currentDelay)
			{
				if (askCommand)
				{
					std::vector<std::string> currentCommand;
					currentCommand = animationCode[codeIndex];
					if (currentCommand[0] == "DELAY")
					{
						askCommand = true;
						currentDelay = std::stoi(currentCommand[1]);
						startDelay = getTickSinceEpoch();
						if (animationPlaymode != "ONETIME" && !(codeIndex >= animationCode.size() - 1))
							codeIndex++;
						else
							isOver = true;
					}
					else if (currentCommand[0] == "PLAY_GROUP")
					{
						if (currentGroupName != "NONE")
							animationGroupMap[currentGroupName]->reset();
						askCommand = false;
						currentGroupName = currentCommand[1];
						if (currentCommand.size() == 3)
						{
							loopTime = stoi(currentCommand[2]);
							animationGroupMap[currentGroupName]->setGroupLoop(loopTime);
						}
						else
							animationGroupMap[currentGroupName]->setGroupLoop(1);
					}
					else if (currentCommand[0] == "CALL")
					{
						askCommand = false;
						std::string callGroup;
						callGroup = currentCommand[1];
						fn::String::replaceStringInPlace(callGroup, "'", "");
						currentStatus = "CALL:" + callGroup;
					}
				}
				if (currentGroupName != "NONE")
				{
					animationGroupMap[currentGroupName]->next();
					if (animationGroupMap[currentGroupName]->isGroupOver())
					{
						if (animationPlaymode != "ONETIME")
						{
							askCommand = true;
							animationGroupMap[currentGroupName]->reset();
							codeIndex++;
						}
						else if (animationPlaymode == "ONETIME")
						{
							if (codeIndex < animationCode.size() - 1)
							{
								askCommand = true;
								animationGroupMap[currentGroupName]->reset();
								codeIndex++;
							}
							else
							{
								animationGroupMap[currentGroupName]->forcePrevious();
								isOver = true;
							}
						}	
					}
					else
						animationGroupMap[currentGroupName]->updateSprite();
				}
			}
		}
	}
}
void anim::Animation::resetAnimation() {
	for (std::map<std::string, AnimationGroup*>::iterator it = animationGroupMap.begin(); it != animationGroupMap.end(); ++it) {
		it->second->reset();
	}
	startDelay = 0;
	currentDelay = 0;
	loopTime = 0;
	currentStatus = "PLAY";
	codeIndex = 0;
	askCommand = true;
	isOver = false;
}
sf::Texture* anim::Animation::getTextureAtIndex(int index) {
	return animationTextures[index];
}
sf::Sprite* anim::Animation::getSprite() {
	return animationGroupMap[currentGroupName]->returnSprite();
}
sf::IntRect* anim::Animation::getSpriteRect() {
	return animationGroupMap[currentGroupName]->getSpriteRect();
}
int anim::Animation::getSpriteOffsetX() {
	return sprOffsetX;
}
int anim::Animation::getSpriteOffsetY() {
	return sprOffsetY;
}
int anim::Animation::getPriority() {
	return priority;
}

//DIRTY ANIMATION
void anim::DirtyAnimation::attachRessourceManager(anim::RessourceManager* rsMan) {
	animatorRsHook = rsMan;
}
void anim::DirtyAnimation::deleteRessourceManager() {
	animatorRsHook = NULL;
}
void anim::DirtyAnimation::setAnimationClock(int animClock) {
	animationClock = animClock;
}
float anim::DirtyAnimation::getAnimationClock() {
	return animationClock;
}
void anim::DirtyAnimation::loadAnimation(std::string path) {
	std::vector<std::string> imageList = fn::File::listFileInDir(path);
	for (unsigned int i = 0; i < imageList.size(); i++)
	{
		std::string textureName = imageList[i];
		if (animatorRsHook == NULL)
		{
			sf::Texture* tempTexture = new sf::Texture;
			tempTexture->loadFromFile(path + "/" + textureName);
			tempTexture->setSmooth(true);
			animationTextures.push_back(tempTexture);
		}
		else
			animationTextures.push_back(animatorRsHook->getTexture(path + "/" + textureName));
	}
}
void anim::DirtyAnimation::update() {
	oldTextureIndex = textureIndex;
	textureIndex++;
	if (textureIndex >= animationTextures.size())
		textureIndex = 0;
}
void anim::DirtyAnimation::setIndex(int index) {
	textureIndex = index;
}
int anim::DirtyAnimation::getIndex() {
	return textureIndex;
}
bool anim::DirtyAnimation::indexChanged() {
	return (oldTextureIndex != textureIndex || noTextureReturned);
}
sf::Texture* anim::DirtyAnimation::getTexture() {
	noTextureReturned = false;
	return animationTextures[textureIndex];
}
sf::Texture* anim::DirtyAnimation::getTextureAtIndex(int index) {
	noTextureReturned = false;
	return animationTextures[index];
}

//ANIMATOR
void anim::Animator::setPath(std::string path) {
	animationPath = path;
}
std::string anim::Animator::getKey() {
	return currentAnimationName;
}
void anim::Animator::setKey(std::string key) {
	bool canChange = true;
	if (fullAnimSet.find(key) == fullAnimSet.end())
		std::cout << "Can't find key : " << key << std::endl;
	else
	{
		/*if (currentAnimationName != "NONE")
		{
			if (!fullAnimSet[currentAnimationName]->canSkipAnimation() && !fullAnimSet[currentAnimationName]->isAnimationOver())
			{
				canChange = false;
			}
		}*/
		if (key != currentAnimationName && canChange)
		{
			bool changeAnim = false;
			if (currentAnimation != NULL)
			{
				if (currentAnimation->isAnimationOver())
				{
					changeAnim = true;
				}
				else if (fullAnimSet[key]->getPriority() >= currentAnimation->getPriority())
				{
					changeAnim = true;
				}
			}
			else
				changeAnim = true;
			if (changeAnim)
			{
				if (currentAnimationName != "NONE")
					fullAnimSet[currentAnimationName]->resetAnimation();
				currentAnimationName = key;
				currentAnimation = fullAnimSet[currentAnimationName];
			}
		}
	}
}
void anim::Animator::loadAnimator() {
	std::vector<std::string> listDir = fn::File::listDirInDir(animationPath);
	std::vector<std::string> allFiles = fn::File::listFileInDir(animationPath);
	std::map<std::string, ComplexAttribute*> animationParameters;
	bool hasCfgFile;
	if (fn::Vector::isInList(std::string("animator.cfg.msd"), allFiles))
	{
		hasCfgFile = true;
		DataParser animatorCfgFile;
		animatorCfgFile.parseFile(animationPath + "/" + "animator.cfg.msd");
		std::vector<std::string> allParamAnim = animatorCfgFile.getAllComplex("Animator", "");
		for (unsigned int i = 0; i < allParamAnim.size(); i++)
			animationParameters[allParamAnim[i]] = animatorCfgFile.getComplexAttribute("Animator", "", allParamAnim[i]);
	}
	for (unsigned int i = 0; i < listDir.size(); i++)
	{
		allAnimationNames.push_back(listDir[i]);
		anim::Animation* tempAnim = new anim::Animation;
		if (ressourceManagerHook != NULL)
			tempAnim->attachRessourceManager(ressourceManagerHook);
		tempAnim->loadAnimation(animationPath + "/" + listDir[i] + "/", listDir[i] + ".ani.msd");
		if (animationParameters.find(listDir[i]) != animationParameters.end() && animationParameters.find("all") != animationParameters.end())
		{
			tempAnim->applyParameters(animationParameters["all"]);
			tempAnim->applyParameters(animationParameters[listDir[i]]);
		}
		else if (animationParameters.find(listDir[i]) != animationParameters.end())
			tempAnim->applyParameters(animationParameters[listDir[i]]);
		else if (animationParameters.find("all") != animationParameters.end())
			tempAnim->applyParameters(animationParameters["all"]);
		fullAnimSet[tempAnim->getAnimationName()] = tempAnim;
	}
}
void anim::Animator::update() {
	std::vector<std::string> animStatusCommand;
	animStatusCommand = fn::String::split(currentAnimation->getAnimationStatus(), ":");
	if (animStatusCommand[0] == "CALL")
	{
		currentAnimation->resetAnimation();
		currentAnimationName = animStatusCommand[1];
		currentAnimation = fullAnimSet[currentAnimationName];
	}
	animStatusCommand = fn::String::split(currentAnimation->getAnimationStatus(), ":");
	if (animStatusCommand[0] == "PLAY")
		currentAnimation->playAnimation();
}
sf::Sprite* anim::Animator::getSprite() {
	lastSpriteAddress = currentAnimation->getSprite();
	lastRect = *currentAnimation->getSpriteRect();
	return currentAnimation->getSprite();
}
sf::Texture* anim::Animator::getTextureAtKey(std::string key, int index) {
	return fullAnimSet[key]->getTextureAtIndex(index);
}
bool anim::Animator::textureChanged() {
	return (currentAnimation->getSprite() != lastSpriteAddress || lastRect != *currentAnimation->getSpriteRect());
}
void anim::Animator::attachRessourceManager(RessourceManager* rsman) {
	ressourceManagerHook = rsman;
}
void anim::Animator::deleteRessourceManager() {
	ressourceManagerHook = NULL;
}
int anim::Animator::getSpriteOffsetX() {
	return currentAnimation->getSpriteOffsetX();
}
int anim::Animator::getSpriteOffsetY() {
	return currentAnimation->getSpriteOffsetY();
}