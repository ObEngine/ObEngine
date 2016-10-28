#include "DebugMode.hpp"

namespace mse
{
	namespace Modes
	{
		void startDebugMode()
		{
			//Creating Window
			sf::RenderWindow window(sf::VideoMode(Functions::Coord::width, Functions::Coord::height), "Melting Saga", sf::Style::Fullscreen);
			window.setKeyRepeatEnabled(false);
			window.setMouseCursorVisible(false);
			sf::Event event;

			Script::hookCore.dropValue("TriggerDatabase", Script::TriggerDatabase::GetInstance());

			//Console
			Console::Console gameConsole;
			gameConsole.setConsoleVisibility(true);
			Script::hookCore.dropValue("Console", &gameConsole);

			//Config
			Data::DataParser configFile;
			configFile.parseFile("Data/config.cfg.msd");
			configFile.hookNavigator(new Data::DataParserNavigator());
			configFile.accessNavigator()->setCurrentDataObject("GameConfig");
			int scrollSensitive = configFile.getAttribute("scrollSensibility")->get<int>();

			//Cursor
			Cursor::Cursor cursor(&window);
			Script::hookCore.dropValue("Cursor", &cursor);

			//World Creation / Loading
			World::World world;
			(*world.getScriptEngine())["stream"] = gameConsole.createStream("World", true);
			Script::hookCore.dropValue("World", &world);
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
			double frameLimiterClock = Time::getTickSinceEpoch();
			bool limitFPS = (configFile.attributeExists("framerateLimit")) ? configFile.getAttribute("framerateLimit")->get<bool>() : true;
			int framerateTarget = (configFile.attributeExists("framerateTarget")) ? configFile.getAttribute("framerateTarget")->get<int>() : 60;
			bool vsyncEnabled = (configFile.attributeExists("vsync")) ? configFile.getAttribute("vsync")->get<bool>() : false;
			double reqFramerateInterval = 1.0 / (double)framerateTarget;
			int currentFrame = 0;
			int frameProgression = 0;
			bool needToRender = false;
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

				//Events
				Script::TriggerDatabase::GetInstance()->update();
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
						if (event.key.code == sf::Keyboard::V)
						{
							if (event.key.control)
							{
								std::string clipboard_content;
								clip::get_text(clipboard_content);
								gameConsole.insertInputBufferContent(clipboard_content);
							}
						}
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
	}
}