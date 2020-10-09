#pragma once

#include <vili/exceptions.hpp>

namespace vili::validator::exceptions
{
    template <class exception_type>
    class validator_exception : public vili::exceptions::exception<exception_type>
    {
    public:
        validator_exception(std::string_view exception_name, std::string_view location,
            vili::exceptions::debug_info info)
            : vili::exceptions::exception<exception_type>(exception_name, info)
        {
            m_message += fmt::format("  - node: {}\n", location);
        }
    };

    class not_a_validator : public validator_exception<not_a_validator>
    {
    public:
        not_a_validator(std::string_view location, std::string_view node_dump,
            vili::exceptions::debug_info info)
            : validator_exception("not_a_validator", location, info)
        {
            this->error("'{}' is not a valid vili::validator", location, node_dump);
        }
    };

    class value_type_mismatch : public validator_exception<value_type_mismatch>
    {
    public:
        value_type_mismatch(std::string_view location, std::string_view expected_type,
            std::string_view real_type, vili::exceptions::debug_info info)
            : validator_exception("value_type_mismatch", location, info)
        {
            this->error("Validator expected value to have '{}' type but got '{}' instead",
                expected_type, real_type);
        }
    };

    class validator_type_mismatch : public validator_exception<validator_type_mismatch>
    {
    public:
        validator_type_mismatch(std::string_view location, std::string_view expected_type,
            std::string_view real_type, vili::exceptions::debug_info info)
            : validator_exception("validator_type_mismatch", location, info)
        {
            this->error(
                "Expected validator with type '{}' but got '{}' validator instead",
                expected_type, real_type);
        }
    };

    class missing_validator_type : public validator_exception<missing_validator_type>
    {
    public:
        missing_validator_type(
            std::string_view location, vili::exceptions::debug_info info)
            : validator_exception("missing_validator_type", location, info)
        {
            this->error("Validator must have a 'type' attribute");
        }
    };

    class validator_constraint_type_mismatch
        : public validator_exception<validator_constraint_type_mismatch>
    {
    public:
        validator_constraint_type_mismatch(std::string_view location,
            std::string_view constraint, std::string_view expected_type,
            std::string_view real_type, vili::exceptions::debug_info info)
            : validator_exception("validator_constraint_type_mismatch", location, info)
        {
            this->error(
                "Validator constraint '{}' should have type '{}' but have type '{}'",
                constraint, expected_type, real_type);
        }
    };

    class constraint_validation_failure
        : public validator_exception<constraint_validation_failure>
    {
    public:
        constraint_validation_failure(std::string_view location,
            std::string_view constraint, std::string_view constraint_value,
            std::string_view node_dump, vili::exceptions::debug_info info)
            : validator_exception("constraint_validation_failure", location, info)
        {
            this->error("Validator constraint {{ {}: {} }} failed to validate value [{}]",
                constraint, constraint_value, node_dump);
        }
    };

    class unknown_pattern : public validator_exception<unknown_pattern>
    {
    public:
        unknown_pattern(std::string_view location, std::string_view pattern,
            vili::exceptions::debug_info info)
            : validator_exception("unknown_pattern", location, info)
        {
            this->error("No such string pattern '{}'", pattern);
        }
    };

    class tuple_size_mismatch : public validator_exception<tuple_size_mismatch>
    {
    public:
        tuple_size_mismatch(std::string_view location, size_t expected_size,
            size_t real_size, vili::exceptions::debug_info info)
            : validator_exception("tuple_size_mismatch", location, info)
        {
            this->error("Validator expected tuple of size {} but got a tuple of size {}",
                expected_size, real_size);
        }
    };

    class missing_property : public validator_exception<missing_property>
    {
    public:
        missing_property(std::string_view location, std::string_view property_name,
            vili::exceptions::debug_info info)
            : validator_exception("missing_property", location, info)
        {
            this->error(
                "Validator expected property '{}' but could not find it", property_name);
        }
    };

    class no_union_match : public validator_exception<no_union_match>
    {
    public:
        no_union_match(std::string_view location, std::string_view union_dump,
            std::string_view input_dump, std::vector<std::string> causes,
            vili::exceptions::debug_info info)
            : validator_exception("no_union_match", location, info)
        {
            this->error("Could not validate input against any of the union types",
                union_dump, input_dump);
            m_message += fmt::format("  - union: {}\n",
                vili::exceptions::indent_string(union_dump.data(), 4, false));
            m_message += fmt::format("  - input: {}\n",
                vili::exceptions::indent_string(input_dump.data(), 4, false));
            for (const std::string& cause : causes)
            {
                m_message += fmt::format(
                    "  - cause: {}\n", vili::exceptions::indent_string(cause, 4, false));
            }
        }
    };
}
