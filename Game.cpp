//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Game.hpp"

void startGame()
{
	//Console
	Console gameConsole;
	Console::Stream* charStream = gameConsole.createStream("CharStream");

	//Resolution
	const int S_WIDTH = fn::Coord::baseWidth;
	const int S_HEIGHT = fn::Coord::baseHeight;
	int resX = fn::Coord::width;
	int resY = fn::Coord::height;

	//Creation fenetre / camera / RenderTexture
	sf::RenderWindow window(sf::VideoMode(resX, resY), "Melting Saga", sf::Style::Fullscreen);
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);

	//Config
	DataParser configFile;
	configFile.parseFile("Data/config.cfg.msd");
	std::string mapName;
	configFile.getAttribute("GameConfig", "", "mapName")->getData(&mapName);
	int scrollSensitive;
	configFile.getAttribute("GameConfig", "", "scrollSensibility")->getData(&scrollSensitive);
	bool showChar, showCol, showDeco, showOverlay, showCursor, showFPS;
	configFile.getAttribute("Developpement", "", "showCharacter")->getData(&showChar);
	configFile.getAttribute("Developpement", "", "showCollisions")->getData(&showCol);
	configFile.getAttribute("Developpement", "", "showLevelSprites")->getData(&showDeco);
	configFile.getAttribute("Developpement", "", "showOverlay")->getData(&showOverlay);
	configFile.getAttribute("Developpement", "", "showCursor")->getData(&showCursor);
	configFile.getAttribute("Developpement", "", "showFPS")->getData(&showFPS);
	bool drawFPS = true;

	//Cursor
	Cursor curs;
	curs.initialize(resX, resY);

	//Creation personnage
	Character character("Natsugi");
	character.setStreamLink(charStream);

	//Creation et chargement du monde
	World world;
	world.loadFromFile(mapName);
	world.addCharacter(&character);
	world.init();
	bool depthOfFieldEnabled;
	configFile.getAttribute("GameConfig", "", "depthOfField")->getData(&depthOfFieldEnabled);
	if (!depthOfFieldEnabled)
		world.setBlurMul(0);
	bool dofEnabled = depthOfFieldEnabled;

	//CastSystem
	Caster castSystem;
	castSystem.hookToChar(&character);
	castSystem.hookToCurs(&curs);
	castSystem.hookToWorld(&world);

	//Keybinding
	KeyBinder keybind = KeyBinder();
	keybind.loadFromFile(&configFile);

	//GUI
	bool drawDEV = false;
	sf::Event event;
	/*GUI::Container gui(&event);
	gui.createWidgetContainer("Menu", 1, 0, 0, resX, resY, GUI::ContainerMovement::Fixed);
	gui.createLabel("Menu", "title", 1475, 0, "Melting Saga", "LeviBrush.ttf", 64, sf::Color(255, 255, 255));
	gui.createCheckbox("Menu", "showFPSCB", 1550, 107, "GREY", showFPS);
	gui.createLabel("Menu", "showFPSLbl", 1580, 100, "Show FPS Counter", "arial.ttf", 24, sf::Color::White);
	gui.createCheckbox("Menu", "useDOFCB", 1550, 137, "GREY", showFPS);
	gui.createLabel("Menu", "useDOFLbl", 1580, 130, "Depth of Field", "arial.ttf", 24, sf::Color::White);*/

	//Overlay
	HUDOverlay hudOver = HUDOverlay();
	hudOver.hookToCaster(&castSystem);
	hudOver.hookToCharacter(&character);
	hudOver.loadAllIcons();

	//Framerate / DeltaTime
	FPSCounter fps;
	sf::Font font;
	font.loadFromFile("Data/Fonts/arial.ttf");
	fps.loadFont(font);

	sf::Clock deltaClock;
	sf::Time sfDeltaTime;
	double deltaTime;
	float speedCoeff = 60.0;
	double gameSpeed = 0.0;
	Chronostasis gameClock;

	//Lancement du jeu
	while (window.isOpen())
	{
		sfDeltaTime = deltaClock.restart();
		deltaTime = std::min(1.0 / 30.0, (double)sfDeltaTime.asMicroseconds() / 1000000.0);
		gameSpeed = deltaTime * speedCoeff;

		world.setCameraPosition(world.getCharacter(0)->getX() - (resX / 2), world.getCharacter(0)->getY() - (resY / 2), "FOLLOW");

		/*if (GUI::Checkbox::getCheckboxById("showFPSCB")->getToggled())
			drawFPS = GUI::Checkbox::getCheckboxById("showFPSCB")->isChecked();
		if (GUI::Checkbox::getCheckboxById("useDOFCB")->getToggled())
		{
			dofEnabled = GUI::Checkbox::getCheckboxById("useDOFCB")->isChecked();
			if (dofEnabled)
				world.setBlurMul(0.0003);
			else
				world.setBlurMul(0);
		}*/

		//Updates
		world.update(gameSpeed);

		//Cursor Actions
		if (curs.getClicked("Left"))
		{
			world.getCharacter(0)->melee(curs.getX(), curs.getY());
		}
		if (curs.getClicked("Right"))
		{
			castSystem.castSpell();
		}

		//Keybinds
		if (keybind.isActionToggled("Left") && keybind.isActionToggled("Right"))
		{

		}
		else if (keybind.isActionToggled("Left"))
			world.getCharacter(0)->move("Left");
		else if (keybind.isActionToggled("Right"))
			world.getCharacter(0)->move("Right");


		if (keybind.isActionToggled("Crouch"))
		{
			world.getCharacter(0)->triggerCrouch(true);
		}
		if (keybind.isActionReleased("Crouch"))
		{
			world.getCharacter(0)->triggerCrouch(false);
		}


		if (keybind.isActionToggled("Jump"))
			world.getCharacter(0)->jump();
		if (keybind.isActionToggled("Sprint"))
			world.getCharacter(0)->sprint(true);
		else
			world.getCharacter(0)->sprint(false);

		for (int k = 1; k <= 8; k++)
		{
			if (keybind.isActionToggled("Spell" + std::to_string(k)))
				castSystem.selectSpell(k - 1);
		}

		keybind.update();
		curs.update();

		//gui.updateAllContainer();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::F)
					drawDEV = !drawDEV;
				if (event.key.code == sf::Keyboard::A)
					castSystem.switchElement("Up");
				if (event.key.code == sf::Keyboard::E)
					castSystem.switchElement("Down");
				if (event.key.code == sf::Keyboard::N)
				{
					castSystem.setBlood(100);
					castSystem.resetCooldown("ALL");
				}
				if (event.key.code == sf::Keyboard::R)
				{
					world.getCharacter(0)->setPos(world.getStartX(), world.getStartY());
					world.getCharacter(0)->cancelMoves();
				}
				break;
			case sf::Event::MouseWheelMoved:
				if (event.mouseWheel.delta >= scrollSensitive)
				{
					castSystem.switchElement("Up");
				}
				else if (event.mouseWheel.delta <= -scrollSensitive)
				{
					castSystem.switchElement("Down");
				}
				break;
			}
		}

		window.clear();
		world.display(&window);

		if (showCol)
		{
			std::vector<sf::Sprite*> colDebug;
			sf::Sprite tempDrawSpr;
			for (unsigned int cdbug = 0; cdbug < colDebug.size(); cdbug++)
			{
				sf::Sprite tempDrawSpr;
				tempDrawSpr = *colDebug[cdbug];
				tempDrawSpr.move(-world.getCamX(), -world.getCamY());
				window.draw(tempDrawSpr);
			}
		}

		//HUD
		if (showOverlay)
			hudOver.draw(&window, gameSpeed);
		if (drawFPS)
		{
			fps.tick();
			window.draw(fps.getFPS());
		}

		if (drawDEV)
		{
			//gui.drawContainer("Menu", &window);
		}

		if (showCursor)
			window.draw(*curs.getSprite());

		window.display();
	}
}