#pragma once

#include <sstream>
#include <string>
#include <vector>

#include <nlohmann/fifo_map.hpp>

namespace vili
{
    constexpr std::string_view true_value = "true";
    constexpr std::string_view false_value = "false";
    constexpr std::string_view bool_type = "boolean";
    constexpr std::string_view int_type = "integer";
    constexpr std::string_view float_type = "number";
    constexpr std::string_view string_type = "string";
    constexpr std::string_view object_type = "object";
    constexpr std::string_view array_type = "array";

    class node;

    using null = void*;

    using object = nlohmann::fifo_map<std::string, node>;
    using array = std::vector<node>;
    using integer = long long int;
    using number = double;
    using boolean = bool;
    using string = std::string;

    /**
     * \brief An enum representing Types of existing Nodes
     */
    enum class node_type
    {
        null,
        string,
        integer,
        number,
        boolean,
        array,
        object,
    };

    // clang-format off
    template <node_type N> struct node_helper_t;
    template <> struct node_helper_t<node_type::null>    { static null    type; };
    template <> struct node_helper_t<node_type::string>  { static string  type; };
    template <> struct node_helper_t<node_type::integer> { static integer type; };
    template <> struct node_helper_t<node_type::number>  { static number  type; };
    template <> struct node_helper_t<node_type::boolean> { static boolean type; };
    template <> struct node_helper_t<node_type::array>   { static array   type; };
    template <> struct node_helper_t<node_type::object>  { static object  type; };
    // clang-format on

    std::ostream& operator<<(std::ostream& os, const node_type& m);

    node_type from_string(std::string_view type);
    std::string to_string(node_type type);
    node_type from_value(std::string_view value);
}
