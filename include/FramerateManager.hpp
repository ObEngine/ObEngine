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
			sf::Clock deltaClock;
			sf::Time sfDeltaTime;
			double deltaTime;
			double speedCoeff = 1.0;
			double frameLimiterClock;
			bool limitFPS;
			int framerateTarget;
			bool vsyncEnabled;
			double reqFramerateInterval;
			int currentFrame = 0;
			int frameProgression = 0;
			bool needToRender = false;
		public:
			FramerateManager(vili::ComplexAttribute& config);

			void update();
			bool doRender();

			double getDeltaTime();
			double getGameSpeed();
			double getSpeedCoeff();
			bool isFramerateLimited();
			int getFramerateTarget();
			bool isVSyncEnabled();

			void setSpeedCoeff(double speed);
			void limitFramerate(bool state);
			void setFramerateTarget(int limit);
			void setVSyncEnabled(bool vsync);
	};
}
