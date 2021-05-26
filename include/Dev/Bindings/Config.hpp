
#include <sol/sol.hpp>

namespace tgui
{
    class String;
}

namespace sol
{
    template <> struct is_container<tgui::String> : std::false_type
    {
    };
}