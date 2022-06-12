#pragma once

namespace sol
{
    class state_view;
};
namespace obe::engine::Bindings
{
    void LoadClassEngine(sol::state_view state);
    void LoadClassResourceManagedObject(sol::state_view state);
    void LoadClassResourceManager(sol::state_view state);
};