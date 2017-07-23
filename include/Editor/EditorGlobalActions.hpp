#pragma once

#include <TGUI/Widgets/CheckBox.hpp>
#include <TGUI/Widgets/ComboBox.hpp>
#include <TGUI/Widgets/Label.hpp>

#include <Editor/Grid.hpp>
#include <Input/InputManager.hpp>
#include <Scene/World.hpp>
#include <System/Cursor.hpp>
#include <Time/FramerateManager.hpp>


namespace obe
{
    namespace Editor
    {
        void connectCamMovementActions(Input::InputManager& inputManager, Scene::World& world, int& cameraSpeed, Time::FramerateManager& framerateManager);
        void connectMagnetActions(Input::InputManager& inputManager, tgui::CheckBox::Ptr& enableGridCheckbox, System::Cursor& cursor, Editor::EditorGrid& editorGrid);
        void connectMenuActions(Input::InputManager& inputManager, tgui::ComboBox::Ptr editMode, tgui::ComboBox::Ptr cameraMode);
        void connectSaveActions(Input::InputManager& inputManager, const std::string& mapName, Scene::World& world, double& waitForMapSaving, tgui::Label::Ptr savedLabel);
    }
}
