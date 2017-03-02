#include "Package.hpp"

namespace obe
{
	namespace System
	{
		int on_extract_entry(const char *filename, void *arg) {
			static int i = 0;
			int n = *(int *)arg;
			printf("Extracted: %s (%d of %d)\n", filename, ++i, n);

			return 0;
		}

		std::string Package::GetPackageLocation(std::string packageName)
		{
			if (PackageExists(packageName)) {
				return (vili::DataParser("Package/Packages.vili")->at<vili::BaseAttribute>(packageName, "path")->get<std::string>());
			}
			else {
				std::cout << "<Error:Package:Package>[GetPackageLocation] : Package <" << packageName << "> does not exists" << std::endl;
			}
			return std::string();
		}

		bool Package::PackageExists(std::string packageName)
		{
			return (vili::DataParser("Package/Packages.vili")->contains(vili::Types::ComplexAttribute, packageName));
		}

		bool Package::Install(std::string packageName)
		{
			if (!PackageExists(packageName)) {
				int arg = 1000;
				std::cout << "<Package> Installing Package <" << packageName << "> ..." << std::endl;
				elz::extractZip("Package/" + packageName + ".opaque", "Package/" + packageName);
				std::cout << "<Package> Package <" << packageName << "> has been successfully installed !" << std::endl;
				vili::DataParser cPackage("Package/" + packageName + "/Opaque.vili");
				std::string realPackageName = cPackage->at<vili::BaseAttribute>("Meta", "name")->get<std::string>();
				std::string packageVersion = cPackage->at<vili::BaseAttribute>("Meta", "version")->get<std::string>();
				vili::DataParser packages("Package/Packages.vili");
				packages->createComplexAttribute(realPackageName);
				packages.at(packageName)->createBaseAttribute("version", packageVersion);
				packages.at(packageName)->createBaseAttribute("path", "Package/" + packageName);
				packages.writeFile("Package/Packages.vili");
				return true;
			}
			else {
				std::cout << "<Error:Package:Package>[Install] : Package <" << packageName << "> has already been installed !" << std::endl;
				return false;
			}
		}
		bool Package::Load(std::string packageName)
		{
			if (PackageExists(packageName)) {
				Path::basePaths.push_back("Package/" + packageName);
				std::cout << "<System> Mounting Package : " << packageName << " : " << GetPackageLocation(packageName) << std::endl;
				return true;
			}
			else {
				std::cout << "<Error:Package:Package>[Load] : Package <" << packageName << "> does not exists" << std::endl;
				return false;
			}
		}
	}
}
