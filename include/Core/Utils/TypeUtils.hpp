#pragma once

#ifdef __clang__
#include <experimental/source_location>
#else
#include <source_location>
#endif
#include <string>
#include <string_view>

#ifdef __clang__
namespace std
{
    using source_location = experimental::source_location;
}
#endif

namespace obe::utils::types
{
    template <typename T>
    constexpr auto get_type_name() -> std::string
    {
        std::source_location location = std::source_location::current();
        const std::string function = location.function_name();

        constexpr std::string_view prefix = "[T = ";
        constexpr std::string_view suffix = "]";

        const auto start = function.find(prefix) + prefix.size();
        const auto end = function.find(suffix);
        const auto size = end - start;

        return function.substr(start, size);
    }
}