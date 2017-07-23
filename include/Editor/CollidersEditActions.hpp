#pragma once

#include <Input/InputManager.hpp>
#include <Scene/World.hpp>
#include <System/Cursor.hpp>

namespace obe
{
    namespace Editor
    {
        void connectCollidersActions(
            Input::InputManager& inputManager, 
            Scene::World& world, 
            System::Cursor& cursor, 
            int& colliderPtGrabbed, 
            Collision::PolygonalCollider*& selectedMasterCollider,
            bool& masterColliderGrabbed);
    }
}
