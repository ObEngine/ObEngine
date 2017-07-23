#include <Editor/CollidersEditActions.hpp>

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
            bool& masterColliderGrabbed)
        {
            inputManager.getAction("ColliderPointPick").connect(
                [&world, &cursor, &selectedMasterCollider, &masterColliderGrabbed, &colliderPtGrabbed]
            (Input::InputActionEvent event)
            {
                Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                if (colliderPtGrabbed == -1 && world.getColliderPointByPosition(cursCoord).first != nullptr)
                {
                    std::pair<Collision::PolygonalCollider*, int> selectedPtCollider;
                    selectedPtCollider = world.getColliderPointByPosition(cursCoord);
                    if (selectedMasterCollider != nullptr && selectedMasterCollider != selectedPtCollider.first)
                    {
                        selectedMasterCollider->setSelected(false);
                        selectedMasterCollider = nullptr;
                        masterColliderGrabbed = false;
                        colliderPtGrabbed = -1;
                    }
                    selectedMasterCollider = selectedPtCollider.first;
                    selectedMasterCollider->setSelected(true);
                    colliderPtGrabbed = selectedPtCollider.second;
                }
            });
            
            inputManager.getAction("ColliderPointMove").connect(
                [&selectedMasterCollider, &masterColliderGrabbed, &colliderPtGrabbed, &world, &cursor]
            (Input::InputActionEvent event)
            {
                if (selectedMasterCollider != nullptr && !masterColliderGrabbed && colliderPtGrabbed != -1)
                {
                    Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                    Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                    selectedMasterCollider->setPointPosition(colliderPtGrabbed, cursCoord);
                }
            });

            inputManager.getAction("ColliderPointRelease").connect([&colliderPtGrabbed](Input::InputActionEvent& event)
            {
                colliderPtGrabbed = -1;
            });

            inputManager.getAction("ColliderMasterPick").connect(
                [&world, &cursor, &selectedMasterCollider, &colliderPtGrabbed, &masterColliderGrabbed]
            (Input::InputActionEvent& event)
            {

                Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                if (world.getColliderCentroidByPosition(cursCoord) != nullptr)
                {
                    Collision::PolygonalCollider* tempCol = world.getColliderCentroidByPosition(cursCoord);
                    if (selectedMasterCollider != nullptr && selectedMasterCollider != tempCol)
                    {
                        selectedMasterCollider->setSelected(false);
                        selectedMasterCollider = nullptr;
                        masterColliderGrabbed = false;
                        colliderPtGrabbed = -1;
                    }
                    selectedMasterCollider = tempCol;
                    selectedMasterCollider->setSelected(true);
                    if (selectedMasterCollider->getParentId() != "") world.getGameObjectById(selectedMasterCollider->getParentId())->setUpdateState(false);
                    masterColliderGrabbed = true;
                }
            });

            //Collision Master Move
            inputManager.getAction("ColliderMasterMove").connect(
                [&selectedMasterCollider, &masterColliderGrabbed, &world, &cursor]
            (Input::InputActionEvent& event)
            {
                if (selectedMasterCollider != nullptr && masterColliderGrabbed)
                {
                    Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                    Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                    selectedMasterCollider->setPositionFromMaster(cursCoord);
                }
            });

            inputManager.getAction("ColliderMasterRelease").connect(
                [&masterColliderGrabbed, &selectedMasterCollider, &world]
            (Input::InputActionEvent& event)
            {
                if (masterColliderGrabbed)
                {
                    masterColliderGrabbed = false;
                    if (selectedMasterCollider->getParentId() != "") 
                        world.getGameObjectById(selectedMasterCollider->getParentId())->setUpdateState(true);
                }
            });

            inputManager.getAction("ColliderPointCreate").connect(
                [&selectedMasterCollider, &masterColliderGrabbed, &world, &cursor]
            (Input::InputActionEvent& event)
            {
                if (selectedMasterCollider != nullptr && !masterColliderGrabbed)
                {
                    const Transform::UnitVector pTolerance = Transform::UnitVector(6, 6, Transform::Units::WorldPixels);
                    Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                    Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                    int rqPtRes = selectedMasterCollider->hasPoint(cursCoord, pTolerance);
                    if (rqPtRes == -1)
                    {
                        selectedMasterCollider->addPoint(cursCoord, selectedMasterCollider->findClosestLine(cursCoord));
                    }
                }
            });

            inputManager.getAction("ColliderPointDelete").connect(
                [&selectedMasterCollider, &masterColliderGrabbed, &colliderPtGrabbed, &world]
            (Input::InputActionEvent& event)
            {
                if (selectedMasterCollider != nullptr && !masterColliderGrabbed && colliderPtGrabbed != -1)
                {
                    selectedMasterCollider->deletePoint(colliderPtGrabbed);
                    if (selectedMasterCollider->getPointsAmount() <= 2)
                    {
                        selectedMasterCollider->setSelected(false);
                        world.removeColliderById(selectedMasterCollider->getId());
                        selectedMasterCollider = nullptr;
                        masterColliderGrabbed = false;
                        colliderPtGrabbed = -1;
                    }
                    colliderPtGrabbed = -1;
                }
            });

            inputManager.getAction("ColliderRelease").connect(
                [&selectedMasterCollider, &world, &cursor, &masterColliderGrabbed, &colliderPtGrabbed]
            (Input::InputActionEvent& event)
            {
                if (selectedMasterCollider != nullptr)
                {
                    Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                    Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                    if (world.getColliderCentroidByPosition(cursCoord) == nullptr)
                    {
                        if (world.getColliderPointByPosition(cursCoord).first == nullptr)
                        {
                            selectedMasterCollider->setSelected(false);
                            selectedMasterCollider = nullptr;
                            masterColliderGrabbed = false;
                            colliderPtGrabbed = -1;
                        }
                    }
                }
            });

            inputManager.getAction("ColliderDelete").connect(
                [&selectedMasterCollider, &masterColliderGrabbed, &world, &colliderPtGrabbed]
            (Input::InputActionEvent& event)
            {
                if (selectedMasterCollider != nullptr && masterColliderGrabbed)
                {
                    selectedMasterCollider->setSelected(false);
                    world.removeColliderById(selectedMasterCollider->getId());
                    selectedMasterCollider = nullptr;
                    masterColliderGrabbed = false;
                    colliderPtGrabbed = -1;
                }
            });

            inputManager.getAction("ColliderCreate").connect([&selectedMasterCollider, &world, &cursor](Input::InputActionEvent& event)
            {
                std::cout << "Called : " << (selectedMasterCollider == nullptr) << std::endl;
                if (selectedMasterCollider == nullptr)
                {
                    Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                    std::cout << "Let's go : " << (cursor.getX() + pixelCamera.x) << ", " << (cursor.getY() + pixelCamera.y) << std::endl;
                    int i = 0;
                    Transform::UnitVector pPos(cursor.getX(), cursor.getY(), Transform::Units::WorldPixels);
                    std::string testId = "collider" + std::to_string(world.getColliderAmount() + i);
                    while (world.doesColliderExists(testId))
                    {
                        testId = "collider" + std::to_string(world.getColliderAmount() + i++);
                    }
                    Collision::PolygonalCollider* newCollider = world.createCollider(testId);
                    newCollider->addPoint(Transform::UnitVector(50, 0, Transform::Units::WorldPixels));
                    newCollider->addPoint(Transform::UnitVector(0, 50, Transform::Units::WorldPixels));
                    newCollider->addPoint(Transform::UnitVector(100, 50, Transform::Units::WorldPixels));
                    newCollider->setPositionFromMaster(pPos);
                }
            });
        }
    }
}
