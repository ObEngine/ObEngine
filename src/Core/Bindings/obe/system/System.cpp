#include <Bindings/obe/system/System.hpp>

#include <Engine/Engine.hpp>
#include <System/Cursor.hpp>
#include <System/MountablePath.hpp>
#include <System/Path.hpp>
#include <System/Plugin.hpp>
#include <System/Window.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::bindings
{
    void load_enum_cursor_type(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        system_namespace.new_enum<obe::system::CursorType>("CursorType",
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
    void load_enum_mountable_path_type(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        system_namespace.new_enum<obe::system::MountablePathType>("MountablePathType",
            { { "Path", obe::system::MountablePathType::Path },
                { "Package", obe::system::MountablePathType::Package },
                { "Project", obe::system::MountablePathType::Project } });
    }
    void load_enum_same_prefix_policy(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        system_namespace.new_enum<obe::system::SamePrefixPolicy>("SamePrefixPolicy",
            { { "KeepBoth", obe::system::SamePrefixPolicy::KeepBoth },
                { "Skip", obe::system::SamePrefixPolicy::Skip },
                { "Replace", obe::system::SamePrefixPolicy::Replace } });
    }
    void load_enum_path_type(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        system_namespace.new_enum<obe::system::PathType>("PathType",
            { { "All", obe::system::PathType::All },
                { "Directory", obe::system::PathType::Directory },
                { "File", obe::system::PathType::File } });
    }
    void load_enum_window_context(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        system_namespace.new_enum<obe::system::WindowContext>("WindowContext",
            { { "GameWindow", obe::system::WindowContext::GameWindow },
                { "EditorWindow", obe::system::WindowContext::EditorWindow } });
    }
    void load_enum_stretch_mode(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        system_namespace.new_enum<obe::system::StretchMode>("StretchMode",
            { { "None", obe::system::StretchMode::None },
                { "Center", obe::system::StretchMode::Center },
                { "Stretch", obe::system::StretchMode::Stretch },
                { "Fit", obe::system::StretchMode::Fit } });
    }
    void load_enum_window_size(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        system_namespace.new_enum<obe::system::WindowSize>(
            "WindowSize", { { "Screen", obe::system::WindowSize::Screen } });
    }
    void load_enum_render_size(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        system_namespace.new_enum<obe::system::RenderSize>("RenderSize",
            { { "Window", obe::system::RenderSize::Window },
                { "Screen", obe::system::RenderSize::Screen } });
    }
    void load_class_contextual_path_factory(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::ContextualPathFactory> bind_contextual_path_factory
            = system_namespace.new_usertype<obe::system::ContextualPathFactory>(
                "ContextualPathFactory", sol::call_constructor,
                sol::constructors<obe::system::ContextualPathFactory(const std::string&),
                    obe::system::ContextualPathFactory(
                        const std::string&, const obe::system::MountList&)>());
        bind_contextual_path_factory[sol::meta_function::call]
            = &obe::system::ContextualPathFactory::operator();
    }
    void load_class_cursor(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::Cursor> bind_cursor
            = system_namespace.new_usertype<obe::system::Cursor>("Cursor", sol::call_constructor,
                sol::constructors<obe::system::Cursor(
                    obe::system::Window&, obe::event::EventNamespace&)>());
        bind_cursor["get_constrained_x"] = &obe::system::Cursor::get_constrained_x;
        bind_cursor["get_constrained_y"] = &obe::system::Cursor::get_constrained_y;
        bind_cursor["get_x"] = &obe::system::Cursor::get_x;
        bind_cursor["get_y"] = &obe::system::Cursor::get_y;
        bind_cursor["set_x"] = &obe::system::Cursor::set_x;
        bind_cursor["set_y"] = &obe::system::Cursor::set_y;
        bind_cursor["set_position"] = &obe::system::Cursor::set_position;
        bind_cursor["show"] = &obe::system::Cursor::show;
        bind_cursor["hide"] = &obe::system::Cursor::hide;
        bind_cursor["set_visible"] = &obe::system::Cursor::set_visible;
        bind_cursor["is_visible"] = &obe::system::Cursor::is_visible;
        bind_cursor["get_position"] = &obe::system::Cursor::get_position;
        bind_cursor["get_scene_position"] = &obe::system::Cursor::get_scene_position;
        bind_cursor["update"] = &obe::system::Cursor::update;
        bind_cursor["set_constraint"] = sol::overload(
            [](obe::system::Cursor* self,
                const obe::system::Cursor::PositionConstraint& constraint) -> void
            { return self->set_constraint(constraint); },
            [](obe::system::Cursor* self, const obe::system::Cursor::PositionConstraint& constraint,
                obe::system::Cursor::ConstraintCondition condition) -> void
            { return self->set_constraint(constraint, condition); });
        bind_cursor["is_pressed"] = &obe::system::Cursor::is_pressed;
        bind_cursor["set_cursor"] = &obe::system::Cursor::set_cursor;
    }
    void load_class_cursor_model(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::CursorModel> bind_cursor_model
            = system_namespace.new_usertype<obe::system::CursorModel>(
                "CursorModel", sol::call_constructor, sol::default_constructor);
        bind_cursor_model["load_from_file"] = &obe::system::CursorModel::load_from_file;
        bind_cursor_model["load_from_system"] = &obe::system::CursorModel::load_from_system;
    }
    void load_class_find_result(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::FindResult> bind_find_result
            = system_namespace.new_usertype<obe::system::FindResult>("FindResult",
                sol::call_constructor,
                sol::constructors<obe::system::FindResult(obe::system::PathType, const std::string&,
                                      const std::string&, const obe::system::MountList&),
                    obe::system::FindResult(obe::system::PathType,
                        std::shared_ptr<obe::system::MountablePath>, const std::string&,
                        const std::string&),
                    obe::system::FindResult(obe::system::PathType,
                        std::shared_ptr<obe::system::MountablePath>, const std::string&,
                        const std::string&, const std::string&)>());
        bind_find_result["hypothetical_path"] = &obe::system::FindResult::hypothetical_path;
        bind_find_result["path"] = &obe::system::FindResult::path;
        bind_find_result["mount"] = &obe::system::FindResult::mount;
        bind_find_result["query"] = &obe::system::FindResult::query;
        bind_find_result["element"] = &obe::system::FindResult::element;
        bind_find_result["success"] = &obe::system::FindResult::success;
    }
    void load_class_mountable_path(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::MountablePath> bind_mountable_path
            = system_namespace.new_usertype<obe::system::MountablePath>("MountablePath",
                sol::call_constructor,
                sol::constructors<obe::system::MountablePath(obe::system::MountablePathType,
                                      std::string_view, std::string_view),
                    obe::system::MountablePath(obe::system::MountablePathType, std::string_view,
                        std::string_view, unsigned int),
                    obe::system::MountablePath(obe::system::MountablePathType, std::string_view,
                        std::string_view, unsigned int, bool),
                    obe::system::MountablePath(obe::system::MountablePathType, std::string_view,
                        std::string_view, unsigned int, bool, bool)>());
        bind_mountable_path[sol::meta_function::equal_to] = &obe::system::MountablePath::operator==;
        bind_mountable_path["resolve_base_path"] = &obe::system::MountablePath::resolve_base_path;
        bind_mountable_path["load_mount_file"]
            = sol::overload([]() -> void { return obe::system::MountablePath::load_mount_file(); },
                [](bool from_cwd) -> void
                { return obe::system::MountablePath::load_mount_file(from_cwd); },
                [](bool from_cwd, bool from_exe) -> void
                { return obe::system::MountablePath::load_mount_file(from_cwd, from_exe); });
        bind_mountable_path["mount"] = sol::overload([](obe::system::MountablePath path) -> void
            { return obe::system::MountablePath::mount(path); },
            [](obe::system::MountablePath path,
                obe::system::SamePrefixPolicy same_prefix_policy) -> void
            { return obe::system::MountablePath::mount(path, same_prefix_policy); });
        bind_mountable_path["unmount"] = &obe::system::MountablePath::unmount;
        bind_mountable_path["unmount_all"] = &obe::system::MountablePath::unmount_all;
        bind_mountable_path["paths"] = &obe::system::MountablePath::paths;
        bind_mountable_path["string_paths"] = &obe::system::MountablePath::string_paths;
        bind_mountable_path["sort"] = &obe::system::MountablePath::sort;
        bind_mountable_path["from_prefix"] = &obe::system::MountablePath::from_prefix;
        bind_mountable_path["get_all_prefixes"] = &obe::system::MountablePath::get_all_prefixes;
        bind_mountable_path["path_type"] = &obe::system::MountablePath::path_type;
        bind_mountable_path["base_path"] = &obe::system::MountablePath::base_path;
        bind_mountable_path["prefix"] = &obe::system::MountablePath::prefix;
        bind_mountable_path["priority"] = &obe::system::MountablePath::priority;
        bind_mountable_path["implicit"] = &obe::system::MountablePath::implicit;
        bind_mountable_path["deferred_resolution"]
            = &obe::system::MountablePath::deferred_resolution;
    }
    void load_class_path(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::Path> bind_path = system_namespace.new_usertype<
            obe::system::Path>("Path", sol::call_constructor,
            sol::constructors<obe::system::Path(), obe::system::Path(const obe::system::MountList&),
                obe::system::Path(const obe::system::Path&), obe::system::Path(std::string_view),
                obe::system::Path(std::string_view, std::string_view)>());
        bind_path["set"] = &obe::system::Path::set;
        bind_path["add"] = &obe::system::Path::add;
        bind_path["last"] = &obe::system::Path::last;
        bind_path["get_path"] = &obe::system::Path::get_path;
        bind_path["list"]
            = sol::overload([](obe::system::Path* self) -> std::vector<obe::system::FindResult>
                { return self->list(); },
                [](obe::system::Path* self,
                    obe::system::PathType path_type) -> std::vector<obe::system::FindResult>
                { return self->list(path_type); });
        bind_path["find"] = sol::overload([](obe::system::Path* self) -> obe::system::FindResult
            { return self->find(); },
            [](obe::system::Path* self, obe::system::PathType path_type) -> obe::system::FindResult
            { return self->find(path_type); });
        bind_path["find_all"]
            = sol::overload([](obe::system::Path* self) -> std::vector<obe::system::FindResult>
                { return self->find_all(); },
                [](obe::system::Path* self,
                    obe::system::PathType path_type) -> std::vector<obe::system::FindResult>
                { return self->find_all(path_type); });
        bind_path["to_string"] = &obe::system::Path::to_string;
        state.script_file("obe://Lib/Internal/Require.lua"_fs);
        state.script_file("obe://Lib/Internal/Filesystem.lua"_fs);
    }
    void load_class_plugin(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::Plugin> bind_plugin
            = system_namespace.new_usertype<obe::system::Plugin>("Plugin", sol::call_constructor,
                sol::constructors<obe::system::Plugin(const std::string&, const std::string&)>(),
                sol::base_classes, sol::bases<obe::Types::Identifiable>());
        bind_plugin["on_init"] = &obe::system::Plugin::on_init;
        bind_plugin["on_exit"] = &obe::system::Plugin::on_exit;
        bind_plugin["has_on_init"] = &obe::system::Plugin::has_on_init;
        bind_plugin["has_on_exit"] = &obe::system::Plugin::has_on_exit;
        bind_plugin["is_valid"] = &obe::system::Plugin::is_valid;
    }
    void load_class_window(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        sol::usertype<obe::system::Window> bind_window
            = system_namespace.new_usertype<obe::system::Window>("Window", sol::call_constructor,
                sol::constructors<obe::system::Window(vili::node)>());
        bind_window["create"] = &obe::system::Window::create;
        bind_window["clear"] = &obe::system::Window::clear;
        bind_window["close"] = &obe::system::Window::close;
        bind_window["display"] = &obe::system::Window::display;
        bind_window["get_render_size"] = &obe::system::Window::get_render_size;
        bind_window["get_window_size"] = &obe::system::Window::get_window_size;
        bind_window["get_size"] = &obe::system::Window::get_size;
        bind_window["is_open"] = &obe::system::Window::is_open;
        bind_window["poll_event"] = &obe::system::Window::poll_event;
        bind_window["set_size"] = &obe::system::Window::set_size;
        bind_window["set_window_size"] = &obe::system::Window::set_window_size;
        bind_window["set_render_size"] = &obe::system::Window::set_render_size;
        bind_window["set_title"] = &obe::system::Window::set_title;
        bind_window["set_vertical_sync_enabled"] = &obe::system::Window::set_vertical_sync_enabled;
        bind_window["set_view"] = &obe::system::Window::set_view;
        bind_window["set_icon"] = &obe::system::Window::set_icon;
        bind_window["get_target"] = &obe::system::Window::get_target;
        bind_window["get_window"] = &obe::system::Window::get_window;
        bind_window["get_clear_color"] = &obe::system::Window::get_clear_color;
        bind_window["set_clear_color"] = &obe::system::Window::set_clear_color;
        bind_window["set_mouse_cursor_visible"] = &obe::system::Window::set_mouse_cursor_visible;
        bind_window["get_screen_size"] = &obe::system::Window::get_screen_size;
    }
    void load_function_split_path_and_prefix(sol::state_view state)
    {
        sol::table system_namespace = state["obe"]["system"].get<sol::table>();
        system_namespace.set_function("split_path_and_prefix",
            sol::overload([](const std::string& path) -> std::pair<std::string, std::string>
                { return obe::system::split_path_and_prefix(path); },
                [](const std::string& path,
                    bool warn_on_missing_prefix) -> std::pair<std::string, std::string>
                { return obe::system::split_path_and_prefix(path, warn_on_missing_prefix); }));
    }
};