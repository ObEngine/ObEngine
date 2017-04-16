//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Animation.hpp"

//ANIMATION GROUP
namespace obe
{
	namespace Animation
	{
		AnimationGroup::AnimationGroup(std::string pgroupname)
		{
			m_groupName = pgroupname;
		}

		void AnimationGroup::build()
		{
			m_currentSprite = sf::Sprite(*m_groupList[0]);
		}

		void AnimationGroup::setGroupClock(const int& clock)
		{
			m_groupClock = clock;
		}

		void AnimationGroup::setGroupLoop(const int& loops)
		{
			m_loopTime = loops;
		}

		void AnimationGroup::pushTexture(sf::Texture* texture)
		{
			m_groupList.push_back(texture);
			m_groupSize++;
		}

		void AnimationGroup::removeTextureByIndex(const int& index)
		{
			if (m_groupSize > 0)
			{
				m_groupList.erase(m_groupList.begin() + index);
				m_groupSize--;
			}
		}

		sf::Sprite* AnimationGroup::returnSprite()
		{
			return &m_currentSprite;
		}

		void AnimationGroup::updateSprite()
		{
			m_currentSprite.setTexture(*m_groupList[m_groupIndex], true);
		}

		void AnimationGroup::reset()
		{
			m_groupIndex = 0;
			m_groupOver = false;
			m_currentLoop = 0;
			m_loopTime = 0;
		}

		void AnimationGroup::next()
		{
			if (Time::getTickSinceEpoch() - m_startDelayClock > m_groupClock)
			{
				m_startDelayClock = Time::getTickSinceEpoch();
				m_groupIndex++;
				if (m_groupIndex > m_groupList.size() - 1)
				{
					if (m_currentLoop != m_loopTime - 1)
					{
						m_groupIndex = 0;
						m_currentLoop++;
						this->updateSprite();
					}
					else
					{
						m_groupOver = true;
					}
				}
			}
		}

		void AnimationGroup::previous()
		{
			if (Time::getTickSinceEpoch() - m_startDelayClock > m_groupClock)
			{
				m_startDelayClock = Time::getTickSinceEpoch();
				m_groupIndex--;
				if (m_groupIndex < 0)
				{
					if (m_currentLoop != 0)
						m_groupIndex = m_groupList.size() - 1;
					else
					{
						m_groupIndex = 0;
						m_currentLoop = 0;
					}
				}
			}
			this->updateSprite();
		}

		void AnimationGroup::forcePrevious()
		{
			m_groupIndex--;
		}

		void AnimationGroup::forceNext()
		{
			m_groupIndex++;
		}

		bool AnimationGroup::isGroupOver() const
		{
			return m_groupOver;
		}

		int AnimationGroup::getGroupIndex() const
		{
			return m_groupIndex;
		}

		int AnimationGroup::getGroupSize() const
		{
			return m_groupList.size();
		}

		std::string AnimationGroup::getGroupName() const
		{
			return m_groupName;
		}

		int AnimationGroup::getGroupClock() const
		{
			return m_groupClock;
		}


		//RESSOURCE MANAGER
		RessourceManager* RessourceManager::instance = nullptr;
		RessourceManager* RessourceManager::GetInstance()
		{
			if (instance == nullptr)
				instance = new RessourceManager();
			return instance;
		}

		sf::Texture* RessourceManager::getTexture(std::string path)
		{
			if (textureDatabase.size() != 0)
			{
				if (textureDatabase.find(path) == textureDatabase.end())
				{
					std::unique_ptr<sf::Texture> tempTexture = std::make_unique<sf::Texture>();
					System::Path(path).loadResource(tempTexture.get(), System::Loaders::textureLoader);
					if (tempTexture != nullptr)
					{
						tempTexture->setSmooth(true);
						textureDatabase[path] = std::move(tempTexture);
						return textureDatabase[path].get();
					}
					throw aube::ErrorHandler::Raise("ObEngine.Animation.RessourceManager.LoadTexture_NETD", {{"file", path}});
				}
				else
				{
					return textureDatabase[path].get();;
				}
			}
			else
			{
				std::unique_ptr<sf::Texture> tempTexture = std::make_unique<sf::Texture>();
				System::Path(path).loadResource(tempTexture.get(), System::Loaders::textureLoader);
				if (tempTexture != nullptr)
				{
					tempTexture->setSmooth(true);
					textureDatabase[path] = std::move(tempTexture);
					return textureDatabase[path].get();
				}
				throw aube::ErrorHandler::Raise("ObEngine.Animation.RessourceManager.LoadTexture_ETD", {{"file", path}});
			}
		}

		//ANIMATION
		std::string Animation::Animation::getAnimationName() const
		{
			return animationName;
		}

		float Animation::Animation::getAnimationClock() const
		{
			return animationClock;
		}

		AnimationGroup* Animation::Animation::getAnimationGroup(std::string groupname)
		{
			if (animationGroupMap.find(groupname) != animationGroupMap.end())
				return animationGroupMap[groupname].get();
			throw aube::ErrorHandler::Raise("ObEngine.Animation.Animation.AnimationGroupNotFound", {{"animation", animationName}, {"group", groupname}});
		}

		std::string Animation::Animation::getCurrentAnimationGroup() const
		{
			return currentGroupName;
		}

		std::vector<std::string> Animation::Animation::getAllAnimationGroupName()
		{
			std::vector<std::string> rname;
			for (auto it = animationGroupMap.begin(); it != animationGroupMap.end(); ++it)
				rname.push_back(it->first);
			return rname;
		}

		std::string Animation::Animation::getAnimationPlayMode() const
		{
			return animationPlaymode;
		}

		std::string Animation::Animation::getAnimationStatus() const
		{
			return currentStatus;
		}

		bool Animation::Animation::isAnimationOver() const
		{
			return isOver;
		}

		void Animation::Animation::loadAnimation(System::Path path, std::string filename)
		{
			vili::DataParser animFile;
			path.add(filename).loadResource(&animFile, System::Loaders::dataLoader);
			//Meta
			vili::ComplexAttribute* meta = animFile.at("Meta");
			animationName = meta->at<vili::BaseAttribute>("name")->get<std::string>();
			if (meta->contains(vili::Types::BaseAttribute, "clock"))
				animationClock = meta->at<vili::BaseAttribute>("clock")->get<int>();
			if (meta->contains(vili::Types::BaseAttribute, "play-mode"))
				animationPlaymode = meta->at<vili::BaseAttribute>("play-mode")->get<std::string>();
			//Images
			vili::ListAttribute* imageList = animFile.at<vili::ListAttribute>("Images", "ImageList");
			std::string model = "";
			if (animFile.at("Images")->contains(vili::Types::BaseAttribute, "model"))
			{
				model = animFile.at("Images")->getBaseAttribute("model")->get<std::string>();
			}
			for (unsigned int i = 0; i < imageList->getSize(); i++)
			{
				std::string textureName = "";
				if (imageList->get(i)->getDataType() == vili::Types::Int && model != "")
					textureName = Functions::String::replaceString(model, "%s", std::to_string(imageList->get(i)->get<int>()));
				else if (imageList->get(i)->getDataType() == vili::Types::String)
					textureName = imageList->get(i)->get<std::string>();
				animationTextures[i] = RessourceManager::GetInstance()->getTexture(path.add(textureName).toString());
			}
			//Groups
			vili::ComplexAttribute* groups = animFile.at("Groups");
			for (std::string complexName : groups->getAll(vili::Types::ComplexAttribute))
			{
				animationGroupMap.emplace(complexName, std::make_unique<AnimationGroup>(complexName));
				vili::ComplexAttribute* currentGroup = groups->at(complexName);
				for (vili::BaseAttribute* currentTexture : *currentGroup->at<vili::ListAttribute>("content"))
					animationGroupMap[complexName]->pushTexture(animationTextures[*currentTexture]);
				if (currentGroup->contains(vili::Types::BaseAttribute, "clock"))
					animationGroupMap[complexName]->setGroupClock(*currentGroup->at<vili::BaseAttribute>("clock"));
				else
					animationGroupMap[complexName]->setGroupClock(animationClock);
				animationGroupMap[complexName]->build();
			}
			//Animation Code
			vili::ComplexAttribute* animation = animFile.at("Animation");
			for (vili::BaseAttribute* command : *animation->at<vili::ListAttribute>("AnimationCode"))
			{
				std::string curCom = command->get<std::string>();
				std::vector<std::string> vecCurCom;
				Functions::String::replaceStringInPlace(curCom, " ", "");
				Functions::String::replaceStringInPlace(curCom, ")", "");
				Functions::String::replaceStringInPlace(curCom, "(", ",");
				vecCurCom = Functions::String::split(curCom, ",");
				animationCode.push_back(vecCurCom);
			}
		}

		void Animation::Animation::applyParameters(vili::ComplexAttribute* parameters)
		{
			if (parameters->contains(vili::Types::BaseAttribute, "spriteOffsetX"))
				sprOffsetX = parameters->at<vili::BaseAttribute>("spriteOffsetX")->get<int>();
			if (parameters->contains(vili::Types::BaseAttribute, "spriteOffsetY"))
				sprOffsetY = parameters->at<vili::BaseAttribute>("spriteOffsetY")->get<int>();
			if (parameters->contains(vili::Types::BaseAttribute, "priority"))
				priority = parameters->at<vili::BaseAttribute>("priority")->get<int>();
		}

		void Animation::Animation::playAnimation()
		{
			if (animationCode.size() > 0)
			{
				if (codeIndex > animationCode.size() - 1 && animationPlaymode != "ONETIME")
					codeIndex = 0;
				if (Time::getTickSinceEpoch() - startDelay > currentDelay)
				{
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
			for (auto it = animationGroupMap.begin(); it != animationGroupMap.end(); ++it)
				it->second->reset();
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

		int Animation::Animation::getSpriteOffsetX() const
		{
			return sprOffsetX;
		}

		int Animation::Animation::getSpriteOffsetY() const
		{
			return sprOffsetY;
		}

		int Animation::Animation::getPriority() const
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
				return fullAnimSet[animationName].get();
			throw aube::ErrorHandler::Raise("ObEngine.Animation.Animator.AnimationNotFound", 
				{ { "function", "getAnimation" }, {"animation", animationName}, {"%animator", animationPath.toString()} 
			});
		}

		std::vector<std::string> Animator::getAllAnimationName() const
		{
			return allAnimationNames;
		}

		std::string Animator::getKey() const
		{
			return currentAnimationName;
		}

		void Animator::setKey(std::string key)
		{
			if (fullAnimSet.find(key) == fullAnimSet.end())
				throw aube::ErrorHandler::Raise("ObEngine.Animation.Animator.AnimationNotFound", {
					{"function", "setKey"}, { "animation", key },{ "%animator", animationPath.toString() } 
				});
			if (key != currentAnimationName)
			{
				bool changeAnim = false;
				if (currentAnimation != nullptr)
				{
					if (currentAnimation->isAnimationOver())
						changeAnim = true;
					else if (fullAnimSet[key]->getPriority() >= currentAnimation->getPriority())
						changeAnim = true;
				}
				else
					changeAnim = true;
				if (changeAnim)
				{
					if (currentAnimationName != "NONE")
						fullAnimSet[currentAnimationName]->resetAnimation();
					currentAnimationName = key;
					currentAnimation = fullAnimSet[currentAnimationName].get();
				}
			}
		}

		void Animator::loadAnimator()
		{
			std::vector<std::string> listDir;
			animationPath.loadResource(&listDir, System::Loaders::dirPathLoader);
			std::vector<std::string> allFiles;
			animationPath.loadResource(&allFiles, System::Loaders::filePathLoader);
			vili::DataParser animatorCfgFile;
			std::map<std::string, vili::ComplexAttribute*> animationParameters;
			bool hasCfgFile;
			if (Functions::Vector::isInList(std::string("animator.cfg.vili"), allFiles))
			{
				hasCfgFile = true;
				System::Path(animationPath.toString() + "/" + "animator.cfg.vili").loadResource(&animatorCfgFile, System::Loaders::dataLoader);
				for (std::string& currentAnimParameters : animatorCfgFile.at("Animator")->getAll(vili::Types::ComplexAttribute))
					animationParameters[currentAnimParameters] = animatorCfgFile.at("Animator", currentAnimParameters);
			}
			for (unsigned int i = 0; i < listDir.size(); i++)
			{
				allAnimationNames.push_back(listDir[i]);
				std::unique_ptr<Animation> tempAnim = std::make_unique<Animation>();
				tempAnim->loadAnimation(animationPath.add(listDir[i]), listDir[i] + ".ani.vili");
				if (animationParameters.find(listDir[i]) != animationParameters.end() && animationParameters.find("all") != animationParameters.end())
				{
					tempAnim->applyParameters(animationParameters["all"]);
					tempAnim->applyParameters(animationParameters[listDir[i]]);
				}
				else if (animationParameters.find(listDir[i]) != animationParameters.end())
					tempAnim->applyParameters(animationParameters[listDir[i]]);
				else if (animationParameters.find("all") != animationParameters.end())
					tempAnim->applyParameters(animationParameters["all"]);
				fullAnimSet[tempAnim->getAnimationName()] = std::move(tempAnim);
			}
		}

		void Animator::update()
		{
			std::vector<std::string> animStatusCommand;
			if (currentAnimation != nullptr)
				animStatusCommand = Functions::String::split(currentAnimation->getAnimationStatus(), ":");
			else
				throw aube::ErrorHandler::Raise("ObEngine.Animator.Animator.UpdateNullAnimation", { {"animator", animationPath.toString() } });
			if (animStatusCommand[0] == "CALL")
			{
				currentAnimation->resetAnimation();
				currentAnimationName = animStatusCommand[1];
				currentAnimation = fullAnimSet[currentAnimationName].get();
			}
			animStatusCommand = Functions::String::split(currentAnimation->getAnimationStatus(), ":");
			if (animStatusCommand[0] == "PLAY")
				currentAnimation->playAnimation();
		}

		sf::Sprite* Animator::getSprite()
		{
			lastSpriteAddress = currentAnimation->getSprite();
			return currentAnimation->getSprite();
		}

		sf::Texture* Animator::getTextureAtKey(std::string key, int index)
		{
			return fullAnimSet[key]->getTextureAtIndex(index);
		}

		bool Animator::textureChanged() const
		{
			return (currentAnimation->getSprite() != lastSpriteAddress);
		}

		int Animator::getSpriteOffsetX() const
		{
			return currentAnimation->getSpriteOffsetX();
		}

		int Animator::getSpriteOffsetY() const
		{
			return currentAnimation->getSpriteOffsetY();
		}
	}
}
