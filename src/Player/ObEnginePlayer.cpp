#include <SFML/Window/VideoMode.hpp>

#include <Debug/Logger.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Modes/Game.hpp>
#include <ObEngineCore.hpp>
#include <Transform/UnitVector.hpp>

#include <vili/parser.hpp>
#include <vili/writer.hpp>

using namespace obe;

int main(int argc, char** argv)
{
    const unsigned int surfaceWidth = sf::VideoMode::getDesktopMode().width;
    const unsigned int surfaceHeight = sf::VideoMode::getDesktopMode().height;
#if defined _DEBUG
    InitEngine(surfaceWidth, surfaceHeight);
#else
    try
    {
        InitEngine(surfaceWidth, surfaceHeight);
    }
    catch (const std::exception& e)
    {
        debug::Log->error(e.what());
        debug::Log->error("Error occurred while initializing ObEngine");
        return 1;
    }
#endif

    debug::Log->info("<ObEngine> Screen surface resolution {0}x{1}",
        Transform::UnitVector::Screen.w, Transform::UnitVector::Screen.h);

#if defined _DEBUG
    Modes::startGame();
#else
    try
    {
        Modes::startGame();
    }
    catch (const std::exception& e)
    {
        debug::Log->error("The following error occurred while running ObEngine");
        debug::Log->error(e.what());
        return 1;
    }
#endif

    return 0;
}
