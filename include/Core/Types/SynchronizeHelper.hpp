#pragma once

#include "Global.hpp"
#include "Debug/Logger.hpp"

namespace obe::Globals
{
    namespace Debug
    {
        extern Types::Global<0, std::shared_ptr<spdlog::logger>> Log;
        extern Types::Global<1, std::vector<int>> Prrr;
        //static Types::Global<2, int> null_int(nullptr);
    }
}
