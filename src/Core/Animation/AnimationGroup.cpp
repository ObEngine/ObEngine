#include <Animation/AnimationGroup.hpp>
#include <Animation/Exceptions.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/Texture.hpp>

namespace obe::animation
{
    bool AnimationGroup::is_delay_elapsed()
    {
        if (time::epoch() - m_group_clock > m_delay)
        {
            m_group_clock = time::epoch();
            return true;
        }
        return false;
    }
    AnimationGroup::AnimationGroup(std::string name)
        : m_name(std::move(name))
    {
    }

    AnimationGroup::AnimationGroup(const AnimationGroup& group)
        : m_delay(group.m_delay), m_textures(group.m_textures)
    {
    }

    void AnimationGroup::set_delay(time::TimeUnit delay) noexcept
    {
        m_delay = delay;
    }

    void AnimationGroup::set_loops(int loops) noexcept
    {
        m_loop_amount = loops;
    }

    void AnimationGroup::push_texture(const graphics::Texture& texture)
    {
        m_textures.push_back(texture);
    }

    void AnimationGroup::remove_texture_by_index(std::size_t index)
    {
        if (index < m_textures.size())
            m_textures.erase(m_textures.begin() + index);
        throw exceptions::AnimationGroupTextureIndexOverflow(m_name, index, m_textures.size(),
            EXC_INFO); // TODO: Improve this exception
    }

    const graphics::Texture& AnimationGroup::get_current_texture() const
    {
        return m_textures[m_index];
    }

    void AnimationGroup::reset() noexcept
    {
        debug::Log->trace("            <AnimationGroup> Resetting AnimationGroup '{}'", m_name);
        m_index = 0;
        m_over = false;
        m_loop_index = 0;
    }

    void AnimationGroup::next(bool force)
    {
        if (is_delay_elapsed() || force)
        {
            m_index++;
            if (m_index > m_textures.size() - 1)
            {
                if (m_loop_index < m_loop_amount - 1)
                {
                    m_index = 0;
                    m_loop_index++;
                }
                else
                {
                    m_over = true;
                }
            }
            debug::Log->trace("            <AnimationGroup> Loading next image on group "
                              "'{}' (image: {} / {}) "
                              "(repeat: {} / {})",
                m_name, m_index, m_textures.size() - 1, m_loop_index, m_loop_amount - 1);
        }
    }

    void AnimationGroup::previous(bool force)
    {
        if (is_delay_elapsed() || force)
        {
            if (m_index == 0)
            {
                if (m_loop_index != 0)
                    m_index = m_textures.size() - 1;
            }
            else
                m_index--;
            debug::Log->trace("            <AnimationGroup> Loading previous image on "
                              "group '{}' (image: {} / {}) "
                              "(repeat: {} / {})",
                m_name, m_index, m_textures.size() - 1, m_loop_index, m_loop_amount - 1);
        }
    }

    bool AnimationGroup::is_over() const noexcept
    {
        return m_over;
    }

    std::size_t AnimationGroup::get_current_index() const noexcept
    {
        return m_index;
    }

    std::size_t AnimationGroup::get_textures_amount() const noexcept
    {
        return m_textures.size();
    }

    std::string AnimationGroup::get_name() const noexcept
    {
        return m_name;
    }

    time::TimeUnit AnimationGroup::get_delay() const noexcept
    {
        return m_delay;
    }
} // namespace obe::animation
