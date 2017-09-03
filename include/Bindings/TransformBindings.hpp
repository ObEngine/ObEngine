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
            void LoadMovable(kaguya::State* lua);
            void LoadNode2D(kaguya::State* lua);
            void LoadProtectedUnitVector(kaguya::State* lua);
            void LoadRect(kaguya::State* lua);
            void LoadReferencial(kaguya::State* lua);
            void LoadUnitBasedObject(kaguya::State* lua);
            void LoadUnitVector(kaguya::State* lua);
            void LoadUnits(kaguya::State* lua);
        }
    }
}