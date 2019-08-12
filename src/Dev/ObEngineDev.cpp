#include <fstream>
#include <iostream>

#include <vili/Vili.hpp>

#include <SFML/Window/VideoMode.hpp>

#include <Bindings/Bindings.hpp>
#include <Debug/Logger.hpp>
#include <Editor/MapEditor.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/KeyList.hpp>
#include <Modes/Game.hpp>
#include <Modes/Menu.hpp>
#include <Modes/Toolkit.hpp>
#include <ObEngineDev.hpp>
#include <Script/GlobalState.hpp>
#include <System/Config.hpp>
#include <System/MountablePath.hpp>
#include <System/Plugin.hpp>
#include <Transform/UnitVector.hpp>
#include <Utils/ExecUtils.hpp>

#include "Utils/MathUtils.hpp"
#include "Collision/PolygonalCollider.hpp"
#include <Graphics/LevelSprite.hpp>

void LoadErrors()
{
    aube::LoadErrors("Data/Errors.vili");
}

using namespace obe;

int main(int argc, char** argv)
{
    Graphics::ResourceManager::Init();
    Utils::Exec::RunArgsParser runParser(argc, argv);
    const std::string startMode = runParser.getArgumentValue("-mode");
    std::cout << "Running ObEngine using mode : " << startMode << std::endl;
    Debug::InitLogger();
    vili::ViliParser::StoreInCache("Obe.vili");

    Debug::Log->info("Running ObEngine Dev (Version : {} ({}:{}))", OBENGINE_VERSION, OBENGINE_GIT_BRANCH, OBENGINE_GIT_HASH);

    Debug::Log->debug("<ObEngine> Initialising UnitVector Screen Surface");
    Transform::UnitVector::Init(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    Debug::Log->debug("<ObEngine> Initialising Position Transformers");
    Graphics::InitPositionTransformer();
    Debug::Log->debug("<ObEngine> Initialising Input Handling");
    Input::InitKeyList();

    Debug::Log->info("<ObEngine> Screen surface resolution {0}x{1}", Transform::UnitVector::Screen.w, Transform::UnitVector::Screen.h);

    Debug::Log->debug("<ObEngine> Initialising Errors Handling");
    LoadErrors();
    Debug::Log->debug("<ObEngine> Mounting paths");
    System::MountPaths();
    System::InitConfiguration();
    Debug::InitLoggerLevel();
    System::IndexPlugins();

    Debug::Log->debug("<ObEngine> Indexing ObEngine Lua Bindings");
    Bindings::IndexBindings();
    Debug::Log->debug("<ObEngine> Initialising Lua State");
    Script::InitScriptEngine();
    Script::ScriptEngine["obe"]["version"] = OBENGINE_VERSION;
    Script::ScriptEngine["obe"]["commit"] = OBENGINE_GIT_HASH;
    Script::ScriptEngine["obe"]["branch"] = OBENGINE_GIT_BRANCH;

    Input::InputButtonMonitor::InitKeyTriggerGroup();

    Debug::Log->info("<ObEngine> Initialisation over ! Starting ObEngine");

    if (startMode == "edit")
    {
        Debug::Log->info("<ObEngine> Starting ObEngine MapEditor");
        const std::string editMapName = Modes::chooseMapMenu();
        if (editMapName != "")
            Editor::editMap(editMapName);
        //Editor::startEditor();
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
        Debug::Log->warn("<ObEngine> Unknown mode '{0}', starting ObEngine Dev Menu by default", startMode);
        Modes::startDevMenu();
    }
        

    return 0;
}
