#pragma once

#include <Input/InputManager.hpp>
#include <Scene/Scene.hpp>
#include <System/Cursor.hpp>

namespace obe
{
    namespace Editor
    {
        void connectCollidersActions(
            Input::InputManager& inputManager, 
            Scene::Scene& world, 
            System::Cursor& cursor, 
            int& colliderPtGrabbed, 
            Collision::PolygonalCollider*& selectedMasterCollider,
            bool& masterColliderGrabbed);
    }
}
