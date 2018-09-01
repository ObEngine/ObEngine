#include <Types/Global.hpp>
#include <Utils/ExecUtils.hpp>
#include <Types/SynchronizeHelper.inl>

#include <memory>

namespace obe::Types::Globals
{
    struct GlobalMap
    {
        static Bindings::BindingTree* BindTree;
        static std::shared_ptr<spdlog::logger>* Log;
        static 
    };

    void Synchronize(Globals::GlobalMap* OtherIndex)
    {
        std::cout << "STARTING SYNCHRONIZATION" << std::endl;
        const Globals::SynchronizeHelper helper(OtherIndex);
        //Loop<0, MaxGlobals - 1>::run(helper);
        //std::cout << Types::GetGlobal<0>() << std::endl;
    }
}