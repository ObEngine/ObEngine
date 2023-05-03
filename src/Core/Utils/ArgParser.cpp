#include <Utils/ArgParser.hpp>

#include <vili/parser.hpp>

namespace obe::utils::argparser
{
    /// @brief Test string to see if it is a bool value
    /// @param str string value to test
    /// @return true if is a bool, false if not
    bool is_bool(std::string str)
    {
        bool b = false;
        std::transform(str.begin(), str.end(), str.begin(),
        [](unsigned char c){ return std::tolower(c); });
        if (str.rfind("true", 0) == 0 || str.rfind("false", 0) == 0) {
            b = true;
        }

        return b;
    }

    /// @brief Determines if a string value contains a numeric value
    /// @tparam Numeric type of numeric to test for (int,float, etc.)
    /// @param str string value to test
    /// @return true if is numeric type, false if not
    template<typename Numeric>
    bool is_numeric(const std::string& str)
    {
        Numeric n;
        return((std::istringstream(str) >> n >> std::ws).eof());
    }

    /// @brief Converts string value to bool value
    /// @param str string to be converted
    /// @return boolean value converted from string
    bool to_bool(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        std::istringstream is(str);
        bool b;
        is >> std::boolalpha >> b;
        return b;
    }

    /// @brief Converts string value representing argv[idx] into expected C-type, before converting to vili type
    /// @param argvalue string value representing arguvment value to-be converted
    /// @return vili::node representing converted value from string to C-type/vili type
    vili::node smart_argument_value(std::string argvalue)
    {
        vili::node ret = argvalue;

        if(std::isalpha(argvalue[0])) {
            // bool:
            if(is_bool(argvalue)) {
                bool bv = to_bool(argvalue);
                ret = bv;
            }
        }
        else {
            // int or float
            if(is_numeric<int>(argvalue))
            {
                ret = atoi(argvalue.c_str());
            }
            else if(is_numeric<float>(argvalue))
            {
                ret = atof(argvalue.c_str());
            }
        }

        return ret;
    }

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
                throw exceptions::InvalidArgumentFormat(argument_name);
            }
            if (idx + 1 >= argv.size())
            {
                throw exceptions::InvalidArgumentFormat(argument_name);
            }
            vili::node argument_value = smart_argument_value(argv[idx + 1]);
            argstore.insert(argument_name_strip, argument_value);
        }
        return argstore;
    }
}
