#include "FramerateManager.hpp"

mse::FramerateManager::FramerateManager(vili::ComplexAttribute& config)
{
	sf::Clock deltaClock;
	sf::Time sfDeltaTime;
	speedCoeff = 60.0;
	frameLimiterClock = Time::getTickSinceEpoch();
	limitFPS = (config.contains(vili::Types::BaseAttribute, "framerateLimit")) ? *config.at<vili::BaseAttribute>("framerateLimit") : true;
	framerateTarget = (config.contains(vili::Types::BaseAttribute, "framerateTarget")) ? *config.at<vili::BaseAttribute>("framerateTarget") : 60;
	vsyncEnabled = (config.contains(vili::Types::BaseAttribute, "vsync")) ? *config.at<vili::BaseAttribute>("vsync") : true;
	reqFramerateInterval = 1.0 / (double)framerateTarget;
	currentFrame = 0;
	frameProgression = 0;
	needToRender = false;
}

void mse::FramerateManager::update()
{
	sfDeltaTime = deltaClock.restart();
	deltaTime = std::min(1.0 / 60.0, (double)sfDeltaTime.asMicroseconds() / 1000000.0);
	if (limitFPS)
	{
		if (Time::getTickSinceEpoch() - frameLimiterClock > 1000)
		{
			frameLimiterClock = Time::getTickSinceEpoch();
			currentFrame = 0;
		}
		frameProgression = std::round((Time::getTickSinceEpoch() - frameLimiterClock) / (reqFramerateInterval * 1000));
		needToRender = false;
		if (frameProgression > currentFrame)
		{
			currentFrame = frameProgression;
			needToRender = true;
		}
	}
}

double mse::FramerateManager::getDeltaTime()
{
	return deltaTime;
}

double mse::FramerateManager::getGameSpeed()
{
	return deltaTime * speedCoeff;
}

double mse::FramerateManager::getSpeedCoeff()
{
	return speedCoeff;
}

bool mse::FramerateManager::isFramerateLimited()
{
	return limitFPS;
}

int mse::FramerateManager::getFramerateTarget()
{
	return framerateTarget;
}

bool mse::FramerateManager::isVSyncEnabled()
{
	return vsyncEnabled;
}

void mse::FramerateManager::setSpeedCoeff(double speed)
{
	speedCoeff = speed;
}

void mse::FramerateManager::limitFramerate(bool state)
{
	limitFPS = state;
}

void mse::FramerateManager::setFramerateTarget(int limit)
{
	framerateTarget = limit;
}

void mse::FramerateManager::setVSyncEnabled(bool vsync)
{
	vsyncEnabled = vsync;
}

bool mse::FramerateManager::doRender()
{
	return (!limitFPS || needToRender);
}
