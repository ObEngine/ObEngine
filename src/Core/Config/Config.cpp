#include <Config/Config.hpp>
#include <System/Path.hpp>

#include <Debug/Logger.hpp>

namespace obe::Config
{
    ConfigurationManager Config;
    ConfigurationManager::ConfigurationManager()
    {
    }
    void ConfigurationManager::load()
    {
        // TODO: Do not modify MountedPaths directly
        auto mountPoints = System::MountablePath::Paths();
        std::reverse(mountPoints.begin(), mountPoints.end());
        const System::LoaderMultipleResult loadResult
            = System::Path(mountPoints)
                  .set("Data/config.cfg.vili")
                  .loadAll(System::Loaders::dataLoader, m_config, false);
        for (const std::string path : loadResult.paths())
        {
            Debug::Log->info("Loaded config file from {}", path);
        }
    }
    vili::ComplexNode& ConfigurationManager::get() const
    {
        return m_config.root();
    }
} // namespace obe::System