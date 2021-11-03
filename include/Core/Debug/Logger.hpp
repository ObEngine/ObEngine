#pragma once

#include <fmt/ostream.h>
#include <spdlog/spdlog.h>

namespace obe::Debug
{
    using Logger = std::shared_ptr<spdlog::logger>;
    extern Logger Log;

    // TODO: Create a Logger class wrapper instead of separate function with a global
    /**
     * \brief Initialize the Logger
     */
    void InitLogger();

    void trace(const std::string& content);
    void debug(const std::string& content);
    void info(const std::string& content);
    void warn(const std::string& content);
    void error(const std::string& content);
    void critical(const std::string& content);
} // namespace obe::Debug
