#include <Animation/Animation.hpp>

#include <Debug/Logger.hpp>
#include <Graphics/ResourceManager.hpp>
#include <System/Loaders.hpp>
#include <Utils/MapUtils.hpp>
#include <Utils/StringUtils.hpp>

namespace obe::Animation
{
    AnimationPlayMode stringToAnimationPlayMode(const std::string& animationPlayMode)
    {
        if (animationPlayMode == "OneTime")
            return AnimationPlayMode::OneTime;
        if (animationPlayMode == "Loop")
            return AnimationPlayMode::Loop;
        if (animationPlayMode == "Force")
            return AnimationPlayMode::Force;
        throw aube::ErrorHandler::Raise("ObEngine.Animation.AnimationPlayMode.UnknownPlayMode",
            { { "playmode", animationPlayMode } });
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
        throw aube::ErrorHandler::Raise("ObEngine.Animation.Animation.AnimationGroupNotFound",
            { { "animation", m_animationName }, { "group", groupName } });
    }

    std::string Animation::getCurrentAnimationGroup() const
    {
        return m_currentGroupName;
    }

    std::vector<std::string> Animation::getAllAnimationGroupName() const
    {
        return Utils::Map::getKeys(m_animationGroupMap);
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

    Transform::UnitVector Animation::getSpriteOffset() const
    {
        return m_offset;
    }

    void Animation::loadAnimation(const System::Path& path)
    {
        Debug::Log->debug("<Animation> Loading Animation at {0}", path.toString());
        vili::ViliParser animFile;
        path.add(path.last() + ".ani.vili").load(System::Loaders::dataLoader, animFile);
        // Meta
        vili::ComplexNode& meta = animFile.at("Meta");
        m_animationName = meta.at<vili::DataNode>("name").get<std::string>();
        if (meta.contains(vili::NodeType::DataNode, "clock"))
            m_animationDelay = meta.at<vili::DataNode>("clock").get<int>();
        if (meta.contains(vili::NodeType::DataNode, "play-mode"))
            m_animationPlayMode = stringToAnimationPlayMode(
                meta.at<vili::DataNode>("play-mode").get<std::string>());
        // Images
        vili::ArrayNode& imageList = animFile.at<vili::ArrayNode>("Images", "ImageList");
        std::string model;
        if (animFile.at("Images").contains(vili::NodeType::DataNode, "model"))
        {
            model = animFile.at("Images").getDataNode("model").get<std::string>();
        }
        for (unsigned int i = 0; i < imageList.size(); i++)
        {
            std::string textureName;
            if (imageList.get(i).getDataType() == vili::DataType::Int && model != "")
                textureName = Utils::String::replace(
                    model, "%s", std::to_string(imageList.get(i).get<int>()));
            else if (imageList.get(i).getDataType() == vili::DataType::String && model != "")
                textureName
                    = Utils::String::replace(model, "%s", imageList.get(i).get<std::string>());
            else if (imageList.get(i).getDataType() == vili::DataType::String)
                textureName = imageList.get(i).get<std::string>();
            Debug::Log->trace(
                "<Animation> Loading Texture {0} in Animation {1}", textureName, m_animationName);
            m_animationTextures.push_back(Graphics::ResourceManager::GetInstance().getTexture(
                path.add(textureName).toString(), m_antiAliasing));
        }
        // Groups
        vili::ComplexNode& groups = animFile.at("Groups");
        for (vili::ComplexNode* complex : groups.getAll<vili::ComplexNode>())
        {
            m_animationGroupMap.emplace(
                complex->getId(), std::make_unique<AnimationGroup>(complex->getId()));
            for (vili::DataNode* currentTexture : complex->at<vili::ArrayNode>("content"))
                m_animationGroupMap[complex->getId()]->pushTexture(
                    m_animationTextures[currentTexture->get<int>()]);
            if (complex->contains(vili::NodeType::DataNode, "clock"))
                m_animationGroupMap[complex->getId()]->setGroupDelay(
                    complex->at<vili::DataNode>("clock"));
            else
                m_animationGroupMap[complex->getId()]->setGroupDelay(m_animationDelay);
            Debug::Log->trace("<Animation> Building AnimationGroup {0} in Animation {1}",
                complex->getId(), m_animationName);
            m_animationGroupMap[complex->getId()]->build();
        }
        // Animation Code
        vili::ComplexNode& animation = animFile.at("Animation");
        for (vili::DataNode* command : animation.at<vili::ArrayNode>("AnimationCode"))
        {
            std::string curCom = command->get<std::string>();
            Utils::String::replaceInPlace(curCom, " ", "");
            Utils::String::replaceInPlace(curCom, ")", "");
            Utils::String::replaceInPlace(curCom, "(", ",");
            const std::vector<std::string> vecCurCom = Utils::String::split(curCom, ",");
            m_animationCode.push_back(vecCurCom);
        }
    }

    void Animation::applyParameters(vili::ComplexNode& parameters)
    {
        if (parameters.contains(vili::NodeType::ComplexNode, "offset"))
        {
            if (parameters.at("offset").contains(vili::NodeType::DataNode, "unit"))
                m_offset.unit = Transform::stringToUnits(
                    parameters.at<vili::DataNode>("offset", "unit").get<std::string>());
            if (parameters.at("offset").contains(vili::NodeType::DataNode, "x"))
                m_offset.x = parameters.at<vili::DataNode>("offset", "x").get<int>();
            if (parameters.at("offset").contains(vili::NodeType::DataNode, "y"))
                m_offset.y = parameters.at<vili::DataNode>("offset", "y").get<int>();
            m_offset = m_offset.to<Transform::Units::ScenePixels>();
        }
        if (parameters.contains(vili::NodeType::DataNode, "priority"))
            m_priority = parameters.at<vili::DataNode>("priority").get<int>();
    }

    void Animation::update()
    {
        if (!m_animationCode.empty())
        {
            if (m_codeIndex > m_animationCode.size() - 1
                && m_animationPlayMode != AnimationPlayMode::OneTime)
                m_codeIndex = 0;
            if (Time::getTickSinceEpoch() - m_animationDelay > m_currentDelay)
            {
                Debug::Log->trace("<Animation> Updating Animation {0}", m_animationName);
                if (m_askCommand)
                {
                    std::vector<std::string> currentCommand = m_animationCode[m_codeIndex];
                    if (currentCommand[0] == "DELAY")
                    {
                        m_askCommand = true;
                        m_currentDelay = stoi(currentCommand[1]);
                        m_animationClock = Time::getTickSinceEpoch();
                        if (m_animationPlayMode != AnimationPlayMode::OneTime
                            && !(m_codeIndex >= m_animationCode.size() - 1))
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

    void Animation::setAntiAliasing(bool antiAliasing)
    {
        m_antiAliasing = antiAliasing;
    }

    bool Animation::getAntiAliasing()
    {
        return m_antiAliasing;
    }

    void Animation::reset()
    {
        Debug::Log->trace("<Animation> Resetting Animation {0}", m_animationName);
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

    int Animation::getPriority() const
    {
        return m_priority;
    }
} // namespace obe::Animation