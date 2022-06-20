#include <Bindings/obe/system/constraints/Constraints.hpp>

#include <System/Cursor.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::constraints::bindings
{
    void load_global_default(sol::state_view state)
    {
        sol::table constraints_namespace = state["obe"]["system"]["constraints"].get<sol::table>();
        constraints_namespace["Default"] = obe::system::constraints::Default;
    }
};