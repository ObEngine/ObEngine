#include <Animation/Animator.hpp>
#include <Animation/Exceptions.hpp>

#include <Graphics/Sprite.hpp>
#include <Utils/VectorUtils.hpp>

#include <vili/parser.hpp>

using namespace std::string_literals;

namespace obe::Animation
{
    AnimatorTargetScaleMode stringToAnimatorTargetScaleMode(
        const std::string& targetScaleMode)
    {
        if (targetScaleMode == "Fit")
        {
            return AnimatorTargetScaleMode::Fit;
        }
        if (targetScaleMode == "FixedHeight")
        {
            return AnimatorTargetScaleMode::FixedHeight;
        }
        if (targetScaleMode == "FixedWidth")
        {
            return AnimatorTargetScaleMode::FixedWidth;
        }
        if (targetScaleMode == "TextureSize")
        {
            return AnimatorTargetScaleMode::TextureSize;
        }
        throw Exceptions::UnknownTargetScaleMode(targetScaleMode, EXC_INFO);
    }

    void Animator::applyTexture() const
    {
        const Graphics::Texture& texture = this->getTexture();
        m_target->setTexture(texture);

        if (m_targetScaleMode == AnimatorTargetScaleMode::Fit)
        {
            if (m_target->getSize().x >= m_target->getSize().y)
            {
                m_target->setSize(Transform::UnitVector(m_target->getSize().x,
                    static_cast<float>(texture.getSize().y)
                        / static_cast<float>(texture.getSize().x)
                        * m_target->getSize().x));
            }
            else
            {
                m_target->setSize(Transform::UnitVector(
                    static_cast<float>(texture.getSize().x)
                        / static_cast<float>(texture.getSize().y) * m_target->getSize().y,
                    m_target->getSize().y));
            }
        }
        else if (m_targetScaleMode == AnimatorTargetScaleMode::FixedWidth)
        {
            m_target->setSize(Transform::UnitVector(m_target->getSize().x,
                static_cast<float>(texture.getSize().y)
                    / static_cast<float>(texture.getSize().x) * m_target->getSize().x));
        }
        else if (m_targetScaleMode == AnimatorTargetScaleMode::FixedHeight)
        {
            m_target->setSize(
                Transform::UnitVector(static_cast<float>(texture.getSize().x)
                        / static_cast<float>(texture.getSize().y) * m_target->getSize().y,
                    m_target->getSize().y));
        }
        else if (m_targetScaleMode == AnimatorTargetScaleMode::TextureSize)
            m_target->useTextureSize();
    }

    void Animator::clear() noexcept
    {
        Debug::Log->trace("<Animator> Clearing Animator at '{0}'", m_path.toString());
        m_animations.clear();
        m_currentAnimation = nullptr;
    }

    Animation& Animator::getAnimation(const std::string& animationName) const
    {
        if (m_animations.find(animationName) != m_animations.end())
            return *m_animations.at(animationName).get();
        throw Exceptions::UnknownAnimation(
            m_path.toString(), animationName, this->getAllAnimationName(), EXC_INFO);
    }

    std::vector<std::string> Animator::getAllAnimationName() const
    {
        std::vector<std::string> allAnimationsNames;
        for (auto& animationPair : m_animations)
            allAnimationsNames.push_back(animationPair.first);
        return allAnimationsNames;
    }

    std::string Animator::getKey() const noexcept
    {
        if (m_currentAnimation)
            return m_currentAnimation->getName();
        else
            return "";
    }

    void Animator::setKey(const std::string& key)
    {
        Debug::Log->trace("<Animator> Set Animation Key '{0}' for Animator at {1} {2}", key,
            m_path.toString(), m_animations.size());
        if (m_animations.find(key) == m_animations.end())
        {
            throw Exceptions::UnknownAnimation(
                m_path.toString(), key, this->getAllAnimationName(), EXC_INFO);
        }
        if (key != this->getKey())
        {
            bool changeAnim = false;
            if (m_currentAnimation != nullptr)
            {
                if (m_currentAnimation->isOver()
                    || m_animations[key]->getPriority()
                        >= m_currentAnimation->getPriority())
                    changeAnim = true;
            }
            else
                changeAnim = true;
            if (changeAnim)
            {
                if (m_currentAnimation)
                    m_currentAnimation->reset();
                m_currentAnimation = m_animations[key].get();
            }
        }
    }

    void Animator::setPaused(bool pause) noexcept
    {
        m_paused = pause;
    }

    void Animator::load(System::Path path, Engine::ResourceManager* resources)
    {
        m_path = path;
        Debug::Log->debug("<Animator> Loading Animator at {0}", m_path.toString());
        std::vector<System::FindResult> directories
            = m_path.list(System::PathType::Directory);
        vili::node animatorCfgFile;
        auto foundAnimatorCfg
            = m_path.add("animator.cfg.vili").find(System::PathType::File);
        if (foundAnimatorCfg.success())
        {
            animatorCfgFile = vili::parser::from_file(foundAnimatorCfg.path());
        }
        for (const auto& directory : directories)
        {
            std::unique_ptr<Animation> tempAnim = std::make_unique<Animation>();
            if (m_target)
            {
                tempAnim->setAntiAliasing(m_target->getAntiAliasing());
            }
            tempAnim->loadAnimation(System::Path(directory.path()), resources);
            if (!animatorCfgFile.is_null())
            {
                if (animatorCfgFile.contains("all"))
                {
                    tempAnim->applyParameters(animatorCfgFile.at("all"));
                }
                if (animatorCfgFile.contains(directory.element()))
                {
                    tempAnim->applyParameters(animatorCfgFile.at(directory.element()));
                }
            }

            m_animations[tempAnim->getName()] = move(tempAnim);
        }
    }

    void Animator::update()
    {
        if (!m_paused)
        {
            Debug::Log->trace("<Animator> Updating Animator at {0}", m_path.toString());
            if (m_currentAnimation == nullptr)
                throw Exceptions::NoSelectedAnimation(m_path.toString(), EXC_INFO);
            if (m_currentAnimation->getStatus() == AnimationStatus::Call)
            {
                m_currentAnimation->reset();
                const std::string nextAnimation
                    = m_currentAnimation->getCalledAnimation();
                if (m_animations.find(nextAnimation) == m_animations.end())
                    throw Exceptions::UnknownAnimation(m_path.toString(), nextAnimation,
                        this->getAllAnimationName(), EXC_INFO);
                m_currentAnimation = m_animations[nextAnimation].get();
            }
            if (m_currentAnimation->getStatus() == AnimationStatus::Play)
                m_currentAnimation->update();

            if (m_target)
            {
                this->applyTexture();
            }
        }
    }

    void Animator::setTarget(
        Graphics::Sprite& sprite, AnimatorTargetScaleMode targetScaleMode)
    {
        m_target = &sprite;
        m_targetScaleMode = targetScaleMode;
    }

    const Graphics::Texture& Animator::getTexture() const
    {
        if (m_currentAnimation)
            return m_currentAnimation->getTexture();
        throw Exceptions::NoSelectedAnimation(m_path.toString(), EXC_INFO);
    }

    const Graphics::Texture& Animator::getTextureAtKey(
        const std::string& key, int index) const
    {
        return this->getAnimation(key).getTextureAtIndex(index);
    }
} // namespace obe::Animation
