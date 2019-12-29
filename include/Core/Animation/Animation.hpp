#pragma once

#include <unordered_map>

#include <vili/Vili.hpp>

#include <Animation/AnimationGroup.hpp>
#include <System/Path.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::Animation
{
    /**
     * \brief The Play Mode of an Animation.\n
     * It indicates whether an Animation can be interrupted or not and
     * what to do when the Animation is over
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
     * form to an AnimationPlayMode enum value \param animationPlayMode The
     * std::string containing the AnimationPlayMode in string form \return The
     * converted value which is an AnimationPlayMode enum value
     */
    AnimationPlayMode stringToAnimationPlayMode(
        const std::string& animationPlayMode);

    /**
     * \brief The AnimationStatus indicates whether the current Animation should
     * continue to play or call another one.
     */
    enum class AnimationStatus
    {
        /**
         * \brief The Animation continues to play.
         */
        Play,
        /**
         * \brief The Animation will call another one.\n
         * The name of the Animation to call is stored in
         * m_animationToCall.\n You can also get the Animation name to call by
         * using Animation::getCalledAnimation().
         */
        Call
    };

    /**
     * \brief A whole Animation that contains one or more AnimationGroup.
     * @Bind
     */
    class Animation
    {
    private:
        Time::TimeUnit m_animationClock = 0;
        std::vector<std::vector<std::string>> m_animationCode;
        unsigned int m_animationDelay = 0;
        std::unordered_map<std::string, std::unique_ptr<AnimationGroup>>
            m_animationGroupMap;
        std::string m_animationName;
        AnimationPlayMode m_animationPlayMode = AnimationPlayMode::OneTime;
        std::vector<sf::Texture*> m_animationTextures;
        std::string m_animationToCall = "";
        bool m_askCommand = true;
        unsigned int m_codeIndex = 0;
        int m_currentDelay = 0;
        std::string m_currentGroupName = "NONE";
        AnimationStatus m_currentStatus = AnimationStatus::Play;
        bool m_isOver = false;
        int m_loopAmount = 0;
        Transform::UnitVector m_offset;
        int m_priority = 0;
        bool m_antiAliasing = false;

    public:
        /**
         * \brief Apply global Animation parameters (Sprite offset and priority)
         * \param parameters A vili::ComplexAttribute that contains the
         * following facultative parameters :\n
         * - spriteOffsetX : x Coordinate of the Sprite Offset in the Animation
         * in pixels.\n
         * - spriteOffsetY : y Coordinate of the Sprite Offset in the Animation
         * in pixels.\n
         * - priority : Priority of the Animation (A higher Animation priority
         * can't be interrupted by an Animation with a lower one).
         */
        void applyParameters(vili::ComplexNode& parameters);
        /**
         * \brief Get the name of all contained AnimationGroup of the Animation
         * \return A std::vector of std::string with all the names of the
         * AnimationGroup
         */
        std::vector<std::string> getAllAnimationGroupName() const;
        /**
         * \brief Get the default delay of the Animation.\n
         *        The delay will be transfered to AnimationGroup children if not
         * specified. \return The default delay of the Animation in
         * milliseconds.
         */
        unsigned int getAnimationDelay() const;
        /**
         * \brief Get AnimationGroup pointer by groupName.\n
         *          It will throws a
         * ObEngine.Animation.Animation.AnimationGroupNotFound if the
         * AnimationGroup is not found. \param groupName The name of the
         * AnimationGroup to return \return A pointer to the AnimationGroup
         */
        AnimationGroup* getAnimationGroup(const std::string& groupName);
        /**
         * \brief Get the Animation name
         * \return A std::string containing the name of the Animation
         */
        std::string getAnimationName() const;

        /**
         * \brief Get the Animation Play Mode
         * \return An enum value containing the AnimationPlayMode, it can be one
         * of these modes :\n
         *           - AnimationPlayMode::OneTime\n
         *           - AnimationPlayMode::Loop\n
         *         - AnimationPlayMode::Force\n
         */
        AnimationPlayMode getAnimationPlayMode() const;
        /**
         * \brief Get the Animation Status
         * \return An enum value containing the AnimationStatus, it can be one
         * of these modes ;\n
         * - AnimationStatus::Play\n
         * - AnimationStatus::Call\n
         */
        AnimationStatus getAnimationStatus() const;
        /**
         * \brief Get the name of the Animation to call when the AnimationStatus
         * of the Animation is equal to AnimationStatus::Call \return A
         * std::string containing the name of the Animation that will be called.
         */
        std::string getCalledAnimation() const;
        /**
         * \brief Get the name of the current AnimationGroup
         * \return A std::string containing the name of the current
         * AnimationGroup
         */
        std::string getCurrentAnimationGroup() const;
        /**
         * \brief Return the Animation priority
         * \return An int containing the priority of the Animation.\n
         *         Higher value is higher priority = Can't be interrupted by
         * lower priority.
         */
        int getPriority() const;
        /**
         * \brief Get the Sprite Offset ((0, 0) if not defined)
         * \return An UnitVector containing the Sprite offset (in pixels)
         */
        Transform::UnitVector getSpriteOffset() const;
        /**
         * \brief Get the sf::Texture containing the current texture in the
         * Animation \return A reference to the currently displayed Texture
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
        bool isAnimationOver() const;
        /**
         * \brief Configure an Animation using the Animation configuration file
         * (Vili file) \param path System::Path to the Animation config file
         * (.ani.vili file extension)
         */
        void loadAnimation(const System::Path& path);
        /**
         * \brief Reset the Animation (Unselect current AnimationGroup and
         * restart AnimationCode)
         */
        void reset();
        /**
         * \brief Update the Animation (Updates the current AnimationGroup,
         * executes the AnimationCode)
         */
        void update();

        void setAntiAliasing(bool antiAliasing);
        bool getAntiAliasing();
    };
} // namespace obe::Animation