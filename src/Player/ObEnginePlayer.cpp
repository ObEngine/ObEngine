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
    const unsigned int surface_width = sf::VideoMode::getDesktopMode().width;
    const unsigned int surface_height = sf::VideoMode::getDesktopMode().height;
#if defined _DEBUG
    init_engine(surface_width, surface_height, true);
#else
    try
    {
        init_engine(surface_width, surface_height, true);
    }
    catch (const std::exception& e)
    {
        debug::Log->error(e.what());
        debug::Log->error("Error occurred while initializing ObEngine");
        return 1;
    }
#endif

    debug::Log->info("<ObEngine> Screen surface resolution {0}x{1}",
        transform::UnitVector::Screen.w, transform::UnitVector::Screen.h);

#if defined _DEBUG
    modes::start_game();
#else
    try
    {
        modes::start_game();
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
