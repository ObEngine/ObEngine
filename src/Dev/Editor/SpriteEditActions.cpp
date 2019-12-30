#include <Editor/SpriteEditActions.hpp>

namespace obe::Editor
{
    void connectSpriteLayerActions(Triggers::TriggerGroup* editorTriggers,
        Input::InputManager& inputManager, Graphics::LevelSprite*& selectedSprite,
        Scene::Scene& scene, int& currentLayer)
    {
        inputManager.getAction("SpriteZDepthInc")
            .connect([editorTriggers, &selectedSprite, &scene](
                         const Input::InputActionEvent& event) {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setZDepth(selectedSprite->getZDepth() + 1);
                    editorTriggers->pushParameter(
                        "SpriteZDepthChanged", "zdepth", selectedSprite->getZDepth());
                    editorTriggers->pushParameter("SpriteZDepthChanged", "sprite", selectedSprite);
                    editorTriggers->pushParameter("SpriteZDepthChanged", "operation", "Increase");
                    editorTriggers->trigger("SpriteZDepthChanged");
                }
            });
        inputManager.getAction("SpriteZDepthDec")
            .connect([editorTriggers, &selectedSprite, &scene](
                         const Input::InputActionEvent& event) {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setZDepth(selectedSprite->getZDepth() - 1);
                    editorTriggers->pushParameter(
                        "SpriteZDepthChanged", "zdepth", selectedSprite->getZDepth());
                    editorTriggers->pushParameter("SpriteZDepthChanged", "sprite", selectedSprite);
                    editorTriggers->pushParameter("SpriteZDepthChanged", "operation", "Decrease");
                    editorTriggers->trigger("SpriteZDepthChanged");
                }
            });
        inputManager.getAction("SpriteLayerInc")
            .connect([editorTriggers, &selectedSprite, &scene, &currentLayer](
                         const Input::InputActionEvent& event) {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setLayer(selectedSprite->getLayer() + 1);

                    editorTriggers->pushParameter(
                        "SpriteLayerChanged", "layer", selectedSprite->getLayer());
                    editorTriggers->pushParameter("SpriteLayerChanged", "sprite", selectedSprite);
                    editorTriggers->pushParameter("SpriteLayerChanged", "operation", "Increase");
                    editorTriggers->trigger("SpriteLayerChanged");
                }
                currentLayer += 1;
            });
        inputManager.getAction("SpriteLayerDec")
            .connect([editorTriggers, &selectedSprite, &scene, &currentLayer](
                         const Input::InputActionEvent& event) {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setLayer(selectedSprite->getLayer() - 1);

                    editorTriggers->pushParameter(
                        "SpriteLayerChanged", "layer", selectedSprite->getLayer());
                    editorTriggers->pushParameter("SpriteLayerChanged", "sprite", selectedSprite);
                    editorTriggers->pushParameter("SpriteLayerChanged", "operation", "Decrease");
                    editorTriggers->trigger("SpriteLayerChanged");
                }
                currentLayer -= 1;
            });
    }

    void connectSpriteActions(Triggers::TriggerGroup* editorTriggers,
        Input::InputManager& inputManager, Graphics::LevelSprite*& hoveredSprite,
        Graphics::LevelSprite*& selectedSprite,
        Graphics::LevelSpriteHandlePoint*& selectedHandlePoint, Scene::Scene& world,
        System::Cursor& cursor, Editor::EditorGrid& editorGrid, int& selectedSpriteOffsetX,
        int& selectedSpriteOffsetY, Editor::Tooltip& tooltip, Transform::Units& editorUnit)
    {
        inputManager.getAction("MoveHandlePoint")
            .connect([editorTriggers, &selectedHandlePoint, &cursor, &world](
                         const Input::InputActionEvent& event) {
                Transform::UnitVector pixelCamera
                    = world.getCamera()->getPosition().to<Transform::Units::ScenePixels>();
                if (selectedHandlePoint != nullptr)
                {
                    selectedHandlePoint->moveTo(cursor.getPosition(), pixelCamera);
                    editorTriggers->pushParameter(
                        "SpriteHandlePointMoved", "handlePoint", selectedHandlePoint);
                    editorTriggers->trigger("SpriteHandlePointMoved");
                }
            });

        inputManager.getAction("ReleaseHandlePoint")
            .connect([editorTriggers, &selectedHandlePoint](const Input::InputActionEvent& event) {
                if (selectedHandlePoint != nullptr)
                {
                    editorTriggers->pushParameter(
                        "SpriteHandlePointReleased", "handlePoint", selectedHandlePoint);
                    editorTriggers->trigger("SpriteHandlePointReleased");
                    selectedHandlePoint = nullptr;
                }
            });

        inputManager.getAction("SpritePick")
            .connect([editorTriggers, &selectedSprite, &selectedSpriteOffsetX,
                         &selectedSpriteOffsetY, &cursor, &selectedHandlePoint, &hoveredSprite,
                         &tooltip, &world](const Input::InputActionEvent& event) {
                Transform::UnitVector pixelCamera
                    = world.getCamera()->getPosition().to<Transform::Units::ScenePixels>();
                if (selectedSprite != nullptr && selectedHandlePoint == nullptr)
                {
                    selectedHandlePoint
                        = selectedSprite->getHandlePoint(pixelCamera, cursor.getX(), cursor.getY());
                    if (selectedHandlePoint != nullptr)
                    {
                        editorTriggers->pushParameter(
                            "SpriteHandlePointPicked", "handlePoint", selectedHandlePoint);
                        editorTriggers->pushParameter(
                            "SpriteHandlePointPicked", "pos", pixelCamera + cursor.getPosition());
                        editorTriggers->trigger("SpriteHandlePointPicked");
                        hoveredSprite = nullptr;
                    }
                    else if (hoveredSprite != selectedSprite)
                    {
                        editorTriggers->pushParameter("SpriteUnselect", "sprite", selectedSprite);
                        editorTriggers->trigger("SpriteUnselect");
                        selectedSprite->setColor(sf::Color::White);
                        selectedSprite->unselect();
                        tooltip.clear();
                        selectedSprite = nullptr;
                        selectedSpriteOffsetX = 0;
                        selectedSpriteOffsetY = 0;
                    }
                }
                if (hoveredSprite != nullptr && selectedHandlePoint == nullptr)
                {
                    selectedSprite = hoveredSprite;
                    Transform::UnitVector selectedSpriteOffset
                        = selectedSprite
                              ->getPositionTransformer()(
                                  cursor.getPosition() - selectedSprite->getPosition(),
                                  -pixelCamera, selectedSprite->getLayer())
                              .to<Transform::Units::ScenePixels>();
                    selectedSpriteOffsetX = selectedSpriteOffset.x;
                    selectedSpriteOffsetY = selectedSpriteOffset.y;
                    editorTriggers->pushParameter("SpriteSelect", "sprite", selectedSprite);
                    editorTriggers->pushParameter("SpriteSelect", "offset",
                        Transform::UnitVector(selectedSpriteOffsetX, selectedSpriteOffsetY,
                            Transform::Units::ScenePixels));
                    editorTriggers->pushParameter("SpriteSelect", "pos",
                        pixelCamera
                            + Transform::UnitVector(
                                  cursor.getX(), cursor.getY(), Transform::Units::ScenePixels));
                    editorTriggers->trigger("SpriteSelect");
                    selectedSprite->select();

                    selectedSprite->setColor(sf::Color(100, 255, 100));
                }
            });

        inputManager.getAction("SpriteMove")
            .connect([editorTriggers, &selectedSprite, &cursor, &selectedSpriteOffsetX,
                         &selectedSpriteOffsetY, &selectedHandlePoint, &tooltip, &world,
                         &editorUnit](const Input::InputActionEvent& event) {
                if (selectedSprite != nullptr && selectedHandlePoint == nullptr)
                {
                    editorTriggers->pushParameter("SpriteMoved", "sprite", selectedSprite);
                    editorTriggers->pushParameter(
                        "SpriteMoved", "oldPos", selectedSprite->getPosition());
                    Transform::UnitVector pixelCamera
                        = world.getCamera()->getPosition().to<Transform::Units::ScenePixels>();
                    Transform::UnitVector basePos(cursor.getConstrainedX() - selectedSpriteOffsetX,
                        cursor.getConstrainedY() - selectedSpriteOffsetY,
                        Transform::Units::ScenePixels);
                    Transform::UnitVector newPosition = selectedSprite->getPositionTransformer()(
                        basePos, -pixelCamera, selectedSprite->getLayer());
                    selectedSprite->setPosition(newPosition);
                    editorTriggers->pushParameter(
                        "SpriteMoved", "pos", selectedSprite->getPosition());
                    editorTriggers->pushParameter("SpriteMoved", "offset",
                        Transform::UnitVector(selectedSpriteOffsetX, selectedSpriteOffsetY,
                            Transform::Units::ScenePixels));
                    editorTriggers->trigger("SpriteMoved");

                    tooltip.setText("Selected Sprite : \n"
                                    "   Id : {}\n"
                                    "   Name : {}\n"
                                    "   Pos : {}, {}\n"
                                    "   Size : {}, {}\n"
                                    "   Rot : {}\n"
                                    "   Layer / Z : {}, {}\n",
                        selectedSprite->getId(), selectedSprite->getPath(),
                        selectedSprite->getPosition().to(editorUnit).x,
                        selectedSprite->getPosition().to(editorUnit).y,
                        selectedSprite->getSize().to(editorUnit).x,
                        selectedSprite->getSize().to(editorUnit).y, selectedSprite->getRotation(),
                        selectedSprite->getLayer(),
                        selectedSprite->getZDepth()); // <REVISION> Duplicated code (See
                                                      // MapEditor.cpp)

                    tooltip.setPosition(cursor.getX() + 40, cursor.getY());
                }
            });

        inputManager.getAction("SpriteRemove")
            .connect([editorTriggers, &selectedSprite, &world, &tooltip, &hoveredSprite,
                         &selectedSpriteOffsetX,
                         &selectedSpriteOffsetY](const Input::InputActionEvent& event) {
                if (selectedSprite != nullptr)
                {
                    editorTriggers->pushParameter("SpriteRemoved", "id", selectedSprite->getId());
                    editorTriggers->trigger("SpriteRemoved");
                    world.removeLevelSprite(selectedSprite->getId());
                    selectedSprite = nullptr;
                    tooltip.clear();
                    hoveredSprite = nullptr;
                    selectedSpriteOffsetX = 0;
                    selectedSpriteOffsetY = 0;
                }
            });

        inputManager.getAction("SpriteCancelOffset")
            .connect([&selectedSprite, &cursor, &editorGrid, &selectedSpriteOffsetX,
                         &selectedSpriteOffsetY,
                         &selectedHandlePoint](const Input::InputActionEvent& event) {
                if (selectedSprite != nullptr && selectedHandlePoint == nullptr)
                {
                    selectedSpriteOffsetX = 0;
                    selectedSpriteOffsetY = 0;
                }
            });
    }
} // namespace obe::Editor