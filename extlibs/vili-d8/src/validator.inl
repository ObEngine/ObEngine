#pragma once

#include <vld8/exceptions.hpp>
#include <vld8/validator.hpp>

namespace vili::validator
{
    inline std::string join_path(const std::string& first, const std::string& second)
    {
        return first + "/" + second;
    }

    bool check_permissive_cast(
        std::string_view validator_type, std::string_view input_type)
    {
        if constexpr (vili::PERMISSIVE_CAST)
        {
            if (input_type == vili::int_type && validator_type == vili::float_type)
            {
                return true;
            }
            return false;
        }
        return false;
    }

    template <vili::node_type node_type>
    inline void validate_input(std::string_view location, const vili::node& input)
    {
        if (!input.is<node_type>())
        {
            const std::string input_type = vili::to_string(input.type());
            if (check_permissive_cast(vili::to_string(node_type), input_type))
            {
                return;
            }
            throw exceptions::value_type_mismatch(location, vili::to_string(node_type),
                vili::to_string(input.type()), VILI_EXC_INFO);
        }
    }

    inline void validate_validator(std::string_view location, const vili::node& validator)
    {
        if (!validator.is<vili::object>())
        {
            throw exceptions::not_a_validator(location, validator.dump(), VILI_EXC_INFO);
        }
        if (!validator.contains("type"))
        {
            throw exceptions::missing_validator_type(location, VILI_EXC_INFO);
        }
    }

    template <vili::node_type node_type>
    inline void validate_validator(std::string_view location, const vili::node& validator)
    {
        validate_validator(location, validator);
        const std::string validator_type = validator.at("type").as_string();
        if (validator_type != vili::to_string(node_type))
        {
            throw exceptions::validator_type_mismatch(
                location, vili::to_string(node_type), validator_type, VILI_EXC_INFO);
        }
    }

    inline void validate_validator_type(
        std::string_view location, const vili::node& validator, const vili::node& input)
    {
        const std::string& validator_type = validator.at("type").as_string();
        const std::string& input_type = vili::to_string(input.type());
        if (validator_type != input_type)
        {
            if (check_permissive_cast(validator_type, input_type))
            {
                return;
            }
            throw exceptions::value_type_mismatch(
                location, validator_type, input_type, VILI_EXC_INFO);
        }
    }

    template <vili::node_type node_type>
    inline bool validate_validator_attribute(std::string_view location,
        const vili::node& validator, const std::string& constraint)
    {
        if (validator.contains(constraint))
        {
            const vili::node& validator_constraint = validator.at(constraint);
            if (!validator_constraint.is<node_type>())
            {
                throw exceptions::validator_constraint_type_mismatch(location, constraint,
                    vili::to_string(node_type),
                    vili::to_string(validator_constraint.type()), VILI_EXC_INFO);
            }
            return true;
        }
        return false;
    }

    inline bool validate_values(
        std::string_view location, const vili::node& validator, const vili::node& input)
    {
        if (validator.contains("value"))
        {
            const vili::node& validator_value = validator.at("value");
            if (validator_value != input)
            {
                throw exceptions::constraint_validation_failure(location, "value",
                    validator_value.dump(), input.dump(), VILI_EXC_INFO);
            }
        }
        if (validate_validator_attribute<vili::node_type::array>(
                location, validator, "values"))
        {
            const vili::node& validator_values = validator.at("values");
            bool found_matching_value = false;
            for (const vili::node& value : validator_values)
            {
                if (value == input)
                {
                    found_matching_value = true;
                    break;
                }
            }
            if (!found_matching_value)
            {
                throw exceptions::constraint_validation_failure(location, "values",
                    validator_values.dump(), input.dump(), VILI_EXC_INFO);
            }
        }
    }
}