#include <vili/parser.hpp>
#include <vld8/validator.hpp>

#include <Config/Config.hpp>
#include <Config/Templates/Config.hpp>
#include <Config/Validators.hpp>
#include <System/Path.hpp>

namespace obe::Config
{
    ConfigurationManager::ConfigurationManager()
        : vili::node(vili::object {})
    {
    }
    void ConfigurationManager::load()
    {
        // TODO: Do not modify MountedPaths directly
        auto mountPoints = System::MountablePath::Paths();
        std::reverse(mountPoints.begin(), mountPoints.end());
        const auto loadResult
            = System::Path(mountPoints).set("*://Data/config.cfg.vili").findAll();
        for (const auto& findResult : loadResult)
        {
            Debug::Log->info("Loading config file from {}", findResult.path());
            vili::node conf
                = vili::parser::from_file(findResult.path(), Templates::getConfigTemplates());
            this->merge(conf);
        }
        vili::validator::validate_tree(Validators::ConfigValidator(), *this);
    }
} // namespace obe::System