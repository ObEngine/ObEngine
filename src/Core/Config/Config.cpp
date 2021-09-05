#include <vili/parser.hpp>
#include <vld8/validator.hpp>

#include <Config/Config.hpp>
#include <Config/Templates/Config.hpp>
#include <Config/Validators.hpp>
#include <Debug/Logger.hpp>
#include <System/Path.hpp>
#include <Utils/FileUtils.hpp>


namespace obe::Config
{
    ConfigurationManager::ConfigurationManager()
        : vili::node(vili::object {})
    {
    }
    void ConfigurationManager::load()
    {
        System::MountList configMounts;
        const auto& allMounts = System::MountablePath::Paths();
        std::set<std::string> canonicalPaths;
        for (auto mountIt = allMounts.rbegin(); mountIt != allMounts.rend(); ++mountIt)
        {
            const std::string basePath
                = mountIt->get()->basePath;
            if (canonicalPaths.find(basePath) == canonicalPaths.end())
            {
                configMounts.push_back(std::make_shared<System::MountablePath>(
                    System::MountablePathType::Path, basePath,
                    mountIt->get()->prefix, 0,
                    true));
                canonicalPaths.emplace(basePath);
            }
        }
        const auto loadResult
            = System::Path(configMounts).set("*://config.cfg.vili").findAll();
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