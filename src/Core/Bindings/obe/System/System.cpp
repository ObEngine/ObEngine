#include <Bindings/obe/System/System.hpp>

#include <System/Cursor.hpp>
#include <System/Loaders.hpp>
#include <System/MountablePath.hpp>
#include <System/Path.hpp>
#include <System/Plugin.hpp>
#include <System/Window.hpp>

#include <Bindings/Config.hpp>

namespace obe::System::Bindings
{
    void LoadEnumMountablePathType(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        SystemNamespace.new_enum<obe::System::MountablePathType>("MountablePathType",
            { { "Path", obe::System::MountablePathType::Path },
                { "Package", obe::System::MountablePathType::Package },
                { "Workspace", obe::System::MountablePathType::Workspace } });
    }
    void LoadEnumPathType(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        SystemNamespace.new_enum<obe::System::PathType>("PathType",
            { { "All", obe::System::PathType::All },
                { "Directory", obe::System::PathType::Directory },
                { "File", obe::System::PathType::File } });
    }
    void LoadEnumWindowContext(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        SystemNamespace.new_enum<obe::System::WindowContext>("WindowContext",
            { { "GameWindow", obe::System::WindowContext::GameWindow },
                { "EditorWindow", obe::System::WindowContext::EditorWindow } });
    }
    void LoadClassCursor(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::Cursor> bindCursor
            = SystemNamespace.new_usertype<obe::System::Cursor>("Cursor",
                sol::call_constructor,
                sol::constructors<obe::System::Cursor(
                    obe::System::Window&, obe::Triggers::TriggerManager&)>());
        bindCursor["getConstrainedX"] = &obe::System::Cursor::getConstrainedX;
        bindCursor["getConstrainedY"] = &obe::System::Cursor::getConstrainedY;
        bindCursor["getX"] = &obe::System::Cursor::getX;
        bindCursor["getY"] = &obe::System::Cursor::getY;
        bindCursor["setX"] = &obe::System::Cursor::setX;
        bindCursor["setY"] = &obe::System::Cursor::setY;
        bindCursor["setPosition"] = &obe::System::Cursor::setPosition;
        bindCursor["show"] = &obe::System::Cursor::show;
        bindCursor["hide"] = &obe::System::Cursor::hide;
        bindCursor["setVisible"] = &obe::System::Cursor::setVisible;
        bindCursor["isVisible"] = &obe::System::Cursor::isVisible;
        bindCursor["getPosition"] = &obe::System::Cursor::getPosition;
        bindCursor["update"] = &obe::System::Cursor::update;
        bindCursor["setConstraint"] = sol::overload(
            [](obe::System::Cursor* self,
                std::function<std::pair<int, int>(obe::System::Cursor*)> constraint)
                -> void { return self->setConstraint(constraint); },
            [](obe::System::Cursor* self,
                std::function<std::pair<int, int>(obe::System::Cursor*)> constraint,
                std::function<bool()> condition) -> void {
                return self->setConstraint(constraint, condition);
            });
        bindCursor["isPressed"] = &obe::System::Cursor::isPressed;
    }
    void LoadClassLoaderMultipleResult(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::LoaderMultipleResult> bindLoaderMultipleResult
            = SystemNamespace.new_usertype<obe::System::LoaderMultipleResult>(
                "LoaderMultipleResult", sol::call_constructor,
                sol::constructors<obe::System::LoaderMultipleResult(),
                    obe::System::LoaderMultipleResult(
                        const std::vector<std::string>&)>());
        bindLoaderMultipleResult["paths"] = &obe::System::LoaderMultipleResult::paths;
        bindLoaderMultipleResult["loadCount"]
            = &obe::System::LoaderMultipleResult::loadCount;
        bindLoaderMultipleResult["success"] = &obe::System::LoaderMultipleResult::success;
        bindLoaderMultipleResult["operator bool"]
            = &obe::System::LoaderMultipleResult::operator bool;
    }
    void LoadClassLoaderResult(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::LoaderResult> bindLoaderResult
            = SystemNamespace.new_usertype<obe::System::LoaderResult>("LoaderResult",
                sol::call_constructor,
                sol::constructors<obe::System::LoaderResult(),
                    obe::System::LoaderResult(const std::string&)>());
        bindLoaderResult["path"] = &obe::System::LoaderResult::path;
        bindLoaderResult["success"] = &obe::System::LoaderResult::success;
        bindLoaderResult["operator bool"] = &obe::System::LoaderResult::operator bool;
    }
    void LoadClassMountablePath(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::MountablePath> bindMountablePath
            = SystemNamespace.new_usertype<obe::System::MountablePath>("MountablePath",
                sol::call_constructor,
                sol::constructors<obe::System::MountablePath(
                                      obe::System::MountablePathType, const std::string&),
                    obe::System::MountablePath(obe::System::MountablePathType,
                        const std::string&, unsigned int)>());
        bindMountablePath[sol::meta_function::equal_to]
            = &obe::System::MountablePath::operator==;
        bindMountablePath["LoadMountFile"] = &obe::System::MountablePath::LoadMountFile;
        bindMountablePath["Mount"] = &obe::System::MountablePath::Mount;
        bindMountablePath["Unmount"] = &obe::System::MountablePath::Unmount;
        bindMountablePath["Paths"] = &obe::System::MountablePath::Paths;
        bindMountablePath["StringPaths"] = &obe::System::MountablePath::StringPaths;
        bindMountablePath["Sort"] = &obe::System::MountablePath::Sort;
        bindMountablePath["pathType"] = &obe::System::MountablePath::pathType;
        bindMountablePath["basePath"] = &obe::System::MountablePath::basePath;
        bindMountablePath["priority"] = &obe::System::MountablePath::priority;
    }
    void LoadClassPath(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::Path> bindPath
            = SystemNamespace.new_usertype<obe::System::Path>("Path",
                sol::call_constructor,
                sol::constructors<obe::System::Path(),
                    obe::System::Path(const std::vector<obe::System::MountablePath>&),
                    obe::System::Path(const obe::System::Path&),
                    obe::System::Path(std::string_view)>());
        bindPath["set"] = &obe::System::Path::set;
        bindPath["add"] = &obe::System::Path::add;
        bindPath["last"] = &obe::System::Path::last;
        bindPath["getPath"] = &obe::System::Path::getPath;
        bindPath["find"] = sol::overload(
            [](obe::System::Path* self) -> std::string { return self->find(); },
            [](obe::System::Path* self, obe::System::PathType pathType) -> std::string {
                return self->find(pathType);
            });
        bindPath["findAll"] = sol::overload(
            [](obe::System::Path* self) -> std::vector<std::string> {
                return self->findAll();
            },
            [](obe::System::Path* self, obe::System::PathType pathType)
                -> std::vector<std::string> { return self->findAll(pathType); });
        bindPath["toString"] = &obe::System::Path::toString;
        bindPath["operator="] = &obe::System::Path::operator=;
    }
    void LoadClassPlugin(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::Plugin> bindPlugin
            = SystemNamespace.new_usertype<obe::System::Plugin>("Plugin",
                sol::call_constructor,
                sol::constructors<obe::System::Plugin(
                    const std::string&, const std::string&)>(),
                sol::base_classes, sol::bases<obe::Types::Identifiable>());
        bindPlugin["onLoadBindings"] = &obe::System::Plugin::onLoadBindings;
        bindPlugin["onUpdate"] = &obe::System::Plugin::onUpdate;
        bindPlugin["onRender"] = &obe::System::Plugin::onRender;
        bindPlugin["onExit"] = &obe::System::Plugin::onExit;
        bindPlugin["hasOnInit"] = &obe::System::Plugin::hasOnInit;
        bindPlugin["hasOnLoadBindings"] = &obe::System::Plugin::hasOnLoadBindings;
        bindPlugin["hasOnUpdate"] = &obe::System::Plugin::hasOnUpdate;
        bindPlugin["hasOnRender"] = &obe::System::Plugin::hasOnRender;
        bindPlugin["hasOnExit"] = &obe::System::Plugin::hasOnExit;
    }
    void LoadClassWindow(sol::state_view state)
    {
        sol::table SystemNamespace = state["obe"]["System"].get<sol::table>();
        sol::usertype<obe::System::Window> bindWindow
            = SystemNamespace.new_usertype<obe::System::Window>("Window",
                sol::call_constructor,
                sol::constructors<obe::System::Window(vili::node)>());
        bindWindow["create"] = &obe::System::Window::create;
        bindWindow["clear"] = &obe::System::Window::clear;
        bindWindow["close"] = &obe::System::Window::close;
        bindWindow["display"] = &obe::System::Window::display;
        bindWindow["getSize"] = &obe::System::Window::getSize;
        bindWindow["isOpen"] = &obe::System::Window::isOpen;
        bindWindow["pollEvent"] = &obe::System::Window::pollEvent;
        bindWindow["setSize"] = &obe::System::Window::setSize;
        bindWindow["setTitle"] = &obe::System::Window::setTitle;
        bindWindow["setVerticalSyncEnabled"]
            = &obe::System::Window::setVerticalSyncEnabled;
        bindWindow["setView"] = &obe::System::Window::setView;
        bindWindow["getTarget"] = &obe::System::Window::getTarget;
        bindWindow["getWindow"] = &obe::System::Window::getWindow;
        bindWindow["getClearColor"] = &obe::System::Window::getClearColor;
        bindWindow["setClearColor"] = &obe::System::Window::setClearColor;
        bindWindow["setMouseCursorVisible"] = &obe::System::Window::setMouseCursorVisible;
    }
};