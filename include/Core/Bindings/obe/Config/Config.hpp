#pragma once

namespace sol
{
    class state_view;
};
namespace obe::config::Bindings
{
    void LoadClassConfigurationManager(sol::state_view state);
    void LoadClassVersion(sol::state_view state);
};