#include <Config/Config.hpp>
#include <System/Path.hpp>

#include <Debug/Logger.hpp>

#include <vili/parser/parser.hpp>

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
        const auto loadResult
            = System::Path(mountPoints).set("Data/config.cfg.vili").findAll();
        m_config = vili::object {};
        for (const std::string path : loadResult)
        {
            Debug::Log->info("Loading config file from {}", path);
            vili::node conf = vili::parser::from_file(path);
            m_config.merge(conf);
        }
    }
    vili::node ConfigurationManager::get() const
    {
        return m_config;
    }
} // namespace obe::System