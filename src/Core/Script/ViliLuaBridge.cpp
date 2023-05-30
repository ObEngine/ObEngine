#include <sol/sol.hpp>

#include <Script/Scripting.hpp>
#include <Script/ViliLuaBridge.hpp>

namespace obe::script::vili_lua_bridge
{
    sol::lua_value vili_to_lua(const vili::node& convert)
    {
        if (convert.is<vili::array>())
        {
            return vili_array_to_lua_table(convert);
        }
        else if (convert.is<vili::object>())
        {
            return vili_object_to_lua_table(convert);
        }
        else if (convert.is_primitive())
        {
            return vili_primitive_to_lua_value(convert);
        }
    }

    sol::lua_value vili_to_lua_keep_order(sol::state_view state, const vili::node& convert)
    {
        if (convert.is<vili::array>())
        {
            return vili_array_to_lua_table(convert);
        }
        else if (convert.is<vili::object>())
        {
            return vili_object_to_lua_table_keep_order(state, convert);
        }
        else if (convert.is_primitive())
        {
            return vili_primitive_to_lua_value(convert);
        }
    }

    vili::node lua_to_vili(const sol::object& convert)
    {
        if (convert.is<sol::table>())
        {
            vili::integer expect = 1;
            for (auto& [k, _] : convert.as<sol::table>())
            {
                if (!k.is<vili::integer>()
                    || (k.is<vili::integer>() && (k.as<vili::integer>() != expect++)))
                {
                    return lua_table_to_vili_object(convert);
                }
            }
            return lua_table_to_vili_array(convert);
        }
        else
        {
            return lua_value_to_vili_primitive(convert);
        }
    }

    sol::lua_value vili_object_to_lua_table(const vili::node& convert)
    {
        std::unordered_map<std::string, sol::lua_value> result;
        for (auto [key, value] : convert.items())
        {
            if (value.is_primitive())
            {
                result.emplace(key, vili_primitive_to_lua_value(value));
            }
            else if (value.is<vili::object>())
            {
                result.emplace(key, vili_object_to_lua_table(value));
            }
            else if (value.is<vili::array>())
            {
                result.emplace(key, vili_array_to_lua_table(value));
            }
        }

        return sol::as_table(result);
    }

    sol::lua_value vili_object_to_lua_table_keep_order(
        sol::state_view state, const vili::node& convert)
    {
        sol::table result = state.create_table();
        std::vector<std::string> ordered_keys;
        for (auto [key, value] : convert.items())
        {
            if (value.is_primitive())
            {
                result[key] = vili_primitive_to_lua_value(value);
            }
            else if (value.is<vili::object>())
            {
                result[key] = vili_object_to_lua_table_keep_order(state, value);
            }
            else if (value.is<vili::array>())
            {
                result[key] = vili_array_to_lua_table(value);
            }
            ordered_keys.push_back(key);
        }
        std::cout << "Applying ordered_table" << std::endl;
        script::safe_lua_call(state["Helpers"]["ordered_table"], result, ordered_keys);

        return result;
    }

    sol::lua_value vili_primitive_to_lua_value(const vili::node& convert)
    {
        if (convert.is<vili::integer>())
            return convert.as<vili::integer>();
        else if (convert.is<vili::string>())
            return convert.as<vili::string>();
        else if (convert.is<vili::boolean>())
            return convert.as<vili::boolean>();
        else if (convert.is<vili::number>())
            return convert.as<vili::number>();
    }

    sol::lua_value vili_array_to_lua_table(const vili::node& convert)
    {
        std::vector<sol::lua_value> result;
        for (const vili::node& value : convert)
        {
            if (value.is_primitive())
                result.push_back(vili_primitive_to_lua_value(value));
            else if (value.is<vili::array>())
                result.push_back(vili_array_to_lua_table(value));
            else if (value.is<vili::object>())
                result.push_back(vili_object_to_lua_table(value));
        }
        return sol::as_table(result);
    }

    vili::node lua_table_to_vili_object(const sol::table& convert)
    {
        vili::node result = vili::object {};

        for (const auto& [key, value] : convert.pairs())
        {
            result.insert(key.as<std::string>(), lua_to_vili(value));
        }
        return result;
    }

    vili::node lua_value_to_vili_primitive(const sol::lua_value& convert)
    {
        vili::node result;
        if (convert.is<vili::integer>())
        {
            result = convert.as<vili::integer>();
        }
        else if (convert.is<vili::number>())
        {
            result = convert.as<vili::number>();
        }
        else if (convert.is<vili::boolean>())
        {
            result = convert.as<vili::boolean>();
        }
        else if (convert.is<vili::string>())
        {
            result = convert.as<vili::string>();
        }
        return result;
    }

    vili::node lua_table_to_vili_array(const sol::table& convert)
    {
        vili::node result = vili::array {};
        for (auto& [_, value] : convert)
        {
            result.push(lua_to_vili(value));
        }
        return result;
    }

    sol::lua_value vili_to_lua_keep_order_proxy(sol::this_state state, const vili::node& convert)
    {
        return vili_to_lua_keep_order(state, convert);
    }
} // namespace obe::script::DataBridge
