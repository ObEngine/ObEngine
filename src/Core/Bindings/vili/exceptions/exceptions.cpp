#include <Bindings/vili/exceptions/Exceptions.hpp>

#include <vili/exceptions.hpp>

#include <Bindings/Config.hpp>

namespace vili::exceptions::bindings
{
    void load_class_array_index_overflow(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::array_index_overflow> bind_array_index_overflow
            = exceptions_namespace.new_usertype<vili::exceptions::array_index_overflow>(
                "array_index_overflow", sol::call_constructor,
                sol::constructors<vili::exceptions::array_index_overflow(
                    size_t, size_t, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::array_index_overflow>,
                    vili::exceptions::base_exception>());
    }
    void load_class_base_exception(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::base_exception> bind_base_exception
            = exceptions_namespace.new_usertype<vili::exceptions::base_exception>(
                "base_exception", sol::call_constructor, sol::default_constructor);
        bind_base_exception["what"] = &vili::exceptions::base_exception::what;
    }
    void load_class_debug_info(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::debug_info> bind_debug_info
            = exceptions_namespace.new_usertype<vili::exceptions::debug_info>("debug_info",
                sol::call_constructor,
                sol::constructors<vili::exceptions::debug_info(
                    std::string_view, int, std::string_view)>());
        bind_debug_info["file"] = &vili::exceptions::debug_info::file;
        bind_debug_info["line"] = &vili::exceptions::debug_info::line;
        bind_debug_info["function"] = &vili::exceptions::debug_info::function;
    }
    void load_class_file_not_found(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::file_not_found> bind_file_not_found
            = exceptions_namespace.new_usertype<vili::exceptions::file_not_found>("file_not_found",
                sol::call_constructor,
                sol::constructors<vili::exceptions::file_not_found(
                    std::string_view, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::file_not_found>,
                    vili::exceptions::base_exception>());
    }
    void load_class_inconsistent_indentation(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::inconsistent_indentation> bind_inconsistent_indentation
            = exceptions_namespace.new_usertype<vili::exceptions::inconsistent_indentation>(
                "inconsistent_indentation", sol::call_constructor,
                sol::constructors<vili::exceptions::inconsistent_indentation(
                    int64_t, int64_t, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::inconsistent_indentation>,
                    vili::exceptions::base_exception>());
    }
    void load_class_integer_dump_error(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::integer_dump_error> bind_integer_dump_error
            = exceptions_namespace.new_usertype<vili::exceptions::integer_dump_error>(
                "integer_dump_error", sol::call_constructor,
                sol::constructors<vili::exceptions::integer_dump_error(
                    vili::integer, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::integer_dump_error>,
                    vili::exceptions::base_exception>());
    }
    void load_class_invalid_cast(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::invalid_cast> bind_invalid_cast
            = exceptions_namespace.new_usertype<vili::exceptions::invalid_cast>("invalid_cast",
                sol::call_constructor,
                sol::constructors<vili::exceptions::invalid_cast(
                    std::string_view, std::string_view, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::invalid_cast>,
                    vili::exceptions::base_exception>());
    }
    void load_class_invalid_data_type(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::invalid_data_type> bind_invalid_data_type
            = exceptions_namespace.new_usertype<vili::exceptions::invalid_data_type>(
                "invalid_data_type", sol::call_constructor,
                sol::constructors<vili::exceptions::invalid_data_type(
                    vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::invalid_data_type>,
                    vili::exceptions::base_exception>());
    }
    void load_class_invalid_merge(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::invalid_merge> bind_invalid_merge
            = exceptions_namespace.new_usertype<vili::exceptions::invalid_merge>("invalid_merge",
                sol::call_constructor,
                sol::constructors<vili::exceptions::invalid_merge(
                    std::string_view, std::string_view, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::invalid_merge>,
                    vili::exceptions::base_exception>());
    }
    void load_class_invalid_node_type(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::invalid_node_type> bind_invalid_node_type
            = exceptions_namespace.new_usertype<vili::exceptions::invalid_node_type>(
                "invalid_node_type", sol::call_constructor,
                sol::constructors<vili::exceptions::invalid_node_type(
                    std::string_view, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::invalid_node_type>,
                    vili::exceptions::base_exception>());
    }
    void load_class_number_dump_error(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::number_dump_error> bind_number_dump_error
            = exceptions_namespace.new_usertype<vili::exceptions::number_dump_error>(
                "number_dump_error", sol::call_constructor,
                sol::constructors<vili::exceptions::number_dump_error(
                    vili::number, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::number_dump_error>,
                    vili::exceptions::base_exception>());
    }
    void load_class_parsing_error(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::parsing_error> bind_parsing_error
            = exceptions_namespace.new_usertype<vili::exceptions::parsing_error>("parsing_error",
                sol::call_constructor,
                sol::constructors<vili::exceptions::parsing_error(
                    std::string_view, size_t, size_t, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::parsing_error>,
                    vili::exceptions::base_exception>());
    }
    void load_class_too_much_indentation(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::too_much_indentation> bind_too_much_indentation
            = exceptions_namespace.new_usertype<vili::exceptions::too_much_indentation>(
                "too_much_indentation", sol::call_constructor,
                sol::constructors<vili::exceptions::too_much_indentation(
                    int64_t, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::too_much_indentation>,
                    vili::exceptions::base_exception>());
    }
    void load_class_unknown_child_node(sol::state_view state)
    {
        sol::table exceptions_namespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::unknown_child_node> bind_unknown_child_node
            = exceptions_namespace.new_usertype<vili::exceptions::unknown_child_node>(
                "unknown_child_node", sol::call_constructor,
                sol::constructors<vili::exceptions::unknown_child_node(
                    std::string_view, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<vili::exceptions::unknown_child_node>,
                    vili::exceptions::base_exception>());
        bind_unknown_child_node["key"] = &vili::exceptions::unknown_child_node::key;
    }
};