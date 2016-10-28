//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Game.hpp"

namespace mse
{
	namespace Modes
	{
		void startGame(std::string mapName)
		{
			Script::hookCore.dropValue("TriggerDatabase", Script::TriggerDatabase::GetInstance());
			Graphics::TextRenderer textDisplay;
			Script::hookCore.dropValue("TextDisplay", &textDisplay);

			//Console
			Console::Console gameConsole;
			Script::hookCore.dropValue("Console", &gameConsole);

			//Font
			sf::Font font;
			font.loadFromFile("Data/Fonts/arial.ttf");

			//Creating Window
			sf::RenderWindow window(sf::VideoMode(Functions::Coord::width, Functions::Coord::height), "Melting Saga", sf::Style::Fullscreen);
			window.setKeyRepeatEnabled(false);
			window.setMouseCursorVisible(false);
			sf::Event event;

			//Config
			Data::DataParser configFile;
			System::Path("Data").add("config.cfg.msd").loadResource(&configFile, System::Loaders::dataLoader);
			configFile.hookNavigator(new Data::DataParserNavigator)->setCurrentDataObject("GameConfig");
			bool drawFPS = true;
			bool showCursor = true;

			//Cursor
			Cursor::Cursor cursor(&window);

			//Character Initialisation
			Character character("Natsugi");

			//World Creation / Loading
			World::World world;
			Script::hookCore.dropValue("World", &world);
			world.loadFromFile(mapName);
			world.addCharacter(&character);
			bool depthOfFieldEnabled = configFile.getAttribute("depthOfField")->get<bool>();
			if (!depthOfFieldEnabled)
				world.setBlurMul(0.0);

			//Keybinding
			Input::KeyBinder keybind;
			keybind.loadFromFile(&configFile);

			//Framerate / DeltaTime
			Time::FPSCounter fps;
			fps.loadFont(font);
			sf::Clock deltaClock;
			sf::Time sfDeltaTime;
			double deltaTime;
			double speedCoeff = 60.0;
			double gameSpeed = 0.0;
			double frameLimiterClock = Time::getTickSinceEpoch();
			bool limitFPS = (configFile.attributeExists("framerateLimit")) ? configFile.getAttribute("framerateLimit")->get<bool>() : true;
			int framerateTarget = (configFile.attributeExists("framerateTarget")) ? configFile.getAttribute("framerateTarget")->get<int>() : 60;
			bool vsyncEnabled = (configFile.attributeExists("vsync")) ? configFile.getAttribute("vsync")->get<bool>() : false;
			double reqFramerateInterval = 1.0 / (double)framerateTarget;
			int currentFrame = 0;
			int frameProgression = 0;
			bool needToRender = false;
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
					if (Time::getTickSinceEpoch() - frameLimiterClock > 1000)
					{
						frameLimiterClock = Time::getTickSinceEpoch();
						currentFrame = 0;
					}
					frameProgression = std::round((Time::getTickSinceEpoch() - frameLimiterClock) / (reqFramerateInterval * 1000));
					needToRender = false;
					if (frameProgression > currentFrame)
					{
						currentFrame = frameProgression;
						needToRender = true;
					}
				}

				world.setCameraPosition(world.getCharacter(0)->getX() - (Functions::Coord::width / 2) + 128,
					world.getCharacter(0)->getY() - (Functions::Coord::height / 2) + 152, "FOLLOW");

				//Updates
				world.update(gameSpeed);

				//Cursor Actions
				if (cursor.getClicked("Left"))
					world.getCharacter(0)->melee(cursor.getX(), cursor.getY());

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

				//Updates
				keybind.update();
				cursor.update();
				Script::TriggerDatabase::GetInstance()->update();
				gameConsole.update();
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
						break;
					}
				}

				//Draw Everything Here
				if (!limitFPS || needToRender)
				{
					window.clear();
					world.display(&window);

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
	}
}