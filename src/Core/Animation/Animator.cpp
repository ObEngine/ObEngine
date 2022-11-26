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
        const graphics::TexturePart& texture = this->get_current_texture();
        m_target->set_texture(texture);

        if (m_target_scale_mode == AnimatorTargetScaleMode::KeepRatio)
        {
            if (m_target->get_size().x >= m_target->get_size().y)
            {
                m_target->set_size(transform::UnitVector(m_target->get_size().x,
                    static_cast<float>(texture.get_size().y)
                        / static_cast<float>(texture.get_size().x) * m_target->get_size().x));
            }
            else
            {
                m_target->set_size(transform::UnitVector(static_cast<float>(texture.get_size().x)
                        / static_cast<float>(texture.get_size().y) * m_target->get_size().y,
                    m_target->get_size().y));
            }
        }
        else if (m_target_scale_mode == AnimatorTargetScaleMode::FixedWidth)
        {
            m_target->set_size(transform::UnitVector(m_target->get_size().x,
                static_cast<float>(texture.get_size().y) / static_cast<float>(texture.get_size().x)
                    * m_target->get_size().x));
        }
        else if (m_target_scale_mode == AnimatorTargetScaleMode::FixedHeight)
        {
            m_target->set_size(transform::UnitVector(static_cast<float>(texture.get_size().x)
                    / static_cast<float>(texture.get_size().y) * m_target->get_size().y,
                m_target->get_size().y));
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
        for (const auto& [animation_name, animation] : m_parent.m_animations)
        {
            auto state = std::make_unique<AnimationState>(*animation.get());
            state->load();
            m_states.emplace(animation_name, std::move(state));
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
        debug::Log->trace("<Animator> Clearing Animator at '{0}'", m_path.to_string());
        m_animations.clear();
        m_default_state.reset();
    }

    Animation& Animator::get_animation(const std::string& animation_name) const
    {
        if (m_animations.find(animation_name) != m_animations.end())
            return *m_animations.at(animation_name).get();
        throw exceptions::UnknownAnimation(
            m_path.to_string(), animation_name, this->get_all_animations_names(), EXC_INFO);
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
                m_parent.m_path.to_string(), key, m_parent.get_all_animations_names(), EXC_INFO);
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
            m_path.to_string(), m_animations.size());
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

    void Animator::load(system::Path path, engine::ResourceManager* resources)
    {
        m_path = path;
        debug::Log->debug("<Animator> Loading Animator at {0}", m_path.to_string());
        std::vector<system::FindResult> directories = m_path.list(system::PathType::Directory);
        vili::node animator_cfg_file;
        auto found_animator_cfg = m_path.add("animator.cfg.vili").find(system::PathType::File);
        if (found_animator_cfg.success())
        {
            animator_cfg_file = vili::parser::from_file(found_animator_cfg.path());
        }
        for (const auto& directory : directories)
        {
            system::Path animation_path = path.add(system::Path(directory.path()).last());
            std::unique_ptr<Animation> temp_animation = std::make_unique<Animation>(animation_path, resources);
            if (m_default_state.get_target())
            {
                temp_animation->set_anti_aliasing(m_default_state.get_target()->is_anti_aliased());
            }
            const std::string animation_config_file
                = animation_path.add(animation_path.last() + ".animation.vili").find();
            try
            {
                temp_animation->load_from_file(animation_config_file);
            }
            catch (const std::exception& exc)
            {
                throw exceptions::InvalidAnimationFile(animation_config_file, EXC_INFO).nest(exc);
            }
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
            debug::Log->trace("<Animator> Updating Animator at {0}", m_parent.m_path.to_string());
            if (m_current_animation == nullptr)
                throw exceptions::NoSelectedAnimation(m_parent.m_path.to_string(), EXC_INFO);
            if (m_current_animation->get_status() == AnimationStatus::Call)
            {
                m_current_animation->reset();
                const std::string next_animation = m_current_animation->get_next_animation();
                if (m_parent.m_animations.find(next_animation) == m_parent.m_animations.end())
                    throw exceptions::UnknownAnimation(m_parent.m_path.to_string(), next_animation,
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

    void AnimatorState::set_target(
        graphics::Sprite& sprite, AnimatorTargetScaleMode target_scale_mode)
    {
        m_target = &sprite;
        m_target_scale_mode = target_scale_mode;
    }

    void Animator::set_target(graphics::Sprite& sprite, AnimatorTargetScaleMode target_scale_mode)
    {
        m_default_state.set_target(sprite, target_scale_mode);
    }

    system::Path Animator::get_filesystem_path() const
    {
        return m_path;
    }

    AnimatorState Animator::make_state() const
    {
        auto state = AnimatorState(*this);
        state.load();
        return state;
    }

    const graphics::TexturePart& Animator::get_current_texture() const
    {
        return m_default_state.get_current_texture();
    }

    const graphics::TexturePart& AnimatorState::get_current_texture() const
    {
        if (m_current_animation)
            return m_current_animation->get_texture();
        throw exceptions::NoSelectedAnimation(m_parent.get_filesystem_path().to_string(), EXC_INFO);
    }

    const Animator& AnimatorState::get_animator() const
    {
        return m_parent;
    }
} // namespace obe::animation
