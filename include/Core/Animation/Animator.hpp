#pragma once

#include <map>
#include <vector>

#include <Animation/Animation.hpp>
#include <System/Path.hpp>

namespace obe::Graphics
{
    class Sprite;
} // namespace obe

namespace obe::Animation
{
    /**
     * \brief Sets the scaling bevaviour the Animator will apply on target
     * \bind{Animator.TargetScaleMode}
     */
    enum class AnimatorTargetScaleMode
    {
        // Fits the animation texture into the target's size, ignoring the ratio
        Fit,
        // Animation texture will have target's width, height will be ajusted with correct
        // ratio
        FixedWidth,
        // Animation texture will have target's height, width will be ajusted with correct
        // ratio
        FixedHeight,
        // Animation texture will keep its size, ignoring target's size
        TextureSize
    };

    /**
     * \brief A Class that will manage a set of Animation
     * \bind{Animator}
     */
    class Animator
    {
    private:
        std::unordered_map<std::string, std::unique_ptr<Animation>> m_animations;
        System::Path m_path;
        Animation* m_currentAnimation = nullptr;
        bool m_paused = false;
        Graphics::Sprite* m_target = nullptr;
        AnimatorTargetScaleMode m_targetScaleMode = AnimatorTargetScaleMode::Fit;

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
        const sf::Texture& getTextureAtKey(const std::string& key, int index) const;
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

        void setTarget(Graphics::Sprite& sprite,
            AnimatorTargetScaleMode targetScaleMode = AnimatorTargetScaleMode::Fit);
    };
} // namespace obe::Animation
