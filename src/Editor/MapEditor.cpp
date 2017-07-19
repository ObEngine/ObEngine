#include <TGUI/TGUI.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Debug/Console.hpp>
#include <Editor/EditorGUI.hpp>
#include <Editor/Grid.hpp>
#include <Editor/MapEditor.hpp>
#include <Editor/MapEditorTools.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Input/KeyManager.hpp>
#include <Network/Network.hpp>
#include <Scene/World.hpp>
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

            //Console
            Debug::Console gameConsole;
            Script::hookCore.dropValue("Console", &gameConsole);

            //Font
            sf::Font font;
            font.loadFromFile("Data/Fonts/arial.ttf");

            //Config
            vili::DataParser configFile;
            System::Path("Data/config.cfg.vili").loadResource(&configFile, System::Loaders::dataLoader);
            vili::ComplexAttribute& gameConfig = configFile->at("GameConfig");
            int scrollSensitive = gameConfig.at<vili::BaseAttribute>("scrollSensibility");
            vili::ComplexAttribute& developpement = configFile.at("Developpement");

            bool showCursor = developpement.at<vili::BaseAttribute>("showCursor");

            //Cursor
            System::Cursor cursor(&window);
            cursor.selectAnimatorPath("RoundWhite");
            Script::hookCore.dropValue("Cursor", &cursor);

            //World Creation / Loading
            Scene::World world;
            Script::ScriptEngine["stream"] = gameConsole.createStream("World", true);
            Script::ScriptEngine.setErrorHandler([&gameConsole](int statuscode, const char* message)
            {
                gameConsole.pushMessage("LuaError", std::string("<Main> :: ") + message, sf::Color::Red);
                std::cout << "[LuaError]<Main> : " << "[CODE::" << statuscode << "] : " << message << std::endl;
            });
            Script::hookCore.dropValue("World", &world);

            //Socket
            Network::NetworkHandler networkHandler;

            //Keybinding
            Input::KeyboardManager keybind;
            Script::hookCore.dropValue("KeyBinder", &keybind);
            keybind.configure(configFile.at("KeyBinding"));
            keybind.addContext("game")
                   .addContext("mapEditor");

            //Editor Grid
            EditorGrid editorGrid(32, 32);
            keybind.getAction("MagnetizeUp").setRepeat(200);
            keybind.getAction("MagnetizeDown").setRepeat(200);
            keybind.getAction("MagnetizeLeft").setRepeat(200);
            keybind.getAction("MagnetizeRight").setRepeat(200);

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

            GUI::buildEditorMapMenu(mapPanel, world);
            GUI::buildEditorSettingsMenu(settingsPanel, editorGrid, cursor, editMode);
            GUI::buildEditorSpritesMenu(spritesPanel);
            GUI::buildEditorObjectsMenu(objectsPanel, requiresPanel);

            tgui::CheckBox::Ptr enableGridCheckbox = gui.get<tgui::CheckBox>("enableGridCheckbox", true);
            tgui::TextBox::Ptr mapNameInput = gui.get<tgui::TextBox>("mapNameInput", true);
            tgui::Label::Ptr savedLabel = gui.get<tgui::Label>("savedLabel", true);
            tgui::Label::Ptr infoLabel = gui.get<tgui::Label>("infoLabel", true);
            tgui::CheckBox::Ptr displayFramerateCheckbox = gui.get<tgui::CheckBox>("displayFramerateCheckbox", true);

            //Map Editor
            Graphics::LevelSprite* hoveredSprite = nullptr;
            Graphics::LevelSprite* selectedSprite = nullptr;
            Graphics::LevelSprite::HandlePoint* selectedHandlePoint = nullptr;
            sf::FloatRect sdBoundingRect;
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

            // KeyBind Actions
            keybind.getAction("CamMovable").connect(Input::KeyState::Pressed, [&cameraMode](Input::KeyboardActionEvent event)
                                                {
                                                    cameraMode->setSelectedItemByIndex(0);
                                                });
            keybind.getAction("CamFree").connect(Input::KeyState::Pressed, [&cameraMode](Input::KeyboardActionEvent event)
                                             {
                                                 cameraMode->setSelectedItemByIndex(1);
                                             });
            keybind.getAction("SpriteMode").connect(Input::KeyState::Pressed, [&editMode](Input::KeyboardActionEvent event)
                                                {
                                                    editMode->setSelectedItemByIndex(0);
                                                });
            keybind.getAction("CollisionMode").connect(Input::KeyState::Pressed, [&editMode](Input::KeyboardActionEvent event)
                                                   {
                                                       editMode->setSelectedItemByIndex(1);
                                                   });
            keybind.getAction("CamLeft").connect(Input::KeyState::Hold, [&world, &cameraSpeed, &framerateManager](Input::KeyboardActionEvent event)
                                             {
                                                 world.getCamera()->move(Transform::UnitVector(-cameraSpeed * framerateManager.getGameSpeed(), 0, Transform::Units::WorldPixels));
                                             });
            keybind.getAction("CamRight").connect(Input::KeyState::Hold, [&world, &cameraSpeed, &framerateManager](Input::KeyboardActionEvent event)
                                              {
                                                  world.getCamera()->move(Transform::UnitVector(cameraSpeed * framerateManager.getGameSpeed(), 0, Transform::Units::WorldPixels));
                                              });
            keybind.getAction("CamUp").connect(Input::KeyState::Hold, [&world, &cameraSpeed, &framerateManager](Input::KeyboardActionEvent event)
                                           {
                                               world.getCamera()->move(Transform::UnitVector(0, -cameraSpeed * framerateManager.getGameSpeed(), Transform::Units::WorldPixels));
                                           });
            keybind.getAction("CamDown").connect(Input::KeyState::Hold, [&world, &cameraSpeed, &framerateManager](Input::KeyboardActionEvent event)
                                             {
                                                 world.getCamera()->move(Transform::UnitVector(0, cameraSpeed * framerateManager.getGameSpeed(), Transform::Units::WorldPixels));
                                             });
            keybind.getAction("CamDash").connect(Input::KeyState::Pressed, [&cameraSpeed](Input::KeyboardActionEvent event)
                                             {
                                                 cameraSpeed = Transform::UnitVector::Screen.h * 2.5;
                                             });
            keybind.getAction("CamDash").connect(Input::KeyState::Released, [&cameraSpeed](Input::KeyboardActionEvent event)
                                             {
                                                 cameraSpeed = Transform::UnitVector::Screen.h;
                                             });
            keybind.getAction("MagnetizeUp").connect(Input::KeyState::Hold, [&enableGridCheckbox, &cursor, &editorGrid](Input::KeyboardActionEvent event)
                                                 {
                                                     if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, 0, -1);
                                                 });
            keybind.getAction("MagnetizeRight").connect(Input::KeyState::Hold, [&enableGridCheckbox, &cursor, &editorGrid](Input::KeyboardActionEvent event)
                                                    {
                                                        if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, 1, 0);
                                                    });
            keybind.getAction("MagnetizeDown").connect(Input::KeyState::Hold, [&enableGridCheckbox, &cursor, &editorGrid](Input::KeyboardActionEvent event)
                                                   {
                                                       if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, 0, 1);
                                                   });
            keybind.getAction("MagnetizeLeft").connect(Input::KeyState::Hold, [&enableGridCheckbox, &cursor, &editorGrid](Input::KeyboardActionEvent event)
                                                   {
                                                       if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, -1, 0);
                                                   });
            keybind.getAction("MagnetizeCursor").connect(Input::KeyState::Hold, [&enableGridCheckbox, &cursor, &editorGrid](Input::KeyboardActionEvent event)
                                                     {
                                                         if (enableGridCheckbox->isChecked()) editorGrid.magnetize(cursor);
                                                     });
            keybind.getAction("CancelOffset").connect(Input::KeyState::Pressed,
                                                      [&selectedSprite, &cursor, &editorGrid, &selectedSpriteOffsetX, &selectedSpriteOffsetY](Input::KeyboardActionEvent event)
                                                  {
                                                      if (cursor.getPressed(System::MouseButton::Left) && selectedSprite != nullptr)
                                                      {
                                                          selectedSpriteOffsetX = 0;
                                                          selectedSpriteOffsetY = 0;
                                                      }
                                                  });
            keybind.getAction("DeleteSprite").connect(Input::KeyState::Pressed,
                                                      [&selectedSprite, &world, &sprInfo, &hoveredSprite, &selectedSpriteOffsetX, &selectedSpriteOffsetY](Input::KeyboardActionEvent event)
                                                  {
                                                      if (selectedSprite != nullptr)
                                                      {
                                                          world.deleteSprite(selectedSprite);
                                                          selectedSprite = nullptr;
                                                          sprInfo.setString("");
                                                          hoveredSprite = nullptr;
                                                          selectedSpriteOffsetX = 0;
                                                          selectedSpriteOffsetY = 0;
                                                      }
                                                  });
            keybind.getAction("Attack").connect(Input::KeyState::Hold, [&world, &framerateManager](Input::KeyboardActionEvent event)
                                            {
                                                Collision::PolygonalCollider* collider0 = world.getCollisionByID("collider0");
                                                collider0->move(Transform::UnitVector(100.0 * framerateManager.getGameSpeed(), 0, Transform::Units::WorldPixels));
                                            });

            world.loadFromFile(mapName);

            mapNameInput->setText(world.getLevelName());

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
                keybind.setEnabled(!gameConsole.isConsoleVisible());

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

                Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                //Updates
                if (!gameConsole.isConsoleVisible())
                {
                    if (cameraMode->getSelectedItem() == "Movable Camera")
                    {
                        world.setCameraLock(true);
                    }
                    else
                    {
                        world.setCameraLock(false);
                    }
                }

                //Sprite Editing
                if (editMode->getSelectedItem() == "LevelSprites")
                {
                    world.enableShowCollision(true, true, false, false);

                    if (selectedHandlePoint != nullptr && cursor.getPressed(System::MouseButton::Left))
                    {
                        std::cout << "Moving ref : " << selectedHandlePoint->getReferencial() << std::endl;
                        selectedHandlePoint->moveTo(cursor.getX(), cursor.getY());
                    }
                    else if (selectedHandlePoint != nullptr && cursor.getReleased(System::MouseButton::Left))
                    {
                        selectedHandlePoint = nullptr;
                    }
                    else
                    {
                        //Layer Change
                        /*if (selectedSprite == nullptr && keybind.isActionToggled("LayerInc"))
                        {
                            currentLayer += 1;
                            world.getCamera()->scale(1.1);
                            if (hoveredSprite != nullptr)
                            {
                                hoveredSprite->setColor(sf::Color::White);
                                hoveredSprite = nullptr;
                                sprInfo.setString("");
                            }
                        }
                        if (selectedSprite == nullptr && keybind.isActionToggled("LayerDec"))
                        {
                            world.getCamera()->scale(0.9);
                            currentLayer -= 1;
                            if (hoveredSprite != nullptr)
                            {
                                hoveredSprite->setColor(sf::Color::White);
                                hoveredSprite = nullptr;
                                sprInfo.setString("");
                            }
                        }*/
                        //Sprite Hover
                        if (hoveredSprite == nullptr)
                        {
                            hoveredSprite = world.getSpriteByPos(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, currentLayer);
                            if (hoveredSprite != nullptr && hoveredSprite != selectedSprite)
                            {
                                hoveredSprite = world.getSpriteByPos(cursor.getX() + pixelCamera.x,
                                                                     cursor.getY() + pixelCamera.y, currentLayer);
                                sdBoundingRect = hoveredSprite->getRect();
                                hoveredSprite->setColor(sf::Color(0, 255, 255));
                                std::string sprInfoStr;
                                sprInfoStr = "Hovered Sprite : \n";
                                sprInfoStr += "    ID : " + hoveredSprite->getId() + "\n";
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
                            Graphics::LevelSprite* testHoverSprite = world.getSpriteByPos(cursor.getX() + pixelCamera.x,
                                                                                          cursor.getY() + pixelCamera.y, currentLayer);
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

                        //Sprite Pick
                        if (cursor.getClicked(System::MouseButton::Left))
                        {
                            if (selectedSprite != nullptr)
                            {
                                std::cout << "Picky picky :D" << std::endl;
                                selectedHandlePoint = selectedSprite->getHandlePoint(pixelCamera, cursor.getX(), cursor.getY());
                                std::cout << selectedHandlePoint << ", " << hoveredSprite << ", " << selectedSprite << std::endl;
                                if (selectedHandlePoint != nullptr)
                                {
                                    std::cout << "POINT POINT POINT" << std::endl;
                                    hoveredSprite = nullptr;
                                }
                                else if (hoveredSprite != selectedSprite)
                                {
                                    std::cout << "Unselect" << std::endl;
                                    selectedSprite->setColor(sf::Color::White);
                                    selectedSprite->unselect();
                                    sprInfo.setString("");
                                    selectedSprite = nullptr;
                                    selectedSpriteOffsetX = 0;
                                    selectedSpriteOffsetY = 0;
                                }
                                std::cout << "Ended NonEf" << std::endl;
                            }
                            if (hoveredSprite != nullptr)
                            {
                                std::cout << "MUCH WOW" << std::endl;
                                selectedSprite = hoveredSprite;
                                selectedSpriteOffsetX = (cursor.getX() + pixelCamera.x) - selectedSprite->getPosition().to<Transform::Units::WorldPixels>().x;
                                selectedSpriteOffsetY = (cursor.getY() + pixelCamera.y) - selectedSprite->getPosition().to<Transform::Units::WorldPixels>().y;
                                selectedSprite->select();

                                sdBoundingRect = selectedSprite->getRect();
                                selectedSprite->setColor(sf::Color(100, 255, 100));
                            }
                        }


                        //Sprite Scale
                        /*if (cursor.getPressed("Left") && selectedSprite != nullptr)
                        {
                            selectedSprite->setZDepth(selectedSprite->getZDepth() + 1);
                            world.reorganizeLayers();
                        }*/
                        //Sprite Move
                        if (cursor.getPressed(System::MouseButton::Left) && selectedSprite != nullptr && selectedHandlePoint == nullptr)
                        {
                            if (selectedSprite->getParentId().empty())
                            {
                                selectedSprite->setPosition(Transform::UnitVector(cursor.getX() + pixelCamera.x - selectedSpriteOffsetX,
                                                                                  cursor.getY() + pixelCamera.y - selectedSpriteOffsetY, Transform::Units::WorldPixels));
                            }
                            else
                            {
                                std::cout << "Not empty : '" << selectedSprite->getParentId() << "'" << std::endl;
                                // What to do here ?
                            }
                            sdBoundingRect = selectedSprite->getRect();
                            std::string sprInfoStr;
                            sprInfoStr = "Hovered Sprite : \n";
                            sprInfoStr += "    ID : " + selectedSprite->getId() + "\n";
                            sprInfoStr += "    Name : " + selectedSprite->getPath() + "\n";
                            sprInfoStr += "    Pos : " + std::to_string(selectedSprite->getX()) + "," + std::to_string(selectedSprite->getY()) + "\n";
                            sprInfoStr += "    Size : " + std::to_string(selectedSprite->getWidth()) + "," + std::to_string(selectedSprite->getHeight()) + "\n";
                            sprInfoStr += "    Rot : " + std::to_string(selectedSprite->getRotation()) + "\n";
                            sprInfoStr += "    Layer / Z : " + std::to_string(selectedSprite->getLayer()) + "," + std::to_string(selectedSprite->getZDepth()) + "\n";
                            sprInfo.setString(sprInfoStr);
                            sprInfoBackground.setSize(sf::Vector2f(sprInfo.getGlobalBounds().width + 20, sprInfo.getGlobalBounds().height - 10));
                            sprInfoBackground.setPosition(cursor.getX() + 40, cursor.getY());
                            sprInfo.setPosition(cursor.getX() + 50, cursor.getY());
                        }

                        //Sprite Rotate (Non-fonctionnal)
                        /*if ((keybind.isActionEnabled("RotateLeft") || keybind.isActionEnabled("RotateRight")) && selectedSprite != nullptr)
                        {
                            if (keybind.isActionEnabled("RotateLeft") && selectedSprite != nullptr)
                            {
                                //selectedSprite->rotate(-1 * framerateManager.getGameSpeed());
                                selectedSprite->scale(2 * framerateManager.getGameSpeed(), 2 * framerateManager.getGameSpeed());
                            }
                                
                            if (keybind.isActionEnabled("RotateRight") && selectedSprite != nullptr)
                            {
                                //selectedSprite->rotate(1 * framerateManager.getGameSpeed());
                                selectedSprite->scale(-2 * framerateManager.getGameSpeed(), -2 * framerateManager.getGameSpeed());
                            }
                        }*/

                        /*if ((keybind.isActionEnabled("ScaleInc") || keybind.isActionEnabled("ScaleDec")) && selectedSprite != nullptr)
                        {
                            if (keybind.isActionEnabled("ScaleDec"))
                                selectedSprite->scale(-0.05 * framerateManager.getGameSpeed() * selectedSprite->getScaleX(), -0.05 * framerateManager.getGameSpeed() * selectedSprite->getScaleY());
                            if (keybind.isActionEnabled("ScaleInc"))
                                selectedSprite->scale(0.05 * framerateManager.getGameSpeed() * selectedSprite->getScaleX(), 0.05 * framerateManager.getGameSpeed() * selectedSprite->getScaleY());
                        }*/

                        //Sprite Layer / Z-Depth
                        /*if (cursor.getPressed(System::MouseButton::Left) && selectedSprite != nullptr && keybind.isActionToggled("ZInc"))
                        {
                            selectedSprite->setZDepth(selectedSprite->getZDepth() + 1);
                            world.reorganizeLayers();
                        }
                        if (cursor.getPressed(System::MouseButton::Left) && selectedSprite != nullptr && keybind.isActionToggled("ZDec"))
                        {
                            selectedSprite->setZDepth(selectedSprite->getZDepth() - 1);
                            world.reorganizeLayers();
                        }
                        if (cursor.getPressed(System::MouseButton::Left) && selectedSprite != nullptr && keybind.isActionToggled("LayerInc"))
                        {
                            selectedSprite->setLayer(selectedSprite->getLayer() + 1);
                            currentLayer += 1;
                            world.reorganizeLayers();
                        }
                        if (cursor.getPressed(System::MouseButton::Left) && selectedSprite != nullptr && keybind.isActionToggled("LayerDec"))
                        {
                            selectedSprite->setLayer(selectedSprite->getLayer() - 1);
                            currentLayer -= 1;
                            world.reorganizeLayers();
                        }*/
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
                    bool deletedCollision = false;
                    world.enableShowCollision(true, true, true, true);
                    if (selectedMasterCollider != nullptr)
                    {
                        selectedMasterCollider->clearHighlights();
                        selectedMasterCollider->highlightLine(selectedMasterCollider->findClosestLine(cursCoord));
                    }
                    //Collision Point Grab
                    if (cursor.getClicked(System::MouseButton::Left) && colliderPtGrabbed == -1 &&
                        world.getCollisionPointByPos(cursor.getX() + pixelCamera.x,
                                                     cursor.getY() + pixelCamera.y).first != nullptr)
                    {
                        std::pair<Collision::PolygonalCollider*, int> selectedPtCollider;
                        selectedPtCollider = world.getCollisionPointByPos(cursor.getX() + pixelCamera.x,
                                                                          cursor.getY() + pixelCamera.y);
                        if (selectedMasterCollider != nullptr && selectedMasterCollider != selectedPtCollider.first)
                        {
                            selectedMasterCollider->setSelected(false);
                            selectedMasterCollider = nullptr;
                            masterColliderGrabbed = false;
                            colliderPtGrabbed = -1;
                        }
                        selectedMasterCollider = selectedPtCollider.first;
                        selectedMasterCollider->setSelected(true);
                        colliderPtGrabbed = selectedPtCollider.second;
                    }
                    //Collision Point Move
                    if (cursor.getPressed(System::MouseButton::Left) && selectedMasterCollider != nullptr && !masterColliderGrabbed && colliderPtGrabbed != -1)
                    {
                        selectedMasterCollider->setPointPosition(colliderPtGrabbed, cursCoord);
                        if (colliderPtGrabbed == 0 && selectedMasterCollider->getParentId() != "" && world.getGameObject(selectedMasterCollider->getParentId())->canDisplay())
                        {
                            world.getGameObject(selectedMasterCollider->getParentId())->getLevelSprite()->setPosition(
                                cursor.getX() + pixelCamera.x,
                                cursor.getY() + pixelCamera.y);
                        }
                    }
                    //Collision Point Release
                    if (cursor.getReleased(System::MouseButton::Left))
                    {
                        colliderPtGrabbed = -1;
                    }
                    //Collision Master Grab
                    if (cursor.getClicked(System::MouseButton::Left) && world.getCollisionMasterByPos(cursor.getX() + pixelCamera.x,
                                                                                                      cursor.getY() + pixelCamera.y) != nullptr)
                    {
                        Collision::PolygonalCollider* tempCol = world.getCollisionMasterByPos(cursor.getX() + pixelCamera.x,
                                                                                              cursor.getY() + pixelCamera.y);
                        if (selectedMasterCollider != nullptr && selectedMasterCollider != tempCol)
                        {
                            selectedMasterCollider->setSelected(false);
                            selectedMasterCollider = nullptr;
                            masterColliderGrabbed = false;
                            colliderPtGrabbed = -1;
                        }
                        selectedMasterCollider = tempCol;
                        selectedMasterCollider->setSelected(true);
                        if (selectedMasterCollider->getParentId() != "") world.getGameObject(selectedMasterCollider->getParentId())->setUpdateState(false);
                        masterColliderGrabbed = true;
                    }
                    //Collision Master Move
                    if (cursor.getPressed(System::MouseButton::Left) && selectedMasterCollider != nullptr && masterColliderGrabbed)
                    {
                        selectedMasterCollider->setPositionFromMaster(cursCoord);
                        if (selectedMasterCollider->getParentId() != "" && world.getGameObject(selectedMasterCollider->getParentId())->canDisplay())
                        {
                            Transform::UnitVector zeroCoords = selectedMasterCollider->getPointPosition(0).to<Transform::Units::WorldPixels>();
                            Transform::UnitVector masterCoords = selectedMasterCollider->getMasterPointPosition().to<Transform::Units::WorldPixels>();
                            world.getGameObject(selectedMasterCollider->getParentId())->getLevelSprite()->setPosition(
                                cursor.getX() + pixelCamera.x + zeroCoords.x - masterCoords.x,
                                cursor.getY() + pixelCamera.y + zeroCoords.y - masterCoords.y);
                        }
                    }
                    //Collision Master Release
                    if (cursor.getReleased(System::MouseButton::Left) && masterColliderGrabbed)
                    {
                        masterColliderGrabbed = false;
                        if (selectedMasterCollider->getParentId() != "") world.getGameObject(selectedMasterCollider->getParentId())->setUpdateState(true);
                    }
                    if (cursor.getClicked(System::MouseButton::Right) && selectedMasterCollider != nullptr && !masterColliderGrabbed)
                    {
                        const Transform::UnitVector pTolerance = Transform::UnitVector(6, 6, Transform::Units::WorldPixels);
                        int rqPtRes = selectedMasterCollider->hasPoint(cursCoord, pTolerance);
                        //Collision Point Create
                        if (rqPtRes == -1)
                        {
                            selectedMasterCollider->addPoint(cursCoord, selectedMasterCollider->findClosestLine(cursCoord));
                        }
                        //Collision Point Delete
                        else
                        {
                            selectedMasterCollider->deletePoint(rqPtRes);
                            if (selectedMasterCollider->getPointsAmount() <= 2)
                            {
                                selectedMasterCollider->setSelected(false);
                                world.deleteCollisionByID(selectedMasterCollider->getId());
                                selectedMasterCollider = nullptr;
                                masterColliderGrabbed = false;
                                colliderPtGrabbed = -1;
                                deletedCollision = true;
                            }
                        }
                    }
                    //Collision Release
                    if (cursor.getClicked(System::MouseButton::Left) && selectedMasterCollider != nullptr)
                    {
                        if (world.getCollisionMasterByPos(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y) == nullptr)
                        {
                            if (world.getCollisionPointByPos(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y).first == nullptr)
                            {
                                selectedMasterCollider->setSelected(false);
                                selectedMasterCollider = nullptr;
                                masterColliderGrabbed = false;
                                colliderPtGrabbed = -1;
                            }
                        }
                    }
                    //Collision Delete
                    if (cursor.getClicked(System::MouseButton::Right) && selectedMasterCollider != nullptr && masterColliderGrabbed)
                    {
                        selectedMasterCollider->setSelected(false);
                        world.deleteCollisionByID(selectedMasterCollider->getId());
                        selectedMasterCollider = nullptr;
                        masterColliderGrabbed = false;
                        colliderPtGrabbed = -1;
                        deletedCollision = true;
                    }
                    //Collision Create
                    if (cursor.getClicked(System::MouseButton::Right) && selectedMasterCollider == nullptr && !deletedCollision)
                    {
                        world.createCollisionAtPos(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y);
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
                Triggers::TriggerDatabase::GetInstance()->update();
                world.update(framerateManager.getGameSpeed());
                keybind.update();
                cursor.update();
                if (drawFPS) fps.uTick();
                if (drawFPS && framerateManager.doRender()) fps.tick();

                //Triggers Handling
                networkHandler.handleTriggers();
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
                        if (event.key.code == sf::Keyboard::S)
                        {
                            if (event.key.control)
                            {
                                world.saveData()->writeFile(world.getBaseFolder() + "/Data/Maps/" + mapName, true);
                                if (waitForMapSaving < 0)
                                {
                                    savedLabel->showWithEffect(tgui::ShowAnimationType::SlideFromTop, sf::Time(sf::seconds(0.5)));
                                    waitForMapSaving = 0;
                                }
                            }
                        }
                        if (event.key.code == sf::Keyboard::V)
                        {
                            if (event.key.control)
                            {
                                std::string clipboard_content = "";
                                gameConsole.insertInputBufferContent(clipboard_content);
                            }
                        }
                        if (event.key.code == sf::Keyboard::F1)
                            gameConsole.setConsoleVisibility(!gameConsole.isConsoleVisible());
                        if (event.key.code == sf::Keyboard::Up)
                            gameConsole.upHistory();
                        if (event.key.code == sf::Keyboard::Down)
                            gameConsole.downHistory();
                        if (event.key.code == sf::Keyboard::Left && gameConsole.isConsoleVisible())
                            gameConsole.moveCursor(-1);
                        if (event.key.code == sf::Keyboard::Right && gameConsole.isConsoleVisible())
                            gameConsole.moveCursor(1);
                        break;
                    case sf::Event::TextEntered:
                        if (gameConsole.isConsoleVisible())
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
                    world.display(window);
                    pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>(); // Do it once (Grid Draw Offset) <REVISION>
                    //Show Collision
                    if (editMode->getSelectedItem() == "Collisions")
                        world.enableShowCollision(true);
                    else
                        world.enableShowCollision(false);
                    //Game Display
                    if (hoveredSprite != nullptr)
                    {
                        sf::RectangleShape sprBorder = sf::RectangleShape(sf::Vector2f(sdBoundingRect.width, sdBoundingRect.height));
                        sprBorder.setPosition(sdBoundingRect.left - pixelCamera.x, sdBoundingRect.top - pixelCamera.y);
                        sprBorder.setFillColor(sf::Color(0, 0, 0, 0));
                        sprBorder.setOutlineColor(sf::Color(255, 0, 0));
                        sprBorder.setOutlineThickness(2);
                        window.draw(sprBorder);
                    }
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
                    if (gameConsole.isConsoleVisible())
                        gameConsole.display(window);

                    //Cursor
                    if (showCursor)
                        cursor.display(window);

                    window.display();
                }
            }
            window.close();
        }
    }
}
