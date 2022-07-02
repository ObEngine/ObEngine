#include <sol/sol.hpp>

namespace obe::script::Helpers
{
    std::unordered_map<std::string, sol::protected_function> make_all_helpers(sol::state_view lua);
    sol::protected_function fetch_from_one_of(sol::state_view lua);
    sol::protected_function rawget_from(sol::state_view lua);
    sol::protected_function len_from(sol::state_view lua);
    sol::protected_function pairs_from(sol::state_view lua);
} // namespace obe::script::Helpers