#pragma once

#include <string>
#include <string_view>
#include <vector>

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

    std::string indent(
        const std::string& input, unsigned int indent_level = 4, bool pad_left = true);
    std::size_t distance(std::string_view source, std::string_view target);
    std::vector<std::string> sort_by_distance(
        const std::string& source, const std::vector<std::string>& words, std::size_t limit);
}