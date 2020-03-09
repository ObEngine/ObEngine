#pragma once

#include <spdlog/spdlog.h>

namespace obe::Debug
{
    extern std::shared_ptr<spdlog::logger> Log;

    // TODO: Create a Logger class wrapper instead of separate function with a global
    /**
     * \brief Initialize the Logger
     */
    void InitLogger();
} // namespace obe::Debug
