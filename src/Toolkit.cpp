#include "Toolkit.hpp"

std::string colorConsole(std::string color)
{
	if (color == "black") rlutil::setColor(rlutil::BLACK);
	else if (color == "blue") rlutil::setColor(rlutil::BLUE);
	else if (color == "brown") rlutil::setColor(rlutil::BROWN);
	else if (color == "cyan") rlutil::setColor(rlutil::CYAN);
	else if (color == "darkgrey") rlutil::setColor(rlutil::DARKGREY);
	else if (color == "green") rlutil::setColor(rlutil::GREEN);
	else if (color == "grey") rlutil::setColor(rlutil::GREY);
	else if (color == "lightblue") rlutil::setColor(rlutil::LIGHTBLUE);
	else if (color == "lightcyan") rlutil::setColor(rlutil::LIGHTCYAN);
	else if (color == "lightgreen") rlutil::setColor(rlutil::LIGHTGREEN);
	else if (color == "lightmagenta") rlutil::setColor(rlutil::LIGHTMAGENTA);
	else if (color == "lightred") rlutil::setColor(rlutil::LIGHTRED);
	else if (color == "magenta") rlutil::setColor(rlutil::MAGENTA);
	else if (color == "red") rlutil::setColor(rlutil::RED);
	else if (color == "white") rlutil::setColor(rlutil::WHITE);
	else if (color == "yellow") rlutil::setColor(rlutil::YELLOW);
	return "";
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
				toolkitEngine["color"] = kaguya::function(colorConsole);
				toolkitEngine.dofile("Lib/Toolkit/Toolkit.lua");
				continueToolkit = toolkitEngine["reload"];
				printf("Press Enter to Continue");
				std::cin.ignore();
			}
		}
	}
}