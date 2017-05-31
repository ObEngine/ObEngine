#include "Game.hpp"
#include "FramerateManager.hpp"

namespace obe
{
    namespace Modes
    {
        void startGame(std::string mapName)
        {
            //Creating Window
            sf::RenderWindow window(sf::VideoMode(Coord::UnitVector::Screen.w, Coord::UnitVector::Screen.h), "ObEngine", sf::Style::Fullscreen);
            window.setKeyRepeatEnabled(false);
            window.setMouseCursorVisible(false);
            sf::Texture loadingTexture;
            loadingTexture.loadFromFile("Sprites/Menus/loading.png");
            loadingTexture.setSmooth(true);
            sf::Sprite loadingSprite;
            loadingSprite.setTexture(loadingTexture);
            sf::Font loadingFont;
            loadingFont.loadFromFile("Data/Fonts/weblysleekuil.ttf");
            sf::Text loadingText;
            loadingText.setFont(loadingFont);
            loadingText.setCharacterSize(70.0);
            loadingText.setPosition(348.0, 595.0);
            vili::DataParser loadingStrDP("Sprites/Menus/loading.vili");
            std::string loadingRandomStr = loadingStrDP.at<vili::ListAttribute>("Loading", "loadingStr").get(
                Functions::Math::randint(0, loadingStrDP.at<vili::ListAttribute>("Loading", "loadingStr").size() - 1));
            loadingText.setString(loadingRandomStr);
            window.draw(loadingSprite);
            window.draw(loadingText);
            window.display();

            Script::hookCore.dropValue("TriggerDatabase", Script::TriggerDatabase::GetInstance());
            Graphics::TextRenderer textDisplay;
            textDisplay.createRenderer("Shade", "MapSaver");
            Script::hookCore.dropValue("TextDisplay", &textDisplay);

            //Font
            sf::Font font;
            font.loadFromFile("Data/Fonts/arial.ttf");

            //Config
            vili::DataParser configFile;
            System::Path("Data/config.cfg.vili").loadResource(&configFile, System::Loaders::dataLoader);
            vili::ComplexAttribute& gameConfig = configFile.at("GameConfig");

            //Cursor
            Cursor::Cursor cursor(&window);
            cursor.updateOutsideWindow(true);
            Collision::PolygonalCollider cursorCollider("cursor");
            cursorCollider.addPoint(0, 0);
            cursorCollider.addPoint(1, 0);
            cursorCollider.addPoint(1, 1);
            cursorCollider.addPoint(0, 1);
            Script::hookCore.dropValue("Cursor", &cursor);

            //World Creation / Loading
            World::World world;
            Script::hookCore.dropValue("World", &world);

            //Keybinding
            Input::KeyBinder keybind;
            Script::hookCore.dropValue("KeyBinder", &keybind);
            keybind.loadFromFile(configFile);

            sf::Event event;

            //Framerate / DeltaTime
            Time::FPSCounter fps;
            fps.loadFont(font);
            FramerateManager framerateManager(gameConfig);
            window.setVerticalSyncEnabled(framerateManager.isVSyncEnabled());

            Light::initLights();

            if (mapName != "")
                world.loadFromFile(mapName);
            System::Path("boot.lua").loadResource(world.getScriptEngine(), System::Loaders::luaLoader);

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
                    cursorCollider.setPosition(cursor.getX(), cursor.getY());
                    std::vector<Script::GameObject*> clickableGameObjects = world.getAllGameObjects({"Click"});
                    std::vector<Collision::PolygonalCollider*> elementsCollidedByCursor = world.getAllCollidersByCollision(
                        &cursorCollider, -world.getCamera()->getX(), -world.getCamera()->getY());
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
