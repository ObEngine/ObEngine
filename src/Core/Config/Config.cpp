#include <Config/Config.hpp>
#include <System/Path.hpp>

#include <Debug/Logger.hpp>

namespace obe::Config
{
    vili::ViliParser Config;

    void InitConfiguration()
    {
        Config = vili::ViliParser();
        std::reverse(System::Path::MountedPaths.begin(), System::Path::MountedPaths.end());
        System::LoaderMultipleResult loadResult
            = System::Path("Data/config.cfg.vili").loadAll(System::Loaders::dataLoader, Config);
        for (const std::string path : loadResult.paths())
        {
            Debug::Log->info("Loaded config file from {}", path);
        }
        std::reverse(System::Path::MountedPaths.begin(), System::Path::MountedPaths.end());
    }
} // namespace obe::System