#include <Bindings/obe/Animation/Animation.hpp>

#include <Animation/Animation.hpp>
#include <Animation/AnimationGroup.hpp>
#include <Animation/Animator.hpp>
#include <Animation/Tweening.hpp>

#include <Bindings/Config.hpp>

namespace obe::Animation::Bindings
{
    void LoadEnumAnimationPlayMode(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        AnimationNamespace.new_enum<obe::Animation::AnimationPlayMode>(
            "AnimationPlayMode",
            { { "OneTime", obe::Animation::AnimationPlayMode::OneTime },
                { "Loop", obe::Animation::AnimationPlayMode::Loop },
                { "Force", obe::Animation::AnimationPlayMode::Force } });
    }
    void LoadEnumAnimationStatus(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        AnimationNamespace.new_enum<obe::Animation::AnimationStatus>("AnimationStatus",
            { { "Play", obe::Animation::AnimationStatus::Play },
                { "Call", obe::Animation::AnimationStatus::Call } });
    }
    void LoadEnumAnimatorTargetScaleMode(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        AnimationNamespace.new_enum<obe::Animation::AnimatorTargetScaleMode>(
            "AnimatorTargetScaleMode",
            { { "Fit", obe::Animation::AnimatorTargetScaleMode::Fit },
                { "FixedWidth", obe::Animation::AnimatorTargetScaleMode::FixedWidth },
                { "FixedHeight", obe::Animation::AnimatorTargetScaleMode::FixedHeight },
                { "TextureSize",
                    obe::Animation::AnimatorTargetScaleMode::TextureSize } });
    }
    void LoadClassAnimation(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::Animation> bindAnimation
            = AnimationNamespace.new_usertype<obe::Animation::Animation>(
                "Animation", sol::call_constructor, sol::default_constructor);
        bindAnimation["applyParameters"] = &obe::Animation::Animation::applyParameters;
        bindAnimation["getAllAnimationGroupName"]
            = &obe::Animation::Animation::getAllAnimationGroupName;
        bindAnimation["getDelay"] = &obe::Animation::Animation::getDelay;
        bindAnimation["getAnimationGroup"]
            = &obe::Animation::Animation::getAnimationGroup;
        bindAnimation["getName"] = &obe::Animation::Animation::getName;
        bindAnimation["getPlayMode"] = &obe::Animation::Animation::getPlayMode;
        bindAnimation["getStatus"] = &obe::Animation::Animation::getStatus;
        bindAnimation["getCalledAnimation"]
            = &obe::Animation::Animation::getCalledAnimation;
        bindAnimation["getCurrentAnimationGroup"]
            = &obe::Animation::Animation::getCurrentAnimationGroup;
        bindAnimation["getPriority"] = &obe::Animation::Animation::getPriority;
        bindAnimation["getTexture"] = &obe::Animation::Animation::getTexture;
        bindAnimation["getTextureAtIndex"]
            = &obe::Animation::Animation::getTextureAtIndex;
        bindAnimation["isOver"] = &obe::Animation::Animation::isOver;
        bindAnimation["loadAnimation"] = sol::overload(
            [](obe::Animation::Animation* self, const obe::System::Path& path) -> void {
                return self->loadAnimation(path);
            },
            [](obe::Animation::Animation* self, const obe::System::Path& path,
                obe::Engine::ResourceManager* resources) -> void {
                return self->loadAnimation(path, resources);
            });
        bindAnimation["reset"] = &obe::Animation::Animation::reset;
        bindAnimation["update"] = &obe::Animation::Animation::update;
        bindAnimation["setAntiAliasing"] = &obe::Animation::Animation::setAntiAliasing;
        bindAnimation["getAntiAliasing"] = &obe::Animation::Animation::getAntiAliasing;
    }
    void LoadClassAnimationGroup(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::AnimationGroup> bindAnimationGroup
            = AnimationNamespace.new_usertype<obe::Animation::AnimationGroup>(
                "AnimationGroup", sol::call_constructor,
                sol::constructors<obe::Animation::AnimationGroup(std::string)>());
        bindAnimationGroup["getDelay"] = &obe::Animation::AnimationGroup::getDelay;
        bindAnimationGroup["getIndex"] = &obe::Animation::AnimationGroup::getIndex;
        bindAnimationGroup["getName"] = &obe::Animation::AnimationGroup::getName;
        bindAnimationGroup["getSize"] = &obe::Animation::AnimationGroup::getSize;
        bindAnimationGroup["getTexture"] = &obe::Animation::AnimationGroup::getTexture;
        bindAnimationGroup["isOver"] = &obe::Animation::AnimationGroup::isOver;
        bindAnimationGroup["next"] = sol::overload(
            [](obe::Animation::AnimationGroup* self) -> void { return self->next(); },
            [](obe::Animation::AnimationGroup* self, bool force) -> void {
                return self->next(force);
            });
        bindAnimationGroup["previous"] = sol::overload(
            [](obe::Animation::AnimationGroup* self) -> void { return self->previous(); },
            [](obe::Animation::AnimationGroup* self, bool force) -> void {
                return self->previous(force);
            });
        bindAnimationGroup["pushTexture"] = &obe::Animation::AnimationGroup::pushTexture;
        bindAnimationGroup["removeTextureByIndex"]
            = &obe::Animation::AnimationGroup::removeTextureByIndex;
        bindAnimationGroup["reset"] = &obe::Animation::AnimationGroup::reset;
        bindAnimationGroup["setDelay"] = &obe::Animation::AnimationGroup::setDelay;
        bindAnimationGroup["setLoops"] = &obe::Animation::AnimationGroup::setLoops;
    }
    void LoadClassAnimator(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::Animator> bindAnimator
            = AnimationNamespace.new_usertype<obe::Animation::Animator>(
                "Animator", sol::call_constructor, sol::default_constructor);
        bindAnimator["clear"] = &obe::Animation::Animator::clear;
        bindAnimator["getAllAnimationName"]
            = &obe::Animation::Animator::getAllAnimationName;
        bindAnimator["getAnimation"] = &obe::Animation::Animator::getAnimation;
        bindAnimator["getKey"] = &obe::Animation::Animator::getKey;
        bindAnimator["getTexture"] = &obe::Animation::Animator::getTexture;
        bindAnimator["getTextureAtKey"] = &obe::Animation::Animator::getTextureAtKey;
        bindAnimator["load"] = sol::overload(
            [](obe::Animation::Animator* self, obe::System::Path path) -> void {
                return self->load(path);
            },
            [](obe::Animation::Animator* self, obe::System::Path path,
                obe::Engine::ResourceManager* resources) -> void {
                return self->load(path, resources);
            });
        bindAnimator["setKey"] = &obe::Animation::Animator::setKey;
        bindAnimator["setPaused"] = &obe::Animation::Animator::setPaused;
        bindAnimator["update"] = &obe::Animation::Animator::update;
        bindAnimator["setTarget"] = sol::overload(
            [](obe::Animation::Animator* self, obe::Graphics::Sprite& sprite) -> void {
                return self->setTarget(sprite);
            },
            [](obe::Animation::Animator* self, obe::Graphics::Sprite& sprite,
                obe::Animation::AnimatorTargetScaleMode targetScaleMode) -> void {
                return self->setTarget(sprite, targetScaleMode);
            });
    }
    void LoadClassValueTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::ValueTweening> bindValueTweening
            = AnimationNamespace.new_usertype<obe::Animation::ValueTweening>(
                "ValueTweening", sol::call_constructor,
                sol::constructors<obe::Animation::ValueTweening(obe::Time::TimeUnit),
                    obe::Animation::ValueTweening(
                        double, double, obe::Time::TimeUnit)>());
        bindValueTweening["from"] = &obe::Animation::ValueTweening::from;
        bindValueTweening["to"] = &obe::Animation::ValueTweening::to;
        bindValueTweening["ease"] = &obe::Animation::ValueTweening::ease;
        bindValueTweening["step"] = &obe::Animation::ValueTweening::step;
    }
    void LoadFunctionStringToAnimationPlayMode(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        AnimationNamespace.set_function(
            "stringToAnimationPlayMode", obe::Animation::stringToAnimationPlayMode);
    }
};