#pragma once

#include <Bindings/BindingTree.hpp>
#include <Bindings/BindingUtils.hpp>

namespace obe
{
    namespace Bindings
    {
        extern BindingTree BindTree;
        void Load(kaguya::State* lua, const std::string& lib);
        void IndexBindings();
    }
}
