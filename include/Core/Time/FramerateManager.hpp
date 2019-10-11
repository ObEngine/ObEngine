#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <vili/Vili.hpp>

namespace obe::Time
{
    /**
     * \brief Class that handles Framerate, DeltaTime and stuff related to time
     * @Bind
     */
    class FramerateManager
    {
    private:
        sf::Clock m_deltaClock;
        double m_deltaTime = 0.0;
        double m_speedCoeff = 1.0;
        double m_frameLimiterClock;
        bool m_limitFPS;
        unsigned int m_framerateTarget;
        bool m_vsyncEnabled;
        double m_reqFramerateInterval;
        int m_currentFrame = 0;
        int m_frameProgression = 0;
        bool m_needToRender = false;
        bool m_syncUpdateRender = true;

    public:
        /**
         * \brief Creates a new FramerateManager
         * \param config Initial configuration of the FramerateManager
         */
        FramerateManager(vili::ComplexNode& config);
        /**
         * \brief Updates the FramerateManager (done everytime in the main loop)
         */
        void update();
        /**
         * \brief Get if the engine should render everything
         * \return true if the engine should render everything, false otherwise
         */
        bool doRender() const;
        /**
         * \brief Get the DeltaTime
         * \return A double containing the DeltaTime
         */
        double getDeltaTime() const;
        /**
         * \brief Get the GameSpeed (DeltaTime * SpeedCoeff)
         * \return A double containing the GameSpeed
         */
        double getGameSpeed() const;
        /**
         * \brief Get the SpeedCoeff
         * \return A double containing the SpeedCoeff
         */
        double getSpeedCoeff() const;
        /**
         * \brief Check if Framerate is limited or not
         * \return true if the Framerate is limited, false otherwise
         */
        bool isFramerateLimited() const;
        /**
         * \brief Get the frame per second cap
         * \return An unsigned int containing the frame per second (fps) cap
         */
        unsigned int getFramerateTarget() const;
        /**
         * \brief Check if vSync is enabled or not
         * \return true if vSync is enabled, false otherwise
         */
        bool isVSyncEnabled() const;
        /**
         * \brief Set the SpeedCoeff
         * \param speed The new SpeedCoeff
         */
        void setSpeedCoeff(double speed);
        /**
         * \brief Set if the Framerate should be limited or not
         * \param state should be true if the framerate has to be limited, false
         * otherwise
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
         * (true = enabled)
         */
        void setVSyncEnabled(bool vsync);
    };
} // namespace obe::Time