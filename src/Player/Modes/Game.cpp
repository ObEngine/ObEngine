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
#include "Scene/TXScene.hpp"

namespace obe::Modes
{
    void startGame()
    {
        //Creating Window
        System::MainWindow.init(System::WindowContext::GameWindow);

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

        //Config
        vili::ComplexNode& gameConfig = System::Config.at("GameConfig");

        //Cursor
        System::Cursor cursor;

        //Scene Creation / Loading
        Scene::Scene scene;
        //Scene::TXScene scene = Scene::TXScene::CreateRootScene();

        Script::ScriptEngine.setErrorHandler([](int statuscode, const char* message)
        {
            Debug::Log->error("<LuaError>({0}) : {1}", statuscode, message);
        });

        //Keybinding
        Input::InputManager inputManager;

        inputManager.configure(System::Config.at("KeyBinding"));
        inputManager.addContext("game");

        sf::Event event;

        //Framerate / DeltaTime
        Time::FramerateManager framerateManager(gameConfig);

        System::Path("Lib/Internal/GameInit.lua").load(System::Loaders::luaLoader, Script::ScriptEngine);
        System::Path("boot.lua").load(System::Loaders::luaLoader, Script::ScriptEngine, true);
        Script::ScriptEngine.dostring("Game.Start()");

        //Game Starts
        while (System::MainWindow.isOpen())
        {
            framerateManager.update();

            gameTriggers->pushParameter("Update", "dt", framerateManager.getGameSpeed());
            gameTriggers->trigger("Update");
                
            if (framerateManager.doRender())
                gameTriggers->trigger("Render");

            while (System::MainWindow.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    System::MainWindow.close();
                    break;
                case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                case sf::Event::JoystickButtonPressed:
                case sf::Event::JoystickButtonReleased:
                case sf::Event::JoystickMoved:
                case sf::Event::KeyReleased:
                case sf::Event::KeyPressed:
                    Input::Monitors::RequireRefresh = true;
                    if (event.key.code == sf::Keyboard::Escape)
                        System::MainWindow.close();
                    break;
                }
            }

            //Events
            scene.update();
            Triggers::TriggerDatabase::GetInstance()->update();
            inputManager.update();
            if (Input::Monitors::RequireRefresh)
                Input::Monitors::UpdateMonitors();
            cursor.update();

            if (framerateManager.doRender())
            {
                System::MainWindow.clear(Graphics::Utils::ClearColor);
                scene.draw();
                for (auto& sprite : Graphics::LevelSprite::Pool)
                {
                }

                System::MainWindow.display();
            }
        }
        gameTriggers->trigger("End");
        Triggers::TriggerDatabase::GetInstance()->update();
        scene.clear();
        scene.update();
        System::MainWindow.close();
    }
}
