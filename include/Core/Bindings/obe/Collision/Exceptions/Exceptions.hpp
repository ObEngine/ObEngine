#pragma once

namespace sol
{
    class state_view;
};
namespace obe::collision::Exceptions::bindings
{
    void load_class_invalid_tag_format(sol::state_view state);
};