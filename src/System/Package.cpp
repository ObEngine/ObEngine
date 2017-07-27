#include <System/Package.hpp>
#include <System/Path.hpp>
#include <Utils/FileUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace System
    {
        namespace Package
        {
            std::string GetPackageLocation(const std::string& packageName)
            {
                if (PackageExists(packageName))
                {
                    return (vili::ViliParser("Package/Packages.vili")->at<vili::DataNode>(packageName, "path").get<std::string>());
                }
                throw aube::ErrorHandler::Raise("ObEngine.Package.Package.InexistantPackage", {{"function", "GetPackageLocation"},{"package", packageName}});
            }

            bool PackageExists(const std::string& packageName)
            {
                return (vili::ViliParser("Package/Packages.vili")->contains(vili::NodeType::ComplexNode, packageName));
            }

            bool Install(const std::string& packageName)
            {
                if (!Utils::Vector::isInList(packageName + ".opaque", Utils::File::getFileList("Package")))
                    throw aube::ErrorHandler::Raise("ObEngine.Package.Package.CantFindPackage", {{"package", packageName}});
                if (!PackageExists(packageName))
                {
                    elz::extractFile("Package/" + packageName + ".opaque", "Opaque.vili", "Package/Opaque.vili");
                    vili::ViliParser cPackage("Package/Opaque.vili");
                    std::string realPackageName = cPackage.at<vili::DataNode>("Meta", "name").get<std::string>();
                    std::string packageVersion = cPackage.at<vili::DataNode>("Meta", "version").get<std::string>();
                    std::cout << "<Package> Installing Package <" << packageName << "> ..." << std::endl;
                    elz::extractZip("Package/" + packageName + ".opaque", "Package/" + realPackageName);
                    std::cout << "<Package> Package <" << packageName << "> has been successfully installed !" << std::endl;

                    vili::ViliParser packages("Package/Packages.vili");
                    packages->createComplexNode(realPackageName);
                    packages.at(realPackageName).createDataNode("version", packageVersion);
                    packages.at(realPackageName).createDataNode("path", "Package/" + realPackageName);
                    packages.writeFile("Package/Packages.vili");
                    return true;
                }
                throw aube::ErrorHandler::Raise("ObEngine.Package.Package.AlreadyInstalled", {{"package", packageName}});
            }

            bool Load(const std::string& packageName, unsigned int priority)
            {
                if (PackageExists(packageName))
                {
                    Path::Mount(MountablePath(PathType::Package, GetPackageLocation(packageName), priority));
                    std::cout << "<System> Mounting Package : " << packageName << " : " << GetPackageLocation(packageName) << std::endl;
                    return true;
                }
                throw aube::ErrorHandler::Raise("ObEngine.Package.Package.InexistantPackage", {{"function", "Load"}, {"package", packageName}});
            }
        }
    }
}
