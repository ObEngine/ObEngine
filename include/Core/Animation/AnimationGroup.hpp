#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <Graphics/Texture.hpp>
#include <Time/TimeUtils.hpp>

namespace obe::Animation
{
    /**
     * \brief A sub-part of an Animation containing the Textures to display
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
        Time::TimeUnit m_delay = 0;
        /**
         * \brief The current frame index of the AnimationGroup
         */
        std::size_t m_index = 0;
        /**
         * \brief The list that contains pointers to all textures in the
         *        AnimationGroup
         */
        std::vector<Graphics::Texture> m_groupList;
        /**
         * \brief The name of the AnimationGroup
         */
        std::string m_name;
        /**
         * \brief Does the AnimationGroup reached the end
         */
        bool m_over = false;
        /**
         * \brief The amount of times the AnimationGroup will be repeated
         */
        int m_loopAmount = 0;
        /**
         * \brief The amount of times the AnimationGroup has been repeated
         */
        int m_loopIndex = 0;

        bool checkDelay();

    public:
        /**
         * \brief AnimationGroup constructor
         * \param name Name of the AnimationGroup
         */
        explicit AnimationGroup(std::string name);
        /**
         * \brief Get the delay between each frame of the AnimationGroup
         * \return The delay between each frame in milliseconds
         */
        [[nodiscard]] Time::TimeUnit getDelay() const noexcept;
        /**
         * \brief Get the current index of AnimationGroup
         * \return The index of the texture in the AnimationGroup currently
         *         displayed
         */
        [[nodiscard]] std::size_t getIndex() const noexcept;
        /**
         * \brief Get the name of the AnimationGroup
         * \return A std::string containing the AnimationGroup's name
         */
        [[nodiscard]] std::string getName() const noexcept;
        /**
         * \brief Get the AnimationGroup size
         * \return The number of textures in the AnimationGroup
         */
        [[nodiscard]] std::size_t getSize() const noexcept;
        /**
         * \brief Get the current Sprite of the AnimationGroup
         * \return A reference to the Texture currently played by the
         *         AnimationGroup
         */
        [[nodiscard]] const Graphics::Texture& getTexture() const;
        /**
         * \brief Get if the AnimationGroup is done playing
         * \return A boolean which is true if the AnimationGroup's Animation is
         *         over
         */
        [[nodiscard]] bool isOver() const noexcept;
        /**
         * \brief Increment index of the current texture to be displayed.
         *        - If max index is reached and no more loops, the AnimationGroup
         *        will be over.
                  - If max index is reached but there is some loops left,
         *        index will go back to 0.
         * \param force Force increments the index of the AnimationGroup without waiting
         *        for the delay if force is true
         */
        void next(bool force = false);
        /**
         * \brief Decrement index of the current texture to be displayed.
         *        - If index reach 0 and no more loops, the AnimationGroup index
         *        will stay at 0.
         *        - If index reach 0 and there is some loops left,
         *        index will go at getSize() - 1.
         * \param force Force decrements the index of the AnimationGroup without waiting
         *        for the delay if force is true
         */
        void previous(bool force = false);
        /**
         * \todo Add a way to specify the index of the texture
         * \brief Add a new texture to the AnimationGroup
         * \param texture A pointer of a Texture to add to the
         *        AnimationGroup
         */
        void pushTexture(const Graphics::Texture& texture);
        /**
         * \brief Remove the texture at the given index in the AnimationGroup
         * \param index Removes the texture at index
         */
        void removeTextureByIndex(std::size_t index);
        /**
         * \brief Reset the AnimationGroup (Index to 0, Loops to 0, Delay to 0)
         */
        void reset() noexcept;
        /**
         * \brief Set the delay between each frame of the AnimationGroup
         * \param delay Delay in milliseconds
         */
        void setDelay(Time::TimeUnit delay) noexcept;
        /**
         * \brief Set how many times the AnimationGroup should be replayed
         *        before end
         * \param loops Amount of loops to do
         */
        void setLoops(int loops) noexcept;
    };
} // namespace obe::Animation