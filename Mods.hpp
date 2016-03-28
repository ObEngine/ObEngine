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