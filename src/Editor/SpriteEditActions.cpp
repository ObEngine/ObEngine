#include <Editor/SpriteEditActions.hpp>

namespace obe
{
    namespace Editor
    {
        void connectSpriteLayerActions(Input::InputManager& inputManager, Graphics::LevelSprite*& selectedSprite, Scene::Scene& world, int& currentLayer)
        {
            inputManager.getAction("SpriteZDepthInc").connect([&selectedSprite, &world](const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setZDepth(selectedSprite->getZDepth() + 1);
                    world.reorganizeLayers();
                }
            });
            inputManager.getAction("SpriteZDepthDec").connect([&selectedSprite, &world](const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setZDepth(selectedSprite->getZDepth() - 1);
                    world.reorganizeLayers();
                }
            });
            inputManager.getAction("SpriteLayerInc").connect([&selectedSprite, &world, &currentLayer](const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setLayer(selectedSprite->getLayer() + 1);
                    
                    world.reorganizeLayers();
                }
                currentLayer += 1;
            });
            inputManager.getAction("SpriteLayerInc").connect([&selectedSprite, &world, &currentLayer](const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setLayer(selectedSprite->getLayer() - 1);
                    world.reorganizeLayers();
                }
                currentLayer -= 1;
            });
        }

        void connectSpriteActions(
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
            inputManager.getAction("MoveHandlePoint").connect([&selectedHandlePoint, &cursor](const Input::InputActionEvent& event)
            {
                if (selectedHandlePoint != nullptr)
                {
                    std::cout << "Moving ref : " << selectedHandlePoint->getReferencial() << std::endl;
                    selectedHandlePoint->moveTo(cursor.getX(), cursor.getY());
                }
            });

            inputManager.getAction("ReleaseHandlePoint").connect([&selectedHandlePoint](const Input::InputActionEvent& event)
            {
                if (selectedHandlePoint != nullptr)
                {
                    selectedHandlePoint = nullptr;
                }
            });

            inputManager.getAction("SpritePick").connect(
                [&selectedSprite, 
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
                    std::cout << "Picky picky :D" << std::endl;
                    selectedHandlePoint = selectedSprite->getHandlePoint(pixelCamera, cursor.getX(), cursor.getY());
                    std::cout << selectedHandlePoint << ", " << hoveredSprite << ", " << selectedSprite << std::endl;
                    if (selectedHandlePoint != nullptr)
                    {
                        std::cout << "POINT POINT POINT" << std::endl;
                        hoveredSprite = nullptr;
                    }
                    else if (hoveredSprite != selectedSprite)
                    {
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
                    selectedSprite->select();

                    selectedSprite->setColor(sf::Color(100, 255, 100));
                }
            });

            inputManager.getAction("SpriteMove").connect(
                [&selectedSprite, 
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
                    if (selectedSprite->getParentId().empty())
                    {
                        Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                        selectedSprite->setPosition(Transform::UnitVector(cursor.getX() + pixelCamera.x - selectedSpriteOffsetX,
                            cursor.getY() + pixelCamera.y - selectedSpriteOffsetY, Transform::Units::WorldPixels));
                    }
                    else
                    {
                        std::cout << "Not empty : '" << selectedSprite->getParentId() << "'" << std::endl;
                        // What to do here ? <REVISION>
                    }
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

            inputManager.getAction("SpriteDelete").connect(
                [&selectedSprite, &world, &sprInfo, &hoveredSprite, &selectedSpriteOffsetX, &selectedSpriteOffsetY]
            (const Input::InputActionEvent& event)
            {
                if (selectedSprite != nullptr)
                {
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
