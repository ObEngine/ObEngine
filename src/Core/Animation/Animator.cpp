#include <vili/parser.hpp>

#include <Animation/Animator.hpp>
#include <Animation/Exceptions.hpp>
#include <Graphics/Sprite.hpp>
#include <Transform/UnitVector.hpp>

using namespace std::string_literals;

namespace obe::animation
{
    void AnimatorState::apply_texture() const
    {
        const graphics::Texture& texture = this->get_current_texture();
        m_target->set_texture(texture);

        if (m_target_scale_mode == AnimatorTargetScaleMode::KeepRatio)
        {
            if (m_target->getSize().x >= m_target->getSize().y)
            {
                m_target->setSize(Transform::UnitVector(m_target->getSize().x,
                    static_cast<float>(texture.getSize().y)
                        / static_cast<float>(texture.getSize().x) * m_target->getSize().x));
            }
            else
            {
                m_target->setSize(Transform::UnitVector(static_cast<float>(texture.getSize().x)
                        / static_cast<float>(texture.getSize().y) * m_target->getSize().y,
                    m_target->getSize().y));
            }
        }
        else if (m_target_scale_mode == AnimatorTargetScaleMode::FixedWidth)
        {
            m_target->setSize(Transform::UnitVector(m_target->getSize().x,
                static_cast<float>(texture.getSize().y) / static_cast<float>(texture.getSize().x)
                    * m_target->getSize().x));
        }
        else if (m_target_scale_mode == AnimatorTargetScaleMode::FixedHeight)
        {
            m_target->setSize(Transform::UnitVector(static_cast<float>(texture.getSize().x)
                    / static_cast<float>(texture.getSize().y) * m_target->getSize().y,
                m_target->getSize().y));
        }
        else if (m_target_scale_mode == AnimatorTargetScaleMode::TextureSize)
            m_target->use_texture_size();
    }

    AnimatorState::AnimatorState(const Animator& parent)
        : m_parent(parent)
    {
    }

    void AnimatorState::load()
    {
        for (const auto& [animationName, animation] : m_parent.m_animations)
        {
            auto state = std::make_unique<AnimationState>(*animation.get());
            state->load();
            m_states.emplace(animationName, std::move(state));
        }
    }

    void AnimatorState::reset()
    {
        m_current_animation = nullptr;
    }

    graphics::Sprite* AnimatorState::get_target() const
    {
        return m_target;
    }

    AnimationState* AnimatorState::get_current_animation() const
    {
        return m_current_animation;
    }

    Animator::Animator()
        : m_default_state(*this)
    {
    }

    void Animator::clear() noexcept
    {
        debug::Log->trace("<Animator> Clearing Animator at '{0}'", m_path.toString());
        m_animations.clear();
        m_default_state.reset();
    }

    Animation& Animator::get_animation(const std::string& animation_name) const
    {
        if (m_animations.find(animation_name) != m_animations.end())
            return *m_animations.at(animation_name).get();
        throw exceptions::UnknownAnimation(
            m_path.toString(), animation_name, this->get_all_animations_names(), EXC_INFO);
    }

    std::vector<std::string> Animator::get_all_animations_names() const
    {
        std::vector<std::string> all_animations_names;
        for (const auto& animation_pair : m_animations)
            all_animations_names.push_back(animation_pair.first);
        return all_animations_names;
    }

    std::string AnimatorState::get_current_animation_name() const noexcept
    {
        if (m_current_animation)
            return m_current_animation->get_animation().get_name();
        else
            return "";
    }

    std::string Animator::get_current_animation_name() const noexcept
    {
        return m_default_state.get_current_animation_name();
    }

    void AnimatorState::set_animation(const std::string& key)
    {
        if (m_parent.m_animations.find(key) == m_parent.m_animations.end())
        {
            throw exceptions::UnknownAnimation(
                m_parent.m_path.toString(), key, m_parent.get_all_animations_names(), EXC_INFO);
        }
        if (key != this->get_current_animation_name())
        {
            bool change_animation = false;
            if (m_current_animation != nullptr)
            {
                if (m_current_animation->is_over()
                    || m_parent.m_animations.at(key)->get_priority()
                        >= m_current_animation->get_animation().get_priority())
                    change_animation = true;
            }
            else
                change_animation = true;
            if (change_animation)
            {
                if (m_current_animation)
                    m_current_animation->reset();
                m_current_animation = m_states.at(key).get();
            }
        }
    }

    void Animator::set_animation(const std::string& key)
    {
        debug::Log->trace("<Animator> Set animation Key '{0}' for Animator at {1} {2}", key,
            m_path.toString(), m_animations.size());
        m_default_state.set_animation(key);
    }

    void AnimatorState::set_paused(bool pause) noexcept
    {
        m_paused = pause;
    }

    void Animator::set_paused(bool pause) noexcept
    {
        m_default_state.set_paused(pause);
    }

    void Animator::load(System::Path path, engine::ResourceManager* resources)
    {
        m_path = path;
        debug::Log->debug("<Animator> Loading Animator at {0}", m_path.toString());
        std::vector<System::FindResult> directories = m_path.list(System::PathType::Directory);
        vili::node animator_cfg_file;
        auto found_animator_cfg = m_path.add("animator.cfg.vili").find(System::PathType::File);
        if (found_animator_cfg.success())
        {
            animator_cfg_file = vili::parser::from_file(found_animator_cfg.path());
        }
        for (const auto& directory : directories)
        {
            std::unique_ptr<Animation> temp_animation = std::make_unique<Animation>();
            if (m_default_state.get_target())
            {
                temp_animation->set_anti_aliasing(m_default_state.get_target()->get_anti_aliasing());
            }
            temp_animation->load_animation(path.add(System::Path(directory.path()).last()), resources);
            if (!animator_cfg_file.is_null())
            {
                if (animator_cfg_file.contains("all"))
                {
                    temp_animation->apply_parameters(animator_cfg_file.at("all"));
                }
                if (animator_cfg_file.contains(directory.element()))
                {
                    temp_animation->apply_parameters(animator_cfg_file.at(directory.element()));
                }
            }

            m_animations[temp_animation->get_name()] = move(temp_animation);
        }
        m_default_state.load();
    }

    void AnimatorState::update()
    {
        if (!m_paused)
        {
            debug::Log->trace("<Animator> Updating Animator at {0}", m_parent.m_path.toString());
            if (m_current_animation == nullptr)
                throw exceptions::NoSelectedAnimation(m_parent.m_path.toString(), EXC_INFO);
            if (m_current_animation->get_status() == AnimationStatus::Call)
            {
                m_current_animation->reset();
                const std::string next_animation = m_current_animation->get_called_animation();
                if (m_parent.m_animations.find(next_animation) == m_parent.m_animations.end())
                    throw exceptions::UnknownAnimation(m_parent.m_path.toString(), next_animation,
                        m_parent.get_all_animations_names(), EXC_INFO);
                m_current_animation = m_states.at(next_animation).get();
            }
            if (m_current_animation->get_status() == AnimationStatus::Play)
                m_current_animation->update();

            if (m_target)
            {
                this->apply_texture();
            }
        }
    }

    void Animator::update()
    {
        m_default_state.update();
    }

    void AnimatorState::set_target(graphics::Sprite& sprite, AnimatorTargetScaleMode target_scale_mode)
    {
        m_target = &sprite;
        m_target_scale_mode = target_scale_mode;
    }

    void Animator::set_target(graphics::Sprite& sprite, AnimatorTargetScaleMode target_scale_mode)
    {
        m_default_state.set_target(sprite, target_scale_mode);
    }

    System::Path Animator::get_filesystem_path() const
    {
        return m_path;
    }

    AnimatorState Animator::make_state() const
    {
        auto state = AnimatorState(*this);
        state.load();
        return state;
    }

    const graphics::Texture& Animator::get_current_texture() const
    {
        return m_default_state.get_current_texture();
    }

    const graphics::Texture& AnimatorState::get_current_texture() const
    {
        if (m_current_animation)
            return m_current_animation->get_texture();
        throw exceptions::NoSelectedAnimation(m_parent.get_filesystem_path().toString(), EXC_INFO);
    }

    const Animator& AnimatorState::get_animator() const
    {
        return m_parent;
    }
} // namespace obe::animation
