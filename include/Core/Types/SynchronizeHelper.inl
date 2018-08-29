#pragma once

#include <Types/Global.hpp>

#include <Utils/ExecUtils.hpp>
#include <Debug/Logger.hpp>

namespace obe::Globals
{
    namespace Debug
    {
        inline Types::Global<0, std::shared_ptr<spdlog::logger>> Log(GLOBE_GET(obe::Debug::Log));
        inline Types::Global<1, std::vector<int>> Prrr(GLOBE_GET(obe::Debug::Prrr));
        //static Types::Global<2, int> null_int(nullptr);
    }
}

namespace obe::Types
{
    namespace Globals
    {
        struct SynchronizeHelper
        {
            Globals::GlobalMap* tmp_globals;
            SynchronizeHelper(obe::Types::Globals::GlobalMap* OtherIndex) { tmp_globals = OtherIndex; }
            template <unsigned short I>
            void operator()(obe::Types::Globals::int_<I>) const {
                //std::cout << "Synchronizing index " << I << "(LOCAL : " << GetGlobal<I>() << ")" << " (REMOTE : " << GetGlobal<I>(tmp_globals) << ")" << std::endl;
                GetGlobal<I>().reset(GetGlobal<I>(tmp_globals).ptr());
            }
        };
    }
}
