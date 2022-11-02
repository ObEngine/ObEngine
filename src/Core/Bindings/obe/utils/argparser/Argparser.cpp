#include <Bindings/obe/utils/argparser/Argparser.hpp>

#include <Utils/ArgParser.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::argparser::bindings
{
    void load_function_parse_args(sol::state_view state)
    {
        sol::table argparser_namespace = state["obe"]["utils"]["argparser"].get<sol::table>();
        argparser_namespace.set_function("parse_args", &obe::utils::argparser::parse_args);
    }
};