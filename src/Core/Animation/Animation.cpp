#include <vili/node.hpp>
#include <vili/parser/parser.hpp>
#include <vili/types.hpp>
#include <vld8/validator.hpp>

#include <Animation/Animation.hpp>
#include <Animation/AnimationValidator.hpp>
#include <Animation/Exceptions.hpp>
#include <Config/Templates/Animation.hpp>
#include <Debug/Logger.hpp>
#include <Engine/ResourceManager.hpp>
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

    Time::TimeUnit Animation::getDelay() const noexcept
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
        vili::node animationConfig
            = vili::parser::from_file(path.add(path.last() + ".ani.vili").find(),
                Config::Templates::getAnimationTemplates());

        vili::validator::validate_tree(AnimationValidator(), animationConfig);

        // Meta
        Debug::Log->trace("  <Animation> Loading Meta block");
        this->loadMeta(animationConfig.at("Meta"));

        // Images
        Debug::Log->trace("  <Animation> Loading Images block");
        this->loadImages(animationConfig.at("Images"), path, resources);

        // Groups
        Debug::Log->trace("  <Animation> Loading Groups block");
        this->loadGroups(animationConfig.at("Groups"));

        // Animation Code
        Debug::Log->trace("  <Animation> Loading Animation block");
        this->loadCode(animationConfig.at("Animation"));
    }

    void Animation::executeInstruction()
    {
        vili::node& currentCommand = m_code[m_codeIndex];
        Debug::Log->trace("<Animation> Executing instruction {} / {} : {}", m_codeIndex,
            m_code.size() - 1, currentCommand.dump());
        if (currentCommand.at("command") == Config::Templates::wait_command)
        {
            m_feedInstructions = true;
            m_sleep = currentCommand.at("time");
        }
        else if (currentCommand.at("command") == Config::Templates::play_group_command)
        {
            if (!m_currentGroupName.empty())
                m_groups[m_currentGroupName]->reset();
            m_feedInstructions = false;
            m_currentGroupName = currentCommand.at("group");
            m_groups[m_currentGroupName]->setLoops(currentCommand.at("repeat"));
        }
        else if (currentCommand.at("command") == Config::Templates::set_animation_command)
        {
            m_feedInstructions = false;
            m_status = AnimationStatus::Call;
            m_nextAnimation = currentCommand.at("animation");
        }
        else
        {
            throw Exceptions::UnknownAnimationCommand(
                m_name, currentCommand.at("command"), EXC_INFO);
        }
        m_codeIndex++;
        if (m_feedInstructions && m_codeIndex > m_code.size() - 1
            && m_playMode != AnimationPlayMode::OneTime)
        {
            this->reset();
        }
    }

    void Animation::updateCurrentGroup()
    {
        Debug::Log->trace(
            "    <Animation> Updating AnimationGroup '{}'", m_currentGroupName);
        m_groups[m_currentGroupName]->next();
        if (m_groups[m_currentGroupName]->isOver())
        {
            Debug::Log->trace(
                "        <Animation> AnimationGroup '{}' is over", m_currentGroupName);
            if (m_codeIndex < m_code.size())
            {
                Debug::Log->trace("    <Animation> Restarting code execution");
                m_feedInstructions = true;
                m_groups[m_currentGroupName]->reset();
            }
            else
            {
                Debug::Log->trace(
                    "    <Animation> Animation '{}' has no more code to execute");
                if (m_playMode == AnimationPlayMode::OneTime)
                {
                    Debug::Log->trace(
                        "    <Animation> Animation '{}' will stay on the last texture");
                    m_groups[m_currentGroupName]->previous(true);
                    m_over = true;
                }
                else
                {
                    Debug::Log->trace(
                        "    <Animation> Animation '{}' will reset code execution");
                    m_feedInstructions = true;
                    m_groups[m_currentGroupName]->reset();
                    m_codeIndex = 0;
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

    void Animation::loadMeta(const vili::node& meta)
    {
        m_name = meta.at("name");
        Debug::Log->trace("    <Animation> Animation name = '{}'", m_name);
        if (meta.contains("clock"))
        {
            m_delay = meta.at("clock");
            Debug::Log->trace("    <Animation> Animation clock = {}", m_delay);
        }
        if (meta.contains("mode"))
        {
            m_playMode = stringToAnimationPlayMode(meta.at("mode"));
            Debug::Log->trace("    <Animation> Animation play-mode = '{}'", m_playMode);
        }
    }

    void Animation::loadImages(const vili::node& images, const System::Path& path,
        Engine::ResourceManager* resources)
    {
        const vili::node& imageList = images.at("images");
        std::string model;
        if (images.contains("model"))
        {
            model = images.at("model");
            Debug::Log->trace(
                "    <Animation> Using following template to load images : {}", model);
        }
        for (std::size_t i = 0; i < imageList.size(); i++)
        {
            std::string textureName;
            if (imageList.at(i).is<vili::integer>() && !model.empty())
            {
                textureName = Utils::String::replace(
                    model, "%s", std::to_string(imageList.at(i).as<vili::integer>()));
                Debug::Log->trace("    <Animation> Loading image '{}' (name determined "
                                  "with template[int])",
                    textureName);
            }
            else if (imageList.at(i).is<vili::string>() && !model.empty())
            {
                textureName = Utils::String::replace(model, "%s", imageList.at(i));
                Debug::Log->trace("    <Animation> Loading image '{}' (name determined "
                                  "with template[str])",
                    textureName);
            }
            else if (imageList.at(i).is<vili::string>())
            {
                textureName = imageList.at(i);
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

    void Animation::loadGroups(const vili::node& groups)
    {
        for (auto [groupName, group] : groups.items())
        {
            Debug::Log->trace("    <Animation> Loading AnimationGroup '{}'", groupName);
            m_groups.emplace(groupName, std::make_unique<AnimationGroup>(groupName));
            for (vili::node& currentTexture : group.at("content"))
            {
                Debug::Log->trace("      <Animation> Pushing Texture {} into group",
                    currentTexture.as<vili::integer>());
                m_groups[groupName]->pushTexture(
                    m_textures[currentTexture.as<vili::integer>()]);
            }

            if (group.contains("clock"))
            {
                vili::number delay = group.at("clock");
                Debug::Log->trace("      <Animation> Setting group delay to {}", delay);
                m_groups[groupName]->setDelay(delay);
            }
            else
            {
                Debug::Log->trace(
                    "      <Animation> No delay specified, using parent delay : {}",
                    m_delay);
                m_groups[groupName]->setDelay(m_delay);
            }
        }
    }

    void Animation::loadCode(const vili::node& code)
    {
        for (const vili::node& command : code.at("code"))
        {
            Debug::Log->trace("    <Animation> Parsing Animation command '{}'", command);
            m_code.push_back(command);
        }
        if (m_code.empty())
            m_feedInstructions = false;
    }

    void Animation::applyParameters(vili::node& parameters)
    {
        // TODO: Re-implement texture offset in a better way
        if (parameters.contains("priority"))
            m_priority = parameters.at("priority");
    }

    void Animation::update()
    {
        if (!m_over)
        {
            const Time::TimeUnit delay = (m_sleep) ? m_sleep : m_delay;
            Debug::Log->trace("<Animation> Delay is {} seconds", delay);
            if (Time::epoch() - m_clock > delay)
            {
                m_clock = Time::epoch();
                m_sleep = 0;
                Debug::Log->trace("<Animation> Updating Animation '{0}'", m_name);

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