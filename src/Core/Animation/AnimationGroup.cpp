#include <Animation/AnimationGroup.hpp>
#include <Animation/Exceptions.hpp>

namespace obe::Animation
{
    bool AnimationGroup::checkDelay()
    {
        if (Time::epoch() - m_groupClock > m_delay)
        {
            m_groupClock = Time::epoch();
            return true;
        }
        return false;
    }
    AnimationGroup::AnimationGroup(std::string name)
        : m_name(std::move(name))
    {
    }

    void AnimationGroup::setDelay(unsigned int delay) noexcept
    {
        m_delay = delay;
    }

    void AnimationGroup::setLoops(int loops) noexcept
    {
        m_loopAmount = loops;
    }

    void AnimationGroup::pushTexture(const Graphics::Texture& texture)
    {
        m_groupList.push_back(texture);
    }

    void AnimationGroup::removeTextureByIndex(unsigned int index)
    {
        if (index < m_groupList.size())
            m_groupList.erase(m_groupList.begin() + index);
        throw Exceptions::AnimationGroupTextureIndexOverflow(m_name, index,
            m_groupList.size(),
            EXC_INFO); // TODO: Improve this exception
    }

    const Graphics::Texture& AnimationGroup::getTexture() const
    {
        return m_groupList[m_index];
    }

    void AnimationGroup::reset() noexcept
    {
        m_index = 0;
        m_over = false;
        m_loopIndex = 0;
    }

    void AnimationGroup::next(bool force)
    {
        if (checkDelay() | force)
        {
            m_index++;
            if (m_index > m_groupList.size() - 1)
            {
                if (m_loopIndex != m_loopAmount - 1)
                {
                    m_index = 0;
                    m_loopIndex++;
                }
                else
                {
                    m_over = true;
                }
            }
        }
    }

    void AnimationGroup::previous(bool force)
    {
        if (checkDelay() || force)
        {
            if (m_index == 0)
            {
                if (m_loopIndex != 0)
                    m_index = m_groupList.size() - 1;
            }
            else
                m_index--;
        }
    }

    bool AnimationGroup::isOver() const noexcept
    {
        return m_over;
    }

    unsigned int AnimationGroup::getIndex() const noexcept
    {
        return m_index;
    }

    unsigned int AnimationGroup::getSize() const noexcept
    {
        return m_groupList.size();
    }

    std::string AnimationGroup::getName() const noexcept
    {
        return m_name;
    }

    unsigned int AnimationGroup::getDelay() const noexcept
    {
        return m_delay;
    }
} // namespace obe::Animation