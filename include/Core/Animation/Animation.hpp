#pragma once

#include <unordered_map>

#include <Animation/AnimationGroup.hpp>
#include <System/Path.hpp>
#include <Time/TimeUtils.hpp>
#include <Types/Serializable.hpp>
#include <Types/SmartEnum.hpp>


namespace obe
{
    namespace engine
    {
        class ResourceManager;
    }
    namespace graphics
    {
        class Texture;
    }
    namespace system
    {
        class Path;
    }
} // namespace obe

namespace vili
{
    class node;
}

namespace obe::animation
{
    /**
     * \brief The Play Mode of an Animation.
     *        It indicates whether an Animation can be interrupted or not and
     *        what to do when the Animation is over
     * TODO: /bind{AnimationPlayMode}
     */
    enum class AnimationPlayMode
    {
        /**
         * \brief The Animation will play once and stay at last texture
         */
        OneTime,
        /**
         * \brief The Animation will play on a loop and can be interrupted any
         *        time
         */
        Loop,
        /**
         * \brief The Animation will be played once and can't be interrupted
         */
        Force
    };

    using AnimationPlayModeMeta = types::SmartEnum<AnimationPlayMode>;

    enum class AnimationCommand
    {
        /**
         * \brief Wait for a given amount of seconds
         */
        Wait,
        /**
         * \brief Play an AnimationGroup with a given name
         */
        PlayGroup,
        /**
         * \brief Change Animation
         */
        SetAnimation
    };

    using AnimationCommandMeta = types::SmartEnum<AnimationCommand>;

    /**
     * \brief The AnimationStatus indicates whether the current Animation should
     *        continue to play or call another one.
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
         *        using Animation::get_next_animation().
         */
        Call
    };

    class Animation;

    class AnimationState
    {
    private:
        const Animation& m_parent;
        std::unordered_map<std::string, std::unique_ptr<AnimationGroup>> m_groups;
        std::size_t m_code_index = 0;
        bool m_feed_instructions = true;
        AnimationGroup* m_current_group = nullptr;
        std::string m_next_animation_name;
        bool m_over = false;
        AnimationStatus m_status = AnimationStatus::Play;
        time::TimeUnit m_clock = 0;
        time::TimeUnit m_sleep = 0;

        void execute_instruction();
        void update_current_group();
        void set_active_animation_group(const std::string& group_name);

    public:
        AnimationState(const Animation& parent);
        void load();
        /**
         * \brief Get the Animation Status
         * \return An enum value containing the AnimationStatus, it can be one
         *         of these modes :
         *         - AnimationStatus::Play
         *         - AnimationStatus::Call
         */
        [[nodiscard]] AnimationStatus get_status() const noexcept;
        /**
         * \brief Get the name of the Animation to call when the AnimationStatus
         *        of the Animation is equal to AnimationStatus::Call
         * \return A std::string containing the name of the Animation that will be called.
         */
        [[nodiscard]] std::string get_next_animation() const noexcept;
        /**
         * \brief Get AnimationGroup pointer by group_name.
         *        It will throw a
         *        ObEngine.Animation.Animation.AnimationGroupNotFound if the
         *        AnimationGroup is not found.
         * \param group_name The name of the
         *        AnimationGroup to return
         * \return A pointer to the AnimationGroup
         * \throw UnknownAnimationGroup if the group does not exists
         */
        AnimationGroup& get_animation_group(const std::string& group_name);
        /**
         * \brief Get the name of the current AnimationGroup
         * \return A std::string containing the name of the current
         *         AnimationGroup
         */
        [[nodiscard]] std::string get_current_animation_group() const noexcept;
        /**
         * \brief Get the current Texture displayed by the Animation
         * \return A reference to the currently displayed Texture
         */
        const graphics::TexturePart& get_current_texture() const;
        /**
         * \brief Return whether the Animation is over or not
         * \return true if the Animation is over, false otherwise
         */
        [[nodiscard]] bool is_over() const noexcept;
        /**
         * \brief Reset the Animation (Unselect current AnimationGroup and
         *        restart AnimationCode)
         */
        void reset() noexcept;
        /**
         * \brief Update the Animation (Updates the current AnimationGroup,
         *        executes the AnimationCode)
         */
        void update();
        const Animation& get_animation() const;

        [[nodiscard]] uint32_t get_current_frame_index() const;
    };

    /**
     * \brief A whole Animation that contains one or more AnimationGroup.
     *
     */
    class Animation : public types::Serializable
    {
    private:
        AnimationState m_default_state;
        std::string m_name;
        std::unordered_map<std::string, std::unique_ptr<AnimationGroup>> m_groups;

        bool m_anti_aliasing = false;
        time::TimeUnit m_delay = 0;

        std::vector<vili::node> m_code;

        std::vector<graphics::Texture> m_textures;
        std::vector<graphics::TexturePart> m_frames;
        std::unordered_map<uint32_t, vili::node> m_frames_metadata;

        AnimationPlayMode m_play_mode = AnimationPlayMode::OneTime;

        system::Path m_path;
        engine::ResourceManager* m_resource_manager = nullptr;

        int m_priority = 0;

        void load_source(const vili::node& source);
        void load_frames_metadata(const vili::node& metadata);
        void load_groups(const vili::node& groups);
        void load_code(const vili::node& code);

        [[nodiscard]] const graphics::Texture& load_texture(const std::string& local_path);

        friend class AnimationState;

    public:
        Animation(const system::Path& path, engine::ResourceManager* resources = nullptr);
        Animation(const Animation&) = delete;
        /**
         * \todo Make Animation a serializable type instead of this "apply_parameters"
         * \brief Apply global Animation parameters (Sprite offset and priority)
         * \param parameters A vili::node that contains the
         *        following optional parameters :
         *        - spriteOffsetX : x Coordinate of the Sprite Offset in the Animation in
         *                          pixels.
         *        - spriteOffsetY : y Coordinate of the Sprite Offset in the Animation in
         *                          pixels.
         *        - priority : Priority of the Animation (A higher Animation
         *                     priority can't be interrupted by an Animation with a
         *                     lower one).
         */
        void apply_parameters(vili::node& parameters);
        /**
         * \brief Get the name of all contained AnimationGroup of the Animation
         * \return An array of strings with all the names of the
         *         AnimationGroup
         */
        [[nodiscard]] std::vector<std::string> get_all_animation_groups_names() const;
        /**
         * \brief Get the default delay of the Animation.
         *        The delay will be transferred to AnimationGroup children if not
         *        specified.
         *        The delay represents the amount of seconds between each frame of
         *        the Animation
         * \return The default delay of the Animation in seconds.
         */
        [[nodiscard]] time::TimeUnit get_delay() const noexcept;
        /**
         * \brief Get AnimationGroup pointer by group_name.
         *        It will throws a
         *        ObEngine.Animation.Animation.AnimationGroupNotFound if the
         *        AnimationGroup is not found.
         * \param group_name The name of the
         *        AnimationGroup to return
         * \return A pointer to the AnimationGroup
         * \throw UnknownAnimationGroup if the group does not exists
         */
        AnimationGroup& get_animation_group(const std::string& group_name);
        /**
         * \brief Get the Animation name
         * \return A string containing the name of the Animation
         */
        [[nodiscard]] std::string get_name() const noexcept;

        /**
         * \brief Get the Animation Play Mode
         * \return An enum value containing the AnimationPlayMode, it can be one
         *         of these modes :
         *         - AnimationPlayMode::OneTime
         *         - AnimationPlayMode::Loop
         *         - AnimationPlayMode::Force
         */
        [[nodiscard]] AnimationPlayMode get_play_mode() const noexcept;
        /**
         * \brief Get the Animation Status
         * \return An enum value containing the AnimationStatus, it can be one
         *         of these modes :
         *         - AnimationStatus::Play
         *         - AnimationStatus::Call
         */
        [[nodiscard]] AnimationStatus get_status() const noexcept;
        /**
         * \brief Get the name of the Animation to call when the AnimationStatus
         *        of the Animation is equal to AnimationStatus::Call
         * \return A std::string containing the name of the Animation that will be called.
         */
        [[nodiscard]] std::string get_next_animation() const noexcept;
        /**
         * \brief Get the name of the current AnimationGroup
         * \return A std::string containing the name of the current
         *         AnimationGroup
         */
        [[nodiscard]] std::string get_current_animation_group() const noexcept;
        /**
         * \brief Return the Animation priority
         * \return An int containing the priority of the Animation.
         *         Higher value is higher priority = Can't be interrupted by
         *         lower priority.
         */
        [[nodiscard]] int get_priority() const noexcept;
        /**
         * \brief Get the current Texture displayed by the Animation
         * \return A reference to the currently displayed Texture
         */
        [[nodiscard]] const graphics::TexturePart& get_current_texture() const;
        /**
         * \brief Get the texture used in the Animation at the specified index
         * \param index Index of the texture to return.
         * \return A reference to the Texture at the given index
         */
        [[nodiscard]] const graphics::TexturePart& get_texture_at_index(int index);
        /**
         * \brief Return whether the Animation is over or not
         * \return true if the Animation is over, false otherwise
         */
        [[nodiscard]] bool is_over() const noexcept;
        /**
         * \brief Reset the Animation (Unselect current AnimationGroup and
         *        restart AnimationCode)
         */
        void reset() noexcept;
        /**
         * \brief Update the Animation (Updates the current AnimationGroup,
         *        executes the AnimationCode)
         */
        void update();
        /**
         * \brief Enables or disables anti-aliasing for textures of this animation
         * \param anti_aliasing should be true to enable anti_aliasing, false otherwise
         */
        void set_anti_aliasing(bool anti_aliasing) noexcept;
        /**
         * \brief Gets the anti-aliasing status for the Animation
         */
        [[nodiscard]] bool is_anti_aliased() const noexcept;
        [[nodiscard]] AnimationState make_state() const;

        [[nodiscard]] vili::node get_frame_metadata(uint32_t frame_index) const; 
        [[nodiscard]] uint32_t get_frames_amount() const;
        [[nodiscard]] uint32_t get_current_frame_index() const;

        [[nodiscard]] vili::node dump() const override;
        void load(const vili::node& data) override;
        [[nodiscard]] vili::node schema() const override;
    };
} // namespace obe::animation
