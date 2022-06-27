#pragma once

#include <fmt/ostream.h>
#include <spdlog/spdlog.h>

#include <Types/SmartEnum.hpp>

namespace obe::debug
{
    using Logger = std::shared_ptr<spdlog::logger>;
    extern Logger Log;

    enum class LogLevel
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
        Off
    };
    using LogLevelMeta = types::SmartEnum<LogLevel>;

    // TODO: Create a Logger class wrapper instead of separate function with a global
    /**
     * \brief Initialize the Logger
     */
    void init_logger();

    void trace(const std::string& content);
    void debug(const std::string& content);
    void info(const std::string& content);
    void warn(const std::string& content);
    void error(const std::string& content);
    void critical(const std::string& content);
} // namespace obe::debug
