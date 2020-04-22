#include <Bindings/Utils/Map/Map.hpp>

#include <Utils/MapUtils.hpp>

#include <sol/sol.hpp>

namespace obe::Utils::Map::Bindings
{
    void LoadFunctionValueInMap(sol::state_view state)
    {
        sol::table MapNamespace = state["obe"]["Utils"]["Map"].get<sol::table>();
    }
    void LoadFunctionKeyInMap(sol::state_view state)
    {
        sol::table MapNamespace = state["obe"]["Utils"]["Map"].get<sol::table>();
    }
    void LoadFunctionGetKeys(sol::state_view state)
    {
        sol::table MapNamespace = state["obe"]["Utils"]["Map"].get<sol::table>();
    }
};