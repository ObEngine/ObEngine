#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <TGUI/Animation.hpp>

#include <Editor/EditorGlobalActions.hpp>

namespace obe
{
    namespace Editor
    {
        void connectCamMovementActions(Input::InputManager& inputManager, Scene::Scene& world, int& cameraSpeed, Time::FramerateManager& framerateManager)
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

        void connectMagnetActions(Input::InputManager& inputManager, tgui::CheckBox::Ptr& enableGridCheckbox, System::Cursor& cursor, Editor::EditorGrid& editorGrid)
        {
            inputManager.getAction("MagnetizeUp").connect([&enableGridCheckbox, &cursor, &editorGrid](const Input::InputActionEvent& event)
            {
                if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, 0, -1);
            });
            inputManager.getAction("MagnetizeRight").connect([&enableGridCheckbox, &cursor, &editorGrid](const Input::InputActionEvent& event)
            {
                if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, 1, 0);
            });
            inputManager.getAction("MagnetizeDown").connect([&enableGridCheckbox, &cursor, &editorGrid](const Input::InputActionEvent& event)
            {
                if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, 0, 1);
            });
            inputManager.getAction("MagnetizeLeft").connect([&enableGridCheckbox, &cursor, &editorGrid](const Input::InputActionEvent& event)
            {
                if (enableGridCheckbox->isChecked()) editorGrid.moveMagnet(cursor, -1, 0);
            });
            inputManager.getAction("MagnetizeCursor").connect([&enableGridCheckbox, &cursor, &editorGrid](const Input::InputActionEvent& event)
            {
                if (enableGridCheckbox->isChecked()) editorGrid.magnetize(cursor);
            });
        }

        void connectMenuActions(Input::InputManager& inputManager, tgui::ComboBox::Ptr editMode, tgui::ComboBox::Ptr cameraMode)
        {
            inputManager.getAction("CamMovable").connect([cameraMode](const Input::InputActionEvent& event)
            {
                cameraMode->setSelectedItemByIndex(0);
            });
            inputManager.getAction("CamFree").connect([cameraMode](const Input::InputActionEvent& event)
            {
                cameraMode->setSelectedItemByIndex(1);
            });
            inputManager.getAction("SpriteMode").connect([editMode](const Input::InputActionEvent& event)
            {
                editMode->setSelectedItemByIndex(0);
            });
            inputManager.getAction("CollisionMode").connect([editMode](const Input::InputActionEvent& event)
            {
                editMode->setSelectedItemByIndex(1);
            });
        }

        void connectSaveActions(Input::InputManager& inputManager, const std::string& mapName, Scene::Scene& world, double& waitForMapSaving, tgui::Label::Ptr savedLabel)
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
