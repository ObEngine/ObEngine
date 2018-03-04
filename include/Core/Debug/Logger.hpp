#pragma once

#include <spdlog/spdlog.h>

namespace obe::Debug
{
    namespace spd = spdlog;
    extern std::shared_ptr<spd::logger> Log;

    void InitLogger();
    void InitLoggerLevel();
}