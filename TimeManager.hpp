#pragma once

#include <map>
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <SFML/Graphics.hpp>

class Chronostasis
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
	double lastTick = GetTickCount64();
	int fpsCounter = 0;
	int saveFPS = 0;
	bool canUpdateFPS = false;
	sf::Text text;
	sf::Font font;
public:
	void tick();
	void loadFont(sf::Font &font);
	sf::Text getFPS();
	void ForceText(std::string replacement);
	sf::Text getText();
};