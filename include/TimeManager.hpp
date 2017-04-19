//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <map>
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace obe
{
	namespace Time
	{
		double getTickSinceEpoch();
		double getTickSinceEpochMicro();

		class Chronometer
		{
			private:
				std::chrono::high_resolution_clock::time_point m_chronoStart;
				std::chrono::high_resolution_clock::time_point m_chronoCurrent;
				bool m_started = false;
				unsigned long long int m_limit = 0;
			public:
				Chronometer();
				void start();
				void stop();
				unsigned long long int getTime();
				void setLimit(unsigned long long int limit);
				bool limitExceeded();
		};

		class FPSCounter
		{
			private:
				double m_lastTick = getTickSinceEpoch();
				int m_fpsCounter = 0;
				int m_updCounter = 0;
				int m_saveFPS = 0;
				int m_saveUPD = 0;
				bool m_canUpdateFPS = false;
				sf::Text m_text;
				sf::Font m_font;
			public:
				void tick();
				void uTick();
				void loadFont(sf::Font &font);
				sf::Text getFPS();
		};
	}
}