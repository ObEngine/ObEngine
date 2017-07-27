#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
         * \brief Bindings to Collision related classes and functions
         */
        namespace CollisionBindings
        {
            void LoadPolygonalCollider(kaguya::State* lua);
        }
    }
}
