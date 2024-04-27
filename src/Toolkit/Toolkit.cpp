#include <iostream>
#include <map>
#include <memory>

#include <styler/styler.hpp>

#include <Debug/Logger.hpp>
#include <Graphics/Color.hpp>
#include <Script/Scripting.hpp>
#include <System/Path.hpp>


styler::Foreground convert_color(obe::graphics::Color color)
{
    if (color.to_name() == "white")
    {
        return styler::Foreground::White;
    }
    else if (color.to_name() == "red")
    {
        return styler::Foreground::Red;
    }
    else if (color.to_name() == "green")
    {
        return styler::Foreground::Green;
    }
    else if (color.to_name() == "blue")
    {
        return styler::Foreground::Blue;
    }
    else if (color.to_name() == "yellow")
    {
        return styler::Foreground::Yellow;
    }
    else if (color.to_name() == "magenta")
    {
        return styler::Foreground::Magenta;
    }
    else if (color.to_name() == "cyan")
    {
        return styler::Foreground::Cyan;
    }
    else if (color.to_name() == "black")
    {
        return styler::Foreground::Black;
    }
    else
    {
        return styler::Foreground::White;
    }
}

void run(std::string command)
{
    using namespace obe;

    debug::init_logger(false);
    debug::Log->set_level(spdlog::level::warn);
    system::MountablePath::load_mount_file(false, true);
}

int main(int argc, char** argv)
{
    using namespace obe;

    std::string command;
    std::for_each(argv + 1, argv + argc,
        [&](const char* c_str)
        {
            command += std::string(c_str) + " ";
        });

#if defined _DEBUG
    run(command);
#else
    try
    {
        run(command);
    }
    catch (const std::exception& e)
    {
        if (debug::Log)
        {
            debug::Log->error("The following error occurred while running obey");
            debug::Log->error(e.what());
        }
        else
        {
            std::cerr << "The following error occurred while running obey" << std::endl;
            std::cerr << e.what() << std::endl;
        }
        return 1;
    }
#endif

    return 0;
}
