#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <TGUI/Animation.hpp>

#include <Editor/EditorGlobalActions.hpp>

namespace obe::Editor
{
    void connectCamMovementActions(Triggers::TriggerGroup* editorTriggers,
        Input::InputManager& inputManager, Scene::Scene& world, int& cameraSpeed,
        Time::FramerateManager& framerateManager)
    {
        inputManager.getAction("CamLeft").connect(
            [editorTriggers, &world, &cameraSpeed, &framerateManager](
                const Input::InputActionEvent& event) {
                Transform::UnitVector moveVec(-cameraSpeed * framerateManager.getGameSpeed(), 0,
                    Transform::Units::ScenePixels);
                world.getCamera()->move(moveVec);
                editorTriggers->pushParameter("CameraMoved", "direction", "Left");
                editorTriggers->pushParameter("CameraMoved", "move", moveVec);
                editorTriggers->pushParameter("CameraMoved", "camera", world.getCamera());
                editorTriggers->trigger("CameraMoved");
            });
        inputManager.getAction("CamRight")
            .connect([editorTriggers, &world, &cameraSpeed, &framerateManager](
                         const Input::InputActionEvent& event) {
                Transform::UnitVector moveVec(cameraSpeed * framerateManager.getGameSpeed(), 0,
                    Transform::Units::ScenePixels);
                world.getCamera()->move(moveVec);
                editorTriggers->pushParameter("CameraMoved", "direction", "Left");
                editorTriggers->pushParameter("CameraMoved", "move", moveVec);
                editorTriggers->pushParameter("CameraMoved", "camera", world.getCamera());
                editorTriggers->trigger("CameraMoved");
            });
        inputManager.getAction("CamUp").connect(
            [editorTriggers, &world, &cameraSpeed, &framerateManager](
                const Input::InputActionEvent& event) {
                Transform::UnitVector moveVec(0, -cameraSpeed * framerateManager.getGameSpeed(),
                    Transform::Units::ScenePixels);
                world.getCamera()->move(moveVec);
                editorTriggers->pushParameter("CameraMoved", "direction", "Left");
                editorTriggers->pushParameter("CameraMoved", "move", moveVec);
                editorTriggers->pushParameter("CameraMoved", "camera", world.getCamera());
                editorTriggers->trigger("CameraMoved");
            });
        inputManager.getAction("CamDown").connect(
            [editorTriggers, &world, &cameraSpeed, &framerateManager](
                const Input::InputActionEvent& event) {
                Transform::UnitVector moveVec(0, cameraSpeed * framerateManager.getGameSpeed(),
                    Transform::Units::ScenePixels);
                world.getCamera()->move(moveVec);
                editorTriggers->pushParameter("CameraMoved", "direction", "Left");
                editorTriggers->pushParameter("CameraMoved", "move", moveVec);
                editorTriggers->pushParameter("CameraMoved", "camera", world.getCamera());
                editorTriggers->trigger("CameraMoved");
            });
        inputManager.getAction("CamDash").connect(
            [&cameraSpeed](const Input::InputActionEvent& event) {
                cameraSpeed = Transform::UnitVector::Screen.h * 2.5;
            });
        inputManager.getAction("CamDash").connect(
            [&cameraSpeed](const Input::InputActionEvent& event) {
                cameraSpeed = Transform::UnitVector::Screen.h;
            });
        inputManager.getAction("ResetCameraSize")
            .connect(
                [&world](const Input::InputActionEvent& event) { world.getCamera()->setSize(1); });
    }

    void connectGridActions(Triggers::TriggerGroup* editorTriggers,
        Input::InputManager& inputManager, tgui::CheckBox::Ptr& enableGridCheckbox,
        tgui::CheckBox::Ptr& snapGridCheckbox, System::Cursor& cursor,
        Editor::EditorGrid& editorGrid)
    {
        inputManager.getAction("MagnetizeUp")
            .connect([editorTriggers, enableGridCheckbox, &cursor, &editorGrid](
                         const Input::InputActionEvent& event) {
                if (enableGridCheckbox->isChecked())
                {
                    editorGrid.moveMagnet(cursor, 0, -1);
                    editorTriggers->pushParameter("GridCursorMoved", "direction", "Up");
                    editorTriggers->pushParameter("GridCursorMoved", "grid", editorGrid);
                    editorTriggers->pushParameter("GridCursorMoved", "cursor", &cursor);
                    editorTriggers->trigger("GridCursorMoved");
                    editorTriggers->pushParameter("CursorMagnetized", "grid", editorGrid);
                    editorTriggers->pushParameter("CursorMagnetized", "cursor", &cursor);
                    editorTriggers->trigger("CursorMagnetized");
                }
            });
        inputManager.getAction("MagnetizeRight")
            .connect([editorTriggers, enableGridCheckbox, &cursor, &editorGrid](
                         const Input::InputActionEvent& event) {
                if (enableGridCheckbox->isChecked())
                {
                    editorGrid.moveMagnet(cursor, 1, 0);
                    editorTriggers->pushParameter("GridCursorMoved", "direction", "Right");
                    editorTriggers->pushParameter("GridCursorMoved", "grid", editorGrid);
                    editorTriggers->pushParameter("GridCursorMoved", "cursor", &cursor);
                    editorTriggers->trigger("GridCursorMoved");
                    editorTriggers->pushParameter("CursorMagnetized", "grid", editorGrid);
                    editorTriggers->pushParameter("CursorMagnetized", "cursor", &cursor);
                    editorTriggers->trigger("CursorMagnetized");
                }
            });
        inputManager.getAction("MagnetizeDown")
            .connect([editorTriggers, enableGridCheckbox, &cursor, &editorGrid](
                         const Input::InputActionEvent& event) {
                if (enableGridCheckbox->isChecked())
                {
                    editorGrid.moveMagnet(cursor, 0, 1);
                    editorTriggers->pushParameter("GridCursorMoved", "direction", "Down");
                    editorTriggers->pushParameter("GridCursorMoved", "grid", editorGrid);
                    editorTriggers->pushParameter("GridCursorMoved", "cursor", &cursor);
                    editorTriggers->trigger("GridCursorMoved");
                    editorTriggers->pushParameter("CursorMagnetized", "grid", editorGrid);
                    editorTriggers->pushParameter("CursorMagnetized", "cursor", &cursor);
                    editorTriggers->trigger("CursorMagnetized");
                }
            });
        inputManager.getAction("MagnetizeLeft")
            .connect([editorTriggers, enableGridCheckbox, &cursor, &editorGrid](
                         const Input::InputActionEvent& event) {
                if (enableGridCheckbox->isChecked())
                {
                    editorGrid.moveMagnet(cursor, -1, 0);
                    editorTriggers->pushParameter("GridCursorMoved", "direction", "Left");
                    editorTriggers->pushParameter("GridCursorMoved", "grid", editorGrid);
                    editorTriggers->pushParameter("GridCursorMoved", "cursor", &cursor);
                    editorTriggers->trigger("GridCursorMoved");
                    editorTriggers->pushParameter("CursorMagnetized", "grid", editorGrid);
                    editorTriggers->pushParameter("CursorMagnetized", "cursor", &cursor);
                    editorTriggers->trigger("CursorMagnetized");
                }
            });
        inputManager.getAction("MagnetizeCursor")
            .connect([editorTriggers, enableGridCheckbox, &cursor, &editorGrid](
                         const Input::InputActionEvent& event) {
                if (enableGridCheckbox->isChecked())
                {
                    editorGrid.magnetize(cursor);
                    editorTriggers->pushParameter("CursorMagnetized", "grid", editorGrid);
                    editorTriggers->pushParameter("CursorMagnetized", "cursor", &cursor);
                    editorTriggers->trigger("CursorMagnetized");
                }
            });
        inputManager.getAction("ToggleGrid")
            .connect([editorTriggers, &editorGrid, enableGridCheckbox](
                         const Input::InputActionEvent& event) {
                editorTriggers->pushParameter(
                    "GridToggled", "state", enableGridCheckbox->isChecked());
                editorTriggers->trigger("GridToggled");
                enableGridCheckbox->isChecked() ? enableGridCheckbox->uncheck()
                                                : enableGridCheckbox->check();
            });
        inputManager.getAction("ToggleGridSnap")
            .connect([editorTriggers, snapGridCheckbox](const Input::InputActionEvent& event) {
                if (snapGridCheckbox->isEnabled())
                {
                    editorTriggers->pushParameter(
                        "GridSnapToggled", "state", snapGridCheckbox->isChecked());
                    editorTriggers->trigger("GridSnapToggled");
                    if (snapGridCheckbox->isChecked())
                    {
                        snapGridCheckbox->uncheck();
                    }
                    else
                    {
                        snapGridCheckbox->check();
                    }
                }
            });
    }

    void connectMenuActions(Input::InputManager& inputManager, tgui::ComboBox::Ptr editMode,
        tgui::Panel::Ptr editorPanel)
    {
        inputManager.getAction("SpriteMode")
            .connect([editMode](const Input::InputActionEvent& event) {
                editMode->setSelectedItemByIndex(0);
            });
        inputManager.getAction("CollisionMode")
            .connect([editMode](const Input::InputActionEvent& event) {
                editMode->setSelectedItemByIndex(1);
            });
        inputManager.getAction("ToggleEditorMenu")
            .connect([editorPanel](const Input::InputActionEvent& event) {
                editorPanel->isVisible() ? editorPanel->hide() : editorPanel->show();
            });
    }

    void connectSaveActions(Triggers::TriggerGroup* editorTriggers,
        Input::InputManager& inputManager, const std::string& mapName, Scene::Scene& scene,
        double& waitForMapSaving, tgui::Label::Ptr savedLabel,
        tgui::CheckBox::Ptr saveCameraPositionCheckbox)
    {
        inputManager.getAction("Save").connect(
            [&mapName, &scene, &waitForMapSaving, savedLabel, saveCameraPositionCheckbox](
                const Input::InputActionEvent& event) {
                Debug::Log->info("<EditorGlobalActions> Saving Map '{0}'", mapName);
                vili::ViliParser* sceneDump = scene.dump(saveCameraPositionCheckbox->isChecked());
                sceneDump->writeFile(scene.getFilePath(), true);
                if (waitForMapSaving < 0)
                {
                    savedLabel->showWithEffect(
                        tgui::ShowAnimationType::SlideFromTop, sf::Time(sf::seconds(0.5)));
                    waitForMapSaving = 0;
                }
            });
    }

    void connectCopyPasteActions(Triggers::TriggerGroup* editorTriggers,
        Input::InputManager& inputManager, Scene::Scene& scene, vili::ComplexNode& sceneClipboard,
        tgui::Label::Ptr savedLabel, Collision::PolygonalCollider*& selectedMasterCollider,
        Graphics::LevelSprite*& selectedSprite)
    {
        inputManager.getAction("Copy").connect([&editorTriggers, &scene, &sceneClipboard,
                                                   savedLabel, &selectedMasterCollider,
                                                   &selectedSprite](
                                                   const Input::InputActionEvent& event) {
            Debug::Log->debug("<EditorGlobalActions> Copying Object");
            if (selectedMasterCollider)
            {
                sceneClipboard.clear();
                selectedMasterCollider->dump(sceneClipboard);
                sceneClipboard.at(selectedMasterCollider->getId())
                    .createDataNode("type", "Collider");
            }
            if (selectedSprite)
            {
                sceneClipboard.clear();
                selectedSprite->dump(sceneClipboard);
                sceneClipboard.at(selectedSprite->getId()).createDataNode("type", "LevelSprite");
            }
        });

        inputManager.getAction("Cut").connect([](const Input::InputActionEvent& event) {
            Debug::Log->debug("<EditorGlobalActions> Cutting Object");
        });

        inputManager.getAction("Paste").connect(
            [&sceneClipboard, &scene](const Input::InputActionEvent& event) {
                Debug::Log->debug("<EditorGlobalActions> Pasting Object");

                for (vili::ComplexNode* item : sceneClipboard.getAll<vili::ComplexNode>())
                {
                    if (item->at<vili::DataNode>("type").get<std::string>() == "Collider")
                    {
                        scene.createCollider()->load(*item);
                    }
                    else if (item->at<vili::DataNode>("type").get<std::string>() == "LevelSprite")
                    {
                        scene.createLevelSprite()->load(*item);
                    }
                }
            });
    }

    void connectGameConsoleActions(Input::InputManager& inputManager, Debug::Console& gameConsole)
    {
        inputManager.getAction("ConsoleToggle")
            .connect([&gameConsole, &inputManager](const Input::InputActionEvent& event) {
                gameConsole.setVisible(!gameConsole.isVisible());
            });
        inputManager.getAction("ConsoleCursorLeft")
            .connect([&gameConsole](
                         const Input::InputActionEvent& event) { gameConsole.moveCursor(-1); });
        inputManager.getAction("ConsoleCursorRight")
            .connect([&gameConsole](
                         const Input::InputActionEvent& event) { gameConsole.moveCursor(1); });
        inputManager.getAction("ConsoleUpHistory")
            .connect(
                [&gameConsole](const Input::InputActionEvent& event) { gameConsole.upHistory(); });
        inputManager.getAction("ConsoleDownHistory")
            .connect([&gameConsole](
                         const Input::InputActionEvent& event) { gameConsole.downHistory(); });
    }
} // namespace obe::Editor