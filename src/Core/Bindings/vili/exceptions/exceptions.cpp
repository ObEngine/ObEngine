#include <Bindings/vili/exceptions/exceptions.hpp>

#include <vili/exceptions.hpp>

#include <Bindings/Config.hpp>

namespace vili::exceptions::Bindings
{
    void LoadClassArrayIndexOverflow(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::array_index_overflow> bindarray_index_overflow
            = exceptionsNamespace.new_usertype<vili::exceptions::array_index_overflow>(
                "array_index_overflow", sol::call_constructor,
                sol::constructors<vili::exceptions::array_index_overflow(
                    size_t, size_t, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<array_index_overflow>,
                    vili::exceptions::base_exception>());
    }
    void LoadClassBaseException(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::base_exception> bindbase_exception
            = exceptionsNamespace.new_usertype<vili::exceptions::base_exception>(
                "base_exception", sol::call_constructor, sol::default_constructor);
        bindbase_exception["what"] = &vili::exceptions::base_exception::what;
    }
    void LoadClassDebugInfo(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::debug_info> binddebug_info
            = exceptionsNamespace.new_usertype<vili::exceptions::debug_info>("debug_info",
                sol::call_constructor,
                sol::constructors<vili::exceptions::debug_info(
                    std::string_view, int, std::string_view)>());
        binddebug_info["file"] = &vili::exceptions::debug_info::file;
        binddebug_info["line"] = &vili::exceptions::debug_info::line;
        binddebug_info["function"] = &vili::exceptions::debug_info::function;
    }
    void LoadClassFileNotFound(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::file_not_found> bindfile_not_found
            = exceptionsNamespace.new_usertype<vili::exceptions::file_not_found>("file_not_found",
                sol::call_constructor,
                sol::constructors<vili::exceptions::file_not_found(
                    std::string_view, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<file_not_found>,
                    vili::exceptions::base_exception>());
    }
    void LoadClassInconsistentIndentation(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::inconsistent_indentation> bindinconsistent_indentation
            = exceptionsNamespace.new_usertype<vili::exceptions::inconsistent_indentation>(
                "inconsistent_indentation", sol::call_constructor,
                sol::constructors<vili::exceptions::inconsistent_indentation(
                    int64_t, int64_t, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<inconsistent_indentation>,
                    vili::exceptions::base_exception>());
    }
    void LoadClassIntegerDumpError(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::integer_dump_error> bindinteger_dump_error
            = exceptionsNamespace.new_usertype<vili::exceptions::integer_dump_error>(
                "integer_dump_error", sol::call_constructor,
                sol::constructors<vili::exceptions::integer_dump_error(
                    vili::integer, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<integer_dump_error>,
                    vili::exceptions::base_exception>());
    }
    void LoadClassInvalidCast(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::invalid_cast> bindinvalid_cast
            = exceptionsNamespace.new_usertype<vili::exceptions::invalid_cast>("invalid_cast",
                sol::call_constructor,
                sol::constructors<vili::exceptions::invalid_cast(
                    std::string_view, std::string_view, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<invalid_cast>,
                    vili::exceptions::base_exception>());
    }
    void LoadClassInvalidDataType(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::invalid_data_type> bindinvalid_data_type
            = exceptionsNamespace.new_usertype<vili::exceptions::invalid_data_type>(
                "invalid_data_type", sol::call_constructor,
                sol::constructors<vili::exceptions::invalid_data_type(
                    vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<invalid_data_type>,
                    vili::exceptions::base_exception>());
    }
    void LoadClassInvalidMerge(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::invalid_merge> bindinvalid_merge
            = exceptionsNamespace.new_usertype<vili::exceptions::invalid_merge>("invalid_merge",
                sol::call_constructor,
                sol::constructors<vili::exceptions::invalid_merge(
                    std::string_view, std::string_view, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<invalid_merge>,
                    vili::exceptions::base_exception>());
    }
    void LoadClassInvalidNodeType(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::invalid_node_type> bindinvalid_node_type
            = exceptionsNamespace.new_usertype<vili::exceptions::invalid_node_type>(
                "invalid_node_type", sol::call_constructor,
                sol::constructors<vili::exceptions::invalid_node_type(
                    std::string_view, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<invalid_node_type>,
                    vili::exceptions::base_exception>());
    }
    void LoadClassNumberDumpError(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::number_dump_error> bindnumber_dump_error
            = exceptionsNamespace.new_usertype<vili::exceptions::number_dump_error>(
                "number_dump_error", sol::call_constructor,
                sol::constructors<vili::exceptions::number_dump_error(
                    vili::number, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<number_dump_error>,
                    vili::exceptions::base_exception>());
    }
    void LoadClassParsingError(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::parsing_error> bindparsing_error
            = exceptionsNamespace.new_usertype<vili::exceptions::parsing_error>("parsing_error",
                sol::call_constructor,
                sol::constructors<vili::exceptions::parsing_error(
                    std::string_view, size_t, size_t, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<parsing_error>,
                    vili::exceptions::base_exception>());
    }
    void LoadClassTooMuchIndentation(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::too_much_indentation> bindtoo_much_indentation
            = exceptionsNamespace.new_usertype<vili::exceptions::too_much_indentation>(
                "too_much_indentation", sol::call_constructor,
                sol::constructors<vili::exceptions::too_much_indentation(
                    int64_t, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<too_much_indentation>,
                    vili::exceptions::base_exception>());
    }
    void LoadClassUnknownChildNode(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::unknown_child_node> bindunknown_child_node
            = exceptionsNamespace.new_usertype<vili::exceptions::unknown_child_node>(
                "unknown_child_node", sol::call_constructor,
                sol::constructors<vili::exceptions::unknown_child_node(
                    std::string_view, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<unknown_child_node>,
                    vili::exceptions::base_exception>());
        bindunknown_child_node["key"] = &vili::exceptions::unknown_child_node::key;
    }
    void LoadClassUnknownTemplate(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        sol::usertype<vili::exceptions::unknown_template> bindunknown_template
            = exceptionsNamespace.new_usertype<vili::exceptions::unknown_template>(
                "unknown_template", sol::call_constructor,
                sol::constructors<vili::exceptions::unknown_template(
                    std::string_view, vili::exceptions::debug_info)>(),
                sol::base_classes,
                sol::bases<vili::exceptions::exception<unknown_template>,
                    vili::exceptions::base_exception>());
    }
    void LoadFunctionIndentString(sol::state_view state)
    {
        sol::table exceptionsNamespace = state["vili"]["exceptions"].get<sol::table>();
        exceptionsNamespace.set_function("indent_string", vili::exceptions::indent_string);
    }
};
