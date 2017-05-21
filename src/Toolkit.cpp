#include "Toolkit.hpp"
#include <rang/rang.hpp>

void colorConsole(std::string color)
{
	if (color == "black") std::cout << rang::fg::black;
	else if (color == "blue") std::cout << rang::fg::blue;
	else if (color == "cyan") std::cout << rang::fg::cyan;
	else if (color == "green") std::cout << rang::fg::green;
	else if (color == "grey") std::cout << rang::fg::gray;
	else if (color == "magenta") std::cout << rang::fg::magenta;
	else if (color == "red") std::cout << rang::fg::red;
	else if (color == "white") std::cout << rang::style::reset;
	else if (color == "yellow") std::cout << rang::fg::yellow;
}

void displayConsole(std::string disp)
{
	std::cout << disp;
	std::cout << rang::style::reset;
}

namespace obe
{
	namespace Modes
	{
		void startToolkitMode()
		{
			bool continueToolkit = true;

			while (continueToolkit)
			{
				kaguya::State toolkitEngine;
				toolkitEngine["This"] = &toolkitEngine;
				toolkitEngine.dofile("Lib/GameLib/WScrInit.lua");
				Script::loadLib(&toolkitEngine, "Core.*");
				Script::loadBaseLib(&toolkitEngine);
				toolkitEngine["_term_setcolor"] = kaguya::function(colorConsole);
				toolkitEngine["_term_display"] = kaguya::function(displayConsole);
				toolkitEngine.dofile("Lib/Toolkit/Toolkit.lua");
				continueToolkit = toolkitEngine["reload"];
				printf("Press Enter to Continue");
				std::cin.ignore();
			}
		}
	}
}