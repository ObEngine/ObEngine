#include "Toolkit.hpp"
#include <rang/rang.hpp>

#if defined(UNIX)
#include <termios.h>
#include <unistd.h>
int getch(void)
{
	struct termios oldattr, newattr;
	int ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}
#elif defined(WINDOWS)
int getch() {
	DWORD mode, cc;
	HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
	if (h == NULL) {
		return 0; // console not found
	}
	GetConsoleMode(h, &mode);
	SetConsoleMode(h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
	TCHAR c = 0;
	ReadConsole(h, &c, 1, &cc, NULL);
	SetConsoleMode(h, mode);
	return c;
}
#endif

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

std::string strGetch()
{
	int getchResult = getch();
	//std::cout << getchResult << std::endl;
	switch (getchResult)
	{
	case 8:
		return "BS";
	case 9:
		return "TAB";
	case 13:
		return "CR";
	default:
		return std::string(1, getchResult);;
	}
}

namespace obe
{
	namespace Modes
	{
		void startToolkitMode()
		{
			bool continueToolkit = true;
			std::cout << strGetch() << std::endl;

			while (continueToolkit)
			{
				kaguya::State toolkitEngine;
				toolkitEngine["This"] = &toolkitEngine;
				toolkitEngine.dofile("Lib/GameLib/WScrInit.lua");
				Script::loadLib(&toolkitEngine, "Core.*");
				Script::loadBaseLib(&toolkitEngine);
				toolkitEngine["_term_getch"] = kaguya::function(strGetch);
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