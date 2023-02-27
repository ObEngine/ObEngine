#include <Bindings/obe/Obe.hpp>

#include <Exception.hpp>
#include <ObEngineCore.hpp>

#include <Bindings/Config.hpp>

namespace obe::bindings
{
    void load_class_base_exception(sol::state_view state)
    {
        sol::table obe_namespace = state["obe"].get<sol::table>();
        sol::usertype<obe::BaseException> bind_base_exception
            = obe_namespace.new_usertype<obe::BaseException>(
                "BaseException", sol::call_constructor, sol::constructors<obe::BaseException()>());
        bind_base_exception["what"] = &obe::BaseException::what;
        bind_base_exception["traceback"] = &obe::BaseException::traceback;
    }
    void load_function_get_type_name(sol::state_view state)
    {
        sol::table obe_namespace = state["obe"].get<sol::table>();
    }
    void load_function_init_engine(sol::state_view state)
    {
        sol::table obe_namespace = state["obe"].get<sol::table>();
        obe_namespace.set_function("init_engine", &obe::init_engine);
    }
};