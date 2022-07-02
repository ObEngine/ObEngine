#include <Bindings/obe/animation/Animation.hpp>

#include <Animation/Animation.hpp>
#include <Animation/AnimationGroup.hpp>
#include <Animation/Animator.hpp>
#include <Animation/Tweening.hpp>
#include <Graphics/Sprite.hpp>

#include <Bindings/Config.hpp>

namespace obe::animation::bindings
{
    void load_enum_animation_play_mode(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        animation_namespace.new_enum<obe::animation::AnimationPlayMode>("AnimationPlayMode",
            { { "OneTime", obe::animation::AnimationPlayMode::OneTime },
                { "Loop", obe::animation::AnimationPlayMode::Loop },
                { "Force", obe::animation::AnimationPlayMode::Force } });
    }
    void load_enum_animation_command(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        animation_namespace.new_enum<obe::animation::AnimationCommand>("AnimationCommand",
            { { "Wait", obe::animation::AnimationCommand::Wait },
                { "PlayGroup", obe::animation::AnimationCommand::PlayGroup },
                { "SetAnimation", obe::animation::AnimationCommand::SetAnimation } });
    }
    void load_enum_animation_status(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        animation_namespace.new_enum<obe::animation::AnimationStatus>("AnimationStatus",
            { { "Play", obe::animation::AnimationStatus::Play },
                { "Call", obe::animation::AnimationStatus::Call } });
    }
    void load_enum_animator_target_scale_mode(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        animation_namespace.new_enum<obe::animation::AnimatorTargetScaleMode>(
            "AnimatorTargetScaleMode",
            { { "Fit", obe::animation::AnimatorTargetScaleMode::Fit },
                { "KeepRatio", obe::animation::AnimatorTargetScaleMode::KeepRatio },
                { "FixedWidth", obe::animation::AnimatorTargetScaleMode::FixedWidth },
                { "FixedHeight", obe::animation::AnimatorTargetScaleMode::FixedHeight },
                { "TextureSize", obe::animation::AnimatorTargetScaleMode::TextureSize } });
    }
    void load_class_animation(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::Animation> bind_animation
            = animation_namespace.new_usertype<obe::animation::Animation>("Animation",
                sol::call_constructor, sol::constructors<obe::animation::Animation()>(),
                sol::base_classes, sol::bases<obe::types::Serializable>());
        bind_animation["apply_parameters"] = &obe::animation::Animation::apply_parameters;
        bind_animation["get_all_animation_groups_names"]
            = &obe::animation::Animation::get_all_animation_groups_names;
        bind_animation["get_delay"] = &obe::animation::Animation::get_delay;
        bind_animation["get_animation_group"] = &obe::animation::Animation::get_animation_group;
        bind_animation["get_name"] = &obe::animation::Animation::get_name;
        bind_animation["get_play_mode"] = &obe::animation::Animation::get_play_mode;
        bind_animation["get_status"] = &obe::animation::Animation::get_status;
        bind_animation["get_next_animation"] = &obe::animation::Animation::get_next_animation;
        bind_animation["get_current_animation_group"]
            = &obe::animation::Animation::get_current_animation_group;
        bind_animation["get_priority"] = &obe::animation::Animation::get_priority;
        bind_animation["get_current_texture"] = &obe::animation::Animation::get_current_texture;
        bind_animation["get_texture_at_index"] = &obe::animation::Animation::get_texture_at_index;
        bind_animation["is_over"] = &obe::animation::Animation::is_over;
        bind_animation["load_animation"] = sol::overload(
            [](obe::animation::Animation* self, const obe::system::Path& path) -> void {
                return self->load_animation(path);
            },
            [](obe::animation::Animation* self, const obe::system::Path& path,
                obe::engine::ResourceManager* resources) -> void {
                return self->load_animation(path, resources);
            });
        bind_animation["reset"] = &obe::animation::Animation::reset;
        bind_animation["update"] = &obe::animation::Animation::update;
        bind_animation["set_anti_aliasing"] = &obe::animation::Animation::set_anti_aliasing;
        bind_animation["is_anti_aliased"] = &obe::animation::Animation::is_anti_aliased;
        bind_animation["make_state"] = &obe::animation::Animation::make_state;
        bind_animation["schema"] = &obe::animation::Animation::schema;
        bind_animation["dump"] = &obe::animation::Animation::dump;
        bind_animation["load"] = &obe::animation::Animation::load;
    }
    void load_class_animation_group(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::AnimationGroup> bind_animation_group
            = animation_namespace.new_usertype<obe::animation::AnimationGroup>("AnimationGroup",
                sol::call_constructor,
                sol::constructors<obe::animation::AnimationGroup(std::string),
                    obe::animation::AnimationGroup(const obe::animation::AnimationGroup&)>());
        bind_animation_group["get_delay"] = &obe::animation::AnimationGroup::get_delay;
        bind_animation_group["get_current_index"]
            = &obe::animation::AnimationGroup::get_current_index;
        bind_animation_group["get_name"] = &obe::animation::AnimationGroup::get_name;
        bind_animation_group["get_textures_amount"]
            = &obe::animation::AnimationGroup::get_textures_amount;
        bind_animation_group["get_current_texture"]
            = &obe::animation::AnimationGroup::get_current_texture;
        bind_animation_group["is_over"] = &obe::animation::AnimationGroup::is_over;
        bind_animation_group["next"] = sol::overload(
            [](obe::animation::AnimationGroup* self) -> void { return self->next(); },
            [](obe::animation::AnimationGroup* self, bool force) -> void {
                return self->next(force);
            });
        bind_animation_group["previous"] = sol::overload(
            [](obe::animation::AnimationGroup* self) -> void { return self->previous(); },
            [](obe::animation::AnimationGroup* self, bool force) -> void {
                return self->previous(force);
            });
        bind_animation_group["push_texture"] = &obe::animation::AnimationGroup::push_texture;
        bind_animation_group["remove_texture_by_index"]
            = &obe::animation::AnimationGroup::remove_texture_by_index;
        bind_animation_group["reset"] = &obe::animation::AnimationGroup::reset;
        bind_animation_group["set_delay"] = &obe::animation::AnimationGroup::set_delay;
        bind_animation_group["set_loops"] = &obe::animation::AnimationGroup::set_loops;
    }
    void load_class_animation_state(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::AnimationState> bind_animation_state
            = animation_namespace.new_usertype<obe::animation::AnimationState>("AnimationState",
                sol::call_constructor,
                sol::constructors<obe::animation::AnimationState(
                    const obe::animation::Animation&)>());
        bind_animation_state["load"] = &obe::animation::AnimationState::load;
        bind_animation_state["get_status"] = &obe::animation::AnimationState::get_status;
        bind_animation_state["get_next_animation"]
            = &obe::animation::AnimationState::get_next_animation;
        bind_animation_state["get_animation_group"]
            = &obe::animation::AnimationState::get_animation_group;
        bind_animation_state["get_current_animation_group"]
            = &obe::animation::AnimationState::get_current_animation_group;
        bind_animation_state["get_texture"] = &obe::animation::AnimationState::get_texture;
        bind_animation_state["is_over"] = &obe::animation::AnimationState::is_over;
        bind_animation_state["reset"] = &obe::animation::AnimationState::reset;
        bind_animation_state["update"] = &obe::animation::AnimationState::update;
        bind_animation_state["get_animation"]
            = [](obe::animation::AnimationState* self) -> const obe::animation::Animation* {
            return &self->get_animation();
        };
    }
    void load_class_animator(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::Animator> bind_animator
            = animation_namespace.new_usertype<obe::animation::Animator>(
                "Animator", sol::call_constructor, sol::constructors<obe::animation::Animator()>());
        bind_animator["clear"] = &obe::animation::Animator::clear;
        bind_animator["get_all_animations_names"]
            = &obe::animation::Animator::get_all_animations_names;
        bind_animator["get_animation"] = &obe::animation::Animator::get_animation;
        bind_animator["get_current_animation_name"]
            = &obe::animation::Animator::get_current_animation_name;
        bind_animator["get_current_texture"] = &obe::animation::Animator::get_current_texture;
        bind_animator["load"]
            = sol::overload([](obe::animation::Animator* self,
                                obe::system::Path path) -> void { return self->load(path); },
                [](obe::animation::Animator* self, obe::system::Path path,
                    obe::engine::ResourceManager* resources) -> void {
                    return self->load(path, resources);
                });
        bind_animator["set_animation"] = &obe::animation::Animator::set_animation;
        bind_animator["set_paused"] = &obe::animation::Animator::set_paused;
        bind_animator["update"] = &obe::animation::Animator::update;
        bind_animator["set_target"] = sol::overload(
            [](obe::animation::Animator* self, obe::graphics::Sprite& sprite) -> void {
                return self->set_target(sprite);
            },
            [](obe::animation::Animator* self, obe::graphics::Sprite& sprite,
                obe::animation::AnimatorTargetScaleMode target_scale_mode) -> void {
                return self->set_target(sprite, target_scale_mode);
            });
        bind_animator["get_filesystem_path"] = &obe::animation::Animator::get_filesystem_path;
        bind_animator["make_state"] = &obe::animation::Animator::make_state;
    }
    void load_class_animator_state(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::AnimatorState> bind_animator_state
            = animation_namespace.new_usertype<obe::animation::AnimatorState>("AnimatorState",
                sol::call_constructor,
                sol::constructors<obe::animation::AnimatorState(
                    const obe::animation::Animator&)>());
        bind_animator_state["load"] = &obe::animation::AnimatorState::load;
        bind_animator_state["get_current_animation_name"]
            = &obe::animation::AnimatorState::get_current_animation_name;
        bind_animator_state["set_animation"] = &obe::animation::AnimatorState::set_animation;
        bind_animator_state["set_paused"] = &obe::animation::AnimatorState::set_paused;
        bind_animator_state["update"] = &obe::animation::AnimatorState::update;
        bind_animator_state["set_target"] = sol::overload(
            [](obe::animation::AnimatorState* self, obe::graphics::Sprite& sprite) -> void {
                return self->set_target(sprite);
            },
            [](obe::animation::AnimatorState* self, obe::graphics::Sprite& sprite,
                obe::animation::AnimatorTargetScaleMode target_scale_mode) -> void {
                return self->set_target(sprite, target_scale_mode);
            });
        bind_animator_state["reset"] = &obe::animation::AnimatorState::reset;
        bind_animator_state["get_target"] = &obe::animation::AnimatorState::get_target;
        bind_animator_state["get_current_animation"]
            = &obe::animation::AnimatorState::get_current_animation;
        bind_animator_state["get_current_texture"]
            = &obe::animation::AnimatorState::get_current_texture;
        bind_animator_state["get_animator"]
            = [](obe::animation::AnimatorState* self) -> const obe::animation::Animator* {
            return &self->get_animator();
        };
    }
    void load_class_color_tweening(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<obe::graphics::Color>> bind_color_tweening
            = animation_namespace.new_usertype<obe::animation::ValueTweening<obe::graphics::Color>>(
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
        bind_color_tweening["from"] = &obe::animation::ValueTweening<obe::graphics::Color>::from;
        bind_color_tweening["to"] = &obe::animation::ValueTweening<obe::graphics::Color>::to;
        bind_color_tweening["ease"] = &obe::animation::ValueTweening<obe::graphics::Color>::ease;
        bind_color_tweening["start"] = &obe::animation::ValueTweening<obe::graphics::Color>::start;
        bind_color_tweening["stop"] = &obe::animation::ValueTweening<obe::graphics::Color>::stop;
        bind_color_tweening["seek"] = &obe::animation::ValueTweening<obe::graphics::Color>::seek;
        bind_color_tweening["reset"] = &obe::animation::ValueTweening<obe::graphics::Color>::reset;
        bind_color_tweening["resume"]
            = &obe::animation::ValueTweening<obe::graphics::Color>::resume;
        bind_color_tweening["done"] = &obe::animation::ValueTweening<obe::graphics::Color>::done;
        bind_color_tweening["step"] = &obe::animation::ValueTweening<obe::graphics::Color>::step;
    }
    void load_class_unit_vector_tweening(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<obe::transform::UnitVector>>
            bind_unit_vector_tweening
            = animation_namespace
                  .new_usertype<obe::animation::ValueTweening<obe::transform::UnitVector>>(
                      "UnitVectorTweening", sol::call_constructor,
                      sol::constructors<obe::animation::ValueTweening<obe::transform::UnitVector>(
                                            obe::time::TimeUnit),
                          obe::animation::ValueTweening<obe::transform::UnitVector>(
                              obe::time::TimeUnit, obe::animation::easing::EasingFunction),
                          obe::animation::ValueTweening<obe::transform::UnitVector>(
                              obe::transform::UnitVector, obe::transform::UnitVector,
                              obe::time::TimeUnit),
                          obe::animation::ValueTweening<obe::transform::UnitVector>(
                              obe::transform::UnitVector, obe::transform::UnitVector,
                              obe::time::TimeUnit, obe::animation::easing::EasingFunction)>());
        bind_unit_vector_tweening["from"]
            = &obe::animation::ValueTweening<obe::transform::UnitVector>::from;
        bind_unit_vector_tweening["to"]
            = &obe::animation::ValueTweening<obe::transform::UnitVector>::to;
        bind_unit_vector_tweening["ease"]
            = &obe::animation::ValueTweening<obe::transform::UnitVector>::ease;
        bind_unit_vector_tweening["start"]
            = &obe::animation::ValueTweening<obe::transform::UnitVector>::start;
        bind_unit_vector_tweening["stop"]
            = &obe::animation::ValueTweening<obe::transform::UnitVector>::stop;
        bind_unit_vector_tweening["seek"]
            = &obe::animation::ValueTweening<obe::transform::UnitVector>::seek;
        bind_unit_vector_tweening["reset"]
            = &obe::animation::ValueTweening<obe::transform::UnitVector>::reset;
        bind_unit_vector_tweening["resume"]
            = &obe::animation::ValueTweening<obe::transform::UnitVector>::resume;
        bind_unit_vector_tweening["done"]
            = &obe::animation::ValueTweening<obe::transform::UnitVector>::done;
        bind_unit_vector_tweening["step"]
            = &obe::animation::ValueTweening<obe::transform::UnitVector>::step;
    }
    void load_class_rect_tweening(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<obe::transform::Rect>> bind_rect_tweening
            = animation_namespace.new_usertype<obe::animation::ValueTweening<obe::transform::Rect>>(
                "RectTweening", sol::call_constructor,
                sol::constructors<obe::animation::ValueTweening<obe::transform::Rect>(
                                      obe::time::TimeUnit),
                    obe::animation::ValueTweening<obe::transform::Rect>(
                        obe::time::TimeUnit, obe::animation::easing::EasingFunction),
                    obe::animation::ValueTweening<obe::transform::Rect>(
                        obe::transform::Rect, obe::transform::Rect, obe::time::TimeUnit),
                    obe::animation::ValueTweening<obe::transform::Rect>(obe::transform::Rect,
                        obe::transform::Rect, obe::time::TimeUnit,
                        obe::animation::easing::EasingFunction)>());
        bind_rect_tweening["from"] = &obe::animation::ValueTweening<obe::transform::Rect>::from;
        bind_rect_tweening["to"] = &obe::animation::ValueTweening<obe::transform::Rect>::to;
        bind_rect_tweening["ease"] = &obe::animation::ValueTweening<obe::transform::Rect>::ease;
        bind_rect_tweening["start"] = &obe::animation::ValueTweening<obe::transform::Rect>::start;
        bind_rect_tweening["stop"] = &obe::animation::ValueTweening<obe::transform::Rect>::stop;
        bind_rect_tweening["seek"] = &obe::animation::ValueTweening<obe::transform::Rect>::seek;
        bind_rect_tweening["reset"] = &obe::animation::ValueTweening<obe::transform::Rect>::reset;
        bind_rect_tweening["resume"] = &obe::animation::ValueTweening<obe::transform::Rect>::resume;
        bind_rect_tweening["done"] = &obe::animation::ValueTweening<obe::transform::Rect>::done;
        bind_rect_tweening["step"] = &obe::animation::ValueTweening<obe::transform::Rect>::step;
    }
    void load_class_trajectory_tweening(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<obe::collision::Trajectory>>
            bind_trajectory_tweening
            = animation_namespace
                  .new_usertype<obe::animation::ValueTweening<obe::collision::Trajectory>>(
                      "TrajectoryTweening", sol::call_constructor,
                      sol::constructors<obe::animation::ValueTweening<obe::collision::Trajectory>(
                                            obe::time::TimeUnit),
                          obe::animation::ValueTweening<obe::collision::Trajectory>(
                              obe::time::TimeUnit, obe::animation::easing::EasingFunction),
                          obe::animation::ValueTweening<obe::collision::Trajectory>(
                              obe::collision::Trajectory, obe::collision::Trajectory,
                              obe::time::TimeUnit),
                          obe::animation::ValueTweening<obe::collision::Trajectory>(
                              obe::collision::Trajectory, obe::collision::Trajectory,
                              obe::time::TimeUnit, obe::animation::easing::EasingFunction)>());
        bind_trajectory_tweening["from"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::from;
        bind_trajectory_tweening["to"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::to;
        bind_trajectory_tweening["ease"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::ease;
        bind_trajectory_tweening["start"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::start;
        bind_trajectory_tweening["stop"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::stop;
        bind_trajectory_tweening["seek"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::seek;
        bind_trajectory_tweening["reset"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::reset;
        bind_trajectory_tweening["resume"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::resume;
        bind_trajectory_tweening["done"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::done;
        bind_trajectory_tweening["step"]
            = &obe::animation::ValueTweening<obe::collision::Trajectory>::step;
    }
    void load_class_int_tweening(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<int>> bind_int_tweening
            = animation_namespace.new_usertype<obe::animation::ValueTweening<int>>("IntTweening",
                sol::call_constructor,
                sol::constructors<obe::animation::ValueTweening<int>(obe::time::TimeUnit),
                    obe::animation::ValueTweening<int>(
                        obe::time::TimeUnit, obe::animation::easing::EasingFunction),
                    obe::animation::ValueTweening<int>(int, int, obe::time::TimeUnit),
                    obe::animation::ValueTweening<int>(
                        int, int, obe::time::TimeUnit, obe::animation::easing::EasingFunction)>());
        bind_int_tweening["from"] = &obe::animation::ValueTweening<int>::from;
        bind_int_tweening["to"] = &obe::animation::ValueTweening<int>::to;
        bind_int_tweening["ease"] = &obe::animation::ValueTweening<int>::ease;
        bind_int_tweening["start"] = &obe::animation::ValueTweening<int>::start;
        bind_int_tweening["stop"] = &obe::animation::ValueTweening<int>::stop;
        bind_int_tweening["seek"] = &obe::animation::ValueTweening<int>::seek;
        bind_int_tweening["reset"] = &obe::animation::ValueTweening<int>::reset;
        bind_int_tweening["resume"] = &obe::animation::ValueTweening<int>::resume;
        bind_int_tweening["done"] = &obe::animation::ValueTweening<int>::done;
        bind_int_tweening["step"] = &obe::animation::ValueTweening<int>::step;
    }
    void load_class_double_tweening(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        sol::usertype<obe::animation::ValueTweening<double>> bind_double_tweening
            = animation_namespace.new_usertype<obe::animation::ValueTweening<double>>(
                "DoubleTweening", sol::call_constructor,
                sol::constructors<obe::animation::ValueTweening<double>(obe::time::TimeUnit),
                    obe::animation::ValueTweening<double>(
                        obe::time::TimeUnit, obe::animation::easing::EasingFunction),
                    obe::animation::ValueTweening<double>(double, double, obe::time::TimeUnit),
                    obe::animation::ValueTweening<double>(double, double, obe::time::TimeUnit,
                        obe::animation::easing::EasingFunction)>());
        bind_double_tweening["from"] = &obe::animation::ValueTweening<double>::from;
        bind_double_tweening["to"] = &obe::animation::ValueTweening<double>::to;
        bind_double_tweening["ease"] = &obe::animation::ValueTweening<double>::ease;
        bind_double_tweening["start"] = &obe::animation::ValueTweening<double>::start;
        bind_double_tweening["stop"] = &obe::animation::ValueTweening<double>::stop;
        bind_double_tweening["seek"] = &obe::animation::ValueTweening<double>::seek;
        bind_double_tweening["reset"] = &obe::animation::ValueTweening<double>::reset;
        bind_double_tweening["resume"] = &obe::animation::ValueTweening<double>::resume;
        bind_double_tweening["done"] = &obe::animation::ValueTweening<double>::done;
        bind_double_tweening["step"] = &obe::animation::ValueTweening<double>::step;
    }
    void load_function_template_specialization_exists_impl(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
    }
    void load_function_tween(sol::state_view state)
    {
        sol::table animation_namespace = state["obe"]["animation"].get<sol::table>();
        animation_namespace["Tween"] = sol::overload(
            [](obe::graphics::Color from, obe::graphics::Color to,
                obe::time::TimeUnit duration) -> ValueTweening<obe::graphics::Color> {
                return obe::animation::ValueTweening<obe::graphics::Color>(from, to, duration);
            },
            [](obe::graphics::Color from, obe::graphics::Color to, obe::time::TimeUnit duration,
                obe::animation::easing::EasingFunction easing)
                -> ValueTweening<obe::graphics::Color> {
                return obe::animation::ValueTweening<obe::graphics::Color>(
                    from, to, duration, easing);
            },
            [](obe::transform::UnitVector from, obe::transform::UnitVector to,
                obe::time::TimeUnit duration) -> ValueTweening<obe::transform::UnitVector> {
                return obe::animation::ValueTweening<obe::transform::UnitVector>(
                    from, to, duration);
            },
            [](obe::transform::UnitVector from, obe::transform::UnitVector to,
                obe::time::TimeUnit duration, obe::animation::easing::EasingFunction easing)
                -> ValueTweening<obe::transform::UnitVector> {
                return obe::animation::ValueTweening<obe::transform::UnitVector>(
                    from, to, duration, easing);
            },
            [](obe::transform::Rect from, obe::transform::Rect to,
                obe::time::TimeUnit duration) -> ValueTweening<obe::transform::Rect> {
                return obe::animation::ValueTweening<obe::transform::Rect>(from, to, duration);
            },
            [](obe::transform::Rect from, obe::transform::Rect to, obe::time::TimeUnit duration,
                obe::animation::easing::EasingFunction easing)
                -> ValueTweening<obe::transform::Rect> {
                return obe::animation::ValueTweening<obe::transform::Rect>(
                    from, to, duration, easing);
            },
            [](obe::collision::Trajectory from, obe::collision::Trajectory to,
                obe::time::TimeUnit duration) -> ValueTweening<obe::collision::Trajectory> {
                return obe::animation::ValueTweening<obe::collision::Trajectory>(
                    from, to, duration);
            },
            [](obe::collision::Trajectory from, obe::collision::Trajectory to,
                obe::time::TimeUnit duration, obe::animation::easing::EasingFunction easing)
                -> ValueTweening<obe::collision::Trajectory> {
                return obe::animation::ValueTweening<obe::collision::Trajectory>(
                    from, to, duration, easing);
            },
            [](int from, int to, obe::time::TimeUnit duration) -> ValueTweening<int> {
                return obe::animation::ValueTweening<int>(from, to, duration);
            },
            [](int from, int to, obe::time::TimeUnit duration,
                obe::animation::easing::EasingFunction easing) -> ValueTweening<int> {
                return obe::animation::ValueTweening<int>(from, to, duration, easing);
            },
            [](double from, double to, obe::time::TimeUnit duration) -> ValueTweening<double> {
                return obe::animation::ValueTweening<double>(from, to, duration);
            },
            [](double from, double to, obe::time::TimeUnit duration,
                obe::animation::easing::EasingFunction easing) -> ValueTweening<double> {
                return obe::animation::ValueTweening<double>(from, to, duration, easing);
            });
    }
};