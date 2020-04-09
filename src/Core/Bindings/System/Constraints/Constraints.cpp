#include <Bindings/System/Constraints/Constraints.hpp>

#include <System/Cursor.hpp>

#include <sol/sol.hpp>

namespace obe::System::Constraints::Bindings
{
    void LoadGlobalDefault(sol::state_view state)
    {
        sol::table ConstraintsNamespace
            = state["obe"]["System"]["Constraints"].get<sol::table>();
        ConstraintsNamespace["Default"] = obe::System::Constraints::Default;
    }
};