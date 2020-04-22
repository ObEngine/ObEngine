#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Utils::Map::Bindings
{
    void LoadFunctionValueInMap(sol::state_view state);
    void LoadFunctionKeyInMap(sol::state_view state);
    void LoadFunctionGetKeys(sol::state_view state);
};