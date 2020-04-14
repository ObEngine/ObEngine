#include <cmath>

#include <Debug/Logger.hpp>
#include <System/Window.hpp>
#include <Time/FramerateManager.hpp>
#include <thread>

namespace obe::Time
{
    FramerateManager::FramerateManager(System::Window& window)
        : m_window(window)
    {
        m_frameLimiterClock = epoch();
        m_currentFrame = 0;
        m_frameProgression = 0;
        m_needToRender = false;
    }

    void FramerateManager::configure(vili::ComplexNode& config)
    {
        m_limitFPS = (config.contains(vili::NodeType::DataNode, "framerateLimit"))
            ? config.at<vili::DataNode>("framerateLimit")
            : true;
        m_framerateTarget = (config.contains(vili::NodeType::DataNode, "framerateTarget"))
            ? config.at<vili::DataNode>("framerateTarget")
            : 60;
        m_vsyncEnabled = (config.contains(vili::NodeType::DataNode, "vsync"))
            ? config.at<vili::DataNode>("vsync")
            : true;
        m_syncUpdateRender
            = (config.contains(vili::NodeType::DataNode, "syncUpdateToRender"))
            ? config.at<vili::DataNode>("syncUpdateToRender")
            : true;
        m_reqFramerateInterval = 1.0 / static_cast<double>(m_framerateTarget);
        Debug::Log->info("Framerate parameters : {} FPS {}, V-sync {}, Update Lock {}",
            m_framerateTarget, (m_limitFPS) ? "capped" : "uncapped",
            (m_vsyncEnabled) ? "enabled" : "disabled",
            (m_syncUpdateRender) ? "enabled" : "disabled");

        m_window.setVerticalSyncEnabled(m_vsyncEnabled);
    }

    void FramerateManager::update()
    {
        const sf::Time timeBuffer = m_deltaClock.restart();
        m_deltaTime = static_cast<double>(timeBuffer.asMicroseconds()) * microseconds;
        if (m_limitFPS)
        {
            if (epoch() - m_frameLimiterClock > 1)
            {
                m_frameLimiterClock = epoch();
                m_currentFrame = 0;
            }
            m_frameProgression
                = round((epoch() - m_frameLimiterClock) / (m_reqFramerateInterval));
            m_needToRender = false;
            if (m_frameProgression > m_currentFrame)
            {
                m_currentFrame = m_frameProgression;
                m_needToRender = true;
            }
            else
            {
                std::this_thread::sleep_for(
                    std::chrono::duration<double>(m_reqFramerateInterval));
            }
        }
    }

    TimeUnit FramerateManager::getDeltaTime() const
    {
        return m_deltaTime;
    }

    double FramerateManager::getGameSpeed() const
    {
        return m_deltaTime * m_speedCoefficient;
    }

    double FramerateManager::getSpeedCoefficient() const
    {
        return m_speedCoefficient;
    }

    bool FramerateManager::isFramerateLimited() const
    {
        return m_limitFPS;
    }

    unsigned int FramerateManager::getFramerateTarget() const
    {
        return m_framerateTarget;
    }

    bool FramerateManager::isVSyncEnabled() const
    {
        return m_vsyncEnabled;
    }

    void FramerateManager::setSpeedCoefficient(const double speed)
    {
        m_speedCoefficient = speed;
    }

    void FramerateManager::limitFramerate(const bool state)
    {
        m_limitFPS = state;
    }

    void FramerateManager::setFramerateTarget(const unsigned int limit)
    {
        m_framerateTarget = limit;
    }

    void FramerateManager::setVSyncEnabled(const bool vsync)
    {
        m_vsyncEnabled = vsync;
        m_window.setVerticalSyncEnabled(vsync);
    }

    bool FramerateManager::doRender() const
    {
        return (!m_limitFPS || m_needToRender);
    }
} // namespace obe::Time
