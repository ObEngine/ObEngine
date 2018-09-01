#pragma once

#include <spdlog/spdlog.h>
#include <fmt/ostream.h>

namespace obe::Debug
{
    namespace spd = spdlog;
    inline std::shared_ptr<spd::logger> Log;

    void InitLogger();
    void InitLoggerLevel();
}
