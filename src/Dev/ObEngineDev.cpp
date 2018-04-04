#include <fstream>
#include <iostream>

#include <vili/Vili.hpp>
#include <QGuiApplication>
#include <SFML/Window/VideoMode.hpp>

#include <Backend/Backend.hpp>
#include <Bindings/Bindings.hpp>
#include <Debug/Logger.hpp>
#include <Editor/MapEditor.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Input/KeyList.hpp>
#include <Modes/Game.hpp>
#include <Modes/Menu.hpp>
#include <Modes/Toolkit.hpp>
#include <ObEngineDev.hpp>
#include <Script/GlobalState.hpp>
#include <System/Config.hpp>
#include <System/MountablePath.hpp>
#include <Transform/UnitVector.hpp>
#include <Utils/ExecUtils.hpp>

void LoadErrors()
{
    aube::LoadErrors("Data/Errors.vili");
}

using namespace obe;

int main(int argc, char** argv)
{
	QGuiApplication app(argc, argv);
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    Backend::RegisterTypes();

    Utils::Exec::RunArgsParser runParser(argc, argv);
	const std::string startMode = runParser.getArgumentValue("-mode");
    std::cout << "Running ObEngine using mode : " << startMode << std::endl;

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

    Debug::Log->debug("<ObEngine> Indexing ObEngine Lua Bindings");
    Bindings::IndexBindings();
    Debug::Log->debug("<ObEngine> Initialising Lua State");
    Script::InitScriptEngine();
    Debug::Log->debug("<ObEngine> Loading NoTexture asset");
    Graphics::ResourceManager::GetTexture("Sprites/Others/notexture.png");

    Debug::Log->info("<ObEngine> Initialisation over ! Starting ObEngine");

    if (startMode == "edit")
    {
        Debug::Log->info("<ObEngine> Starting ObEngine MapEditor");
	    const std::string editMapName = Modes::chooseMapMenu();
        if (editMapName != "")
            Editor::editMap(editMapName);
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
