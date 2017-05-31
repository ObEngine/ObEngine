#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include <vili/Vili.hpp>

#include "TimeManager.hpp"

namespace obe
{
    class FramerateManager
    {
    private:
        sf::Clock m_deltaClock;
        sf::Time m_sfDeltaTime;
        double m_deltaTime = 0.0;
        double m_speedCoeff = 1.0;
        double m_frameLimiterClock;
        bool m_limitFPS;
        int m_framerateTarget;
        bool m_vsyncEnabled;
        double m_reqFramerateInterval;
        int m_currentFrame = 0;
        int m_frameProgression = 0;
        bool m_needToRender = false;
    public:
        FramerateManager(vili::ComplexAttribute& config);

        void update();
        bool doRender() const;

        double getDeltaTime() const;
        double getGameSpeed() const;
        double getSpeedCoeff() const;
        bool isFramerateLimited() const;
        int getFramerateTarget() const;
        bool isVSyncEnabled() const;

        void setSpeedCoeff(double speed);
        void limitFramerate(bool state);
        void setFramerateTarget(int limit);
        void setVSyncEnabled(bool vsync);
    };
}
