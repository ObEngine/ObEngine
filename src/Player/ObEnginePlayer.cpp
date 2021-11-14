#include <SFML/Window/VideoMode.hpp>

#include <Debug/Logger.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Modes/Game.hpp>
#include <ObEngineCore.hpp>
#include <Transform/UnitVector.hpp>

using namespace obe;

int main(int argc, char** argv)
{
    const unsigned int surfaceWidth = sf::VideoMode::getDesktopMode().width;
    const unsigned int surfaceHeight = sf::VideoMode::getDesktopMode().height;
#if defined _DEBUGi
    InitEngine(surfaceWidth, surfaceHeight);
#else
    try
    {
        InitEngine(surfaceWidth, surfaceHeight);
    }
    catch (const std::exception& e)
    {
        Debug::Log->error(e.what());
        Debug::Log->error("Error occurred while initializing ObEngine");
        return 1;
    }
#endif

    Debug::Log->info("<ObEngine> Screen surface resolution {0}x{1}",
        Transform::UnitVector::Screen.w, Transform::UnitVector::Screen.h);

#if defined _DEBUGi
    Modes::startGame();
#else
    try
    {
        Modes::startGame();
    }
    catch (const std::exception& e)
    {
        Debug::Log->error("The following error occurred while running ObEngine");
        Debug::Log->error(e.what());
        return 1;
    }
#endif

    return 0;
}
