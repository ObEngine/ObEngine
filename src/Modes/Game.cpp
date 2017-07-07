#include <SFML/Graphics.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Input/KeyBind.hpp>
#include <Modes/Game.hpp>
#include <Scene/World.hpp>
#include <Script/Script.hpp>
#include <System/Cursor.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <Time/FramerateCounter.hpp>
#include <Time/FramerateManager.hpp>
#include <Transform/UnitVector.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/MathUtils.hpp>

namespace obe
{
    namespace Modes
    {
        void startGame()
        {
            //Creating Window
            sf::RenderWindow window(sf::VideoMode(Transform::UnitVector::Screen.w, Transform::UnitVector::Screen.h), "ObEngine", sf::Style::Fullscreen);
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
                Utils::Math::randint(0, loadingStrDP.at<vili::ListAttribute>("Loading", "loadingStr").size() - 1));
            loadingText.setString(loadingRandomStr);
            window.draw(loadingSprite);
            window.draw(loadingText);
            window.display();

            Script::hookCore.dropValue("TriggerDatabase", Triggers::TriggerDatabase::GetInstance());

            //Font
            sf::Font font;
            font.loadFromFile("Data/Fonts/arial.ttf");

            //Config
            vili::DataParser configFile;
            System::Path("Data/config.cfg.vili").loadResource(&configFile, System::Loaders::dataLoader);
            vili::ComplexAttribute& gameConfig = configFile.at("GameConfig");

            //Cursor
            System::Cursor cursor(&window);
            cursor.updateOutsideWindow(true);
            Collision::PolygonalCollider cursorCollider("cursor");
            cursorCollider.addPoint(0, 0);
            cursorCollider.addPoint(1, 0);
            cursorCollider.addPoint(1, 1);
            cursorCollider.addPoint(0, 1);
            Script::hookCore.dropValue("Cursor", &cursor);

            //World Creation / Loading
            Scene::World world;
            Script::hookCore.dropValue("World", &world);

            //Keybinding
            Input::KeyBinder keybind;
            Script::hookCore.dropValue("KeyBinder", &keybind);
            keybind.loadFromFile(configFile);

            sf::Event event;

            //Framerate / DeltaTime
            Time::FPSCounter fps;
            fps.loadFont(font);
            Time::FramerateManager framerateManager(gameConfig);
            window.setVerticalSyncEnabled(framerateManager.isVSyncEnabled());

            world.setCameraLock(false);

            System::Path("boot.lua").loadResource(world.getScriptEngine(), System::Loaders::luaLoader);
            world.getScriptEngine()->dostring("Game.Start()");

            //Game Starts
            while (window.isOpen())
            {
                framerateManager.update();

                //Events
                Triggers::TriggerDatabase::GetInstance()->update();
                world.update(framerateManager.getGameSpeed());
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
                        break;
                    }
                }

                if (cursor.getClicked(System::CursorButton::Left) || cursor.getPressed(System::CursorButton::Left))
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
                                if (cursor.getClicked(System::CursorButton::Left))
                                    world.getGameObject(clickableGameObjects[j]->getID())->getLocalTriggers()->setTriggerState("Click", true);
                                if (cursor.getPressed(System::CursorButton::Left))
                                    world.getGameObject(clickableGameObjects[j]->getID())->getLocalTriggers()->setTriggerState("Press", true);
                            }
                        }
                    }
                }

                if (framerateManager.doRender())
                {
                    window.clear();
                    world.display(window);
                    window.draw(*cursor.getSprite());

                    window.display();
                }
            }
            window.close();
        }
    }
}
