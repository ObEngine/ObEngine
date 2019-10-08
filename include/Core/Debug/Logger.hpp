#pragma once

#include <fmt/ostream.h>
#include <spdlog/spdlog.h>

namespace obe::Debug
{
    namespace spd = spdlog;
    extern std::shared_ptr<spd::logger> Log;

    void InitLogger();
    void InitLoggerLevel();
    void SetLoggerLevel(const spdlog::level::level_enum);
} // namespace obe::Debug
