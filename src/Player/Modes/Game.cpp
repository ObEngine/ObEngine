#include <Graphics/DrawUtils.hpp>
#include <Input/InputManager.hpp>
#include <Modes/Game.hpp>
#include <Scene/Scene.hpp>
#include <Script/GlobalState.hpp>
#include <System/Config.hpp>
#include <System/Cursor.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <System/Window.hpp>
#include <Time/FramerateCounter.hpp>
#include <Time/FramerateManager.hpp>
#include <Triggers/TriggerDatabase.hpp>

#include <Time/TimeUtils.hpp>

#include <any>

namespace obe
{
    namespace Modes
    {
        void startGame()
        {
            //Creating Window
            System::InitWindow(System::WindowContext::GameWindow);

            Triggers::TriggerDatabase::GetInstance()->reg("TriggerDatabase");

            //Game Triggers
            Triggers::TriggerGroupPtr gameTriggers(
                Triggers::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Game"),
                Triggers::TriggerGroupPtrRemover);
            gameTriggers
                ->addTrigger("Start")
                ->trigger("Start")
                ->addTrigger("End")
                ->addTrigger("Update")
                ->addTrigger("Render");

            //Font
            sf::Font font;
            font.loadFromFile("Data/Fonts/arial.ttf");

            //Config
            vili::ComplexNode& gameConfig = System::Config.at("GameConfig");

            //Cursor
            System::Cursor cursor;
            cursor.reg("Cursor");

            //Scene Creation / Loading
            Scene::Scene scene;
            scene.reg("Scene");
            Script::ScriptEngine.setErrorHandler([](int statuscode, const char* message)
            {
                Debug::Log->error("<LuaError>({0}) : {1}", statuscode, message);
            });

            //Keybinding
            Input::InputManager inputManager;
            inputManager.reg("InputManager");
            inputManager.configure(System::Config.at("KeyBinding"));
            inputManager.addContext("game");

            sf::Event event;

            //Framerate / DeltaTime
            Time::FPSCounter fps;
            fps.loadFont(font);
            Time::FramerateManager framerateManager(gameConfig);

            System::Path("boot.lua").loadResource(&Script::ScriptEngine, System::Loaders::luaLoader);
            Script::ScriptEngine.dostring("Game.Start()");

            sf::Clock CLOCKI;
            sf::Time lastDisplay;
            sf::Time t1;
            sf::Time t2;
            sf::Time t3;

            //Game Starts
            while (System::MainWindow.isOpen())
            {
                framerateManager.update();

                t1 = CLOCKI.getElapsedTime();
                gameTriggers->pushParameter("Update", "dt", framerateManager.getGameSpeed());
                gameTriggers->trigger("Update");
                std::cout << "Update : " << (CLOCKI.getElapsedTime() - t1).asMilliseconds() << std::endl;
                
                t2 = CLOCKI.getElapsedTime();
                if (true)
                {
                    gameTriggers->trigger("Render");
                }
                std::cout << "Render : " << (CLOCKI.getElapsedTime() - t2).asMilliseconds() << std::endl;
                    

                //Events
                t3 = CLOCKI.getElapsedTime();
                scene.update(framerateManager.getGameSpeed());
                Triggers::TriggerDatabase::GetInstance()->update();
                inputManager.update();
                cursor.update();
                std::cout << "Scene : " << (CLOCKI.getElapsedTime() - t3).asMilliseconds() << std::endl;

                //Triggers Handling
                inputManager.handleTriggers();

                while (System::MainWindow.pollEvent(event))
                {
                    switch (event.type)
                    {
                    case sf::Event::Closed:
                        System::MainWindow.close();
                        break;

                    case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Escape)
                            System::MainWindow.close();
                        break;
                    }
                }

                if (true)
                {
                    System::MainWindow.clear(Graphics::Utils::clearColor);
                    scene.display();

                    System::MainWindow.display();
                    std::cout << "Last display : " << (CLOCKI.getElapsedTime() - lastDisplay).asMilliseconds() << std::endl;
                    lastDisplay = CLOCKI.getElapsedTime();
                }
            }
            gameTriggers->trigger("End");
            Triggers::TriggerDatabase::GetInstance()->update();
            
            scene.update(framerateManager.getGameSpeed());
            System::MainWindow.close();

            std::cin.get();
        }
    }
}
