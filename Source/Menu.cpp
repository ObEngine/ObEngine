#include "Menu.hpp"

namespace mse
{
	namespace Modes
	{
		std::string currentChosenMap = "";

		void chooseMapAddMaps(GUI::Container* gui)
		{
			gui->getContainerByContainerName("maps")->removeAllWidget(false); // Doesn't work when memory is freed
			std::vector<std::string> allMapsTemp;
			System::Path("Data/Maps").loadResource(&allMapsTemp, System::Loaders::filePathLoader);
			std::vector<std::string> allMaps;
			for (int i = 0; i < allMapsTemp.size(); i++)
			{
				if (allMapsTemp[i].size() > 8 && allMapsTemp[i].substr(allMapsTemp[i].size() - 8) == ".map.msd")
					allMaps.push_back(allMapsTemp[i]);
			}
			for (int i = 0; i < allMaps.size(); i++)
			{
				std::string mapFile = allMaps[i];
				Data::DataParser mapInfoParser;
				System::Path("Data/Maps").add(allMaps[i]).loadResource(&mapInfoParser, System::Loaders::dataLoader);
				std::string filename = (allMaps[i].size() <= 16) ? allMaps[i].substr(0, allMapsTemp[i].size() - 8) :
					allMaps[i].substr(0, 8) + "..";
				std::string levelName = "???";
				int mapSizeX = 0;
				int mapSizeY = 0;
				mapInfoParser.parseFile("Data/Maps/" + allMaps[i]);
				if (mapInfoParser.attributeExists("Meta", "", "Level")) levelName = mapInfoParser.getAttribute("Meta", "", "Level")->get<std::string>();
				if (mapInfoParser.attributeExists("Meta", "", "SizeX")) mapSizeX = mapInfoParser.getAttribute("Meta", "", "SizeX")->get<int>();
				if (mapInfoParser.attributeExists("Meta", "", "SizeY")) mapSizeY = mapInfoParser.getAttribute("Meta", "", "SizeY")->get<int>();
				GUI::Button* btn = gui->createButton("maps", "map_gbtn_" + std::to_string(i), 0, i * 100, true, true, "MAPSELECT");
				gui->createLabel("maps", "map_glbl_" + std::to_string(i), 30, i * 100 + 10, filename, "weblysleekuil.ttf", 64, sf::Color::White);
				gui->createLabel("maps", "map_gname_" + std::to_string(i), 320, i * 100 + 10, levelName, "weblysleekuil.ttf", 24, sf::Color::White);
				gui->createLabel("maps", "map_gsize_" + std::to_string(i), 320, i * 100 + 60,
					"Size : (" + std::to_string(mapSizeX) + "," + std::to_string(mapSizeY) + ")", "weblysleekuil.ttf", 16, sf::Color::White);
				btn->bindFunction([mapFile] { currentChosenMap = mapFile;  });
				gui->getContainerByContainerName("maps")->addScrollBar();
			}
		}

		void createLevel(GUI::Container* gui)
		{
			std::string newLevelName = GUI::Widget::getWidgetByID<GUI::TextInput>("createInput")->getText();
			if (newLevelName != "")
			{
				if (!Functions::File::fileExists(System::Path("Data/Maps").add(newLevelName + ".map.msd").getPath(0)))
				{
					std::cout << "Creating new level : " << newLevelName << std::endl;
					Data::DataParser newFileParser;
					newFileParser.hookNavigator(new Data::DataParserNavigator());
					newFileParser.createFlag("Map");
					newFileParser.createFlag("Lock");
					newFileParser.createDataObject("Meta");
					newFileParser.createBaseAttribute("Level", newLevelName);
					newFileParser.createBaseAttribute("SizeX", 1920);
					newFileParser.createBaseAttribute("SizeY", 1080);
					newFileParser.createBaseAttribute("StartX", 0);
					newFileParser.createBaseAttribute("StartY", 0);
					newFileParser.writeFile(System::Path("Data/Maps").add(newLevelName + ".map.msd").getPath(0), true);
					GUI::Widget::getWidgetByID<GUI::TextInput>("createInput")->setText("");
					chooseMapAddMaps(gui);
				}
				else
					std::cout << "<Warning:Menu:Menu>[createLevel] : Level \"" << newLevelName << "\" already exists, abort..." << std::endl;
			}
		}

		std::string chooseMapMenu()
		{
			sf::RenderWindow window(sf::VideoMode(640, 480), "Melting Saga", sf::Style::None);
			window.setMouseCursorVisible(false);
			sf::RectangleShape windowBorder(sf::Vector2f(638, 478));
			windowBorder.setPosition(1, 1);
			windowBorder.setFillColor(sf::Color(40, 40, 40));
			windowBorder.setOutlineColor(sf::Color::White);
			windowBorder.setOutlineThickness(1);
			sf::Vertex linetop[] = { sf::Vertex(sf::Vector2f(0, 60)), sf::Vertex(sf::Vector2f(640, 60)) };
			window.clear(sf::Color(40, 40, 40));
			window.display();
			std::cout << "Map Selector Initialisation.." << std::endl;

			sf::Event sfevent;
			GUI::Container gui(&sfevent, &window, 640, 480);
			GUI::WidgetContainer* mainContainer = gui.createWidgetContainer("main", 1, 0, 0, 640, 480, GUI::ContainerMovement::Fixed, 0, 0);
			GUI::WidgetContainer* mapsContainer = gui.createWidgetContainer("maps", 1, 0, 60, 640, 360, GUI::ContainerMovement::Fixed, 0, 0);
			GUI::WidgetContainer* creaContainer = gui.createWidgetContainer("crea", 2, 0, 420, 640, 60, GUI::ContainerMovement::Fixed, 0, 0);
			creaContainer->setBackground(sf::Color(50, 50, 50));

			gui.createLabel("main", "titleLbl", 10, 10, "Melting Saga", "weblysleekuil.ttf", 32, sf::Color::White);
			gui.createLabel("main", "titleLbl2", 200, 25, "Map Editor", "weblysleekuil.ttf", 16, sf::Color::White);
			gui.createButton("main", "quitBtn", 590, 15, true, true, "QUIT");

			gui.createLabel("crea", "createLbl", 10, 10, "Create Level :", "weblysleekuil.ttf", 26, sf::Color::White);
			gui.createTextInput("crea", "createInput", 250, 20, "", "weblysleekuil.ttf", 13, sf::Color::White, false, "GREY");
			gui.createButton("crea", "createBtn", 598, 14, true, true, "ADD");
			GUI::Widget::getWidgetByID<GUI::Button>("createBtn")->bindFunction([&gui]() { createLevel(&gui); });

			std::cout << "Map Selector GUI Initialisation..." << std::endl;
			chooseMapAddMaps(&gui);
			mapsContainer->addScrollBar();
			std::cout << "All maps Added" << std::endl;

			Cursor::Cursor cursor(&window);
			cursor.selectCursor("RoundWhite");
			std::cout << "Cursor Init" << std::endl;

			sf::Font font;
			font.loadFromFile("Data/Fonts/weblysleekuil.ttf");
			std::cout << "Font init" << std::endl;

			GUI::ButtonEvent* appQuitBool = GUI::Widget::getWidgetByID<GUI::Button>("quitBtn")->getHook();
			sf::Vector2i grabbedOffset;
			bool grabbedWindow = false;
			std::cout << "Start loop" << std::endl;

			while (window.isOpen() && currentChosenMap == "")
			{
				while (window.pollEvent(sfevent))
				{
					if (sfevent.type == sf::Event::Closed)
						window.close();
					else if (sfevent.type == sf::Event::KeyPressed)
					{
						if (sfevent.key.code == sf::Keyboard::Escape)
							window.close();
					}
					else if (sfevent.type == sf::Event::MouseButtonPressed)
					{
						if (sf::Mouse::getPosition().y - window.getPosition().y < 60 && sf::Mouse::getPosition().x - window.getPosition().x < 580)
						{
							if (sfevent.mouseButton.button == sf::Mouse::Left)
							{
								grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
								grabbedWindow = true;
							}
						}
					}
					else if (sfevent.type == sf::Event::MouseButtonReleased)
					{
						if (sfevent.mouseButton.button == sf::Mouse::Left)
							grabbedWindow = false;
					}
					else if (sfevent.type == sf::Event::MouseMoved)
					{
						if (grabbedWindow)
							window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
					}
				}

				gui.updateAllContainer();
				cursor.update();
				if (*appQuitBool == GUI::ButtonEvent::Pressed) { window.close(); }

				window.clear(sf::Color(40, 40, 40));
				window.draw(windowBorder);
				gui.drawAllContainer(&window);
				window.draw(linetop, 2, sf::Lines);
				window.draw(*cursor.getSprite());
				window.display();
			}
			std::cout << currentChosenMap << std::endl;
			window.close();
			return currentChosenMap;
		}
	}
}