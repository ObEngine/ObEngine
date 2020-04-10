#pragma once

#include <vector>

#include <Animation/Animation.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Texture.hpp>
#include <System/Path.hpp>

namespace obe::Animation
{
    /**
     * \brief Sets the scaling behaviour the Animator will apply on target
     * \bind{Animator.TargetScaleMode}
     */
    enum class AnimatorTargetScaleMode
    {
        // Fits the animation texture into the target's size, ignoring the ratio
        Fit,
        // Animation texture will have target's width, height will be adjusted with correct
        // ratio
        FixedWidth,
        // Animation texture will have target's height, width will be adjusted with correct
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
        Animation* m_currentAnimation = nullptr;
        bool m_paused = false;
        System::Path m_path;
        Graphics::Sprite* m_target = nullptr;
        AnimatorTargetScaleMode m_targetScaleMode = AnimatorTargetScaleMode::Fit;
        void applyTexture() const;

    public:
        /**
         * \brief Clear the Animator of all Animation
         */
        void clear() noexcept;
        /**
         * \brief Get the name of all contained Animation
         * \return A std::vector of std::string containing the name of all
         *         contained Animation
         */
        [[nodiscard]] std::vector<std::string> getAllAnimationName() const;
        /**
         * \brief Get the contained Animation pointer by Animation name
         * \param animationName Name of the Animation to get
         * \return A pointer to the wanted Animation.
         *         Throws a ObEngine.Animation.Animator.AnimationNotFound if the
         *         Animation is not found
         */
        [[nodiscard]] Animation& getAnimation(const std::string& animationName) const;
        /**
         * \brief Get the name of the currently played Animation
         * \return A std::string containing the name of the currently played
         *         Animation
         */
        [[nodiscard]] std::string getKey() const noexcept;
        /**
         * \brief Get the current Sprite of the current Animation
         * \return A pointer of the Sprite currently played by the current
         *         Animation
         */
        [[nodiscard]] const Graphics::Texture& getTexture() const;
        /**
         * \brief Call Animation::getTextureAtIndex
         * \param key Name of the Animation where the Texture is located
         * \param index Index of the Texture in the Animation
         * \return A pointer to the Texture
         */
        [[nodiscard]] const Graphics::Texture& getTextureAtKey(
            const std::string& key, int index) const;
        /**
         * \brief Loads the Animator
         *        It will also load all the Animation contained in the Animator.
         *        If an Animator configuration file is found it will load it.
         */
        void load(System::Path path, Engine::ResourceManager* resources = nullptr);
        /**
         * \brief Set the Animation to play by name
         * \param key A std::string containing the name of the Animation to
         *        play.
         * \throw UnknownAnimation if the Animation key is not found.
         */
        void setKey(const std::string& key);
        /**
         * \brief Start or Pause the Animator (won't do anything even if
         *        updated)
         * \param pause true if the Animator should pause, false
         *        otherwise
         */
        void setPaused(bool pause) noexcept;
        /**
         * \brief Update the Animator and the currently played Animation
         */
        void update();

        void setTarget(Graphics::Sprite& sprite,
            AnimatorTargetScaleMode targetScaleMode = AnimatorTargetScaleMode::Fit);
    };
} // namespace obe::Animation
