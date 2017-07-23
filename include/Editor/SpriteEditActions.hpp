#pragma once

#include <Editor/Grid.hpp>
#include <Input/InputManager.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Scene/World.hpp>
#include <System/Cursor.hpp>

namespace obe
{
    namespace Editor
    {
        void connectSpriteLayerActions(Input::InputManager& inputManager, Graphics::LevelSprite*& selectedSprite, Scene::World& world, int& currentLayer);
        void connectSpriteActions(
            Input::InputManager& inputManager, 
            Graphics::LevelSprite*& hoveredSprite,
            Graphics::LevelSprite*& selectedSprite, 
            Graphics::LevelSpriteHandlePoint*& selectedHandlePoint,
            Scene::World& world,
            System::Cursor &cursor, 
            Editor::EditorGrid& editorGrid, 
            int& selectedSpriteOffsetX, 
            int& selectedSpriteOffsetY,
            sf::Text& sprInfo,
            sf::FloatRect& sdBoundingRect,
            sf::RectangleShape& sprInfoBackground);
    }
}
