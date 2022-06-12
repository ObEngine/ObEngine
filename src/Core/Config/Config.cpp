#include <vili/parser.hpp>
#include <vld8/validator.hpp>

#include <Config/Config.hpp>
#include <Config/Exceptions.hpp>
#include <Config/Validators.hpp>
#include <Debug/Logger.hpp>
#include <System/Path.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::config
{
    ConfigurationManager::ConfigurationManager()
        : vili::node(vili::object {})
    {
    }
    void ConfigurationManager::load()
    {
        System::MountList config_mounts;
        const auto& all_mounts = System::MountablePath::Paths();
        std::set<std::string> canonical_paths;
        for (auto mount_it = all_mounts.rbegin(); mount_it != all_mounts.rend(); ++mount_it)
        {
            const std::string base_path = mount_it->get()->basePath;
            if (canonical_paths.find(base_path) == canonical_paths.end())
            {
                config_mounts.push_back(std::make_shared<System::MountablePath>(
                    System::MountablePathType::Path, base_path, mount_it->get()->prefix, 0, true));
                canonical_paths.emplace(base_path);
            }
        }
        const auto load_result = System::Path(config_mounts).set("*://config.vili").findAll();
        for (const auto& find_result : load_result)
        {
            debug::Log->info("Loading config file from '{}'", find_result.path());
            vili::node conf
                = vili::parser::from_file(find_result.path());
            debug::Log->trace("Configuration '{}' content : {}", find_result.path(), conf.dump());
            this->merge(conf);
        }
        try
        {
            vili::validator::validate_tree(validators::config_validator(), *this);
        }
        catch (const vili::exceptions::base_exception& e)
        {
            std::vector<std::string> config_files;
            config_files.reserve(load_result.size());
            for (const System::FindResult& path : load_result)
            {
                config_files.push_back(path.path());
            }
            throw Exceptions::ConfigError(config_files, EXC_INFO).nest(e);
        }
    }
} // namespace obe::System
