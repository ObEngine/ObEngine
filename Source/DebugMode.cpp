#include "DebugMode.hpp"

void startDebugMode()
{
	//Creating Window
	sf::RenderWindow window(sf::VideoMode(fn::Coord::width, fn::Coord::height), "Melting Saga", sf::Style::Fullscreen);
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);
	sf::Event event;

	hookCore.dropValue("TriggerDatabase", &triggerDatabaseCore);

	//Console
	Console gameConsole;
	gameConsole.setConsoleVisibility(true);
	hookCore.dropValue("Console", &gameConsole);

	//Config
	DataParser configFile;
	configFile.parseFile("Data/config.cfg.msd");
	int scrollSensitive;
	configFile.getAttribute("GameConfig", "", "scrollSensibility")->getData(&scrollSensitive);

	//Cursor
	Cursor cursor;
	cursor.initialize(&window);
	hookCore.dropValue("Cursor", &cursor);

	//World Creation / Loading
	World world;
	(*world.getScriptEngine())["stream"] = gameConsole.createStream("World", true);
	hookCore.dropValue("World", &world);
	world.getScriptEngine()->setErrorHandler([&gameConsole](int statuscode, const char* message) { 
		gameConsole.pushMessage("LuaError", std::string("<Main> :: ") + message, 255, 0, 0); 
		std::cout << "[LuaError]<Main> : " << "[CODE::" << statuscode << "] : " << message << std::endl;
	});

	//Framerate / DeltaTime
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

	//Game Starts
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

		//Events
		triggerDatabaseCore.update();
		world.update(gameSpeed);
		cursor.update();
		gameConsole.update();

		//Console Command Handle
		if (gameConsole.hasCommand())
			world.getScriptEngine()->dostring(gameConsole.getCommand());
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Up)
						gameConsole.upHistory();
					if (event.key.code == sf::Keyboard::Down)
						gameConsole.downHistory();
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					if (event.key.code == sf::Keyboard::Left)
						gameConsole.moveCursor(-1);
					if (event.key.code == sf::Keyboard::Right)
						gameConsole.moveCursor(1);
					break;
				case sf::Event::TextEntered:
					gameConsole.inputKey(event.text.unicode);
					break;
				case sf::Event::MouseWheelMoved:
					if (event.mouseWheel.delta >= scrollSensitive)
						gameConsole.scroll(-1);
					else if (event.mouseWheel.delta <= -scrollSensitive)
						gameConsole.scroll(1);
					break;
			}
		}
		//Draw Everything Here
		if (!limitFPS || needToRender)
		{
			window.clear();
			//Console
			gameConsole.display(&window);
			//Cursor
			window.draw(*cursor.getSprite());
			window.display();
		}
	}
	window.close();
}