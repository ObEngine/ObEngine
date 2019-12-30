#pragma once

#include <map>
#include <vector>

#include <Animation/Animation.hpp>
#include <System/Path.hpp>

namespace obe
{
    namespace Graphics
    {
        class LevelSprite;
    }
} // namespace obe

namespace obe::Animation
{
    enum class AnimatorTargetScaleMode
    {
        Fit,
        FixedSize,
        FixedWidth,
        FixedHeight,
        TextureSize
    };

    /**
     * \brief A Class that will manage a set of Animation.\n
     * @Bind
     * Example :
     * \code
     * using obe::Animation::Animator;
     * Animator animator;
     * animator.setPath("Path/To/Animator");
     * animator.loadAnimator();
     * for (std::string& animationName : animator.getAllAnimationName())
     *     std::cout << "Animator contains Animation : " << animationName <<
     * std::endl; animator.setKey("Running"); while (True)
     * {
     *     animator.update();
     *     window.draw(*animator.getSprite());
     * }
     * \endcode
     *
     * The root folder of an Animator is just a simple folder with multiple
     * Animations folders inside. \n Example : \n "Path/To/Animator" : \n
     * - Walking/
     *  - walking_01.png
     *  - walking_02.png
     *    - Walking.ani.vili
     * - Running/
     *  - running_01.png
     *  - running_02.png
     *  - running_03.png
     *  - Running.ani.vili
     */
    class Animator
    {
    private:
        std::unordered_map<std::string, std::unique_ptr<Animation>>
            m_animationSet;
        System::Path m_animatorPath;
        Animation* m_currentAnimation = nullptr;
        std::string m_currentAnimationName = "NONE";
        bool m_paused = false;
        Graphics::LevelSprite* m_target = nullptr;
        AnimatorTargetScaleMode m_targetScaleMode;

    public:
        /**
         * \brief Animator Class default constructor
         */
        Animator();
        /**
         * \brief Animator Class Path constructor (Equivalent to default
         * constructor + Animation::setPath()) \param path Path to the Animator
         * root
         */
        explicit Animator(const System::Path& path);
        /**
         * \brief Clear the Animator of all Animation
         * \param clearMemory Delete the contained Animation in memory
         */
        void clear(bool clearMemory = true);
        /**
         * \brief Get the name of all contained Animation
         * \return A std::vector of std::string containing the name of all
         * contained Animation
         */
        std::vector<std::string> getAllAnimationName() const;
        /**
         * \brief Get the contained Animation pointer by Animation name
         * \param animationName Name of the Animation to get
         * \return A pointer to the wanted Animation.\n
         *         Throws a ObEngine.Animation.Animator.AnimationNotFound if the
         * Animation is not found
         */
        Animation* getAnimation(const std::string& animationName) const;
        /**
         * \brief Get the name of the currently played Animation
         * \return A std::string containing the name of the currently played
         * Animation
         */
        std::string getKey() const;
        /**
         * \brief Get the current offset of the current Sprite
         * \return The current offset of the current Sprite (in pixels)
         */
        Transform::UnitVector getSpriteOffset() const;
        /**
         * \brief Get the current sf::Sprite of the current Animation
         * \return A pointer of the sf::Sprite currently played by the current
         * Animation
         */
        const sf::Texture& getTexture() const;
        /**
         * \brief Call Animation::getTextureAtIndex
         * \param key Name of the Animation where the Texture is located
         * \param index Index of the Texture in the Animation
         * \return A pointer to the Texture
         */
        const sf::Texture& getTextureAtKey(
            const std::string& key, int index) const;
        /**
         * \brief Load the Animator (Using the Animator root path).\n
         *        It will also load all the Animation contained in the Animator.
         *        If an Animator configuration file is found it will load it.
         */
        void loadAnimator();
        /**
         * \brief Set the Animation to play by name
         * \param key A std::string containing the name of the Animation to
         * play.\n Throws a ObEngine.Animation.Animator.AnimationNotFound
         * exception if the Animation key is not found.
         */
        void setKey(const std::string& key);
        /**
         * \brief Set the path of the Animator root
         * \param path System::Path pointing to the Animator root
         */
        void setPath(const System::Path& path);
        /**
         * \brief Set the path of the Animator root
         * \param path std::string pointing to the Animator root (later
         * converted to System::Path)
         */
        void setPath(const std::string& path);
        /**
         * \brief Start or Pause the Animator (won't do anything even if
         * updated) \param pause true if the Animator should pause, false
         * otherwise
         */
        void setPaused(bool pause);
        /**
         * \brief Update the Animator and the currently played Animation
         */
        void update();

        void setTarget(Graphics::LevelSprite& sprite,
            AnimatorTargetScaleMode targetScaleMode
            = AnimatorTargetScaleMode::Fit);
    };
} // namespace obe::Animation
