#include <Types/Global.hpp>
#include <Utils/ExecUtils.hpp>
#include <Types/SynchronizeHelper.inl>

namespace obe::Types::Globals
{
    

    void Synchronize(Globals::GlobalMap* OtherIndex)
    {
        std::cout << "STARTING SYNCHRONIZATION" << std::endl;
        const Globals::SynchronizeHelper helper(OtherIndex);
        Loop<0, MaxGlobals - 1>::run(helper);
        //GetGlobal<0>().reset(GetGlobal<0>(OtherIndex).ptr());
        //std::cout << Types::GetGlobal<0>() << std::endl;
    }
}