#include <sol/sol.hpp>

namespace vili
{
    class node;
}

namespace obe::event
{
    class LuaEventListener;
}

namespace sol
{
    template <>
    struct is_container<vili::node> : std::false_type
    {
    };

    template <>
    struct is_callable<obe::event::LuaEventListener> : std::false_type
    {
    };
}
