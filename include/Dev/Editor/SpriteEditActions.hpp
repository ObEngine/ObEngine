#pragma once

#include <Editor/EditorTooltip.hpp>
#include <Editor/Grid.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Input/InputManager.hpp>
#include <Scene/Scene.hpp>
#include <System/Cursor.hpp>

namespace obe::Editor
{
    void connectSpriteLayerActions(Triggers::TriggerGroup* editorTriggers,
                                   Input::InputManager& inputManager,
                                   Graphics::LevelSprite*& selectedSprite,
                                   Scene::Scene& world, int& currentLayer);
    void
    connectSpriteActions(Triggers::TriggerGroup* editorTriggers,
                         Input::InputManager& inputManager,
                         Graphics::LevelSprite*& hoveredSprite,
                         Graphics::LevelSprite*& selectedSprite,
                         Graphics::LevelSpriteHandlePoint*& selectedHandlePoint,
                         Scene::Scene& world, System::Cursor& cursor,
                         Editor::EditorGrid& editorGrid,
                         int& selectedSpriteOffsetX, int& selectedSpriteOffsetY,
                         Editor::Tooltip& tooltip,
                         Transform::Units& editorUnit);
} // namespace obe::Editor
