#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <System/Window.hpp>
#include <Time/TimeUtils.hpp>

#include <vili/node.hpp>

namespace obe::Time
{
    /**
     * \brief Class that handles Framerate, DeltaTime and stuff related to time
     */
    class FramerateManager
    {
    private:
        System::Window& m_window;
        sf::Clock m_deltaClock;
        double m_deltaTime = 0.0;
        double m_speedCoefficient = 1.0;
        double m_frameLimiterClock;
        bool m_limitFramerate = false;
        unsigned int m_framerateTarget;
        bool m_vsyncEnabled = true;
        double m_reqFramerateInterval;
        int m_currentFrame = 0;
        int m_frameProgression = 0;
        bool m_needToRender = false;
        bool m_syncUpdateRender = true;

    public:
        /**
         * \brief Creates a new FramerateManager
         */
        FramerateManager(System::Window& window);
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
        [[nodiscard]] bool doRender() const;
        /**
         * \brief Get the DeltaTime
         * \return A double containing the DeltaTime
         */
        [[nodiscard]] TimeUnit getDeltaTime() const;
        /**
         * \brief Get the GameSpeed (DeltaTime * SpeedCoefficient)
         * \return A double containing the GameSpeed
         */
        [[nodiscard]] double getGameSpeed() const;
        /**
         * \brief Get the SpeedCoefficient
         * \return A double containing the SpeedCoefficient
         */
        [[nodiscard]] double getSpeedCoefficient() const;
        /**
         * \brief Check if Framerate is limited or not
         * \return true if the Framerate is limited, false otherwise
         */
        [[nodiscard]] bool isFramerateLimited() const;
        /**
         * \brief Get the frame per second cap
         * \return An unsigned int containing the frame per second (fps) cap
         */
        [[nodiscard]] unsigned int getFramerateTarget() const;
        /**
         * \brief Check if vSync is enabled or not
         * \return true if vSync is enabled, false otherwise
         */
        [[nodiscard]] bool isVSyncEnabled() const;
        /**
         * \brief Set the SpeedCoefficient
         * \param speed The new SpeedCoefficient
         */
        void setSpeedCoefficient(double speed);
        /**
         * \brief Set if the Framerate should be limited or not
         * \param state should be true if the framerate has to be limited, false
         *        otherwise
         */
        void limitFramerate(bool state);
        /**
         * \brief Set the max framerate
         * \param limit An unsigned int containing the max framerate
         */
        void setFramerateTarget(unsigned int limit);
        /**
         * \brief Set if VerticalSync should be enabled or not
         * \param vsync A boolean containing if the v-sync should be enabled
         *        (true = enabled)
         */
        void setVSyncEnabled(bool vsync);
    };
} // namespace obe::Time