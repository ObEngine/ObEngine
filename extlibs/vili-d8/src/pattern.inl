#pragma once

#include <regex>
#include <string>

#include <vld8/exceptions.hpp>

namespace vili::validator::patterns
{
    std::regex integer_re("^[-+]*[0-9]+$");
    std::regex number_re("^[+-]?([0-9]*[.])?[0-9]+$");
    std::regex ipv4_re("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-"
                       "4][0-9]|[01]?[0-9][0-9]?)$");
    std::regex ipv6_re(
        "^(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-"
        "F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}"
        "|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-"
        "9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]"
        "{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-"
        "F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,"
        "1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]"
        "{1,4}:){1,4}:((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|"
        "1{0,1}[0-9]){0,1}[0-9]))$");
    std::regex url_re(
        "^((https?|ftp|file):\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$");
    std::regex mail_re("^.+@.+$");
    std::regex hexcolor_re("^#?([a-fA-F0-9]{6}|[a-fA-F0-9]{3})$");
    std::regex date_re(
        "^(0?[1-9]|[12][0-9]|3[01])([ \/\-])(0?[1-9]|1[012])\2([0-9][0-9][0-9][0-9])(([ "
        "-])([0-1]?[0-9]|2[0-3]):[0-5]?[0-9]:[0-5]?[0-9])?$");
}

namespace vili::validator
{
    bool validate_pattern(
        std::string_view location, std::string_view pattern, const std::string& value)
    {
        if (pattern == "integer")
            return std::regex_match(value, patterns::integer_re);
        if (pattern == "number")
            return std::regex_match(value, patterns::number_re);
        if (pattern == "ipv4")
            return std::regex_match(value, patterns::ipv4_re);
        if (pattern == "ipv6")
            return std::regex_match(value, patterns::ipv6_re);
        if (pattern == "url")
            return std::regex_match(value, patterns::url_re);
        if (pattern == "mail")
            return std::regex_match(value, patterns::mail_re);
        if (pattern == "hexcolor")
            return std::regex_match(value, patterns::hexcolor_re);
        if (pattern == "date")
            return std::regex_match(value, patterns::date_re);
        throw exceptions::unknown_pattern(location, pattern, VILI_EXC_INFO);
    }
}