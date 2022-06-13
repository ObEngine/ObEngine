#include <Bindings/obe/System/Constraints/Constraints.hpp>

#include <System/Cursor.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::constraints::Bindings
{
    void LoadGlobalDefault(sol::state_view state)
    {
        sol::table ConstraintsNamespace = state["obe"]["system"]["constraints"].get<sol::table>();
        ConstraintsNamespace["Default"] = obe::system::constraints::Default;
    }
};