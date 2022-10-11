#include <Utils/ArgParser.hpp>

#include <vili/parser.hpp>

namespace obe::utils::argparser
{
    vili::node parse_args(const std::vector<std::string>& argv)
    {
        vili::node argstore = vili::object {};
        for (size_t idx = 1; idx < argv.size(); idx += 2)
        {
            const std::string& argument_name = argv[idx];
            const std::string& argument_name_strip = argument_name.substr(2, std::string::npos);
            const bool valid_arg_format = argument_name.starts_with("--")
                && argument_name.size() > 2 && std::isalpha(argument_name[2])
                && std::all_of(argument_name_strip.begin(), argument_name_strip.end(),
                    [](const char c) { return std::isalpha(c) || c == '-' || c == '_'; });
            if (!valid_arg_format)
            {
                throw exceptions::InvalidArgumentFormat(argument_name, EXC_INFO);
            }
            if (idx + 1 >= argv.size())
            {
                throw exceptions::InvalidArgumentFormat(argument_name, EXC_INFO);
            }
            vili::node argument_value = argv[idx + 1];
            argstore.insert(argument_name_strip, argument_value);
        }
        return argstore;
    }
}
