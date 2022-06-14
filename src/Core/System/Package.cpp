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
        throw Exceptions::UnknownPackage(package_name, list_packages(), EXC_INFO);
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
        if (!Utils::Vector::contains(package_name + ".opaque", Utils::File::get_file_list("Package")))
        {
            throw Exceptions::PackageFileNotFound(
                fmt::format("Package/{}.opaque", package_name), EXC_INFO);
        }

        if (!package_exists(package_name))
        {
            throw std::runtime_error(
                "Invalid feature: Package installation has been disabled for >v0.4");
        }
        throw Exceptions::PackageAlreadyInstalled(package_name, EXC_INFO);
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
        throw Exceptions::UnknownPackage(package_name, list_packages(), EXC_INFO);
    }
} // namespace obe::system::package
