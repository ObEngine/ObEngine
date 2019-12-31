#include <ObEngineCore.hpp>

#include <Audio/AudioManager.hpp>
#include <Bindings/Bindings.hpp>
#include <Config/Config.hpp>
#include <Config/Git.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/KeyList.hpp>
#include <Script/GlobalState.hpp>
#include <System/Path.hpp>
#include <System/Plugin.hpp>

#include <soloud/soloud.h>
#include <vili/ErrorHandler.hpp>
#include <vili/ViliParser.hpp>

namespace obe
{
    void InitEngine(unsigned int surfaceWidth, unsigned int surfaceHeight)
    {
        Debug::InitLogger();
        Debug::Log->debug("<ObEngine> Storing Obe.vili in cache");
        vili::ViliParser::StoreInCache("Obe.vili");

        Debug::Log->info("Using ObEngineCore (Version : {} ({}:{}))",
            Config::OBENGINE_VERSION, Config::OBENGINE_GIT_BRANCH,
            Config::OBENGINE_GIT_HASH);

        Transform::UnitVector::Init(surfaceWidth, surfaceHeight);
        Debug::Log->debug("<ObEngine> Initialising Position Transformers");
        Graphics::InitPositionTransformer();
        Debug::Log->debug("<ObEngine> Initialising Input Handling");
        Input::InitKeyList();

        Debug::Log->debug("<ObEngine> Initialising Errors Handling");
        aube::LoadErrors("Data/Errors.vili");
        Debug::Log->debug("<ObEngine> Mounting paths");
        System::MountPaths();
        Debug::Log->debug("<ObEngine> Loading Configuration");
        Config::InitConfiguration();
        Debug::InitLoggerLevel();
        System::IndexPlugins();

        Debug::Log->debug("<ObEngine> Indexing ObEngine Lua Bindings");
        Bindings::IndexBindings();
        Debug::Log->debug("<ObEngine> Initialising Lua State");
        Script::InitScriptEngine();

        Debug::Log->debug("<ObEngine> Loading ResourceManager");
        Graphics::ResourceManager::GetInstance();

        Debug::Log->debug("<ObEngine> Loading Audio Engine");
        Audio::AudioManager::GetInstance();

        Input::InputButtonMonitor::InitKeyTriggerGroup();

        Debug::Log->info("<ObEngine> Initialisation over !");
    }
}