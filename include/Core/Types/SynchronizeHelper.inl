#pragma once

#include <Types/Global.hpp>

#include <Utils/ExecUtils.hpp>

#include <Bindings/Bindings.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Input/InputButtonMonitor.hpp>
#include <Input/KeyList.hpp>
#include <Script/GlobalState.hpp>
#include <System/Config.hpp>
#include <System/Window.hpp>

namespace obe::Types
{
    namespace Globals
    {
        /*int gl_a;
        double gl_b;
        Global<0, int> a(&gl_a);
        Global<1, double> b(&gl_b);*/
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
