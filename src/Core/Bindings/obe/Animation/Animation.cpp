#include <Bindings/obe/Animation/Animation.hpp>

#include <Animation/Animation.hpp>
#include <Animation/AnimationGroup.hpp>
#include <Animation/Animator.hpp>
#include <Animation/Tweening.hpp>
#include <Graphics/Sprite.hpp>

#include <Bindings/Config.hpp>

namespace obe::animation::Bindings
{
    void LoadEnumAnimationPlayMode(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        AnimationNamespace.new_enum<obe::animation::AnimationPlayMode>("AnimationPlayMode",
            { { "OneTime", obe::animation::AnimationPlayMode::OneTime },
                { "Loop", obe::animation::AnimationPlayMode::Loop },
                { "Force", obe::animation::AnimationPlayMode::Force } });
    }
    void LoadEnumAnimationStatus(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        AnimationNamespace.new_enum<obe::animation::AnimationStatus>("AnimationStatus",
            { { "Play", obe::animation::AnimationStatus::Play },
                { "Call", obe::animation::AnimationStatus::Call } });
    }
    void LoadEnumAnimatorTargetScaleMode(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        AnimationNamespace.new_enum<obe::animation::AnimatorTargetScaleMode>(
            "AnimatorTargetScaleMode",
            { { "Fit", obe::animation::AnimatorTargetScaleMode::Fit },
                { "KeepRatio", obe::animation::AnimatorTargetScaleMode::KeepRatio },
                { "FixedWidth", obe::animation::AnimatorTargetScaleMode::FixedWidth },
                { "FixedHeight", obe::animation::AnimatorTargetScaleMode::FixedHeight },
                { "TextureSize", obe::animation::AnimatorTargetScaleMode::TextureSize } });
    }
    void LoadClassAnimation(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::Animation> bindAnimation
            = AnimationNamespace.new_usertype<obe::animation::Animation>("animation",
                sol::call_constructor, sol::constructors<obe::animation::Animation()>());
        bindAnimation["apply_parameters"] = &obe::animation::Animation::apply_parameters;
        bindAnimation["get_all_animation_groups_names"]
            = &obe::animation::Animation::get_all_animation_groups_names;
        bindAnimation["get_delay"] = &obe::animation::Animation::get_delay;
        bindAnimation["get_animation_group"] = &obe::animation::Animation::get_animation_group;
        bindAnimation["get_name"] = &obe::animation::Animation::get_name;
        bindAnimation["get_play_mode"] = &obe::animation::Animation::get_play_mode;
        bindAnimation["get_status"] = &obe::animation::Animation::get_status;
        bindAnimation["get_called_animation"] = &obe::animation::Animation::get_next_animation;
        bindAnimation["get_current_animation_group"]
            = &obe::animation::Animation::get_current_animation_group;
        bindAnimation["get_priority"] = &obe::animation::Animation::get_priority;
        bindAnimation["get_current_texture"] = &obe::animation::Animation::get_current_texture;
        bindAnimation["get_texture_at_index"] = &obe::animation::Animation::get_texture_at_index;
        bindAnimation["is_over"] = &obe::animation::Animation::is_over;
        bindAnimation["load_animation"] = sol::overload(
            [](obe::animation::Animation* self, const obe::system::Path& path) -> void {
                return self->load_animation(path);
            },
            [](obe::animation::Animation* self, const obe::system::Path& path,
                obe::engine::ResourceManager* resources) -> void {
                return self->load_animation(path, resources);
            });
        bindAnimation["reset"] = &obe::animation::Animation::reset;
        bindAnimation["update"] = &obe::animation::Animation::update;
        bindAnimation["set_anti_aliasing"] = &obe::animation::Animation::set_anti_aliasing;
        bindAnimation["is_anti_aliased"] = &obe::animation::Animation::is_anti_aliased;
        bindAnimation["make_state"] = &obe::animation::Animation::make_state;
    }
    void LoadClassAnimationGroup(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::AnimationGroup> bindAnimationGroup
            = AnimationNamespace.new_usertype<obe::animation::AnimationGroup>("AnimationGroup",
                sol::call_constructor,
                sol::constructors<obe::animation::AnimationGroup(std::string),
                    obe::animation::AnimationGroup(const obe::animation::AnimationGroup&)>());
        bindAnimationGroup["get_delay"] = &obe::animation::AnimationGroup::get_delay;
        bindAnimationGroup["get_current_index"] = &obe::animation::AnimationGroup::get_current_index;
        bindAnimationGroup["get_name"] = &obe::animation::AnimationGroup::get_name;
        bindAnimationGroup["get_textures_amount"] = &obe::animation::AnimationGroup::get_textures_amount;
        bindAnimationGroup["get_current_texture"] = &obe::animation::AnimationGroup::get_current_texture;
        bindAnimationGroup["is_over"] = &obe::animation::AnimationGroup::is_over;
        bindAnimationGroup["next"] = sol::overload(
            [](obe::animation::AnimationGroup* self) -> void { return self->next(); },
            [](obe::animation::AnimationGroup* self, bool force) -> void {
                return self->next(force);
            });
        bindAnimationGroup["previous"] = sol::overload(
            [](obe::animation::AnimationGroup* self) -> void { return self->previous(); },
            [](obe::animation::AnimationGroup* self, bool force) -> void {
                return self->previous(force);
            });
        bindAnimationGroup["push_texture"] = &obe::animation::AnimationGroup::push_texture;
        bindAnimationGroup["remove_texture_by_index"]
            = &obe::animation::AnimationGroup::remove_texture_by_index;
        bindAnimationGroup["reset"] = &obe::animation::AnimationGroup::reset;
        bindAnimationGroup["set_delay"] = &obe::animation::AnimationGroup::set_delay;
        bindAnimationGroup["set_loops"] = &obe::animation::AnimationGroup::set_loops;
    }
    void LoadClassAnimationState(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::AnimationState> bindAnimationState
            = AnimationNamespace.new_usertype<obe::animation::AnimationState>("AnimationState",
                sol::call_constructor,
                sol::constructors<obe::animation::AnimationState(
                    const obe::animation::Animation&)>());
        bindAnimationState["load"] = &obe::animation::AnimationState::load;
        bindAnimationState["get_status"] = &obe::animation::AnimationState::get_status;
        bindAnimationState["get_called_animation"]
            = &obe::animation::AnimationState::get_called_animation;
        bindAnimationState["get_animation_group"]
            = &obe::animation::AnimationState::get_animation_group;
        bindAnimationState["get_current_animation_group"]
            = &obe::animation::AnimationState::get_current_animation_group;
        bindAnimationState["get_current_texture"] = &obe::animation::AnimationState::get_texture;
        bindAnimationState["is_over"] = &obe::animation::AnimationState::is_over;
        bindAnimationState["reset"] = &obe::animation::AnimationState::reset;
        bindAnimationState["update"] = &obe::animation::AnimationState::update;
        bindAnimationState["get_animation"]
            = [](obe::animation::AnimationState* self) -> const obe::animation::Animation* {
            return &self->get_animation();
        };
    }
    void LoadClassAnimator(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::Animator> bindAnimator
            = AnimationNamespace.new_usertype<obe::animation::Animator>(
                "Animator", sol::call_constructor, sol::constructors<obe::animation::Animator()>());
        bindAnimator["clear"] = &obe::animation::Animator::clear;
        bindAnimator["get_all_animations_names"] = &obe::animation::Animator::get_all_animations_names;
        bindAnimator["get_animation"] = &obe::animation::Animator::get_animation;
        bindAnimator["get_current_animation_name"] = &obe::animation::Animator::get_current_animation_name;
        bindAnimator["get_current_texture"] = &obe::animation::Animator::get_current_texture;
        bindAnimator["load"]
            = sol::overload([](obe::animation::Animator* self,
                                obe::system::Path path) -> void { return self->load(path); },
                [](obe::animation::Animator* self, obe::system::Path path,
                    obe::engine::ResourceManager* resources) -> void {
                    return self->load(path, resources);
                });
        bindAnimator["set_animation"] = &obe::animation::Animator::set_animation;
        bindAnimator["set_paused"] = &obe::animation::Animator::set_paused;
        bindAnimator["update"] = &obe::animation::Animator::update;
        bindAnimator["set_target"] = sol::overload(
            [](obe::animation::Animator* self, obe::graphics::Sprite& sprite) -> void {
                return self->set_target(sprite);
            },
            [](obe::animation::Animator* self, obe::graphics::Sprite& sprite,
                obe::animation::AnimatorTargetScaleMode targetScaleMode) -> void {
                return self->set_target(sprite, targetScaleMode);
            });
        bindAnimator["get_filesystem_path"] = &obe::animation::Animator::get_filesystem_path;
        bindAnimator["make_state"] = &obe::animation::Animator::make_state;
    }
    void LoadClassAnimatorState(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::AnimatorState> bindAnimatorState
            = AnimationNamespace.new_usertype<obe::animation::AnimatorState>("AnimatorState",
                sol::call_constructor,
                sol::constructors<obe::animation::AnimatorState(
                    const obe::animation::Animator&)>());
        bindAnimatorState["load"] = &obe::animation::AnimatorState::load;
        bindAnimatorState["get_current_animation_name"] = &obe::animation::AnimatorState::get_current_animation_name;
        bindAnimatorState["set_animation"] = &obe::animation::AnimatorState::set_animation;
        bindAnimatorState["set_paused"] = &obe::animation::AnimatorState::set_paused;
        bindAnimatorState["update"] = &obe::animation::AnimatorState::update;
        bindAnimatorState["set_target"] = sol::overload(
            [](obe::animation::AnimatorState* self, obe::graphics::Sprite& sprite) -> void {
                return self->set_target(sprite);
            },
            [](obe::animation::AnimatorState* self, obe::graphics::Sprite& sprite,
                obe::animation::AnimatorTargetScaleMode targetScaleMode) -> void {
                return self->set_target(sprite, targetScaleMode);
            });
        bindAnimatorState["reset"] = &obe::animation::AnimatorState::reset;
        bindAnimatorState["get_target"] = &obe::animation::AnimatorState::get_target;
        bindAnimatorState["get_current_animation"]
            = &obe::animation::AnimatorState::get_current_animation;
        bindAnimatorState["get_current_texture"] = &obe::animation::AnimatorState::get_current_texture;
        bindAnimatorState["get_animator"]
            = [](obe::animation::AnimatorState* self) -> const obe::animation::Animator* {
            return &self->get_animator();
        };
    }
    void LoadClassColorTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<obe::graphics::Color>> bindColorTweening
            = AnimationNamespace.new_usertype<obe::animation::ValueTweening<obe::graphics::Color>>(
                "ColorTweening", sol::call_constructor,
                sol::constructors<obe::animation::ValueTweening<obe::graphics::Color>(
                                      obe::time::TimeUnit),
                    obe::animation::ValueTweening<obe::graphics::Color>(
                        obe::time::TimeUnit, obe::animation::easing::EasingFunction),
                    obe::animation::ValueTweening<obe::graphics::Color>(
                        obe::graphics::Color, obe::graphics::Color, obe::time::TimeUnit),
                    obe::animation::ValueTweening<obe::graphics::Color>(obe::graphics::Color,
                        obe::graphics::Color, obe::time::TimeUnit,
                        obe::animation::easing::EasingFunction)>());
        bindColorTweening["from"] = &obe::animation::ValueTweening<obe::graphics::Color>::from;
        bindColorTweening["to"] = &obe::animation::ValueTweening<obe::graphics::Color>::to;
        bindColorTweening["ease"] = &obe::animation::ValueTweening<obe::graphics::Color>::ease;
        bindColorTweening["start"] = &obe::animation::ValueTweening<obe::graphics::Color>::start;
        bindColorTweening["stop"] = &obe::animation::ValueTweening<obe::graphics::Color>::stop;
        bindColorTweening["seek"] = &obe::animation::ValueTweening<obe::graphics::Color>::seek;
        bindColorTweening["reset"] = &obe::animation::ValueTweening<obe::graphics::Color>::reset;
        bindColorTweening["resume"] = &obe::animation::ValueTweening<obe::graphics::Color>::resume;
        bindColorTweening["done"] = &obe::animation::ValueTweening<obe::graphics::Color>::done;
        bindColorTweening["step"] = &obe::animation::ValueTweening<obe::graphics::Color>::step;
    }
    void LoadClassUnitVectorTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<obe::Transform::UnitVector>>
            bindUnitVectorTweening = AnimationNamespace.new_usertype<
                obe::animation::ValueTweening<obe::Transform::UnitVector>>("UnitVectorTweening",
                sol::call_constructor,
                sol::constructors<obe::animation::ValueTweening<obe::Transform::UnitVector>(
                                      obe::time::TimeUnit),
                    obe::animation::ValueTweening<obe::Transform::UnitVector>(
                        obe::time::TimeUnit, const obe::animation::easing::EasingFunction&),
                    obe::animation::ValueTweening<obe::Transform::UnitVector>(
                        obe::Transform::UnitVector, obe::Transform::UnitVector,
                        obe::time::TimeUnit),
                    obe::animation::ValueTweening<obe::Transform::UnitVector>(
                        obe::Transform::UnitVector, obe::Transform::UnitVector, obe::time::TimeUnit,
                        const obe::animation::easing::EasingFunction&)>());
        bindUnitVectorTweening["from"]
            = &obe::animation::ValueTweening<obe::Transform::UnitVector>::from;
        bindUnitVectorTweening["to"]
            = &obe::animation::ValueTweening<obe::Transform::UnitVector>::to;
        bindUnitVectorTweening["ease"]
            = &obe::animation::ValueTweening<obe::Transform::UnitVector>::ease;
        bindUnitVectorTweening["start"]
            = &obe::animation::ValueTweening<obe::Transform::UnitVector>::start;
        bindUnitVectorTweening["stop"]
            = &obe::animation::ValueTweening<obe::Transform::UnitVector>::stop;
        bindUnitVectorTweening["seek"]
            = &obe::animation::ValueTweening<obe::Transform::UnitVector>::seek;
        bindUnitVectorTweening["reset"]
            = &obe::animation::ValueTweening<obe::Transform::UnitVector>::reset;
        bindUnitVectorTweening["resume"]
            = &obe::animation::ValueTweening<obe::Transform::UnitVector>::resume;
        bindUnitVectorTweening["done"]
            = &obe::animation::ValueTweening<obe::Transform::UnitVector>::done;
        bindUnitVectorTweening["step"]
            = &obe::animation::ValueTweening<obe::Transform::UnitVector>::step;
    }
    void LoadClassRectTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<obe::Transform::Rect>> bindRectTweening
            = AnimationNamespace.new_usertype<obe::animation::ValueTweening<obe::Transform::Rect>>(
                "RectTweening", sol::call_constructor,
                sol::constructors<obe::animation::ValueTweening<obe::Transform::Rect>(
                                      obe::time::TimeUnit),
                    obe::animation::ValueTweening<obe::Transform::Rect>(
                        obe::time::TimeUnit, const obe::animation::easing::EasingFunction&),
                    obe::animation::ValueTweening<obe::Transform::Rect>(
                        obe::Transform::Rect, obe::Transform::Rect, obe::time::TimeUnit),
                    obe::animation::ValueTweening<obe::Transform::Rect>(obe::Transform::Rect,
                        obe::Transform::Rect, obe::time::TimeUnit,
                        const obe::animation::easing::EasingFunction&)>());
        bindRectTweening["from"] = &obe::animation::ValueTweening<obe::Transform::Rect>::from;
        bindRectTweening["to"] = &obe::animation::ValueTweening<obe::Transform::Rect>::to;
        bindRectTweening["ease"] = &obe::animation::ValueTweening<obe::Transform::Rect>::ease;
        bindRectTweening["start"] = &obe::animation::ValueTweening<obe::Transform::Rect>::start;
        bindRectTweening["stop"] = &obe::animation::ValueTweening<obe::Transform::Rect>::stop;
        bindRectTweening["seek"] = &obe::animation::ValueTweening<obe::Transform::Rect>::seek;
        bindRectTweening["reset"] = &obe::animation::ValueTweening<obe::Transform::Rect>::reset;
        bindRectTweening["resume"] = &obe::animation::ValueTweening<obe::Transform::Rect>::resume;
        bindRectTweening["done"] = &obe::animation::ValueTweening<obe::Transform::Rect>::done;
        bindRectTweening["step"] = &obe::animation::ValueTweening<obe::Transform::Rect>::step;
    }
    void LoadClassTrajectoryTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<obe::collision::Trajectory>>
            bindTrajectoryTweening = AnimationNamespace.new_usertype<
                obe::animation::ValueTweening<obe::collision::Trajectory>>("TrajectoryTweening",
                sol::call_constructor,
                sol::constructors<obe::animation::ValueTweening<obe::collision::Trajectory>(
                                      obe::time::TimeUnit),
                    obe::animation::ValueTweening<obe::collision::Trajectory>(
                        obe::time::TimeUnit, const obe::animation::easing::EasingFunction&),
                    obe::animation::ValueTweening<obe::collision::Trajectory>(
                        obe::collision::Trajectory, obe::collision::Trajectory,
                        obe::time::TimeUnit),
                    obe::animation::ValueTweening<obe::collision::Trajectory>(
                        obe::collision::Trajectory, obe::collision::Trajectory, obe::time::TimeUnit,
                        const obe::animation::easing::EasingFunction&)>());
        bindTrajectoryTweening["from"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::from;
        bindTrajectoryTweening["to"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::to;
        bindTrajectoryTweening["ease"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::ease;
        bindTrajectoryTweening["start"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::start;
        bindTrajectoryTweening["stop"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::stop;
        bindTrajectoryTweening["seek"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::seek;
        bindTrajectoryTweening["reset"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::reset;
        bindTrajectoryTweening["resume"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::resume;
        bindTrajectoryTweening["done"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::done;
        bindTrajectoryTweening["step"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::step;
    }
    void LoadClassIntTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<int>> bindIntTweening
            = AnimationNamespace.new_usertype<obe::animation::ValueTweening<int>>("IntTweening",
                sol::call_constructor,
                sol::constructors<obe::animation::ValueTweening<int>(obe::time::TimeUnit),
                    obe::animation::ValueTweening<int>(
                        obe::time::TimeUnit, const obe::animation::easing::EasingFunction&),
                    obe::animation::ValueTweening<int>(int, int, obe::time::TimeUnit),
                    obe::animation::ValueTweening<int>(int, int, obe::time::TimeUnit,
                        const obe::animation::easing::EasingFunction&)>());
        bindIntTweening["from"] = &obe::animation::ValueTweening<int>::from;
        bindIntTweening["to"] = &obe::animation::ValueTweening<int>::to;
        bindIntTweening["ease"] = &obe::animation::ValueTweening<int>::ease;
        bindIntTweening["start"] = &obe::animation::ValueTweening<int>::start;
        bindIntTweening["stop"] = &obe::animation::ValueTweening<int>::stop;
        bindIntTweening["seek"] = &obe::animation::ValueTweening<int>::seek;
        bindIntTweening["reset"] = &obe::animation::ValueTweening<int>::reset;
        bindIntTweening["resume"] = &obe::animation::ValueTweening<int>::resume;
        bindIntTweening["done"] = &obe::animation::ValueTweening<int>::done;
        bindIntTweening["step"] = &obe::animation::ValueTweening<int>::step;
    }
    void LoadClassDoubleTweening(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<double>> bindDoubleTweening
            = AnimationNamespace.new_usertype<obe::animation::ValueTweening<double>>(
                "DoubleTweening", sol::call_constructor,
                sol::constructors<obe::animation::ValueTweening<double>(obe::time::TimeUnit),
                    obe::animation::ValueTweening<double>(
                        obe::time::TimeUnit, const obe::animation::easing::EasingFunction&),
                    obe::animation::ValueTweening<double>(double, double, obe::time::TimeUnit),
                    obe::animation::ValueTweening<double>(double, double, obe::time::TimeUnit,
                        const obe::animation::easing::EasingFunction&)>());
        bindDoubleTweening["from"] = &obe::animation::ValueTweening<double>::from;
        bindDoubleTweening["to"] = &obe::animation::ValueTweening<double>::to;
        bindDoubleTweening["ease"] = &obe::animation::ValueTweening<double>::ease;
        bindDoubleTweening["start"] = &obe::animation::ValueTweening<double>::start;
        bindDoubleTweening["stop"] = &obe::animation::ValueTweening<double>::stop;
        bindDoubleTweening["seek"] = &obe::animation::ValueTweening<double>::seek;
        bindDoubleTweening["reset"] = &obe::animation::ValueTweening<double>::reset;
        bindDoubleTweening["resume"] = &obe::animation::ValueTweening<double>::resume;
        bindDoubleTweening["done"] = &obe::animation::ValueTweening<double>::done;
        bindDoubleTweening["step"] = &obe::animation::ValueTweening<double>::step;
    }
    void LoadFunctionTemplateSpecializationExistsImpl(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
    }
    void LoadFunctionTween(sol::state_view state)
    {
        sol::table AnimationNamespace = state["obe"]["animation"].get<sol::table>();
        AnimationNamespace["Tween"] = sol::overload(
            [](obe::graphics::Color from, obe::graphics::Color to,
                obe::time::TimeUnit duration) -> ValueTweening<obe::graphics::Color> {
                return obe::animation::ValueTweening<obe::graphics::Color>(from, to, duration);
            },
            [](obe::graphics::Color from, obe::graphics::Color to, obe::time::TimeUnit duration,
                const obe::animation::easing::EasingFunction& easing)
                -> ValueTweening<obe::graphics::Color> {
                return obe::animation::ValueTweening<obe::graphics::Color>(
                    from, to, duration, easing);
            },
            [](obe::Transform::UnitVector from, obe::Transform::UnitVector to,
                obe::time::TimeUnit duration) -> ValueTweening<obe::Transform::UnitVector> {
                return obe::animation::ValueTweening<obe::Transform::UnitVector>(
                    from, to, duration);
            },
            [](obe::Transform::UnitVector from, obe::Transform::UnitVector to,
                obe::time::TimeUnit duration, const obe::animation::easing::EasingFunction& easing)
                -> ValueTweening<obe::Transform::UnitVector> {
                return obe::animation::ValueTweening<obe::Transform::UnitVector>(
                    from, to, duration, easing);
            },
            [](obe::Transform::Rect from, obe::Transform::Rect to,
                obe::time::TimeUnit duration) -> ValueTweening<obe::Transform::Rect> {
                return obe::animation::ValueTweening<obe::Transform::Rect>(from, to, duration);
            },
            [](obe::Transform::Rect from, obe::Transform::Rect to, obe::time::TimeUnit duration,
                const obe::animation::easing::EasingFunction& easing)
                -> ValueTweening<obe::Transform::Rect> {
                return obe::animation::ValueTweening<obe::Transform::Rect>(
                    from, to, duration, easing);
            },
            [](obe::collision::Trajectory from, obe::collision::Trajectory to,
                obe::time::TimeUnit duration) -> ValueTweening<obe::collision::Trajectory> {
                return obe::animation::ValueTweening<obe::collision::Trajectory>(
                    from, to, duration);
            },
            [](obe::collision::Trajectory from, obe::collision::Trajectory to,
                obe::time::TimeUnit duration, const obe::animation::easing::EasingFunction& easing)
                -> ValueTweening<obe::collision::Trajectory> {
                return obe::animation::ValueTweening<obe::collision::Trajectory>(
                    from, to, duration, easing);
            },
            [](int from, int to, obe::time::TimeUnit duration) -> ValueTweening<int> {
                return obe::animation::ValueTweening<int>(from, to, duration);
            },
            [](int from, int to, obe::time::TimeUnit duration,
                const obe::animation::easing::EasingFunction& easing) -> ValueTweening<int> {
                return obe::animation::ValueTweening<int>(from, to, duration, easing);
            },
            [](double from, double to, obe::time::TimeUnit duration) -> ValueTweening<double> {
                return obe::animation::ValueTweening<double>(from, to, duration);
            },
            [](double from, double to, obe::time::TimeUnit duration,
                const obe::animation::easing::EasingFunction& easing) -> ValueTweening<double> {
                return obe::animation::ValueTweening<double>(from, to, duration, easing);
            });
    }
};