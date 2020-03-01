#pragma once

#include <unordered_map>

#include <vili/Vili.hpp>

#include <Animation/AnimationGroup.hpp>
#include <System/Path.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::Animation
{
    /**
     * \brief The Play Mode of an Animation.
     *        It indicates whether an Animation can be interrupted or not and
     *        what to do when the Animation is over
     * \bind{AnimationPlayMode}
     */
    enum class AnimationPlayMode
    {
        /**
         * \brief The Animation will play once and stay at last texture
         */
        OneTime,
        /**
         * \brief The Animation will play on a loop and can be interrupted any
         * time
         */
        Loop,
        /**
         * \brief The Animation will be played once and can't be interrupted
         */
        Force
    };

    /**
     * \brief Convert a std::string containing an AnimationPlayMode in string
     *        form to an AnimationPlayMode enum value
     * \param animationPlayMode The std::string containing the AnimationPlayMode in string
     *        form
     * \return The converted value which is an AnimationPlayMode enum value
     * \bind{[mt]AnimationPlayMode.__call}
     */
    AnimationPlayMode stringToAnimationPlayMode(const std::string& animationPlayMode);

    /**
     * \brief The AnimationStatus indicates whether the current Animation should
     *        continue to play or call another one.
     * \bind{AnimationStatus}
     */
    enum class AnimationStatus
    {
        /**
         * \brief The Animation continues to play.
         */
        Play,
        /**
         * \brief The Animation will call another one.
         *        The name of the Animation to call is stored in
         *        m_nextAnimation. You can also get the Animation name to call by
         *        using Animation::getCalledAnimation().
         */
        Call
    };

    /**
     * \brief A whole Animation that contains one or more AnimationGroup.
     * \bind{Animation}
     */
    class Animation
    {
    private:
        std::string m_name;

        Time::TimeUnit m_clock = 0;
        unsigned int m_delay = 0;
        unsigned int m_sleep = 0;

        std::vector<std::vector<std::string>> m_code;
        unsigned int m_codeIndex = 0;
        bool m_feedInstructions = true;

        std::vector<sf::Texture*> m_textures;
        std::unordered_map<std::string, std::unique_ptr<AnimationGroup>> m_groups;
        std::string m_currentGroupName = "NONE";
        std::string m_nextAnimation = "";

        AnimationPlayMode m_playMode = AnimationPlayMode::OneTime;
        AnimationStatus m_status = AnimationStatus::Play;

        bool m_over = false;
        int m_priority = 0;
        bool m_antiAliasing = false;

        void executeInstruction();
        void updateCurrentGroup();

    public:
        /**
         * \todo Make Animation a serializable type instead of this "applyParameters"
         * \brief Apply global Animation parameters (Sprite offset and priority)
         * \param parameters A vili::ComplexAttribute that contains the
         *        following facultative parameters :
         *        - spriteOffsetX : x Coordinate of the Sprite Offset in the Animation in
         *                          pixels.
         *        - spriteOffsetY : y Coordinate of the Sprite Offset in the Animation in
         *                          pixels.
         *        - priority : Priority of the Animation (A higher Animation
         *                     priority can't be interrupted by an Animation with a
         *                     lower one).
         */
        void applyParameters(vili::ComplexNode& parameters);
        /**
         * \brief Get the name of all contained AnimationGroup of the Animation
         * \return A std::vector of std::string with all the names of the
         *         AnimationGroup
         */
        std::vector<std::string> getAllAnimationGroupName() const;
        /**
         * \brief Get the default delay of the Animation.
         *        The delay will be transfered to AnimationGroup children if not
         *        specified.
         * \return The default delay of the Animation in milliseconds.
         */
        unsigned int getDelay() const;
        /**
         * \brief Get AnimationGroup pointer by groupName.\n
         *        It will throws a
         *        ObEngine.Animation.Animation.AnimationGroupNotFound if the
         *        AnimationGroup is not found.
         * \param groupName The name of the
         *        AnimationGroup to return
         * \return A pointer to the AnimationGroup
         */
        AnimationGroup* getAnimationGroup(const std::string& groupName);
        /**
         * \brief Get the Animation name
         * \return A std::string containing the name of the Animation
         */
        std::string getName() const;

        /**
         * \brief Get the Animation Play Mode
         * \return An enum value containing the AnimationPlayMode, it can be one
         *         of these modes :
         *         - AnimationPlayMode::OneTime
         *         - AnimationPlayMode::Loop
         *         - AnimationPlayMode::Force
         */
        AnimationPlayMode getPlayMode() const;
        /**
         * \brief Get the Animation Status
         * \return An enum value containing the AnimationStatus, it can be one
         *         of these modes :
         *         - AnimationStatus::Play
         *         - AnimationStatus::Call
         */
        AnimationStatus getStatus() const;
        /**
         * \brief Get the name of the Animation to call when the AnimationStatus
         *        of the Animation is equal to AnimationStatus::Call
         * \return A std::string containing the name of the Animation that will be called.
         */
        std::string getCalledAnimation() const;
        /**
         * \brief Get the name of the current AnimationGroup
         * \return A std::string containing the name of the current
         *         AnimationGroup
         */
        std::string getCurrentAnimationGroup() const;
        /**
         * \brief Return the Animation priority
         * \return An int containing the priority of the Animation.
         *         Higher value is higher priority = Can't be interrupted by
         *         lower priority.
         */
        int getPriority() const;
        /**
         * \brief Get the sf::Texture containing the current texture in the
         *        Animation
         * \return A reference to the currently displayed Texture
         */
        const sf::Texture& getTexture();
        /**
         * \brief Get the texture used in the Animation at the specified index
         * \param index Index of the texture to return.
         * \return A reference to the sf::Texture at the given index
         */
        const sf::Texture& getTextureAtIndex(int index);
        /**
         * \brief Return whether the Animation is over or not
         * \return true if the Animation is over, false otherwise
         */
        bool isOver() const;
        /**
         * \brief Configure an Animation using the Animation configuration file
         *        (Vili file)
         * \param path System::Path to the Animation config file
         *        (.ani.vili file extension)
         */
        void loadAnimation(const System::Path& path);
        /**
         * \brief Reset the Animation (Unselect current AnimationGroup and
         *        restart AnimationCode)
         */
        void reset();
        /**
         * \brief Update the Animation (Updates the current AnimationGroup,
         *        executes the AnimationCode)
         */
        void update();
        /**
         * \brief Enables or disables anti-aliasing for textures of this animation
         * \param antiAliasing should be true to enable antiAliasing, false otherwise
         */
        void setAntiAliasing(bool antiAliasing);
        /**
         * \brief Gets the anti-aliasing status for the Animation
         */
        bool getAntiAliasing();
    };
} // namespace obe::Animation