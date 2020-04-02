#include <Bindings/System/Package/Package.hpp>

#include <System/Package.hpp>

#include <sol/sol.hpp>

namespace obe::System::Package::Bindings
{
void LoadFunctionGetPackageLocation(sol::state_view state)
{
sol::table PackageNamespace = state["obe"]["System"]["Package"].get<sol::table>();
PackageNamespace.set_function("GetPackageLocation", obe::System::Package::GetPackageLocation);}
void LoadFunctionPackageExists(sol::state_view state)
{
sol::table PackageNamespace = state["obe"]["System"]["Package"].get<sol::table>();
PackageNamespace.set_function("PackageExists", obe::System::Package::PackageExists);}
void LoadFunctionInstall(sol::state_view state)
{
sol::table PackageNamespace = state["obe"]["System"]["Package"].get<sol::table>();
PackageNamespace.set_function("Install", obe::System::Package::Install);}
void LoadFunctionLoad(sol::state_view state)
{
sol::table PackageNamespace = state["obe"]["System"]["Package"].get<sol::table>();
PackageNamespace.set_function("Load", obe::System::Package::Load);}
};