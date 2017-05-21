//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "ObEngine.hpp"

void LoadErrors()
{
	vili::LoadErrors("Data/Errors.vili");
}

int main(int argc, char** argv)
{
	obe::Functions::Run::Parser runParser(argv, argc);
	std::string startMode = runParser.getArgumentValue("-mode");
	std::cout << "Running ObEngine using mode : " << startMode << std::endl;

	vili::DataParser dpfile;
	dpfile.parseFile("Package/BiblicalFortress/Data/Maps/Main.map.vili", true);
	dpfile.writeFile("testout.vili", true);

	obe::Coord::UnitVector::Init(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

	/*std::ofstream out("debug.log");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	std::ofstream out_err("errors.log");
	std::streambuf *cerrbug = std::cerr.rdbuf();
	std::cerr.rdbuf(out_err.rdbuf());*/

	LoadErrors();
	obe::System::MountPaths();

	if (startMode == "edit")
	{
		std::string editMapName = obe::Modes::chooseMapMenu();
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