#pragma once

namespace sol
{
    class state_view;
};
namespace obe::utils::vector::bindings
{
    void load_function_contains(sol::state_view state);
    void load_function_join(sol::state_view state);
}; // namespace obe::utils::vector::bindings