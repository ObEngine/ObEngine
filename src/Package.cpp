#include "Package.hpp"

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
					return (vili::DataParser("Package/Packages.vili")->at<vili::BaseAttribute>(packageName, "path").get<std::string>());
				}
				throw aube::ErrorHandler::Raise("ObEngine.Package.Package.InexistantPackage", { {"function", "GetPackageLocation"},{"package", packageName} });
			}

			bool PackageExists(const std::string& packageName)
			{
				return (vili::DataParser("Package/Packages.vili")->contains(vili::Types::ComplexAttribute, packageName));
			}

			bool Install(const std::string& packageName)
			{
				if (!Functions::Vector::isInList(packageName + ".opaque", Functions::File::getFileList("Package")))
					throw aube::ErrorHandler::Raise("ObEngine.Package.Package.CantFindPackage", { {"package", packageName} });
				if (!PackageExists(packageName))
				{
					elz::extractFile("Package/" + packageName + ".opaque", "Opaque.vili", "Package/Opaque.vili");
					vili::DataParser cPackage("Package/Opaque.vili");
					std::string realPackageName = cPackage.at<vili::BaseAttribute>("Meta", "name").get<std::string>();
					std::string packageVersion = cPackage.at<vili::BaseAttribute>("Meta", "version").get<std::string>();
					std::cout << "<Package> Installing Package <" << packageName << "> ..." << std::endl;
					elz::extractZip("Package/" + packageName + ".opaque", "Package/" + realPackageName);
					std::cout << "<Package> Package <" << packageName << "> has been successfully installed !" << std::endl;

					vili::DataParser packages("Package/Packages.vili");
					packages->createComplexAttribute(realPackageName);
					packages.at(realPackageName).createBaseAttribute("version", packageVersion);
					packages.at(realPackageName).createBaseAttribute("path", "Package/" + realPackageName);
					packages.writeFile("Package/Packages.vili");
					return true;
				}
				throw aube::ErrorHandler::Raise("ObEngine.Package.Package.AlreadyInstalled", { {"package", packageName} });
			}

			bool Load(const std::string& packageName, unsigned int priority)
			{
				if (PackageExists(packageName))
				{
					Path::addPath(PriorizedPath(PathType::Package, GetPackageLocation(packageName), priority));
					std::cout << "<System> Mounting Package : " << packageName << " : " << GetPackageLocation(packageName) << std::endl;
					return true;
				}
				throw aube::ErrorHandler::Raise("ObEngine.Package.Package.InexistantPackage", { {"function", "Load"}, {"package", packageName} });
			}
		}
    }
}
