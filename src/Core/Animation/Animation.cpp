#include <Animation/Animation.hpp>

#include <Debug/Logger.hpp>
#include <Graphics/ResourceManager.hpp>
#include <System/Loaders.hpp>
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
        throw aube::ErrorHandler::Raise(
            "ObEngine.Animation.AnimationPlayMode.UnknownPlayMode",
            { { "playmode", animationPlayMode } });
    }

    std::string Animation::getCalledAnimation() const
    {
        return m_nextAnimation;
    }

    std::string Animation::getName() const
    {
        return m_name;
    }

    unsigned int Animation::getDelay() const
    {
        return m_delay;
    }

    AnimationGroup& Animation::getAnimationGroup(const std::string& groupName)
    {
        if (auto& group = m_groups.find(groupName); group != m_groups.end())
            return *group->second.get();
        throw aube::ErrorHandler::Raise(
            "ObEngine.Animation.Animation.AnimationGroupNotFound",
            { { "animation", m_name }, { "group", groupName } });
    }

    std::string Animation::getCurrentAnimationGroup() const
    {
        return m_currentGroupName;
    }

    std::vector<std::string> Animation::getAllAnimationGroupName() const
    {
        std::vector<std::string> animationGroupKeys;
        animationGroupKeys.reserve(m_groups.size());
        std::transform(m_groups.cbegin(), m_groups.cend(), animationGroupKeys.begin(),
            [](const auto& pair) { return pair.first; });
        return animationGroupKeys;
    }

    AnimationPlayMode Animation::getPlayMode() const
    {
        return m_playMode;
    }

    AnimationStatus Animation::getStatus() const
    {
        return m_status;
    }

    bool Animation::isOver() const
    {
        return m_over;
    }

    void Animation::loadAnimation(const System::Path& path)
    {
        Debug::Log->debug("<Animation> Loading Animation at {0}", path.toString());
        vili::ViliParser animFile;
        path.add(path.last() + ".ani.vili").load(System::Loaders::dataLoader, animFile);
        // Meta
        vili::ComplexNode& meta = animFile.at("Meta");
        m_name = meta.at<vili::DataNode>("name").get<std::string>();
        if (meta.contains(vili::NodeType::DataNode, "clock"))
            m_delay = meta.at<vili::DataNode>("clock").get<int>();
        if (meta.contains(vili::NodeType::DataNode, "play-mode"))
            m_playMode = stringToAnimationPlayMode(
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
            else if (imageList.get(i).getDataType() == vili::DataType::String
                && model != "")
                textureName = Utils::String::replace(
                    model, "%s", imageList.get(i).get<std::string>());
            else if (imageList.get(i).getDataType() == vili::DataType::String)
                textureName = imageList.get(i).get<std::string>();
            Debug::Log->trace(
                "<Animation> Loading Texture {0} in Animation {1}", textureName, m_name);
            m_textures.push_back(Graphics::ResourceManager::GetInstance().getTexture(
                path.add(textureName).toString(), m_antiAliasing));
        }
        // Groups
        vili::ComplexNode& groups = animFile.at("Groups");
        for (vili::ComplexNode* complex : groups.getAll<vili::ComplexNode>())
        {
            m_groups.emplace(
                complex->getId(), std::make_unique<AnimationGroup>(complex->getId()));
            for (vili::DataNode* currentTexture : complex->at<vili::ArrayNode>("content"))
                m_groups[complex->getId()]->pushTexture(
                    m_textures[currentTexture->get<int>()]);
            if (complex->contains(vili::NodeType::DataNode, "clock"))
                m_groups[complex->getId()]->setDelay(
                    complex->at<vili::DataNode>("clock"));
            else
                m_groups[complex->getId()]->setDelay(m_delay);
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
            m_code.push_back(vecCurCom);
        }
    }

    void Animation::executeInstruction()
    {
        std::vector<std::string> currentCommand = m_code[m_codeIndex];
        if (currentCommand[0] == "DELAY")
        {
            m_feedInstructions = true;
            m_sleep = stoi(currentCommand[1]);

            if (m_playMode != AnimationPlayMode::OneTime
                && !(m_codeIndex >= m_code.size() - 1))
                m_codeIndex++;
            else
                m_over = true;
        }
        else if (currentCommand[0] == "PLAY_GROUP")
        {
            if (m_currentGroupName != "NONE")
                m_groups[m_currentGroupName]->reset();
            m_feedInstructions = false;
            m_currentGroupName = currentCommand[1];
            if (currentCommand.size() == 3)
            {
                int loops = stoi(currentCommand[2]);
                m_groups[m_currentGroupName]->setLoops(loops);
            }
            else
                m_groups[m_currentGroupName]->setLoops(1);
        }
        else if (currentCommand[0] == "CALL")
        {
            m_feedInstructions = false;
            std::string callAnimation = currentCommand[1];
            Utils::String::replaceInPlace(callAnimation, "'", "");
            m_status = AnimationStatus::Call;
            m_nextAnimation = callAnimation;
        }
    }

    void Animation::updateCurrentGroup()
    {
        m_groups[m_currentGroupName]->next();
        if (m_groups[m_currentGroupName]->isOver())
        {
            if (m_playMode != AnimationPlayMode::OneTime)
            {
                m_feedInstructions = true;
                m_groups[m_currentGroupName]->reset();
                m_codeIndex++;
            }
            else if (m_playMode == AnimationPlayMode::OneTime)
            {
                if (m_codeIndex < m_code.size() - 1)
                {
                    m_feedInstructions = true;
                    m_groups[m_currentGroupName]->reset();
                    m_codeIndex++;
                }
                else
                {
                    m_groups[m_currentGroupName]->previous(true);
                    m_over = true;
                }
            }
        }
    }

    void Animation::applyParameters(vili::ComplexNode& parameters)
    {
        // TODO: Reimplement texture offset in a better way
        if (parameters.contains(vili::NodeType::DataNode, "priority"))
            m_priority = parameters.at<vili::DataNode>("priority").get<int>();
    }

    void Animation::update()
    {
        if (!m_code.empty())
        {
            if (m_codeIndex > m_code.size() - 1
                && m_playMode != AnimationPlayMode::OneTime)
                m_codeIndex = 0;
            unsigned int delay = (m_sleep) ? m_sleep : m_delay;
            if (Time::epochAsMilliseconds() - m_clock > delay)
            {
                m_clock = Time::epochAsMilliseconds();
                m_sleep = 0;
                Debug::Log->trace("<Animation> Updating Animation {0}", m_name);

                if (m_feedInstructions)
                {
                    this->executeInstruction();
                }
                if (m_currentGroupName != "NONE")
                {
                    this->updateCurrentGroup();
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
        Debug::Log->trace("<Animation> Resetting Animation {0}", m_name);
        for (auto& it = m_groups.cbegin(); it != m_groups.cend(); ++it)
            it->second->reset();
        m_status = AnimationStatus::Play;
        m_codeIndex = 0;
        m_feedInstructions = true;
        m_over = false;
    }

    const sf::Texture& Animation::getTextureAtIndex(int index)
    {
        return *m_textures[index];
    }

    const sf::Texture& Animation::getTexture()
    {
        return m_groups[m_currentGroupName]->getTexture();
    }

    int Animation::getPriority() const
    {
        return m_priority;
    }
} // namespace obe::Animation