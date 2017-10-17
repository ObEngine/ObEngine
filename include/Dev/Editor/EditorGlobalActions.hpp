#pragma once

#include <TGUI/Widgets/CheckBox.hpp>
#include <TGUI/Widgets/ComboBox.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Panel.hpp>

#include <Debug/Console.hpp>
#include <Editor/Grid.hpp>
#include <Input/InputManager.hpp>
#include <Scene/Scene.hpp>
#include <System/Cursor.hpp>
#include <Time/FramerateManager.hpp>

namespace obe
{
    namespace Editor
    {
        void connectCamMovementActions(
            Triggers::TriggerGroup* editorTriggers,
            Input::InputManager& inputManager, 
            Scene::Scene& world, 
            int& cameraSpeed, 
            Time::FramerateManager& framerateManager);
        void connectGridActions(
            Triggers::TriggerGroup* editorTriggers,
            Input::InputManager& inputManager, 
            tgui::CheckBox::Ptr& enableGridCheckbox, 
            tgui::CheckBox::Ptr& snapGridCheckbox, 
            System::Cursor& cursor, 
            Editor::EditorGrid& editorGrid);
        void connectMenuActions(
            Input::InputManager& inputManager, 
            tgui::ComboBox::Ptr editMode, 
            tgui::Panel::Ptr editorPanel);
        void connectSaveActions(
            Triggers::TriggerGroup* editorTriggers, 
            Input::InputManager& inputManager, 
            const std::string& mapName, 
            Scene::Scene& world, 
            double& waitForMapSaving, 
            tgui::Label::Ptr savedLabel,
            tgui::CheckBox::Ptr saveCameraPositionCheckbox);
        /**
         * \brief Connects Console's related Triggers
         * \param inputManager Reference to the InputManager
         * \param gameConsole Reference to the Game Console
         */
        void connectGameConsoleActions(
            Input::InputManager& inputManager,
            Debug::Console& gameConsole
        );
    }
}
