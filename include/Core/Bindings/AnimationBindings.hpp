#pragma once

namespace kaguya { class State; }

/**
 * \brief Bindings to Animation related classes and functions
 */
namespace obe::Bindings::AnimationBindings
{
    void LoadAnimationGroup(kaguya::State* lua);
    void LoadAnimation(kaguya::State* lua);
    void LoadAnimator(kaguya::State* lua);
}
