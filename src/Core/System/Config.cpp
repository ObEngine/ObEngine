#include <System/Config.hpp>
#include <System/Path.hpp>

#include <Debug/Logger.hpp>

namespace obe::System
{
    vili::ViliParser Config;

    void InitConfiguration()
    {
        Config = vili::ViliParser();
        std::reverse(Path::MountedPaths.begin(), Path::MountedPaths.end());
        Path("Data/config.cfg.vili").loadAll(System::Loaders::dataLoader, Config);
        std::reverse(Path::MountedPaths.begin(), Path::MountedPaths.end());
    }
}