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
        std::reverse(
            System::Path::MountedPaths.begin(), System::Path::MountedPaths.end());
        const System::LoaderMultipleResult loadResult
            = System::Path("Data/config.cfg.vili")
                  .loadAll(System::Loaders::dataLoader, m_config);
        for (const std::string path : loadResult.paths())
        {
            Debug::Log->info("Loaded config file from {}", path);
        }
        std::reverse(
            System::Path::MountedPaths.begin(), System::Path::MountedPaths.end());
    }
    vili::ComplexNode& ConfigurationManager::get() const
    {
        return m_config.root();
    }
} // namespace obe::System