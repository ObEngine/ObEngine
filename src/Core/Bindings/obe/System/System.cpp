#include <Bindings/obe/System/System.hpp>

#include <Engine/Engine.hpp>
#include <System/Cursor.hpp>
#include <System/MountablePath.hpp>
#include <System/Path.hpp>
#include <System/Plugin.hpp>
#include <System/Window.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::Bindings
{
    void LoadEnumCursorType(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        SystemNamespace.new_enum<obe::system::CursorType>("CursorType",
            { { "Arrow", obe::system::CursorType::Arrow },
                { "ArrowWait", obe::system::CursorType::ArrowWait },
                { "Wait", obe::system::CursorType::Wait },
                { "Text", obe::system::CursorType::Text },
                { "Hand", obe::system::CursorType::Hand },
                { "SizeHorizontal", obe::system::CursorType::SizeHorizontal },
                { "SizeVertical", obe::system::CursorType::SizeVertical },
                { "SizeTopLeftBottomRight", obe::system::CursorType::SizeTopLeftBottomRight },
                { "SizeBottomLeftTopRight", obe::system::CursorType::SizeBottomLeftTopRight },
                { "SizeAll", obe::system::CursorType::SizeAll },
                { "Cross", obe::system::CursorType::Cross },
                { "Help", obe::system::CursorType::Help },
                { "NotAllowed", obe::system::CursorType::NotAllowed } });
    }
    void LoadEnumMountablePathType(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        SystemNamespace.new_enum<obe::system::MountablePathType>("MountablePathType",
            { { "Path", obe::system::MountablePathType::Path },
                { "Package", obe::system::MountablePathType::Package },
                { "Project", obe::system::MountablePathType::Project } });
    }
    void LoadEnumSamePrefixPolicy(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        SystemNamespace.new_enum<obe::system::SamePrefixPolicy>("SamePrefixPolicy",
            { { "KeepBoth", obe::system::SamePrefixPolicy::KeepBoth },
                { "Skip", obe::system::SamePrefixPolicy::Skip },
                { "Replace", obe::system::SamePrefixPolicy::Replace } });
    }
    void LoadEnumPathType(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        SystemNamespace.new_enum<obe::system::PathType>("PathType",
            { { "All", obe::system::PathType::All },
                { "Directory", obe::system::PathType::Directory },
                { "File", obe::system::PathType::File } });
    }
    void LoadEnumWindowContext(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        SystemNamespace.new_enum<obe::system::WindowContext>("WindowContext",
            { { "GameWindow", obe::system::WindowContext::GameWindow },
                { "EditorWindow", obe::system::WindowContext::EditorWindow } });
    }
    void LoadEnumStretchMode(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        SystemNamespace.new_enum<obe::system::StretchMode>("StretchMode",
            { { "None", obe::system::StretchMode::None },
                { "Center", obe::system::StretchMode::Center },
                { "Stretch", obe::system::StretchMode::Stretch },
                { "Fit", obe::system::StretchMode::Fit } });
    }
    void LoadClassContextualPathFactory(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::ContextualPathFactory> bindContextualPathFactory
            = SystemNamespace.new_usertype<obe::system::ContextualPathFactory>(
                "ContextualPathFactory", sol::call_constructor,
                sol::constructors<obe::system::ContextualPathFactory(const std::string&),
                    obe::system::ContextualPathFactory(
                        const std::string&, const obe::system::MountList&)>());
        bindContextualPathFactory[sol::meta_function::call]
            = &obe::system::ContextualPathFactory::operator();
    }
    void LoadClassCursor(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::Cursor> bindCursor
            = SystemNamespace.new_usertype<obe::system::Cursor>("Cursor", sol::call_constructor,
                sol::constructors<obe::system::Cursor(
                    obe::system::Window&, obe::event::EventNamespace&)>());
        bindCursor["get_constrained_x"] = &obe::system::Cursor::get_constrained_x;
        bindCursor["get_constrained_y"] = &obe::system::Cursor::get_constrained_y;
        bindCursor["get_x"] = &obe::system::Cursor::get_x;
        bindCursor["getY"] = &obe::system::Cursor::get_y;
        bindCursor["setX"] = &obe::system::Cursor::set_x;
        bindCursor["setY"] = &obe::system::Cursor::set_y;
        bindCursor["set_position"] = &obe::system::Cursor::set_position;
        bindCursor["show"] = &obe::system::Cursor::show;
        bindCursor["hide"] = &obe::system::Cursor::hide;
        bindCursor["set_visible"] = &obe::system::Cursor::set_visible;
        bindCursor["is_visible"] = &obe::system::Cursor::is_visible;
        bindCursor["get_position"] = &obe::system::Cursor::get_position;
        bindCursor["get_scene_position"] = &obe::system::Cursor::get_scene_position;
        bindCursor["update"] = &obe::system::Cursor::update;
        bindCursor["set_constraint"] = sol::overload(
            [](obe::system::Cursor* self, const obe::system::Cursor::PositionConstraint& constraint)
                -> void { return self->set_constraint(constraint); },
            [](obe::system::Cursor* self, const obe::system::Cursor::PositionConstraint& constraint,
                obe::system::Cursor::ConstraintCondition condition) -> void {
                return self->set_constraint(constraint, condition);
            });
        bindCursor["is_pressed"] = &obe::system::Cursor::is_pressed;
        bindCursor["set_cursor"] = &obe::system::Cursor::set_cursor;
    }
    void LoadClassCursorModel(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::CursorModel> bindCursorModel
            = SystemNamespace.new_usertype<obe::system::CursorModel>(
                "CursorModel", sol::call_constructor, sol::default_constructor);
        bindCursorModel["load_from_file"] = &obe::system::CursorModel::load_from_file;
        bindCursorModel["load_from_system"] = &obe::system::CursorModel::load_from_system;
    }
    void LoadClassFindResult(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::FindResult> bindFindResult
            = SystemNamespace.new_usertype<obe::system::FindResult>("FindResult",
                sol::call_constructor,
                sol::constructors<obe::system::FindResult(obe::system::PathType, const std::string&,
                                      const std::string&, const obe::system::MountList&),
                    obe::system::FindResult(obe::system::PathType,
                        std::shared_ptr<obe::system::MountablePath>, const std::string&,
                        const std::string&),
                    obe::system::FindResult(obe::system::PathType,
                        std::shared_ptr<obe::system::MountablePath>, const std::string&,
                        const std::string&, const std::string&)>());
        bindFindResult["hypothetical_path"] = &obe::system::FindResult::hypothetical_path;
        bindFindResult["path"] = &obe::system::FindResult::path;
        bindFindResult["mount"] = &obe::system::FindResult::mount;
        bindFindResult["query"] = &obe::system::FindResult::query;
        bindFindResult["element"] = &obe::system::FindResult::element;
        bindFindResult["success"] = &obe::system::FindResult::success;
    }
    void LoadClassMountablePath(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::MountablePath> bindMountablePath
            = SystemNamespace.new_usertype<obe::system::MountablePath>("MountablePath",
                sol::call_constructor,
                sol::constructors<obe::system::MountablePath(obe::system::MountablePathType,
                                      std::string_view, std::string_view),
                    obe::system::MountablePath(obe::system::MountablePathType, std::string_view,
                        std::string_view, unsigned int),
                    obe::system::MountablePath(obe::system::MountablePathType, std::string_view,
                        std::string_view, unsigned int, bool),
                    obe::system::MountablePath(obe::system::MountablePathType, std::string_view,
                        std::string_view, unsigned int, bool, bool)>());
        bindMountablePath[sol::meta_function::equal_to] = &obe::system::MountablePath::operator==;
        bindMountablePath["resolve_base_path"] = &obe::system::MountablePath::resolve_base_path;
        bindMountablePath["load_mount_file"] = sol::overload(
            []() -> void { return obe::system::MountablePath::load_mount_file(); },
            [](bool fromCWD) -> void { return obe::system::MountablePath::load_mount_file(fromCWD); },
            [](bool fromCWD, bool fromExe) -> void {
                return obe::system::MountablePath::load_mount_file(fromCWD, fromExe);
            });
        bindMountablePath["mount"] = sol::overload(
            [](obe::system::MountablePath path) -> void {
                return obe::system::MountablePath::mount(path);
            },
            [](obe::system::MountablePath path, obe::system::SamePrefixPolicy samePrefixPolicy)
                -> void { return obe::system::MountablePath::mount(path, samePrefixPolicy); });
        bindMountablePath["unmount"] = &obe::system::MountablePath::unmount;
        bindMountablePath["unmount_all"] = &obe::system::MountablePath::unmount_all;
        bindMountablePath["paths"] = &obe::system::MountablePath::paths;
        bindMountablePath["string_paths"] = &obe::system::MountablePath::string_paths;
        bindMountablePath["sort"] = &obe::system::MountablePath::sort;
        bindMountablePath["from_prefix"] = &obe::system::MountablePath::from_prefix;
        bindMountablePath["get_all_prefixes"] = &obe::system::MountablePath::get_all_prefixes;
        bindMountablePath["path_type"] = &obe::system::MountablePath::path_type;
        bindMountablePath["base_path"] = &obe::system::MountablePath::base_path;
        bindMountablePath["prefix"] = &obe::system::MountablePath::prefix;
        bindMountablePath["priority"] = &obe::system::MountablePath::priority;
        bindMountablePath["implicit"] = &obe::system::MountablePath::implicit;
        bindMountablePath["deferred_resolution"] = &obe::system::MountablePath::deferred_resolution;
    }
    void LoadClassPath(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::Path> bindPath = SystemNamespace.new_usertype<obe::system::Path>(
            "Path", sol::call_constructor,
            sol::constructors<obe::system::Path(), obe::system::Path(const obe::system::MountList&),
                obe::system::Path(const obe::system::Path&), obe::system::Path(std::string_view),
                obe::system::Path(std::string_view, std::string_view)>());
        bindPath["set"] = &obe::system::Path::set;
        bindPath["add"] = &obe::system::Path::add;
        bindPath["last"] = &obe::system::Path::last;
        bindPath["get_path"] = &obe::system::Path::get_path;
        bindPath["list"] = sol::overload(
            [](obe::system::Path* self) -> std::vector<obe::system::FindResult> {
                return self->list();
            },
            [](obe::system::Path* self, obe::system::PathType pathType)
                -> std::vector<obe::system::FindResult> { return self->list(pathType); });
        bindPath["find"] = sol::overload(
            [](obe::system::Path* self) -> obe::system::FindResult { return self->find(); },
            [](obe::system::Path* self, obe::system::PathType pathType) -> obe::system::FindResult {
                return self->find(pathType);
            });
        bindPath["find_all"] = sol::overload(
            [](obe::system::Path* self) -> std::vector<obe::system::FindResult> {
                return self->find_all();
            },
            [](obe::system::Path* self, obe::system::PathType pathType)
                -> std::vector<obe::system::FindResult> { return self->find_all(pathType); });
        bindPath["to_string"] = &obe::system::Path::to_string;
        state.script_file("obe://Lib/Internal/Require.lua"_fs);
        state.script_file("obe://Lib/Internal/Filesystem.lua"_fs);
    }
    void LoadClassPlugin(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::Plugin> bindPlugin
            = SystemNamespace.new_usertype<obe::system::Plugin>("Plugin", sol::call_constructor,
                sol::constructors<obe::system::Plugin(const std::string&, const std::string&)>(),
                sol::base_classes, sol::bases<obe::Types::Identifiable>());
        bindPlugin["on_init"] = &obe::system::Plugin::on_init;
        bindPlugin["on_exit"] = &obe::system::Plugin::on_exit;
        bindPlugin["has_on_init"] = &obe::system::Plugin::has_on_init;
        bindPlugin["has_on_exit"] = &obe::system::Plugin::has_on_exit;
        bindPlugin["is_valid"] = &obe::system::Plugin::is_valid;
    }
    void LoadClassWindow(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::Window> bindWindow
            = SystemNamespace.new_usertype<obe::system::Window>("Window", sol::call_constructor,
                sol::constructors<obe::system::Window(vili::node)>());
        bindWindow["create"] = &obe::system::Window::create;
        bindWindow["clear"] = &obe::system::Window::clear;
        bindWindow["close"] = &obe::system::Window::close;
        bindWindow["display"] = &obe::system::Window::display;
        bindWindow["get_render_size"] = &obe::system::Window::get_render_size;
        bindWindow["get_window_size"] = &obe::system::Window::get_window_size;
        bindWindow["get_screen_size"] = &obe::system::Window::get_screen_size;
        bindWindow["get_size"] = &obe::system::Window::get_size;
        bindWindow["is_open"] = &obe::system::Window::is_open;
        bindWindow["poll_event"] = &obe::system::Window::poll_event;
        bindWindow["set_size"] = &obe::system::Window::set_size;
        bindWindow["set_window_size"] = &obe::system::Window::set_window_size;
        bindWindow["set_render_size"] = &obe::system::Window::set_render_size;
        bindWindow["set_title"] = &obe::system::Window::set_title;
        bindWindow["set_vertical_sync_enabled"] = &obe::system::Window::set_vertical_sync_enabled;
        bindWindow["set_view"] = &obe::system::Window::set_view;
        bindWindow["set_icon"] = &obe::system::Window::set_icon;
        bindWindow["get_target"] = &obe::system::Window::get_target;
        bindWindow["get_window"] = &obe::system::Window::get_window;
        bindWindow["get_clear_color"] = &obe::system::Window::get_clear_color;
        bindWindow["set_clear_color"] = &obe::system::Window::set_clear_color;
        bindWindow["set_mouse_cursor_visible"] = &obe::system::Window::set_mouse_cursor_visible;
    }
    void LoadFunctionSplitPathAndPrefix(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["system"].get<sol::table>();
        SystemNamespace.set_function("split_path_and_prefix",
            sol::overload(
                [](const std::string& path) -> std::pair<std::string, std::string> {
                    return obe::system::split_path_and_prefix(path);
                },
                [](const std::string& path,
                    bool warnOnMissingPrefix) -> std::pair<std::string, std::string> {
                    return obe::system::split_path_and_prefix(path, warnOnMissingPrefix);
                }));
    }
};