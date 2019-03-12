#pragma once

#include <spdlog/spdlog.h>
#include <fmt/ostream.h>

namespace obe::Debug
{
    namespace spd = spdlog;
    extern std::shared_ptr<spd::logger> Log;

    void InitLogger();
    void InitLoggerLevel();
    void SetLoggerLevel(const spdlog::level::level_enum);

}
