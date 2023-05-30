#include <cppnet/log.hpp>

namespace cppnet
{
    std::ostream& err()
    {
        if constexpr (LOG_ERRORS)
        {
            return std::cerr;
        }
        else
        {
            return NULL_STREAM;
        }
    }
}