#include <elzip/elzip.hpp>
#include <vili/parser.hpp>

#include <Debug/Logger.hpp>
#include <System/Package.hpp>
#include <System/Path.hpp>
#include <Utils/FileUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::system::package
{
    std::string get_package_location(const std::string& package_name)
    {
        if (package_exists(package_name))
        {
            return vili::parser::from_file("obe://Packages/packages.vili"_fs)
                .at(package_name)
                .at("path");
        }
        throw exceptions::UnknownPackage(package_name, list_packages());
    }

    bool package_exists(const std::string& package_name)
    {
        return vili::parser::from_file("obe://Packages/packages.vili"_fs).contains(package_name);
    }

    std::vector<std::string> list_packages()
    {
        vili::node packages = vili::parser::from_file("obe://Packages/packages.vili"_fs);
        std::vector<std::string> package_names;
        for (const auto& [package_name, _] : packages.items())
        {
            package_names.push_back(package_name);
        }
        return package_names;
    }

    bool install(const std::string& package_name)
    {
        debug::Log->info("<Package> Installing Package '{0}'", package_name);
        if (!utils::vector::contains(
                package_name + ".opaque", utils::file::get_file_list("Package")))
        {
            throw exceptions::PackageFileNotFound(fmt::format("Package/{}.opaque", package_name));
        }

        if (!package_exists(package_name))
        {
            throw std::runtime_error(
                "Invalid feature: Package installation has been disabled for >v0.4");
        }
        throw exceptions::PackageAlreadyInstalled(package_name);
    }

    bool load(
        const std::string& package_name, const std::string& prefix, const unsigned int priority)
    {
        debug::Log->info("<Package> Loading Package '{0}' with priority", package_name, priority);
        if (package_exists(package_name))
        {
            MountablePath::mount(MountablePath(
                MountablePathType::Package, get_package_location(package_name), prefix, priority));
            return true;
        }
        throw exceptions::UnknownPackage(package_name, list_packages());
    }
} // namespace obe::system::package
