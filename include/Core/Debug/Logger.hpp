#pragma once

#include <spdlog/spdlog.h>
#include <fmt/ostream.h>

#include <Config.hpp>
#include <Types/Global.hpp>

namespace obe::Debug
{
    namespace spd = spdlog;
    GLOBE(1, Log, std::shared_ptr<spd::logger>);
    //inline std::shared_ptr<spd::logger> Log;
    GLOBE(2, Prrr, std::vector<int>);

    void InitLogger();
    void InitLoggerLevel();
}
