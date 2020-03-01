#pragma once

#include <fmt/ostream.h>
#include <spdlog/spdlog.h>

namespace obe::Debug
{
    namespace spd = spdlog;
    extern std::shared_ptr<spd::logger> Log;

    // TODO: Create a Logger class wrapper instead of separate function with a global
    /**
     * \brief Initialize the Logger
     */
    void InitLogger();
    /**
     * \brief Sets the Logger Level from the configuration file
     */
    void InitLoggerLevel();
    /**
     * \brief Sets the Logger level (will silent messages with not enough level)
              The levels are the following ones :
                - 0: trace
                - 1: debug
                - 2: info
                - 3: warn
                - 4: err
                - 5: critical
                - 6: off
     * \param level Minimum level required for messages to be logged
     * \bind{Logger.setLevel}
    */
    void SetLoggerLevel(const spdlog::level::level_enum level);
} // namespace obe::Debug
