#include <ObEngineCore.hpp>

#include <Config/Git.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/Sprite.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <System/Path.hpp>

namespace obe
{
    void init_engine(unsigned int surface_width, unsigned int surface_height)
    {
        debug::init_logger();

        debug::Log->info("Using ObEngineCore (Version : {} ({}:{}))", config::OBENGINE_VERSION,
            config::OBENGINE_GIT_BRANCH, config::OBENGINE_GIT_HASH);

        transform::UnitVector::init(surface_width, surface_height);
        debug::Log->debug("<ObEngine> Initialising Position Transformers");
        graphics::init_position_transformers();

        debug::Log->debug("<ObEngine> Mounting paths");
        system::MountablePath::load_mount_file();

        debug::Log->debug("<ObEngine> Initialising NullTexture");
        graphics::make_null_texture();

        debug::Log->info("<ObEngine> Initialisation over !");
    }
}
