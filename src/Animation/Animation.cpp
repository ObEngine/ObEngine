#include <Animation/Animation.hpp>
#include <Graphics/ResourceManager.hpp>
#include <System/Loaders.hpp>
#include <Utils/StringUtils.hpp>

namespace obe
{
    namespace Animation
    {
        AnimationPlayMode stringToAnimationPlayMode(const std::string& animationPlayMode)
        {
            if (animationPlayMode == "OneTime")
                return AnimationPlayMode::OneTime;
            if (animationPlayMode == "Loop")
                return AnimationPlayMode::Loop;
            if (animationPlayMode == "Force")
                return AnimationPlayMode::Force;
            throw aube::ErrorHandler::Raise("ObEngine.Animation.AnimationPlayMode.UnknownPlayMode", {{"playmode", animationPlayMode}});
        }

        std::string Animation::getCalledAnimation() const
        {
            return m_animationToCall;
        }

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
            vili::ViliParser animFile;
            path.add(path.last() + ".ani.vili").loadResource(&animFile, System::Loaders::dataLoader);
            //Meta
            vili::ComplexNode& meta = animFile.at("Meta");
            m_animationName = meta.at<vili::DataNode>("name").get<std::string>();
            if (meta.contains(vili::NodeType::DataNode, "clock"))
                m_animationDelay = meta.at<vili::DataNode>("clock").get<int>();
            if (meta.contains(vili::NodeType::DataNode, "play-mode"))
                m_animationPlayMode = stringToAnimationPlayMode(meta.at<vili::DataNode>("play-mode").get<std::string>());
            //Images
            vili::ArrayNode& imageList = animFile.at<vili::ArrayNode>("Images", "ImageList");
            std::string model = "";
            if (animFile.at("Images").contains(vili::NodeType::DataNode, "model"))
            {
                model = animFile.at("Images").getDataNode("model").get<std::string>();
            }
            for (unsigned int i = 0; i < imageList.size(); i++)
            {
                std::string textureName = "";
                if (imageList.get(i).getDataType() == vili::DataType::Int && model != "")
                    textureName = Utils::String::replace(model, "%s", std::to_string(imageList.get(i).get<int>()));
                else if (imageList.get(i).getDataType() == vili::DataType::String)
                    textureName = imageList.get(i).get<std::string>();
                m_animationTextures[i] = Graphics::ResourceManager::GetInstance()->getTexture(path.add(textureName).toString());
            }
            //Groups
            vili::ComplexNode& groups = animFile.at("Groups");
            for (std::string complexName : groups.getAll(vili::NodeType::ComplexNode))
            {
                m_animationGroupMap.emplace(complexName, std::make_unique<AnimationGroup>(complexName));
                vili::ComplexNode& currentGroup = groups.at(complexName);
                for (vili::DataNode* currentTexture : currentGroup.at<vili::ArrayNode>("content"))
                    m_animationGroupMap[complexName]->pushTexture(m_animationTextures[*currentTexture]);
                if (currentGroup.contains(vili::NodeType::DataNode, "clock"))
                    m_animationGroupMap[complexName]->setGroupDelay(currentGroup.at<vili::DataNode>("clock"));
                else
                    m_animationGroupMap[complexName]->setGroupDelay(m_animationDelay);
                m_animationGroupMap[complexName]->build();
            }
            //Animation Code
            vili::ComplexNode& animation = animFile.at("Animation");
            for (vili::DataNode* command : animation.at<vili::ArrayNode>("AnimationCode"))
            {
                std::string curCom = command->get<std::string>();
                Utils::String::replaceInPlace(curCom, " ", "");
                Utils::String::replaceInPlace(curCom, ")", "");
                Utils::String::replaceInPlace(curCom, "(", ",");
                std::vector<std::string> vecCurCom = Utils::String::split(curCom, ",");
                m_animationCode.push_back(vecCurCom);
            }
        }

        void Animation::applyParameters(vili::ComplexNode& parameters)
        {
            if (parameters.contains(vili::NodeType::DataNode, "spriteOffsetX"))
                m_sprOffsetX = parameters.at<vili::DataNode>("spriteOffsetX").get<int>();
            if (parameters.contains(vili::NodeType::DataNode, "spriteOffsetY"))
                m_sprOffsetY = parameters.at<vili::DataNode>("spriteOffsetY").get<int>();
            if (parameters.contains(vili::NodeType::DataNode, "priority"))
                m_priority = parameters.at<vili::DataNode>("priority").get<int>();
        }

        void Animation::update()
        {
            if (m_animationCode.size() > 0)
            {
                if (m_codeIndex > m_animationCode.size() - 1 && m_animationPlayMode != AnimationPlayMode::OneTime)
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
                            if (m_animationPlayMode != AnimationPlayMode::OneTime && !(m_codeIndex >= m_animationCode.size() - 1))
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
                            Utils::String::replaceInPlace(callAnimation, "'", "");
                            m_currentStatus = AnimationStatus::Call;
                            m_animationToCall = callAnimation;
                        }
                    }
                    if (m_currentGroupName != "NONE")
                    {
                        m_animationGroupMap[m_currentGroupName]->next();
                        if (m_animationGroupMap[m_currentGroupName]->isGroupOver())
                        {
                            if (m_animationPlayMode != AnimationPlayMode::OneTime)
                            {
                                m_askCommand = true;
                                m_animationGroupMap[m_currentGroupName]->reset();
                                m_codeIndex++;
                            }
                            else if (m_animationPlayMode == AnimationPlayMode::OneTime)
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
                            m_animationGroupMap[m_currentGroupName]->update();
                    }
                }
            }
        }

        void Animation::reset()
        {
            for (auto it = m_animationGroupMap.begin(); it != m_animationGroupMap.end(); ++it)
                it->second->reset();
            m_currentStatus = AnimationStatus::Play;
            m_codeIndex = 0;
            m_askCommand = true;
            m_isOver = false;
        }

        const sf::Texture& Animation::getTextureAtIndex(int index)
        {
            return *m_animationTextures[index];
        }

        const sf::Texture& Animation::getTexture()
        {
            return m_animationGroupMap[m_currentGroupName]->getTexture();
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
    }
}
