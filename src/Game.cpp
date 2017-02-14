#include "Game.hpp"

namespace mse
{
	namespace Modes
	{
		void startGame(std::string mapName)
		{
			double startLoadTime = Time::getTickSinceEpoch();

			//Creating Window
			sf::RenderWindow window(sf::VideoMode(Functions::Coord::width, Functions::Coord::height), "Melting Saga", sf::Style::Fullscreen);
			window.setKeyRepeatEnabled(false);
			window.setMouseCursorVisible(false);
			sf::Texture loadingTexture; loadingTexture.loadFromFile("Sprites/Menus/loading.png"); loadingTexture.setSmooth(true);
			sf::Sprite loadingSprite; loadingSprite.setTexture(loadingTexture);
			loadingSprite.setScale((double)Functions::Coord::width / (double)Functions::Coord::baseWidth,
				(double)Functions::Coord::height / (double)Functions::Coord::baseHeight);
			sf::Font loadingFont; loadingFont.loadFromFile("Data/Fonts/weblysleekuil.ttf");
			sf::Text loadingText; loadingText.setFont(loadingFont);
			loadingText.setCharacterSize(70.0 * (double)Functions::Coord::height / (double)Functions::Coord::baseHeight);
			loadingText.setPosition(348.0 * (double)Functions::Coord::width / (double)Functions::Coord::baseWidth,
				595.0 * (double)Functions::Coord::height / (double)Functions::Coord::baseHeight);
			Data::DataParser loadingStrDP; loadingStrDP.parseFile("Sprites/Menus/loading.dat.msd");
			loadingStrDP.hookNavigator(new Data::DataParserNavigator)->setCurrentRootAttribute("Loading");
			std::string loadingRandomStr = loadingStrDP.getListAttribute("loadingStr")->get(
				Functions::Math::randint(0, loadingStrDP.getListSize("Loading", "loadingStr") - 1))->get<std::string>();
			loadingText.setString(loadingRandomStr);
			window.draw(loadingSprite); window.draw(loadingText); window.display();

			Script::hookCore.dropValue("TriggerDatabase", Script::TriggerDatabase::GetInstance());
			Graphics::TextRenderer textDisplay;
			textDisplay.createRenderer("Shade", "MapSaver");
			Script::hookCore.dropValue("TextDisplay", &textDisplay);

			//TO DELETE
			sf::Music music;
			music.openFromFile("Music/battle.ogg");
			music.setLoop(true);
			music.play();

			//Font
			sf::Font font;
			font.loadFromFile("Data/Fonts/arial.ttf");

			//Config
			Data::DataParser configFile;
			System::Path("Data/config.cfg.msd").loadResource(&configFile, System::Loaders::dataLoader);
			configFile.hookNavigator(new Data::DataParserNavigator())->setCurrentRootAttribute("GameConfig");
			int scrollSensitive = configFile.getBaseAttribute("scrollSensibility")->get<int>();
			configFile.accessNavigator()->setCurrentRootAttribute("Developpement");

			//Cursor
			Cursor::Cursor cursor(&window);
			cursor.updateOutsideWindow(true);
			Script::hookCore.dropValue("Cursor", &cursor);

			//Character Initialisation
			//Character character("Natsugi");

			//World Creation / Loading
			configFile.accessNavigator()->setCurrentRootAttribute("GameConfig");
			World::World world;
			Script::hookCore.dropValue("World", &world);
			bool depthOfFieldEnabled = configFile.getBaseAttribute("depthOfField")->get<bool>();
			if (!depthOfFieldEnabled) world.setBlurMul(0.0);

			//Keybinding
			Input::KeyBinder keybind;
			Script::hookCore.dropValue("KeyBinder", &keybind);
			keybind.loadFromFile(&configFile);

			sf::Event event;

			//Framerate / DeltaTime
			Time::FPSCounter fps;
			fps.loadFont(font);
			FramerateManager framerateManager(*configFile.getRootAttribute("GameConfig"));
			window.setVerticalSyncEnabled(framerateManager.isVSyncEnabled());

			Light::initLights();

			//world.addCharacter(&character);
			world.loadFromFile(mapName);

			//Game Starts
			while (window.isOpen())
			{
				framerateManager.update();

				//Events
				Script::TriggerDatabase::GetInstance()->update();
				world.update(framerateManager.getGameSpeed());
				textDisplay.update(framerateManager.getGameSpeed());
				keybind.update();
				cursor.update();

				//Triggers Handling
				cursor.handleTriggers();
				keybind.handleTriggers();

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
						if (event.key.code == sf::Keyboard::Return)
						{
							if (textDisplay.textRemaining())
								textDisplay.next();
						}
						break;
					}
				}

				if (cursor.getClicked("Left") || cursor.getPressed("Left"))
				{
					std::vector<Script::GameObject*> clickableGameObjects = world.getAllGameObjects({ "Click" });
					std::vector<Collision::PolygonalCollider*> elementsCollidedByCursor = world.getAllCollidersByCollision(
						cursor.getCollider(), -world.getCamX(), -world.getCamY());
					for (int i = 0; i < elementsCollidedByCursor.size(); i++)
					{
						for (int j = 0; j < clickableGameObjects.size(); j++)
						{
							if (elementsCollidedByCursor[i] == clickableGameObjects[j]->getCollider())
							{
								if (cursor.getClicked("Left"))
									world.getGameObject(clickableGameObjects[j]->getID())->getLocalTriggers()->setTriggerState("Click", true);
								if (cursor.getPressed("Left"))
									world.getGameObject(clickableGameObjects[j]->getID())->getLocalTriggers()->setTriggerState("Press", true);
							}

						}
					}
				}

				if (framerateManager.doRender())
				{
					window.clear();
					world.display(&window);
					if (textDisplay.textRemaining())
						textDisplay.render(&window);
					window.draw(*cursor.getSprite());

					window.display();
				}
			}
			window.close();
		}
	}
}