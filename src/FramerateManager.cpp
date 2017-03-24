#include "FramerateManager.hpp"

namespace obe
{
	FramerateManager::FramerateManager(vili::ComplexAttribute& config)
	{
		m_speedCoeff = 1;
		m_frameLimiterClock = Time::getTickSinceEpoch();
		m_limitFPS = (config.contains(vili::Types::BaseAttribute, "framerateLimit")) ? *config.at<vili::BaseAttribute>("framerateLimit") : true;
		m_framerateTarget = (config.contains(vili::Types::BaseAttribute, "framerateTarget")) ? *config.at<vili::BaseAttribute>("framerateTarget") : 60;
		m_vsyncEnabled = (config.contains(vili::Types::BaseAttribute, "vsync")) ? *config.at<vili::BaseAttribute>("vsync") : true;
		m_reqFramerateInterval = 1.0 / static_cast<double>(m_framerateTarget);
		m_currentFrame = 0;
		m_frameProgression = 0;
		m_needToRender = false;
	}

	void FramerateManager::update()
	{
		m_sfDeltaTime = m_deltaClock.restart();
		m_deltaTime = static_cast<double>(m_sfDeltaTime.asMicroseconds()) / 1000000.0;
		if (m_limitFPS)
		{
			if (Time::getTickSinceEpoch() - m_frameLimiterClock > 1000)
			{
				m_frameLimiterClock = Time::getTickSinceEpoch();
				m_currentFrame = 0;
			}
			m_frameProgression = std::round((Time::getTickSinceEpoch() - m_frameLimiterClock) / (m_reqFramerateInterval * 1000));
			m_needToRender = false;
			if (m_frameProgression > m_currentFrame)
			{
				m_currentFrame = m_frameProgression;
				m_needToRender = true;
			}
		}
	}

	double FramerateManager::getDeltaTime() const
	{
		return m_deltaTime;
	}

	double FramerateManager::getGameSpeed() const
	{
		return m_deltaTime * m_speedCoeff;
	}

	double FramerateManager::getSpeedCoeff() const
	{
		return m_speedCoeff;
	}

	bool FramerateManager::isFramerateLimited() const
	{
		return m_limitFPS;
	}

	int FramerateManager::getFramerateTarget() const
	{
		return m_framerateTarget;
	}

	bool FramerateManager::isVSyncEnabled() const
	{
		return m_vsyncEnabled;
	}

	void FramerateManager::setSpeedCoeff(double speed)
	{
		m_speedCoeff = speed;
	}

	void FramerateManager::limitFramerate(bool state)
	{
		m_limitFPS = state;
	}

	void FramerateManager::setFramerateTarget(int limit)
	{
		m_framerateTarget = limit;
	}

	void FramerateManager::setVSyncEnabled(bool vsync)
	{
		m_vsyncEnabled = vsync;
	}

	bool FramerateManager::doRender() const
	{
		return (!m_limitFPS || m_needToRender);
	}
}
