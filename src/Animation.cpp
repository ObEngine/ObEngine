//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Animation.hpp"

//ANIMATION GROUP
namespace mse
{
	namespace Animation
	{
		AnimationGroup::AnimationGroup(std::string pgroupname)
		{
			this->groupName = pgroupname;
		}
		void AnimationGroup::build()
		{
			currentSprite = sf::Sprite(*groupList[0]);
		}
		void AnimationGroup::setGroupClock(int clock)
		{
			this->groupClock = clock;
		}
		void AnimationGroup::setGroupLoop(int loops)
		{
			this->loopTime = loops;
		}
		void AnimationGroup::pushTexture(sf::Texture* texture)
		{
			groupList.push_back(texture);
			groupSize++;
		}
		void AnimationGroup::removeTextureByIndex(int index)
		{
			if (groupSize > 0)
			{
				groupList.erase(groupList.begin() + index);
				groupSize--;
			}
		}
		sf::Sprite* AnimationGroup::returnSprite()
		{
			return &currentSprite;
		}
		void AnimationGroup::updateSprite()
		{
			std::cout << "Updating texture << [" << groupIndex << "] : " << groupList[groupIndex]->getSize().x << "," << groupList[groupIndex]->getSize().y << std::endl;
			currentSprite.setTexture(*groupList[groupIndex], true);
		}
		void AnimationGroup::reset()
		{
			groupIndex = 0;
			groupOver = false;
			currentLoop = 0;
			loopTime = 0;
		}
		void AnimationGroup::next()
		{
			if (Time::getTickSinceEpoch() - startDelayClock > groupClock)
			{
				startDelayClock = Time::getTickSinceEpoch();
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
		void AnimationGroup::previous()
		{
			if (Time::getTickSinceEpoch() - startDelayClock > groupClock)
			{
				startDelayClock = Time::getTickSinceEpoch();
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
		void AnimationGroup::forcePrevious()
		{
			groupIndex--;
		}
		void AnimationGroup::forceNext()
		{
			groupIndex++;
		}
		bool AnimationGroup::isGroupOver()
		{
			return groupOver;
		}
		int AnimationGroup::getGroupIndex()
		{
			return groupIndex;
		}
		int AnimationGroup::getGroupSize() {
			return groupList.size();
		}
		std::string AnimationGroup::getGroupName()
		{
			return groupName;
		}
		int AnimationGroup::getGroupClock()
		{
			return groupClock;
		}


		//RESSOURCE MANAGER
		RessourceManager* RessourceManager::instance = nullptr;
		RessourceManager::RessourceManager()
		{
			textureDatabase = std::map<std::string, sf::Texture*>();
		}
		RessourceManager* RessourceManager::GetInstance()
		{
			if (instance == nullptr)
				instance = new RessourceManager();
			return instance;
		}
		RessourceManager::~RessourceManager()
		{
			for (auto it = textureDatabase.begin(); it != textureDatabase.end(); it++)
				delete it->second;
		}
		sf::Texture* RessourceManager::getTexture(std::string path)
		{
			if (textureDatabase.size() != 0)
			{
				if (textureDatabase.find(path) == textureDatabase.end())
				{
					sf::Texture* tempTexture = new sf::Texture(); System::Path(path).loadResource(tempTexture, System::Loaders::textureLoader);
					if (tempTexture != nullptr)
					{
						tempTexture->setSmooth(true);
						textureDatabase[path] = tempTexture;
						return textureDatabase[path];
					}
					else
					{
						std::cout << "<Error:Animation:RessourceManager>[getTexture] : Can't open file : " << path << std::endl;
					}
				}
				else
				{
					return textureDatabase[path];
				}
			}
			else
			{
				sf::Texture* tempTexture = new sf::Texture(); System::Path(path).loadResource(tempTexture, System::Loaders::textureLoader);
				if (tempTexture != nullptr)
				{
					tempTexture->setSmooth(true);
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
		std::string Animation::Animation::getAnimationName()
		{
			return animationName;
		}
		void Animation::Animation::attachRessourceManager(RessourceManager* rsMan)
		{
			animatorRsHook = rsMan;
		}
		void Animation::Animation::deleteRessourceManager()
		{
			animatorRsHook = NULL;
		}
		float Animation::Animation::getAnimationClock()
		{
			return animationClock;
		}
		AnimationGroup* Animation::Animation::getAnimationGroup(std::string groupname)
		{
			if (animationGroupMap.find(groupname) != animationGroupMap.end())
				return animationGroupMap[groupname];
			else
				std::cout << "<Error:Animation:Animation>[getAnimationGroup] : Can't find AnimationGroup : " << groupname << std::endl;
			return nullptr;
		}
		std::string Animation::Animation::getCurrentAnimationGroup()
		{
			return currentGroupName;
		}
		std::vector<std::string> Animation::Animation::getAllAnimationGroupName()
		{
			std::vector<std::string> rname;
			for (auto it = animationGroupMap.begin(); it != animationGroupMap.end(); it++)
			{
				rname.push_back(it->first);
			}
			return rname;
		}
		std::string Animation::Animation::getAnimationPlayMode()
		{
			return animationPlaymode;
		}
		std::string Animation::Animation::getAnimationStatus()
		{
			return currentStatus;
		}
		bool Animation::Animation::isAnimationOver()
		{
			return isOver;
		}
		void Animation::Animation::loadAnimation(System::Path path, std::string filename)
		{
			Data::DataParser animFile;
			animFile.hookNavigator(new Data::DataParserNavigator());
			path.add(filename).loadResource(&animFile, System::Loaders::dataLoader);
			//Meta
			animFile.accessNavigator()->setCurrentRootAttribute("Meta");
			animationName = animFile.getBaseAttribute("name")->get<std::string>();
			if (animFile.containsBaseAttribute("clock"))
				animationClock = animFile.getBaseAttribute("clock")->get<int>();
			if (animFile.containsBaseAttribute("play-mode"))
				animationPlaymode = animFile.getBaseAttribute("play-mode")->get<std::string>();
			//Images
			animFile.accessNavigator()->setCurrentRootAttribute("Images");
			for (unsigned int i = 0; i < animFile.getListSize("ImageList"); i++)
			{
				std::string textureName;
				textureName = animFile.getListItem("ImageList", i)->get<std::string>();
				if (animatorRsHook == NULL)
				{
					sf::Texture* tempTexture = new sf::Texture(); path.add(textureName).loadResource(tempTexture, System::Loaders::textureLoader);
					if (tempTexture != nullptr)
					{
						tempTexture->setSmooth(true);
						animationTextures[i] = tempTexture;
					}
					else
						std::cout << "<Error:Animation:Animation>[loadAnimation] : Can't open file : " << path.toString() << std::endl;
				}
				else
					animationTextures[i] = animatorRsHook->getTexture(path.add(textureName).toString());
			}
			//Groups
			animFile.accessNavigator()->setCurrentRootAttribute("Groups");
			std::vector<std::string> allGroups = animFile.getAllComplexAttributes();
			for (unsigned int i = 0; i < allGroups.size(); i++)
			{
				AnimationGroup* tempGroup = new AnimationGroup(allGroups[i]);
				animationGroupMap.insert(std::pair<std::string, AnimationGroup*>(allGroups[i], tempGroup));
				animFile.accessNavigator()->setCurrentPath(allGroups[i]);
				for (unsigned int j = 0; j < animFile.getListSize("content"); j++)
					animationGroupMap[allGroups[i]]->pushTexture(animationTextures[animFile.getListItem("content", j)->get<int>()]);
				if (animFile.containsBaseAttribute("clock"))
					animationGroupMap[allGroups[i]]->setGroupClock(animFile.getBaseAttribute("clock")->get<int>());
				else
					animationGroupMap[allGroups[i]]->setGroupClock(animationClock);
				animationGroupMap[allGroups[i]]->build();
			}
			//Animation Code
			animFile.accessNavigator()->setCurrentRootAttribute("Animation");
			for (unsigned int i = 0; i < animFile.getListSize("AnimationCode"); i++)
			{
				std::string curCom = animFile.getListItem("AnimationCode", i)->get<std::string>();
				std::vector<std::string> vecCurCom;
				Functions::String::replaceStringInPlace(curCom, " ", "");
				Functions::String::replaceStringInPlace(curCom, ")", "");
				Functions::String::replaceStringInPlace(curCom, "(", ",");
				vecCurCom = Functions::String::split(curCom, ",");
				animationCode.push_back(vecCurCom);
			}
		}
		void Animation::Animation::applyParameters(Data::ComplexAttribute* parameters)
		{
			if (parameters->containsBaseAttribute("spriteOffsetX")) sprOffsetX = parameters->getBaseAttribute("spriteOffsetX")->get<int>();
			if (parameters->containsBaseAttribute("spriteOffsetY")) sprOffsetY = parameters->getBaseAttribute("spriteOffsetY")->get<int>();
			if (parameters->containsBaseAttribute("priority")) priority = parameters->getBaseAttribute("priority")->get<int>();
		}
		void Animation::Animation::playAnimation()
		{
			if (animationCode.size() > 0)
			{
				if (codeIndex > animationCode.size() - 1 && animationPlaymode != "ONETIME")
					codeIndex = 0;
				if (Time::getTickSinceEpoch() - startDelay > currentDelay)
				{
					std::cout << "Play animation : " << animationName << std::endl;
					if (askCommand)
					{
						std::vector<std::string> currentCommand;
						currentCommand = animationCode[codeIndex];
						if (currentCommand[0] == "DELAY")
						{
							askCommand = true;
							currentDelay = std::stoi(currentCommand[1]);
							startDelay = Time::getTickSinceEpoch();
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
							Functions::String::replaceStringInPlace(callGroup, "'", "");
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
		void Animation::Animation::resetAnimation()
		{
			for (std::map<std::string, AnimationGroup*>::iterator it = animationGroupMap.begin(); it != animationGroupMap.end(); ++it) {
				it->second->reset();
			}
			loopTime = 0;
			currentStatus = "PLAY";
			codeIndex = 0;
			askCommand = true;
			isOver = false;
		}
		sf::Texture* Animation::Animation::getTextureAtIndex(int index)
		{
			return animationTextures[index];
		}
		sf::Sprite* Animation::Animation::getSprite()
		{
			return animationGroupMap[currentGroupName]->returnSprite();
		}
		int Animation::Animation::getSpriteOffsetX()
		{
			return sprOffsetX;
		}
		int Animation::Animation::getSpriteOffsetY()
		{
			return sprOffsetY;
		}
		int Animation::Animation::getPriority()
		{
			return priority;
		}

		//ANIMATOR
		Animator::Animator()
		{
		}
		Animator::Animator(System::Path path)
		{
			animationPath = path;
		}
		void Animator::setPath(System::Path path)
		{
			animationPath = path;
		}
		void Animator::setPath(std::string path)
		{
			animationPath = System::Path(path);
		}
		void Animator::clear(bool clearMemory)
		{
			if (clearMemory) {
				for (auto it = fullAnimSet.begin(); it != fullAnimSet.end(); it++)
					delete it->second;
			}
			fullAnimSet.clear();
			currentAnimation = nullptr;
			allAnimationNames.clear();
			globalClock = 0;
			currentAnimationName = "NONE";
			animationBehaviour = "";
			animationPath = System::Path("");
			currentNameIndex = 0;
			lastSpriteAddress = nullptr;
		}
		Animation* Animator::getAnimation(std::string animationName)
		{
			if (fullAnimSet.find(animationName) != fullAnimSet.end())
				return fullAnimSet[animationName];
			else
				std::cout << "<Error:Animation:Animator>[getAnimation] : Can't find Animation : " << animationName << std::endl;
			return nullptr;
		}
		std::vector<std::string> Animator::getAllAnimationName()
		{
			return allAnimationNames;
		}
		std::string Animator::getKey()
		{
			return currentAnimationName;
		}
		void Animator::setKey(std::string key)
		{
			std::cout << "Trying to set Key" << key << std::endl;
			if (fullAnimSet.find(key) == fullAnimSet.end())
				std::cout << "<Error:Animation:Animator>[setKey] : Can't find key : " << key << " for Animator : " << animationPath.toString() << std::endl;
			else
			{
				if (key != currentAnimationName)
				{
					std::cout << "Animation switch" << std::endl;
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
		void Animator::loadAnimator()
		{
			std::vector<std::string> listDir;
			animationPath.loadResource(&listDir, System::Loaders::dirPathLoader);
			std::vector<std::string> allFiles;
			animationPath.loadResource(&allFiles, System::Loaders::filePathLoader);
			Data::DataParser animatorCfgFile;
			std::map<std::string, Data::ComplexAttribute*> animationParameters;
			bool hasCfgFile;
			if (Functions::Vector::isInList(std::string("animator.cfg.msd"), allFiles))
			{
				hasCfgFile = true;
				System::Path(animationPath.toString() + "/" + "animator.cfg.msd").loadResource(&animatorCfgFile, System::Loaders::dataLoader);
				std::vector<std::string> allParamAnim = animatorCfgFile.getAllComplexAttributes("Animator");
				for (unsigned int i = 0; i < allParamAnim.size(); i++)
					animationParameters[allParamAnim[i]] = animatorCfgFile.getComplexAttribute("Animator", allParamAnim[i]);
			}
			for (unsigned int i = 0; i < listDir.size(); i++)
			{
				std::cout << "Loading Animation : " << listDir[i] << std::endl;
				allAnimationNames.push_back(listDir[i]);
				Animation* tempAnim = new Animation;
				if (ressourceManagerHook != NULL)
					tempAnim->attachRessourceManager(ressourceManagerHook);
				tempAnim->loadAnimation(animationPath.add(listDir[i]), listDir[i] + ".ani.msd");
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
		void Animator::update()
		{
			std::vector<std::string> animStatusCommand;
			if (currentAnimation != nullptr)
				animStatusCommand = Functions::String::split(currentAnimation->getAnimationStatus(), ":");
			else
				std::cout << "<Error:Animation:Animator>[update] : Current Animation of Animator : " << animationPath.toString() << " is NULL" << std::endl;
			if (animStatusCommand[0] == "CALL")
			{
				currentAnimation->resetAnimation();
				currentAnimationName = animStatusCommand[1];
				currentAnimation = fullAnimSet[currentAnimationName];
			}
			animStatusCommand = Functions::String::split(currentAnimation->getAnimationStatus(), ":");
			if (animStatusCommand[0] == "PLAY")
				currentAnimation->playAnimation();
		}
		sf::Sprite* Animator::getSprite()
		{
			lastSpriteAddress = currentAnimation->getSprite();
			//lastRect = *currentAnimation->getSpriteRect();
			return currentAnimation->getSprite();
		}
		sf::Texture* Animator::getTextureAtKey(std::string key, int index)
		{
			return fullAnimSet[key]->getTextureAtIndex(index);
		}
		bool Animator::textureChanged()
		{
			return (currentAnimation->getSprite() != lastSpriteAddress);
		}
		void Animator::attachRessourceManager(RessourceManager* rsman)
		{
			ressourceManagerHook = rsman;
		}
		void Animator::deleteRessourceManager()
		{
			ressourceManagerHook = NULL;
		}
		int Animator::getSpriteOffsetX()
		{
			return currentAnimation->getSpriteOffsetX();
		}
		int Animator::getSpriteOffsetY()
		{
			return currentAnimation->getSpriteOffsetY();
		}
	}
}