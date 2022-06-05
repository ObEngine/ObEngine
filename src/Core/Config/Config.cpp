#include <vili/parser.hpp>
#include <vld8/validator.hpp>

#include <Config/Config.hpp>
#include <Config/Exceptions.hpp>
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
            const std::string basePath = mountIt->get()->basePath;
            if (canonicalPaths.find(basePath) == canonicalPaths.end())
            {
                configMounts.push_back(std::make_shared<System::MountablePath>(
                    System::MountablePathType::Path, basePath, mountIt->get()->prefix, 0, true));
                canonicalPaths.emplace(basePath);
            }
        }
        const auto loadResult = System::Path(configMounts).set("*://config.vili").findAll();
        for (const auto& findResult : loadResult)
        {
            Debug::Log->info("Loading config file from '{}'", findResult.path());
            vili::node conf
                = vili::parser::from_file(findResult.path(), Templates::getConfigTemplates());
            Debug::Log->info("Configuration '{}' content : {}", findResult.path(), conf.dump());
            this->merge(conf);
        }
        try
        {
            vili::validator::validate_tree(Validators::ConfigValidator(), *this);
        }
        catch (const vili::exceptions::base_exception& e)
        {
            std::vector<std::string> configFiles;
            configFiles.reserve(loadResult.size());
            for (const System::FindResult& path : loadResult)
            {
                configFiles.push_back(path.path());
            }
            throw Exceptions::ConfigError(configFiles, EXC_INFO).nest(e);
        }
    }
} // namespace obe::System
