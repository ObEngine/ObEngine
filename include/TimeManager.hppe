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

		class TimeMonitor
		{
			private:
				std::map<std::string, std::chrono::high_resolution_clock::time_point> chronoSMap; //Start Map
				std::map<std::string, std::chrono::high_resolution_clock::time_point> chronoEMap; //End Map
				std::map<std::string, std::chrono::microseconds> chronoRMap; //Result Map
				std::map<std::string, std::chrono::microseconds> chronoCMap; //Cumulative Map
				std::map<std::string, unsigned long long int> chronoOMap; //Occurences Map
			public:
				void startTick(std::string id);
				void endTick(std::string id);
				void summary();
				void endSummary();
		};

		class Chronometer
		{
			private:
				std::chrono::high_resolution_clock::time_point chronoStart;
				std::chrono::high_resolution_clock::time_point chronoCurrent;
				bool started;
				unsigned long long int limit;
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
				double lastTick = getTickSinceEpoch();
				int fpsCounter = 0;
				int updCounter = 0;
				int saveFPS = 0;
				int saveUPD = 0;
				bool canUpdateFPS = false;
				sf::Text text;
				sf::Font font;
			public:
				void tick();
				void uTick();
				void loadFont(sf::Font &font);
				sf::Text getFPS();
				void ForceText(std::string replacement);
				sf::Text getText();
		};
	}
}