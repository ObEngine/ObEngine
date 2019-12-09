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
        LoaderMultipleResult loadResult
            = Path("Data/config.cfg.vili")
                  .loadAll(System::Loaders::dataLoader, Config);
        for (const std::string path : loadResult.paths())
        {
            Debug::Log->info("Loaded config file from {}", path);
        }
        std::reverse(Path::MountedPaths.begin(), Path::MountedPaths.end());
    }
} // namespace obe::System