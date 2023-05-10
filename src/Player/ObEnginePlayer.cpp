#include <SFML/Window/VideoMode.hpp>

#include <Debug/Logger.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Modes/Game.hpp>
#include <ObEngineCore.hpp>
#include <Transform/UnitVector.hpp>
#include <Utils/ArgParser.hpp>

#include <vili-msgpack/msgpack.hpp>
#include <vili/parser.hpp>
#include <vili/writer.hpp>

#include <Transform/AABB.hpp>

using namespace obe;

int main(int argc, char** argv)
{
    const unsigned int surface_width = sf::VideoMode::getDesktopMode().width;
    const unsigned int surface_height = sf::VideoMode::getDesktopMode().height;

    debug::init_logger(true);

    std::vector<std::string> argvector(argv, argv + argc);
    vili::node arguments;
    try
    {
        arguments = utils::argparser::parse_args(argvector);
    }
    catch (const std::exception& e)
    {
        debug::Log->error("Error occurred while parsing command line arguments");
        debug::Log->error(e.what());
        return 1;
    }

#if defined _DEBUG
    init_engine(surface_width, surface_height, arguments);
#else
    try
    {
        init_engine(surface_width, surface_height, arguments);
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
    modes::start_game(arguments);
#else
    try
    {
        modes::start_game(arguments);
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
