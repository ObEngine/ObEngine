#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
         * \brief Bindings to Animation related classes and functions
         */
        namespace AnimationBindings
        {
            void LoadAnimationGroup(kaguya::State* lua);
            void LoadAnimation(kaguya::State* lua);
            void LoadAnimator(kaguya::State* lua);
        }
    }
}
