#include <TGUI/TGUI.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Config/Config.hpp>
#include <Debug/Console.hpp>
#include <Editor/CollidersEditActions.hpp>
#include <Editor/EditorGUI.hpp>
#include <Editor/EditorGlobalActions.hpp>
#include <Editor/EditorTooltip.hpp>
#include <Editor/Grid.hpp>
#include <Editor/MapEditor.hpp>
#include <Editor/SceneNodeEditActions.hpp>
#include <Editor/SpriteEditActions.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Input/InputManager.hpp>
#include <Input/KeyList.hpp>
#include <Network/NetworkHandler.hpp>
#include <Scene/Scene.hpp>
#include <Script/GlobalState.hpp>
#include <System/Cursor.hpp>
#include <System/Loaders.hpp>
#include <System/Window.hpp>
#include <Time/FramerateCounter.hpp>
#include <Time/FramerateManager.hpp>
#include <Transform/UnitVector.hpp>
#include <Triggers/TriggerDatabase.hpp>

namespace obe::Editor
{
    void editMap(const std::string& mapName)
    {
        // Creating Window
        System::MainWindow.init(System::WindowContext::EditorWindow);

        // Editor Triggers
        Triggers::TriggerGroupPtr editorTriggers(
            Triggers::TriggerDatabase::GetInstance().createTriggerGroup("Global", "Editor"),
            Triggers::TriggerGroupPtrRemover);

        // Editor Collider Triggers
        editorTriggers->addTrigger("ColliderCreated")
            ->addTrigger("ColliderRemoved")
            ->addTrigger("ColliderPicked")
            ->addTrigger("ColliderMoved")
            ->addTrigger("ColliderReleased")
            ->addTrigger("ColliderPointCreated")
            ->addTrigger("ColliderPointRemoved")
            ->addTrigger("ColliderPointPicked")
            ->addTrigger("ColliderPointMoved")
            ->addTrigger("ColliderPointReleased");
        // Editor Various Triggers
        editorTriggers->addTrigger("CameraMoved")
            ->addTrigger("GridCursorMoved")
            ->addTrigger("CursorMagnetized")
            ->addTrigger("GridToggled")
            ->addTrigger("GridSnapToggled")
            ->addTrigger("EditModeChanged")
            ->addTrigger("SceneSaved");
        // Editor Sprite Triggers
        editorTriggers->addTrigger("SpriteZDepthChanged")
            ->addTrigger("SpriteLayerChanged")
            ->addTrigger("SpriteHandlePointPicked")
            ->addTrigger("SpriteHandlePointMoved")
            ->addTrigger("SpriteHandlePointReleased")
            ->addTrigger("SpriteCreated")
            ->addTrigger("SpriteSelect")
            ->addTrigger("SpriteMoved")
            ->addTrigger("SpriteUnselect")
            ->addTrigger("SpriteRemoved");
        // SceneNode Triggers
        editorTriggers->addTrigger("SceneNodePicked")
            ->addTrigger("SceneNodeMoved")
            ->addTrigger("SceneNodeReleased");

        // Game Triggers
        Triggers::TriggerGroupPtr gameTriggers(
            Triggers::TriggerDatabase::GetInstance().createTriggerGroup("Global", "Game"),
            Triggers::TriggerGroupPtrRemover);
        gameTriggers->addTrigger("Start")
            ->trigger("Start")
            ->addTrigger("End")
            ->addTrigger("Update")
            ->addTrigger("Render");

        // Console
        Debug::Console gameConsole;
        bool oldConsoleVisibility = false;
        std::vector<std::string> backupContexts;

        // Font
        sf::Font font;
        System::Path("Data/Fonts/arial.ttf").load(System::Loaders::fontLoader, font);

        // Config
        vili::ComplexNode& gameConfig = Config::Config->at("GameConfig");
        const int scrollSensitive = gameConfig.at<vili::DataNode>("scrollSensibility");

        // Cursor
        System::Cursor cursor;

        // Scene Creation / Loading
        Scene::Scene scene;
        vili::ComplexNode sceneClipboard("Clipboard");
        // scene.getCamera()->bindView(window);
        Script::ScriptEngine["stream"] = gameConsole.createStream("Scene", true);
        Script::ScriptEngine.setErrorHandler([&gameConsole](int statuscode, const char* message) {
            gameConsole.pushMessage(
                "LuaError", std::string("<Main> :: ") + message, sf::Color::Red);
            Debug::Log->error("<LuaError>({0}) : {1}", statuscode, message);
        });

        // Socket
        Network::NetworkHandler networkHandler;

        // Keybinding
        Input::InputManager inputManager;
        inputManager.configure(Config::Config.at("KeyBinding"));
        inputManager.addContext("game").addContext("mapEditor").addContext("gameConsole");

        // Editor Grid
        EditorGrid editorGrid(32, 32);
        inputManager.getAction("MagnetizeUp").setRepeat(200);
        inputManager.getAction("MagnetizeDown").setRepeat(200);
        inputManager.getAction("MagnetizeLeft").setRepeat(200);
        inputManager.getAction("MagnetizeRight").setRepeat(200);

        // GUI
        sf::Event event;
        tgui::Gui gui(System::MainWindow.getTarget());
        gui.setFont("Data/Fonts/weblysleekuil.ttf");
        tgui::Panel::Ptr mainPanel = tgui::Panel::create();
        GUI::init();
        int saveEditMode = -1;
        gui.add(mainPanel);
        mainPanel->setSize("100%", "100%");

        GUI::buildEditorMenu(mainPanel);
        GUI::buildObjectCreationMenu(mainPanel);

        tgui::Panel::Ptr editorPanel = gui.get<tgui::Panel>("editorPanel");
        tgui::Panel::Ptr mapPanel = gui.get<tgui::Panel>("mapPanel");
        tgui::Panel::Ptr settingsPanel = gui.get<tgui::Panel>("settingsPanel");
        tgui::Panel::Ptr spritesPanel = gui.get<tgui::Panel>("spritesPanel");
        tgui::Panel::Ptr objectsPanel = gui.get<tgui::Panel>("objectsPanel");
        tgui::Panel::Ptr requiresPanel = gui.get<tgui::Panel>("requiresPanel");
        tgui::Scrollbar::Ptr spritesScrollbar = gui.get<tgui::Scrollbar>("spritesScrollbar");
        tgui::Scrollbar::Ptr objectsScrollbar = gui.get<tgui::Scrollbar>("objectsScrollbar");

        GUI::buildToolbar(mainPanel, editorPanel, scene);

        tgui::ComboBox::Ptr editMode = gui.get<tgui::ComboBox>("editMode");

        GUI::buildEditorMapMenu(mapPanel, scene);
        GUI::buildEditorSettingsMenu(settingsPanel, editorGrid, cursor, editMode, scene);
        GUI::buildEditorSpritesMenu(spritesPanel, spritesScrollbar, scene);
        GUI::buildEditorObjectsMenu(objectsPanel, requiresPanel, objectsScrollbar, scene);

        tgui::EditBox::Ptr cameraSizeInput = gui.get<tgui::EditBox>("cameraSizeInput");
        tgui::EditBox::Ptr cameraPositionXInput = gui.get<tgui::EditBox>("cameraPositionXInput");
        tgui::EditBox::Ptr cameraPositionYInput = gui.get<tgui::EditBox>("cameraPositionYInput");

        tgui::CheckBox::Ptr enableGridCheckbox = gui.get<tgui::CheckBox>("enableGridCheckbox");
        tgui::CheckBox::Ptr snapGridCheckbox = gui.get<tgui::CheckBox>("snapGridCheckbox");
        tgui::EditBox::Ptr mapNameInput = gui.get<tgui::EditBox>("mapNameInput");
        tgui::Label::Ptr savedLabel = gui.get<tgui::Label>("savedLabel");
        tgui::Label::Ptr infoLabel = gui.get<tgui::Label>("infoLabel");
        const tgui::CheckBox::Ptr displayFramerateCheckbox
            = gui.get<tgui::CheckBox>("displayFramerateCheckbox");
        const tgui::CheckBox::Ptr saveCameraPositionCheckbox
            = gui.get<tgui::CheckBox>("saveCameraPositionCheckbox");

        // Map Editor
        Graphics::LevelSprite* hoveredSprite = nullptr;
        Graphics::LevelSprite* selectedSprite = nullptr;
        Graphics::LevelSpriteHandlePoint* selectedHandlePoint = nullptr;
        Scene::SceneNode* sceneNodeGrabbed = nullptr;
        int selectedSpriteOffsetX = 0;
        int selectedSpriteOffsetY = 0;
        int cameraSpeed = Transform::UnitVector::Screen.h;
        int currentLayer = 1;
        Collision::PolygonalCollider* selectedMasterCollider = nullptr;
        int colliderPtGrabbed = -1;
        bool masterColliderGrabbed = false;
        Tooltip tooltip;
        double waitForMapSaving = -1;
        double saveCamPosX = 0;
        double saveCamPosY = 0;
        Transform::Units editorUnit = Transform::Units::SceneUnits;

        // Framerate / DeltaTime
        Time::FPSCounter fps;
        fps.loadFont(font);
        Time::FramerateManager framerateManager(gameConfig);

        scene.loadFromFile(mapName);

        mapNameInput->setText(scene.getLevelName());
        cameraSizeInput->setText(std::to_string(scene.getCamera()->getSize().y / 2));

        // Connect InputManager Actions
        connectSaveActions(editorTriggers.get(), inputManager, mapName, scene, waitForMapSaving,
            savedLabel, saveCameraPositionCheckbox);
        connectCamMovementActions(
            editorTriggers.get(), inputManager, scene, cameraSpeed, framerateManager);
        connectGridActions(editorTriggers.get(), inputManager, enableGridCheckbox, snapGridCheckbox,
            cursor, editorGrid);
        connectMenuActions(inputManager, editMode, editorPanel);
        connectSpriteLayerActions(
            editorTriggers.get(), inputManager, selectedSprite, scene, currentLayer);
        connectSpriteActions(editorTriggers.get(), inputManager, hoveredSprite, selectedSprite,
            selectedHandlePoint, scene, cursor, editorGrid, selectedSpriteOffsetX,
            selectedSpriteOffsetY, tooltip, editorUnit);
        connectCollidersActions(editorTriggers.get(), inputManager, scene, cursor,
            colliderPtGrabbed, selectedMasterCollider, masterColliderGrabbed);
        connectSceneNodeActions(
            editorTriggers.get(), inputManager, scene, cursor, sceneNodeGrabbed);
        connectGameConsoleActions(inputManager, gameConsole);
        connectCopyPasteActions(editorTriggers.get(), inputManager, scene, sceneClipboard,
            savedLabel, selectedMasterCollider, selectedSprite);
        inputManager.getAction("ExitEditor").connect([](const Input::InputActionEvent& event) {
            System::MainWindow.close();
        });

        auto editModeCallback = [&editorTriggers, &inputManager, editMode]() {
            editorTriggers->pushParameter("EditModeChanged", "mode", editMode->getSelectedItem());
            editorTriggers->trigger("EditModeChanged");
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
            if (editMode->getSelectedItem() == "SceneNodes")
            {
                inputManager.addContext("sceneNodeEditing");
            }
            else
            {
                inputManager.removeContext("sceneNodeEditing");
            }
        };

        editMode->connect("itemselected", editModeCallback);

        GUI::calculateFontSize();
        GUI::applyFontSize(mainPanel);

        System::Path("Lib/Internal/GameInit.lua")
            .load(System::Loaders::luaLoader, Script::ScriptEngine);
        System::Path("boot.lua").load(System::Loaders::luaLoader, Script::ScriptEngine, true);
        Script::ScriptEngine.dostring("Editor.Start()");

        // scene.setUpdateState(false);

        // Game Starts
        while (System::MainWindow.isOpen())
        {
            framerateManager.update();

            gameTriggers->pushParameter("Update", "dt", framerateManager.getGameSpeed());
            gameTriggers->trigger("Update");

            if (framerateManager.doRender())
                gameTriggers->trigger("Render");

            if (waitForMapSaving >= 0)
            {
                waitForMapSaving += framerateManager.getDeltaTime();
                if (waitForMapSaving > 1 && waitForMapSaving < 2)
                {
                    savedLabel->hideWithEffect(
                        tgui::ShowAnimationType::SlideFromTop, sf::Time(sf::seconds(0.5)));
                    waitForMapSaving = 2;
                }
                else if (waitForMapSaving > 3)
                    waitForMapSaving = -1;
            }

            const bool drawFPS = displayFramerateCheckbox->isChecked();

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

            Transform::UnitVector pixelCamera
                = scene.getCamera()->getPosition().to<Transform::Units::ScenePixels>();
            // Updates

            if (oldConsoleVisibility != gameConsole.isVisible())
            {
                if (oldConsoleVisibility)
                {
                    inputManager.clearContexts();
                    for (std::string& context : backupContexts)
                    {
                        inputManager.addContext(context);
                    }
                    backupContexts.clear();
                }
                else
                {
                    backupContexts = inputManager.getContexts();
                    inputManager.setContext("gameConsole");
                }
                oldConsoleVisibility = gameConsole.isVisible();
            }

            // Sprite Editing
            if (editMode->getSelectedItem() == "LevelSprites")
            {
                scene.enableShowSceneNodes(true);
                scene.enableShowCollision(true, true, false, false);

                if (hoveredSprite == nullptr)
                {
                    hoveredSprite = scene.getLevelSpriteByPosition(
                        cursor.getPosition(), -pixelCamera, currentLayer);
                    if (hoveredSprite != nullptr && hoveredSprite != selectedSprite)
                    {
                        hoveredSprite = scene.getLevelSpriteByPosition(
                            cursor.getPosition(), -pixelCamera, currentLayer);
                        hoveredSprite->setColor(sf::Color(0, 255, 255));

                        tooltip.setText("Hovered Sprite : \n"
                                        "   Id : {}\n"
                                        "   Name : {}\n"
                                        "   Pos : {}, {}\n"
                                        "   Size : {}, {}\n"
                                        "   Rot : {}\n"
                                        "   Layer / Z : {}, {}",
                            hoveredSprite->getId(), hoveredSprite->getPath(),
                            hoveredSprite->getPosition().to(editorUnit).x,
                            hoveredSprite->getPosition().to(editorUnit).y,
                            hoveredSprite->getSize().to(editorUnit).x,
                            hoveredSprite->getSize().to(editorUnit).y, hoveredSprite->getRotation(),
                            hoveredSprite->getLayer(), hoveredSprite->getZDepth());
                    }
                    else
                        hoveredSprite = nullptr;
                }
                else if (hoveredSprite != nullptr)
                {
                    tooltip.setPosition(cursor.getX() + 40, cursor.getY());
                    bool outHover = false;
                    Graphics::LevelSprite* testHoverSprite = scene.getLevelSpriteByPosition(
                        cursor.getPosition(), -pixelCamera, currentLayer);
                    if (testHoverSprite != hoveredSprite)
                        outHover = true;
                    if (outHover)
                    {
                        if (hoveredSprite != selectedSprite)
                            hoveredSprite->setColor(sf::Color::White);
                        hoveredSprite = nullptr;
                        tooltip.clear();
                    }
                }
            }
            else
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setColor(sf::Color::White);
                    selectedSprite->setSelected(false);
                }
                if (hoveredSprite != nullptr)
                {
                    hoveredSprite->setColor(sf::Color::White);
                }
                selectedSprite = nullptr;
                hoveredSprite = nullptr;
                selectedSpriteOffsetX = 0;
                selectedSpriteOffsetY = 0;
                tooltip.clear();
            }

            // Collision Edition
            if (editMode->getSelectedItem() == "Collisions")
            {
                const Transform::UnitVector cursCoord(cursor.getConstrainedX() + pixelCamera.x,
                    cursor.getConstrainedY() + pixelCamera.y);

                scene.enableShowSceneNodes(true);
                scene.enableShowCollision(true, true, true, true);
                if (selectedMasterCollider != nullptr)
                {
                    selectedMasterCollider->clearHighlights();
                    selectedMasterCollider->highlightLine(
                        selectedMasterCollider->findClosestSegment(cursCoord).first.index);
                }
                if (Collision::PolygonalCollider* col
                    = scene.getColliderByCentroidPosition(cursor.getPosition() + pixelCamera);
                    col != nullptr)
                {
                    tooltip.setText("Hovered Collider : \n"
                                    "   Id : {}\n"
                                    "   Pos : {}, {}\n",
                        col->getId(), col->getPosition().to(editorUnit).x,
                        col->getPosition().to(editorUnit).y);
                    tooltip.setPosition(cursor.getX() + 40, cursor.getY());
                }
            }

            if (editMode->getSelectedItem() == "SceneNodes")
            {
                const Transform::UnitVector cursCoord(cursor.getConstrainedX() + pixelCamera.x,
                    cursor.getConstrainedY() + pixelCamera.y);

                scene.enableShowCollision(true, true, false, false);
                scene.enableShowSceneNodes(true);
                if (auto sceneNode
                    = scene.getSceneNodeByPosition(cursor.getPosition() + pixelCamera))
                {
                    tooltip.setText("Hovered SceneNode : \n"
                                    "   Pos : {}, {}\n",
                        sceneNode->getPosition().to(editorUnit).x,
                        sceneNode->getPosition().to(editorUnit).y);
                    tooltip.setPosition(cursor.getX() + 40, cursor.getY());
                }
            }

            // GUI Update
            infoLabel->setText("Cursor : (" + std::to_string(cursor.getX()) + ", "
                + std::to_string(cursor.getY()) + ")" + std::string("   Camera : (")
                + std::to_string(int(scene.getCamera()
                                         ->getPosition(Transform::Referential::TopLeft)
                                         .to<Transform::Units::ScenePixels>()
                                         .x))
                + ", "
                + std::to_string(int(scene.getCamera()
                                         ->getPosition(Transform::Referential::TopLeft)
                                         .to<Transform::Units::ScenePixels>()
                                         .y))
                + ")" + std::string("   Sum : (")
                + std::to_string(int(scene.getCamera()
                                         ->getPosition(Transform::Referential::TopLeft)
                                         .to<Transform::Units::ScenePixels>()
                                         .x)
                      + int(cursor.getX()))
                + ", "
                + std::to_string(int(scene.getCamera()
                                         ->getPosition(Transform::Referential::TopLeft)
                                         .to<Transform::Units::ScenePixels>()
                                         .y)
                      + int(cursor.getY()))
                + ")" + std::string("   Layer : ") + std::to_string(currentLayer));

            while (System::MainWindow.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    System::MainWindow.close();
                    break;
                case sf::Event::Resized:
                    Transform::UnitVector::Screen.w = event.size.width;
                    Transform::UnitVector::Screen.h = event.size.height;
                    System::MainWindow.setView(
                        sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                    gui.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                    GUI::calculateFontSize();
                    GUI::applyFontSize(mainPanel);
                    GUI::applyScrollbarMaxValue(mainPanel);
                    break;
                case sf::Event::JoystickConnected:
                    Input::SetGamepadList();
                    break;
                case sf::Event::JoystickDisconnected:
                    Input::SetGamepadList();
                    break;
                case sf::Event::TextEntered:
                    if (gameConsole.isVisible())
                        gameConsole.inputKey(event.text.unicode);
                    break;
                case sf::Event::GainedFocus:
                    inputManager.setEnabled(true);
                    break;
                case sf::Event::LostFocus:
                    inputManager.setEnabled(false);
                    break;
                case sf::Event::MouseWheelMoved:
                    if (event.mouseWheel.delta >= scrollSensitive)
                    {
                        scene.getCamera()->scale(0.9,
                            Transform::Referential(
                                double(cursor.getX()) / double(System::MainWindow.getSize().x),
                                double(cursor.getY()) / double(System::MainWindow.getSize().y)));
                        gameConsole.scroll(-1);
                    }
                    else if (event.mouseWheel.delta <= -scrollSensitive)
                    {
                        scene.getCamera()->scale(1.1,
                            Transform::Referential(
                                double(cursor.getX()) / double(System::MainWindow.getSize().x),
                                double(cursor.getY()) / double(System::MainWindow.getSize().y)));
                        gameConsole.scroll(1);
                    }
                    cameraSizeInput->setText(std::to_string(scene.getCamera()->getSize().y / 2));
                    break;
                case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                case sf::Event::JoystickButtonPressed:
                case sf::Event::JoystickButtonReleased:
                case sf::Event::JoystickMoved:
                case sf::Event::KeyReleased:
                case sf::Event::KeyPressed:
                    Input::Monitors::RequireRefresh = true;
                    break;
                default:;
                }
                gui.handleEvent(event);
            }

            // Events
            scene.update();
            Triggers::TriggerDatabase::GetInstance().update();
            inputManager.update();
            if (Input::Monitors::RequireRefresh)
                Input::Monitors::UpdateMonitors();
            cursor.update();
            if (drawFPS)
                fps.uTick();
            if (drawFPS && framerateManager.doRender())
                fps.tick();

            // Triggers Handling
            networkHandler.handleTriggers();

            // Draw Everything Here
            if (framerateManager.doRender())
            {
                if (saveCamPosX != scene.getCamera()->getPosition(Transform::Referential::TopLeft).x
                    || saveCamPosY
                        != scene.getCamera()->getPosition(Transform::Referential::TopLeft).y)
                {
                    saveCamPosX = scene.getCamera()->getPosition(Transform::Referential::TopLeft).x;
                    saveCamPosY = scene.getCamera()->getPosition(Transform::Referential::TopLeft).y;
                    cameraPositionXInput->setText(std::to_string(saveCamPosX));
                    cameraPositionYInput->setText(std::to_string(saveCamPosY));
                }

                System::MainWindow.clear(Graphics::Utils::ClearColor);
                scene.draw();
                if (selectedHandlePoint != nullptr)
                    Graphics::Utils::drawPoint(selectedHandlePoint->m_dp.x,
                        selectedHandlePoint->m_dp.y, 3, sf::Color::Magenta);
                pixelCamera = scene.getCamera()
                                  ->getPosition()
                                  .to<Transform::Units::ScenePixels>(); // Do it once
                                                                        // (Grid Draw
                                                                        // Offset)
                                                                        // <REVISION>

                if (editorGrid.isEnabled())
                    editorGrid.draw(cursor, pixelCamera.x, pixelCamera.y);
                // HUD & GUI
                if (!tooltip.empty())
                {
                    tooltip.draw();
                }
                gui.draw();
                if (drawFPS)
                    fps.draw();

                // Console
                if (gameConsole.isVisible())
                    gameConsole.draw();

                System::MainWindow.display();
            }
        }
        gameTriggers->trigger("End");
        Triggers::TriggerDatabase::GetInstance().update();
        scene.update();
        scene.clear();
        System::MainWindow.close();
        gui.removeAllWidgets();
        Script::GameObjectDatabase::Clear();
    }
} // namespace obe::Editor
