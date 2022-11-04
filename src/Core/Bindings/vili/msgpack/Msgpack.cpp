#include <Bindings/vili/msgpack/Msgpack.hpp>

#include <../../vili-msgpack/include/vili-msgpack/msgpack.hpp>

#include <Bindings/Config.hpp>

namespace vili::msgpack::bindings
{
    void load_function_from_string(sol::state_view state)
    {
        sol::table msgpack_namespace = state["vili"]["msgpack"].get<sol::table>();
        msgpack_namespace.set_function("from_string", &vili::msgpack::from_string);
    }
    void load_function_to_string(sol::state_view state)
    {
        sol::table msgpack_namespace = state["vili"]["msgpack"].get<sol::table>();
        msgpack_namespace.set_function("to_string", &vili::msgpack::to_string);
    }
    void load_function_dump_element(sol::state_view state)
    {
        sol::table msgpack_namespace = state["vili"]["msgpack"].get<sol::table>();
        msgpack_namespace.set_function("dump_element", &vili::msgpack::dump_element);
    }
};