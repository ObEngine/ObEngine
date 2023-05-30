#include <Script/LuaHelpers.hpp>

namespace obe::script::Helpers
{
    std::unordered_map<std::string, sol::protected_function> make_all_helpers(
        const sol::state_view lua)
    {
        return { { "fetch_from_one_of", fetch_from_one_of(lua) },
            { "rawget_from", rawget_from(lua) }, { "len_from", len_from(lua) },
            { "pairs_from", pairs_from(lua) }, { "ordered_table", ordered_table(lua) } };
    }

    sol::protected_function fetch_from_one_of(sol::state_view lua)
    {
        return lua.safe_script("return function(...)"
                               "   local sources = {...};"
                               "   return function(_, key)"
                               "       for _, source in pairs(sources) do"
                               "           if source[key] ~= nil then"
                               "               return source[key];"
                               "           end"
                               "       end"
                               "   end"
                               " end");
    }

    sol::protected_function rawget_from(sol::state_view lua)
    {
        return lua.safe_script("return function(tbl)"
                               "   return function(_, key)"
                               "       return rawget(tbl, key);"
                               "   end"
                               " end");
    }

    sol::protected_function len_from(sol::state_view lua)
    {
        return lua.safe_script("return function(tbl)"
                               "   return function(_)"
                               "       return #tbl;"
                               "   end"
                               " end");
    }

    sol::protected_function pairs_from(sol::state_view lua)
    {
        return lua.safe_script("return function(tbl)"
                               "   return function(_)"
                               "       return pairs(tbl);"
                               "   end"
                               " end");
    }

    sol::protected_function ordered_table(sol::state_view lua)
    {
        return lua.safe_script("return function(tbl, order)"
                               "    print('ORDERING TABLE');"
                               "    local skip_nil = true;"
                               "    if order.skip_nil ~= nil then"
                               "        skip_nil = order.skip_nil;"
                               "    end"
                               "    return setmetatable(tbl, {"
                               "        __pairs = function(tbl)"
                               "            print('ORDERING TABLE __pairs called');"
                               "            local i = 1;"
                               "            return function(_, _)"
                               "                local real_key = order[i];"
                               "                if skip_nil then"
                               "                    while tbl[real_key] == nil do"
                               "                        i = i + 1;"
                               "                        real_key = order[i];"
                               "                        if real_key == nil then"
                               "                            return nil;"
                               "                        end"
                               "                    end"
                               "                end"
                               "                i = i + 1;"
                               "                if real_key ~= nil then"
                               "                    return real_key, tbl[real_key];"
                               "                else"
                               "                    return nil;"
                               "                end"
                               "            end, tbl, nil"
                               "        end"
                               "    })"
                               "end");
    }
}
