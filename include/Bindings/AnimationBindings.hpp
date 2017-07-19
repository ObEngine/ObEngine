#pragma once

#include <kaguya/kaguya.hpp>

#include <Animation/AnimationGroup.hpp>
#include <Animation/Animation.hpp>
#include <Animation/Animator.hpp>
#include <Bindings/BindingUtils.hpp>

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
