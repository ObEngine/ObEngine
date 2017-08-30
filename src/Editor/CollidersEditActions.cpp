#include <Editor/CollidersEditActions.hpp>

namespace obe
{
    namespace Editor
    {
        void connectCollidersActions(
            Triggers::TriggerGroup* editorTriggers,
            Input::InputManager& inputManager,
            Scene::Scene& world,
            System::Cursor& cursor,
            int& colliderPtGrabbed,
            Collision::PolygonalCollider*& selectedMasterCollider,
            bool& masterColliderGrabbed)
        {
            inputManager.getAction("ColliderPointPick").connect(
                [editorTriggers, &world, &cursor, &selectedMasterCollider, &masterColliderGrabbed, &colliderPtGrabbed]
            (const Input::InputActionEvent& event)
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
                    editorTriggers->pushParameter("ColliderPointPicked", "collider", selectedMasterCollider);
                    editorTriggers->pushParameter("ColliderPointPicked", "pointIndex", colliderPtGrabbed);
                    editorTriggers->pushParameter("ColliderPointPicked", "pos", cursCoord);
                    editorTriggers->trigger("ColliderPointPicked");
                }
            });
            
            inputManager.getAction("ColliderPointMove").connect(
                [editorTriggers, &selectedMasterCollider, &masterColliderGrabbed, &colliderPtGrabbed, &world, &cursor]
            (const Input::InputActionEvent& event)
            {
                if (selectedMasterCollider != nullptr && !masterColliderGrabbed && colliderPtGrabbed != -1)
                {
                    Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                    Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                    editorTriggers->pushParameter("ColliderPointMoved", "collider", selectedMasterCollider);
                    editorTriggers->pushParameter("ColliderPointMoved", "pointIndex", colliderPtGrabbed);
                    editorTriggers->pushParameter("ColliderPointMoved", "oldPos", selectedMasterCollider->getPointPosition(colliderPtGrabbed).to<Transform::Units::WorldPixels>());
                    editorTriggers->pushParameter("ColliderPointMoved", "pos", cursCoord);
                    editorTriggers->trigger("ColliderPointMoved");
                    selectedMasterCollider->setPointPosition(colliderPtGrabbed, cursCoord);
                }
            });

            inputManager.getAction("ColliderPointRelease").connect([editorTriggers, &colliderPtGrabbed, &selectedMasterCollider](const Input::InputActionEvent& event)
            {
                editorTriggers->pushParameter("ColliderPointReleased", "collider", selectedMasterCollider);
                editorTriggers->pushParameter("ColliderPointReleased", "pointIndex", colliderPtGrabbed);
                editorTriggers->trigger("ColliderPointReleased");
                colliderPtGrabbed = -1;
            });

            inputManager.getAction("ColliderMasterPick").connect(
                [editorTriggers, &world, &cursor, &selectedMasterCollider, &colliderPtGrabbed, &masterColliderGrabbed]
            (const Input::InputActionEvent& event)
            {

                Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                if (world.getColliderByCentroidPosition(cursCoord) != nullptr)
                {
                    Collision::PolygonalCollider* tempCol = world.getColliderByCentroidPosition(cursCoord);
                    if (selectedMasterCollider != nullptr && selectedMasterCollider != tempCol)
                    {
                        selectedMasterCollider->setSelected(false);
                        selectedMasterCollider = nullptr;
                        masterColliderGrabbed = false;
                        colliderPtGrabbed = -1;
                    }
                    selectedMasterCollider = tempCol;
                    selectedMasterCollider->setSelected(true);
                    if (selectedMasterCollider->getParentId() != "") world.getGameObject(selectedMasterCollider->getParentId())->setUpdateState(false);
                    masterColliderGrabbed = true;
                    editorTriggers->pushParameter("ColliderPicked", "collider", selectedMasterCollider);
                    editorTriggers->pushParameter("ColliderPicked", "pos", cursCoord);
                    editorTriggers->trigger("ColliderPicked");
                }
            });

            //Collision Master Move
            inputManager.getAction("ColliderMasterMove").connect(
                [editorTriggers, &selectedMasterCollider, &masterColliderGrabbed, &world, &cursor]
            (const Input::InputActionEvent& event)
            {
                if (selectedMasterCollider != nullptr && masterColliderGrabbed)
                {
                    Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                    Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                    editorTriggers->pushParameter("ColliderMoved", "collider", selectedMasterCollider);
                    editorTriggers->pushParameter("ColliderMoved", "oldPos", selectedMasterCollider->getMasterPointPosition().to<Transform::Units::WorldPixels>());
                    editorTriggers->pushParameter("ColliderMoved", "pos", cursCoord);
                    editorTriggers->trigger("ColliderMoved");
                    selectedMasterCollider->setPositionFromMaster(cursCoord);
                }
            });

            inputManager.getAction("ColliderMasterRelease").connect(
                [editorTriggers, &masterColliderGrabbed, &selectedMasterCollider, &world]
            (const Input::InputActionEvent& event)
            {
                if (masterColliderGrabbed)
                {
                    masterColliderGrabbed = false;
                    if (selectedMasterCollider->getParentId() != "") 
                        world.getGameObject(selectedMasterCollider->getParentId())->setUpdateState(true);
                    editorTriggers->pushParameter("ColliderReleased", "collider", selectedMasterCollider);
                    editorTriggers->trigger("ColliderReleased");
                }
            });

            inputManager.getAction("ColliderPointCreate").connect(
                [editorTriggers, &selectedMasterCollider, &masterColliderGrabbed, &world, &cursor]
            (const Input::InputActionEvent& event)
            {
                if (selectedMasterCollider != nullptr && !masterColliderGrabbed)
                {
                    const Transform::UnitVector pTolerance = Transform::UnitVector(6, 6, Transform::Units::WorldPixels);
                    Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                    Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                    int rqPtRes = selectedMasterCollider->hasPoint(cursCoord, pTolerance);
                    if (rqPtRes == -1)
                    {
                        unsigned int newPtIndex = selectedMasterCollider->findClosestLine(cursCoord);
                        editorTriggers->pushParameter("ColliderPointCreated", "collider", selectedMasterCollider);
                        editorTriggers->pushParameter("ColliderPointCreated", "pointIndex", newPtIndex);
                        editorTriggers->pushParameter("ColliderPointCreated", "pos", cursCoord);
                        editorTriggers->trigger("ColliderPointCreated");
                        selectedMasterCollider->addPoint(cursCoord, newPtIndex);
                    }
                }
            });

            inputManager.getAction("ColliderPointRemove").connect(
                [editorTriggers, &selectedMasterCollider, &masterColliderGrabbed, &colliderPtGrabbed, &world]
            (const Input::InputActionEvent& event)
            {
                if (selectedMasterCollider != nullptr && !masterColliderGrabbed && colliderPtGrabbed != -1)
                {
                    selectedMasterCollider->deletePoint(colliderPtGrabbed);
                    if (selectedMasterCollider->getPointsAmount() <= 2)
                    {
                        editorTriggers->pushParameter("ColliderRemoved", "id", selectedMasterCollider->getId());
                        editorTriggers->trigger("ColliderRemoved");
                        selectedMasterCollider->setSelected(false);
                        world.removeCollider(selectedMasterCollider->getId());
                        selectedMasterCollider = nullptr;
                        masterColliderGrabbed = false;
                        colliderPtGrabbed = -1;
                    }
                    else
                    {
                        editorTriggers->pushParameter("ColliderPointRemoved", "collider", selectedMasterCollider);
                        editorTriggers->pushParameter("ColliderPointRemoved", "pointIndex", colliderPtGrabbed);
                        editorTriggers->trigger("ColliderPointRemoved");
                    }
                    colliderPtGrabbed = -1;
                    
                }
            });

            inputManager.getAction("ColliderRelease").connect(
                [editorTriggers, &selectedMasterCollider, &world, &cursor, &masterColliderGrabbed, &colliderPtGrabbed]
            (const Input::InputActionEvent& event)
            {
                if (selectedMasterCollider != nullptr)
                {
                    Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                    Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x, cursor.getY() + pixelCamera.y, Transform::Units::WorldPixels);
                    if (world.getColliderByCentroidPosition(cursCoord) == nullptr)
                    {
                        if (world.getColliderPointByPosition(cursCoord).first == nullptr)
                        {
                            editorTriggers->pushParameter("ColliderReleased", "collider", selectedMasterCollider);
                            editorTriggers->pushParameter("ColliderReleased", "pos", cursCoord);
                            editorTriggers->trigger("ColliderReleased");
                            selectedMasterCollider->setSelected(false);
                            selectedMasterCollider = nullptr;
                            masterColliderGrabbed = false;
                            colliderPtGrabbed = -1;
                        }
                    }
                }
            });

            inputManager.getAction("ColliderRemove").connect(
                [editorTriggers, &selectedMasterCollider, &masterColliderGrabbed, &world, &colliderPtGrabbed]
            (const Input::InputActionEvent& event)
            {
                if (selectedMasterCollider != nullptr && masterColliderGrabbed)
                {
                    editorTriggers->pushParameter("ColliderRemoved", "id", selectedMasterCollider->getId());
                    editorTriggers->trigger("ColliderRemoved");
                    selectedMasterCollider->setSelected(false);
                    world.removeCollider(selectedMasterCollider->getId());
                    selectedMasterCollider = nullptr;
                    masterColliderGrabbed = false;
                    colliderPtGrabbed = -1;
                }
            });

            inputManager.getAction("ColliderCreate").connect([editorTriggers, &selectedMasterCollider, &world, &cursor](const Input::InputActionEvent& event)
            {
                std::cout << "Called : " << (selectedMasterCollider == nullptr) << std::endl;
                if (selectedMasterCollider == nullptr)
                {
                    Transform::UnitVector pixelCamera = world.getCamera()->getPosition().to<Transform::Units::WorldPixels>();
                    std::cout << "Let's go : " << (cursor.getX() + pixelCamera.x) << ", " << (cursor.getY() + pixelCamera.y) << std::endl;
                    int i = 0;
                    Transform::UnitVector pPos(cursor.getX(), cursor.getY(), Transform::Units::WorldPixels);
                    pPos += pixelCamera;
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
                    editorTriggers->pushParameter("ColliderCreated", "collider", newCollider);
                    editorTriggers->pushParameter("ColliderCreated", "pos", pPos);
                    editorTriggers->trigger("ColliderCreated");
                }
            });
        }
    }
}
