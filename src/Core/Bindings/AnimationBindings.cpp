// Corresponding header
#include <Bindings/AnimationBindings.hpp>

// ObEngineCore headers
#include <Animation/Animation.hpp>
#include <Animation/AnimationGroup.hpp>
#include <Animation/Animator.hpp>
#include <Graphics/Sprite.hpp>

// extlibs headers
#include <kaguya/metatable.hpp>
#include <kaguya/native_function.hpp>
#include <kaguya/state.hpp>

namespace obe::Bindings::AnimationBindings
{
    void LoadAnimation(kaguya::State* lua)
    {
        (*lua)["obe"]["Animation"].setClass(
            kaguya::UserdataMetatable<Animation::Animation>()
                .addFunction("applyParameters", &Animation::Animation::applyParameters)
                .addFunction("getAllAnimationGroupName",
                    &Animation::Animation::getAllAnimationGroupName)
                .addFunction("getDelay", &Animation::Animation::getDelay)
                .addFunction(
                    "getAnimationGroup", &Animation::Animation::getAnimationGroup)
                .addFunction("getName", &Animation::Animation::getName)
                .addFunction("getPlayMode", &Animation::Animation::getPlayMode)
                .addFunction("getStatus", &Animation::Animation::getStatus)
                .addFunction(
                    "getCalledAnimation", &Animation::Animation::getCalledAnimation)
                .addFunction("getCurrentAnimationGroup",
                    &Animation::Animation::getCurrentAnimationGroup)
                .addFunction("getPriority", &Animation::Animation::getPriority)
                .addFunction("getTexture", &Animation::Animation::getTexture)
                .addFunction(
                    "getTextureAtIndex", &Animation::Animation::getTextureAtIndex)
                .addFunction("isOver", &Animation::Animation::isOver)
                .addFunction("loadAnimation", &Animation::Animation::loadAnimation)
                .addFunction("reset", &Animation::Animation::reset)
                .addFunction("update", &Animation::Animation::update));
    }

    void LoadAnimationGroup(kaguya::State* lua)
    {
        (*lua)["obe"]["AnimationGroup"].setClass(
            kaguya::UserdataMetatable<Animation::AnimationGroup>()
                .addFunction("getDelay", &Animation::AnimationGroup::getDelay)
                .addFunction("getIndex", &Animation::AnimationGroup::getIndex)
                .addFunction("getName", &Animation::AnimationGroup::getName)
                .addFunction("getSize", &Animation::AnimationGroup::getSize)
                .addFunction("getTexture", &Animation::AnimationGroup::getTexture)
                .addFunction("isOver", &Animation::AnimationGroup::isOver)
                .addFunction("next", &Animation::AnimationGroup::next)
                .addFunction("previous", &Animation::AnimationGroup::previous)
                .addFunction("pushTexture", &Animation::AnimationGroup::pushTexture)
                .addFunction("removeTextureByIndex",
                    &Animation::AnimationGroup::removeTextureByIndex)
                .addFunction("reset", &Animation::AnimationGroup::reset)
                .addFunction("setDelay", &Animation::AnimationGroup::setDelay)
                .addFunction("setLoops", &Animation::AnimationGroup::setLoops));
    }

    KAGUYA_MEMBER_FUNCTION_OVERLOADS(
        Animator_setTarget_wrapper, Animation::Animator, setTarget, 1, 2);
    void LoadAnimator(kaguya::State* lua)
    {
        (*lua)["obe"]["Animator"].setClass(
            kaguya::UserdataMetatable<Animation::Animator>()
                .setConstructors<Animation::Animator(),
                    Animation::Animator(const System::Path&)>()
                .addFunction("clear", &Animation::Animator::clear)
                .addFunction(
                    "getAllAnimationName", &Animation::Animator::getAllAnimationName)
                .addFunction("getAnimation", &Animation::Animator::getAnimation)
                .addFunction("getKey", &Animation::Animator::getKey)
                .addFunction("getTexture", &Animation::Animator::getTexture)
                .addFunction("getTextureAtKey", &Animation::Animator::getTextureAtKey)
                .addFunction("loadAnimator", &Animation::Animator::loadAnimator)
                .addFunction("setKey", &Animation::Animator::setKey)
                .addOverloadedFunctions("setPath",
                    static_cast<void (Animation::Animator::*)(const System::Path&)>(
                        &Animation::Animator::setPath),
                    static_cast<void (Animation::Animator::*)(const std::string&)>(
                        &Animation::Animator::setPath))
                .addFunction("setPaused", &Animation::Animator::setPaused)
                .addFunction("setTarget", Animator_setTarget_wrapper())
                .addFunction("update", &Animation::Animator::update));

        (*lua)["obe"]["Animator"]["setTarget"] = kaguya::overload(
            [](Animation::Animator* animator, Graphics::Sprite* sprite) {
                animator->setTarget(*sprite);
            },
            [](Animation::Animator* animator, Graphics::Sprite* sprite,
                Animation::AnimatorTargetScaleMode scaleMode) {
                animator->setTarget(*sprite, scaleMode);
            });

        (*lua)["obe"]["Animator"]["TargetScaleMode"] = kaguya::NewTable();
        (*lua)["obe"]["Animator"]["TargetScaleMode"]["Fit"]
            = Animation::AnimatorTargetScaleMode::Fit;
        (*lua)["obe"]["Animator"]["TargetScaleMode"]["FixedWidth"]
            = Animation::AnimatorTargetScaleMode::FixedWidth;
        (*lua)["obe"]["Animator"]["TargetScaleMode"]["FixedHeight"]
            = Animation::AnimatorTargetScaleMode::FixedHeight;
        (*lua)["obe"]["Animator"]["TargetScaleMode"]["TextureSize"]
            = Animation::AnimatorTargetScaleMode::TextureSize;
    }
} // namespace obe::Bindings::AnimationBindings