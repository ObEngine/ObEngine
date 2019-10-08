// Corresponding header
#include <Animation/AnimationGroup.hpp>

namespace obe::Animation
{
    AnimationGroup::AnimationGroup(const std::string& groupName)
    {
        m_groupName = groupName;
    }

    void AnimationGroup::build()
    {
        m_texture = *m_groupList[0];
    }

    void AnimationGroup::setGroupDelay(unsigned int clock)
    {
        m_groupDelay = clock;
    }

    void AnimationGroup::setGroupLoop(int loops)
    {
        m_loopAmount = loops;
    }

    void AnimationGroup::pushTexture(sf::Texture* texture)
    {
        m_groupList.push_back(texture);
    }

    void AnimationGroup::removeTextureByIndex(unsigned int index)
    {
        if (m_groupList.size() > 0)
            m_groupList.erase(m_groupList.begin() + index);
    }

    const sf::Texture& AnimationGroup::getTexture() const
    {
        return m_texture;
    }

    void AnimationGroup::update()
    {
        m_texture = *m_groupList[m_groupIndex];
    }

    void AnimationGroup::reset()
    {
        m_groupIndex = 0;
        m_groupOver = false;
        m_loopIndex = 0;
    }

    void AnimationGroup::next()
    {
        if (Time::getTickSinceEpoch() - m_groupClock > m_groupDelay)
        {
            m_groupClock = Time::getTickSinceEpoch();
            m_groupIndex++;
            if (m_groupIndex > m_groupList.size() - 1)
            {
                if (m_loopIndex != m_loopAmount - 1)
                {
                    m_groupIndex = 0;
                    m_loopIndex++;
                    this->update();
                }
                else
                {
                    m_groupOver = true;
                }
            }
        }
    }

    void AnimationGroup::previous()
    {
        if (Time::getTickSinceEpoch() - m_groupClock > m_groupDelay)
        {
            m_groupClock = Time::getTickSinceEpoch();
            if (m_groupIndex == 0)
            {
                if (m_loopIndex != 0)
                    m_groupIndex = m_groupList.size() - 1;
                else
                    m_loopIndex = 0;
            }
            else
                m_groupIndex--;
        }
        this->update();
    }

    void AnimationGroup::forcePrevious()
    {
        m_groupIndex--;
    }

    void AnimationGroup::forceNext()
    {
        m_groupIndex++;
    }

    bool AnimationGroup::isGroupOver() const
    {
        return m_groupOver;
    }

    unsigned int AnimationGroup::getGroupIndex() const
    {
        return m_groupIndex;
    }

    unsigned int AnimationGroup::getGroupSize() const
    {
        return m_groupList.size();
    }

    std::string AnimationGroup::getGroupName() const
    {
        return m_groupName;
    }

    unsigned int AnimationGroup::getGroupDelay() const
    {
        return m_groupDelay;
    }
} // namespace obe::Animation