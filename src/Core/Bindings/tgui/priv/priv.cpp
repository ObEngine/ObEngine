#include <Bindings/tgui/priv/priv.hpp>

#include <TGUI/Animation.hpp>
#include <TGUI/OpenGL.hpp>

#include <Bindings/Config.hpp>

namespace tgui::priv::Bindings
{
    void LoadClassAnimation(sol::state_view state)
    {
        sol::table privNamespace = state["tgui"]["priv"].get<sol::table>();
        sol::usertype<tgui::priv::Animation> bindAnimation
            = privNamespace.new_usertype<tgui::priv::Animation>("Animation");
        bindAnimation["operator="]
            = sol::overload(static_cast<gui::priv::Animation& (
                                tgui::priv::Animation::*)(const gui::priv::Animation&)>(
                                &tgui::priv::Animation::operator=),
                static_cast<gui::priv::Animation& (
                    tgui::priv::Animation::*)(gui::priv::Animation &&)>(
                    &tgui::priv::Animation::operator=));
        bindAnimation["getType"] = &tgui::priv::Animation::getType;
        bindAnimation["update"] = &tgui::priv::Animation::update;
        bindAnimation["finish"] = &tgui::priv::Animation::finish;
    }
    void LoadClassFadeAnimation(sol::state_view state)
    {
        sol::table privNamespace = state["tgui"]["priv"].get<sol::table>();
        sol::usertype<tgui::priv::FadeAnimation> bindFadeAnimation
            = privNamespace.new_usertype<tgui::priv::FadeAnimation>("FadeAnimation",
                sol::call_constructor,
                sol::constructors<tgui::priv::FadeAnimation(std::shared_ptr<gui::Widget>,
                                      float, float, gui::Duration),
                    tgui::priv::FadeAnimation(std::shared_ptr<gui::Widget>, float, float,
                        gui::Duration, std::function<void()>)>(),
                sol::base_classes, sol::bases<tgui::priv::Animation>());
        bindFadeAnimation["update"] = &tgui::priv::FadeAnimation::update;
        bindFadeAnimation["finish"] = &tgui::priv::FadeAnimation::finish;
    }
    void LoadClassMoveAnimation(sol::state_view state)
    {
        sol::table privNamespace = state["tgui"]["priv"].get<sol::table>();
        sol::usertype<tgui::priv::MoveAnimation> bindMoveAnimation
            = privNamespace.new_usertype<tgui::priv::MoveAnimation>("MoveAnimation",
                sol::call_constructor,
                sol::constructors<tgui::priv::MoveAnimation(std::shared_ptr<gui::Widget>,
                                      tgui::Vector2f, tgui::Vector2f, gui::Duration),
                    tgui::priv::MoveAnimation(std::shared_ptr<gui::Widget>,
                        tgui::Vector2f, tgui::Vector2f, gui::Duration,
                        std::function<void()>)>(),
                sol::base_classes, sol::bases<tgui::priv::Animation>());
        bindMoveAnimation["update"] = &tgui::priv::MoveAnimation::update;
        bindMoveAnimation["finish"] = &tgui::priv::MoveAnimation::finish;
    }
    void LoadClassResizeAnimation(sol::state_view state)
    {
        sol::table privNamespace = state["tgui"]["priv"].get<sol::table>();
        sol::usertype<tgui::priv::ResizeAnimation> bindResizeAnimation
            = privNamespace.new_usertype<tgui::priv::ResizeAnimation>("ResizeAnimation",
                sol::call_constructor,
                sol::constructors<tgui::priv::ResizeAnimation(
                                      std::shared_ptr<gui::Widget>, tgui::Vector2f,
                                      tgui::Vector2f, gui::Duration),
                    tgui::priv::ResizeAnimation(std::shared_ptr<gui::Widget>,
                        tgui::Vector2f, tgui::Vector2f, gui::Duration,
                        std::function<void()>)>(),
                sol::base_classes, sol::bases<tgui::priv::Animation>());
        bindResizeAnimation["update"] = &tgui::priv::ResizeAnimation::update;
        bindResizeAnimation["finish"] = &tgui::priv::ResizeAnimation::finish;
    }
    void LoadFunctionCheckAndLogOpenGlError(sol::state_view state)
    {
        sol::table privNamespace = state["tgui"]["priv"].get<sol::table>();
        privNamespace.set_function(
            "checkAndLogOpenGlError", tgui::priv::checkAndLogOpenGlError);
    }
};