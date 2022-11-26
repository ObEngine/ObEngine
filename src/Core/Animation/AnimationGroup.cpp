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

    AnimationGroup::AnimationGroup(const std::string& name)
        : m_name(name)
    {
    }

    AnimationGroup::AnimationGroup(const AnimationGroup& group)
        : m_delay(group.m_delay)
        , m_frame_indexes(group.m_frame_indexes)
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
            if (m_index > this->get_size() - 1)
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
                m_name, m_index, this->get_size() - 1, m_loop_index, m_loop_amount - 1);
        }
    }

    void AnimationGroup::previous(bool force)
    {
        if (is_delay_elapsed() || force)
        {
            if (m_index == 0)
            {
                if (m_loop_index != 0)
                    m_index = this->get_size() - 1;
            }
            else
                m_index--;
            debug::Log->trace("            <AnimationGroup> Loading previous image on "
                              "group '{}' (image: {} / {}) "
                              "(repeat: {} / {})",
                m_name, m_index, this->get_size() - 1, m_loop_index, m_loop_amount - 1);
        }
    }

    void AnimationGroup::push_frame_index(uint32_t frame_index)
    {
        m_frame_indexes.push_back(frame_index);
    }

    bool AnimationGroup::is_over() const noexcept
    {
        return m_over;
    }

    std::size_t AnimationGroup::get_group_index() const noexcept
    {
        return m_index;
    }

    std::size_t AnimationGroup::get_frame_index() const noexcept
    {
        return m_frame_indexes[m_index];
    }

    std::string AnimationGroup::get_name() const noexcept
    {
        return m_name;
    }

    std::size_t AnimationGroup::get_size() const noexcept
    {
        return m_frame_indexes.size();
    }

    time::TimeUnit AnimationGroup::get_delay() const noexcept
    {
        return m_delay;
    }
} // namespace obe::animation
