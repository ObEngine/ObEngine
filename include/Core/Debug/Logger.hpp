#pragma once

#include <spdlog/spdlog.h>
#include <fmt/ostream.h>

#include <Config.hpp>

namespace obe::Debug
{
    namespace spd = spdlog;
    GLOBE(std::shared_ptr<spd::logger>, Log);
    GLOBE(std::vector<int>, Prrr);

    void InitLogger();
    void InitLoggerLevel();
}
