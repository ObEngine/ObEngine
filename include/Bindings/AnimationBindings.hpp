#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace AnimationBindings
        {
            void LoadAnimationGroup(kaguya::State& lua);
            void LoadAnimation(kaguya::State& lua);
            void LoadAnimator(kaguya::State& lua);
        }
    }
}
