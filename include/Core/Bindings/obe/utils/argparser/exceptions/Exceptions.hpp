#pragma once

namespace sol
{
    class state_view;
};
namespace obe::utils::argparser::exceptions::bindings
{
    void load_class_invalid_argument_format(sol::state_view state);
};