//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

namespace ModTools
{
	class ModDatabase
	{
		private:
		public:
	};

	extern ModDatabase modDB;

	class Mod
	{
		private:
			std::string title;
			std::string description;
			sf::Sprite iconSpr;
			sf::Texture iconTex;
			std::map<std::string, std::string> modScripts;
		public:
	};

	void registerMod(Mod mod);
}