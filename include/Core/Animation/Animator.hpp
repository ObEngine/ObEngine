#pragma once

#include <Animation/Animation.hpp>
#include <System/Path.hpp>
#include <vector>

namespace obe
{
    namespace graphics
    {
        class Sprite;
        class Texture;
    } // namespace graphics
} // namespace obe

/**
 * \additionalinclude{Graphics/Sprite.hpp}
 */
namespace obe::animation
{
    class Animator;
    /**
     * \brief Sets the scaling behaviour the Animator will apply on target
     */
    enum class AnimatorTargetScaleMode
    {
        // Fits the animation texture into the target's size, ignoring the ratio
        Fit,
        KeepRatio,
        // animation texture will have target's width, height will be adjusted with correct
        // ratio
        FixedWidth,
        // animation texture will have target's height, width will be adjusted with correct
        // ratio
        FixedHeight,
        // animation texture will keep its size, ignoring target's size
        TextureSize
    };
    using AnimatorTargetScaleModeMeta = types::SmartEnum<AnimatorTargetScaleMode>;

    class AnimatorState
    {
    private:
        std::unordered_map<std::string, std::unique_ptr<AnimationState>> m_states;
        const Animator& m_parent;
        AnimationState* m_current_animation = nullptr;
        bool m_paused = false;
        graphics::Sprite* m_target = nullptr;
        AnimatorTargetScaleMode m_target_scale_mode = AnimatorTargetScaleMode::Fit;

        void apply_texture() const;

    public:
        AnimatorState(const Animator& parent);
        /**
         * \brief Get the name of the currently played Animation
         * \return A std::string containing the name of the currently played
         *         Animation
         */
        void load();
        [[nodiscard]] std::string get_current_animation_name() const noexcept;
        /**
         * \brief Set the Animation to play by name
         * \param key A std::string containing the name of the Animation to
         *        play.
         * \throw UnknownAnimation if the Animation key is not found.
         */
        void set_animation(const std::string& key);
        /**
         * \brief Start or Pause the Animator (won't do anything even if
         *        updated)
         * \param pause true if the Animator should pause, false
         *        otherwise
         */
        void set_paused(bool pause) noexcept;
        /**
         * \brief Update the Animator and the currently played Animation
         */
        void update();
        void set_target(graphics::Sprite& sprite,
            AnimatorTargetScaleMode target_scale_mode = AnimatorTargetScaleMode::Fit);
        void reset();
        [[nodiscard]] graphics::Sprite* get_target() const;
        [[nodiscard]] AnimationState* get_current_animation() const;
        [[nodiscard]] const graphics::TexturePart& get_current_texture() const;
        [[nodiscard]] const Animator& get_animator() const;
    };

    /**
     * \brief A Class that will manage a set of Animation
     *
     */
    class Animator
    {
    private:
        AnimatorState m_default_state;
        std::unordered_map<std::string, std::unique_ptr<Animation>> m_animations;
        system::Path m_path;

        friend class AnimatorState;

    public:
        Animator();
        Animator(const Animator&) = delete;
        /**
         * \brief Clear the Animator of all Animation
         */
        void clear() noexcept;
        /**
         * \brief Get the name of all contained Animation
         * \return A std::vector of std::string containing the name of all
         *         contained Animation
         */
        [[nodiscard]] std::vector<std::string> get_all_animations_names() const;
        /**
         * \brief Get the contained Animation pointer by Animation name
         * \param animation_name Name of the Animation to get
         * \return A pointer to the wanted Animation.
         *         Throws a ObEngine.Animation.Animator.AnimationNotFound if the
         *         Animation is not found
         */
        [[nodiscard]] Animation& get_animation(const std::string& animation_name) const;
        /**
         * \brief Get the name of the currently played Animation
         * \return A std::string containing the name of the currently played
         *         Animation
         */
        [[nodiscard]] std::string get_current_animation_name() const noexcept;
        /**
         * \brief Get the current texture of the current Animation
         * \return A reference to the texture currently played by the current
         *         Animation
         */
        [[nodiscard]] const graphics::TexturePart& get_current_texture() const;
        /**
         * \brief Loads the Animator
         *        It will also load all the Animation contained in the Animator.
         *        If an Animator configuration file is found it will load it.
         */
        void load(system::Path path, engine::ResourceManager* resources = nullptr);
        /**
         * \brief Set the Animation to play by name
         * \param key A std::string containing the name of the Animation to
         *        play.
         * \throw UnknownAnimation if the Animation key is not found.
         */
        void set_animation(const std::string& key);
        /**
         * \brief Start or Pause the Animator (won't do anything even if
         *        updated)
         * \param pause true if the Animator should pause, false
         *        otherwise
         */
        void set_paused(bool pause) noexcept;
        /**
         * \brief Update the Animator and the currently played Animation
         */
        void update();

        void set_target(graphics::Sprite& sprite,
            AnimatorTargetScaleMode target_scale_mode = AnimatorTargetScaleMode::Fit);

        [[nodiscard]] system::Path get_filesystem_path() const;

        [[nodiscard]] AnimatorState make_state() const;
    };
} // namespace obe::animation
