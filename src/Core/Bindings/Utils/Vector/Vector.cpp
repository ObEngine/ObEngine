#include <Bindings/Utils/Vector/Vector.hpp>

#include <Utils/VectorUtils.hpp>

#include <sol/sol.hpp>

namespace obe::Utils::Vector::Bindings
{
    void LoadFunctionJoin(sol::state_view state)
    {
        sol::table VectorNamespace = state["obe"]["Utils"]["Vector"].get<sol::table>();
        VectorNamespace.set_function("join", obe::Utils::Vector::join);
    }
};