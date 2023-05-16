#include <Bindings/obe/utils/terminal/Terminal.hpp>

#include <Utils/Terminal.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::terminal::bindings
{
    void load_function_styled_print(sol::state_view state)
    {
        sol::table terminal_namespace = state["obe"]["utils"]["terminal"].get<sol::table>();
        terminal_namespace.set_function("styled_print", &obe::utils::terminal::styled_print);
    }
};