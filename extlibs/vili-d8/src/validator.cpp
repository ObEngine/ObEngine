#include <regex>

#include <vld8/exceptions.hpp>
#include <vld8/validator.hpp>

#include "pattern.inl"
#include "validator.inl"

namespace vili::validator
{
    vili::node validate_integer(
        std::string location, const vili::node& validator, const vili::node& input)
    {
        validate_input<vili::node_type::integer>(location, input);
        validate_validator<vili::node_type::integer>(location, validator);
        validate_validator_type(location, validator, input);
        validate_values(location, validator, input);

        const vili::integer value = input.as_integer();
        if (validate_validator_attribute<vili::node_type::integer>(
                location, validator, "multiple_of"))
        {
            const vili::integer multiple_of = validator.at("multiple_of").as_integer();
            if (value % multiple_of != 0)
            {
                throw exceptions::constraint_validation_failure(location, "multiple_of",
                    validator.at("multiple_of").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::integer>(
                location, validator, "min"))
        {
            const vili::integer min = validator.at("min").as_integer();
            if (value < min)
            {
                throw exceptions::constraint_validation_failure(location, "min",
                    validator.at("min").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::integer>(
                location, validator, "max"))
        {
            const vili::integer max = validator.at("max").as_integer();
            if (value > max)
            {
                throw exceptions::constraint_validation_failure(location, "max",
                    validator.at("max").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::integer>(
                location, validator, "exclusive_min"))
        {
            const vili::integer exclusive_min
                = validator.at("exclusive_min").as_integer();
            if (value <= exclusive_min)
            {
                throw exceptions::constraint_validation_failure(location, "exclusive_min",
                    validator.at("exclusive_min").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::integer>(
                location, validator, "exclusive_max"))
        {
            const vili::integer exclusive_max
                = validator.at("exclusive_max").as_integer();
            if (value >= exclusive_max)
            {
                throw exceptions::constraint_validation_failure(location, "exclusive_max",
                    validator.at("exclusive_max").dump(), input.dump(), VILI_EXC_INFO);
            }
        }
    }

    vili::node validate_number(
        std::string location, const vili::node& validator, const vili::node& input)
    {
        validate_input<vili::node_type::number>(location, input);
        validate_validator<vili::node_type::number>(location, validator);
        validate_validator_type(location, validator, input);
        validate_values(location, validator, input);

        const vili::number value = input.as_number();
        if (validate_validator_attribute<vili::node_type::number>(
                location, validator, "multiple_of"))
        {
            const vili::number multiple_of = validator.at("multiple_of").as_number();
            if (std::fmod(value, multiple_of) != 0)
            {
                throw exceptions::constraint_validation_failure(location, "multiple_of",
                    validator.at("multiple_of").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::number>(
                location, validator, "min"))
        {
            const vili::number min = validator.at("min").as_number();
            if (value < min)
            {
                throw exceptions::constraint_validation_failure(location, "min",
                    validator.at("min").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::number>(
                location, validator, "max"))
        {
            const vili::number max = validator.at("max").as_number();
            if (value > max)
            {
                throw exceptions::constraint_validation_failure(location, "max",
                    validator.at("max").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::number>(
                location, validator, "exclusive_min"))
        {
            const vili::number exclusive_min = validator.at("exclusive_min").as_number();
            if (value <= exclusive_min)
            {
                throw exceptions::constraint_validation_failure(location, "exclusive_min",
                    validator.at("exclusive_min").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::number>(
                location, validator, "exclusive_max"))
        {
            const vili::number exclusive_max = validator.at("exclusive_max").as_number();
            if (value >= exclusive_max)
            {
                throw exceptions::constraint_validation_failure(location, "exclusive_max",
                    validator.at("exclusive_max").dump(), input.dump(), VILI_EXC_INFO);
            }
        }
    }

    vili::node validate_boolean(
        std::string location, const vili::node& validator, const vili::node& input)
    {
        validate_input<vili::node_type::boolean>(location, input);
        validate_validator<vili::node_type::boolean>(location, validator);
        validate_validator_type(location, validator, input);
        validate_values(location, validator, input);

        return true;
    }

    vili::node validate_string(
        std::string location, const vili::node& validator, const vili::node& input)
    {
        validate_input<vili::node_type::string>(location, input);
        validate_validator<vili::node_type::string>(location, validator);
        validate_validator_type(location, validator, input);
        validate_values(location, validator, input);

        const std::string value = input.as_string();
        if (validate_validator_attribute<vili::node_type::integer>(
                location, validator, "min_length"))
        {
            const vili::integer min_length = validator.at("min_length").as_integer();
            if (value.size() < min_length)
            {
                throw exceptions::constraint_validation_failure(location, "min_length",
                    validator.at("min_length").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::integer>(
                location, validator, "max_length"))
        {
            const vili::integer max_length = validator.at("max_length").as_integer();
            if (value.size() > max_length)
            {
                throw exceptions::constraint_validation_failure(location, "max_length",
                    validator.at("max_length").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::string>(
                location, validator, "pattern"))
        {
            const vili::string pattern = validator.at("pattern").as_string();
            if (!validate_pattern(location, pattern, value))
            {
                throw exceptions::constraint_validation_failure(location, "pattern",
                    validator.at("pattern").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::string>(
                location, validator, "regex"))
        {
            const std::regex regex = std::regex(validator.at("regex").as_string());
            if (!std::regex_match(value, regex))
            {
                throw exceptions::constraint_validation_failure(location, "pattern",
                    validator.at("regex").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        return true;
    }

    vili::node validate_array_items(
        std::string location, const vili::node& validator, const vili::node& input)
    {
        size_t index = 0;
        for (const vili::node& item : input)
        {
            validate_node(join_path(location, std::to_string(index)), validator, item);
            index++;
        }
        return true;
    }

    vili::node validate_object_items(
        std::string location, const vili::node& validator, const vili::node& input)
    {
        for (const auto& [key, item] : input.items())
        {
            validate_node(join_path(location, key), validator, item);
        }
        return true;
    }

    vili::node validate_tuple_items(
        std::string location, const vili::node& validator, const vili::node& input)
    {
        if (validator.size() != input.size())
        {
            throw exceptions::tuple_size_mismatch(
                location, validator.size(), input.size(), VILI_EXC_INFO);
        }
        for (size_t i = 0; i < validator.size(); i++)
        {
            validate_node(
                join_path(location, std::to_string(i)), validator.at(i), input.at(i));
        }
    }

    vili::node validate_array(
        std::string location, const vili::node& validator, const vili::node& input)
    {
        validate_input<vili::node_type::array>(location, input);
        validate_validator<vili::node_type::array>(location, validator);
        validate_validator_type(location, validator, input);

        if (validate_validator_attribute<vili::node_type::integer>(
                location, validator, "min_size"))
        {
            const vili::integer min_size = validator.at("min_size").as_integer();
            if (input.size() < min_size)
            {
                throw exceptions::constraint_validation_failure(location, "min_size",
                    validator.at("min_size").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::integer>(
                location, validator, "max_size"))
        {
            const vili::integer max_size = validator.at("max_size").as_integer();
            if (input.size() > max_size)
            {
                throw exceptions::constraint_validation_failure(location, "max_size",
                    validator.at("max_size").dump(), input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::integer>(
                location, validator, "exclusive_min_size"))
        {
            const vili::integer exclusive_min_size
                = validator.at("exclusive_min_size").as_integer();
            if (input.size() <= exclusive_min_size)
            {
                throw exceptions::constraint_validation_failure(location,
                    "exclusive_min_size", validator.at("exclusive_min_size").dump(),
                    input.dump(), VILI_EXC_INFO);
            }
        }

        if (validate_validator_attribute<vili::node_type::integer>(
                location, validator, "exclusive_max_size"))
        {
            const vili::integer exclusive_max_size
                = validator.at("exclusive_max_size").as_integer();
            if (input.size() >= exclusive_max_size)
            {
                throw exceptions::constraint_validation_failure(location,
                    "exclusive_max_size", validator.at("exclusive_max_size").dump(),
                    input.dump(), VILI_EXC_INFO);
            }
        }

        if (validator.contains("items"))
        {
            const vili::node& items_validator = validator.at("items");
            if (validator.is<vili::object>())
            {
                validate_array_items(location, items_validator, input);
            }
            else if (validator.is<vili::array>())
            {
                validate_tuple_items(location, items_validator, input);
            }
            else
            {
                throw exceptions::validator_constraint_type_mismatch(location, "items",
                    "array|object", vili::to_string(items_validator.type()),
                    VILI_EXC_INFO);
            }
        }
    }

    vili::node validate_object(
        std::string location, const vili::node& validator, const vili::node& input)
    {
        validate_input<vili::node_type::object>(location, input);
        validate_validator<vili::node_type::object>(location, validator);
        validate_validator_type(location, validator, input);

        if (validate_validator_attribute<vili::node_type::object>(
                location, validator, "properties"))
        {
            const vili::node& properties = validator.at("properties");
            for (auto& [key, value] : properties.items())
            {
                if (input.contains(key))
                {
                    validate_node(join_path(location, key), value, input.at(key));
                }
                else
                {
                    if (validate_validator_attribute<vili::node_type::boolean>(
                            location, value, "optional"))
                    {
                        if (!value.at("optional").as_boolean())
                        {
                            throw exceptions::missing_property(
                                location, key, VILI_EXC_INFO);
                        }
                    }
                    else
                    {
                        throw exceptions::missing_property(location, key, VILI_EXC_INFO);
                    }
                }
            }
        }

        if (validator.contains("items"))
        {
            const vili::node& items_validator = validator.at("items");
            if (validator.is<vili::object>())
            {
                validate_object_items(location, items_validator, input);
            }
            else
            {
                throw exceptions::validator_constraint_type_mismatch(location, "items",
                    vili::object_type, vili::to_string(items_validator.type()),
                    VILI_EXC_INFO);
            }
        }
    }

    vili::node validate_union(
        std::string location, const vili::node& validator, const vili::node& input)
    {
        if (validate_validator_attribute<vili::node_type::array>(
                location, validator, "types"))
        {
            const vili::node& types = validator.at("types");
            bool found_matching_type = false;
            std::vector<std::string> matching_failure_causes;
            for (const vili::node& type : types)
            {
                try
                {
                    validate_node(location, type, input);
                    found_matching_type = true;
                    break;
                }
                catch (const vili::exceptions::base_exception& e)
                {
                    matching_failure_causes.push_back(e.what());
                }
            }
            if (!found_matching_type)
            {
                throw exceptions::no_union_match(location, validator.dump(), input.dump(),
                    matching_failure_causes, VILI_EXC_INFO);
            }
        }
        return true;
    }

    vili::node validate_node(
        std::string location, const vili::node& validator, const vili::node& input)
    {
        validate_validator(location, validator);
        const std::string_view validator_expect_type = validator.at("type");

        if (validator_expect_type == vili::int_type)
        {
            validate_integer(location, validator, input);
        }
        else if (validator_expect_type == vili::float_type)
        {
            validate_number(location, validator, input);
        }
        else if (validator_expect_type == vili::bool_type)
        {
            validate_boolean(location, validator, input);
        }
        else if (validator_expect_type == vili::string_type)
        {
            validate_string(location, validator, input);
        }
        else if (validator_expect_type == vili::array_type)
        {
            validate_array(location, validator, input);
        }
        else if (validator_expect_type == vili::object_type)
        {
            validate_object(location, validator, input);
        }
        else if (validator_expect_type == "any")
        {
            const std::string input_type = vili::to_string(input.type());
            if (input_type == vili::int_type)
            {
                validate_integer(location, validator, input);
            }
            else if (input_type == vili::float_type)
            {
                validate_number(location, validator, input);
            }
            else if (input_type == vili::bool_type)
            {
                validate_boolean(location, validator, input);
            }
            else if (input_type == vili::string_type)
            {
                validate_string(location, validator, input);
            }
            else if (input_type == vili::array_type)
            {
                validate_array(location, validator, input);
            }
            else if (input_type == vili::object_type)
            {
                validate_object(location, validator, input);
            }
            else
            {
                // TODO: Add exception
            }
        }
        else if (validator_expect_type == "union")
        {
            validate_union(location, validator, input);
        }
        else
        {
            throw vili::validator::exceptions::validator_type_mismatch(location, "integer|number|boolean|string|array|object|union|any", validator_expect_type, VILI_EXC_INFO);
        }
        return vili::object {};
    }

    vili::node validate_tree(const vili::node& validator, const vili::node& input)
    {
        const vili::node tree
            = vili::object { { "type", "object" }, { "properties", validator } };
        validate_node("", tree, input);
        return true;
    }
}
