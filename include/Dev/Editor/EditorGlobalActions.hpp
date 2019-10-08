#pragma once

#include <TGUI/Widgets/CheckBox.hpp>
#include <TGUI/Widgets/ComboBox.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include <vili/ComplexNode.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Debug/Console.hpp>
#include <Editor/Grid.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Input/InputManager.hpp>
#include <Scene/Scene.hpp>
#include <System/Cursor.hpp>
#include <Time/FramerateManager.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe::Editor
{
    void connectCamMovementActions(Triggers::TriggerGroup* editorTriggers,
                                   Input::InputManager& inputManager,
                                   Scene::Scene& scene, int& cameraSpeed,
                                   Time::FramerateManager& framerateManager);
    void connectGridActions(Triggers::TriggerGroup* editorTriggers,
                            Input::InputManager& inputManager,
                            tgui::CheckBox::Ptr& enableGridCheckbox,
                            tgui::CheckBox::Ptr& snapGridCheckbox,
                            System::Cursor& cursor,
                            Editor::EditorGrid& editorGrid);
    void connectMenuActions(Input::InputManager& inputManager,
                            tgui::ComboBox::Ptr editMode,
                            tgui::Panel::Ptr editorPanel);
    void connectSaveActions(Triggers::TriggerGroup* editorTriggers,
                            Input::InputManager& inputManager,
                            const std::string& mapName, Scene::Scene& scene,
                            double& waitForMapSaving,
                            tgui::Label::Ptr savedLabel,
                            tgui::CheckBox::Ptr saveCameraPositionCheckbox);
    void connectCopyPasteActions(
        Triggers::TriggerGroup* editorTriggers,
        Input::InputManager& inputManager, Scene::Scene& scene,
        vili::ComplexNode& sceneClipboard, tgui::Label::Ptr savedLabel,
        Collision::PolygonalCollider*& selectedMasterCollider,
        Graphics::LevelSprite*& selectedSprite);
    /**
     * \brief Connects Console's related Triggers
     * \param inputManager Reference to the InputManager
     * \param gameConsole Reference to the Game Console
     */
    void connectGameConsoleActions(Input::InputManager& inputManager,
                                   Debug::Console& gameConsole);
} // namespace obe::Editor