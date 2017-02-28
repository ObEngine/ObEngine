//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "ObEngine.hpp"

int main(int argc, char** argv)
{
	mse::Functions::Run::Parser runParser(argv, argc);
	std::string startMode = runParser.getArgumentValue("-mode");
	std::cout << "Running MeSa Engine using mode : " << startMode << std::endl;

	std::ofstream out("log.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	vili::DataParser workspaceConfig("Workspace/workspace.cfg.msd");
	vili::ComplexAttribute* workspace = workspaceConfig.at("Workspace");

	if (workspace->contains(vili::Types::BaseAttribute, "current"))
	{
		if (workspace->contains(vili::Types::ComplexAttribute, workspace->getBaseAttribute("current")->get<std::string>()))
		{
			vili::ComplexAttribute* currentWorkspace = workspace->at(*workspace->getBaseAttribute("current"));
			if (currentWorkspace->contains(vili::Types::BaseAttribute, "path"))
			{
				std::string workspacePath = *currentWorkspace->at<vili::BaseAttribute>("path");
				mse::System::Path::basePaths.push_back("Workspace/" + workspacePath);
				std::cout << "<System> Mounting Workspace : " << *workspace->getBaseAttribute("current") << " : " << workspacePath << std::endl;
			}
			else
				std::cout << "<Error:MeltingSaga:*>[main] : Workspace : " << *workspace->getBaseAttribute("current") << " doesn't have a path defined" << std::endl;
		}
		else
			std::cout << "<Error:MeltingSaga:*>[main] : Workspace : " << *workspace->getBaseAttribute("current") << "doesn't exists" << std::endl;
	}
	std::cout << "<System> Mounting Path : /" << std::endl;
	mse::System::Path::basePaths.push_back("");

	if (startMode == "edit")
	{
		mse::Functions::Coord::width = 640; mse::Functions::Coord::height = 480;
		mse::Functions::Coord::baseWidth = 640; mse::Functions::Coord::baseHeight = 480;
		std::string editMapName = mse::Modes::chooseMapMenu();
		mse::Functions::Coord::width = sf::VideoMode::getDesktopMode().width;  mse::Functions::Coord::height = sf::VideoMode::getDesktopMode().height;
		mse::Functions::Coord::baseWidth = 1920; mse::Functions::Coord::baseHeight = 1080;
		if (editMapName != "")
			mse::Editor::editMap(editMapName);
	}
	else if (startMode == "play")
		mse::Modes::startGame("");
	else if (startMode == "toolkit")
		mse::Modes::startToolkitMode();
	else
		mse::Modes::startGame("");
	
	return 0;
}