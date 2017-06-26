//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Animation.hpp"

//ANIMATION GROUP
namespace obe
{
    namespace Animation
    {
        AnimationGroup::AnimationGroup(const std::string& groupName)
        {
            m_groupName = groupName;
        }

        void AnimationGroup::build()
        {
            m_currentSprite = sf::Sprite(*m_groupList[0]);
        }

        void AnimationGroup::setGroupDelay(unsigned int clock)
        {
            m_groupDelay = clock;
        }

        void AnimationGroup::setGroupLoop(int loops)
        {
            m_loopAmount = loops;
        }

        void AnimationGroup::pushTexture(sf::Texture* texture)
        {
            m_groupList.push_back(texture);
        }

        void AnimationGroup::removeTextureByIndex(unsigned int index)
        {
            if (m_groupList.size() > 0)
                m_groupList.erase(m_groupList.begin() + index);
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
            m_loopIndex = 0;
        }

        void AnimationGroup::next()
        {
            if (Time::getTickSinceEpoch() - m_groupClock > m_groupDelay)
            {
                m_groupClock = Time::getTickSinceEpoch();
                m_groupIndex++;
                if (m_groupIndex > m_groupList.size() - 1)
                {
                    if (m_loopIndex != m_loopAmount - 1)
                    {
                        m_groupIndex = 0;
                        m_loopIndex++;
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
            if (Time::getTickSinceEpoch() - m_groupClock > m_groupDelay)
            {
                m_groupClock = Time::getTickSinceEpoch(); 
                if (m_groupIndex == 0)
                {
                    if (m_loopIndex != 0)
                        m_groupIndex = m_groupList.size() - 1;
                    else
                        m_loopIndex = 0;
                }
				else
					m_groupIndex--;
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

        unsigned int AnimationGroup::getGroupIndex() const
        {
            return m_groupIndex;
        }

        unsigned int AnimationGroup::getGroupSize() const
        {
            return m_groupList.size();
        }

        std::string AnimationGroup::getGroupName() const
        {
            return m_groupName;
        }

        unsigned int AnimationGroup::getGroupDelay() const
        {
            return m_groupDelay;
        }


        //RESSOURCE MANAGER
        RessourceManager* RessourceManager::m_instance = nullptr;

        RessourceManager* RessourceManager::GetInstance()
        {
            if (m_instance == nullptr)
                m_instance = new RessourceManager();
            return m_instance;
        }

        sf::Texture* RessourceManager::getTexture(const std::string& path)
        {
            if (m_textureDatabase.size() != 0)
            {
                if (m_textureDatabase.find(path) == m_textureDatabase.end())
                {
                    std::unique_ptr<sf::Texture> tempTexture = std::make_unique<sf::Texture>();
                    System::Path(path).loadResource(tempTexture.get(), System::Loaders::textureLoader);
                    if (tempTexture != nullptr)
                    {
                        tempTexture->setSmooth(true);
                        m_textureDatabase[path] = move(tempTexture);
                        return m_textureDatabase[path].get();
                    }
                    throw aube::ErrorHandler::Raise("ObEngine.Animation.RessourceManager.LoadTexture_NETD", {{"file", path}});
                }
                return m_textureDatabase[path].get();
            }
            std::unique_ptr<sf::Texture> tempTexture = std::make_unique<sf::Texture>();
            System::Path(path).loadResource(tempTexture.get(), System::Loaders::textureLoader);
            if (tempTexture != nullptr)
            {
                tempTexture->setSmooth(true);
                m_textureDatabase[path] = move(tempTexture);
                return m_textureDatabase[path].get();
            }
            throw aube::ErrorHandler::Raise("ObEngine.Animation.RessourceManager.LoadTexture_ETD", {{"file", path}});
        }

	    AnimationPlayMode stringToAnimationPlayMode(const std::string& animationPlayMode)
	    {
			if (animationPlayMode == "OneTime")
				return OneTime;
			if (animationPlayMode == "Loop")
				return Loop;
			if (animationPlayMode == "Force")
				return Force;
			throw aube::ErrorHandler::Raise("ObEngine.Animation.AnimationPlayMode.UnknownPlayMode", { {"playmode", animationPlayMode} });
	    }

	    std::string Animation::getCalledAnimation() const
	    {
			return m_animationToCall;
	    }

	    //ANIMATION
        std::string Animation::getAnimationName() const
        {
            return m_animationName;
        }

        unsigned int Animation::getAnimationDelay() const
        {
            return m_animationDelay;
        }

        AnimationGroup* Animation::getAnimationGroup(const std::string& groupName)
        {
            if (m_animationGroupMap.find(groupName) != m_animationGroupMap.end())
                return m_animationGroupMap[groupName].get();
            throw aube::ErrorHandler::Raise("ObEngine.Animation.Animation.AnimationGroupNotFound", {{"animation", m_animationName}, {"group", groupName}});
        }

        std::string Animation::getCurrentAnimationGroup() const
        {
            return m_currentGroupName;
        }

        std::vector<std::string> Animation::getAllAnimationGroupName()
        {
            std::vector<std::string> animationGroupsNames;
            for (auto it = m_animationGroupMap.begin(); it != m_animationGroupMap.end(); ++it)
                animationGroupsNames.push_back(it->first);
            return animationGroupsNames;
        }

        AnimationPlayMode Animation::getAnimationPlayMode() const
        {
            return m_animationPlayMode;
        }

        AnimationStatus Animation::getAnimationStatus() const
        {
            return m_currentStatus;
        }

        bool Animation::isAnimationOver() const
        {
            return m_isOver;
        }

        void Animation::loadAnimation(const System::Path& path)
        {
            vili::DataParser animFile;
            path.add(path.last() + ".ani.vili").loadResource(&animFile, System::Loaders::dataLoader);
            //Meta
            vili::ComplexAttribute& meta = animFile.at("Meta");
            m_animationName = meta.at<vili::BaseAttribute>("name").get<std::string>();
            if (meta.contains(vili::Types::BaseAttribute, "clock"))
                m_animationDelay = meta.at<vili::BaseAttribute>("clock").get<int>();
            if (meta.contains(vili::Types::BaseAttribute, "play-mode"))
                m_animationPlayMode = stringToAnimationPlayMode(meta.at<vili::BaseAttribute>("play-mode").get<std::string>());
            //Images
            vili::ListAttribute& imageList = animFile.at<vili::ListAttribute>("Images", "ImageList");
            std::string model = "";
            if (animFile.at("Images").contains(vili::Types::BaseAttribute, "model"))
            {
                model = animFile.at("Images").getBaseAttribute("model").get<std::string>();
            }
            for (unsigned int i = 0; i < imageList.size(); i++)
            {
                std::string textureName = "";
                if (imageList.get(i).getDataType() == vili::Types::Int && model != "")
                    textureName = Functions::String::replaceString(model, "%s", std::to_string(imageList.get(i).get<int>()));
                else if (imageList.get(i).getDataType() == vili::Types::String)
                    textureName = imageList.get(i).get<std::string>();
                m_animationTextures[i] = RessourceManager::GetInstance()->getTexture(path.add(textureName).toString());
            }
            //Groups
            vili::ComplexAttribute& groups = animFile.at("Groups");
            for (std::string complexName : groups.getAll(vili::Types::ComplexAttribute))
            {
                m_animationGroupMap.emplace(complexName, std::make_unique<AnimationGroup>(complexName));
                vili::ComplexAttribute& currentGroup = groups.at(complexName);
                for (vili::BaseAttribute* currentTexture : currentGroup.at<vili::ListAttribute>("content"))
                    m_animationGroupMap[complexName]->pushTexture(m_animationTextures[*currentTexture]);
                if (currentGroup.contains(vili::Types::BaseAttribute, "clock"))
                    m_animationGroupMap[complexName]->setGroupDelay(currentGroup.at<vili::BaseAttribute>("clock"));
                else
                    m_animationGroupMap[complexName]->setGroupDelay(m_animationDelay);
                m_animationGroupMap[complexName]->build();
            }
            //Animation Code
            vili::ComplexAttribute& animation = animFile.at("Animation");
            for (vili::BaseAttribute* command : animation.at<vili::ListAttribute>("AnimationCode"))
            {
                std::string curCom = command->get<std::string>();
	            Functions::String::replaceStringInPlace(curCom, " ", "");
                Functions::String::replaceStringInPlace(curCom, ")", "");
                Functions::String::replaceStringInPlace(curCom, "(", ",");
                std::vector<std::string> vecCurCom = Functions::String::split(curCom, ",");
                m_animationCode.push_back(vecCurCom);
            }
        }

        void Animation::applyParameters(vili::ComplexAttribute& parameters)
        {
            if (parameters.contains(vili::Types::BaseAttribute, "spriteOffsetX"))
                m_sprOffsetX = parameters.at<vili::BaseAttribute>("spriteOffsetX").get<int>();
            if (parameters.contains(vili::Types::BaseAttribute, "spriteOffsetY"))
                m_sprOffsetY = parameters.at<vili::BaseAttribute>("spriteOffsetY").get<int>();
            if (parameters.contains(vili::Types::BaseAttribute, "priority"))
                m_priority = parameters.at<vili::BaseAttribute>("priority").get<int>();
        }

        void Animation::update()
        {
            if (m_animationCode.size() > 0)
            {
                if (m_codeIndex > m_animationCode.size() - 1 && m_animationPlayMode != OneTime)
                    m_codeIndex = 0;
                if (Time::getTickSinceEpoch() - m_animationDelay > m_currentDelay)
                {
                    if (m_askCommand)
                    {
	                    std::vector<std::string> currentCommand = m_animationCode[m_codeIndex];
                        if (currentCommand[0] == "DELAY")
                        {
                            m_askCommand = true;
                            m_currentDelay = stoi(currentCommand[1]);
                            m_animationClock = Time::getTickSinceEpoch();
                            if (m_animationPlayMode != OneTime && !(m_codeIndex >= m_animationCode.size() - 1))
                                m_codeIndex++;
                            else
                                m_isOver = true;
                        }
                        else if (currentCommand[0] == "PLAY_GROUP")
                        {
                            if (m_currentGroupName != "NONE")
                                m_animationGroupMap[m_currentGroupName]->reset();
                            m_askCommand = false;
                            m_currentGroupName = currentCommand[1];
                            if (currentCommand.size() == 3)
                            {
                                m_loopAmount = stoi(currentCommand[2]);
                                m_animationGroupMap[m_currentGroupName]->setGroupLoop(m_loopAmount);
                            }
                            else
                                m_animationGroupMap[m_currentGroupName]->setGroupLoop(1);
                        }
                        else if (currentCommand[0] == "CALL")
                        {
                            m_askCommand = false;
	                        std::string callAnimation = currentCommand[1];
                            Functions::String::replaceStringInPlace(callAnimation, "'", "");
                            m_currentStatus = Call;
							m_animationToCall = callAnimation;
                        }
                    }
                    if (m_currentGroupName != "NONE")
                    {
                        m_animationGroupMap[m_currentGroupName]->next();
                        if (m_animationGroupMap[m_currentGroupName]->isGroupOver())
                        {
                            if (m_animationPlayMode != OneTime)
                            {
                                m_askCommand = true;
                                m_animationGroupMap[m_currentGroupName]->reset();
                                m_codeIndex++;
                            }
                            else if (m_animationPlayMode == OneTime)
                            {
                                if (m_codeIndex < m_animationCode.size() - 1)
                                {
                                    m_askCommand = true;
                                    m_animationGroupMap[m_currentGroupName]->reset();
                                    m_codeIndex++;
                                }
                                else
                                {
                                    m_animationGroupMap[m_currentGroupName]->forcePrevious();
                                    m_isOver = true;
                                }
                            }
                        }
                        else
                            m_animationGroupMap[m_currentGroupName]->updateSprite();
                    }
                }
            }
        }

        void Animation::reset()
        {
            for (auto it = m_animationGroupMap.begin(); it != m_animationGroupMap.end(); ++it)
                it->second->reset();
            m_currentStatus = Play;
            m_codeIndex = 0;
            m_askCommand = true;
            m_isOver = false;
        }

        sf::Texture* Animation::getTextureAtIndex(int index)
        {
            return m_animationTextures[index];
        }

        sf::Sprite* Animation::getSprite()
        {
            return m_animationGroupMap[m_currentGroupName]->returnSprite();
        }

        int Animation::getSpriteOffsetX() const
        {
            return m_sprOffsetX;
        }

        int Animation::getSpriteOffsetY() const
        {
            return m_sprOffsetY;
        }

        int Animation::getPriority() const
        {
            return m_priority;
        }

        //ANIMATOR
        Animator::Animator()
        {
        }

        Animator::Animator(System::Path path)
        {
            m_animatorPath = path;
        }

        void Animator::setPath(System::Path path)
        {
            m_animatorPath = path;
        }

        void Animator::setPath(std::string path)
        {
            m_animatorPath = System::Path(path);
        }

        void Animator::clear(bool clearMemory)
        {
            m_animationSet.clear();
            m_currentAnimation = nullptr;
            m_currentAnimationName = "NONE";
            m_animatorPath = System::Path("");
            m_lastSpritePointer = nullptr;
        }

        Animation* Animator::getAnimation(std::string animationName)
        {
            if (m_animationSet.find(animationName) != m_animationSet.end())
                return m_animationSet[animationName].get();
            throw aube::ErrorHandler::Raise("ObEngine.Animation.Animator.AnimationNotFound",
                                            {{"function", "getAnimation"}, {"animation", animationName}, {"%animator", m_animatorPath.toString()}
                                            });
        }

        std::vector<std::string> Animator::getAllAnimationName() const
        {
			std::vector<std::string> allAnimationsNames;
			for (auto& animationPair : m_animationSet)
				allAnimationsNames.push_back(animationPair.first);
            return allAnimationsNames;
        }

        std::string Animator::getKey() const
        {
            return m_currentAnimationName;
        }

        void Animator::setKey(const std::string& key)
        {
            if (m_animationSet.find(key) == m_animationSet.end())
            {
                throw aube::ErrorHandler::Raise("ObEngine.Animation.Animator.AnimationNotFound", {
                                                    {"function", "setKey"},{"animation", key},{"%animator", m_animatorPath.toString()}
                                                });
            }

            if (key != m_currentAnimationName)
            {
                bool changeAnim = false;
                if (m_currentAnimation != nullptr)
                {
                    if (m_currentAnimation->isAnimationOver())
                        changeAnim = true;
                    else if (m_animationSet[key]->getPriority() >= m_currentAnimation->getPriority())
                        changeAnim = true;
                }
                else
                    changeAnim = true;
                if (changeAnim)
                {
                    if (m_currentAnimationName != "NONE")
                        m_animationSet[m_currentAnimationName]->reset();
                    m_currentAnimationName = key;
                    m_currentAnimation = m_animationSet[m_currentAnimationName].get();
                }
            }
        }

        void Animator::loadAnimator()
        {
            std::vector<std::string> listDir;
            m_animatorPath.loadResource(&listDir, System::Loaders::dirPathLoader);
            std::vector<std::string> allFiles;
            m_animatorPath.loadResource(&allFiles, System::Loaders::filePathLoader);
            vili::DataParser animatorCfgFile;
            std::map<std::string, vili::ComplexAttribute*> animationParameters;
	        if (Functions::Vector::isInList(std::string("animator.cfg.vili"), allFiles))
            {
                System::Path(m_animatorPath.toString() + "/" + "animator.cfg.vili").loadResource(&animatorCfgFile, System::Loaders::dataLoader);
                for (std::string& currentAnimParameters : animatorCfgFile.at("Animator").getAll(vili::Types::ComplexAttribute))
                    animationParameters[currentAnimParameters] = &animatorCfgFile.at("Animator", currentAnimParameters);
            }
            for (unsigned int i = 0; i < listDir.size(); i++)
            {
                std::unique_ptr<Animation> tempAnim = std::make_unique<Animation>();
                tempAnim->loadAnimation(m_animatorPath.add(listDir[i]));
                if (animationParameters.find(listDir[i]) != animationParameters.end() && animationParameters.find("all") != animationParameters.end())
                {
                    tempAnim->applyParameters(*animationParameters["all"]);
                    tempAnim->applyParameters(*animationParameters[listDir[i]]);
                }
                else if (animationParameters.find(listDir[i]) != animationParameters.end())
                    tempAnim->applyParameters(*animationParameters[listDir[i]]);
                else if (animationParameters.find("all") != animationParameters.end())
                    tempAnim->applyParameters(*animationParameters["all"]);
                m_animationSet[tempAnim->getAnimationName()] = move(tempAnim);
            }
        }

        void Animator::update()
        {
            if (m_currentAnimation == nullptr)
                throw aube::ErrorHandler::Raise("ObEngine.Animator.Animator.UpdateNullAnimation", {{"animator", m_animatorPath.toString()}});
            if (m_currentAnimation->getAnimationStatus() == Call)
            {
                m_currentAnimation->reset();
                m_currentAnimation = m_animationSet[m_currentAnimation->getCalledAnimation()].get();
            }
            if (m_currentAnimation->getAnimationStatus() == Play)
                m_currentAnimation->update();      
        }

        sf::Sprite* Animator::getSprite()
        {
            m_lastSpritePointer = m_currentAnimation->getSprite();
            return m_currentAnimation->getSprite();
        }

        sf::Texture* Animator::getTextureAtKey(const std::string& key, int index)
        {
            return this->getAnimation(key)->getTextureAtIndex(index);
        }

        bool Animator::textureChanged() const
        {
            return (m_currentAnimation->getSprite() != m_lastSpritePointer);
        }

        int Animator::getSpriteOffsetX() const
        {
            return m_currentAnimation->getSpriteOffsetX();
        }

        int Animator::getSpriteOffsetY() const
        {
            return m_currentAnimation->getSpriteOffsetY();
        }
    }
}
