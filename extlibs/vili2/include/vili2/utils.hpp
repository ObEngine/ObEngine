#pragma once

#include <string>
#include <string_view>

namespace vili::utils::string
{
    std::string replace(
        std::string subject, const std::string& search, const std::string& replace);
    bool is_int(const std::string& str);
    bool is_float(const std::string& str);
    std::string truncate_float(const std::string& str);
    std::string quote(const std::string& str);
    double to_double(std::string_view input);
    long long to_long(std::string_view input);
}