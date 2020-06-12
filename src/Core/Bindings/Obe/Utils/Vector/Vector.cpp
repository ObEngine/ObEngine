#include <Bindings/obe/Utils/Vector/Vector.hpp>

#include <Utils/VectorUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::Utils::Vector::Bindings
{
    void LoadFunctionContains(sol::state_view state)
    {
        sol::table VectorNamespace = state["obe"]["Utils"]["Vector"].get<sol::table>();
        VectorNamespace.set_function("obe::Utils::Vector::contains",
            sol::overload(static_cast<bool (*)(int, const std::vector<int>&)>(
                              obe::Utils::Vector::contains),
                static_cast<bool (*)(double, const std::vector<double>&)>(
                    obe::Utils::Vector::contains),
                static_cast<bool (*)(std::string, const std::vector<std::string>&)>(
                    obe::Utils::Vector::contains),
                static_cast<bool (*)(bool, const std::vector<bool>&)>(
                    obe::Utils::Vector::contains)));
    }
    void LoadFunctionJoin(sol::state_view state)
    {
        sol::table VectorNamespace = state["obe"]["Utils"]["Vector"].get<sol::table>();
        VectorNamespace.set_function("join", obe::Utils::Vector::join);
    }
};