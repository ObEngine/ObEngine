#include <fstream>
#include <iostream>

#include <vili/Vili.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <Bindings/Bindings.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/KeyList.hpp>
#include <Modes/Game.hpp>
#include <System/Config.hpp>
#include <System/MountablePath.hpp>
#include <System/Plugin.hpp>
#include <Transform/UnitVector.hpp>

void LoadErrors()
{
    aube::LoadErrors("Data/Errors.vili");
}

using namespace obe;

int main(int argc, char** argv)
{
    Graphics::ResourceManager::Init();
    Debug::InitLogger();
    Debug::Log->debug("<ObEngine> Storing Obe.vili in cache");
    vili::ViliParser::StoreInCache("Obe.vili");

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

    Input::InputButtonMonitor::InitKeyTriggerGroup();

    Debug::Log->info("<ObEngine> Initialisation over ! Starting ObEngine");

    Modes::startGame();
    return 0;
}
