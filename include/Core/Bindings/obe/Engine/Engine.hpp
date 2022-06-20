#pragma once

namespace sol
{
    class state_view;
};
namespace obe::engine::bindings
{
    void load_class_engine(sol::state_view state);
    void load_class_resource_managed_object(sol::state_view state);
    void load_class_resource_manager(sol::state_view state);
};