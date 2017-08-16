#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <TGUI/Animation.hpp>

#include <Editor/EditorGlobalActions.hpp>

namespace obe
{
    namespace Editor
    {
        void connectCamMovementActions(
            Triggers::TriggerGroup* editorTriggers, 
            Input::InputManager& inputManager, 
            Scene::Scene& world, 
            int& cameraSpeed, 
            Time::FramerateManager& framerateManager)
        {
            inputManager.getAction("CamLeft").connect([&world, &cameraSpeed, &framerateManager](const Input::InputActionEvent& event)
            {
                world.getCamera()->move(Transform::UnitVector(-cameraSpeed * framerateManager.getGameSpeed(), 0, Transform::Units::WorldPixels));
            });
            inputManager.getAction("CamRight").connect([&world, &cameraSpeed, &framerateManager](const Input::InputActionEvent& event)
            {
                world.getCamera()->move(Transform::UnitVector(cameraSpeed * framerateManager.getGameSpeed(), 0, Transform::Units::WorldPixels));
            });
            inputManager.getAction("CamUp").connect([&world, &cameraSpeed, &framerateManager](const Input::InputActionEvent& event)
            {
                world.getCamera()->move(Transform::UnitVector(0, -cameraSpeed * framerateManager.getGameSpeed(), Transform::Units::WorldPixels));
            });
            inputManager.getAction("CamDown").connect([&world, &cameraSpeed, &framerateManager](const Input::InputActionEvent& event)
            {
                world.getCamera()->move(Transform::UnitVector(0, cameraSpeed * framerateManager.getGameSpeed(), Transform::Units::WorldPixels));
            });
            inputManager.getAction("CamDash").connect([&cameraSpeed](const Input::InputActionEvent& event)
            {
                cameraSpeed = Transform::UnitVector::Screen.h * 2.5;
            });
            inputManager.getAction("CamDash").connect([&cameraSpeed](const Input::InputActionEvent& event)
            {
                cameraSpeed = Transform::UnitVector::Screen.h;
            });
        }

        void connectGridActions(
            Triggers::TriggerGroup* editorTriggers,
            Input::InputManager& inputManager, 
            tgui::CheckBox::Ptr& enableGridCheckbox, 
            tgui::CheckBox::Ptr& snapGridCheckbox, 
            System::Cursor& cursor, 
            Editor::EditorGrid& editorGrid)
        {
            inputManager.getAction("MagnetizeUp").connect([enableGridCheckbox, &cursor, &editorGrid](const Input::InputActionEvent& event)
            {
                if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, 0, -1);
            });
            inputManager.getAction("MagnetizeRight").connect([enableGridCheckbox, &cursor, &editorGrid](const Input::InputActionEvent& event)
            {
                if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, 1, 0);
            });
            inputManager.getAction("MagnetizeDown").connect([enableGridCheckbox, &cursor, &editorGrid](const Input::InputActionEvent& event)
            {
                if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, 0, 1);
            });
            inputManager.getAction("MagnetizeLeft").connect([enableGridCheckbox, &cursor, &editorGrid](const Input::InputActionEvent& event)
            {
                if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, -1, 0);
            });
            inputManager.getAction("MagnetizeCursor").connect([enableGridCheckbox, &cursor, &editorGrid](const Input::InputActionEvent& event)
            {
                if (enableGridCheckbox->isChecked()) editorGrid.magnetize(cursor);
            });
            inputManager.getAction("ToggleGrid").connect([enableGridCheckbox](const Input::InputActionEvent& event)
            {
                enableGridCheckbox->isChecked() ? enableGridCheckbox->uncheck() : enableGridCheckbox->check();
            });
            inputManager.getAction("ToggleGridSnap").connect([snapGridCheckbox](const Input::InputActionEvent& event)
            {
                if (snapGridCheckbox->isEnabled())
                {
                    if (snapGridCheckbox->isChecked())
                    {
                        snapGridCheckbox->uncheck();
                    }
                    else
                    {
                        snapGridCheckbox->check();
                        
                    }
                }
            });
        }

        void connectMenuActions(
            Input::InputManager& inputManager, 
            tgui::ComboBox::Ptr editMode, 
            tgui::ComboBox::Ptr cameraMode)
        {
            inputManager.getAction("CamMovable").connect([cameraMode](const Input::InputActionEvent& event)
            {
                cameraMode->setSelectedItemByIndex(0);
            });
            inputManager.getAction("CamFree").connect([cameraMode](const Input::InputActionEvent& event)
            {
                cameraMode->setSelectedItemByIndex(1);
            });
            inputManager.getAction("SpriteMode").connect([editMode, &inputManager](const Input::InputActionEvent& event)
            {
                editMode->setSelectedItemByIndex(0);
            });
            inputManager.getAction("CollisionMode").connect([&inputManager, editMode](const Input::InputActionEvent& event)
            {
                editMode->setSelectedItemByIndex(1);
            });
        }

        void connectSaveActions(
            Triggers::TriggerGroup* editorTriggers, 
            Input::InputManager& inputManager, 
            const std::string& mapName, 
            Scene::Scene& world, 
            double& waitForMapSaving, 
            tgui::Label::Ptr savedLabel)
        {
            std::cout << "CONNECTED SAVE ACTIONS" << std::endl;
            inputManager.getAction("Save").connect([&mapName, &world, &waitForMapSaving, savedLabel](const Input::InputActionEvent& event)
            {
                std::cout << "Save Map" << std::endl;
                world.dump()->writeFile(world.getBaseFolder() + "/Data/Maps/" + mapName, true);
                if (waitForMapSaving < 0)
                {
                    savedLabel->showWithEffect(tgui::ShowAnimationType::SlideFromTop, sf::Time(sf::seconds(0.5)));
                    waitForMapSaving = 0;
                }
            });
        }
    }
}
