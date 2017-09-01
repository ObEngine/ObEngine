#include <TGUI/TGUI.hpp>
#include <vili/Vili.hpp>

#include <Editor/MapEditor.hpp>
#include <Editor/TGUIFallback.hpp>
#include <Modes/Game.hpp>
#include <Modes/Menu.hpp>
#include <Modes/Toolkit.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <Utils/StringUtils.hpp>

namespace obe
{
    namespace Modes
    {
        void scrollPanel(tgui::Panel::Ptr panel, tgui::Scrollbar::Ptr scrollbar)
        {
            static int previousScrolbarValue = 0;
            int distanceToMove = previousScrolbarValue - scrollbar->getValue();

            for (auto& widget : panel->getWidgets())
                widget->setPosition(widget->getPosition().x, widget->getPosition().y + distanceToMove);

            previousScrolbarValue = scrollbar->getValue();
        }

        void chooseMapAddMaps(tgui::Panel::Ptr middlePanel, tgui::Scrollbar::Ptr scrollbar, tgui::Theme& baseTheme, std::string& currentMap)
        {
            int scrollBoxSize = 0;

            scrollbar->setLowValue(middlePanel->getSize().y);
            scrollbar->setMaximum(scrollBoxSize);

            middlePanel->removeAllWidgets();

            std::vector<std::string> allMapsTemp;
            System::Path("Data/Maps").loadResource(&allMapsTemp, System::Loaders::filePathLoader);
            std::vector<std::string> allMaps;
            for (int i = 0; i < allMapsTemp.size(); i++)
            {
                if (Utils::String::endsWith(allMapsTemp[i], ".map.vili"))
                    allMaps.push_back(allMapsTemp[i]);
            }
            for (int i = 0; i < allMaps.size(); i++)
            {
                vili::ViliParser mapInfoParser;
                mapInfoParser.setQuickLookAttributes({ "Meta" });
                System::Path("Data/Maps").add(allMaps[i]).loadResource(&mapInfoParser, System::Loaders::dataLoader);
                std::string filename = allMaps[i];
                std::string levelName = "???";

                if (mapInfoParser->contains(vili::NodeType::ComplexNode, "Meta"))
                {
                    if (mapInfoParser.at("Meta").contains(vili::NodeType::DataNode, "name"))
                        levelName = mapInfoParser.at("Meta").getDataNode("name").get<std::string>();
                }

                tgui::Button::Ptr selectMapButton = tgui::Button::create();
                selectMapButton->setText(levelName + " (" + filename.substr(0, allMapsTemp[i].size() - 9) + ")");
                selectMapButton->setRenderer(baseTheme.getRenderer("MapSelectButton"));
                selectMapButton->setSize("630", "100");
                selectMapButton->setPosition("0", i * selectMapButton->getSize().y);
                std::cout << "Adding map file : " << levelName << selectMapButton->getPosition().x << ", " << selectMapButton->getPosition().y << std::endl;
                selectMapButton->connect("pressed", [&currentMap, filename] { currentMap = filename; });
                middlePanel->add(selectMapButton);
                scrollBoxSize += selectMapButton->getSize().y - 1;
            }
            scrollbar->setLowValue(middlePanel->getSize().y);
            scrollbar->setMaximum(scrollBoxSize);
        }

        void createLevel(tgui::EditBox::Ptr input)
        {
            std::string newLevelName = input->getText();
            if (newLevelName != "")
            {
                if (!Utils::File::fileExists(System::Path("Data/Maps").add(newLevelName + ".map.vili").getPath(0).toString()))
                {
                    std::cout << "Creating new level : " << newLevelName << std::endl;
                    vili::ViliParser newFileParser;
                    newFileParser.addFlag("Map");
                    newFileParser.addFlag("Lock");
                    newFileParser.includeFile("Obe");
                    newFileParser->createComplexNode("Meta");
                    newFileParser.at("Meta").createDataNode("name", newLevelName);
                    newFileParser->createComplexNode("View");
                    newFileParser.at("View").createComplexNode("pos");
                    newFileParser.at("View", "pos").createDataNode("unit", "WorldUnits");
                    newFileParser.at("View", "pos").createDataNode("x", 0);
                    newFileParser.at("View", "pos").createDataNode("y", 0);
                    newFileParser.at("View", "pos").useTemplate(newFileParser.getTemplate("Vector2<WorldUnits>"));
                    newFileParser.at("View").createDataNode("size", 1);
                    newFileParser.writeFile(System::Path("Data/Maps").add(newLevelName + ".map.vili").getPath(0).toString(), true);
                    input->setText("");
                }
                else
                    std::cout << "<Warning:Menu:Menu>[createLevel] : Level \"" << newLevelName << "\" already exists, abort..." << std::endl;
            }
        }

        std::string chooseMapMenu()
        {
            sf::RenderWindow window({636, 636}, "ObEngine Map Selector", sf::Style::None);

            tgui::Gui gui(window);
            gui.setFont("Data/Fonts/weblysleekuil.ttf");
            tgui::Theme baseTheme;
            baseTheme.load("Data/GUI/obe.style");
            std::string currentMap = "";

            tgui::Panel::Ptr topPanel = tgui::Panel::create();
            tgui::Panel::Ptr bottomPanel = tgui::Panel::create();
            tgui::Panel::Ptr middlePanel = tgui::Panel::create();
            tgui::Scrollbar::Ptr scrollbar = tgui::Scrollbar::create();
            tgui::Label::Ptr titleLabel = tgui::Label::create();
            tgui::Label::Ptr mapEditorLabel = tgui::Label::create();
            tgui::Button::Ptr closeButton = tgui::Button::create();
            tgui::Label::Ptr createMapLabel = tgui::Label::create();
            tgui::Button::Ptr createMapButton = tgui::Button::create();
            tgui::EditBox::Ptr createMapInput = tgui::EditBox::create();

            topPanel->setRenderer(baseTheme.getRenderer("Panel"));
            topPanel->setSize("100%", "10%");
            topPanel->setPosition("0", "0");

            bottomPanel->setRenderer(baseTheme.getRenderer("Panel"));
            bottomPanel->setSize("100%", "10%");
            bottomPanel->setPosition("0", "90%");

            middlePanel->setRenderer(baseTheme.getRenderer("LightPanel"));
            middlePanel->setSize("100%", "80%");
            middlePanel->setPosition("0", "10%");

            scrollbar->setPosition("620", "10% - 1");
            scrollbar->setSize("16", "80% + 1");
            scrollbar->connect("ValueChanged", scrollPanel, middlePanel, scrollbar);

            titleLabel->setRenderer(baseTheme.getRenderer("Label"));
            titleLabel->setText("ObEngine");
            titleLabel->setTextSize(34);
            titleLabel->setPosition("2.5%", "25%");

            mapEditorLabel->setRenderer(baseTheme.getRenderer("Label"));
            mapEditorLabel->setText("<Map Editor>");
            mapEditorLabel->setTextSize(22);
            mapEditorLabel->setPosition("25%", "40%");

            closeButton->setRenderer(baseTheme.getRenderer("CloseButton"));
            closeButton->setSize("32", "32");
            closeButton->setPosition("92%", "25%");
            closeButton->connect("pressed", [&window]()
            {
                window.close();
            });

            createMapLabel->setRenderer(baseTheme.getRenderer("Label"));
            createMapLabel->setText("Create Level : ");
            createMapLabel->setTextSize(30);
            createMapLabel->setPosition("2.5%", "20%");

            auto createMapLambda = [createMapInput, middlePanel, scrollbar, &baseTheme, &currentMap]()
            {
                createLevel(createMapInput);
                chooseMapAddMaps(middlePanel, scrollbar, baseTheme, currentMap);
            };

            createMapButton->setRenderer(baseTheme.getRenderer("AddButton"));
            createMapButton->setSize("32", "32");
            createMapButton->setPosition("90%", "25%");
            createMapButton->connect("pressed", createMapLambda);

            createMapInput->setRenderer(baseTheme.getRenderer("TextBox"));
            createMapInput->setSize("300", "32");
            createMapInput->setPosition("35%", "25%");
            createMapInput->connect("returnkeypressed", createMapLambda);

            gui.add(topPanel);
            gui.add(bottomPanel);
            gui.add(middlePanel);
            gui.add(scrollbar);
            topPanel->add(closeButton);
            topPanel->add(titleLabel);
            topPanel->add(mapEditorLabel);
            bottomPanel->add(createMapButton);
            bottomPanel->add(createMapLabel);
            bottomPanel->add(createMapInput);

            sf::Vector2i grabbedOffset;
            bool grabbedWindow = false;


            chooseMapAddMaps(middlePanel, scrollbar, baseTheme, currentMap);

            while (window.isOpen() && currentMap == "")
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (sf::Mouse::getPosition().y - window.getPosition().y < 60 && sf::Mouse::getPosition().x - window.getPosition().x < 580)
                        {
                            if (event.mouseButton.button == sf::Mouse::Left)
                            {
                                grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
                                grabbedWindow = true;
                            }
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonReleased)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                            grabbedWindow = false;
                    }
                    else if (event.type == sf::Event::MouseWheelScrolled)
                    {
                        scrollbar->mouseWheelScrolled(event.mouseWheelScroll.delta * 30, sf::Vector2f(0, 0));
                    }
                    else if (event.type == sf::Event::MouseMoved)
                    {
                        if (grabbedWindow)
                            window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
                    }
                    gui.handleEvent(event);
                }

                window.clear();
                gui.draw();
                window.display();
            }

            return currentMap;
        }

        void startDevMenu()
        {
            sf::RenderWindow window({636, 636}, "ObEngine Development Window", sf::Style::None);

            tgui::Gui gui(window);
            gui.setFont("Data/Fonts/weblysleekuil.ttf");
            tgui::Theme baseTheme;
            baseTheme.load("Data/GUI/obe.style");

            tgui::Panel::Ptr topPanel = tgui::Panel::create();
            tgui::Panel::Ptr middlePanel = tgui::Panel::create();
            tgui::Label::Ptr titleLabel = tgui::Label::create();
            tgui::Button::Ptr closeButton = tgui::Button::create();
            tgui::Button::Ptr playButton = tgui::Button::create();
            tgui::Button::Ptr editButton = tgui::Button::create();
            tgui::Button::Ptr toolkitButton = tgui::Button::create();
            tgui::Button::Ptr helpButton = tgui::Button::create();

            topPanel->setRenderer(baseTheme.getRenderer("Panel"));
            topPanel->setSize("100%", "10%");
            topPanel->setPosition("0", "0");

            middlePanel->setRenderer(baseTheme.getRenderer("LightPanel"));
            middlePanel->setSize("100%", "90%");
            middlePanel->setPosition("0", "10%");

            titleLabel->setRenderer(baseTheme.getRenderer("Label"));
            titleLabel->setText("ObEngine Development Menu");
            titleLabel->setTextSize(34);
            titleLabel->setPosition("2.5%", "15%");

            closeButton->setRenderer(baseTheme.getRenderer("CloseButton"));
            closeButton->setSize("32", "32");
            closeButton->setPosition("92%", "25%");
            closeButton->connect("pressed", [&window]()
            {
                window.close();
            });

            playButton->setRenderer(baseTheme.getRenderer("PlaySquareButton"));
            playButton->setSize("318", "286");
            playButton->setPosition("0", "0");
            playButton->connect("pressed", []()
            {
                startGame();
            });
            if (System::Path("boot.lua").find() == "")
            {
                playButton->disable();
            }

            editButton->setRenderer(baseTheme.getRenderer("EditSquareButton"));
            editButton->setSize("318", "286");
            editButton->setPosition(tguif::bindRight(playButton), "0");
            editButton->connect("pressed", []()
            {
                std::string editMapName = chooseMapMenu();
                if (editMapName != "")
                    Editor::editMap(editMapName);
            });

            toolkitButton->setRenderer(baseTheme.getRenderer("ToolkitSquareButton"));
            toolkitButton->setSize("318", "286");
            toolkitButton->setPosition("0", tguif::bindBottom(playButton));
            toolkitButton->connect("pressed", [&window]()
            {
                startToolkitMode();
            });

            helpButton->setRenderer(baseTheme.getRenderer("HelpSquareButton"));
            helpButton->setSize("318", "286");
            helpButton->setPosition(tguif::bindLeft(editButton), tguif::bindBottom(playButton));
            //helpButton->connect("pressed", [&window]()

            gui.add(topPanel);
            gui.add(middlePanel);
            topPanel->add(closeButton);
            topPanel->add(titleLabel);
            middlePanel->add(playButton);
            middlePanel->add(editButton);
            middlePanel->add(toolkitButton);
            middlePanel->add(helpButton);

            sf::Vector2i grabbedOffset;
            bool grabbedWindow = false;

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (sf::Mouse::getPosition().y - window.getPosition().y < 60 && sf::Mouse::getPosition().x - window.getPosition().x < 580)
                        {
                            if (event.mouseButton.button == sf::Mouse::Left)
                            {
                                grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
                                grabbedWindow = true;
                            }
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonReleased)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                            grabbedWindow = false;
                    }
                    else if (event.type == sf::Event::MouseMoved)
                    {
                        if (grabbedWindow)
                            window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
                    }
                    gui.handleEvent(event);
                }

                window.clear();
                gui.draw();
                window.display();
            }
        }
    }
}
