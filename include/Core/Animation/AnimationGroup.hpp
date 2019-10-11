#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <Time/TimeUtils.hpp>

namespace obe::Animation
{
    /**
     * \brief A subpart of an Animation containing the Textures to display
     * @Bind
     */
    class AnimationGroup
    {
    private:
        /**
         * \brief Stores the last epoch to wait until the AnimationGroup delay
         */
        Time::TimeUnit m_groupClock = 0;
        /**
         * \brief The delay between each frame of the AnimationGroup
         */
        unsigned int m_groupDelay = 0;
        /**
         * \brief The current index of the AnimationGroup
         */
        unsigned int m_groupIndex = 0;
        /**
         * \brief The list that contains pointers to all textures in the
         * AnimationGroup
         */
        std::vector<sf::Texture*> m_groupList;
        /**
         * \brief The name of the AnimationGroup
         */
        std::string m_groupName;
        /**
         * \brief Does the AnimationGroup reached the end
         */
        bool m_groupOver = false;
        /**
         * \brief The amount of times the AnimationGroup will be repeated
         */
        int m_loopAmount = 0;
        /**
         * \brief The amount of times the AnimationGroup has been repeated
         */
        int m_loopIndex = 0;
        /**
         * \brief The current texture of the AnimationGroup
         */
        sf::Texture m_texture;

    public:
        /**
         * \brief AnimationGroup constructor
         * \param groupName Name of the AnimationGroup
         */
        explicit AnimationGroup(const std::string& groupName);
        /**
         * \brief Initialize animation (Set image at index 0)
         */
        void build();
        /**
         * \brief Just like AnimationGroup::next without any checks
         */
        void forceNext();
        /**
         * \brief Just like AnimationGroup::previous without any checks
         */
        void forcePrevious();
        /**
         * \brief Get the delay between each frame of the AnimationGroup
         * \return The delay between each frame in milliseconds
         */
        unsigned int getGroupDelay() const;
        /**
         * \brief Get the current index of AnimationGroup
         * \return The index of the texture in the AnimationGroup currently
         * displayed
         */
        unsigned int getGroupIndex() const;
        /**
         * \brief Get the name of the AnimationGroup
         * \return A std::string containing the AnimationGroup's name
         */
        std::string getGroupName() const;
        /**
         * \brief Get the AnimationGroup size
         * \return The number of textures in the AnimationGroup
         */
        unsigned int getGroupSize() const;
        /**
         * \brief Get the current Sprite of the AnimationGroup
         * \return A reference to the sf::Texture currently played by the
         * AnimationGroup
         */
        const sf::Texture& getTexture() const;
        /**
         * \brief Get if the AnimationGroup is done playing
         * \return A boolean which is true if the AnimationGroup's Animation is
         * over
         */
        bool isGroupOver() const;
        /**
         * \brief Increment index of the current texture to be displayed.\n
         *        If max index is reached and no more loops, the AnimationGroup
         * will be over.\n If max index is reached but there is some loops left,
         * index will go back to 0.\n
         */
        void next();
        /**
         * \brief Decrement index of the current texture to be displayed.\n
         *        If index reach 0 and no more loops, the AnimationGroup index
         * will stay at 0.\n If index reach 0 and there is some loops left,
         * index will go at getGroupSize() - 1.
         */
        void previous();
        /**
         * \brief Add a new texture to the AnimationGroup
         * \param texture A pointer of a sf::Texture to add to the
         * AnimationGroup
         */
        void pushTexture(sf::Texture* texture);
        /**
         * \brief Remove the texture at the given index in the AnimationGroup
         * \param index Removes the texture at index
         */
        void removeTextureByIndex(unsigned int index);
        /**
         * \brief Reset the AnimationGroup (Index to 0, Loops to 0, Delay to 0)
         */
        void reset();
        /**
         * \brief Set the delay between each frame of the AnimationGroup
         * \param delay Delay in milliseconds
         */
        void setGroupDelay(unsigned int delay);
        /**
         * \brief Set how many times the AnimationGroup should be replayed
         * before end \param loops Amount of loops to do
         */
        void setGroupLoop(int loops);
        /**
         * \brief Update the Texture to display (Done automatically after
         * previous / next)
         */
        void update();
    };
} // namespace obe::Animation