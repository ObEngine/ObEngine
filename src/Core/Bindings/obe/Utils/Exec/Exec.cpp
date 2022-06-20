#include <Bindings/obe/utils/exec/Exec.hpp>

#include <Utils/ExecUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::exec::bindings
{
    void load_class_run_args_parser(sol::state_view state)
    {
        sol::table exec_namespace = state["obe"]["utils"]["exec"].get<sol::table>();
        sol::usertype<obe::utils::exec::RunArgsParser> bind_run_args_parser
            = exec_namespace.new_usertype<obe::utils::exec::RunArgsParser>("RunArgsParser",
                sol::call_constructor,
                sol::constructors<obe::utils::exec::RunArgsParser(int, char**)>());
        bind_run_args_parser["argument_exists"] = &obe::utils::exec::RunArgsParser::argument_exists;
        bind_run_args_parser["get_argument_value"]
            = &obe::utils::exec::RunArgsParser::get_argument_value;
    }
};