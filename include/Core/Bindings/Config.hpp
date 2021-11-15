#include <sol/sol.hpp>

namespace vili
{
    class node;
}

namespace obe::Event
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
    struct is_callable<obe::Event::LuaEventListener> : std::false_type
    {
    };
}
