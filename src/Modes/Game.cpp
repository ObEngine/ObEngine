#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Input/InputManager.hpp>
#include <Modes/Game.hpp>
#include <Scene/Scene.hpp>
#include <Script/GlobalState.hpp>
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
            vili::ViliParser loadingStrDP("Sprites/Menus/loading.vili");
            std::string loadingRandomStr = loadingStrDP.at<vili::ArrayNode>("Loading", "loadingStr").get(
                Utils::Math::randint(0, loadingStrDP.at<vili::ArrayNode>("Loading", "loadingStr").size() - 1));
            loadingText.setString(loadingRandomStr);
            window.draw(loadingSprite);
            window.draw(loadingText);
            window.display();

            Script::hookCore.dropValue("TriggerDatabase", Triggers::TriggerDatabase::GetInstance());

            //Font
            sf::Font font;
            font.loadFromFile("Data/Fonts/arial.ttf");

            //Config
            vili::ViliParser configFile;
            System::Path("Data/config.cfg.vili").loadResource(&configFile, System::Loaders::dataLoader);
            vili::ComplexNode& gameConfig = configFile.at("GameConfig");

            //Cursor
            System::Cursor cursor;
            Script::hookCore.dropValue("Cursor", &cursor);

            //Scene Creation / Loading
            Scene::Scene scene;
            Script::hookCore.dropValue("Scene", &scene);

            //Keybinding
            Input::InputManager inputManager;
            Script::hookCore.dropValue("KeyBinder", &inputManager);
            inputManager.configure(configFile.at("KeyBinding"));
            inputManager.addContext("game");

            sf::Event event;

            //Framerate / DeltaTime
            Time::FPSCounter fps;
            fps.loadFont(font);
            Time::FramerateManager framerateManager(window, gameConfig);
            window.setVerticalSyncEnabled(framerateManager.isVSyncEnabled());

            scene.setCameraLock(false);

            System::Path("boot.lua").loadResource(&Script::ScriptEngine, System::Loaders::luaLoader);
            Script::ScriptEngine.dostring("Game.Start()");

            //Game Starts
            while (window.isOpen())
            {
                framerateManager.update();

                //Events
                Triggers::TriggerDatabase::GetInstance()->update();
                scene.update(framerateManager.getGameSpeed());
                inputManager.update();
                cursor.update();

                //Triggers Handling
                inputManager.handleTriggers();

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

                if (framerateManager.doRender())
                {
                    window.clear();
                    scene.display(window);

                    window.display();
                }
            }
            window.close();
        }
    }
}
