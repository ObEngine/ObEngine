//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "MeltingSaga.hpp"

int main(int argc, char** argv)
{
	//Sauvegarde du log dans log.txt
	std::ofstream out("log.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	fn::Coord::width = 640; fn::Coord::height = 480;
	fn::Coord::baseWidth = 640; fn::Coord::baseHeight = 480;
	std::string editMapName = chooseMapMenu();
	fn::Coord::width = sf::VideoMode::getDesktopMode().width;  fn::Coord::height = sf::VideoMode::getDesktopMode().height;
	fn::Coord::baseWidth = 1920; fn::Coord::baseHeight = 1080;

	//startGame("poly2.map.msd");
	if (editMapName != "")
		MapEditor::editMap(editMapName);
	return 0;
}