#pragma once

#include <Input/InputManager.hpp>
#include <Scene/Scene.hpp>
#include <System/Cursor.hpp>

namespace obe::Editor
{
    void connectSceneNodeActions(
        Triggers::TriggerGroup* editorTriggers,
        Input::InputManager& inputManager, Scene::Scene& scene,
        System::Cursor& cursor, Scene::SceneNode*& sceneNodeGrabbed);
} // namespace obe::Editor