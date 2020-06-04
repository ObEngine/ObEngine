#include "System/Path.hpp"

#include <fstream>
#include <iostream>

#include <SFML/Window/VideoMode.hpp>

#include <Config/Config.hpp>
#include <Debug/Logger.hpp>
#include <Exception.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Modes/Game.hpp>
#include <ObEngineCore.hpp>
#include <System/MountablePath.hpp>
#include <System/Plugin.hpp>
#include <Transform/UnitVector.hpp>

using namespace obe;

int main(int argc, char** argv)
{
    const unsigned int surfaceWidth = sf::VideoMode::getDesktopMode().width;
    const unsigned int surfaceHeight = sf::VideoMode::getDesktopMode().height;
    try
    {
        InitEngine(surfaceWidth, surfaceHeight);
    }
    catch (Exception& e)
    {
        Debug::Log->error(e.what());
        Debug::Log->error("Error occured while initializing ObEngine");
    }

    Debug::Log->info("<ObEngine> Screen surface resolution {0}x{1}",
        Transform::UnitVector::Screen.w, Transform::UnitVector::Screen.h);
    // Modes::startGame();
    try
    {
        Modes::startGame();
    }
    catch (std::exception& e)
    {
        Debug::Log->error(e.what());
        Debug::Log->error("Error occured while running ObEngine");
    }
    return 0;
}
