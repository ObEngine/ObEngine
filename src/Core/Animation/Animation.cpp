#include <Animation/Animation.hpp>
#include <Animation/Exceptions.hpp>

#include <Debug/Logger.hpp>
#include <Engine/ResourceManager.hpp>
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
        throw Exceptions::UnknownAnimationPlayMode(animationPlayMode, EXC_INFO);
    }

    std::ostream& operator<<(std::ostream& os, const AnimationPlayMode& m)
    {
        os << "AnimationPlayMode::";
        switch (m)
        {
        case AnimationPlayMode::Force:
            os << "Force";
            break;
        case AnimationPlayMode::Loop:
            os << "Loop";
            break;
        case AnimationPlayMode::OneTime:
            os << "OneTime";
            break;
        }
        return os;
    }

    std::string Animation::getCalledAnimation() const noexcept
    {
        return m_nextAnimation;
    }

    std::string Animation::getName() const noexcept
    {
        return m_name;
    }

    unsigned int Animation::getDelay() const noexcept
    {
        return m_delay;
    }

    AnimationGroup& Animation::getAnimationGroup(const std::string& groupName)
    {
        if (const auto group = m_groups.find(groupName); group != m_groups.end())
            return *group->second;
        throw Exceptions::UnknownAnimationGroup(
            m_name, groupName, this->getAllAnimationGroupName(), EXC_INFO);
    }

    std::string Animation::getCurrentAnimationGroup() const noexcept
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

    AnimationPlayMode Animation::getPlayMode() const noexcept
    {
        return m_playMode;
    }

    AnimationStatus Animation::getStatus() const noexcept
    {
        return m_status;
    }

    bool Animation::isOver() const noexcept
    {
        return m_over;
    }

    void Animation::loadAnimation(
        const System::Path& path, Engine::ResourceManager* resources)
    {
        Debug::Log->debug("<Animation> Loading Animation at {0}", path.toString());
        vili::ViliParser animFile;
        path.add(path.last() + ".ani.vili").load(System::Loaders::dataLoader, animFile);

        // Meta
        Debug::Log->trace("  <Animation> Loading Meta block");
        vili::ComplexNode& meta = animFile.at("Meta");
        this->loadMeta(meta);

        // Images
        Debug::Log->trace("  <Animation> Loading Images block");
        vili::ComplexNode& images = animFile.at("Images");
        this->loadImages(images, path, resources);

        // Groups
        Debug::Log->trace("  <Animation> Loading Groups block");
        vili::ComplexNode& groups = animFile.at("Groups");
        this->loadGroups(groups);

        // Animation Code
        Debug::Log->trace("  <Animation> Loading Animation block");
        vili::ComplexNode& code = animFile.at("Animation");
        this->loadCode(code);
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
            if (!m_currentGroupName.empty())
                m_groups[m_currentGroupName]->reset();
            m_feedInstructions = false;
            m_currentGroupName = currentCommand[1];
            if (currentCommand.size() == 3)
            {
                const int loops = stoi(currentCommand[2]);
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
        else
        {
            throw Exceptions::UnknownAnimationCommand(
                m_name, currentCommand[0], EXC_INFO);
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
            else
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

    void Animation::setActiveAnimationGroup(const std::string& groupName)
    {
        if (m_groups.find(groupName) != m_groups.end())
        {
            m_currentGroupName = groupName;
        }
        throw Exceptions::UnknownAnimationGroup(
            m_name, groupName, this->getAllAnimationGroupName(), EXC_INFO);
    }

    void Animation::loadMeta(vili::ComplexNode& meta)
    {
        m_name = meta.at<vili::DataNode>("name").get<std::string>();
        Debug::Log->trace("    <Animation> Animation name = '{}'", m_name);
        if (meta.contains(vili::NodeType::DataNode, "clock"))
        {
            m_delay = meta.at<vili::DataNode>("clock").get<int>();
            Debug::Log->trace("    <Animation> Animation clock = {}", m_delay);
        }
        if (meta.contains(vili::NodeType::DataNode, "play-mode"))
        {
            m_playMode = stringToAnimationPlayMode(
                meta.at<vili::DataNode>("play-mode").get<std::string>());
            Debug::Log->trace("    <Animation> Animation play-mode = '{}'", m_playMode);
        }
    }

    void Animation::loadImages(vili::ComplexNode& images, const System::Path& path,
        Engine::ResourceManager* resources)
    {
        vili::ArrayNode& imageList = images.at<vili::ArrayNode>("ImageList");
        std::string model;
        if (images.contains(vili::NodeType::DataNode, "model"))
        {
            model = images.getDataNode("model").get<std::string>();
            Debug::Log->trace(
                "    <Animation> Using following template to load images : {}", model);
        }
        for (unsigned int i = 0; i < imageList.size(); i++)
        {
            std::string textureName;
            if (imageList.get(i).getDataType() == vili::DataType::Int && !model.empty())
            {
                textureName = Utils::String::replace(
                    model, "%s", std::to_string(imageList.get(i).get<int>()));
                Debug::Log->trace("    <Animation> Loading image '{}' (name determined "
                                  "with template[int])",
                    textureName);
            }
            else if (imageList.get(i).getDataType() == vili::DataType::String
                && !model.empty())
            {
                textureName = Utils::String::replace(
                    model, "%s", imageList.get(i).get<std::string>());
                Debug::Log->trace("    <Animation> Loading image '{}' (name determined "
                                  "with template[str])",
                    textureName);
            }
            else if (imageList.get(i).getDataType() == vili::DataType::String)
            {
                textureName = imageList.get(i).get<std::string>();
                Debug::Log->trace("    <Animation> Loading image '{}'", textureName);
            }

            std::string pathToTexture = path.add(textureName).toString();
            Debug::Log->trace(
                "    <Animation> Found Texture Path at '{}'", pathToTexture);
            if (resources)
            {
                Debug::Log->trace(
                    "    <Animation> Loading Texture {0} (using ResourceManager)",
                    textureName);
                m_textures.emplace_back(resources->getTexture(
                    path.add(textureName).toString(), m_antiAliasing));
            }
            else
            {
                Debug::Log->trace("    <Animation> Loading Texture {0}", textureName);
                Graphics::Texture newTexture;
                newTexture.loadFromFile(path.add(textureName).find());
                // TODO: Add a way to configure anti-aliasing for textures without ResourceManager
                m_textures.push_back(std::move(newTexture));
            }
        }
    }

    void Animation::loadGroups(vili::ComplexNode& groups)
    {
        for (vili::ComplexNode* group : groups.getAll<vili::ComplexNode>())
        {
            Debug::Log->trace(
                "    <Animation> Loading AnimationGroup '{}'", group->getId());
            m_groups.emplace(
                group->getId(), std::make_unique<AnimationGroup>(group->getId()));
            for (vili::DataNode* currentTexture : group->at<vili::ArrayNode>("content"))
            {
                Debug::Log->trace("      <Animation> Pushing Texture {} into group",
                    currentTexture->get<int>());
                m_groups[group->getId()]->pushTexture(
                    m_textures[currentTexture->get<int>()]);
            }

            if (group->contains(vili::NodeType::DataNode, "clock"))
            {
                const unsigned int delay = group->at<vili::DataNode>("clock");
                Debug::Log->trace("      <Animation> Setting group delay to {}", delay);
                m_groups[group->getId()]->setDelay(delay);
            }
            else
            {
                Debug::Log->trace(
                    "      <Animation> No delay specified, using parent delay : {}",
                    m_delay);
                m_groups[group->getId()]->setDelay(m_delay);
            }
        }
    }

    void Animation::loadCode(vili::ComplexNode& code)
    {
        for (vili::DataNode* command : code.at<vili::ArrayNode>("AnimationCode"))
        {
            std::string currentCommand = command->get<std::string>();
            Debug::Log->trace(
                "    <Animation> Parsing Animation command '{}'", currentCommand);
            Utils::String::replaceInPlace(currentCommand, " ", "");
            Utils::String::replaceInPlace(currentCommand, ")", "");
            Utils::String::replaceInPlace(currentCommand, "(", ",");
            const std::vector<std::string> vecCurCom
                = Utils::String::split(currentCommand, ",");
            m_code.push_back(vecCurCom);
        }
    }

    void Animation::applyParameters(vili::ComplexNode& parameters)
    {
        // TODO: Re-implement texture offset in a better way
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
            const unsigned int delay = (m_sleep) ? m_sleep : m_delay;
            if (Time::epoch() - m_clock > delay)
            {
                m_clock = Time::epoch();
                m_sleep = 0;
                Debug::Log->trace("<Animation> Updating Animation {0}", m_name);

                if (m_feedInstructions)
                {
                    this->executeInstruction();
                }
                if (!m_currentGroupName.empty())
                {
                    this->updateCurrentGroup();
                }
            }
        }
    }

    void Animation::setAntiAliasing(bool antiAliasing) noexcept
    {
        m_antiAliasing = antiAliasing;
    }

    bool Animation::getAntiAliasing() const noexcept
    {
        return m_antiAliasing;
    }

    void Animation::reset() noexcept
    {
        Debug::Log->trace("<Animation> Resetting Animation '{}'", m_name);
        for (auto it = m_groups.cbegin(); it != m_groups.cend(); ++it)
            it->second->reset();
        m_status = AnimationStatus::Play;
        m_codeIndex = 0;
        m_feedInstructions = true;
        m_over = false;
    }

    const Graphics::Texture& Animation::getTextureAtIndex(int index)
    {
        if (index < m_textures.size())
            return m_textures[index];
        throw Exceptions::AnimationTextureIndexOverflow(
            m_name, index, m_textures.size(), EXC_INFO);
    }

    const Graphics::Texture& Animation::getTexture()
    {
        if (!m_currentGroupName.empty())
            return m_groups[m_currentGroupName]->getTexture();
        throw Exceptions::NoSelectedAnimationGroup(m_name, EXC_INFO);
    }

    int Animation::getPriority() const noexcept
    {
        return m_priority;
    }
} // namespace obe::Animation