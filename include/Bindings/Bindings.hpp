#pragma once

#include <kaguya/kaguya.hpp>

#include <Bindings/BindingTree.hpp>

namespace obe
{
    namespace Bindings
    {
        extern BindingTree BindTree;
        void Load(kaguya::State* lua, const std::string& lib);
        void IndexBindings();
    }
}
