#include <Bindings/obe/Utils/Vector/Vector.hpp>

#include <Utils/VectorUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::Utils::Vector::Bindings
{
    void LoadFunctionContains(sol::state_view state)
    {
        sol::table VectorNamespace = state["obe"]["Utils"]["Vector"].get<sol::table>();
        VectorNamespace.set_function("contains",
            sol::overload(
                static_cast<bool (*)(int, const std::vector<int>&)>(&obe::Utils::Vector::contains),
                static_cast<bool (*)(double, const std::vector<double>&)>(
                    &obe::Utils::Vector::contains),
                static_cast<bool (*)(std::string, const std::vector<std::string>&)>(
                    &obe::Utils::Vector::contains),
                static_cast<bool (*)(bool, const std::vector<bool>&)>(
                    &obe::Utils::Vector::contains)));
    }
    void LoadFunctionJoin(sol::state_view state)
    {
        sol::table VectorNamespace = state["obe"]["Utils"]["Vector"].get<sol::table>();
        VectorNamespace.set_function("join",
            sol::overload([](std::vector<std::string>& vector)
                              -> std::string { return obe::Utils::Vector::join(vector); },
                [](std::vector<std::string>& vector, std::string sep) -> std::string {
                    return obe::Utils::Vector::join(vector, sep);
                },
                [](std::vector<std::string>& vector, std::string sep, int start) -> std::string {
                    return obe::Utils::Vector::join(vector, sep, start);
                },
                [](std::vector<std::string>& vector, std::string sep, int start, int stop)
                    -> std::string { return obe::Utils::Vector::join(vector, sep, start, stop); }));
    }
};