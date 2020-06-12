#pragma once

namespace sol
{
    class state_view;
};
namespace obe::System::Package::Bindings
{
    void LoadFunctionGetPackageLocation(sol::state_view state);
    void LoadFunctionPackageExists(sol::state_view state);
    void LoadFunctionListPackages(sol::state_view state);
    void LoadFunctionInstall(sol::state_view state);
    void LoadFunctionLoad(sol::state_view state);
};