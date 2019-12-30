#include <Editor/SceneNodeEditActions.hpp>

namespace obe::Editor
{
    void connectSceneNodeActions(Triggers::TriggerGroup* editorTriggers,
        Input::InputManager& inputManager, Scene::Scene& scene, System::Cursor& cursor,
        Scene::SceneNode*& sceneNodeGrabbed)
    {
        inputManager.getAction("SceneNodePick")
            .connect([editorTriggers, &scene, &cursor, &sceneNodeGrabbed](
                         const Input::InputActionEvent& event) {
                Transform::UnitVector pixelCamera
                    = scene.getCamera()->getPosition().to<Transform::Units::ScenePixels>();
                Transform::UnitVector cursCoord(cursor.getX() + pixelCamera.x,
                    cursor.getY() + pixelCamera.y, Transform::Units::ScenePixels);
                if (auto sceneNode = scene.getSceneNodeByPosition(cursCoord))
                {
                    if (sceneNodeGrabbed && sceneNode != sceneNodeGrabbed)
                    {
                        sceneNodeGrabbed->setSelected(false);
                        sceneNodeGrabbed = nullptr;
                    }
                    sceneNodeGrabbed = sceneNode;
                    sceneNodeGrabbed->setSelected(true);
                    editorTriggers->pushParameter("SceneNodePicked", "sceneNode", sceneNodeGrabbed);
                    editorTriggers->pushParameter("SceneNodePicked", "pos", cursCoord);
                    editorTriggers->trigger("SceneNodePicked");
                }
                else if (sceneNodeGrabbed)
                {
                    sceneNodeGrabbed->setSelected(false);
                    sceneNodeGrabbed = nullptr;
                }
            });

        inputManager.getAction("SceneNodeMove")
            .connect([editorTriggers, &sceneNodeGrabbed, &scene, &cursor](
                         const Input::InputActionEvent& event) {
                if (sceneNodeGrabbed)
                {
                    Transform::UnitVector pixelCamera
                        = scene.getCamera()->getPosition().to<Transform::Units::ScenePixels>();
                    Transform::UnitVector cursCoord(cursor.getConstrainedX() + pixelCamera.x,
                        cursor.getConstrainedY() + pixelCamera.y, Transform::Units::ScenePixels);
                    editorTriggers->pushParameter("SceneNodeMoved", "sceneNode", sceneNodeGrabbed);
                    editorTriggers->pushParameter("SceneNodeMoved", "oldPos",
                        sceneNodeGrabbed->getPosition().to<Transform::Units::ScenePixels>());
                    editorTriggers->pushParameter("SceneNodeMoved", "pos", cursCoord);
                    editorTriggers->trigger("SceneNodeMoved");
                    sceneNodeGrabbed->setPosition(cursCoord);
                }
            });

        inputManager.getAction("SceneNodeRelease")
            .connect(
                [editorTriggers, &sceneNodeGrabbed, &scene](const Input::InputActionEvent& event) {
                    if (sceneNodeGrabbed)
                    {
                        editorTriggers->pushParameter(
                            "SceneNodeReleased", "sceneNode", sceneNodeGrabbed);
                        editorTriggers->trigger("SceneNodeReleased");
                    }
                });
    }
} // namespace obe::Editor
