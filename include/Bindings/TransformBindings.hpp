#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
        * \brief Bindings to Transform related classes and functions
        */
        namespace TransformBindings
        {
            void LoadProtectedUnitVector(kaguya::State* lua);
            void LoadRect(kaguya::State* lua);
            void LoadUnitBasedObject(kaguya::State* lua);
            void LoadUnitVector(kaguya::State* lua);
        }
    }
}