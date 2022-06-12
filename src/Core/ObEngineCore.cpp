#include <ObEngineCore.hpp>

#include <Config/Git.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/Sprite.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <System/Path.hpp>

namespace obe
{
    void InitEngine(unsigned int surfaceWidth, unsigned int surfaceHeight)
    {
        debug::init_logger();

        debug::Log->info("Using ObEngineCore (Version : {} ({}:{}))", config::OBENGINE_VERSION,
            config::OBENGINE_GIT_BRANCH, config::OBENGINE_GIT_HASH);

        Transform::UnitVector::Init(surfaceWidth, surfaceHeight);
        debug::Log->debug("<ObEngine> Initialising Position Transformers");
        graphics::init_position_transformers();

        debug::Log->debug("<ObEngine> Mounting paths");
        System::MountablePath::LoadMountFile();

        debug::Log->debug("<ObEngine> Initialising NullTexture");
        graphics::make_null_texture();

        debug::Log->info("<ObEngine> Initialisation over !");
    }
}
