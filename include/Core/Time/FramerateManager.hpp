#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <System/Window.hpp>
#include <Time/TimeUtils.hpp>
#include <optional>
#include <vili/node.hpp>

namespace obe::time
{
    /**
     * \brief Class that handles Framerate, DeltaTime and stuff related to time
     */
    class FramerateManager
    {
    private:
        system::Window& m_window;
        time::TimeUnit m_clock;
        double m_delta_time = 0.0;
        double m_speed_coefficient = 1.0;
        std::optional<unsigned int> m_framerate_target;
        bool m_vsync_enabled = true;
        int m_current_frame = 0;
        int m_frame_progression = 0;
        bool m_need_to_render = false;
        bool m_sync_update_render = true;
        double m_max_delta_time = 0.1;

    public:
        /**
         * \brief Creates a new FramerateManager
         */
        FramerateManager(system::Window& window);
        /**
         * \brief Configures the FramerateManager
         * \param config Configuration of the FramerateManager
         */
        void configure(vili::node& config);
        /**
         * \brief Updates the FramerateManager (done every time in the main loop)
         */
        void update();
        /**
         * \brief Get if the engine should render everything
         * \return true if the engine should render everything, false otherwise
         */
        [[nodiscard]] bool should_render() const;
        [[nodiscard]] bool should_update() const;
        void start();
        void reset();
        /**
         * \brief Get the DeltaTime
         * \return A double containing the DeltaTime
         */
        [[nodiscard]] TimeUnit get_raw_delta_time() const;
        /**
         * \brief Get the GameSpeed (DeltaTime * SpeedCoefficient)
         * \return A double containing the GameSpeed
         */
        [[nodiscard]] double get_delta_time() const;
        /**
         * \brief Get the SpeedCoefficient
         * \return A double containing the SpeedCoefficient
         */
        [[nodiscard]] double get_speed_coefficient() const;
        /**
         * \brief Check if Framerate is limited or not
         * \return true if the Framerate is limited, false otherwise
         */
        [[nodiscard]] bool is_framerate_limited() const;
        /**
         * \brief Get the frame per second cap
         * \return An unsigned int containing the frame per second (fps) cap
         */
        [[nodiscard]] unsigned int get_framerate_target() const;
        /**
         * \brief Check if vsync is enabled or not
         * \return true if vsync is enabled, false otherwise
         */
        [[nodiscard]] bool is_vsync_enabled() const;
        /**
         * \brief Set the SpeedCoefficient
         * \param speed The new SpeedCoefficient
         */
        void set_speed_coefficient(double speed);
        /**
         * \brief Set the max framerate
         * \param limit An unsigned int containing the max framerate, 0 for no limit
         */
        void set_framerate_target(unsigned int limit);
        /**
         * \brief Set if VerticalSync should be enabled or not
         * \param vsync A boolean containing if the v-sync should be enabled
         *        (true = enabled)
         */
        void set_vsync_enabled(bool vsync);

        void set_max_delta_time(double max_delta_time);
    };
} // namespace obe::time
