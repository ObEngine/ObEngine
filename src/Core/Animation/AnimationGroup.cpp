#include <Animation/AnimationGroup.hpp>

namespace obe::Animation
{
    bool AnimationGroup::checkDelay()
    {
        if (Time::epochAsMilliseconds() - m_groupClock > m_delay)
        {
            m_groupClock = Time::epochAsMilliseconds();
            return true;
        }
        return false;
    }
    AnimationGroup::AnimationGroup(std::string name)
        : m_name(std::move(name))
    {
    }

    void AnimationGroup::setDelay(unsigned int clock)
    {
        m_delay = clock;
    }

    void AnimationGroup::setLoops(int loops)
    {
        m_loopAmount = loops;
    }

    void AnimationGroup::pushTexture(sf::Texture* texture)
    {
        m_groupList.push_back(texture);
    }

    void AnimationGroup::removeTextureByIndex(unsigned int index)
    {
        if (!m_groupList.empty())
            m_groupList.erase(m_groupList.begin() + index);
    }

    const sf::Texture& AnimationGroup::getTexture() const
    {
        return *m_groupList[m_index];
    }

    void AnimationGroup::reset()
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

    bool AnimationGroup::isOver() const
    {
        return m_over;
    }

    unsigned int AnimationGroup::getIndex() const
    {
        return m_index;
    }

    unsigned int AnimationGroup::getSize() const
    {
        return m_groupList.size();
    }

    std::string AnimationGroup::getName() const
    {
        return m_name;
    }

    unsigned int AnimationGroup::getDelay() const
    {
        return m_delay;
    }
} // namespace obe::Animation