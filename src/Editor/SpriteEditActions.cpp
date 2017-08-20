#include <Editor/SpriteEditActions.hpp>

namespace obe
{
    namespace Editor
    {
        void connectSpriteLayerActions(
            Triggers::TriggerGroup* editorTriggers, 
            Input::InputManager& inputManager, 
            Graphics::LevelSprite*& selectedSprite, 
            Scene::Scene& world, 
            int& currentLayer)
        {
            inputManager.getAction("SpriteZDepthInc").connect([editorTriggers, &selectedSprite, &world](const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setZDepth(selectedSprite->getZDepth() + 1);
                    world.reorganizeLayers();
                    editorTriggers->pushParameter("SpriteZDepthChanged", "zdepth", selectedSprite->getZDepth());
                    editorTriggers->pushParameter("SpriteZDepthChanged", "sprite", selectedSprite);
                    editorTriggers->pushParameter("SpriteZDepthChanged", "operation", "Increase");
                    editorTriggers->trigger("SpriteZDepthChanged");
                }
            });
            inputManager.getAction("SpriteZDepthDec").connect([editorTriggers, &selectedSprite, &world](const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setZDepth(selectedSprite->getZDepth() - 1);
                    world.reorganizeLayers();
                    editorTriggers->pushParameter("SpriteZDepthChanged", "zdepth", selectedSprite->getZDepth());
                    editorTriggers->pushParameter("SpriteZDepthChanged", "sprite", selectedSprite);
                    editorTriggers->pushParameter("SpriteZDepthChanged", "operation", "Decrease");
                    editorTriggers->trigger("SpriteZDepthChanged");
                }
            });
            inputManager.getAction("SpriteLayerInc").connect([editorTriggers, &selectedSprite, &world, &currentLayer](const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setLayer(selectedSprite->getLayer() + 1);

                    editorTriggers->pushParameter("SpriteLayerChanged", "layer", selectedSprite->getLayer());
                    editorTriggers->pushParameter("SpriteLayerChanged", "sprite", selectedSprite);
                    editorTriggers->pushParameter("SpriteLayerChanged", "operation", "Increase");
                    editorTriggers->trigger("SpriteLayerChanged");
                    
                    world.reorganizeLayers();
                }
                currentLayer += 1;
            });
            inputManager.getAction("SpriteLayerDec").connect([editorTriggers, &selectedSprite, &world, &currentLayer](const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setLayer(selectedSprite->getLayer() - 1);

                    editorTriggers->pushParameter("SpriteLayerChanged", "layer", selectedSprite->getLayer());
                    editorTriggers->pushParameter("SpriteLayerChanged", "sprite", selectedSprite);
                    editorTriggers->pushParameter("SpriteLayerChanged", "operation", "Decrease");
                    editorTriggers->trigger("SpriteLayerChanged");

                    world.reorganizeLayers();
                }
                currentLayer -= 1;
            });
        }

        void connectSpriteActions(
            Triggers::TriggerGroup* editorTriggers,
            Input::InputManager& inputManager,
            Graphics::LevelSprite*& hoveredSprite,
            Graphics::LevelSprite*& selectedSprite,
            Graphics::LevelSpriteHandlePoint*& selectedHandlePoint,
            Scene::Scene& world,
            System::Cursor &cursor,
            Editor::EditorGrid& editorGrid,
            int& selectedSpriteOffsetX,
            int& selectedSpriteOffsetY,
            sf::Text& sprInfo,
            sf::RectangleShape& sprInfoBackground)
        {
            inputManager.getAction("MoveHandlePoint").connect([editorTriggers, &selectedHandlePoint, &cursor, &world](const Input::InputActionEvent& event)
            {
                Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                if (selectedHandlePoint != nullptr)
                {
                    std::cout << "Moving ref : " << selectedHandlePoint->getReferencial() << std::endl;
                    selectedHandlePoint->moveTo(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y);
                    editorTriggers->pushParameter("SpriteHandlePointMoved", "handlePoint", selectedHandlePoint);
                    editorTriggers->trigger("SpriteHandlePointMoved");
                }
            });

            inputManager.getAction("ReleaseHandlePoint").connect([editorTriggers, &selectedHandlePoint](const Input::InputActionEvent& event)
            {
                if (selectedHandlePoint != nullptr)
                {
                    editorTriggers->pushParameter("SpriteHandlePointReleased", "handlePoint", selectedHandlePoint);
                    editorTriggers->trigger("SpriteHandlePointReleased");
                    selectedHandlePoint = nullptr;
                }
            });

            inputManager.getAction("SpritePick").connect(
                [editorTriggers,
                &selectedSprite, 
                &selectedSpriteOffsetX, 
                &selectedSpriteOffsetY, 
                &cursor, 
                &selectedHandlePoint, 
                &hoveredSprite,
                &sprInfo,
                &world]
            (const Input::InputActionEvent& event)
            {
                Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                if (selectedSprite != nullptr && selectedHandlePoint == nullptr)
                {
                    selectedHandlePoint = selectedSprite->getHandlePoint(pixelCamera, cursor.getX(), cursor.getY());
                    std::cout << selectedHandlePoint << ", " << hoveredSprite << ", " << selectedSprite << std::endl;
                    if (selectedHandlePoint != nullptr)
                    {
                        editorTriggers->pushParameter("SpriteHandlePointPicked", "handlePoint", selectedHandlePoint);
                        editorTriggers->pushParameter("SpriteHandlePointPicked", "pos", 
                            pixelCamera + Transform::UnitVector(cursor.getX(), cursor.getY(), Transform::Units::WorldPixels));
                        editorTriggers->trigger("SpriteHandlePointPicked");
                        hoveredSprite = nullptr;
                    }
                    else if (hoveredSprite != selectedSprite)
                    {
                        editorTriggers->pushParameter("SpriteUnselect", "sprite", selectedSprite);
                        editorTriggers->trigger("SpriteUnselect");
                        std::cout << "Unselect" << std::endl;
                        selectedSprite->setColor(sf::Color::White);
                        selectedSprite->unselect();
                        sprInfo.setString("");
                        selectedSprite = nullptr;
                        selectedSpriteOffsetX = 0;
                        selectedSpriteOffsetY = 0;

                    }
                    std::cout << "Ended NonEf" << std::endl;
                }
                if (hoveredSprite != nullptr && selectedHandlePoint == nullptr)
                {
                    std::cout << "MUCH WOW" << std::endl;
                    selectedSprite = hoveredSprite;
                    selectedSpriteOffsetX = (cursor.getX() + pixelCamera.x) - selectedSprite->getPosition().to<Transform::Units::WorldPixels>().x;
                    selectedSpriteOffsetY = (cursor.getY() + pixelCamera.y) - selectedSprite->getPosition().to<Transform::Units::WorldPixels>().y;
                    editorTriggers->pushParameter("SpriteSelect", "sprite", selectedSprite);
                    editorTriggers->pushParameter("SpriteSelect", "offset", Transform::UnitVector(selectedSpriteOffsetX, selectedSpriteOffsetY, Transform::Units::WorldPixels));
                    editorTriggers->pushParameter("SpriteSelect", "pos",
                        pixelCamera + Transform::UnitVector(cursor.getX(), cursor.getY(), Transform::Units::WorldPixels));
                    editorTriggers->trigger("SpriteSelect");
                    selectedSprite->select();

                    selectedSprite->setColor(sf::Color(100, 255, 100));
                }
            });

            inputManager.getAction("SpriteMove").connect(
                [editorTriggers,
                &selectedSprite, 
                &cursor, 
                &selectedSpriteOffsetX, 
                &selectedSpriteOffsetY, 
                &selectedHandlePoint, 
                &sprInfo,
                &sprInfoBackground,
                &world]
            (const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr && selectedHandlePoint == nullptr)
                {
                    editorTriggers->pushParameter("SpriteMoved", "sprite", selectedSprite);
                    editorTriggers->pushParameter("SpriteMoved", "oldPos", selectedSprite->getPosition());
                    Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                    selectedSprite->setPosition(Transform::UnitVector(cursor.getX() + pixelCamera.x - selectedSpriteOffsetX,
                        cursor.getY() + pixelCamera.y - selectedSpriteOffsetY, Transform::Units::WorldPixels));
                    editorTriggers->pushParameter("SpriteMoved", "pos", selectedSprite->getPosition());
                    editorTriggers->pushParameter("SpriteMoved", "offset", Transform::UnitVector(selectedSpriteOffsetX, selectedSpriteOffsetY, Transform::Units::WorldPixels));
                    editorTriggers->trigger("SpriteMoved");

                    std::string sprInfoStr;
                    sprInfoStr = "Hovered Sprite : \n";
                    sprInfoStr += "    Id : " + selectedSprite->getId() + "\n";
                    sprInfoStr += "    Name : " + selectedSprite->getPath() + "\n";
                    sprInfoStr += "    Pos : " + std::to_string(selectedSprite->getX()) + "," + std::to_string(selectedSprite->getY()) + "\n";
                    sprInfoStr += "    Size : " + std::to_string(selectedSprite->getWidth()) + "," + std::to_string(selectedSprite->getHeight()) + "\n";
                    sprInfoStr += "    Rot : " + std::to_string(selectedSprite->getRotation()) + "\n";
                    sprInfoStr += "    Layer / Z : " + std::to_string(selectedSprite->getLayer()) + "," + std::to_string(selectedSprite->getZDepth()) + "\n";
                    sprInfo.setString(sprInfoStr);
                    sprInfoBackground.setSize(sf::Vector2f(sprInfo.getGlobalBounds().width + 20, sprInfo.getGlobalBounds().height - 10));
                    sprInfoBackground.setPosition(cursor.getX() + 40, cursor.getY());
                    sprInfo.setPosition(cursor.getX() + 50, cursor.getY());
                }
            });

            inputManager.getAction("SpriteRemove").connect(
                [editorTriggers, &selectedSprite, &world, &sprInfo, &hoveredSprite, &selectedSpriteOffsetX, &selectedSpriteOffsetY]
            (const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr)
                {
                    editorTriggers->pushParameter("SpriteRemoved", "id", selectedSprite->getId());
                    editorTriggers->trigger("SpriteRemoved");
                    world.removeLevelSpriteById(selectedSprite->getId());
                    selectedSprite = nullptr;
                    sprInfo.setString("");
                    hoveredSprite = nullptr;
                    selectedSpriteOffsetX = 0;
                    selectedSpriteOffsetY = 0;

                }
            });

            inputManager.getAction("SpriteCancelOffset").connect(
                [&selectedSprite, &cursor, &editorGrid, &selectedSpriteOffsetX, &selectedSpriteOffsetY, &selectedHandlePoint](const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr && selectedHandlePoint == nullptr)
                {
                    selectedSpriteOffsetX = 0;
                    selectedSpriteOffsetY = 0;
                }
            });
        }
    }
}
