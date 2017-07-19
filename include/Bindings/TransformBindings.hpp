#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace TransformBindings
        {
            void LoadProtectedUnitVector(kaguya::State& lua);
            void LoadRect(kaguya::State& lua);
            void LoadUnitBasedObject(kaguya::State& lua);
            void LoadUnitVector(kaguya::State& lua);
        }
    }
}