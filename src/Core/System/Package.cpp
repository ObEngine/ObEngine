#include <elzip/elzip.hpp>
#include <vili/ViliParser.hpp>

#include <System/Package.hpp>
#include <System/Path.hpp>
#include <Utils/FileUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::System::Package
{
    std::string GetPackageLocation(const std::string& packageName)
    {
        if (PackageExists(packageName))
        {
            return (vili::ViliParser("Package/Packages.vili")
                        ->at<vili::DataNode>(packageName, "path")
                        .get<std::string>());
        }
        throw Exceptions::UnknownPackage(packageName, ListPackages(), EXC_INFO);
    }

    bool PackageExists(const std::string& packageName)
    {
        return (vili::ViliParser("Package/Packages.vili")
                    ->contains(vili::NodeType::ComplexNode, packageName));
    }

    std::vector<std::string> ListPackages()
    {
        const vili::ViliParser packages("Package/Packages.vili");
        auto nodes = packages->getAll(vili::NodeType::ComplexNode);
        std::vector<std::string> packageNames;
        std::transform(nodes.begin(), nodes.end(), std::back_inserter(packageNames),
            [](const vili::Node* node) { return node->getId(); });
        return packageNames;
    }

    bool Install(const std::string& packageName)
    {
        Debug::Log->info("<Package> Installing Package '{0}'", packageName);
        if (!Utils::Vector::contains(
                packageName + ".opaque", Utils::File::getFileList("Package")))
        {
            throw Exceptions::PackageFileNotFound(
                fmt::format("Package/{}.opaque", packageName), EXC_INFO);
        }

        if (!PackageExists(packageName))
        {
            elz::extractFile("Package/" + packageName + ".opaque", "Opaque.vili",
                "Package/Opaque.vili");
            vili::ViliParser cPackage("Package/Opaque.vili");
            const std::string realPackageName
                = cPackage.at<vili::DataNode>("Meta", "name").get<std::string>();
            const std::string packageVersion
                = cPackage.at<vili::DataNode>("Meta", "version").get<std::string>();
            elz::extractZip(
                "Package/" + packageName + ".opaque", "Package/" + realPackageName);
            Debug::Log->info(
                "<Package> Package '{0}' has been successfully installed", packageName);

            vili::ViliParser packages("Package/Packages.vili");
            packages->createComplexNode(realPackageName);
            packages.at(realPackageName).createDataNode("version", packageVersion);
            packages.at(realPackageName)
                .createDataNode("path", "Package/" + realPackageName);
            packages.writeFile("Package/Packages.vili");
            return true;
        }
        throw Exceptions::PackageAlreadyInstalled(packageName, EXC_INFO);
    }

    bool Load(const std::string& packageName, const unsigned int priority)
    {
        Debug::Log->info(
            "<Package> Loading Package '{0}' with priority", packageName, priority);
        if (PackageExists(packageName))
        {
            MountablePath::Mount(MountablePath(
                MountablePathType::Package, GetPackageLocation(packageName), priority));
            return true;
        }
        throw Exceptions::UnknownPackage(packageName, ListPackages(), EXC_INFO);
    }
} // namespace obe::System::Package
