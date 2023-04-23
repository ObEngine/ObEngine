#pragma once

#include <iostream>

namespace cppnet
{
    constexpr bool LOG_ERRORS = false;

    namespace
    {
        class NullBuffer : public std::streambuf
        {
        public:
            int overflow(int c) { return c; }
        };

        static inline NullBuffer NULL_BUFFER;
        static inline std::ostream NULL_STREAM(&NULL_BUFFER);
    }

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
} // namespace cppnet