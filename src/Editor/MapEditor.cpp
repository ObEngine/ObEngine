#include <TGUI/TGUI.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Debug/Console.hpp>
#include <Editor/CollidersEditActions.hpp>
#include <Editor/EditorGUI.hpp>
#include <Editor/Grid.hpp>
#include <Editor/MapEditor.hpp>
#include <Editor/MapEditorTools.hpp>
#include <Editor/EditorGlobalActions.hpp>
#include <Editor/SpriteEditActions.hpp>
#include <Input/InputManager.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Network/Network.hpp>
#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>
#include <Script/GlobalState.hpp>
#include <Script/Script.hpp>
#include <System/Cursor.hpp>
#include <System/Loaders.hpp>
#include <Time/FramerateCounter.hpp>
#include <Time/FramerateManager.hpp>
#include <Transform/UnitVector.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/MathUtils.hpp>

namespace obe
{
    namespace Editor
    {
        void editMap(const std::string& mapName)
        {
            std::cout << "<System> Creating window with resolution " << Transform::UnitVector::Screen.w << "x" << Transform::UnitVector::Screen.h << std::endl;
            
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

            //Console
            Debug::Console gameConsole;
            Script::hookCore.dropValue("Console", &gameConsole);

            //Font
            sf::Font font;
            font.loadFromFile("Data/Fonts/arial.ttf");

            //Config
            vili::ViliParser configFile;
            System::Path("Data/config.cfg.vili").loadResource(&configFile, System::Loaders::dataLoader);
            vili::ComplexNode& gameConfig = configFile->at("GameConfig");
            int scrollSensitive = gameConfig.at<vili::DataNode>("scrollSensibility");
            vili::ComplexNode& developpement = configFile.at("Developpement");

            //Cursor
            System::Cursor cursor;
            Script::hookCore.dropValue("Cursor", &cursor);

            //Scene Creation / Loading
            Scene::Scene scene;
            //scene.getCamera()->bindView(window);
            Script::ScriptEngine["stream"] = gameConsole.createStream("Scene", true);
            Script::ScriptEngine.setErrorHandler([&gameConsole](int statuscode, const char* message)
            {
                gameConsole.pushMessage("LuaError", std::string("<Main> :: ") + message, sf::Color::Red);
                std::cout << "[LuaError]<Main> : " << "[CODE::" << statuscode << "] : " << message << std::endl;
            });
            Script::hookCore.dropValue("Scene", &scene);

            //Socket
            Network::NetworkHandler networkHandler;

            //Keybinding
            Input::InputManager inputManager;
            Script::hookCore.dropValue("KeyBinder", &inputManager);
            inputManager.configure(configFile.at("KeyBinding"));
            inputManager.addContext("game")
                   .addContext("mapEditor");

            //Editor Grid
            EditorGrid editorGrid(32, 32);
            inputManager.getAction("MagnetizeUp").setRepeat(200);
            inputManager.getAction("MagnetizeDown").setRepeat(200);
            inputManager.getAction("MagnetizeLeft").setRepeat(200);
            inputManager.getAction("MagnetizeRight").setRepeat(200);

            //GUI
            sf::Event event;
            tgui::Gui gui(window);
            gui.setFont("Data/Fonts/weblysleekuil.ttf");
            tgui::Panel::Ptr mainPanel = tgui::Panel::create();
            GUI::init(window);
            int saveEditMode = -1;
            gui.add(mainPanel);
            mainPanel->setSize(window.getSize().x, window.getSize().y);

            GUI::buildEditorMenu(mainPanel);
            GUI::buildObjectCreationMenu(mainPanel);

            tgui::Panel::Ptr editorPanel = gui.get<tgui::Panel>("editorPanel", true);
            tgui::Panel::Ptr mapPanel = gui.get<tgui::Panel>("mapPanel", true);
            tgui::Panel::Ptr settingsPanel = gui.get<tgui::Panel>("settingsPanel", true);
            tgui::Panel::Ptr spritesPanel = gui.get<tgui::Panel>("spritesPanel", true);
            tgui::Panel::Ptr objectsPanel = gui.get<tgui::Panel>("objectsPanel", true);
            tgui::Panel::Ptr requiresPanel = gui.get<tgui::Panel>("requiresPanel", true);

            GUI::buildToolbar(mainPanel, editorPanel);

            tgui::ComboBox::Ptr editMode = gui.get<tgui::ComboBox>("editMode", true);
            tgui::ComboBox::Ptr cameraMode = gui.get<tgui::ComboBox>("cameraMode", true);

            GUI::buildEditorMapMenu(mapPanel, scene);
            GUI::buildEditorSettingsMenu(settingsPanel, editorGrid, cursor, editMode);
            GUI::buildEditorSpritesMenu(spritesPanel);
            GUI::buildEditorObjectsMenu(objectsPanel, requiresPanel);

            tgui::CheckBox::Ptr enableGridCheckbox = gui.get<tgui::CheckBox>("enableGridCheckbox", true);
            tgui::CheckBox::Ptr snapGridCheckbox = gui.get<tgui::CheckBox>("snapGridCheckbox", true);
            tgui::TextBox::Ptr mapNameInput = gui.get<tgui::TextBox>("mapNameInput", true);
            tgui::Label::Ptr savedLabel = gui.get<tgui::Label>("savedLabel", true);
            tgui::Label::Ptr infoLabel = gui.get<tgui::Label>("infoLabel", true);
            tgui::CheckBox::Ptr displayFramerateCheckbox = gui.get<tgui::CheckBox>("displayFramerateCheckbox", true);

            //Map Editor
            Graphics::LevelSprite* hoveredSprite = nullptr;
            Graphics::LevelSprite* selectedSprite = nullptr;
            Graphics::LevelSpriteHandlePoint* selectedHandlePoint = nullptr;
            int selectedSpriteOffsetX = 0;
            int selectedSpriteOffsetY = 0;
            int cameraSpeed = Transform::UnitVector::Screen.h;
            int currentLayer = 1;
            Collision::PolygonalCollider* selectedMasterCollider = nullptr;
            int colliderPtGrabbed = -1;
            bool masterColliderGrabbed = false;
            sf::Text sprInfo;
            sprInfo.setFont(font);
            sprInfo.setCharacterSize(16);
            sprInfo.setFillColor(sf::Color::White);
            sf::RectangleShape sprInfoBackground(sf::Vector2f(100, 160));
            sprInfoBackground.setFillColor(sf::Color(0, 0, 0, 200));
            double waitForMapSaving = -1;

            //Framerate / DeltaTime
            Time::FPSCounter fps;
            fps.loadFont(font);
            Time::FramerateManager framerateManager(window, gameConfig);
            window.setVerticalSyncEnabled(framerateManager.isVSyncEnabled());

            scene.loadFromFile(mapName);

            mapNameInput->setText(scene.getLevelName());

            //Connect InputManager Actions
            connectSaveActions(inputManager, mapName, scene, waitForMapSaving, savedLabel);
            connectCamMovementActions(inputManager, scene, cameraSpeed, framerateManager);
            connectGridActions(inputManager, enableGridCheckbox, snapGridCheckbox, cursor, editorGrid);
            connectMenuActions(inputManager, editMode, cameraMode);
            connectSpriteLayerActions(inputManager, selectedSprite, scene, currentLayer);
            connectSpriteActions(inputManager, hoveredSprite, selectedSprite, selectedHandlePoint, 
                scene, cursor, editorGrid, selectedSpriteOffsetX, selectedSpriteOffsetY, sprInfo, sprInfoBackground);
            connectCollidersActions(inputManager, scene, cursor, colliderPtGrabbed, selectedMasterCollider, masterColliderGrabbed);

            editMode->connect("itemselected", [&inputManager, editMode]()
            {
                if (editMode->getSelectedItem() == "LevelSprites")
                {
                    inputManager.addContext("spriteEditing");
                }
                else
                {
                    inputManager.removeContext("spriteEditing");
                }
                if (editMode->getSelectedItem() == "Collisions")
                {
                    inputManager.addContext("colliderEditing");
                }
                else
                {
                    inputManager.removeContext("colliderEditing");
                }
            });

            inputManager.getAction("MagnetizeUp").connect([&scene](const Input::InputActionEvent& event)
            {
                scene.getCamera()->scale(1.1);
            });
            inputManager.getAction("MagnetizeDown").connect([&scene](const Input::InputActionEvent& event)
            {
                scene.getCamera()->scale(0.9);
            });

            //Game Starts
            while (window.isOpen())
            {
                framerateManager.update();
                if (waitForMapSaving >= 0)
                {
                    waitForMapSaving += framerateManager.getDeltaTime();
                    if (waitForMapSaving > 1 && waitForMapSaving < 2)
                    {
                        savedLabel->hideWithEffect(tgui::ShowAnimationType::SlideFromTop, sf::Time(sf::seconds(0.5)));
                        waitForMapSaving = 2;
                    }
                    else if (waitForMapSaving > 3)
                        waitForMapSaving = -1;
                }


                //GUI Actions
                inputManager.setEnabled(!gameConsole.isVisible());

                bool drawFPS = displayFramerateCheckbox->isChecked();

                if (editorPanel->isVisible() && saveEditMode < 0)
                {
                    saveEditMode = editMode->getSelectedItemIndex();
                    editMode->setSelectedItemByIndex(3);
                }
                else if (!editorPanel->isVisible() && saveEditMode > 0)
                {
                    editMode->setSelectedItemByIndex(saveEditMode);
                    saveEditMode = -1;
                }

                Transform::UnitVector pixelCamera = scene.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                //Updates
                if (!gameConsole.isVisible())
                {
                    if (cameraMode->getSelectedItem() == "Movable Camera")
                    {
                        scene.setCameraLock(true);
                    }
                    else
                    {
                        scene.setCameraLock(false);
                    }
                }

                Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                //Sprite Editing
                if (editMode->getSelectedItem() == "LevelSprites")
                {
                    scene.enableShowCollision(true, true, false, false);

                    if (hoveredSprite == nullptr)
                    {
                        hoveredSprite = scene.getLevelSpriteByPosition(cursCoord, currentLayer);
                        if (hoveredSprite != nullptr && hoveredSprite != selectedSprite)
                        {
                            hoveredSprite = scene.getLevelSpriteByPosition(cursCoord, currentLayer);
                            hoveredSprite->setColor(sf::Color(0, 255, 255));
                            std::string sprInfoStr;
                            sprInfoStr = "Hovered Sprite : \n";
                            sprInfoStr += "    Id : " + hoveredSprite->getId() + "\n";
                            sprInfoStr += "    Name : " + hoveredSprite->getPath() + "\n";
                            sprInfoStr += "    Pos : " + std::to_string(hoveredSprite->getX()) + "," + std::to_string(hoveredSprite->getY()) + "\n";
                            sprInfoStr += "    Size : " + std::to_string(hoveredSprite->getWidth()) + "," + std::to_string(hoveredSprite->getHeight()) + "\n";
                            sprInfoStr += "    Rot : " + std::to_string(hoveredSprite->getRotation()) + "\n";
                            sprInfoStr += "    Layer / Z : " + std::to_string(hoveredSprite->getLayer()) + "," + std::to_string(hoveredSprite->getZDepth()) + "\n";
                            sprInfo.setString(sprInfoStr);
                            sprInfoBackground.setSize(sf::Vector2f(sprInfo.getGlobalBounds().width + 20, sprInfo.getGlobalBounds().height - 10));
                        }
                        else
                            hoveredSprite == nullptr;
                    }
                    else if (hoveredSprite != nullptr)
                    {
                        sprInfoBackground.setPosition(cursor.getX() + 40, cursor.getY());
                        sprInfo.setPosition(cursor.getX() + 50, cursor.getY());
                        bool outHover = false;
                        Graphics::LevelSprite* testHoverSprite = scene.getLevelSpriteByPosition(cursCoord, currentLayer);
                        if (testHoverSprite != hoveredSprite)
                            outHover = true;
                        if (outHover)
                        {
                            if (hoveredSprite != selectedSprite)
                                hoveredSprite->setColor(sf::Color::White);
                            hoveredSprite = nullptr;
                            sprInfo.setString("");
                        }
                    }                      
                }
                else
                {
                    if (selectedSprite != nullptr)
                        selectedSprite->setColor(sf::Color::White);
                    selectedSprite = nullptr;
                    hoveredSprite = nullptr;
                    selectedSpriteOffsetX = 0;
                    selectedSpriteOffsetY = 0;
                    sprInfo.setString("");
                }

                //Collision Edition
                if (editMode->getSelectedItem() == "Collisions")
                {
                    Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);

                    scene.enableShowCollision(true, true, true, true);
                    if (selectedMasterCollider != nullptr)
                    {
                        selectedMasterCollider->clearHighlights();
                        selectedMasterCollider->highlightLine(selectedMasterCollider->findClosestLine(cursCoord));
                    }     
                }

                //GUI Update
                infoLabel->setText(
                    "Cursor : (" +
                    std::to_string(cursor.getX()) + ", " + std::to_string(cursor.getY()) +
                    ")" +
                    std::string("   Camera : (") +
                    std::to_string(int(pixelCamera.x)) + ", " + std::to_string(int(pixelCamera.y)) +
                    ")" +
                    std::string("   Sum : (") +
                    std::to_string(int(pixelCamera.x) + int(cursor.getX())) + ", " + std::to_string(int(pixelCamera.y) + int(cursor.getY())) +
                    ")" +
                    std::string("   Layer : ") + std::to_string(currentLayer)
                );

                //Events
                scene.update(framerateManager.getGameSpeed());
                Triggers::TriggerDatabase::GetInstance()->update();
                inputManager.update();
                cursor.update();
                if (drawFPS) fps.uTick();
                if (drawFPS && framerateManager.doRender()) fps.tick();

                //Triggers Handling
                networkHandler.handleTriggers();
                //cursor.handleTriggers();
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
                        if (event.key.code == sf::Keyboard::V)
                        {
                            if (event.key.control)
                            {
                                std::string clipboard_content = "";
                                gameConsole.insertInputBufferContent(clipboard_content);
                            }
                        }
                        if (event.key.code == sf::Keyboard::F1)
                            gameConsole.setVisible(!gameConsole.isVisible());
                        if (event.key.code == sf::Keyboard::Up)
                            gameConsole.upHistory();
                        if (event.key.code == sf::Keyboard::Down)
                            gameConsole.downHistory();
                        if (event.key.code == sf::Keyboard::Left && gameConsole.isVisible())
                            gameConsole.moveCursor(-1);
                        if (event.key.code == sf::Keyboard::Right && gameConsole.isVisible())
                            gameConsole.moveCursor(1);
                        break;
                    case sf::Event::TextEntered:
                        if (gameConsole.isVisible())
                            gameConsole.inputKey(event.text.unicode);
                        break;
                    case sf::Event::MouseWheelMoved:
                        if (event.mouseWheel.delta >= scrollSensitive)
                        {
                            gameConsole.scroll(-1);
                        }
                        else if (event.mouseWheel.delta <= -scrollSensitive)
                        {
                            gameConsole.scroll(1);
                        }
                        break;
                    }
                    gui.handleEvent(event);
                }
                //Draw Everything Here
                if (framerateManager.doRender())
                {
                    window.clear();
                    scene.display(window);
                    pixelCamera = scene.getCamera()->getPosition().to<Transform::Units::WorldPixels>(); // Do it once (Grid Draw Offset) <REVISION>
                    //Show Collision
                    if (editMode->getSelectedItem() == "Collisions")
                        scene.enableShowCollision(true);
                    else
                        scene.enableShowCollision(false);
                    if (enableGridCheckbox->isChecked())
                        editorGrid.draw(window, cursor, pixelCamera.x, pixelCamera.y);
                    //HUD & GUI
                    if (sprInfo.getString() != "")
                    {
                        window.draw(sprInfoBackground);
                        window.draw(sprInfo);
                    }
                    gui.draw();
                    if (drawFPS)
                        fps.draw(window);

                    //Console
                    if (gameConsole.isVisible())
                        gameConsole.display(window);

                    window.display();
                }
            }
            window.close();
            gui.removeAllWidgets();
        }
    }
}
