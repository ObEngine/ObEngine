#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Config::Bindings
{
    void LoadClassConfigurationManager(sol::state_view state);
    void LoadGlobalOBENGINEGITBRANCH(sol::state_view state);
    void LoadGlobalOBENGINEGITHASH(sol::state_view state);
    void LoadGlobalOBENGINEVERSION(sol::state_view state);
};