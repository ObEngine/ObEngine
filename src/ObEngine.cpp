//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "ObEngine.hpp"

int main(int argc, char** argv)
{
	obe::Functions::Run::Parser runParser(argv, argc);
	std::string startMode = runParser.getArgumentValue("-mode");
	std::cout << "Running ObEngine using mode : " << startMode << std::endl;

	std::ofstream out("log.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	obe::System::MountPaths();

	if (startMode == "edit")
	{
		obe::Functions::Coord::width = 640; obe::Functions::Coord::height = 480;
		obe::Functions::Coord::viewWidth = 640; obe::Functions::Coord::viewHeight = 480;
		std::string editMapName = obe::Modes::chooseMapMenu();
		obe::Functions::Coord::width = sf::VideoMode::getDesktopMode().width;  obe::Functions::Coord::height = sf::VideoMode::getDesktopMode().height;
		obe::Functions::Coord::viewWidth = 1920; obe::Functions::Coord::viewHeight = 1080;
		if (editMapName != "")
			obe::Editor::editMap(editMapName);
	}
	else if (startMode == "play")
		obe::Modes::startGame("");
	else if (startMode == "toolkit")
		obe::Modes::startToolkitMode();
	else
		obe::Modes::startGame("");
	
	return 0;
}