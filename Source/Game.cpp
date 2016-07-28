//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Game.hpp"

void startGame(std::string mapName)
{
	hookCore.dropValue("TriggerDatabase", &triggerDatabaseCore);
	TextRenderer textDisplay;
	hookCore.dropValue("TextDisplay", &textDisplay);

	//Console
	Console gameConsole;
	hookCore.dropValue("Console", &gameConsole);

	//Font
	sf::Font font;
	font.loadFromFile("Data/Fonts/arial.ttf");

	//Creating Window
	sf::RenderWindow window(sf::VideoMode(fn::Coord::width, fn::Coord::height), "Melting Saga", sf::Style::Fullscreen);
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);
	sf::Event event;

	//Config
	DataParser configFile;
	configFile.parseFile("Data/config.cfg.msd");
	bool drawFPS = true;
	bool showCursor = true;

	//Cursor
	Cursor cursor(&window);

	//Character Initialisation
	Character character("Natsugi");

	//World Creation / Loading
	World world;
	hookCore.dropValue("World", &world);
	world.loadFromFile(mapName);
	world.addCharacter(&character);
	bool depthOfFieldEnabled;
	configFile.getAttribute("GameConfig", "", "depthOfField")->getData(&depthOfFieldEnabled);
	if (!depthOfFieldEnabled)
		world.setBlurMul(0.0);

	//CastSystem
	Caster castSystem;
	castSystem.hookToChar(&character);
	castSystem.hookToCurs(&cursor);
	castSystem.hookToWorld(&world);

	//Keybinding
	KeyBinder keybind = KeyBinder();
	keybind.loadFromFile(&configFile);

	//Overlay
	HUDOverlay hudOver = HUDOverlay();
	hudOver.hookToCaster(&castSystem);
	hudOver.hookToCharacter(&character);
	hudOver.loadAllIcons();

	//Framerate / DeltaTime
	FPSCounter fps;
	fps.loadFont(font);
	sf::Clock deltaClock;
	sf::Time sfDeltaTime;
	double deltaTime;
	double speedCoeff = 60.0;
	double gameSpeed = 0.0;
	double frameLimiterClock = getTickSinceEpoch();
	bool limitFPS = true;
	if (configFile.attributeExists("GameConfig", "", "framerateLimit"))
		configFile.getAttribute("GameConfig", "", "framerateLimit")->getData(&limitFPS);
	int framerateTarget = 60;
	if (configFile.attributeExists("GameConfig", "", "framerateTarget"))
		configFile.getAttribute("GameConfig", "", "framerateTarget")->getData(&framerateTarget);
	double reqFramerateInterval = 1.0 / (double)framerateTarget;
	int currentFrame = 0;
	int frameProgression = 0;
	bool needToRender = false;
	bool vsyncEnabled = false;
	if (configFile.attributeExists("GameConfig", "", "vsync"))
		configFile.getAttribute("GameConfig", "", "vsync")->getData(&vsyncEnabled);
	window.setVerticalSyncEnabled(vsyncEnabled);

	//Lancement du jeu
	while (window.isOpen())
	{
		//DeltaTime
		sfDeltaTime = deltaClock.restart();
		deltaTime = std::min(1.0 / 60.0, (double)sfDeltaTime.asMicroseconds() / 1000000.0);
		gameSpeed = deltaTime * speedCoeff;
		if (limitFPS)
		{
			if (getTickSinceEpoch() - frameLimiterClock > 1000)
			{
				frameLimiterClock = getTickSinceEpoch();
				currentFrame = 0;
			}
			frameProgression = std::round((getTickSinceEpoch() - frameLimiterClock) / (reqFramerateInterval * 1000));
			needToRender = false;
			if (frameProgression > currentFrame)
			{
				currentFrame = frameProgression;
				needToRender = true;
			}
		}

		world.setCameraPosition(world.getCharacter(0)->getX() - (fn::Coord::width / 2) + 128,
			world.getCharacter(0)->getY() - (fn::Coord::height / 2) + 152, "FOLLOW");

		//Updates
		world.update(gameSpeed);

		//Cursor Actions
		if (cursor.getClicked("Left"))
			world.getCharacter(0)->melee(cursor.getX(), cursor.getY());
		if (cursor.getClicked("Right"))
			castSystem.castSpell();

		//Keybinds
		if (keybind.isActionEnabled("Left") && keybind.isActionEnabled("Right")) {}
		else if (keybind.isActionEnabled("Left"))
			world.getCharacter(0)->move("Left");
		else if (keybind.isActionEnabled("Right"))
			world.getCharacter(0)->move("Right");


		if (keybind.isActionToggled("Crouch"))
			world.getCharacter(0)->triggerCrouch(true);
		if (keybind.isActionReleased("Crouch"))
			world.getCharacter(0)->triggerCrouch(false);


		if (keybind.isActionToggled("Jump"))
			world.getCharacter(0)->jump();
		if (keybind.isActionToggled("Sprint"))
			world.getCharacter(0)->sprint(true);
		else if (keybind.isActionReleased("Sprint"))
			world.getCharacter(0)->sprint(false);

		for (int k = 1; k <= 8; k++)
		{
			if (keybind.isActionToggled("Spell" + std::to_string(k)))
				castSystem.selectSpell(k - 1);
		}

		//Updates
		keybind.update();
		cursor.update();
		triggerDatabaseCore.update();
		gameConsole.update();
		hudOver.update(gameSpeed);
		if (drawFPS) fps.tick();

	
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
				if (event.key.code == sf::Keyboard::A)
					castSystem.switchElement("Up");
				if (event.key.code == sf::Keyboard::E)
					castSystem.switchElement("Down");
				if (event.key.code == sf::Keyboard::N)
				{
					castSystem.setBlood(100);
					castSystem.resetCooldown("ALL");
				}
				break;
			case sf::Event::MouseWheelMoved:
				if (event.mouseWheel.delta >= 1)
				{
					castSystem.switchElement("Up");
				}
				else if (event.mouseWheel.delta <= -1)
				{
					castSystem.switchElement("Down");
				}
				break;
			}
		}

		//Draw Everything Here
		if (!limitFPS || needToRender)
		{
			window.clear();
			world.display(&window);

			//HUD
			hudOver.draw(&window);

			if (drawFPS)
				window.draw(fps.getFPS());

			if (textDisplay.textRemaining())
				textDisplay.render(&window);

			//Console
			if (gameConsole.isConsoleVisible())
				gameConsole.display(&window);

			//Cursor
			if (showCursor)
				window.draw(*cursor.getSprite());

			window.display();
		}
	}
}