//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "MeltingSaga.hpp"

int main(int argc, char** argv)
{
	mse::Functions::Run::Parser runParser(argv, argc);
	std::cout << "Running MeSa Engine using mode : " << runParser.getArgumentValue("-mode") << std::endl;

	//Sauvegarde du log dans log.txt
	std::ofstream out("log.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	mse::Data::DataParser workspaceConfig;
	workspaceConfig.parseFile("Workspace/workspace.cfg.msd");
	workspaceConfig.hookNavigator(new mse::Data::DataParserNavigator())->setCurrentDataObject("Workspace");
	if (workspaceConfig.attributeExists("current"))
	{
		if (workspaceConfig.complexExists(workspaceConfig.getAttribute("current")->get<std::string>()))
		{
			workspaceConfig.accessNavigator()->setCurrentPath(workspaceConfig.getAttribute("current")->get<std::string>());
			if (workspaceConfig.attributeExists("path"))
			{
				std::string workspacePath = workspaceConfig.getAttribute("path")->get<std::string>();
				mse::System::Path::basePaths.push_back("Workspace/" + workspacePath);
				workspaceConfig.accessNavigator()->setCurrentDataObject("Workspace");
				std::cout << "<System> Mounting Workspace : " << workspaceConfig.getAttribute("current")->get<std::string>() << " : " << workspacePath << std::endl;
			}
			else
			{
				workspaceConfig.accessNavigator()->setCurrentDataObject("Workspace");
				std::cout << "<Error:MeltingSaga:*>[main] : Workspace : " << workspaceConfig.getAttribute("current")->get<std::string>() << " doesn't have a path defined" << std::endl;
			}
		}
		else
		{
			std::cout << "<Error:MeltingSaga:*>[main] : Workspace : " << workspaceConfig.getAttribute("current")->get<std::string>() << "doesn't exists" << std::endl;
		}
	}
	std::cout << "<System> Mounting Path : /" << std::endl;
	mse::System::Path::basePaths.push_back("");

	if (runParser.getArgumentValue("-mode") == "edit")
	{
		mse::Functions::Coord::width = 640; mse::Functions::Coord::height = 480;
		mse::Functions::Coord::baseWidth = 640; mse::Functions::Coord::baseHeight = 480;
		std::string editMapName = mse::Modes::chooseMapMenu();
		mse::Functions::Coord::width = sf::VideoMode::getDesktopMode().width;  mse::Functions::Coord::height = sf::VideoMode::getDesktopMode().height;
		mse::Functions::Coord::baseWidth = 1920; mse::Functions::Coord::baseHeight = 1080;
		std::cout << "Editing : " << editMapName << std::endl;
		if (editMapName != "")
			mse::Editor::editMap(editMapName);
	}
	else if (runParser.getArgumentValue("-mode") == "play")
		mse::Modes::startGame("poly2.map.msd");
	else if (runParser.getArgumentValue("-mode") == "console")
		mse::Modes::startDebugMode();
	else if (runParser.getArgumentValue("-mode") == "toolkit")
		mse::Modes::startToolkitMode();
	else
	{
		mse::Functions::Coord::width = 640; mse::Functions::Coord::height = 480;
		mse::Functions::Coord::baseWidth = 640; mse::Functions::Coord::baseHeight = 480;
		std::string editMapName = mse::Modes::chooseMapMenu();
		mse::Functions::Coord::width = sf::VideoMode::getDesktopMode().width;  mse::Functions::Coord::height = sf::VideoMode::getDesktopMode().height;
		mse::Functions::Coord::baseWidth = 1920; mse::Functions::Coord::baseHeight = 1080;
		if (editMapName != "")
			mse::Editor::editMap(editMapName);
	}
	
	return 0;
}