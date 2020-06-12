#include <sol/sol.hpp>

namespace vili
{
    class node;
}

namespace sol
{
    template <> struct is_container<vili::node> : std::false_type
    {
    };
}