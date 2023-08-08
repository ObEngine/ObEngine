#include <Bindings/obe/utils/threading/Threading.hpp>

#include <Utils/Threading.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::threading::bindings
{
    void load_class_thread(sol::state_view state)
    {
        sol::table threading_namespace = state["obe"]["utils"]["threading"].get<sol::table>();
        sol::usertype<obe::utils::threading::Thread> bind_thread
            = threading_namespace.new_usertype<obe::utils::threading::Thread>("Thread",
                sol::call_constructor,
                sol::constructors<obe::utils::threading::Thread(std::function<bool()>)>());
        bind_thread["on_complete"] = &obe::utils::threading::Thread::on_complete;
        bind_thread["is_complete"] = &obe::utils::threading::Thread::is_complete;
        bind_thread["is_success"] = &obe::utils::threading::Thread::is_success;
        bind_thread["join"] = &obe::utils::threading::Thread::join;
        bind_thread["detach"] = &obe::utils::threading::Thread::detach;
    }
};