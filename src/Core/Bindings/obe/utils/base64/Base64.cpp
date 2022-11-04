#include <Bindings/obe/utils/base64/Base64.hpp>

#include <Utils/Encoding.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::base64::bindings
{
    void load_function_encode(sol::state_view state)
    {
        sol::table base64_namespace = state["obe"]["utils"]["base64"].get<sol::table>();
        base64_namespace.set_function("encode", &obe::utils::base64::encode);
    }
    void load_function_decode(sol::state_view state)
    {
        sol::table base64_namespace = state["obe"]["utils"]["base64"].get<sol::table>();
        base64_namespace.set_function("decode", &obe::utils::base64::decode);
    }
    void load_global_base64_chars(sol::state_view state)
    {
        sol::table base64_namespace = state["obe"]["utils"]["base64"].get<sol::table>();
        base64_namespace["base64_chars"] = obe::utils::base64::base64_chars;
    }
};