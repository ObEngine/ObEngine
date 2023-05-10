#include <Bindings/obe/utils/vector/Vector.hpp>

#include <Utils/VectorUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::vector::bindings
{
    void load_function_contains(sol::state_view state)
    {
        sol::table vector_namespace = state["obe"]["utils"]["vector"].get<sol::table>();
        vector_namespace.set_function("contains",
            sol::overload(
                static_cast<bool (*)(int, const std::vector<int>&)>(&obe::utils::vector::contains),
                static_cast<bool (*)(double, const std::vector<double>&)>(
                    &obe::utils::vector::contains),
                static_cast<bool (*)(std::string, const std::vector<std::string>&)>(
                    &obe::utils::vector::contains),
                static_cast<bool (*)(bool, const std::vector<bool>&)>(
                    &obe::utils::vector::contains)));
    }
    void load_function_join(sol::state_view state)
    {
        sol::table vector_namespace = state["obe"]["utils"]["vector"].get<sol::table>();
        vector_namespace.set_function("join",
            sol::overload(
                [](std::vector<std::string>& vector) -> std::string
                {
                    return obe::utils::vector::join(vector);
                },
                [](std::vector<std::string>& vector, std::string sep) -> std::string
                {
                    return obe::utils::vector::join(vector, sep);
                },
                [](std::vector<std::string>& vector, std::string sep, int start) -> std::string
                {
                    return obe::utils::vector::join(vector, sep, start);
                },
                [](std::vector<std::string>& vector, std::string sep, int start,
                    int stop) -> std::string
                {
                    return obe::utils::vector::join(vector, sep, start, stop);
                }));
    }
};