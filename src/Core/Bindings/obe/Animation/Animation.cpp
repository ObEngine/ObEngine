#include <Bindings/obe/Animation/Animation.hpp>

#include <Animation/Animation.hpp>
#include <Animation/AnimationGroup.hpp>
#include <Animation/Animator.hpp>
#include <Animation/Tweening.hpp>
#include <Graphics/Sprite.hpp>

#include <Bindings/Config.hpp>

namespace obe::Animation::Bindings
{
    void LoadEnumAnimationPlayMode(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        AnimationNamespace.new_enum<obe::Animation::AnimationPlayMode>("AnimationPlayMode",
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
                { "KeepRatio", obe::Animation::AnimatorTargetScaleMode::KeepRatio },
                { "FixedWidth", obe::Animation::AnimatorTargetScaleMode::FixedWidth },
                { "FixedHeight", obe::Animation::AnimatorTargetScaleMode::FixedHeight },
                { "TextureSize", obe::Animation::AnimatorTargetScaleMode::TextureSize } });
    }
    void LoadClassAnimation(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::Animation> bindAnimation
            = AnimationNamespace.new_usertype<obe::Animation::Animation>("Animation",
                sol::call_constructor, sol::constructors<obe::Animation::Animation()>());
        bindAnimation["applyParameters"] = &obe::Animation::Animation::applyParameters;
        bindAnimation["getAllAnimationGroupName"]
            = &obe::Animation::Animation::getAllAnimationGroupName;
        bindAnimation["getDelay"] = &obe::Animation::Animation::getDelay;
        bindAnimation["getAnimationGroup"] = &obe::Animation::Animation::getAnimationGroup;
        bindAnimation["getName"] = &obe::Animation::Animation::getName;
        bindAnimation["getPlayMode"] = &obe::Animation::Animation::getPlayMode;
        bindAnimation["getStatus"] = &obe::Animation::Animation::getStatus;
        bindAnimation["getCalledAnimation"] = &obe::Animation::Animation::getCalledAnimation;
        bindAnimation["getCurrentAnimationGroup"]
            = &obe::Animation::Animation::getCurrentAnimationGroup;
        bindAnimation["getPriority"] = &obe::Animation::Animation::getPriority;
        bindAnimation["getTexture"] = &obe::Animation::Animation::getTexture;
        bindAnimation["getTextureAtIndex"] = &obe::Animation::Animation::getTextureAtIndex;
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
        bindAnimation["makeState"] = &obe::Animation::Animation::makeState;
    }
    void LoadClassAnimationGroup(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::AnimationGroup> bindAnimationGroup
            = AnimationNamespace.new_usertype<obe::Animation::AnimationGroup>("AnimationGroup",
                sol::call_constructor,
                sol::constructors<obe::Animation::AnimationGroup(std::string),
                    obe::Animation::AnimationGroup(const obe::Animation::AnimationGroup&)>());
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
    void LoadClassAnimationState(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::AnimationState> bindAnimationState
            = AnimationNamespace.new_usertype<obe::Animation::AnimationState>("AnimationState",
                sol::call_constructor,
                sol::constructors<obe::Animation::AnimationState(
                    const obe::Animation::Animation&)>());
        bindAnimationState["load"] = &obe::Animation::AnimationState::load;
        bindAnimationState["getStatus"] = &obe::Animation::AnimationState::getStatus;
        bindAnimationState["getCalledAnimation"]
            = &obe::Animation::AnimationState::getCalledAnimation;
        bindAnimationState["getAnimationGroup"]
            = &obe::Animation::AnimationState::getAnimationGroup;
        bindAnimationState["getCurrentAnimationGroup"]
            = &obe::Animation::AnimationState::getCurrentAnimationGroup;
        bindAnimationState["getTexture"] = &obe::Animation::AnimationState::getTexture;
        bindAnimationState["isOver"] = &obe::Animation::AnimationState::isOver;
        bindAnimationState["reset"] = &obe::Animation::AnimationState::reset;
        bindAnimationState["update"] = &obe::Animation::AnimationState::update;
        bindAnimationState["getAnimation"]
            = [](obe::Animation::AnimationState* self) -> const obe::Animation::Animation* {
            return &self->getAnimation();
        };
    }
    void LoadClassAnimator(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::Animator> bindAnimator
            = AnimationNamespace.new_usertype<obe::Animation::Animator>(
                "Animator", sol::call_constructor, sol::constructors<obe::Animation::Animator()>());
        bindAnimator["clear"] = &obe::Animation::Animator::clear;
        bindAnimator["getAllAnimationName"] = &obe::Animation::Animator::getAllAnimationName;
        bindAnimator["getAnimation"] = &obe::Animation::Animator::getAnimation;
        bindAnimator["getKey"] = &obe::Animation::Animator::getKey;
        bindAnimator["getTexture"] = &obe::Animation::Animator::getTexture;
        bindAnimator["getTextureAtKey"] = &obe::Animation::Animator::getTextureAtKey;
        bindAnimator["load"]
            = sol::overload([](obe::Animation::Animator* self,
                                obe::System::Path path) -> void { return self->load(path); },
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
        bindAnimator["getPath"] = &obe::Animation::Animator::getPath;
        bindAnimator["makeState"] = &obe::Animation::Animator::makeState;
    }
    void LoadClassAnimatorState(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::AnimatorState> bindAnimatorState
            = AnimationNamespace.new_usertype<obe::Animation::AnimatorState>("AnimatorState",
                sol::call_constructor,
                sol::constructors<obe::Animation::AnimatorState(
                    const obe::Animation::Animator&)>());
        bindAnimatorState["load"] = &obe::Animation::AnimatorState::load;
        bindAnimatorState["getKey"] = &obe::Animation::AnimatorState::getKey;
        bindAnimatorState["setKey"] = &obe::Animation::AnimatorState::setKey;
        bindAnimatorState["setPaused"] = &obe::Animation::AnimatorState::setPaused;
        bindAnimatorState["update"] = &obe::Animation::AnimatorState::update;
        bindAnimatorState["setTarget"] = sol::overload(
            [](obe::Animation::AnimatorState* self, obe::Graphics::Sprite& sprite) -> void {
                return self->setTarget(sprite);
            },
            [](obe::Animation::AnimatorState* self, obe::Graphics::Sprite& sprite,
                obe::Animation::AnimatorTargetScaleMode targetScaleMode) -> void {
                return self->setTarget(sprite, targetScaleMode);
            });
        bindAnimatorState["reset"] = &obe::Animation::AnimatorState::reset;
        bindAnimatorState["getTarget"] = &obe::Animation::AnimatorState::getTarget;
        bindAnimatorState["getCurrentAnimation"]
            = &obe::Animation::AnimatorState::getCurrentAnimation;
        bindAnimatorState["getTexture"] = &obe::Animation::AnimatorState::getTexture;
        bindAnimatorState["getAnimator"]
            = [](obe::Animation::AnimatorState* self) -> const obe::Animation::Animator* {
            return &self->getAnimator();
        };
    }
    void LoadClassColorTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::ValueTweening<obe::Graphics::Color>> bindColorTweening
            = AnimationNamespace.new_usertype<obe::Animation::ValueTweening<obe::Graphics::Color>>(
                "ColorTweening", sol::call_constructor,
                sol::constructors<obe::Animation::ValueTweening<obe::Graphics::Color>(
                                      obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<obe::Graphics::Color>(
                        obe::Time::TimeUnit, const obe::Animation::Easing::EasingFunction&),
                    obe::Animation::ValueTweening<obe::Graphics::Color>(
                        obe::Graphics::Color, obe::Graphics::Color, obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<obe::Graphics::Color>(obe::Graphics::Color,
                        obe::Graphics::Color, obe::Time::TimeUnit,
                        const obe::Animation::Easing::EasingFunction&)>());
        bindColorTweening["from"] = &obe::Animation::ValueTweening<obe::Graphics::Color>::from;
        bindColorTweening["to"] = &obe::Animation::ValueTweening<obe::Graphics::Color>::to;
        bindColorTweening["ease"] = &obe::Animation::ValueTweening<obe::Graphics::Color>::ease;
        bindColorTweening["start"] = &obe::Animation::ValueTweening<obe::Graphics::Color>::start;
        bindColorTweening["stop"] = &obe::Animation::ValueTweening<obe::Graphics::Color>::stop;
        bindColorTweening["seek"] = &obe::Animation::ValueTweening<obe::Graphics::Color>::seek;
        bindColorTweening["reset"] = &obe::Animation::ValueTweening<obe::Graphics::Color>::reset;
        bindColorTweening["resume"] = &obe::Animation::ValueTweening<obe::Graphics::Color>::resume;
        bindColorTweening["done"] = &obe::Animation::ValueTweening<obe::Graphics::Color>::done;
        bindColorTweening["step"] = &obe::Animation::ValueTweening<obe::Graphics::Color>::step;
    }
    void LoadClassUnitVectorTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::ValueTweening<obe::Transform::UnitVector>>
            bindUnitVectorTweening = AnimationNamespace.new_usertype<
                obe::Animation::ValueTweening<obe::Transform::UnitVector>>("UnitVectorTweening",
                sol::call_constructor,
                sol::constructors<obe::Animation::ValueTweening<obe::Transform::UnitVector>(
                                      obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<obe::Transform::UnitVector>(
                        obe::Time::TimeUnit, const obe::Animation::Easing::EasingFunction&),
                    obe::Animation::ValueTweening<obe::Transform::UnitVector>(
                        obe::Transform::UnitVector, obe::Transform::UnitVector,
                        obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<obe::Transform::UnitVector>(
                        obe::Transform::UnitVector, obe::Transform::UnitVector, obe::Time::TimeUnit,
                        const obe::Animation::Easing::EasingFunction&)>());
        bindUnitVectorTweening["from"]
            = &obe::Animation::ValueTweening<obe::Transform::UnitVector>::from;
        bindUnitVectorTweening["to"]
            = &obe::Animation::ValueTweening<obe::Transform::UnitVector>::to;
        bindUnitVectorTweening["ease"]
            = &obe::Animation::ValueTweening<obe::Transform::UnitVector>::ease;
        bindUnitVectorTweening["start"]
            = &obe::Animation::ValueTweening<obe::Transform::UnitVector>::start;
        bindUnitVectorTweening["stop"]
            = &obe::Animation::ValueTweening<obe::Transform::UnitVector>::stop;
        bindUnitVectorTweening["seek"]
            = &obe::Animation::ValueTweening<obe::Transform::UnitVector>::seek;
        bindUnitVectorTweening["reset"]
            = &obe::Animation::ValueTweening<obe::Transform::UnitVector>::reset;
        bindUnitVectorTweening["resume"]
            = &obe::Animation::ValueTweening<obe::Transform::UnitVector>::resume;
        bindUnitVectorTweening["done"]
            = &obe::Animation::ValueTweening<obe::Transform::UnitVector>::done;
        bindUnitVectorTweening["step"]
            = &obe::Animation::ValueTweening<obe::Transform::UnitVector>::step;
    }
    void LoadClassRectTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::ValueTweening<obe::Transform::Rect>> bindRectTweening
            = AnimationNamespace.new_usertype<obe::Animation::ValueTweening<obe::Transform::Rect>>(
                "RectTweening", sol::call_constructor,
                sol::constructors<obe::Animation::ValueTweening<obe::Transform::Rect>(
                                      obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<obe::Transform::Rect>(
                        obe::Time::TimeUnit, const obe::Animation::Easing::EasingFunction&),
                    obe::Animation::ValueTweening<obe::Transform::Rect>(
                        obe::Transform::Rect, obe::Transform::Rect, obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<obe::Transform::Rect>(obe::Transform::Rect,
                        obe::Transform::Rect, obe::Time::TimeUnit,
                        const obe::Animation::Easing::EasingFunction&)>());
        bindRectTweening["from"] = &obe::Animation::ValueTweening<obe::Transform::Rect>::from;
        bindRectTweening["to"] = &obe::Animation::ValueTweening<obe::Transform::Rect>::to;
        bindRectTweening["ease"] = &obe::Animation::ValueTweening<obe::Transform::Rect>::ease;
        bindRectTweening["start"] = &obe::Animation::ValueTweening<obe::Transform::Rect>::start;
        bindRectTweening["stop"] = &obe::Animation::ValueTweening<obe::Transform::Rect>::stop;
        bindRectTweening["seek"] = &obe::Animation::ValueTweening<obe::Transform::Rect>::seek;
        bindRectTweening["reset"] = &obe::Animation::ValueTweening<obe::Transform::Rect>::reset;
        bindRectTweening["resume"] = &obe::Animation::ValueTweening<obe::Transform::Rect>::resume;
        bindRectTweening["done"] = &obe::Animation::ValueTweening<obe::Transform::Rect>::done;
        bindRectTweening["step"] = &obe::Animation::ValueTweening<obe::Transform::Rect>::step;
    }
    void LoadClassTrajectoryTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::ValueTweening<obe::Collision::Trajectory>>
            bindTrajectoryTweening = AnimationNamespace.new_usertype<
                obe::Animation::ValueTweening<obe::Collision::Trajectory>>("TrajectoryTweening",
                sol::call_constructor,
                sol::constructors<obe::Animation::ValueTweening<obe::Collision::Trajectory>(
                                      obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<obe::Collision::Trajectory>(
                        obe::Time::TimeUnit, const obe::Animation::Easing::EasingFunction&),
                    obe::Animation::ValueTweening<obe::Collision::Trajectory>(
                        obe::Collision::Trajectory, obe::Collision::Trajectory,
                        obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<obe::Collision::Trajectory>(
                        obe::Collision::Trajectory, obe::Collision::Trajectory, obe::Time::TimeUnit,
                        const obe::Animation::Easing::EasingFunction&)>());
        bindTrajectoryTweening["from"]
            = &obe::Animation::ValueTweening<obe::Collision::Trajectory>::from;
        bindTrajectoryTweening["to"]
            = &obe::Animation::ValueTweening<obe::Collision::Trajectory>::to;
        bindTrajectoryTweening["ease"]
            = &obe::Animation::ValueTweening<obe::Collision::Trajectory>::ease;
        bindTrajectoryTweening["start"]
            = &obe::Animation::ValueTweening<obe::Collision::Trajectory>::start;
        bindTrajectoryTweening["stop"]
            = &obe::Animation::ValueTweening<obe::Collision::Trajectory>::stop;
        bindTrajectoryTweening["seek"]
            = &obe::Animation::ValueTweening<obe::Collision::Trajectory>::seek;
        bindTrajectoryTweening["reset"]
            = &obe::Animation::ValueTweening<obe::Collision::Trajectory>::reset;
        bindTrajectoryTweening["resume"]
            = &obe::Animation::ValueTweening<obe::Collision::Trajectory>::resume;
        bindTrajectoryTweening["done"]
            = &obe::Animation::ValueTweening<obe::Collision::Trajectory>::done;
        bindTrajectoryTweening["step"]
            = &obe::Animation::ValueTweening<obe::Collision::Trajectory>::step;
    }
    void LoadClassIntTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::ValueTweening<int>> bindIntTweening
            = AnimationNamespace.new_usertype<obe::Animation::ValueTweening<int>>("IntTweening",
                sol::call_constructor,
                sol::constructors<obe::Animation::ValueTweening<int>(obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<int>(
                        obe::Time::TimeUnit, const obe::Animation::Easing::EasingFunction&),
                    obe::Animation::ValueTweening<int>(int, int, obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<int>(int, int, obe::Time::TimeUnit,
                        const obe::Animation::Easing::EasingFunction&)>());
        bindIntTweening["from"] = &obe::Animation::ValueTweening<int>::from;
        bindIntTweening["to"] = &obe::Animation::ValueTweening<int>::to;
        bindIntTweening["ease"] = &obe::Animation::ValueTweening<int>::ease;
        bindIntTweening["start"] = &obe::Animation::ValueTweening<int>::start;
        bindIntTweening["stop"] = &obe::Animation::ValueTweening<int>::stop;
        bindIntTweening["seek"] = &obe::Animation::ValueTweening<int>::seek;
        bindIntTweening["reset"] = &obe::Animation::ValueTweening<int>::reset;
        bindIntTweening["resume"] = &obe::Animation::ValueTweening<int>::resume;
        bindIntTweening["done"] = &obe::Animation::ValueTweening<int>::done;
        bindIntTweening["step"] = &obe::Animation::ValueTweening<int>::step;
    }
    void LoadClassDoubleTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        sol::usertype<obe::Animation::ValueTweening<double>> bindDoubleTweening
            = AnimationNamespace.new_usertype<obe::Animation::ValueTweening<double>>(
                "DoubleTweening", sol::call_constructor,
                sol::constructors<obe::Animation::ValueTweening<double>(obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<double>(
                        obe::Time::TimeUnit, const obe::Animation::Easing::EasingFunction&),
                    obe::Animation::ValueTweening<double>(double, double, obe::Time::TimeUnit),
                    obe::Animation::ValueTweening<double>(double, double, obe::Time::TimeUnit,
                        const obe::Animation::Easing::EasingFunction&)>());
        bindDoubleTweening["from"] = &obe::Animation::ValueTweening<double>::from;
        bindDoubleTweening["to"] = &obe::Animation::ValueTweening<double>::to;
        bindDoubleTweening["ease"] = &obe::Animation::ValueTweening<double>::ease;
        bindDoubleTweening["start"] = &obe::Animation::ValueTweening<double>::start;
        bindDoubleTweening["stop"] = &obe::Animation::ValueTweening<double>::stop;
        bindDoubleTweening["seek"] = &obe::Animation::ValueTweening<double>::seek;
        bindDoubleTweening["reset"] = &obe::Animation::ValueTweening<double>::reset;
        bindDoubleTweening["resume"] = &obe::Animation::ValueTweening<double>::resume;
        bindDoubleTweening["done"] = &obe::Animation::ValueTweening<double>::done;
        bindDoubleTweening["step"] = &obe::Animation::ValueTweening<double>::step;
    }
    void LoadFunctionStringToAnimationPlayMode(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        AnimationNamespace.set_function(
            "stringToAnimationPlayMode", &obe::Animation::stringToAnimationPlayMode);
    }
    void LoadFunctionStringToAnimatorTargetScaleMode(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        AnimationNamespace.set_function(
            "stringToAnimatorTargetScaleMode", &obe::Animation::stringToAnimatorTargetScaleMode);
    }
    void LoadFunctionTemplateSpecializationExistsImpl(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
    }
    void LoadFunctionTween(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["Animation"].get<sol::table>();
        AnimationNamespace["Tween"] = sol::overload(
            [](obe::Graphics::Color from, obe::Graphics::Color to,
                obe::Time::TimeUnit duration) -> ValueTweening<obe::Graphics::Color> {
                return obe::Animation::ValueTweening<obe::Graphics::Color>::ValueTweening(
                    from, to, duration);
            },
            [](obe::Graphics::Color from, obe::Graphics::Color to, obe::Time::TimeUnit duration,
                const obe::Animation::Easing::EasingFunction& easing)
                -> ValueTweening<obe::Graphics::Color> {
                return obe::Animation::ValueTweening<obe::Graphics::Color>::ValueTweening(
                    from, to, duration, easing);
            },
            [](obe::Transform::UnitVector from, obe::Transform::UnitVector to,
                obe::Time::TimeUnit duration) -> ValueTweening<obe::Transform::UnitVector> {
                return obe::Animation::ValueTweening<obe::Transform::UnitVector>::ValueTweening(
                    from, to, duration);
            },
            [](obe::Transform::UnitVector from, obe::Transform::UnitVector to,
                obe::Time::TimeUnit duration, const obe::Animation::Easing::EasingFunction& easing)
                -> ValueTweening<obe::Transform::UnitVector> {
                return obe::Animation::ValueTweening<obe::Transform::UnitVector>::ValueTweening(
                    from, to, duration, easing);
            },
            [](obe::Transform::Rect from, obe::Transform::Rect to,
                obe::Time::TimeUnit duration) -> ValueTweening<obe::Transform::Rect> {
                return obe::Animation::ValueTweening<obe::Transform::Rect>::ValueTweening(
                    from, to, duration);
            },
            [](obe::Transform::Rect from, obe::Transform::Rect to, obe::Time::TimeUnit duration,
                const obe::Animation::Easing::EasingFunction& easing)
                -> ValueTweening<obe::Transform::Rect> {
                return obe::Animation::ValueTweening<obe::Transform::Rect>::ValueTweening(
                    from, to, duration, easing);
            },
            [](obe::Collision::Trajectory from, obe::Collision::Trajectory to,
                obe::Time::TimeUnit duration) -> ValueTweening<obe::Collision::Trajectory> {
                return obe::Animation::ValueTweening<obe::Collision::Trajectory>::ValueTweening(
                    from, to, duration);
            },
            [](obe::Collision::Trajectory from, obe::Collision::Trajectory to,
                obe::Time::TimeUnit duration, const obe::Animation::Easing::EasingFunction& easing)
                -> ValueTweening<obe::Collision::Trajectory> {
                return obe::Animation::ValueTweening<obe::Collision::Trajectory>::ValueTweening(
                    from, to, duration, easing);
            },
            [](int from, int to, obe::Time::TimeUnit duration) -> ValueTweening<int> {
                return obe::Animation::ValueTweening<int>::ValueTweening(from, to, duration);
            },
            [](int from, int to, obe::Time::TimeUnit duration,
                const obe::Animation::Easing::EasingFunction& easing) -> ValueTweening<int> {
                return obe::Animation::ValueTweening<int>::ValueTweening(
                    from, to, duration, easing);
            },
            [](double from, double to, obe::Time::TimeUnit duration) -> ValueTweening<double> {
                return obe::Animation::ValueTweening<double>::ValueTweening(from, to, duration);
            },
            [](double from, double to, obe::Time::TimeUnit duration,
                const obe::Animation::Easing::EasingFunction& easing) -> ValueTweening<double> {
                return obe::Animation::ValueTweening<double>::ValueTweening(
                    from, to, duration, easing);
            });
    }
};