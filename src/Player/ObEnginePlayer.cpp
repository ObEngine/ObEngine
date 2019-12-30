#include <fstream>
#include <iostream>

#include <SFML/Window/VideoMode.hpp>
#include <vili/Vili.hpp>

#include <Bindings/Bindings.hpp>
#include <Config/Config.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/KeyList.hpp>
#include <Modes/Game.hpp>
#include <ObEngineCore.hpp>
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
    unsigned int surfaceWidth = sf::VideoMode::getDesktopMode().width;
    unsigned int surfaceHeight = sf::VideoMode::getDesktopMode().height;
    InitEngine(surfaceWidth, surfaceHeight);

    Debug::Log->info("<ObEngine> Screen surface resolution {0}x{1}",
        Transform::UnitVector::Screen.w, Transform::UnitVector::Screen.h);

    Modes::startGame();
    return 0;
}
