#include <Bindings/obe/utils/types/Types.hpp>

#include <Utils/TypeUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::types::bindings
{
    void load_function_get_type_name(sol::state_view state)
    {
        sol::table types_namespace = state["obe"]["utils"]["types"].get<sol::table>();
    }
};