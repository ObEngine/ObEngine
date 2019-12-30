#include <fstream>
#include <iostream>

#include <vili/Vili.hpp>

#include <SFML/Window/VideoMode.hpp>

#include <Bindings/Bindings.hpp>
#include <Config/Config.hpp>
#include <Config/Git.hpp>
#include <Debug/Logger.hpp>
#include <Editor/MapEditor.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/KeyList.hpp>
#include <Modes/Game.hpp>
#include <Modes/Menu.hpp>
#include <Modes/Toolkit.hpp>
#include <ObEngineCore.hpp>
#include <ObEngineDev.hpp>
#include <Script/GlobalState.hpp>
#include <System/MountablePath.hpp>
#include <System/Plugin.hpp>
#include <Transform/UnitVector.hpp>
#include <Utils/ExecUtils.hpp>

void LoadErrors()
{
    aube::LoadErrors("Data/Errors.vili");
}

using namespace obe;

int main(int argc, char** argv)
{
    unsigned int surfaceWidth = sf::VideoMode::getDesktopMode().width;
    unsigned int surfaceHeight = sf::VideoMode::getDesktopMode().height;
    InitEngine(surfaceWidth, surfaceHeight);

    Debug::Log->debug("<ObEngine> Initialising UnitVector Screen Surface");

    Debug::Log->info("<ObEngine> Screen surface resolution {0}x{1}",
        Transform::UnitVector::Screen.w, Transform::UnitVector::Screen.h);

    Utils::Exec::RunArgsParser runParser(argc, argv);
    const std::string startMode = runParser.getArgumentValue("-mode");
    Debug::Log->debug("Running ObEngine with mode {}", startMode);

    if (startMode == "edit")
    {
        Debug::Log->info("<ObEngine> Starting ObEngine MapEditor");
        const std::string editMapName = Modes::chooseMapMenu();
        if (editMapName != "")
            Editor::editMap(editMapName);
        // Editor::startEditor();
    }
    else if (startMode == "play")
    {
        Debug::Log->info("<ObEngine> Starting ObEngine Player");
        Modes::startGame();
    }
    else if (startMode == "toolkit")
    {
        Debug::Log->info("<ObEngine> Starting ObEngine Toolkit");
        Modes::startToolkitMode();
    }
    else if (startMode == "dev")
    {
        Debug::Log->info("<ObEngine> Starting ObEngine Development Menu");
        Modes::startDevMenu();
    }
    else
    {
        Debug::Log->warn("<ObEngine> Unknown mode '{0}', starting ObEngine Dev "
                         "Menu by default",
            startMode);
        Modes::startDevMenu();
    }

    return 0;
}
