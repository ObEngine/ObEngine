#pragma once

#include <Input/InputManager.hpp>
#include <Scene/Scene.hpp>
#include <System/Cursor.hpp>

namespace obe::Editor
{
    /**
     * \brief Connects all Colliders' related Actions in the Editor
     * \param editorTriggers TriggerGroup of Editor
     * \param inputManager InputManager reference
     * \param scene Scene reference
     * \param cursor Cursor reference
     * \param colliderPtGrabbed Index of the Collider point grabbed
     * \param selectedMasterCollider Pointer to the selected Collider
     * \param masterColliderGrabbed Reference to a boolean that indicates
     * whether a Collider is grabbed or not
     */
    void connectCollidersActions(
        Triggers::TriggerGroup* editorTriggers,
        Input::InputManager& inputManager, Scene::Scene& scene,
        System::Cursor& cursor, int& colliderPtGrabbed,
        Collision::PolygonalCollider*& selectedMasterCollider,
        bool& masterColliderGrabbed);
} // namespace obe::Editor