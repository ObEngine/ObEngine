#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Component::Exceptions::bindings
{
    void load_class_component_id_already_taken(sol::state_view state);
    void load_class_unknown_component_type(sol::state_view state);
};