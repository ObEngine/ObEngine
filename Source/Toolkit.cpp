#include "Toolkit.hpp"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

std::string colorConsole(std::string color)
{
	int code = 15;
	if (color == "darkblue") code = 1;
	else if (color == "darkgreen") code = 2;
	else if (color == "teal") code = 3;
	else if (color == "darkred") code = 4;
	else if (color == "purple") code = 5;
	else if (color == "gold") code = 6;
	else if (color == "darkwhite") code = 7;
	else if (color == "grey") code = 8;
	else if (color == "blue") code = 9;
	else if (color == "green") code = 10;
	else if (color == "cyan") code = 11;
	else if (color == "red") code = 12;
	else if (color == "magenta") code = 13;
	else if (color == "yellow") code = 14;
	else if (color == "white") code = 15;
	SetConsoleTextAttribute(hConsole, code);
	return "";
}

void startToolkitMode()
{
	bool continueToolkit = true;

	while (continueToolkit)
	{
		kaguya::State toolkitEngine;
		toolkitEngine.dofile("Data/GameScripts/WScrInit.lua");
		loadLib(&toolkitEngine, "Core.*");
		loadBaseLib(&toolkitEngine);
		toolkitEngine["color"] = kaguya::function(colorConsole);
		toolkitEngine.dofile("Lib/Toolkit/Toolkit.lua");
		continueToolkit = toolkitEngine["reload"];
		printf("Press Enter to Continue");
		std::cin.ignore();
	}
}
