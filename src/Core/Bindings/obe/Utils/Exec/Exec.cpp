#include <Bindings/obe/Utils/Exec/Exec.hpp>

#include <Utils/ExecUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::Utils::Exec::Bindings
{
    void LoadClassRunArgsParser(sol::state_view state)
    {
        sol::table ExecNamespace = state["obe"]["Utils"]["Exec"].get<sol::table>();
        sol::usertype<obe::Utils::Exec::RunArgsParser> bindRunArgsParser
            = ExecNamespace.new_usertype<obe::Utils::Exec::RunArgsParser>("RunArgsParser",
                sol::call_constructor,
                sol::constructors<obe::Utils::Exec::RunArgsParser(int, char**)>());
        bindRunArgsParser["argument_exists"] = &obe::Utils::Exec::RunArgsParser::argument_exists;
        bindRunArgsParser["get_argument_value"] = &obe::Utils::Exec::RunArgsParser::get_argument_value;
    }
};