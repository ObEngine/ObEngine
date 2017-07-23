#include <Editor/SpriteEditActions.hpp>

namespace obe
{
    namespace Editor
    {
        void connectSpriteLayerActions(Input::InputManager& inputManager, Graphics::LevelSprite*& selectedSprite, Scene::World& world, int& currentLayer)
        {
            inputManager.getAction("SpriteZDepthInc").connect([&selectedSprite, &world](Input::InputActionEvent event)
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setZDepth(selectedSprite->getZDepth() + 1);
                    world.reorganizeLayers();
                }
            });
            inputManager.getAction("SpriteZDepthDec").connect([&selectedSprite, &world](Input::InputActionEvent event)
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setZDepth(selectedSprite->getZDepth() - 1);
                    world.reorganizeLayers();
                }
            });
            inputManager.getAction("SpriteLayerInc").connect([&selectedSprite, &world, &currentLayer](Input::InputActionEvent event)
            {
                if (selectedSprite != nullptr)
                {
                    selectedSprite->setLayer(selectedSprite->getLayer() + 1);
                    
                    world.reorganizeLayers();
                }
                currentLayer += 1;
            });
            inputManager.getAction("SpriteLayerInc").connect([&selectedSprite, &world, &currentLayer](Input::InputActionEvent event)
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
            Scene::World& world,
            System::Cursor &cursor,
            Editor::EditorGrid& editorGrid,
            int& selectedSpriteOffsetX,
            int& selectedSpriteOffsetY,
            sf::Text& sprInfo,
            sf::FloatRect& sdBoundingRect,
            sf::RectangleShape& sprInfoBackground)
        {
            Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();

            inputManager.getAction("MoveHandlePoint").connect([&selectedHandlePoint, &cursor](Input::InputActionEvent event)
            {
                if (selectedHandlePoint != nullptr)
                {
                    std::cout << "Moving ref : " << selectedHandlePoint->getReferencial() << std::endl;
                    selectedHandlePoint->moveTo(cursor.getX(), cursor.getY());
                }
            });

            inputManager.getAction("ReleaseHandlePoint").connect([&selectedHandlePoint](Input::InputActionEvent event)
            {
                if (selectedHandlePoint == nullptr)
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
                &pixelCamera,
                &sprInfo,
                &sdBoundingRect]
            (Input::InputActionEvent event)
            {
                std::cout << "Trigger Action SpritePick" << std::endl;
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

                    sdBoundingRect = selectedSprite->getRect();
                    selectedSprite->setColor(sf::Color(100, 255, 100));
                }
            });

            inputManager.getAction("SpriteMove").connect(
                [&selectedSprite, 
                &cursor, 
                &selectedSpriteOffsetX, 
                &selectedSpriteOffsetY, 
                &selectedHandlePoint, 
                &pixelCamera,
                &sdBoundingRect,
                &sprInfo,
                &sprInfoBackground]
            (Input::InputActionEvent event)
            {
                if (selectedSprite != nullptr && selectedHandlePoint == nullptr)
                {
                    if (selectedSprite->getParentId().empty())
                    {
                        selectedSprite->setPosition(Transform::UnitVector(cursor.getX() + pixelCamera.x - selectedSpriteOffsetX,
                            cursor.getY() + pixelCamera.y - selectedSpriteOffsetY, Transform::Units::WorldPixels));
                    }
                    else
                    {
                        std::cout << "Not empty : '" << selectedSprite->getParentId() << "'" << std::endl;
                        // What to do here ? <REVISION>
                    }
                    sdBoundingRect = selectedSprite->getRect();
                    std::string sprInfoStr;
                    sprInfoStr = "Hovered Sprite : \n";
                    sprInfoStr += "    ID : " + selectedSprite->getId() + "\n";
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
            (Input::InputActionEvent event)
            {
                if (selectedSprite != nullptr)
                {
                    world.deleteSprite(selectedSprite);
                    selectedSprite = nullptr;
                    sprInfo.setString("");
                    hoveredSprite = nullptr;
                    selectedSpriteOffsetX = 0;
                    selectedSpriteOffsetY = 0;
                }
            });

            inputManager.getAction("SpriteCancelOffset").connect(
                [&selectedSprite, &cursor, &editorGrid, &selectedSpriteOffsetX, &selectedSpriteOffsetY, &selectedHandlePoint](Input::InputActionEvent event)
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
